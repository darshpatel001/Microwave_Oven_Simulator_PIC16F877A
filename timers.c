#include "main.h"
#include "global.h"


void init_timer2(void)
{
    /* Prescaler 1:16 */
    T2CKPS0 = 1;
    T2CKPS1 = 1;

    /* Period register */
    PR2 = 250;

    TMR2IF = 0;
    TMR2IE = 1;

    TMR2ON = 0;
}

void __interrupt() isr(void)
{
    static unsigned int blink_count = 0;
    static unsigned int one_sec_count = 0;

    if(TMR2IF)
    {
        TMR2IF = 0;

        if(++blink_count >= 622)
        {
            blink_count = 0;
            blink_F ^= 1;
        }

        if(++one_sec_count >= 1245)
        {
            one_sec_count = 0;
            one_sec_flag = 1;
        }
    }
}