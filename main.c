#include "main.h"
#include "global.h"

#pragma config WDTE = OFF

unsigned char key;
unsigned char operational_flag;

unsigned char minute = 0;
unsigned char second = 0;

unsigned int temperature = 180;



unsigned char run_flag = 0;
unsigned char pause_flag = 0;

volatile unsigned char one_sec_flag = 0;

unsigned char blink_F = 0;

unsigned int total_seconds = 0;

void init_config(void) {
    
    init_clcd();
    init_matrix_keypad();
    init_timer2();

#ifdef DEBUG
    init_uart(9600);
#endif

    FAN_DDR = 0;
    BUZZER_DDR = 0;
    FAN = 0;
    BUZZER = 0;
    GIE = 1;
    PEIE = 1;
    TMR2IE = 1;
}

void main(void) {
    init_config();

    clear_screen();
    power_on_screen();

    __delay_ms(1500);

    clear_screen();

    operational_flag = MENU_SCREEN;

    while (1) {
        key = read_matrix_keypad(STATE);

        /* Timer countdown */
        update_countdown();


        switch (operational_flag) {
            case MENU_SCREEN:

                menu_screen();

                if (key != ALL_RELEASED) {
                    if (key == 1) {
                        clear_screen();

                        clcd_print("Power = 900W", LINE2(2));
                        clcd_print("MICRO MODE", LINE3(2));

                        __delay_ms(2000);

                        clear_screen();

                        operational_flag = MICRO_MODE_SCREEN;

                        TMR2ON = 1;
                    } else if (key == 2) {
                        clear_screen();

                        clcd_print("Power = 900W", LINE2(2));
                        clcd_print("GRILL MODE", LINE3(2));

                        __delay_ms(2000);

                        clear_screen();

                        operational_flag = GRILL_MODE_SCREEN;

                        TMR2ON = 1;
                    } else if (key == 3) {
                        clear_screen();

                        clcd_print("Power = 900W", LINE2(2));
                        clcd_print("CONVECTION MODE", LINE3(1));

                        __delay_ms(2000);

                        clear_screen();

                        operational_flag = CONVECTION_MODE_SCREEN;

                        TMR2ON = 1;
                    } else if (key == 4) {
                        clear_screen();

                        minute = 1;
                        second = 0;

                        total_seconds = 60;

                        run_flag = 1;
                        pause_flag = 0;

                        TMR2ON = 1;

                        operational_flag = START_MODE_SCREEN;
                    }
                }
                break;

            case MICRO_MODE_SCREEN:
                micro_menu_mode();
                break;

            case GRILL_MODE_SCREEN:
                micro_menu_mode();
                break;

            case CONVECTION_MODE_SCREEN:
                convection_mode();
                break;

            case START_MODE_SCREEN:
                start();
                break;

            default:
                operational_flag = MENU_SCREEN;
                break;
        }
    }
}