#include <tv_pickit2_shift_1.c> 
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>

unsigned int8     j, solan = 100, so_lan_kc = 20 ; 
unsigned int16    lm35a, lm35b;
signed int8       i;
unsigned int8     donvi_lm35a, chuc_lm35a, donvi_lm35b, chuc_lm35b, donvi_kcach, chuc_kcach;
unsigned int16    kqadc, kcach, chenh_lenh_kcach;
unsigned int8     dv_lm35b, ch_lm35b, dv_kcach, ch_kcach;

void  giai_ma_hien_thi ()
{
   dv_lm35b  = ma7doan[lm35b%10];
   ch_lm35b  = ma7doan[lm35b/10]; 
   dv_kcach  = ma7doan[kcach%10];
   ch_kcach  = ma7doan[kcach/10]; 
   xuat_4led_7doan_4so(ch_kcach, dv_kcach&0x7f, ch_lm35b, dv_lm35b);
}

void giai_ma_gan_cho_8led_quet()
{
   led_7dq[6] = ma7doan [kcach %10];
   led_7dq[7] = ma7doan [kcach/10];

   led_7dq[3] = ma7doan [lm35a %10];
   led_7dq[4] = ma7doan [lm35a/10];
   
   led_7dq[0] = ma7doan [lm35b %10];
   led_7dq[1] = ma7doan [lm35b /10];
   
   if (led_7dq[1] == 0xc0) led_7dq[1] = 0xff;
   if (led_7dq[4] == 0xc0) led_7dq[7] = 0xff;
   if (led_7dq[7] == 0xc0) led_7dq[7] = 0xff;
}

void GM_LCD()
{
   donvi_lm35a = lm35a%10+0x30;
   chuc_lm35a  = lm35a/10+0x30; 
   
   donvi_lm35b  = lm35b%10+0x30;
   chuc_lm35b   =  lm35b/10+0x30;
   
   donvi_kcach  = kcach%10+0x30;
   chuc_kcach   =  kcach/10+0x30;
   
   if (chuc_lm35a   == 0x30)     chuc_lm35a = 0x20;
   if (chuc_lm35b   == 0x30)     chuc_lm35b = 0x20;
   if (chuc_kcach   == 0x30)     chuc_kcach = 0x20;
}

void hienthi_lcd()
{
   GM_LCD();
   lcd_goto_xy(0,8);
   lcd_data(chuc_lm35a); 
   lcd_data(donvi_lm35a); 
   lcd_goto_xy(0,16);
   lcd_data(chuc_lm35b); 
   lcd_data(donvi_lm35b); 
   lcd_goto_xy(0,0);
   lcd_data(chuc_kcach); 
   lcd_data(donvi_kcach); 
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

void doc_nd_lm35a() 
{
   set_adc_channel(0); 
   lm35a = 0;
   delay_ms(1);
   for (j=0; j<solan; j++) 
   {
      lm35a = lm35a + read_adc();
      hien_thi_8led_7doan_quet(); 
   }
   lm35a = lm35a /2.046; 
   lm35a = lm35a /solan;
}

void doc_nd_lm35b() 
{
   set_adc_channel(1); 
   delay_ms(1);
   lm35b = 0;
   for (j=0; j<solan; j++) 
   {
      lm35b = lm35b + read_adc(); 
      hien_thi_8led_7doan_quet(); 
   }
   lm35b = lm35b /2.046; 
   lm35b = lm35b /solan;
}

void doc_kc() 
{
   set_adc_channel(2); 
   kqadc = 0;
   delay_ms(1);
   for (j=0; j<so_lan_kc; j++) 
   {
      kqadc = kqadc + read_adc(); 
      hien_thi_8led_7doan_quet(); 
   }
   kqadc = kqadc / so_lan_kc;
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
   setup_adc(adc_clock_div_32); 
   setup_adc_ports(an0_to_an2|vss_vdd);
   setup_lcd();
   
   lcd_command(0x40);
   for (i=0;i<64;i++)  {  lcd_data(lcd_ma_8doan[i]); }
   
   while(true)
   {
      doc_nd_lm35a();
      doc_nd_lm35b();
      doc_kc();
      giai_ma_gan_cho_8led_quet();
      hien_thi_8led_7doan_quet(); 
      giai_ma_hien_thi ();
      hienthi_lcd();
      lcd_hienthi_so_z_toado_xy(kcach/10, 2, 0);
      lcd_hienthi_so_z_toado_xy(kcach%10, 2, 3);
      lcd_hienthi_so_z_toado_xy(lm35a/10, 2, 7);
      lcd_hienthi_so_z_toado_xy(lm35a%10, 2, 10);
      lcd_hienthi_so_z_toado_xy(lm35b/10, 2, 14);
      lcd_hienthi_so_z_toado_xy(lm35b%10, 2, 17);
   }
}
