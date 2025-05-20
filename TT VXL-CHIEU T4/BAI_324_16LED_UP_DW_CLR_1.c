#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
unsigned int32 y;

void phim_up()
{
   if (!input(BT0))
   {
      delay_ms(20);
      {
         if (!input(BT0))
         {
            y = (y<<1) |0x01;
            xuat_32led_don_2word(0,y);
            delay_ms(100);
            while (!input(BT0));
         }
      }
   }
}
void phim_dw()
{
   if (!input(BT2))
   {
      delay_ms(20);
      {
         if (!input(BT2))
         {
            y = (y>>1);
            xuat_32led_don_2word(0,y);
            delay_ms(100);
            while (!input(BT2));
         }
      }
   }
}
void phim_clr()
{
   if (!input(BT3))
   {
      y = 0;
      xuat_32led_don_2word(0,y);
      delay_ms(20);
   }
}
void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   y = 0;
   xuat_32led_don_2word(0,y);
   delay_ms(100);
   while (true)
   {
      phim_up();
      phim_dw();
      phim_clr();
   }
}
      
