#include <stddef.h>
#include <sys/types.h>

void _exit(int status) {
    while(1); // Infinite loop, no OS to return to
}

off_t _lseek(int fd, off_t offset, int whence) {
    return -1;  // currently not supported
}

int _close(int fd) {
    return -1;  // currently not supported
}

int _read(int fd, char *buf, size_t count) {
    // You can add your own logic here to read from hardware if needed
    return 0;
}

int _write(int fd, const char *buf, size_t count) {
    // Write data to a UART or another output (e.g., debug output)
    for (size_t i = 0; i < count; i++) {
        // Insert logic here to send `buf[i]` via a UART or other interface
        // Example: UART_SendByte(buf[i]);
    }

    return count;  // Return the number of bytes written
}

char *_sbrk(int incr) {
    return (char *)-1;  // Indicate an error (heap allocation not supported)
}
