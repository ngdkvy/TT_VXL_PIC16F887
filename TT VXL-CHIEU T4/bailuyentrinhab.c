#include <tv_pickit2_shift_1.c> 
//!#include <tv_pickit2_shift_1_proteus.c>  
#include <tv_pickit2_shift_ds18b20.c> 
#include <tv_pickit2_shift_ds1307_i2c.c>

float             lm35b;
int16             kq_ht_lm35b;
unsigned int8     j, solan_lm35 = 35; 
signed int8       i;
const unsigned char daucham[] = {32, 3, 32, 32, 32, 32};
const unsigned char chuU[] = {0, 32, 2, 7, 3, 7};
unsigned int8     donvi_lcd, chuc_lcd;
unsigned int8     donvi_giay, chuc_giay, donvi_thu, chuc_thu;

void doc_nd_lm35b() 
{
   set_adc_channel(1); 
   delay_ms(1);
   lm35b = 0;
   for (j=0; j<solan_lm35; j++) 
   {
      lm35b = lm35b + read_adc(); 
      hien_thi_8led_7doan_quet();
   }
   lm35b = lm35b /2.046; 
   lm35b = lm35b /solan_lm35;
   kq_ht_lm35b = (int16) (lm35b*10); 
}

void giai_ma_gan_cho_8led_quet()
{
   led_7dq[2] = ma7doan [kq_ht_lm35b /10%10] &0x7f;
   led_7dq[3] = ma7doan [kq_ht_lm35b/100] ;
   
   led_7dq[0] = ma7doan [ds18a % 10];
   led_7dq[1] = ma7doan [ds18a / 10];
}

void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
   lcd_goto_xy(x1,y1); 
   for (i=0;i<6;i++)
   {
      if (i==3)   lcd_goto_xy(x1+1,y1); 
      lcd_data(lcd_so_x[lcd_so][i]);
      hien_thi_8led_7doan_quet();
   }
}

void lcd_hienthi_daucham(signed int8 x2, y2)
{
   lcd_goto_xy(x2,y2); 
   for (i=0;i<6;i++)
   {
      if (i==3)   lcd_goto_xy(x2+1,y2); 
      lcd_data(daucham[i]);
      hien_thi_8led_7doan_quet();
   }
}

void hienthi_LCD_nhietdo_nho()
{
   donvi_lcd    = ds18a%10+0x30;
   chuc_lcd     = ds18a/10+0x30; 
   lcd_goto_xy(3,0);
   lcd_data(donvi_lcd);
   lcd_goto_xy(3,19);
   lcd_data(chuc_lcd);
}

void hienthi_LCD_nhietdo_to()
{
   lcd_hienthi_so_z_toado_xy(kq_ht_lm35b%10, 2, 4);
   lcd_hienthi_daucham(3, 7);
   lcd_hienthi_so_z_toado_xy(kq_ht_lm35b/100, 2, 10);
   lcd_hienthi_so_z_toado_xy(kq_ht_lm35b/10%10, 2, 13);
}

void lcd_hienthi_chuU(signed int8 x2, y2)
{
   lcd_goto_xy(x2,y2); 
   for (i=0;i<6;i++)
   {
      if (i==3)   lcd_goto_xy(x2+1,y2); 
      lcd_data(chuU[i]);
      hien_thi_8led_7doan_quet();
   }
}

void hienthi_LCD_thoigian_to()
{
   lcd_hienthi_so_z_toado_xy(giay_ds13/16, 0, 3);
   lcd_hienthi_so_z_toado_xy(giay_ds13%16, 0, 6);
   lcd_goto_xy(1,9);
   lcd_data('.');
   if (thu_ds13 != 1)
   {
      lcd_hienthi_so_z_toado_xy(0, 0, 10);
      lcd_hienthi_so_z_toado_xy(thu_ds13, 0, 13);
   }
   else 
   {
      lcd_hienthi_so_z_toado_xy(5, 0, 10);
      lcd_hienthi_chuU(0,13);
   }
   lcd_goto_xy(1,16);
   lcd_data('.');
}

void luu_giai_ma_hien_thi_sau_khi_chinh() 
{
   nap_thoi_gian_htai_vao_ds13b07(); 
   hienthi_LCD_thoigian_to();
} 
void phim_UP()
{
   if (!input(BT2)) //==0
   {
      delay_ms(20);
      if (!input(BT2))
      {
         if (thu_ds13 == 7) thu_ds13 = 1;
         else
            thu_ds13++;
         luu_giai_ma_hien_thi_sau_khi_chinh();
         while (!input(BT2));
      }
   }
}

void  giai_ma_4_led_7_doan ()
{
//!   Luu so de hien thi ra LED 
   donvi_giay = ma7doan[giay_ds13%16] & 0x7f;
   chuc_giay  = ma7doan[giay_ds13/16]; 
   if (thu_ds13 != 1)
   {
      donvi_thu = ma7doan[thu_ds13] &0x7f;
      chuc_thu = 0xff;
   }
   else 
   {
      chuc_thu  = ma7doan[5] ;
      donvi_thu = 0x41; 
   }
   xuat_4led_7doan_4so(chuc_giay, donvi_giay, chuc_thu, donvi_thu);
}

void main()
{
   set_up_port_ic_chot(); 

   setup_adc(adc_clock_div_32); 
   setup_adc_ports(an0_to_an1|vss_vdd );
   
   khoi_tao_ds18b20();
   
   setup_lcd();
   lcd_command(0x40); 
   for (i=0;i<64;i++)  {  lcd_data(lcd_ma_8doan[i]); }
   
   doc_thoi_gian_tu_realtime(); 
   if (ma_ds13!=ma_ds)
   {
      thiet_lap_thoi_gian_hien_tai(); 
      nap_thoi_gian_htai_vao_ds13b07();
   }
   thu_ds13 = 1;
   nap_thoi_gian_htai_vao_ds13b07();
   giai_ma_4_led_7_doan ();
   
   while(true)
   {
      doc_nd_lm35b();
      phim_UP();
      doc_thoi_gian_tu_realtime(); 
      if(touch_present()) 
      {
         doc_giatri_ds18b20();
         ds18a   =  ds18a>>4;
         ds18a   =  ds18a & 0x0ff;
      }
      giai_ma_gan_cho_8led_quet();
      hien_thi_8led_7doan_quet();
      giai_ma_4_led_7_doan ();
      hienthi_LCD_nhietdo_nho();
      hienthi_LCD_nhietdo_to();
      hienthi_LCD_thoigian_to();
   }

}
