#include <tv_pickit2_shift_1.c>
unsigned int8 min, sec;

void main()
{
   set_up_port_ic_chot();
   while (true)
   {
      for (min = 0; min < 60; min ++)
         for (sec = 0; sec < 60 ; sec ++)
         {  
            xuat_4led_7doan_4so(ma7doan[min/10], ma7doan[min%10], ma7doan[sec/10], ma7doan[sec%10]);
            delay_ms(200);
         }
   }
}
   
