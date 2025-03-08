#ifndef MAIN_H
#define MAIN_H

#include <xc.h>
#include"clcd.h"
#include"matrix_keypad.h"
#include"timers.h"


#define MICRO_MODE     0x03
#define MODE_RESET     0x10
#define GRILL_MODE     0x04
#define CONVECTION_MODE  0x05
#define TIME_DISPLAY     0x06
#define FAN             RC2
#define FAN_DDR        TRISC2
#define ON              1
#define OFF             0
#define RESET_NOTHING     0x0f
#define BUZZER          RC1
#define BUZZER_DDR        TRISC1
void clear_screen(void);

void power_on_screen(void);
void menu_display_screen(void);
void set_time(unsigned char key,int reset_flag);
void time_screen(void);

#endif /* MAIN_H */