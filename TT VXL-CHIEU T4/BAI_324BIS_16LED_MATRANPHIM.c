//0: UP
//4: DW
//8: CLR
#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_key4x4_138.c>
unsigned int32 y, mp;

void phim_up()
{
      y = (y<<1) |0x01;
      xuat_32led_don_2word(0,y);
      delay_ms(100);
}
void phim_dw()
{
      y = (y>>1);
      xuat_32led_don_2word(0,y);
      delay_ms(100);
}
void phim_clr()
{
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
   delay_ms(100);
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
      
