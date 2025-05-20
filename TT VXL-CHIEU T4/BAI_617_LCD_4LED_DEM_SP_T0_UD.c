#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c> 
unsigned int8    t0, tmax;
unsigned int8    donvi, chuc, tram, ngan, dv, ch, tr, ng;

void GM_LCD()
{
   donvi = tmax%10+0x30;
   chuc  = tmax/10+0x30; 
   if (chuc==0x30)   chuc=0x20;
   
   tram = t0%10+0x30;
   ngan = t0/10+0x30; 
   if (ngan==0x30)   ngan=0x20;
}
void  giai_ma_hien_thi (unsigned int16 t, unsigned int16 tam)
{
   dv = ma7doan[tam %10];
   ch  = ma7doan[tam/10%10]; 
   if (ch==0xc0)   ch=0xff;
   tr  = ma7doan[t%10];
   ng  = ma7doan[t/10%10];
   if (ng==0xc0)   ng=0xff;
   xuat_4led_7doan_4so(ng,tr&0x7f,ch,dv);
}
void hienthi_lcd()
{
   lcd_goto_xy(0,0);
   lcd_data("Gia tri cai: "); 
   lcd_goto_xy(0,15);
   lcd_data(chuc); 
   lcd_data(donvi);
   
   lcd_goto_xy(1,0);
   lcd_data("Gia tri dem: "); 
   lcd_goto_xy(1,15);
   lcd_data(ngan); 
   lcd_data(tram);
}

void phim_UP()
{
   if (!input(BT0))
   {
      delay_ms(20);
      if (!input(BT0))
      {
         tmax++;
         while (!input(BT0));
      }
   }
} 
void phim_DW()
{
   if (!input(BT1))
   {
      delay_ms(20);
      if (!input(BT1))
      {
         if (tmax > 0)
            tmax--;
         while (!input(BT1));
      }
   }
} 
void phim_CLR()
{
   if (!input(BT2))
   {
      delay_ms(20);
      if (!input(BT2))
      {
         tmax = 1;
         set_timer0(0);
         t0 = 0;
         while (!input(BT2));
      }
   }
} 

void main()
{
   set_up_port_ic_chot(); 
   setup_lcd();
   
   //Thiet lap counter
   setup_timer_0 (t0_ext_l_to_h | t0_div_1); 
   set_timer0(0);
   
   //Khoi tao bien
   t0 = 0;
   tmax = 99;
   giai_ma_hien_thi (tmax, t0);
   GM_LCD();
   hienthi_lcd();
   while(true)
   {
      t0=get_timer0();
      phim_UP();
      phim_DW();
      phim_CLR();
      //kiem tra counter co dem khong?
      if (t0>tmax)   
      {
         t0 = 0;
         set_timer0(0);
      }
      GM_LCD();
      hienthi_lcd();
      giai_ma_hien_thi (tmax, t0);
      delay_ms(200);
   }
}
