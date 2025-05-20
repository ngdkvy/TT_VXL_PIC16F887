//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
unsigned int32 y;
unsigned int8 i;
void sangdan()
{
   y=0;
   xuat_32led_don_1dw(y);
   delay_ms(300);
   for (i = 0 ; i<3; i++)
   {
      y = ((y>>5) | 0x3E0000) & 0x3FFC00;
      xuat_32led_don_1dw(y);
      delay_ms(300);
   }
   y=0;
   xuat_32led_don_1dw(y);
   delay_ms(300);
   for (i = 0 ; i<3; i++)
   {
      y = ((y<<5) | 0x7C00) & 0x3FFC00;
      xuat_32led_don_1dw(y);
      delay_ms(300);
   }
}
void tatdan()
{
   y=0xFFFFFFFF;
   xuat_32led_don_1dw(y);
   delay_ms(300);
   for (i = 0 ; i<3; i++)
   {
      y = ((y>>5) & 0xFFC1FFFF) | 0xFFC003FF;
      xuat_32led_don_1dw(y);
      delay_ms(300);
   }
   y=0xFFFFFFFF;
   xuat_32led_don_1dw(y);
   delay_ms(300);
    for (i = 0 ; i<3; i++)
   {
      y = ((y<<5) & 0xFFFF83FF) | 0xFFC003FF;
      xuat_32led_don_1dw(y);
      delay_ms(300);
   }
}
void choptat()
{
   for (i = 0; i<2; i++)
   {
      xuat_32led_don_1dw(y);
      delay_ms(300);
      xuat_32led_don_1dw(0x003FFC00);
      delay_ms(300);
   }
}
void main()
{
   set_up_port_ic_chot();
   while (true)
   {
      sangdan();
      choptat();
      tatdan();
      choptat();
   }
}

      

   


