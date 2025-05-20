//!#include <tv_pickit2_shift_1.c> 
#include <tv_pickit2_shift_1_proteus.c> 

void  main()
{
   set_up_port_ic_chot(); 
   xuat_4led_7doan_4so(0xc6, 0x89, 0x88, 0xc0); 
   while(true);
}
