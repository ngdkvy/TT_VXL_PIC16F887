#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_ds18b20.c>
#include <tv_pickit2_shift_lcd.c> 
#define     gh_nda_tren   40
#define     gh_nda_duoi   36

int1 ttqn;

void GM_LED_QUET()
{
   led_7dq[0] = ma7doan[ds18a%10];
   led_7dq[1] = ma7doan[ds18a/10];
}

void  giai_ma_hien_thi ()
{
   if (!ttqn)
      xuat_4led_7doan_2so(0xB0, 0x92);
   else 
      xuat_4led_7doan_2so(0xB0, 0xB0);
      
}

void gm_lcd()
{
   lcd_goto_xy(0,18);
   if (!ttqn)
   {
      lcd_data("35");
   }
   else 
   {
      lcd_data("35");  
   }
}
void main() 
{
   set_up_port_ic_chot(); 
   khoi_tao_ds18b20();
   setup_lcd();
   xuat_32led_don_1dw(0);
   ttqn = 0;
   while(true)
   {
      if(touch_present()) {doc_giatri_ds18b20();} 
      ds18a   =  ds18a>>4;
      ds18a   =  ds18a & 0x0ff;
      GM_LED_QUET();
      gm_lcd();
      giai_ma_hien_thi ();
      hien_thi_8led_7doan_quet_all();
      if (ds18a>gh_nda_tren)
      {
         ttqn = 1;
         triac_2_off();
         xuat_32led_don_1dw(0x0000ffff);
      }
      else if (ds18a<gh_nda_tren)
      {

         xuat_32led_don_1dw(0);
      }
      if (ds18a<gh_nda_duoi)
      {
         ttqn = 0;
         triac_2_on();
      }
      
      hien_thi_8led_7doan_quet_all();
   }
}
