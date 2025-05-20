#include <tv_pickit2_shift_1.c> 
//!#include <tv_pickit2_shift_1_proteus.c> 
#include <tv_pickit2_shift_lcd.c> 
unsigned int16 t0,t0_tam;
unsigned int8    donvi, chuc, tram, dv, ch, tr;

void GM_LCD()
{
   donvi = t0%10+0x30;
   chuc  = t0/10%10+0x30; 
   tram  = t0/100+0x30;
   if (tram==0x30)
   {
      tram=0x20;
      if (chuc==0x30)   chuc=0x20;
   }
}
void  giai_ma_hien_thi (unsigned int8 tam)
{
   dv = ma7doan[tam %10];
   ch  = ma7doan[tam/10%10]; 
   tr  = ma7doan[tam/100];
   if (tr==0xc0)
   {
      tr=0xff;
      if (ch==0xc0)   ch=0xff;
   }
   xuat_4led_7doan_3so(tr, ch, dv);
}
void hienthi_lcd()
{
   GM_LCD();
   lcd_goto_xy(0,0);
   lcd_data(tram); 
   lcd_data(chuc); 
   lcd_data(donvi);
}

void main()
{
   set_up_port_ic_chot(); 
   setup_lcd();
   setup_timer_0 (t0_ext_l_to_h | t0_div_1); 
   set_timer0(0);
   t0=t0_tam=0; 
   while(true)
   {
      t0 = get_timer0();
      if (t0!=t0_tam)
      {
         t0_tam = t0;
         if (t0>=101)   set_timer0(1);
      }
      GM_LCD();
      hienthi_lcd();
      giai_ma_hien_thi (t0);
      delay_ms(200);
      
   }
}
