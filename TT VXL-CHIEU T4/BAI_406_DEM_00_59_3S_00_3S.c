#include <tv_pickit2_shift_1.c>
signed int8 i;

void main()
{
   set_up_port_ic_chot();
   while (true)
   {
      i = 0;
      do
      {   
         xuat_4led_7doan_2so(ma7doan[i/10], ma7doan[i%10]);
         delay_ms(200);
         i++;
      }
      while (i<60);
      delay_ms(2800);
      do
      {   
         i--;
         xuat_4led_7doan_2so(ma7doan[i/10], ma7doan[i%10]);
         delay_ms(200);

      }
      while (i>0);
      delay_ms(2800);  
   }
}
