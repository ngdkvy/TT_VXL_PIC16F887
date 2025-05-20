#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_ds1307_i2c.c>
unsigned  char    giatri_mod;
signed int8  giay, bdn;
unsigned  char gio_caidat, phut_caidat, giay_caidat;

#int_timer1
void interrupt_timer1()
{
    bdn++;
    set_timer1(3036);
} 

void HT_DS13B07 ( )
{     
      LCD_COMMAND (0x8C);
      LCD_DATA(GIO_DS13/16  +0X30);    LCD_DATA(GIO_DS13%16  +0X30);
      LCD_DATA(' ');
      LCD_DATA(PHUT_DS13/16 +0X30);    LCD_DATA(PHUT_DS13%16 +0X30);
      LCD_DATA(' ');
      LCD_DATA(GIAY_DS13/16 +0X30);    LCD_DATA(GIAY_DS13%16 +0X30);
      LCD_COMMAND (0xC9);
      if (thu_ds13 == 1)
      {
            LCD_DATA("CN");
      }
      if ((thu_ds13>=2) && (thu_ds13<=7))
      {
         LCD_DATA(' ');
         LCD_DATA(THU_DS13 + 0X30);
      }
      LCD_COMMAND (0xCB);
      LCD_DATA(' ');
      LCD_DATA(NGAY_DS13/16 +0X30);    LCD_DATA(NGAY_DS13%16 +0X30);
      LCD_DATA(' ');
      LCD_DATA(THANG_DS13/16 +0X30);   LCD_DATA(THANG_DS13%16 +0X30);
      LCD_DATA(' ');
      LCD_DATA(NAM_DS13/16 +0X30);     LCD_DATA(NAM_DS13%16 +0X30);
      LCD_COMMAND (0xa0);
      LCD_DATA(gio_caidat/16 +0X30);    LCD_DATA(gio_caidat%16 +0X30);
      LCD_DATA(' ');
      LCD_DATA(phut_caidat/16 +0X30);   LCD_DATA(phut_caidat%16 +0X30);
      LCD_DATA(' ');
      LCD_DATA(giay_caidat/16 +0X30);     LCD_DATA(giay_caidat%16 +0X30);
}

void hien_thi_gia_tri_mod ( ) 
{
   lcd_command(0x8a); 
   lcd_data(giatri_mod+0x30);
}

void phim_mod() 
{
   if (!input(BT0)) 
   {
      delay_ms(20);
      if (!input(BT0))
      {
         if(giatri_mod<3)  giatri_mod++;
         else              giatri_mod=0;
         hien_thi_gia_tri_mod ( );
         while(!input(BT0));
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
   if (!input(BT1)) 
   {
      delay_ms(20);
      if (!input(BT1))
      {
         switch (giatri_mod)
         {
            case 1:  if (giay_caidat == 0x59) giay_caidat=0;
                     else
                     {
                        giay_caidat++;
                        giay_caidat=hieu_chinh_so_bcd_tang(giay_caidat);
                     }
                     break;
            
            case 2:  if (phut_caidat == 0x59) phut_caidat = 0;
                     else
                     {
                        phut_caidat++;
                        phut_caidat=hieu_chinh_so_bcd_tang(phut_caidat);
                     }

                     break;
            
            case 3:  if (gio_caidat == 0x23) gio_caidat=0;
                     else
                     {
                        gio_caidat++;
                        gio_caidat=hieu_chinh_so_bcd_tang(gio_caidat);
                     }
                     break;
            default: break;
         }
         while(!input(BT1));
      }
   }
}

void phim_dw() 
{
   if (!input(BT2)) 
   {
      delay_ms(20);
      if (!input(BT2))
      {
         switch (giatri_mod)
         {
            case 1:  if (giay_caidat == 0) giay_caidat = 0x59;
                     else
                     {
                        giay_caidat--;
                        giay_caidat=hieu_chinh_so_bcd_giam(giay_caidat);
                     }
                     break;
            
            case 2:  if (phut_caidat == 0) phut_caidat=0x59;
                     else
                     {
                        phut_caidat--;
                        phut_caidat=hieu_chinh_so_bcd_giam(phut_caidat);
                     }
                     break;
            
            case 3:  if (gio_caidat == 0) gio_caidat = 0x23;
                     else
                     {
                        gio_caidat--;
                        gio_caidat=hieu_chinh_so_bcd_giam(gio_caidat);
                     }
                     break;
            
            default: break;
         }
         while(!input(BT2));
      }
   }
} 

void nhap_nhay_con_tro() 
{
   switch (giatri_mod) 
   {
      case 1:  lcd_command(0xa6);
               lcd_data("  ");
               break;
      case 2:  lcd_command(0xa3);
               lcd_data("  ");
               break;
      case 3:  lcd_command(0xa0);
               lcd_data("  ");
               break;
      default: break;
   }
}


void main() 
{
   set_up_port_ic_chot();
   
   setup_timer_1(t1_internal | t1_div_by_8);
   set_timer1(3036);
   enable_interrupts(global); 
   enable_interrupts(int_timer1); 
   
   setup_lcd();
   lcd_command(lcd_addr_line1);
   lcd_data("clock:"); 
   doc_thoi_gian_tu_realtime(); 
   if (ma_ds13!=ma_ds)
   {
      thiet_lap_thoi_gian_hien_tai(); 
      nap_thoi_gian_htai_vao_ds13b07();
   }
   giatri_mod=giay_caidat=phut_caidat=gio_caidat=0; 
   hien_thi_gia_tri_mod ( );
   
   doc_thoi_gian_tu_realtime(); 
   giay = 0;
   while(true)
   {
      doc_thoi_gian_tu_realtime();
      hien_thi_gia_tri_mod ( );
      if    (bdn<5) 
      {
         HT_DS13B07 ( );
         phim_mod(); 
         phim_up();  
         phim_dw();
      }
      else if (bdn < 10)
         nhap_nhay_con_tro();
      else
      {
         bdn = bdn - 10;
         if (giay != 0)
            giay --;
      }
      if  ((gio_caidat == gio_ds13) &&(phut_caidat == phut_ds13) && (giay_caidat == giay_ds13))
      {
         giay = 5;
         xuat_32led_don_2word(0,0xff);
      }
      if (giay == 0)
         xuat_32led_don_2word(0,0);
   } 
}
