//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
unsigned int32 y;
unsigned int8 i;

void main()
{
   set_up_port_ic_chot();
   y=0;
   while (true)
   {
      for (i=0;i<16;i++)
      {
         xuat_32led_don_4byte(y>>24,y>>16,y>>8,y);
         delay_ms(300);
      }
      for (i=0; i<16;i++)
      {
         xuat_32led_don_4byte(y>>24,y>>16,y>>8,y);
         delay_ms(300);
      }
   }
}
