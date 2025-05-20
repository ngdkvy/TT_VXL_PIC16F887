#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
#include <tv_pickit2_shift_key4x4_138.c> 

unsigned int8    t0, tmax;
signed int8  mp;
unsigned int8 mp_lcd[2]={' '};
unsigned int8    donvi, chuc, tram, ngan;

void GM_LCD()
{
   if (mp < 10)
   {
//!doi so hien tai sang hang chuc, gan so vua nhan tu ma tran phim vao hang don vi, +0x30 de xuat ra lcd
      mp_lcd[1] = mp_lcd[0];
      mp_lcd[0] = mp + 0x30;
   }
   if (mp == 12)
   {
      tmax = 1;
      
//!0x31: so 1
//!0x30: so 0
      mp_lcd[0] = 0x31;
      mp_lcd[1] = 0x30;
   }
   if (mp == 15)
   {
      //!-0x30 de quy doi ra so thap phan
      tmax = (mp_lcd[1] - 0x30)*10 + (mp_lcd[0] - 0x30);
   }
}

void hienthi_lcd()
{
   lcd_goto_xy(0,0);
   lcd_data("Gia tri cai: "); 
   lcd_goto_xy(0,15);
   
//!+0x30 de xuat ra lcd   
   lcd_data(tmax/10 + 0x30); 
   lcd_data(tmax%10 + 0x30);
   
   lcd_goto_xy(1,0);
   lcd_data("Gia tri dem: "); 
   lcd_goto_xy(1,15);
   lcd_data(t0/10+0x30); 
   lcd_data(t0%10+0x30);
}
void  giai_ma_hien_thi (unsigned int16 t, unsigned int16 tam)
{
   donvi = ma7doan[tam %10];
   chuc  = ma7doan[tam/10%10]; 
   tram  = ma7doan[t%10];
   ngan  = ma7doan[t/10%10];
   xuat_4led_7doan_4so(ngan,tram&0x7f,chuc,donvi);
}
void main()
{
   set_up_port_ic_chot(); 
   setup_lcd();
   set_tris_b(0x3c);
   //Thiet lap counter
   setup_timer_0 (t0_ext_l_to_h | t0_div_1); 
   set_timer0(0);
   
   //Khoi tao bien
   t0  = 0;
   tmax = 99;
   giai_ma_hien_thi (tmax, t0);
   hienthi_lcd();
   
   while(true)
   {
      t0=get_timer0();
      mp= key_4x4_up();
      if (mp != 0xff)
         GM_LCD();
      if (t0>tmax)   
      {
         t0 = 0;
         set_timer0(0);
      }
      giai_ma_hien_thi (tmax, t0);
      hienthi_lcd();
   }
}
