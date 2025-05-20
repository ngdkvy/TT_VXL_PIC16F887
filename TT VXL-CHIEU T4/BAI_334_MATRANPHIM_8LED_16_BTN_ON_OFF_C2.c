#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_key4x4_138.c>
unsigned int8 mp, y;
void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   y = 0;
   while (true)
   {
      mp = key_4x4_dw();
      if (mp!=0xff)
      {
         if (mp < 8)
            y = y | (0x01 << mp);
         else 
         {  
            y = y & ~(0x01 << (mp-8));        
         }
      }
      xuat_32led_don_4byte(0, 0, y, 0);
   }
}

      
