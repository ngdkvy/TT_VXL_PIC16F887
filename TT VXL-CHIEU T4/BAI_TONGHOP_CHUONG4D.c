//!TT_SP = 0 => Pause
//!TT_SP = 1 => Start

//!TT_HT = 0 => Counter ben trai, SP ben phai
//!TT_HT = 1 => Nguoc lai

//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
unsigned int8    t0;
unsigned int8    donvi, chuc;
int1 TT_SP, TT_HT;

void phim_SP()
{
   if (!input(BT0))
   {
      delay_ms(20);
      if (!input(BT0))
      {
         TT_SP= ~ TT_SP;
         while (!input(BT0));
      }
   }
} 
void phim_HT()
{
   if (!input(BT2))
   {
      delay_ms(20);
      if (!input(BT2))
      {
         TT_HT= ~ TT_HT;
         while (!input(BT2));
      }
   }
} 
void  giai_ma_hien_thi (unsigned int16 tam)
{
   donvi = ma7doan[tam %10];
   chuc  = ma7doan[tam/10%10]; 
   if (chuc==0xc0)   chuc=0xff;
   if (!TT_HT)
      xuat_4led_7doan_4so(chuc,donvi &0x7f, 0x92, 0x8c);
   else 
      xuat_4led_7doan_4so(0x92, 0x0c, chuc,donvi);
}
void main()
{
   set_up_port_ic_chot();
   setup_timer_0 (t0_ext_l_to_h | t0_div_1| t0_8_bit); 
   set_timer0(99);
   TT_SP = TT_HT = 0;
   while(true)
   {
      t0=get_timer0();
      
      //Kiem tra phim nhan
      phim_SP();
      phim_HT();
      
      //Xu ly Start/Pause
      if (!TT_SP) 
         setup_timer_0(t0_off);
      else
         setup_timer_0 (t0_ext_l_to_h | t0_div_1| t0_8_bit); 
         
      giai_ma_hien_thi (t0);
      if (t0>99)   set_timer0(1);
   }
}
