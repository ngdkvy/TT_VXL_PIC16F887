#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_key4x4_138.c>
signed int8 mp;
unsigned int8 y;

void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   while (true)
   {
      mp = key_4x4_dw();
      if (mp != 0xff)
      {
         delay_ms(200);
         if (mp == 0) 
            y = 0xff;
         if (mp == 7)
            y = 0;
         xuat_32led_don_4byte (0, 0, 0, y);
      }
   }
}

