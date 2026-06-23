#include "main.h"
#include "global.h"
#include "microwave_oven.h"
static unsigned char field = 0; // 0=MM, 1=SS
static unsigned char temp;

void clear_screen(void) {
    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
}

void power_on_screen(void) {
    for (unsigned char i = 0; i < 16; i++) {
        clcd_putch(0xFF, LINE1(i));

        __delay_ms(400);

        if (i == 10) {
            clcd_print("Powering On...", LINE2(0));
            clcd_print("Microwave Oven", LINE3(0));
        }

    }
    for (unsigned char j = 0; j < 16; j++) {
        clcd_putch(0xFF, LINE4(j));
        __delay_ms(200);

    }

}

void menu_screen(void) {
    clcd_print("1.Micro", LINE1(0));
    clcd_print("2.Grill", LINE2(0));
    clcd_print("3.Convection", LINE3(0));
    clcd_print("4.Start", LINE4(0));
}

void micro_menu_mode(void) {
    unsigned char k = key;

    clcd_print("SET TIME <MM:SS> ", LINE1(0));
    clcd_print("TIME:", LINE2(0));
    /* Minute Field */
    if (field == 0 && blink_F) {
        clcd_print("  ", LINE2(6));
    } else {
        clcd_putch((minute / 10) + '0', LINE2(6));
        clcd_putch((minute % 10) + '0', LINE2(7));
    }

    clcd_putch(':', LINE2(8));

    /* Second Field */
    if (field == 1 && blink_F) {
        clcd_print("  ", LINE2(9));
    } else {
        clcd_putch((second / 10) + '0', LINE2(9));
        clcd_putch((second % 10) + '0', LINE2(10));
    }

    clcd_print("*:CLEAR", LINE4(0));
    clcd_print("#:ENTER", LINE4(8));

    if (k != ALL_RELEASED && k <= 9) {
        if (field == 0) {
            minute = ((minute % 10) * 10) + k;
        } else {
            unsigned char temp = ((second % 10) * 10) + k;

            if (temp <= 59) {
                second = temp;
            }
        }
    }

    if (k == '*') {
        minute = 0;
        second = 0;
        field = 0;
    }

    if (k == '#') {
        if (field == 0) {
            field = 1;
        } else {
            total_seconds = (minute * 60) + second;

            run_flag = 1;
            pause_flag = 0;

            field = 0;
            operational_flag = START_MODE_SCREEN;

            clear_screen();

            TMR2ON = 1;
            FAN = 1;
        }
    }
}

void convection_mode(void) {
    unsigned char k = key;

    static unsigned char temp_digits = 0;
    static unsigned char min_digits = 0;
    static unsigned char sec_digits = 0;

    clcd_print("SET TEMP <*C>", LINE1(0));

    /* Temperature */
    clcd_print("TEMP:", LINE2(0));

    if (field == 0 && blink_F) {
        clcd_print("   ", LINE2(6));
    } else {
        clcd_putch((temp / 100) + '0', LINE2(6));
        clcd_putch(((temp / 10) % 10) + '0', LINE2(7));
        clcd_putch((temp % 10) + '0', LINE2(8));
    }

    clcd_putch(0xDF, LINE2(9));
    clcd_putch('C', LINE2(10));

    /* Time */
    clcd_print("TIME:", LINE3(0));

    if (field == 1 && blink_F) {
        clcd_print("  ", LINE3(6));
    } else {
        clcd_putch((minute / 10) + '0', LINE3(6));
        clcd_putch((minute % 10) + '0', LINE3(7));
    }

    clcd_putch(':', LINE3(8));

    if (field == 2 && blink_F) {
        clcd_print("  ", LINE3(9));
    } else {
        clcd_putch((second / 10) + '0', LINE3(9));
        clcd_putch((second % 10) + '0', LINE3(10));
    }

    clcd_print("*:CLR", LINE4(0));
    clcd_print("#:ENTER", LINE4(8));

    /* Numeric Entry */
    if (k != ALL_RELEASED && k <= 9) {
        if (field == 0) {
            if (temp_digits == 0) {
                temp = k;
                temp_digits = 1;
            } else if (temp_digits == 1) {
                temp = (temp * 10) + k;
                temp_digits = 2;
            } else {
                temp = (temp * 10) + k;

                if (temp > 250) {
                    temp = 250;
                }

                temp_digits = 3;
            }
        } else if (field == 1) {
            minute = ((minute % 10) * 10) + k;

            if (++min_digits >= 2) {
                min_digits = 2;
            }
        } else if (field == 2) {
            unsigned char s;

            s = ((second % 10) * 10) + k;

            if (s <= 59) {
                second = s;
            }

            if (++sec_digits >= 2) {
                sec_digits = 2;
            }
        }
    }

    /* Clear */
    if (k == '*') {
        if (field == 0) {
            temp = 0;
            temp_digits = 0;
        } else if (field == 1) {
            minute = 0;
            min_digits = 0;
        } else {
            second = 0;
            sec_digits = 0;
        }
    }

    /* Next */
    if (k == '#') {
        if (field == 0) {
            field = 1;
        } else if (field == 1) {
            field = 2;
        } else {
            temperature = temp;
            total_seconds = (minute * 60) + second;

            run_flag = 1;
            pause_flag = 0;

            field = 0;

            temp_digits = 0;
            min_digits = 0;
            sec_digits = 0;

            operational_flag = START_MODE_SCREEN;

            clear_screen();
            FAN = 1;
            TMR2ON = 1;
        }
    }
}

void update_countdown(void) {
    if (run_flag == 0)
        return;

    if (one_sec_flag == 0)
        return;

    one_sec_flag = 0;

    if (total_seconds > 0) {
        total_seconds--;

        minute = total_seconds / 60;
        second = total_seconds % 60;
    } else {
        TMR2ON = 0;
        run_flag = 0;
        pause_flag = 0;


        clear_screen();

        clcd_print("Enjoy Your Meal", LINE2(1));
        field = 0;

        if (minute == 0 && second == 0) {
            FAN = 0;
            for (unsigned char l = 0; l < 5; l++) {
                BUZZER = 1;
                __delay_ms(500);
                BUZZER = 0;
                __delay_ms(500);
            }
        }

        clear_screen();

        operational_flag = MENU_SCREEN;
    }
}

void start(void) {
    FAN = 1;
    char str[6];
    unsigned char start_key = (key == 4);
    unsigned char pause_key = (key == 5);
    unsigned char stop_key = (key == 6);



    str[0] = (minute / 10) + '0';
    str[1] = (minute % 10) + '0';
    str[2] = ':';
    str[3] = (second / 10) + '0';
    str[4] = (second % 10) + '0';
    str[5] = '\0';

    clcd_print("TIME :", LINE1(0));
    clcd_print(str, LINE1(7));

    clcd_print("4.START", LINE2(0));
    clcd_print("5.PAUSE", LINE3(0));
    clcd_print("6.STOP ", LINE4(0));
    if (start_key) {
        run_flag = 1;
        pause_flag = 0;
        TMR2ON = 1;

    }

    if (pause_key) {
        run_flag = 0;
        pause_flag = 1;
        TMR2ON = 0;

    }

    if (stop_key) {
        run_flag = 0;
        pause_flag = 0;
        TMR2ON = 0;
        

        total_seconds = 0;

        minute = 0;
        second = 0;

        operational_flag = MENU_SCREEN;

        clear_screen();
    }

}