.globl _msyscall

/*
XNU syscall ABI:
- The immediate passed to svc is ignored, but the standard library uses svc 0x80
- x16 holds the syscall number
- x0 through x8 hold up to 9 arguments
- There are no arguments on the stack
- x0 and x1 hold up to 2 return values (e.g. in the case of fork)
- The carry bit is used to report an error, in which case x0 holds the error code
*/
.align 4
_msyscall:
    mov x16, x0
    ldp x0, x1, [sp]
    ldp x2, x3, [sp, 0x10]
    ldp x4, x5, [sp, 0x20]
    ldp x6, x7, [sp, 0x30]
    ldr x8, [sp, 0x40]
    svc 0
    b.cs _msyscall_botch
_msyscall_epilog:
    ret
_msyscall_botch:
    stp fp, lr, [sp, #-16]!
    mov fp, sp
    bl _cerror
    ldp fp, lr, [sp], #16

    mov w0, #-1
    b _msyscall_epilog
