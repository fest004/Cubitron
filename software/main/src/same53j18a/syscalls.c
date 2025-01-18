#include <stddef.h>
#include <sys/types.h>

void _exit(int status) {
    while(1); // Infinite loop to simulate "exit" behavior
}

off_t _lseek(int fd, off_t offset, int whence) {
    return 0;  // Simply return 0 to avoid error
}

int _close(int fd) {
    // No file system, so just return 0 (success)
    return 0;
}

int _read(int fd, char *buf, size_t count) {
    // Just return 0 to indicate no data (EOF)
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

#define HEAP_SIZE  0x1000  // Size of the heap in bytes
static char heap[HEAP_SIZE];  // Static array to act as the heap
static char *heap_end = heap; // Pointer to the end of the heap

void* _sbrk(int incr) {
    char *prev_heap_end = heap_end;

    // Check if there is enough space left in the heap
    if (heap_end + incr > heap + HEAP_SIZE) {
        // Return -1 to indicate no more memory is available
        return (void*)-1;
    }

    heap_end += incr;  // Move the heap end pointer

    return (void*)prev_heap_end;  // Return the previous end of the heap
}
