//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
unsigned int32 y;
unsigned int8 i;

void sangdan_18led_giua()
{
   y = 0;
   xuat_32led_don_1dw(y);
   delay_ms(100);
   for (i = 0 ; i<4; i++)
   {
      y = ((y>>3) | 0x001C0000) & 0x1FF800;
      xuat_32led_don_1dw(y);
      delay_ms(100);
   }
   y = 0;
   xuat_32led_don_1dw(y);
   delay_ms(100);
   for (i = 0 ; i<4; i++)
   {
      y = ((y<<3) | 0x3800) & 0x1FF800;
      xuat_32led_don_1dw(y);
      delay_ms(100);
   }
}
void main()
{
   set_up_port_ic_chot();
   while (true)
   {
      sangdan_18led_giua();
   }
}
