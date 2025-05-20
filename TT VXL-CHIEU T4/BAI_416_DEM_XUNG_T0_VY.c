#include <tv_pickit2_shift_1.c>
unsigned int16    t0, t0_tam;
unsigned int8    donvi, chuc, tram, ngan;

void  giai_ma_hien_thi (unsigned int16 tam)
{
   donvi = ma7doan[tam %10];
   chuc  = ma7doan[tam/10%10]; 
   tram  = ma7doan[tam/100%10];
   ngan  = ma7doan[tam/1000];
   if (ngan==0xc0)
   {
      ngan=0xff;
      if (tram==0xc0)
      {
         tram=0xff;
         if (chuc==0xc0)   chuc=0xff;
      }
   }
   xuat_4led_7doan_4so(ngan,tram,chuc,donvi);
}

void main()
{
   set_up_port_ic_chot();
   
   //Thiet lap counter
   setup_timer_0 (t0_ext_l_to_h | t0_div_1); 
   set_timer0(0);
   
   //Khoi tao bien, trang thai led
   t0 = t0_tam = 0;
   giai_ma_hien_thi (t0);
   
   while(true)
   {
      t0=get_timer0();
      
      //kiem tra counter co dem khong?
      if (t0 != t0_tam)
      {
         t0_tam = t0;
         giai_ma_hien_thi (t0);
         if (t0>=10000)   set_timer0(1);
      }
   }
}
