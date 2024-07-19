#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

//int NTGlobalFlag_x86()
//{
//	unsigned char Flag = 0;
//
//	_asm
//	{
//		// Move the address from PEB (Process Environment Block) to eax
//		mov eax, dword ptr fs:[0x30]
//
//		// The NT Global Flag is located at: PEB + 0x2
//		mov cl, [eax + 0x68]
//
//		// Move the NT Global Flag to the variable Flg
//		mov byte ptr[Flag], cl
//	}
//
//	// Convert ASCII to int and return the result
//	return Flag;
//}

int NTGlobalFlag_x64()
{
	unsigned char Flag = 0;

	_asm
	{
		// Move the address from PEB (Process Environment Block) to rax
		mov rax, qword ptr gs:[0x60]

		// The NT Global Flag is located at: PEB + 0x2
		mov cl, [rax + 0xbc]

		// Move the NT Global Flag to the variable Flg
		mov byte ptr[Flag], cl
	}

	// Convert ASCII to int and return the result
    return Flag;
}



int main()
{
	printf(">> Anti-Debugger example << \n\n");

	while(1)
	{
		Sleep(1000);

		// Check if IsDebuggerPresent has detected a debugger
		if (IsDebuggerPresent() == true)
		{
			printf("IsDebuggerPresent --> Debugger detected !!!\n");
		}

		else
		{
			printf("IsDebuggerPresent --> No debugger detected\n");
		}

		// When the NT Global Flag is 1 then a debugger has been attached to the process
		if (NTGlobalFlag_x64() != 0)
		{
			printf("NT Global Flag --> Debugger detected !!!\n");
		}

		else
		{
			printf("NT Global Flag --> No debugger detected\n");
		}

		printf("\n");
    }

	return 0;
}





