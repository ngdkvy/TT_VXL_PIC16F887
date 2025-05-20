//!TT_SP = 0 => Pause
//!TT_SP = 1 => Start

//!TT_HT = 0 => Counter ben trai, SP ben phai
//!TT_HT = 1 => Nguoc lai

//!TT_DC = 0 => Dem len
//!TT_DC = 1 => Dem xuong

//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
unsigned int8    t0;
unsigned int8    donvi, chuc;
int1 TT_SP, TT_HT, TT_DC;

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
void phim_DC()
{
   if (!input(BT1))
   {
      delay_ms(20);
      if (!input(BT1))
      {
         TT_DC = ~ TT_DC;
         while (!input(BT1));
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
         TT_HT = ~ TT_HT;
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
   set_timer0(0);
   TT_SP = TT_HT = TT_DC = 0;
   while(true)
   {
      t0=get_timer0();
      
      //Kiem tra phim nhan
      phim_SP();
      phim_HT();
      phim_DC();
      
      //Xu ly Start/Pause
      if (!TT_SP) 
         setup_timer_0(t0_off);
      else
         setup_timer_0 (t0_ext_l_to_h | t0_div_1| t0_8_bit); 
       
      //Xu ly dao chieu dem len, dem xuong
      if (!TT_DC)
         t0 = get_timer0();
      else 
         t0 = 4 - get_timer0();
      if ((t0 > 4) && (!TT_DC))
         t0 = set_timer0(1);
      if ((!t0) && (TT_DC))
         set_timer0(0);   
      giai_ma_hien_thi (t0);
   }
}
