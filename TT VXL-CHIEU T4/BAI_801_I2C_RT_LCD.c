#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_ds1307_i2c.c>

unsigned int8 donvi, chuc, tram, ngan;

void  giai_ma_hien_thi ()
{
   donvi = ma7doan[giay_ds13%16 ];
   chuc  = ma7doan[giay_ds13/16]; 
   
   tram  = ma7doan[phut_ds13%16];
   ngan  = ma7doan[phut_ds13/16]; 
   if (chuc==0xc0)   chuc=0xff;
   xuat_4led_7doan_4so(ngan, tram&0x7f, chuc,donvi);
}

void giai_ma_gan_cho_8led_quet()
{
      led_7dq[0] = ma7doan [giay_ds13%16];
      led_7dq[1] = ma7doan [giay_ds13/16];
      led_7dq[3] = ma7doan [phut_ds13%16];
      led_7dq[4] = ma7doan [phut_ds13/16];
      led_7dq[6] = ma7doan [gio_ds13%16];
      led_7dq[7] = ma7doan [gio_ds13/16];
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
   //thiet_lap_thoi_gian_hien_tai();
   //nap_thoi_gian_htai_vao_ds1307();
   doc_thoi_gian_tu_realtime();  
   while(true)
   {
      doc_thoi_gian_tu_realtime();
      hien_thi_thoi_gian_ds13b07 ( );
      giai_ma_hien_thi ();
      giai_ma_gan_cho_8led_quet();
      hien_thi_8led_7doan_quet();
   }
}
