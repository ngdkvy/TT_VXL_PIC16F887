#include <tv_pickit2_shift_1.c> 
//!#include <tv_pickit2_shift_1_proteus.c>  
#include <tv_pickit2_shift_ds18b20.c> 
#include <tv_pickit2_shift_ds1307_i2c.c>

float                lm35b;
int16                kq_ht_lm35b;
unsigned int8        j, solan_lm35 = 100, solan_kcach = 20; 
signed int8          i;
const unsigned char  daucham[] = {32,  3,  32, 32, 32, 32};
const unsigned char  chuU[]    = {0,  32,   2,  7,  3,  7};
unsigned int8        donvi_lcd, chuc_lcd;
unsigned int8        donvi_giay, chuc_giay, donvi_thu, chuc_thu;
unsigned int16       kqadc, kcach, chenh_lenh_kcach;
signed int8          bdn;

//!Xu ly ngat timer1
#int_timer1
void interrupt_timer1()
{
    bdn++;
    set_timer1(3036);
} 

//!Doc LM35 o kenh 1
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
   
//!   Xu ly so de lay phan thap phan
   kq_ht_lm35b = (int16) (lm35b*10); 
}

void giai_ma_gan_cho_8led_quet()
{
//!   Xu ly nhiet do do tu LM35 o kenh 1 va hien thi dau cham  
   led_7dq[2] = ma7doan [kq_ht_lm35b /10%10] &0x7f;
   led_7dq[3] = ma7doan [kq_ht_lm35b/100];
   
//!   Xu ly nhiet do do tu DS18B20
   led_7dq[0] = ma7doan [ds18a % 10];
   led_7dq[1] = ma7doan [ds18a / 10];
   
//!   xuat dau gach tren, duoi ra LED
   led_7dq[7] = 0xF7;
   led_7dq[4] = 0xFE;
   
//!   Xu ly so do khoang cach va hien thi dau cham
   led_7dq[5] = ma7doan [kcach % 10]& 0x7f;
   led_7dq[6] = ma7doan [kcach / 10] ;
}

//!Ham hien thi so font to ra LCD
void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
   lcd_goto_xy(x1,y1); 
   for (i=0;i<6;i++)
   {
      if (i==3)   lcd_goto_xy(x1+1,y1); 
      lcd_data(lcd_so_x[lcd_so][i]);
   }
}

//!Ham hien thi dau cham font to ra LCD
void lcd_hienthi_daucham(signed int8 x2, y2)
{
   lcd_goto_xy(x2,y2); 
   for (i=0;i<6;i++)
   {
      if (i==3)   lcd_goto_xy(x2+1,y2); 
      lcd_data(daucham[i]);
   }
}

//!Hien thi nhiet do do duoc tu DS18B20 ra LCD
void hienthi_LCD_nhietdo_nho()
{
   donvi_lcd    = ds18a%10+0x30;
   chuc_lcd     = ds18a/10+0x30; 
   
//!   Di chuyen den dau LCD
   lcd_goto_xy(3,0);
   lcd_data(donvi_lcd);
   
//!   Di chuyen den cuoi LCD
   lcd_goto_xy(3,19);
   lcd_data(chuc_lcd);
}

//!Hien thi nhiet do do duoc tu LM35 kenh 1  dung font to ra LCD
void hienthi_LCD_nhietdo_to()
{
   lcd_hienthi_so_z_toado_xy(kq_ht_lm35b%10, 2, 4);
   lcd_hienthi_daucham(3, 7);
   lcd_hienthi_so_z_toado_xy(kq_ht_lm35b/100, 2, 10);
   lcd_hienthi_so_z_toado_xy(kq_ht_lm35b/10%10, 2, 13);
}

//!Ham hien thi chu U font to ra LCD
void lcd_hienthi_chuU(signed int8 x2, y2)
{
   lcd_goto_xy(x2,y2); 
   for (i=0;i<6;i++)
   {
      if (i==3)   lcd_goto_xy(x2+1,y2); 
      lcd_data(chuU[i]);
   }
}

//!Hien thi real time dung font to ra LCD
void hienthi_LCD_thoigian_to()
{
   lcd_hienthi_so_z_toado_xy(giay_ds13/16, 0, 3);
   lcd_hienthi_so_z_toado_xy(giay_ds13%16, 0, 6);
   lcd_goto_xy(1,9);
   lcd_data('.');
   
//!   Thu doc duoc tu cam bien DS1307 la tu 1 -> 7
//!   Cho 1 la Chu nhat
//!   Neu 2 -> 7 xuat so binh thuong
//!   Con la 1 thi xu ly hien thi SU
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
//!Sau khi chinh sua luu lai gia tri da dieu chinh vao bo nho cua cam bien
   nap_thoi_gian_htai_vao_ds13b07(); 
   hienthi_LCD_thoigian_to();
} 

void phim_UP()
{
   if (!input(BT2))
   {
      delay_ms(20);
      if (!input(BT2))
      {
//!         Xu ly phan dieu chinh tang thu
//!         Xet bang 7 vi khi thu = 7, nhan nut BT2 thu se tang len 8, nhung cam bien chi doc duoc tu 1 -> 7
//!         Nen khong cho tang ma gan thu = 1
         if (thu_ds13 == 7) thu_ds13 = 1;
         else
            thu_ds13++;
            
//!         Sau khi chinh sua luu lai gia tri da dieu chinh vao bo nho cua cam bien
         luu_giai_ma_hien_thi_sau_khi_chinh();
         while (!input(BT2));
      }
   }
}

