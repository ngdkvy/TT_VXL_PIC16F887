//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
unsigned int16 y;
unsigned int8 i;

void main()
{
   set_up_port_ic_chot();
   while (true)
   {
      y=0;
      for (i=0;i<17;i++)
      {
         xuat_32led_don_2word(y,y);
         delay_ms(300);
         y= (y>>1)|0X8000;
      }
      y=0;
      for (i=0; i<17;i++)
      {
         xuat_32led_don_2word(y,y);
         delay_ms(300);
         y = (y<<1)+1;
      }
   }
}
