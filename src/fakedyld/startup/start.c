#include <fakedyld/fakedyld.h>

/* This function never returns */
void start(const struct KernelArgs* kernArgs, void* preDyldMH)
__attribute__((noreturn)) __asm("start");
void start(const struct KernelArgs* kernArgs, void* preDyldMH) {
    int argc = (int)kernArgs->argc;
    const char** argv = (const char**)&kernArgs->args[0];
    const char** envp = (const char**)&kernArgs->args[argc + 1];
    const char** apple = envp;
    while (*apple != NULL) apple++;
    main(argc, (char**)argv, (char**)envp, (char**)apple);
    while(1) {
        sleep(5);
    }
}
