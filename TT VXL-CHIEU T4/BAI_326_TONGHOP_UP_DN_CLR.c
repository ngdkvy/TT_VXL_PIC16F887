//UP BT0
//DW BT2
//CLR BT3
#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
unsigned int8 tt_ct, dem_led;
unsigned int32 y;
unsigned int16 yt, yp;

void reset_bien()
{
   y = 0; yt = 0; yp = 0;
   if (tt_ct != 1) dem_led = 0;
}
void PHIM_UP()
{
   if (!input(BT1) && (tt_ct < 5))
   {
      delay_ms(10);
      if (!input(BT1))
      {
         tt_ct++;
         while (!input(BT1));
      }
   }
}
void PHIM_DW()
{
   if (!input(BT2) && (tt_ct > 1))
   {
      delay_ms(10);
      if (!input(BT2))
      {
         tt_ct--;
         while (!input(BT2));
      }
   }
}
void PHIM_CLR()
{
   if (!input(BT3) && (tt_ct > 1))
   {
      tt_ct = 1;
      reset_bien();
   }
}
void CHOPTAT()
{
   y = 0xFFFFFFFF;
   xuat_32led_don_1dw(y);
   delay_ms(30);
   y = 0;
   xuat_32led_don_1dw(y);
   delay_ms(100);
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
   tt_ct = 1;
   dem_led = 0;
   while (true)
   {
      if (tt_ct == 1) CHOPTAT();
      if (tt_ct == 2) ST_32_PST();
      if (tt_ct == 3) ST_32_TSP();
      if (tt_ct == 4) ST_NV();
      if (tt_ct == 5) ST_TR();
      PHIM_UP();
      PHIM_DW();
      PHIM_CLR();
   }
}

   
