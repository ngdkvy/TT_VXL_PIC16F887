#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
unsigned int32 y, save, run;
unsigned int8 i, j;

void sangdon()
{
   y = 0;
   xuat_32led_don_1dw(y);
   delay_ms(100);
   save = 0;
   for (i = 0 ; i < 32 ; i++)
   {
      run = 0x80000000;
      for (j = i ; j < 32 ; j++)
      {
         y = run|save;
         xuat_32led_don_1dw(y);
         delay_ms(100);
         run = run>>1;
      }
      save = y;
   }
}
void main()
{
   set_up_port_ic_chot();
   y = 0;
   xuat_32led_don_1dw(y);
   delay_ms(100);
   while (true)
   {
      sangdon();
   }
}
         
