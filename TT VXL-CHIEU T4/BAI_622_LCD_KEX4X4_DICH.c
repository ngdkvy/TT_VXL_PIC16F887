#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
#include <tv_pickit2_shift_key4x4_138.c> 
//!#include <tv_pickit2_shift_key4x4_138_proteus.c> 
signed int8  mp, i, j;
unsigned int8 mp_lcd[20];
void khoitao()
{
   j = 0;
   for (i = 0; i < 20; i++)
      mp_lcd[i] = 0x20;
}
void GM_LCD()
{
   if (j>0)
      for (i = j-1; i>-1; i--)
         mp_lcd[i] = mp_lcd[i-1];
   if(mp<10)   mp_lcd[0] = mp + 0x30; 
   else        mp_lcd[0] = mp + 0x37;
   if (j < 20) j++;
}
void hienthi_lcd()
{
   lcd_goto_xy(1,19-j);
   for (i = j-1; i>-1; i--)
     lcd_data(mp_lcd[i]);
}

void main()
{
   set_up_port_ic_chot(); 
   setup_lcd();
   khoitao();
   lcd_goto_xy(0,0);
   lcd_data("hay nhan phim:");
    while(true)
    {
      mp= key_4x4_up();
      if (mp != 0xff)
      {
         GM_LCD();
         hienthi_lcd();
      }
      delay_ms(100);
    }
}
