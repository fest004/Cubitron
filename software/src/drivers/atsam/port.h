/* LED pin macros */

#define STAT1_LED_Set()               (PORT->GROUP[1].PORT_OUTSET = ((uint32_t)1U << 22U))
#define STAT1_LED_Clear()             (PORT->GROUP[1].PORT_OUTCLR = ((uint32_t)1U << 22U))
#define STAT1_LED_Toggle()            (PORT->GROUP[1].PORT_OUTTGL = ((uint32_t)1U << 22U))
#define STAT1_LED_OutputEnable()      (PORT->GROUP[1].PORT_DIRSET = ((uint32_t)1U << 22U))
#define STAT1_LED_InputEnable()       (PORT->GROUP[1].PORT_DIRCLR = ((uint32_t)1U << 22U))

#define STAT2_LED_Set()               (PORT->GROUP[1].PORT_OUTSET = ((uint32_t)1U << 23U))
#define STAT2_LED_Clear()             (PORT->GROUP[1].PORT_OUTCLR = ((uint32_t)1U << 23U))
#define STAT2_LED_Toggle()            (PORT->GROUP[1].PORT_OUTTGL = ((uint32_t)1U << 23U))
#define STAT2_LED_OutputEnable()      (PORT->GROUP[1].PORT_DIRSET = ((uint32_t)1U << 23U))
#define STAT2_LED_InputEnable()       (PORT->GROUP[1].PORT_DIRCLR = ((uint32_t)1U << 23U))

#define STAT3_LED_Set()               (PORT->GROUP[0].PORT_OUTSET = ((uint32_t)1U << 23U))
#define STAT3_LED_Clear()             (PORT->GROUP[0].PORT_OUTCLR = ((uint32_t)1U << 23U))
#define STAT3_LED_Toggle()            (PORT->GROUP[0].PORT_OUTTGL = ((uint32_t)1U << 23U))
#define STAT3_LED_OutputEnable()      (PORT->GROUP[0].PORT_DIRSET = ((uint32_t)1U << 23U))
#define STAT3_LED_InputEnable()       (PORT->GROUP[0].PORT_DIRCLR = ((uint32_t)1U << 23U))


#define PROCLED_LED_Set()               (PORT->GROUP[0].PORT_OUTSET = ((uint32_t)1U << 00U))
#define PROCLED_LED_Clear()             (PORT->GROUP[0].PORT_OUTCLR = ((uint32_t)1U << 00U))
#define PROCLED_LED_Toggle()            (PORT->GROUP[0].PORT_OUTTGL = ((uint32_t)1U << 00U))
#define PROCLED_LED_OutputEnable()      (PORT->GROUP[0].PORT_DIRSET = ((uint32_t)1U << 00U))
#define PROCLED_LED_InputEnable()       (PORT->GROUP[0].PORT_DIRCLR = ((uint32_t)1U << 00U))

#define ERRLED_LED_Set()               (PORT->GROUP[0].PORT_OUTSET = ((uint32_t)1U << 01U))
#define ERRLED_LED_Clear()             (PORT->GROUP[0].PORT_OUTCLR = ((uint32_t)1U << 01U))
#define ERRLED_LED_Toggle()            (PORT->GROUP[0].PORT_OUTTGL = ((uint32_t)1U << 01U))
#define ERRLED_LED_OutputEnable()      (PORT->GROUP[0].PORT_DIRSET = ((uint32_t)1U << 01U))
#define ERRLED_LED_InputEnable()       (PORT->GROUP[0].PORT_DIRCLR = ((uint32_t)1U << 01U))




