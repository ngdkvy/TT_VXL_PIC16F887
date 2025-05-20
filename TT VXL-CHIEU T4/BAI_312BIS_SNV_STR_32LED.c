#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
unsigned int16 zp, zt;
int1 TT_CT = 0;
unsigned int16 dem_led = 0;

void SNV()
{
   if (dem_led < 16)
   {
      zp = (zp << 1) | 0x01;
      zt = (zt >> 1) | 0x8000;
      xuat_32led_don_2word (zt, zp);
      delay_ms (100);
      dem_led ++;
   }
   else if (dem_led == 16)
   {
      dem_led = 0;
      TT_CT = ~TT_CT;
      zp = zt = 0;
      xuat_32led_don_2word (zt, zp);
      delay_ms (100);
   }   
}
void STR()
{
   if (dem_led < 16)
   {
      zp = (zp << 1) | 0x01;
      zt = (zt >> 1) | 0x8000;
      xuat_32led_don_2word (zp, zt);
      delay_ms (100);
      dem_led ++;
   }
   else if (dem_led == 16)
   {
      dem_led = 0;
      TT_CT = ~TT_CT;
      zp = zt = 0;
      xuat_32led_don_2word (zt, zp);
      delay_ms (100);
   }  
}
void main ()
{
   set_up_port_ic_chot();
   zp = zt = 0;
   xuat_32led_don_2word(zt, zp);
   delay_ms (100);
   TT_CT = 0;
   while (true)
   {
      if (TT_CT == 0)
         SNV();
      else 
         STR();
   }
}
