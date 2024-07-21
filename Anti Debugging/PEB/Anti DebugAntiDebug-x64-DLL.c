#include <windows.h>

BOOL WINAPI DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved )
{
    // Checks if the DLL is attached to an external process
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		_asm
		{
			// Move the address from PEB (Process Environment Block) to rax
			mov rax, qword ptr gs:[0x60]

			// Set BeingDebugged field to 0
			mov byte ptr ds:[rax+0x2], 0

			// Set NT Global Flag field to 0
			mov byte ptr ds:[rax+0xbc], 0
		}
	}
  return 0;
}
