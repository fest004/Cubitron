
/* test function before infinite while loop */
void test()
{
    /* testing turning on an led on the compass V2. The V2 has PA06 as a led pin */
    /* PA06 is unconnected on Kuben, so no consequence of this */
    #define TEST_LED_Set()               (PORT_REGS->GROUP[0].PORT_OUTSET = ((uint32_t)1U << 6U))
    #define TEST_LED_Clear()             (PORT_REGS->GROUP[0].PORT_OUTCLR = ((uint32_t)1U << 6U))


    /* error led, process led */
    PORT_REGS->GROUP[0].PORT_DIRSET = (1 << 0); /* Set direction to output for PA00 */
    PORT_REGS->GROUP[0].PORT_OUTCLR = (1 << 0); /* Set it to zero */

    TEST_LED_Set();
}
