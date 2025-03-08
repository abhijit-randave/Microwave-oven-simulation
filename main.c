
#include "main.h"

#pragma config WDTE=OFF
unsigned char sec=0,min=0;
int operation_flag= 0x01;
static void init_config(void)
{
init_clcd();
init_matrix_keypad();
FAN_DDR =0;
FAN=OFF;
BUZZER_DDR =0;
BUZZER=OFF;
init_timer2();
GIE=1;
PEIE=1;
       
}

void main(void) {
    init_config();
    int operation_flag= 0x01;
    int reset_flag;
    unsigned char key;
    while(1)
    {
       
        key = read_matrix_keypad(STATE);
        if(operation_flag==0x02)
        {
        if(key==1)
        {
            operation_flag= 0x03;
            reset_flag= 0x10;
            clear_screen();
            clcd_print("  Power = 900W   ",LINE2(0));
             __delay_ms(3000);
             clear_screen();
        }
        }
        switch(operation_flag)
        {
            case 0x01:
                power_on_screen();
                operation_flag=0x02;
                clear_screen();
                break;
               
            case 0x02:
                 menu_display_screen();
                 break;
                 
            case  0x03:
                set_time(key,reset_flag);
               
                break;
               
          case 0x06:
            //  clear_screen();
               time_screen();
                break;

        }
        reset_flag= RESET_NOTHING ;

    }
   
}
 void time_screen(void)
{
 
      clcd_print("time=",LINE1(0));
     
     clcd_putch(min/10+'0',LINE1(9));
     clcd_putch(min%10+'0',LINE1(10));
     clcd_putch(':',LINE1(11));
     clcd_putch(sec/10+'0',LINE1(12));
     clcd_putch(sec%10+'0',LINE1(13));  
     
     clcd_print(" 4.Start/Resume",LINE2(0));
     clcd_print(" 5.Pause",LINE3(0));
     clcd_print(" 6.Stop",LINE4(0));
   
/*     if((sec == 0)&&(min == 0))
     {
         clear_screen();
         clcd_print(" TIME UP !",LINE2(0));
         BUZZER=ON;
         __delay_ms(3000);
         clear_screen();
         BUZZER=OFF;
         FAN=OFF;
         TMR2ON = OFF;
         operation_flag=0x02;
     }*/
     
}
   
void clear_screen(void)
{
     clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    __delay_us(500);
}
 void power_on_screen(void)
 {
     unsigned char i;
     for(i=0;i<16;i++)
     {
         clcd_putch(BAR,LINE1(i));
         __delay_ms(100);
     }
     
     
     clcd_print("  Powering ON   ",LINE2(0));
     clcd_print(" Microwave Oven ",LINE3(0));
     for(i=0;i<16;i++)
     {
         clcd_putch(BAR,LINE4(i));
         __delay_ms(100);
     }
     __delay_ms(3000);
     
 }
 
 
 
  void menu_display_screen(void)
  {
      clcd_print("1.Micro",LINE1(0));
      clcd_print("2.Grill",LINE2(0));
      clcd_print("3.Convection",LINE3(0));
      clcd_print("4.Start",LINE4(0));
  }
  void set_time(unsigned char key,int reset_flag)
  {
      static unsigned char key_count,blink_pos,blink;
      static int wait;
      if(reset_flag == MODE_RESET)
      {
          key_count=0;
          sec=0;
          min=0;
          blink_pos=0;
          key=ALL_RELEASED;
          wait=0;
          blink=0;
      clcd_print("SET TIME (MM:SS)",LINE1(0));
      clcd_print("TIME-",LINE2(0));
      clcd_print("*:CLEAR  #:ENTER",LINE4(0));
     
      }
     
      if((key!='*')&&(key!='#')&&(key!=ALL_RELEASED))
      {  
          key_count++;
          if(key_count<=2)
          {
              sec=sec*10+key;
               blink_pos=0;
          }
          else if(key_count>2 && key_count<=4)
          {
               min=min*10+key;
                blink_pos=1;
          }
      }
          else if(key=='*')
          {
              if( blink_pos == 0)
              {
                  sec=0;
                  key_count=0;
              }
              else if( blink_pos == 1)
              {
                  min=0;
                  key_count=2;
              }
          }
       else if(key == '#')
          {
             
            operation_flag = 0x06;
              FAN=ON;
              TMR2ON = ON;
             
          }
       if(wait++ ==15)
          {
              wait=0;
              blink =  !blink;
              clcd_putch(min/10+'0',LINE2(6));
              clcd_putch(min%10+'0',LINE2(7));
              clcd_putch(':',LINE2(8));
              clcd_putch(sec/10+'0',LINE2(9));
              clcd_putch(sec%10+'0',LINE2(10));
             
          }
      if(blink)
      {
          switch(blink_pos)
          {
              case 0:
                   clcd_print("  ",LINE2(9));
                  break;
              case 1:
                  clcd_print("  ",LINE2(6));
                  break;
          }
      }
  }
