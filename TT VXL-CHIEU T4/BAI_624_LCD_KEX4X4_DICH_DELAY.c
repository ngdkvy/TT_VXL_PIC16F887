//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
//!#include <tv_pickit2_shift_key4x4_138.c> 
#include <tv_pickit2_shift_key4x4_138_proteus.c> 
signed int8  mp;
unsigned int8 time;

void main()
{
   set_up_port_ic_chot(); 
   setup_lcd();
   
   time = 1;
   lcd_goto_xy(0,0);
   lcd_data("DIEU KHIEN BUZZER");
   lcd_goto_xy(1,0);
   lcd_data("BUZZER: ON");
   lcd_goto_xy(1,12);
   lcd_data("TG: 1");
   buzzer_on();
   delay_ms(1000*time);  
   buzzer_off();
   lcd_goto_xy(1,8);
   lcd_data("OFF");
    while(true)
    {
      mp= key_4x4_up();
      if (mp != 0xff)
      {
         if(mp<10)   
         {
            time = mp;         
            lcd_goto_xy(1,16);
            lcd_data(mp+0x30);
         }
         if (mp == 10)
         {
            buzzer_on();
            lcd_goto_xy(1,8);
            lcd_data("ON ");
            delay_ms(1000*time);  
            buzzer_off();
            lcd_goto_xy(1,8);
            lcd_data("OFF");
         }  
      }
    }
}
