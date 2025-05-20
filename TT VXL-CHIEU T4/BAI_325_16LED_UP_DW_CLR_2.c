#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
unsigned int16 y;
int1 TT_CT = 0;

void phim_up()
{
   if (!input(BT0))
   {
      delay_ms(20);
      {
         if (!input(BT0))
         {
            if (TT_CT == 0)
               y = (y << 1) |0x01;
            else
               y = (y >> 1) |0x8000;
            xuat_32led_don_2word(0,y);
            delay_ms(20);
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
            if (TT_CT == 0)
               y = (y >> 1);
            else 
               y = (y << 1);
            xuat_32led_don_2word(0,y);
            delay_ms(20);
            while (!input(BT2));
         }
      }
   }
}
void phim_clr()
{
   if (!input(BT3))
   {
      delay_ms(20);
      if (!input(BT3))
      {
         TT_CT = ~TT_CT;
         y = 0;
         xuat_32led_don_2word(0,y);
         delay_ms(20);
         while (!input(BT3));
      }
      
   }
}
void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   y = 0;
   xuat_32led_don_2word(0,y);
   delay_ms(20);
   while (true)
   {
      phim_up();
      phim_dw();
      phim_clr();
   }
}
      
