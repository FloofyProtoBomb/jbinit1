#include <fakedyld/fakedyld.h>

int main(int argc, char* argv[], char* envp[], char* apple[]) {
    int console_fd = open("/dev/console", O_RDWR, 0);
    set_console_fd(console_fd);
    if (console_fd == -1) spin();
    printf(
        "=============================================================\n"
        "!!! NICK CHAN AND PLOOSH DYNAMICALLY LINKING AND PATCHING !!!\n"
        "=============================================================\n"
        "                   (c) 2023 palera1n team                    \n"
        "=============================================================\n"
    );
    struct paleinfo pinfo;
    get_pinfo(&pinfo);
    printf(
        "kbase: 0x%llx\n"
        "kslide: 0x%llx\n"
        "flags: 0x%llx\n"
        "rootdev: %s\n"
    ,pinfo.kbase,pinfo.kslide,pinfo.flags,pinfo.rootdev
    );


    spin();
    __builtin_unreachable();
}
