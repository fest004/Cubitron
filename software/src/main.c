#include "definitions.h"
#include <stddef.h>
#include "drivers/atsam/sercom.h"




int main(void)
{

}


// Reset handler
void Reset_Handler(void)
{
    main();       // Jump to main function
}



// Vector table
__attribute__((section(".isr_vector"))) void (*vector_table[])(void) = 
{
    (void (*)(void))(0x20020000),  // Initial stack pointer
    Reset_Handler                 // Reset handler
};


void *_sbrk(ptrdiff_t incr) 
{
    extern char _end; 
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0) {
        heap_end = &_end;
    }
    prev_heap_end = heap_end;
    heap_end += incr;

    return (void *)prev_heap_end;
}
