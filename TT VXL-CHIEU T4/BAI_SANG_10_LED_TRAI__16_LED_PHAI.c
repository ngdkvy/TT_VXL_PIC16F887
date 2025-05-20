#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
unsigned int16 yt, yp, slt, slp;

void main()
{
   set_up_port_ic_chot();
   yt = 0; yp = 0;
   slt = 0; slp = 0;
   xuat_32led_don_4byte (yt>>8, yt, yp>>8 , yp);
   delay_ms(100);
   while (true)
   {
      if (slt < 10)
      {
         yt = (yt << 1) | 0x0001;
         slt++;
      }
      else 
      {
         yt = 0;
         slt = 0;
      }
      if (slp < 16)
      {
         yp = (yp >> 1) | 0x8000;
         slp++;
      }
      else 
      {
         yp = 0;
         slp = 0;
      }
      xuat_32led_don_4byte (yt>>8, yt, yp>>8 , yp);
      delay_ms(100);
   }
}
