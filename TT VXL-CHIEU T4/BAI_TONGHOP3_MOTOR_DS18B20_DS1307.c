//!BT0 chinh dao chieu motor
//!BT1 chon che do chinh thoi gian
//!BT2 tang so duoc chon
//!BT3 giam so duoc chon

#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_step_motor.c> 
#include <tv_pickit2_shift_ds18b20.c> 
#include <tv_pickit2_shift_ds1307_i2c.c>

unsigned int16 so_buoc;
unsigned int16 donvi_motor, chuc_motor, tram_motor, ngan_motor;
unsigned  char    giatri_mod;
signed int8  bdn;

#int_timer1
void interrupt_timer1()
{
    bdn++;
    set_timer1(3036);
} 

void  giai_ma_hien_thi ()
{
//!   Luu so de hien thi ra LED 
   donvi_motor = ma7doan[so_buoc%10];
   chuc_motor  = ma7doan[so_buoc/10%10]; 
   tram_motor  = ma7doan[so_buoc/100%10]; 
   ngan_motor  = ma7doan[so_buoc/1000]; 
   
//!   Xoa so 0 vo nghia
   if (ngan_motor == 0xc0)   
   {
      ngan_motor = 0xff;
      if (tram_motor == 0xc0)   
      {
         tram_motor = 0xff;
         if (chuc_motor == 0xc0)   
            chuc_motor = 0xff;
      }
   }
   xuat_4led_7doan_4so(ngan_motor, tram_motor, chuc_motor, donvi_motor);
}

void giai_ma_gan_cho_8led_quet()
{
   led_7dq[0] = ma7doan [tp % 10];
   led_7dq[1] = ma7doan [tp / 10];
   
   led_7dq[2] = ma7doan [nguyen % 10];
   led_7dq[3] = ma7doan [nguyen / 10];
}

void ht_ds13b07 ( )
{     
      lcd_command (0x8c);
      lcd_data(gio_ds13/16  +0x30);    lcd_data(gio_ds13%16  +0x30);
      lcd_data(' ');
      lcd_data(phut_ds13/16 +0x30);    lcd_data(phut_ds13%16 +0x30);
      lcd_data(' ');
      lcd_data(giay_ds13/16 +0x30);    lcd_data(giay_ds13%16 +0x30);
      lcd_command (0xc9); 
      if (thu_ds13 != 1)
      {
         LCD_DATA(' ');
         LCD_DATA(THU_DS13 + 0X30);
      }
      else
      {
         LCD_DATA("CN");            
      }
      lcd_command (0xcb);
      lcd_data(' ');
      lcd_data(ngay_ds13/16 +0x30);    lcd_data(ngay_ds13%16 +0x30);
      lcd_data(' ');
      lcd_data(thang_ds13/16 +0x30);   lcd_data(thang_ds13%16 +0x30);
      lcd_data(' ');
      lcd_data(nam_ds13/16 +0x30);     lcd_data(nam_ds13%16 +0x30); 
}

void hien_thi_gia_tri_mod ( ) 
{
   lcd_command(0x8a); 
   lcd_data(giatri_mod+0x30);
}

void phim_mod() 
{
   if (!input(BT1)) 
   {
      delay_ms(20);
      if (!input(BT1))
      {
         if(giatri_mod<7)  giatri_mod++;
         else              giatri_mod=0;
         hien_thi_gia_tri_mod ( );
         while(!input(BT1));
      }
   } 
}

void phim_inv()
{
   if (!input(BT0))
   {
      delay_ms(20);
      if (!input(BT0))
      {
         stepmotor_tn=~stepmotor_tn;    
         motor_step_run_fs();
         so_buoc = 0;
         giai_ma_hien_thi ();
         delay_ms(stepmotor_delay);
         while (!input(BT0));
      }
   }
} 

unsigned  int8 hieu_chinh_so_bcd_tang(unsigned  int8 x ) 
{
    unsigned  int8 y; 
    y = x;
    x = x & 0x0f;
    if  (x==0x0a)   y = y + 6; 
    return(y);
}

