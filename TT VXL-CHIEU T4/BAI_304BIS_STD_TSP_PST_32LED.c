#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
unsigned int8 i, y;

void sang_pst()
{
   y=0;
   xuat_32led_don_4byte(0, 0, 0, y);
   delay_ms(30);
   for (i = 0 ; i < 8 ; i++)
   {
      y = y>>1 |0x80;
      xuat_32led_don_4byte(0, 0, 0, y);
      delay_ms(200);
   }
}
void sang_tsp()
{
   y=0;
   xuat_32led_don_4byte(0, 0, 0, y);
   delay_ms(200);
   for (i = 0 ; i < 8 ; i++)
   {
      y = y<<1 | 0x01;
      xuat_32led_don_4byte(0, 0, 0, y);
      delay_ms(200);
   }
}
void main()
{
   set_up_port_ic_chot();
   while (true)
   {
       sang_pst();
       sang_tsp();
   }
}

