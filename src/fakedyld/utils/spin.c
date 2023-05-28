#include <fakedyld/fakedyld.h>

void spin() {
    printf("spinning...\n");
    while(1) {
        sleep(5);
    }
}
