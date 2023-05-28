.globl __dyld_start
.align 4

__dyld_start:
    mov x0, sp
    and sp, x0, ~15
    mov fp, sp
    mov lr, xzr
    b start
    b .
