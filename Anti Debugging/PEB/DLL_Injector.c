// My Youtube video: https://www.youtube.com/watch?v=ZWUeOMQIVAs

#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <tlhelp32.h>

int ReturnProcessId( char* ProcessName );

int main(int argc, char *argv[])
{

	if (argc <= 1)
	{
		printf("You need to pass a parameter: PEB.exe file.dll TargetProcess.exe.\n");
				   system("PAUSE");
		return 0;
	}

	printf("DLL: %s\n", argv[1] );
	printf("Target process: %s\n\n", argv[2] );


	char * Dll_Name = argv[2];

	unsigned ProcessID = ReturnProcessId (Dll_Name);

	if (ProcessID == -1)
	{
		printf("Unable to find the process.\n");
		printf("Press any key to continue.");
		system("PAUSE");

	}

	// Open a handle to the target process where the DLL will get injected
	HANDLE handle = OpenProcess  (PROCESS_ALL_ACCESS, false, ProcessID);

	if (handle == NULL)
	{
		printf("Unable to open process handle. Error code: %lu\n",GetLastError());
		printf("Press any key to continue.\n");

		return 0;
	}

	// Allocates memory in the target process
	void *MemoryAddress = VirtualAllocEx (handle, 0, strlen(Dll_Name), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	if (MemoryAddress == 0)
	{
		printf("Unable to allocate memory in target process. Error code: %lu\n\n",  GetLastError());
		printf("Press any key to continue.\n");

		return 0;
	}

	// Write the name of the DLL which will get injected in the previous allocated memory space
	if (WriteProcessMemory(handle, (void*) MemoryAddress , &Dll_Name[0],  strlen(Dll_Name), 0) == false)
	{
		printf("WriteProcessMemory failed. Error code: %lu\n", GetLastError());
		printf("Press any key to continue.\n");

		return 0;
	}

	// Create a remote thread inside of the target process and inject the DLL
	HANDLE RemoteThreadHandle = CreateRemoteThread (handle, 0, 0, (LPTHREAD_START_ROUTINE) GetProcAddress(GetModuleHandle("kernel32.dll"),"LoadLibraryA"), MemoryAddress, 0, 0);

	if (RemoteThreadHandle == 0)
	{
		printf("Unable to create remote thread in target process. Error code: %lu\n", GetLastError());
		printf("Press any key to continue.\n");

		return 0;
	}

	// Wait until the thread is finished with its work and goes into signal state
	DWORD ReturnState = WaitForSingleObject (RemoteThreadHandle, INFINITE);

	if (ReturnState == WAIT_OBJECT_0)
	{
		// Free the previouse allocated memory
		if (VirtualFreeEx (handle, MemoryAddress, strlen(Dll_Name), MEM_DECOMMIT) == false)
		{
			printf("VirtualFreeEx error code: %lu\n", GetLastError());
			printf("Press any key to continue.\n");

			return 0;
		}

		else
		{
			printf("The DLL has been injected.\n");
			printf("Press any key to continue.\n");
		}
	}

	return 0;
}

int ReturnProcessId( char* ProcessName )
{
	bool ProcessExists = false;
	HANDLE snap;
	PROCESSENTRY32 lppe;
	lppe.dwSize = sizeof(PROCESSENTRY32);

	snap =  CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );

	if ( snap == INVALID_HANDLE_VALUE )
	{
		return -1;
	}

	if (Process32First(snap, &lppe ) == false)
	{
		printf("[Process32First] error code: %lu", GetLastError());
	}

	do
	{
		if( ! strcmp(lppe.szExeFile, ProcessName ) )
		{
			return lppe.th32ProcessID;
		}
	}
	while (Process32Next(snap, &lppe) == 1 ) ;

	return 0;
}