void  giai_ma_4_led_7_doan ()
{
//!   Xu ly giay cua cam bien DS1307 va hien thi dau cham  
   donvi_giay = ma7doan[giay_ds13%16] & 0x7f;
   chuc_giay  = ma7doan[giay_ds13/16]; 
   
//!   Thu doc duoc tu cam bien DS1307 la tu 1 -> 7
//!   Cho 1 la Chu nhat
//!   Neu 2 -> 7 xuat so binh thuong
//!   Con la 1 thi xu ly hien thi SU
//!   Co xu ly hien thi dau cham nhu yeu cau de bai
//!   0xff: tat led
//!   0x41: U + .
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

//!Do khoang cach bang cam bien GP2D12 o kenh 2
void doc_kcach() 
{
   set_adc_channel(2); 
   kqadc = 0;
   for (j=0; j<solan_kcach; j++) 
   {
      kqadc = kqadc + read_adc(); 
      hien_thi_8led_7doan_quet(); 
   }
   kqadc = kqadc / solan_kcach;
   if (kqadc <= 80)
      kcach = 80;
   else if ((kqadc > 80) && (kqadc < 87))
   {
      chenh_lenh_kcach = kqadc - 80;
      kcach = 80 - chenh_lenh_kcach/0.77;
   }
   else if (kqadc == 87)
      kcach = 70;
   else if ((kqadc > 87) && (kqadc < 106))
   {
      chenh_lenh_kcach = kqadc - 87;
      kcach = 70 - chenh_lenh_kcach/2.11;
   }
   else if (kqadc == 106)
      kcach = 60;
   else if ((kqadc > 106) && (kqadc < 124))
   {
      chenh_lenh_kcach = kqadc - 106;
      kcach = 60 - chenh_lenh_kcach/2;
   }
   else if (kqadc == 124)
      kcach = 50;
   else if ((kqadc > 124) && (kqadc < 150))
   {
      chenh_lenh_kcach = kqadc - 124;
      kcach = 50 - chenh_lenh_kcach/2.88;
   }
   else if (kqadc == 150)
      kcach = 40;
   else if ((kqadc > 150) && (kqadc < 196))
   {
      chenh_lenh_kcach = kqadc - 150;
      kcach = 40 - chenh_lenh_kcach/5.11;
   }
   else if (kqadc == 196)
      kcach = 30;
   else if ((kqadc > 196) && (kqadc < 276))
   {
      chenh_lenh_kcach = kqadc - 196;
      kcach = 30 - chenh_lenh_kcach/8.88;
   }
   else if (kqadc == 276)
      kcach = 20;
   else if ((kqadc > 276) && (kqadc < 490))
   {
      chenh_lenh_kcach = kqadc - 276;
      kcach = 20 - chenh_lenh_kcach/23.77;
   }
   else if (kqadc == 490)
      kcach = 10;
}

void main()
{
   set_up_port_ic_chot(); 
   
//!   Cai dat Timer1 + Xu ly ngat
   setup_timer_1(t1_internal | t1_div_by_8); 
   set_timer1(3036);
   enable_interrupts(global); 
   enable_interrupts(int_timer1); 
   
//!   Cai dat bo chia, kenh va nguon dien
   setup_adc(adc_clock_div_32); 
   setup_adc_ports(an0_to_an2|vss_vdd );
   
//!   Khoi tao cho cam bien DS18B20: real time
   khoi_tao_ds18b20();
   
//!   khoi tao LCD + Luu cac doan a, b, c, e, f, g+d vao CGRAM de tao font to
   setup_lcd();
   lcd_command(0x40); 
   for (i=0;i<64;i++)  {  lcd_data(lcd_ma_8doan[i]); }
   
//!   Doc gia tri thoi gian tu cam bien DS18B20: real time va thiet lap lai thoi gian
   doc_thoi_gian_tu_realtime(); 
   if (ma_ds13!=ma_ds)
   {
      thiet_lap_thoi_gian_hien_tai(); 
      nap_thoi_gian_htai_vao_ds13b07();
   }
   
//!De bai yeu cau thu ban dau la CN, nen khoi tao lai thu va luu vao bo nho cam bien
   thu_ds13 = 1;
   nap_thoi_gian_htai_vao_ds13b07();
   giai_ma_4_led_7_doan ();

   bdn=0;

   while(true)
{
//!   doc nhiet do do duoc tu LM35 o kenh 1, do khoang cach
      doc_nd_lm35b();
      doc_kcach();
      
//!      Goi ham kiem tra phim nhan
      phim_UP();
      
//!      Doc thoi gian tu cam bien DS1307
      doc_thoi_gian_tu_realtime(); 
      
//!      Doc nhiet do do duoc tu DS13B20
      if(touch_present()) 
      {
         doc_giatri_ds18b20();
         ds18a   =  ds18a>>4;
         ds18a   =  ds18a & 0x0ff;
      }
      if (kcach > 40)
      {
         if (bdn < 10)
         {
            giai_ma_4_led_7_doan ();
            hien_thi_8led_7doan_quet();
         }
         else if (bdn <30)
         {
            xuat_4led_7doan_4so(0xff, 0xff, 0xff, 0xff);//tat led
            hien_thi_8led_7doan_quet();
         }
         else
            bdn = 0;
      }
      else 
      {
         giai_ma_4_led_7_doan ();
         bdn = 0;
      }
      giai_ma_gan_cho_8led_quet();
      hien_thi_8led_7doan_quet();
      hienthi_LCD_nhietdo_nho();
      hienthi_LCD_nhietdo_to();
      hienthi_LCD_thoigian_to();
   }
}
