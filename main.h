/* 
 * File:   main.h
 * Author: darsh
 *
 * Created on June 3, 2026, 11:15 AM
 */

#ifndef MAIN_H
#define	MAIN_H

//#define DEBUG


#include "clcd.h"
#include "matrix_keypad.h"
#include "timers.h"
#include "microwave_oven.h"
#include <xc.h>
#include "global.h"
//#include "microwave_oven.h"

#ifdef DEBUG
#include "uart.h"
#endif


#define MENU_SCREEN            0x01
#define RUN_SCREEN             0x02

#define MICRO_MODE_SCREEN      0x03
#define GRILL_MODE_SCREEN      0x04
#define CONVECTION_MODE_SCREEN 0x05
#define START_MODE_SCREEN      0x06

#define FAN_DDR                TRISC2
#define FAN                    RC2

#define BUZZER_DDR             TRISC1
#define BUZZER                 RC1

#endif