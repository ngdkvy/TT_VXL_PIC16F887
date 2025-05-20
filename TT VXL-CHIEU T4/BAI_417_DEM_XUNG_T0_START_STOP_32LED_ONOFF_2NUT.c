#include <tv_pickit2_shift_1.c>
unsigned int8 t0, tram, chuc, donvi, t0_tam;

void  giai_ma_hien_thi (unsigned int8 tam)
{
   donvi = ma7doan[tam %10];
   chuc  = ma7doan[tam/10%10]; 
   tram  = ma7doan[tam/100];
   if (tram==0xc0)
   {
      tram=0xff;
      if (chuc==0xc0)   chuc=0xff;
   }
   xuat_4led_7doan_3so(tram, chuc, donvi);
}
void phim_ON()
{
   if (!input(BT0))
   {
      delay_ms(20);
      if (!input(BT0))
      {
         setup_timer_0 (t0_ext_l_to_h | t0_div_1|t0_8_bit); 
         xuat_32led_don_4byte(0xff, 0xff, 0xff, 0xff);
         while (!input(BT0));
      }
   }
} 
void phim_OFF()
{
   if (!input(BT1))
   {
      delay_ms(20);
      if (!input(BT1))
      {
         setup_timer_0(t0_off);
         xuat_32led_don_4byte(0,0,0,0);
         while (!input(BT1));
      }
   }
} 
void main()
{
   set_up_port_ic_chot();
   
   //Thiet lap chan port B
   set_tris_b(0x3c);
   
   //Thiet lap counter
   setup_timer_0(t0_off);
   set_timer0(0);
   
   //Khoi tao bien, trang thai led
   t0_tam = t0 = 0;
   xuat_32led_don_4byte(0,0,0,0); 
   giai_ma_hien_thi (t0);
   
   while (true)
   {  
      t0 = get_timer0();
      phim_ON();
      phim_OFF();
      if (t0 != t0_tam)
      {
         t0_tam = t0;
         giai_ma_hien_thi (t0);
         if (t0>=101)   set_timer0(1);
      }
   }
}
