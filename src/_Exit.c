void __builtin_trap();
void _Exit() { __builtin_trap() };
