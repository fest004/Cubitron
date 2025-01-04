#include "definitions.h"
#include <stddef.h>

#include "drivers/atsam/sercom.h"

// Main application entry point
int main(void)
{
    enable_sercom_instances();
    while (1)
    {
        // Application code
    }
}

// Function prototypes
void SystemInit(void);

// Reset handler
void Reset_Handler(void)
{
    SystemInit(); // Perform necessary system initialization
    main();       // Jump to main function
}

void SystemInit(void)
{
    // Initialize clocks, peripherals, etc.
}



// Vector table
__attribute__((section(".isr_vector"))) void (*vector_table[])(void) = {
    (void (*)(void))(0x20020000),  // Initial stack pointer
    Reset_Handler                 // Reset handler
};


void *_sbrk(ptrdiff_t incr) {
    extern char _end; // Defined in your linker script
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0) {
        heap_end = &_end;
    }
    prev_heap_end = heap_end;
    heap_end += incr;

    return (void *)prev_heap_end;
}
