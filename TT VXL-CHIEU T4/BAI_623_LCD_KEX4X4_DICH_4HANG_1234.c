#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
#include <tv_pickit2_shift_key4x4_138.c> 
//!#include <tv_pickit2_shift_key4x4_138_proteus.c> 
signed int8  mp, ih, jh;
unsigned int8 mp_lcd[80];

void khoitao()
{
   ih = jh = 0;
   for (ih = 0; ih < 80; ih++)
      mp_lcd[ih] = 0x20;
}
void GM_LCD()
{
   if (jh > 0)
      for (ih = jh; ih>-1; ih--)
         mp_lcd[ih] = mp_lcd[ih-1];
   if (mp < 10)   mp_lcd[0] = mp + 0x30; 
   else        mp_lcd[0] = mp + 0x37;
   if (jh < 80) jh++;
}
void hienthi_lcd()
{
   for (ih = 0; ih < jh; ih++)
   {
      lcd_goto_xy(ih/20,19-ih%20); 
      lcd_data(mp_lcd[ih]);
   }
      
}

void main()
{
    set_up_port_ic_chot(); 
    setup_lcd();
    khoitao();
    while(true)
    {
      mp= key_4x4_up();
      if (mp != 0xff)
      {
         GM_LCD();
         hienthi_lcd();
      }
      delay_ms(200);
    }
}
