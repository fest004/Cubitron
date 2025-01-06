OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
SEARCH_DIR(.)

/*
 *  Define the __XC32_RESET_HANDLER_NAME macro on the command line when you
 *  want to use a different name for the Reset Handler function.
 */

#ifndef __XC32_RESET_HANDLER_NAME
#define __XC32_RESET_HANDLER_NAME Reset_Handler
#endif /* __XC32_RESET_HANDLER_NAME */

/*  Set the entry point in the ELF file. Once the entry point is in the ELF
 *  file, you can then use the --write-sla option to xc32-bin2hex to place
 *  the address into the hex file using the SLA field (RECTYPE 5). This hex
 *  record may be useful for a bootloader that needs to determine the entry
 *  point to the application.
 */
ENTRY(__XC32_RESET_HANDLER_NAME)

/*************************************************************************
 * Memory-Region Definitions
 * The MEMORY command describes the location and size of blocks of memory
 * on the target device. The command below uses the macros defined above.
 *************************************************************************/
MEMORY
{
    rom (rx) : ORIGIN = 0x00000000, LENGTH = 256K
    ram (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
    /* tcm (rwx) : ORIGIN = 0x0, LENGTH = 0x0              Tightly Coupled Memory TODO */
    bkupram (rwx) : ORIGIN = 0x47000000, LENGTH = 0x100000
}

/*************************************************************************
 * Section Definitions - Map input sections to output sections
 *************************************************************************/

SECTIONS
{
    .vectors :
    {
        . = ALIGN(4);
        KEEP(*(.vectors))
        KEEP(*(.isr_vector))  /* Interrupt vector table */
    } > rom

    .text :
    {
        . = ALIGN(4);
        *(.text)             /* Program code */
    } > rom

    .data :
    {
        . = ALIGN(4);
        *(.data)             /* Initialized data */
    } > ram

    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss)
        . = ALIGN(4);
        __bss_end__ = .;
        _end = .;    /* Define _end after all sections to mark the end of memory used by the program */
    } > ram
}

