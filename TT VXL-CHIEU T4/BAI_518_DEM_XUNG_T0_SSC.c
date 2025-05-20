//!TT_SS = 0 => Stop
//!TT_SS = 1 => Start

#include <tv_pickit2_shift_1.c>
unsigned int8 t0, chuc, donvi;
int1 TT_SS;

void  giai_ma_hien_thi (unsigned int8 tam)
{
   donvi = ma7doan[tam %10];
   chuc  = ma7doan[tam/10%10]; 
   if (chuc==0xc0)   chuc=0xff;
   //!hien thi 4 led 7 doan
   xuat_4led_7doan_2so(chuc, donvi);
   
   //!hien thi tren 8 led quet
   //!led quet thu 0 (phai qua) hien thi hang don vi
   xuat_8led_7doan_quet_2(0, donvi);
   delay_us(100); 
   
   //!led quet thu 1 (phai qua) hien thi hang chuc
   xuat_8led_7doan_quet_2(1, chuc);
   delay_us(100);
   
   //!chong lem
   xuat_8led_7doan_quet_tat_led(); 

}

//!nut 2 trang thai => chong doi
void phim_START_STOP()
{
   if (!input(BT0))
   {
      delay_ms(20);
      if (!input(BT0))
      {
         TT_SS= ~ TT_SS;
         while (!input(BT0));
      }
   }
}

//!nut 1 trang thai => check button
void phim_CLEAR()
{
   if (!input(BT1))
   {
      set_timer0(0);
      t0 = 0;
   }
} 

void main()
{
   set_up_port_ic_chot();
   
   //Thiet lap chan port B
   set_tris_b(0x3c);
   
   //Thiet lap counter: counter khong dem
   setup_timer_0(t0_off);
   set_timer0(0);
   
   //Khoi tao bien, trang thai led
   TT_SS = 0;
   t0 = 0;
   giai_ma_hien_thi (t0);
   
   while (true)
   {  
      t0 = get_timer0();
      
      //!check button
      phim_START_STOP();
      phim_CLEAR();
      
      //!button Start/Stop
      if (TT_SS == 0) 
         setup_timer_0(t0_off);
      else
         setup_timer_0 (t0_ext_l_to_h | t0_div_1| t0_8_bit);
         
      giai_ma_hien_thi (t0);

      //!reset counter value
      if (t0>99)   set_timer0(1);
   }
}
