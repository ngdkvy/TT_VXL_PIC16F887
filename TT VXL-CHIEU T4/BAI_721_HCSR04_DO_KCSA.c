#include <tv_pickit2_shift_1.c>
#define  trigger      pin_e2 
#define  echo         pin_e1
float    kcs;

void  giai_ma_hienthi_4led (float tam) 
{
   unsigned int16  x;
   x =(unsigned int16 ) tam; 
   xuat_4led_7doan_giaima_xoa_so0(x);
}

void  tao_xung_trigger()
{
   delay_ms(10);
   output_high(trigger); 
   delay_ms(10); 
   output_low(trigger);
   
   set_timer1(0); 
   while(!(input(echo)));
   setup_timer_1(t1_internal|t1_div_by_4); 
   
   while(input(echo));
   kcs =get_timer1(); 
   setup_timer_1(t1_disabled );
}

void main() 
{
   set_up_port_ic_chot(); 
   setup_timer_1(t1_disabled ); 
   giai_ma_hienthi_4led(kcs); 
   while(true)
   {
      tao_xung_trigger();
      kcs=kcs*0.8;
      kcs = (kcs/58);
      giai_ma_hienthi_4led(kcs);
      delay_ms(500);
   }
}
