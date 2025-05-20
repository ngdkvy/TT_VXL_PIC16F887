//!TT_DE = 0 => khong cho phep
//!TT_DE = 1 => cho phep

#include    <tv_pickit2_shift_1.c>
#include    <tv_pickit2_shift_ds18b20.c> 
#include    <tv_pickit2_shift_ds1307_i2c.c>
#include    <tv_pickit2_shift_step_motor.c>

unsigned int8        donvi_ds18a, chuc_ds18a, thapphan1_ds18a, thapphan2_ds18a;
signed int8          i;
const unsigned char  chut[]    = {7,  3,  3,  7,  3,  3};
const unsigned char  chue[]    = {7,  6,  6,  7,  3,  3};
unsigned int8        donvi_giay_to, chuc_giay_to;
unsigned int16       kqadc, kcach, chenh_lenh_kcach;
unsigned int8        j, solan_kcach = 20; 
int1                 TT_ED;
signed int8          bdn;
unsigned int8        so_buoc;

#int_timer1
void interrupt_timer1()
{
    bdn++;
    set_timer1(3036);
} 

void  giai_ma_4_led_7_doan ()
{   
   donvi_ds18a = ma7doan[nguyen % 10];
   chuc_ds18a  = ma7doan[nguyen / 10];
   thapphan1_ds18a = ma7doan[tp/100];
   thapphan2_ds18a = ma7doan[tp/10%10];
   xuat_4led_7doan_4so(chuc_ds18a, donvi_ds18a&0x7f,thapphan1_ds18a, thapphan2_ds18a);
}

void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
   lcd_goto_xy(x1,y1); 
   for (i=0;i<6;i++)
   {
      if (i==3)   lcd_goto_xy(x1+1,y1); 
      lcd_data(lcd_so_x[lcd_so][i]);
      hien_thi_8led_7doan_quet(); 
      step_motor_quay_thuan_fs();
   }
}

void hienthi_LCD_nhietdo()
{
   lcd_hienthi_so_z_toado_xy(nguyen/10, 0, 0);
   lcd_hienthi_so_z_toado_xy(nguyen%10, 0, 3);
   lcd_goto_xy(1,6);
   lcd_data('.');
   lcd_goto_xy(1,7);
   lcd_data(tp/100 + 0x30);
   lcd_data(tp/10%10 + 0x30);
   lcd_data(tp%10 + 0x30);
}

void lcd_hienthi_chut(signed int8 x2, y2)
{
   lcd_goto_xy(x2,y2); 
   for (i=0;i<6;i++)
   {
      if (i==3)   lcd_goto_xy(x2+1,y2); 
      lcd_data(chut[i]);
      hien_thi_8led_7doan_quet(); 
      step_motor_quay_thuan_fs();
   }
}

void lcd_hienthi_chue(signed int8 x2, y2)
{
   lcd_goto_xy(x2,y2); 
   for (i=0;i<6;i++)
   {
      if (i==3)   lcd_goto_xy(x2+1,y2); 
      lcd_data(chue[i]);
   }
}

void xu_ly_so_to_xoa_0_vo_nghia()
{
   chuc_giay_to  = giay_ds13/16;
   donvi_giay_to = giay_ds13%16;
   if (chuc_giay_to == 0) chuc_giay_to = 10;
}

void hienthi_LCD_thoigian_to()
{
   xu_ly_so_to_xoa_0_vo_nghia();
   lcd_hienthi_so_z_toado_xy(chuc_giay_to, 2, 7);
   lcd_hienthi_so_z_toado_xy(donvi_giay_to, 2, 10);
   lcd_goto_xy(3,13);
   lcd_data('.');
   lcd_hienthi_chut(2, 14);
   lcd_hienthi_chue(2, 17);
}

void doc_kcach() 
{
   set_adc_channel(2); 
   kqadc = 0;
   for (j=0; j<solan_kcach; j++) 
   {
      kqadc = kqadc + read_adc(); 
      hien_thi_8led_7doan_quet(); 
      step_motor_quay_thuan_fs();
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

void hienthi_LCD_kcach()
{
   if (!TT_ED)
   {
      lcd_hienthi_so_z_toado_xy(10, 2, 0);
      lcd_hienthi_so_z_toado_xy(10, 2, 3);
   }
   else
   {
      if (kcach <= 30)
      {
         lcd_hienthi_so_z_toado_xy(kcach/10, 2, 0);
         lcd_hienthi_so_z_toado_xy(kcach%10, 2, 3);
      }
      else 
      {
         lcd_hienthi_so_z_toado_xy(10, 2, 0);
         lcd_hienthi_so_z_toado_xy(10, 2, 3);
      }
   }

}

void giai_ma_gan_cho_8led_quet()
{
   led_7dq[0] = 0x86;
   led_7dq[1] = 0x87;
   
   led_7dq[2] = ma7doan [giay_ds13 % 16] &0x7f;
   led_7dq[3] = ma7doan [giay_ds13 / 16] &0x7f;
   
   if (led_7dq[3] == 0x40) led_7dq[3] = 0xff;
   
   led_7dq[4] = ma7doan [so_buoc % 10];
   led_7dq[5] = ma7doan [so_buoc / 10];
   if (led_7dq[5] == 0xc0) led_7dq[5] = 0xff;
   
   if (kcach > 30)
   {
      led_7dq[6] = ma7doan [kcach%10];
      led_7dq[7] = ma7doan [kcach/10];
   }
   else
   {
      led_7dq[6] = 0xff;
      led_7dq[7] = 0xff;
   }
   if (!TT_ED)
   {
      led_7dq[6] = 0xBF;
      led_7dq[7] = 0xBF;
   }
}

void phim_ED()
{
   if (!input(BT1)) 
   {
      delay_ms(20);
      if (!input(BT1))
      {
         TT_ED = ~TT_ED;
         while (!input(BT1));
      }
   }
}

void main() 
{
   set_up_port_ic_chot(); 
   
   khoi_tao_ds18b20(); 
   
   setup_timer_1(t1_internal | t1_div_by_8); 
   set_timer1(3036);
   enable_interrupts(global); 
   enable_interrupts(int_timer1); 


   setup_adc(adc_clock_div_32); 
   setup_adc_ports(an0_to_an2|vss_vdd);

   setup_lcd();
   lcd_command(0x40); 
   for (i=0;i<64;i++)  {  lcd_data(lcd_ma_8doan[i]); }
   
   doc_thoi_gian_tu_realtime(); 
   if (ma_ds13!=ma_ds)
   {
      thiet_lap_thoi_gian_hien_tai(); 
      nap_thoi_gian_htai_vao_ds13b07();
   }
   
   TT_ED   = 0;
   so_buoc = 0;
   bdn     = 0;
   
   while(true)
   {
      doc_thoi_gian_tu_realtime(); 
      
      phim_ED();
      if (TT_ED) 
         doc_kcach();
      
      if(touch_present()) 
      {
         doc_giatri_ds18b20();
      }
      
      stepmotor_onoff=1;   //de khoi canh bao 
      step_motor_quay_thuan_fs();
      
      if (bdn<7) 
      {
         hien_thi_8led_7doan_quet();
         step_motor_quay_thuan_fs();
      }
      else
      {
         bdn = 0;
         if (so_buoc <= 15)
            so_buoc++;
         if (so_buoc == 16)
            so_buoc = 0;
      }

      giai_ma_4_led_7_doan ();
      hienthi_LCD_nhietdo();
      hienthi_LCD_thoigian_to();
      hienthi_LCD_kcach();
      giai_ma_gan_cho_8led_quet();
      hien_thi_8led_7doan_quet(); 
   }
}
