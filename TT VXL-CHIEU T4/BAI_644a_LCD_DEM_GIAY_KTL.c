//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
signed int8    i;
unsigned int8    ch_to, dv_to;
signed int8       giay, bdn;
const unsigned char chuP[] = {7, 6, 7, 7, 32, 32};

#int_timer1
void interrupt_timer1()
{
    bdn++;
    set_timer1(3036);
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
void lcd_hienthi_chuP(signed int8 x2, y2)
{
   lcd_goto_xy(x2,y2); 
   for (i=0;i<6;i++)
   {
      if (i==3)   lcd_goto_xy(x2+1,y2); 
      lcd_data(chuP[i]);
  }
}
void xu_ly_so_to_xoa_0_vo_nghia(unsigned int16 so)
{
   ch_to = so/10;
   dv_to = so%10;
   if(ch_to == 0) ch_to = 10;
}
void main()
{
   set_up_port_ic_chot();
   setup_lcd();
   setup_timer_1(t1_internal | t1_div_by_8);
   set_timer1(3036);
   enable_interrupts(global); 
   enable_interrupts(int_timer1); 
   giay = 0;
   bdn=0;
   lcd_goto_xy(0,0);
   lcd_data("******dem giay******");
   
   lcd_command(0x40);
   for (i=0;i<64;i++)  {  lcd_data(lcd_ma_8doan[i]); }
   lcd_hienthi_so_z_toado_xy(5,2,7);
   lcd_hienthi_chuP(2,10);
   while(true)
   {
      if    (bdn<10)    
      {
         xu_ly_so_to_xoa_0_vo_nghia(giay);
         lcd_hienthi_so_z_toado_xy(ch_to,2,0); 
         lcd_hienthi_so_z_toado_xy(dv_to,2,3);
         delay_ms(500);
      }
      else
      {
         bdn = bdn-10;
         giay++;
         if (giay==60)    giay =0;
      }
   }
}
