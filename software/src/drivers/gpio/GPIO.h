#include "../../definitions.h"



/* LED pin macros */
/* IMPORTANT! Ports must be initialized before using these macros, or else they wont work! */
/* todo, fix syntax here. semantically correct but syntactically wrong! */
#define STAT1_LED_Set()               (PORT_REGS->GROUP[1].PORT_OUTSET = ((uint32_t)1U << 22U))
#define STAT1_LED_Clear()             (PORT_REGS->GROUP[1].PORT_OUTCLR = ((uint32_t)1U << 22U))
#define STAT1_LED_Toggle()            (PORT_REGS->GROUP[1].PORT_OUTTGL = ((uint32_t)1U << 22U))
#define STAT1_LED_OutputEnable()      (PORT_REGS->GROUP[1].PORT_DIRSET = ((uint32_t)1U << 22U))
#define STAT1_LED_InputEnable()       (PORT_REGS->GROUP[1].PORT_DIRCLR = ((uint32_t)1U << 22U))

#define STAT2_LED_Set()               (PORT_REGS->GROUP[1].PORT_OUTSET = ((uint32_t)1U << 23U))
#define STAT2_LED_Clear()             (PORT_REGS->GROUP[1].PORT_OUTCLR = ((uint32_t)1U << 23U))
#define STAT2_LED_Toggle()            (PORT_REGS->GROUP[1].PORT_OUTTGL = ((uint32_t)1U << 23U))
#define STAT2_LED_OutputEnable()      (PORT_REGS->GROUP[1].PORT_DIRSET = ((uint32_t)1U << 23U))
#define STAT2_LED_InputEnable()       (PORT_REGS->GROUP[1].PORT_DIRCLR = ((uint32_t)1U << 23U))

#define STAT3_LED_Set()               (PORT_REGS->GROUP[0].PORT_OUTSET = ((uint32_t)1U << 23U))
#define STAT3_LED_Clear()             (PORT_REGS->GROUP[0].PORT_OUTCLR = ((uint32_t)1U << 23U))
#define STAT3_LED_Toggle()            (PORT_REGS->GROUP[0].PORT_OUTTGL = ((uint32_t)1U << 23U))
#define STAT3_LED_OutputEnable()      (PORT_REGS->GROUP[0].PORT_DIRSET = ((uint32_t)1U << 23U))
#define STAT3_LED_InputEnable()       (PORT_REGS->GROUP[0].PORT_DIRCLR = ((uint32_t)1U << 23U))


#define PROCLED_LED_Set()               (PORT_REGS->GROUP[0].PORT_OUTSET = ((uint32_t)1U << 00U))
#define PROCLED_LED_Clear()             (PORT_REGS->GROUP[0].PORT_OUTCLR = ((uint32_t)1U << 00U))
#define PROCLED_LED_Toggle()            (PORT_REGS->GROUP[0].PORT_OUTTGL = ((uint32_t)1U << 00U))
#define PROCLED_LED_OutputEnable()      (PORT_REGS->GROUP[0].PORT_DIRSET = ((uint32_t)1U << 00U))
#define PROCLED_LED_InputEnable()       (PORT_REGS->GROUP[0].PORT_DIRCLR = ((uint32_t)1U << 00U))

#define ERRLED_LED_Set()               (PORT_REGS->GROUP[0].PORT_OUTSET = ((uint32_t)1U << 01U))
#define ERRLED_LED_Clear()             (PORT_REGS->GROUP[0].PORT_OUTCLR = ((uint32_t)1U << 01U))
#define ERRLED_LED_Toggle()            (PORT_REGS->GROUP[0].PORT_OUTTGL = ((uint32_t)1U << 01U))
#define ERRLED_LED_OutputEnable()      (PORT_REGS->GROUP[0].PORT_DIRSET = ((uint32_t)1U << 01U))
#define ERRLED_LED_InputEnable()       (PORT_REGS->GROUP[0].PORT_DIRCLR = ((uint32_t)1U << 01U))




/* function prototypes: */
void ports_init(void);
void configure_pin(uint8_t group, uint8_t pin, uint8_t pmux_function);
