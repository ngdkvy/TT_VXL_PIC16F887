#include <tv_pickit2_shift_1.c> 
#include <tv_pickit2_shift_key4x4_138.c>
//!
signed int8 mp,k;


unsigned int8 y;

void main()
{ 
   set_up_port_ic_chot();
   set_tris_b(0x3c); 
   while(true)
   { 
      y=0;
      do {mp = key_4x4_dw();}
      if (mp<8)
      {
         k=mp;
         y= y | (0x01<<mp);
         xuat_32led_don_4byte(0,0,0,y);
         delay_ms(30);
      }
      else
      {  
         y=0xFF;
         k=mp-8;
         y= y | (0x01<<mp) ;
         xuat_32led_don_4byte(0,0,0,y);
         delay_ms(30);
      }
   }
}
