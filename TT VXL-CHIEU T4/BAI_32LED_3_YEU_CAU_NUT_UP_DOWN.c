//dieu khien 32 led
// YC0: 32 led tat
// YC1: 32 led sang tat dan phai sang trai
// YC2: 32 led sang tat dan trai sang phai
// 0 -> 1 -> 2 -> 0
// BT0: UP
// BT1: DOWN

#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>

signed int8 tt_ct;
unsigned int32 x, i;

void yc1_32led_std_pst ()
{
   x = 0;
   for (i = 0; i < 32 ; i++)
   {
      x = (x << 1) + 1;
      xuat_32led_don_1dw (x);
      delay_ms(100);
   }
   for (i = 0; i < 32; i++)
   {
      x = (x<<1);
      xuat_32led_don_1dw (x);
      delay_ms(100);
   }
}
void yc2_32led_std_tsp ()
{
   x = 0;
   for (i = 0; i < 32 ; i++)
   {
      x = (x >> 1) + 0x80000000;
      xuat_32led_don_1dw (x);
      delay_ms(100);
   }
   for (i = 0; i < 32; i++)
   {
      x = (x>>1);
      xuat_32led_don_1dw(x);
      delay_ms(100);
   }
}
void phim_bt0_c1 () //UP
{
   if (!input(bt0))
   {
      delay_ms(20);
      if (!input(bt0))
      {
         if (tt_ct<2)
            tt_ct++;
         while (!input (bt0));
      }
   }
}
void phim_bt1_c1 () //DOWN
{
   if (!input(bt1))
   {
      delay_ms(20);
      if (!input(bt1))
      {
         if (tt_ct>0) 
            tt_ct--;
         while (!input (bt0));
      }
   }
}
void main()
{
   set_up_port_ic_chot();
   tt_ct = 0; 
   x = 0;
   while (true)
   {
      phim_bt0_c1 ();
      phim_bt1_c1 ();
      if (tt_ct == 0)
         xuat_32led_don_1dw(0);
      else if (tt_ct == 1) 
         yc1_32led_std_pst();
      else 
         yc2_32led_std_tsp();
   }
}
