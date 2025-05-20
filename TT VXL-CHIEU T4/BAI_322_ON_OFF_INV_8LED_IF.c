#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
unsigned int8 y;
void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   y = 0;
   xuat_32led_don_4byte(0,0,0,0);
   while (true)
   {
      if (!input(on))
      {
         y = 0x0f;
         xuat_32led_don_4byte(0,0,0,y);
      }
      if (!input(off))
      {
         y = 0;
         xuat_32led_don_4byte(0,0,0,0);
      }
      if (y!=0)
      {
         if (!input(inv))
         {
            y = ~y;
            xuat_32led_don_4byte(0,0,0,y);
         }
      }
   }
}
