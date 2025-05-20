#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_key4x4_138.c>

unsigned int8 dem_led, tt_ct;
signed int8 mp;
unsigned int32 y;
unsigned int16 yt, yp;

void reset_bien()
{
   y = 0; yt = 0; yp = 0;
   dem_led = 0;
}
void CHOPTAT()
{
   y = 0xFFFFFFFF;
   xuat_32led_don_1dw(y);
   delay_ms(30);
   y = 0;
   xuat_32led_don_1dw(y);
   delay_ms(30);
}
void ST_32_PST()
{
   if (dem_led < 32)
   {
      y = (y <<1) | 0x01;
      xuat_32led_don_1dw(y);
      delay_ms(30);
      dem_led++;
   }
   else if (dem_led < 64)
   {
      y = y << 1;
      xuat_32led_don_1dw(y);
      delay_ms(30);
      dem_led++;
   }
   else reset_bien();
}
void ST_32_TSP()
{
   if (dem_led < 32)
   {
      y = (y >> 1) | 0x80000000;
      xuat_32led_don_1dw(y);
      delay_ms(30);
      dem_led++;
   }
   else if (dem_led < 64)
   {
      y = y >> 1;
      xuat_32led_don_1dw(y);
      delay_ms(30);
      dem_led++;
   }
   else reset_bien();
}
void ST_NV()
{
   if (dem_led < 16)
   {
      yt = (yt >> 1) | 0x8000;
      yp = (yp << 1) | 0x01;
      xuat_32led_don_2word(yt, yp);
      delay_ms(30);
      dem_led++;
   }
   else if (dem_led < 32)
   {
      yt = (yt >> 1);
      yp = (yp << 1);
      xuat_32led_don_2word(yt, yp);
      delay_ms(30);
      dem_led++;
   }
   else reset_bien();
}
void ST_TR()
{
   if (dem_led < 16)
   {
      yt = (yt >> 1) | 0x8000;
      yp = (yp << 1) | 0x01;
      xuat_32led_don_2word(yp, yt);
      delay_ms(30);
      dem_led++;
   }
   else if (dem_led < 32)
   {
      yt = (yt >> 1);
      yp = (yp << 1);
      xuat_32led_don_2word(yp, yt);
      delay_ms(30);
      dem_led++;
   }
   else reset_bien();
}
void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   y = 0;
   xuat_32led_don_1dw(y);
   delay_ms(30);
   tt_ct = 0;
   dem_led = 0;
   while (true)
   {
      mp = key_4x4_dw();
      if (mp!=0xff)
      {
         if (mp == 0) tt_ct = 0;
         if (mp == 1) tt_ct = 1;
         if (mp == 2) tt_ct = 2;
         if (mp == 3) tt_ct = 3;
         if (mp == 4) tt_ct = 4;
      }
       if (tt_ct == 0) CHOPTAT();
       if (tt_ct == 1) ST_32_PST();
       if (tt_ct == 2) ST_32_TSP();
       if (tt_ct == 3) ST_NV();
       if (tt_ct == 4) ST_TR();
   }
}

   
