#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_key4x4_138.c>
unsigned int8 mp, y;
void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   y = 0;
   while (true)
   {
      mp = key_4x4_dw();
      if (mp!=0xff)
      {
         if (mp==0) y = y | 0x01;
         if (mp==1) y = y | 0x02;
         if (mp==2) y = y | 0x04;
         if (mp==3) y = y | 0x08;
         if (mp==4) y = y | 0x10;
         if (mp==5) y = y | 0x20;
         if (mp==6) y = y | 0x40;
         if (mp==7) y = y | 0x80;
         if (mp == 8) y = y & 0xFE; //1111 1110 <<0
         if (mp == 9) y = y & 0xFD; //1111 1101 <<1 + 0x01
         if (mp == 10) y = y & 0xFB; //1111 1011 <<2 + 0x03
         if (mp == 11) y = y & 0xF7; //1111 0111 <<3 + 0x07
         if (mp == 12) y = y & 0xEF;//1110 1111 <<4 +0x15
         if (mp == 13) y = y & 0xDF;// 1101 1111 <<5 + 0x1F
         if (mp == 14) y = y & 0xBF;// 1011 1111 <<6 + 0x3F
         if (mp == 15) y = y & 0x7F;// 0111 1111 <<7 +0x7F
         
      }
      xuat_32led_don_4byte(0,0,y,0);
   }
}

      
