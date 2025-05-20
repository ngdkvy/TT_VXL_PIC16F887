#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
unsigned int8 dem_led;
unsigned int32 y;
void delay_tuy_y (unsigned int8 d12)
{
   unsigned int8 dl;
   for (dl = 0; dl<d12; dl++)
      delay_ms(10);
}
void sang_tat_dan_pst_32led (unsigned int8 dl)
{
   if (dem_led<32)
   {
      xuat_32led_don_1dw(y);
      y = (y<<1)+1;
      delay_tuy_y(dl);
   }
   else if (dem_led<64)
   {
      xuat_32led_don_1dw(y);
      y = (y<<1);
      delay_tuy_y(dl);
   }
   else
   {
      dem_led=0;
      y = 0;
   }
   dem_led++;
}
void main()
{
   set_up_port_ic_chot();
   y = 0;
   while (true)
   {
      sang_tat_dan_pst_32led(2);
   }
}
