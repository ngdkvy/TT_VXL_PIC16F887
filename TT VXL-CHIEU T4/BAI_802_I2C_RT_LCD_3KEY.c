#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_ds1307_i2c.c>

unsigned int16 k;
unsigned  char    giatri_mod;

void giai_ma_gan_cho_8led_quet()
{
      led_7dq[0] = ma7doan [giay_ds13%16];
      led_7dq[1] = ma7doan [giay_ds13/16];
      led_7dq[3] = ma7doan [phut_ds13%16];
      led_7dq[4] = ma7doan [phut_ds13/16];
      led_7dq[6] = ma7doan [gio_ds13%16];
      led_7dq[7] = ma7doan [gio_ds13/16];
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
         hien_thi_gia_tri_mod( );
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
   hien_thi_thoi_gian_ds13b07 ( );
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
            case 1:  if (giay_ds13==0) giay_ds13=0x59;
                     else
                     {
                        giay_ds13--;
                        giay_ds13=hieu_chinh_so_bcd_giam(giay_ds13);
                     }
                        luu_giai_ma_hien_thi_sau_khi_chinh();
                     break;
            
            case 2: if (phut_ds13==0) phut_ds13=0x59;
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
            
            default: break;
         }
         while(!input(BT2));
      }
   } 
}

void main() 
{
   set_up_port_ic_chot(); 
   setup_lcd();
   lcd_command(lcd_addr_line1);
   lcd_data("clock:"); 
   doc_thoi_gian_tu_realtime(); 
   if (ma_ds13!=ma_ds)
   {
      thiet_lap_thoi_gian_hien_tai(); 
      nap_thoi_gian_htai_vao_ds13b07();
   }
   giatri_mod=0; 
   hien_thi_gia_tri_mod ( );
   
   doc_thoi_gian_tu_realtime(); 
   giaytam=giay_ds13;
   
   while(true)
   {
      doc_thoi_gian_tu_realtime();
      hien_thi_gia_tri_mod ( );
      hien_thi_thoi_gian_ds13b07 ( );
      phim_mod();
      phim_up();
      phim_dw();
      giai_ma_gan_cho_8led_quet();
      hien_thi_8led_7doan_quet();
   }
}
