//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
unsigned int16 y;
unsigned int8 i;

void main()
{
   set_up_port_ic_chot();
   y=0;
   while (true)
   {
      for (i=0;i<16;i++)
      {
         xuat_32led_don_2word(0,y);
         delay_ms(300);
         y= (y<<1) + 1;
      }
      for (i=0; i<16;i++)
      {
         xuat_32led_don_2word(0,y);
         delay_ms(300);
         y = (y<<1);
      }
   }
}
