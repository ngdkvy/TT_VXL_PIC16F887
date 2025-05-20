#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
unsigned int32 y;

void choptat()
{
   y = 0;
   xuat_32led_don_1dw(y);
   delay_ms(200);
   y = 0x001FF80;
   xuat_32led_don_1dw(y);
   delay_ms(200);
}
void main()
{
   set_up_port_ic_chot();
   while (true)
   {
      choptat();
   }
}
   
