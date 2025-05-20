#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c> 
#define  trigger      pin_e2 
#define  echo         pin_e1
float    kcs;
int16 kq_ht;
signed int8 i;

void  giai_ma_hienthi_4led (float tam) 
{
   unsigned int16  x;
   x =(unsigned int16 ) tam; 
   xuat_4led_7doan_giaima_xoa_so0(x);
}

void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
   lcd_goto_xy(x1,y1); 
   for (i=0;i<6;i++)
   {
      if (i==3)   lcd_goto_xy(x1+1,y1); 
      lcd_data(lcd_so_x[lcd_so][i]);
   }
}

void  tao_xung_trigger()
{
   delay_ms(10);
   output_high(trigger); 
   delay_ms(10); 
   output_low(trigger);
   
   set_timer1(0); 
   while(!(input(echo)));
   setup_timer_1(t1_internal|t1_div_by_4); 
   
   while(input(echo));
   kcs =get_timer1(); 
   setup_timer_1(t1_disabled );
}

void main() 
{
   set_up_port_ic_chot(); 
   setup_timer_1(t1_disabled ); 
   setup_lcd();
   giai_ma_hienthi_4led(kcs); 
   lcd_command(0x40);
   for (i=0;i<64;i++)  {  lcd_data(lcd_ma_8doan[i]); }
   while(true)
   {
      tao_xung_trigger();
      kcs=kcs*0.8;
      kcs = (kcs/58);
      giai_ma_hienthi_4led(kcs);
      kq_ht = (int16) (kcs*10);
      lcd_hienthi_so_z_toado_xy(kq_ht/100, 2, 0);
      lcd_hienthi_so_z_toado_xy(kq_ht/10%10, 2, 3);
      lcd_goto_xy(3,7); 
      lcd_data(3);
      lcd_hienthi_so_z_toado_xy(kq_ht %10, 2, 9);
      delay_ms(500);
   }
}
