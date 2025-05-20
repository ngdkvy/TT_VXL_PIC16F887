#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
unsigned int8 k, TT_CT;
unsigned int32 y;

void main()
{
   set_up_port_ic_chot();
   TT_CT = 1;
   y = 0;
   xuat_32led_don_1dw(y);
   delay_ms(100);
   while (true)
   {
      if (TT_CT == 1)
      {
         if (k<32)
         {
            y = (y<<1) + 1;
            xuat_32led_don_1dw(y);
            delay_ms(100);
            k++;
         }
         else 
         {
            k = 0;
            y = 0XFFFFFFFF;
            xuat_32led_don_1dw(y);
            delay_ms(100);
            TT_CT++;
         }
      }
      if (TT_CT == 2)
      {
         if (k<32)
         {
            y = y<<1;
            xuat_32led_don_1dw(y);
            delay_ms(100);
            k++;
         }
         else 
         {
            k = 0;
            y = 0;
            xuat_32led_don_1dw(y);
            delay_ms(100);
            TT_CT=1;
         }
      }
   }
}
   
         
   