unsigned  int8 hieu_chinh_so_bcd_giam(unsigned  int8 x ) 
{
    unsigned  int8 y; 
    y = x;
    x = x & 0x0f;
    if  (x==0x0f)   y = y - 6; 
    return(y);
}

void luu_giai_ma_hien_thi_sau_khi_chinh() 
{
   nap_thoi_gian_htai_vao_ds13b07(); 
   HT_DS13B07 ( );
} 

void phim_up() 
{
   if (!input(BT2)) 
   {
      delay_ms(20);
      if (!input(BT2))
      {
         switch (giatri_mod)
         {
            case 1:  if (giay_ds13==0x59) giay_ds13=0;
                     else
                     {
                        giay_ds13++;
                        giay_ds13=hieu_chinh_so_bcd_tang(giay_ds13);
                     }
                        luu_giai_ma_hien_thi_sau_khi_chinh();
                     break;
            
            case 2:  if (phut_ds13==0x59) phut_ds13=0;
                     else
                     {
                        phut_ds13++;
                        phut_ds13=hieu_chinh_so_bcd_tang(phut_ds13);
                     }
                        luu_giai_ma_hien_thi_sau_khi_chinh();
                     break;
            
            case 3:  if (gio_ds13==0x23) gio_ds13=0;
                     else
                     {
                        gio_ds13++;
                        gio_ds13=hieu_chinh_so_bcd_tang(gio_ds13);
                     }
                        luu_giai_ma_hien_thi_sau_khi_chinh();
                     break;
            
            case 4:  if (ngay_ds13==0x31) ngay_ds13=1;
                     else
                     {
                        ngay_ds13++;
                        ngay_ds13=hieu_chinh_so_bcd_tang(ngay_ds13);
                     }
                        luu_giai_ma_hien_thi_sau_khi_chinh();
                     break;
            
            case 5:  if (thang_ds13==0x12) thang_ds13=1;
                     else
                     {
                        thang_ds13++;
                        thang_ds13=hieu_chinh_so_bcd_tang(thang_ds13);
                     }
                        luu_giai_ma_hien_thi_sau_khi_chinh();
                     break;
            
            case 6:  if (nam_ds13==0x99) nam_ds13=0;
                     else
                     {
                        nam_ds13++;
                        nam_ds13=hieu_chinh_so_bcd_tang(nam_ds13);
                     }
                        luu_giai_ma_hien_thi_sau_khi_chinh();
                     break;
            case 7:  if (thu_ds13==7) thu_ds13=1;
                     else
                     {
                        thu_ds13++;
                        thu_ds13=hieu_chinh_so_bcd_tang(thu_ds13);
                     }
                        luu_giai_ma_hien_thi_sau_khi_chinh();
                     break;
            default: break;
         }
         while(!input(BT2));
      }
   }
}

