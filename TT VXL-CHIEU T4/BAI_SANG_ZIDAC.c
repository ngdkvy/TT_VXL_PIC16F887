#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
unsigned int32 save;
unsigned int8 i, dem;
void sang_zidac()
{
   save = 0x00000001;
   xuat_32led_don_1dw(save);
   delay_ms(100);
   dem = 31;
   while (dem > 1)
   {
      for (i = 0 ; i < dem ; i++)
      {  
         save = save << 1;
         xuat_32led_don_1dw(save);
         delay_ms(100);      
      }
      dem--;
      for (i = 0 ; i < dem; i++)
      {  
         save = save >> 1;
         xuat_32led_don_1dw(save);
         delay_ms(100);      
      }
      dem--;
   }
      
}
void main ()
{
   set_up_port_ic_chot();
   while (true)
   {
      sang_zidac();
   }
}
   
