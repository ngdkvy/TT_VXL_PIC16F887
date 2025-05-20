//counter dem xuong, len
//dat lai gia tri cho counter
//0: dem len
//1: dem xuong
//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
unsigned int8    t0;
unsigned int8    donvi, chuc, tram;
int1 TT_UD;
void  giai_ma_hien_thi (unsigned int16 tam)
{
   donvi = ma7doan[tam %10];
   chuc  = ma7doan[tam/10%10]; 
   tram  = ma7doan[tam/100];
   if (tram==0xc0)
   {
      tram=0xff;
      if (chuc==0xc0)   chuc=0xff;
   }
   xuat_4led_7doan_3so(tram,chuc,donvi);
}
void phim_UP_DW()
{
   if (!input(BT0))
   {
      delay_ms(20);
      if (!input(BT0))
      {
         if (!TT_UD)
            set_timer0(10- t0);
         else 
            set_timer0(t0);
         TT_UD = ~ TT_UD;
         while (!input(BT0));
      }
   }
}
void main()
{
   set_up_port_ic_chot();
   setup_timer_0 (t0_ext_l_to_h | t0_div_1| t0_8_bit); 
   set_timer0(0);
   t0 = 0;
   TT_UD = 0;
   while(true)
   {
      if (TT_UD == 0)
         t0 = get_timer0();  
      else 
      {
         t0 = 10 - get_timer0();
      }
      if ((t0 > 10) && (!TT_UD))
         t0 = set_timer0(1);
      if ((!t0) && (TT_UD))
         set_timer0(0);
      phim_UP_DW();
//!      t0 = get_timer0(); 
      giai_ma_hien_thi (t0);
      delay_ms(10);
   }
}
