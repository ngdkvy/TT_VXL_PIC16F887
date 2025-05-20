//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c> 
#include <tv_pickit2_shift_key4x4_138.c> 

unsigned int8    t0;
unsigned int8    ch_to, dv_to;
unsigned int8    donvi, chuc, dv, ch;
signed int8  i;
signed int8       giay, bdn;

#int_timer1
void interrupt_timer1()
{
    bdn++;
    set_timer1(3036);
} 

void  giai_ma_hien_thi (unsigned int16 tam)
{
//!   Luu so de hien thi ra LED 
   dv = ma7doan[tam %10];
   ch  = ma7doan[tam/10%10]; 
   
//!   Xoa so 0 vo nghia
   if (ch==0xc0)   ch=0xff;
}

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
   lcd_data(" _ SP"); 
   
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
   set_timer0(3);
   
   setup_timer_1(t1_internal | t1_div_by_8);
   set_timer1(3036);
   enable_interrupts(global); 
   enable_interrupts(int_timer1); 
   
   lcd_command(0x40);
   for (i=0;i<64;i++)  {  lcd_data(lcd_ma_8doan[i]); }
   
   t0 = 3;
   giay = 17;
   bdn = 0;
   while(true)
   {
//!   Doc gia tri Counter
      t0 = get_timer0();
      if (t0 == 16) 
      {
         set_timer0(3); 
         t0 = 3;
      }
      xu_ly_so_to_xoa_0_vo_nghia(t0);
      lcd_hienthi_so_z_toado_xy(dv_to,0,0);
      lcd_hienthi_so_z_toado_xy(ch_to,0,10);
      xu_ly_so_nho_xoa_0_vo_nghia();
      hienthi_lcd();
      if    (bdn<10)    
      {
         giai_ma_hien_thi (giay);
         xuat_4led_7doan_4so(0xCE,dv&0x7f,ch,0xF1);
      }
      else
      {
         bdn = bdn-10;
         giay --;
         if (giay == 7)  giay = 17;
      }
   }
}

