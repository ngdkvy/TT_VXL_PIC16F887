//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
//!#include <tv_pickit2_shift_key4x4_138.c> 
#include <tv_pickit2_shift_key4x4_138_proteus.c> 
signed int8  mp;
unsigned int8 time;
signed int8       giay,bdn;
int1 TT_chuong;

//!TT_chuong = 0 => chuong khong keu
//!TT_chuong = 1 => chuong keu

#int_timer1
void interrupt_timer1()
{
    bdn++;
    set_timer1(3036);
}
void hienthi()
{
   lcd_goto_xy(0,0);
   lcd_data("DIEU KHIEN BUZZER");
   if (TT_chuong)
   {
      lcd_goto_xy(1,0);
      lcd_data("BUZZER: ON ");
      buzzer_on();
   }
   else
   {
      lcd_goto_xy(1,0);
      lcd_data("BUZZER: OFF");
      buzzer_off();
   }
   lcd_goto_xy(1,12);
   lcd_data("TG:");
   lcd_goto_xy(1,16);
   lcd_data(time+0x30);
}
void main()
{
   set_up_port_ic_chot(); 
   setup_lcd();
   setup_timer_1(t1_internal | t1_div_by_8);
   set_timer1(3036);
   enable_interrupts(global); 
   enable_interrupts(int_timer1); 
   giay =0;
   bdn=0;
   time = 1;
   TT_chuong = 1;
   hienthi();
   while(true)
   {
      mp= key_4x4_up();
      if (mp != 0xff)
      {
         if(mp<10)   
         {
            time = mp; 
            giay = 0;
         }
         if (mp == 10)
            TT_chuong = 1;
      }
      if    (bdn<10)       hienthi();
      else
      {
         bdn = bdn-10;
         giay++;
         if (giay==time)    TT_chuong = 0;
      }
      delay_ms(200);
   }
}
