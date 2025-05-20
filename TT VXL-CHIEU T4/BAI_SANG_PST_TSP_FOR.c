#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
unsigned int32 y;
unsigned int8 k;

void main()
{
   set_up_port_ic_chot();
   y = 0;
   k = 0;
   xuat_32led_don_1dw(y);
   delay_ms(100);
   while (true)
   {
      y = 0 ;
      xuat_32led_don_1dw(y);
      delay_ms(100);
      for (k = 0 ; k < 32 ; k++)
      {
         y = (y<<1) | 0x01;
         xuat_32led_don_1dw(y);
         delay_ms(100);
      }
//!      if (k < 33)
//!      {
//!         y = (y>>1) | 0x80000000;
//!         xuat_32led_don_1dw(y);
//!         delay_ms(100);   
//!         k++;
//!      }
//!      else 
//!      {  
//!         k = 0;
//!         y = 0;
//!      }
   }
}
      
