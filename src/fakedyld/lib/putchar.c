#include <fakedyld/fakedyld.h>
#define ALLOC_FAILED_MSG "fakedyld: could not allocate log buffer!\nspinning...\n"
#define LINEBUF_SIZE 1024
#define LOGBUF_SIZE 0x10000

static char* log_buffer = NULL;
static int console_fd = -1;
static int log_fd = -1;

void _debug_putchar(char character, void* fd) {
    write(*(int*)fd, &character, 1);
}


void _putchar(char character) {
    static char linebuf[LINEBUF_SIZE];
    static uint64_t linebuf_counter = 0;
    static uint64_t logbuf_counter = 0;
    linebuf[linebuf_counter] = character;
    linebuf_counter++;
    /* log_buffer and linebuf are buffers, NOT strings */
    if (log_buffer == NULL) {
        log_buffer = mmap(NULL, LOGBUF_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
        if (log_buffer == MAP_FAILED) {
            write(console_fd,ALLOC_FAILED_MSG, sizeof(ALLOC_FAILED_MSG)-1);
            while(1) { sleep(5); }
        }
    }
    if (linebuf_counter < LINEBUF_SIZE && character != '\n') return;
    if (console_fd != -1) write(console_fd, linebuf, linebuf_counter);
    if (log_fd != -1) write(log_fd, linebuf, linebuf_counter);
    if ((logbuf_counter += linebuf_counter) < LOGBUF_SIZE && log_buffer != MAP_FAILED)
        memcpy(&log_buffer[logbuf_counter], linebuf, linebuf_counter);
    logbuf_counter += linebuf_counter;
    linebuf_counter = 0;
}

int putchar(int c) {
    _putchar((char)c);
    return ((int)((char)c));
}

int set_console_fd(int fd) {
    return (console_fd = fd);
}

void disable_log_buffer() {
    if (log_buffer == MAP_FAILED) return;
    munmap(log_buffer, LOGBUF_SIZE);
    log_buffer = MAP_FAILED;
}
