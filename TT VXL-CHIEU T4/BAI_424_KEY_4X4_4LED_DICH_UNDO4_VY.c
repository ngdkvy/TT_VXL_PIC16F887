#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_key4x4_138.c>

unsigned char led7 [8] = {0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F};
signed int8 mp;
unsigned int8 k;

void dich_led7()
{
   for (k = 7; k > 0; k--)
      led7 [k] = led7 [k-1];
   led7 [0] = ma7doan [mp];
}

void dich_led7_nguoc()
{
   for (k = 0; k < 7; k++)
      led7 [k] = led7 [k+1];
   led7 [7] = 0x7F;
}

void main()
{
   set_up_port_ic_chot();
   
    //Thiet lap chan port B
   set_tris_b(0x3c);
   
   //Khoi tao trang thai ban dau: 4 dau cham
   xuat_4led_7doan_4so(led7 [3], led7 [2], led7 [1], led7 [0]);
   
   while (true)
   {
      mp = key_4x4_dw();
      if (mp != 0xff)
      {
         if (mp < 10)// 0 -> 9
            dich_led7();
            
         if (mp == 11) //Button: B (4 level undo)
            dich_led7_nguoc();
            
         if (mp == 12) //Button: C (clear)
            for (k = 0; k < 8; k++)
               led7 [k] = 0x7F;
         
         //xuat trang thai led
         xuat_4led_7doan_4so(led7 [3], led7 [2], led7 [1], led7 [0]);
      }
   }
}
