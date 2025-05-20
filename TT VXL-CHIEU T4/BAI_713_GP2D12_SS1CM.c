#include <tv_pickit2_shift_1.c> 
#include <math.h>

unsigned int8     j, solan=20; 
unsigned int16  kqadc;
unsigned int8     dv, ch;
float  k_cach;

void  giai_ma_hien_thi (unsigned int16 tam)
{
   dv = ma7doan[tam%10];
   ch  = ma7doan[tam/10]; 
   xuat_4led_7doan_2so(ch, dv);
}
void doc_adc() 
{
   set_adc_channel(2); 
   kqadc = 0;
   delay_ms(1);
   for (j=0; j<solan; j++) 
   {
      kqadc = kqadc + read_adc(); 
      delay_ms(10);
   }
   kqadc = kqadc / solan;
}
void main() 
{
   set_up_port_ic_chot();
   setup_adc(adc_clock_div_32); 
   setup_adc_ports(an0_to_an2|vss_vdd ); 
   set_adc_channel(2);
   
   while(true)
   {
      doc_adc();
      kqadc=read_adc();
      delay_ms(40);
      k_cach=pow(4277/kqadc,1.106); 
      
      if (k_cach>80)  k_cach=80;
      giai_ma_hien_thi(k_cach);
   } 
}
