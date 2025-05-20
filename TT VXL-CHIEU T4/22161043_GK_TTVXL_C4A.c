#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c> 
#include <tv_pickit2_shift_key4x4_138.c> 

unsigned int8    t0;
unsigned int8    ch_to, dv_to;
unsigned int8    donvi, chuc;
signed int8  i;

void xu_ly_so_nho_xoa_0_vo_nghia()
{
   donvi = t0%10+0x30;
   chuc  = t0/10+0x30; 
   if (chuc==0x30)   chuc=0x20;
}

void xu_ly_so_to_xoa_0_vo_nghia(unsigned int16 so)
{
   ch_to = so/10;
   dv_to = so%10;
   if(ch_to == 0) ch_to = 10;
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

void hienthi_lcd()
{
   lcd_goto_xy(2,8);
   lcd_data(chuc); 
   lcd_data(donvi);
   
   lcd_goto_xy(2,10);
   lcd_data("_SP"); 
   
   lcd_goto_xy(3,0);
   lcd_data("Unit: "); 
   lcd_goto_xy(3,7);
   lcd_data(donvi);

   lcd_goto_xy(3,11);
   lcd_data("Dozen: "); 
   lcd_goto_xy(3,19);
   lcd_data(chuc);
}
void main()
{
//!   Khoi tao ban dau + LCD
   set_up_port_ic_chot();
   setup_lcd();
//!   set_tris_b(0x3c); 
//!   Cai dat timer0
   setup_timer_0 (t0_ext_l_to_h | t0_div_1| t0_8_bit); 
   set_timer0(0);
   
   lcd_command(0x40);
   for (i=0;i<64;i++)  {  lcd_data(lcd_ma_8doan[i]); }
   
   t0 = 3;
   
   while(true)
   {
//!   Doc gia tri Counter
      t0 = get_timer0();
      if (t0 == 16) 
      {
         set_timer0(0); 
         t0 = 3;
      }
      xu_ly_so_to_xoa_0_vo_nghia(t0);
      lcd_hienthi_so_z_toado_xy(ch_to,0,0);
      lcd_hienthi_so_z_toado_xy(dv_to,0,10);
      xu_ly_so_nho_xoa_0_vo_nghia();
      hienthi_lcd();
   }
}

