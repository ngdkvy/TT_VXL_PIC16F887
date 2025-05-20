//ON: BT0
//OFF: BT1
//INV: BT2
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
      while (input(on));
      y = 0x0f;
      xuat_32led_don_4byte(0,0,0,y);
      do
      {
         if (!input(inv))
         {
            y = ~y;
            xuat_32led_don_4byte(0,0,0,y);
         }
      }
      while (input(off));
      xuat_32led_don_4byte(0,0,0,0);
   }
}

