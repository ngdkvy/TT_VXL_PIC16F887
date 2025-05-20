#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
unsigned int32 y, run, save;
unsigned int8 i, j;

void tatdon()
{
   y = 0xFFFFFFFF;
   xuat_32led_don_1dw(y);
   delay_ms(100);
   save = 0xFFFFFFFF;
   for (i = 0 ; i < 32 ; i++)
   {
      run = 0x80000000>>i;
      for (j = 0 ; j < i+1 ; j++)
      {
         run = run << 1;
         y = run|save;
         xuat_32led_don_1dw(y);
         delay_ms(100);  
      }
      save = save >> 1;
   }
}
void main()
{
   set_up_port_ic_chot();
   y = 0xffffffff;
   xuat_32led_don_1dw(y);
   delay_ms(100);
   while (true)
   {
      tatdon();
   }
}
         
