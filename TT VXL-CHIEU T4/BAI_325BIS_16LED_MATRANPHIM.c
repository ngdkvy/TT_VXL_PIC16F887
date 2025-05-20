//0: UP
//1: DW
//2: CLR
#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_key4x4_138.c>
unsigned int16 y, mp;
int1 TT_CT = 0;

void phim_up()
{
   if (TT_CT == 0)
      y = (y << 1) |0x01;
   else
      y = (y >> 1) |0x8000;
   xuat_32led_don_2word(0,y);
   delay_ms(20);
}
void phim_dw()
{
   if (TT_CT == 0)
      y = (y >> 1);
   else 
      y = (y << 1);
   xuat_32led_don_2word(0,y);
   delay_ms(20);
}
void phim_clr()
{
   TT_CT = ~TT_CT;
   y = 0;
   xuat_32led_don_2word(0,y);
   delay_ms(20);
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
      mp = key_4x4_dw();
      if (mp!=0xff)
      {
         if (mp == 0)
            phim_up();
         if (mp == 4)
            phim_dw();
         if (mp == 8)
            phim_clr();   
      }
   }
}
      
