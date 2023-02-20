#include <unistd.h>
#include <stdlib.h>

void __builtin_trap();
void _Exit() { __builtin_trap(); };

_Noreturn void _exit(int status)
{
	_Exit(status);
}
