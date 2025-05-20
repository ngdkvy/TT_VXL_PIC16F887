//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
unsigned int8 i;
unsigned int32 y;

void main()
{
   set_up_port_ic_chot();
   y = 0;
   xuat_32led_don_4byte(y,y,y,y);
   delay_ms(100);
   while (true)
   {
      for (i = 0 ; i < 10; i++)
      {
         y = ((y>>1) + 0x100000) & 0x1FF800;
         xuat_32led_don_4byte(y>>24, y>>16, y>>8, y);
         delay_ms(100);
      }
      y = 0;
      xuat_32led_don_4byte(y,y,y,y);
      delay_ms(100);
      for (i = 0 ; i < 10; i++)
      {
         y = ((y>>1) + 0x800) & 0x1FF800;
         xuat_32led_don_4byte(y, y<<8, y<<16, y<<24);
         delay_ms(100);
      }
      y = 0;
      xuat_32led_don_4byte(y,y,y,y);
      delay_ms(100);
   }
}
