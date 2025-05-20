#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
#include <tv_pickit2_shift_key4x4_138.c> 
//!#include <tv_pickit2_shift_key4x4_138_proteus.c> 
signed int8  mp;
void hienthi_lcd()
{
    lcd_goto_xy(0,19);
    if(mp<10)   lcd_data(mp+0x30); 
    else        lcd_data(mp+0x37);
}

void main()
{
    set_up_port_ic_chot(); 
    setup_lcd();

    lcd_goto_xy(0,0);
    lcd_data("hay nhan phim:");

    while(true)
    {
      mp= key_4x4_up();
      if (mp != 0xff)
      {
         hienthi_lcd();
      }
      delay_ms(200);
    }
}
