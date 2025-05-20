#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_key4x4_138.c>

unsigned char led7 [4] = {0x7F, 0x7F, 0x7F, 0x7F};
signed int8 mp;

void dich_led7()
{
   led7 [3] = led7 [2];
   led7 [2] = led7 [1];
   led7 [1] = led7 [0];
   led7 [0] = ma7doan [mp];
}
void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   xuat_4led_7doan_4so(led7 [3], led7 [2], led7 [1], led7 [0]);
   while (true)
   {
      mp = key_4x4_dw();
      if (mp != 0xff)
      {
         dich_led7();
         xuat_4led_7doan_4so(led7 [3], led7 [2], led7 [1], led7 [0]);
      }
   }
}
