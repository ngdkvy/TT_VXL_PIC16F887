#include <tv_pickit2_shift_1.c>
unsigned int8 min, sec;

void main()
{
   set_up_port_ic_chot();
   sec = 0;
   while (true)
   {
      xuat_4led_7doan_4so(ma7doan[min/10], ma7doan[min%10], ma7doan[sec/10], ma7doan[sec%10]);
      delay_ms(200);
      sec ++;
      if (sec == 60)
      {
         min ++;
         sec = 0;
      }
      if (min == 60) min = 0;
   }
}
   