void phim_dw() 
{
   if (!input(BT3)) 
   {
      delay_ms(20);
      if (!input(BT3))
      {
         switch (giatri_mod)
         {
            case 1:  if (giay_ds13==0) giay_ds13=0x59;
                     else
                     {
                        giay_ds13--;
                        giay_ds13=hieu_chinh_so_bcd_giam(giay_ds13);
                     }
                        luu_giai_ma_hien_thi_sau_khi_chinh();
                     break;
            
            case 2:  if (phut_ds13==0) phut_ds13=0x59;
                     else
                     {
                        phut_ds13--;
                        phut_ds13=hieu_chinh_so_bcd_giam(phut_ds13);
                     }
                        luu_giai_ma_hien_thi_sau_khi_chinh();
                     break;
            
            case 3:  if (gio_ds13==0) gio_ds13=0x23;
                     else
                     {
                        gio_ds13--;
                        gio_ds13=hieu_chinh_so_bcd_giam(gio_ds13);
                     }
                        luu_giai_ma_hien_thi_sau_khi_chinh();
                     break;
            
            case 4:  if (ngay_ds13==0) ngay_ds13=0x31;
                     else
                     {
                        ngay_ds13--;
                        ngay_ds13=hieu_chinh_so_bcd_giam(ngay_ds13);
                     }
                        luu_giai_ma_hien_thi_sau_khi_chinh();
                     break;
            
            case 5:  if (thang_ds13==1) thang_ds13=0x12;
                     else
                     {
                        thang_ds13--;
                        thang_ds13=hieu_chinh_so_bcd_giam(thang_ds13);
                     }
                        luu_giai_ma_hien_thi_sau_khi_chinh();
                     break;
            
            case 6:  if (nam_ds13==0) nam_ds13=0x99;
                     else
                     {
                        nam_ds13--;
                        nam_ds13=hieu_chinh_so_bcd_giam(nam_ds13);
                     }
                        luu_giai_ma_hien_thi_sau_khi_chinh();
                     break;
            case 7:  if (thu_ds13==0) thu_ds13=7;
                     else
                     {
                        thu_ds13--;
                        thu_ds13=hieu_chinh_so_bcd_giam(thu_ds13);
                     }
                        luu_giai_ma_hien_thi_sau_khi_chinh();
                     break;            
            default: break;
         }
         while(!input(BT3));
      }
   }
} 

void nhap_nhay_con_tro() 
{
   switch (giatri_mod) 
   {
      case 1:  lcd_command(0x92);
               lcd_data("  ");
               break;
      case 2:  lcd_command(0x8F);
               lcd_data("  ");
               break;
      case 3:  lcd_command(0x8C);
               lcd_data("  ");
               break;
      case 4:  lcd_command(0xCC);
               lcd_data("  ");
               break;
      case 5:  lcd_command(0xCF);
               lcd_data("  ");
               break;     
      case 6: lcd_command(0xd2);
               lcd_data("  ");
               break;
      case 7: lcd_command(0xc9);
               lcd_data("  ");
               break;
      default: break;
   }
}

void main() 
{
   set_up_port_ic_chot(); 
   
   setup_lcd();
   khoi_tao_ds18b20(); 
   set_tris_b(0x3c);
   
   setup_timer_1(t1_internal | t1_div_by_8);
   set_timer1(3036);
   enable_interrupts(global); 
   enable_interrupts(int_timer1); 
   
   stepmotor_delay=5;
   stepmotor_onoff=1;   //de khoi canh bao 
   so_buoc = 0;
   giatri_mod=0;
   
   lcd_command(lcd_addr_line1);
   lcd_data("clock:"); 
   
   doc_thoi_gian_tu_realtime(); 
   if (ma_ds13!=ma_ds)
   {
      thiet_lap_thoi_gian_hien_tai(); 
      nap_thoi_gian_htai_vao_ds13b07();
   }
   hien_thi_gia_tri_mod ( );
   
   doc_thoi_gian_tu_realtime(); 
   
   while(true)
   {
      if(touch_present()) 
      {
         doc_giatri_ds18b20();
      }
      
      motor_step_run_fs();
      so_buoc++;
      delay_ms(stepmotor_delay);
      phim_inv();
      
      doc_thoi_gian_tu_realtime();
      hien_thi_gia_tri_mod ( );
      giai_ma_hien_thi ();
      giai_ma_gan_cho_8led_quet();
      hien_thi_8led_7doan_quet(); 
      if    (bdn<5) 
      {
         ht_ds13b07();
         phim_mod(); 
         phim_up();  
         phim_dw();
         hien_thi_8led_7doan_quet(); 
      }
      else if (bdn < 10)
      {
         nhap_nhay_con_tro();
         hien_thi_8led_7doan_quet(); 
      }
      else
      {
         bdn = bdn - 10;
         ht_ds13b07();
         hien_thi_8led_7doan_quet(); 
      }     

   } 
}
