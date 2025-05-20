#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_ds1307_i2c.c>
unsigned  char    giatri_mod;
unsigned int8    donvi_phut, chuc_phut, chuc_giay, donvi_giay, donvi_ngay, chuc_ngay;
signed int8  bdn,i;
const unsigned char daugach[] = {32, 3, 32, 32, 32, 32};
const unsigned char khoangtrang[] = {32, 32, 32, 32, 32, 32};

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

void lcd_hienthi_daugach(signed int8 x2, y2)
{
   lcd_goto_xy(x2,y2); 
   for (i=0;i<6;i++)
   {
      if (i==3)   lcd_goto_xy(x2+1,y2); 
      lcd_data(daugach[i]);
   }
}
void xu_ly_so_to_xoa_0_vo_nghia()
{
   donvi_phut = phut_ds13%16;
   chuc_phut  = phut_ds13/16;

   donvi_giay = giay_ds13%16;
   chuc_giay  = giay_ds13/16;
   
   donvi_ngay = ngay_ds13%16;
   chuc_ngay  = ngay_ds13/16;

   if(chuc_phut == 0) chuc_phut = 10;
   if(chuc_giay == 0) chuc_giay = 10;
   if(chuc_ngay == 0) chuc_ngay = 10;
}
void HT_DS13B07 ( )
{     
   lcd_hienthi_so_z_toado_xy(chuc_phut,0,0);
   lcd_hienthi_so_z_toado_xy(donvi_phut,0,3);
   lcd_hienthi_daugach(0,6);
   lcd_hienthi_so_z_toado_xy(chuc_giay,0,10);
   lcd_hienthi_so_z_toado_xy(donvi_giay,0,13);

   lcd_hienthi_so_z_toado_xy(thu_ds13,2,3);
   lcd_hienthi_daugach(2,6);
   lcd_hienthi_so_z_toado_xy(chuc_ngay,2,10);
   lcd_hienthi_so_z_toado_xy(donvi_ngay,2,13);            
}

void lcd_hienthi_khoangtrang(signed int8 x3, y3)
{
   lcd_goto_xy(x3,y3); 
   for (i=0;i<6;i++)
   {
      if (i==3)   lcd_goto_xy(x3+1,y3); 
      lcd_data(khoangtrang[i]);
   }
}
void nhap_nhay_con_tro() 
{
   lcd_hienthi_khoangtrang(0,0);
   lcd_hienthi_khoangtrang(0,3);
   lcd_hienthi_daugach(0,6);
   lcd_hienthi_khoangtrang(0,10);
   lcd_hienthi_khoangtrang(0,13);

   lcd_hienthi_khoangtrang(2,3);
   lcd_hienthi_daugach(2,6);
   lcd_hienthi_khoangtrang(2,10);
   lcd_hienthi_khoangtrang(2,13);    
}

void main() 
{
   set_up_port_ic_chot();
   
   lcd_command(0x40);
   for (i=0;i<64;i++)  {  lcd_data(lcd_ma_8doan[i]); }
   
   setup_timer_1(t1_internal | t1_div_by_8);
   set_timer1(3036);
   enable_interrupts(global); 
   enable_interrupts(int_timer1); 
   
   setup_lcd();
   lcd_command(lcd_addr_line1);
   doc_thoi_gian_tu_realtime(); 
   if (ma_ds13!=ma_ds)
   {
      thiet_lap_thoi_gian_hien_tai(); 
      nap_thoi_gian_htai_vao_ds13b07();
   }
   
   doc_thoi_gian_tu_realtime(); 

   while(true)
   {
      doc_thoi_gian_tu_realtime();
      xu_ly_so_to_xoa_0_vo_nghia();
      if    (bdn<10) 
         nhap_nhay_con_tro(); 
      else if (bdn < 20)
         HT_DS13B07 ( );
      else
      {
         bdn = bdn-20;

      }     
   } 
}
