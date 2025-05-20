#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_ds18b20.c>
int1  ttqn;
#define     gh_nda_tren   40
#define     gh_nda_duoi   35

void GM_LED_QUET()
{
   led_7dq[0] = ma7doan[ds18a%10];
   led_7dq[1] = ma7doan[ds18a/10];
}
void main() 
{
   set_up_port_ic_chot(); 
   khoi_tao_ds18b20();
   xuat_4led_7doan_giaima_xoa_so0(0); 
   xuat_32led_don_1dw(0);
   ttqn=0;
   while(true)
   {
      if(touch_present()) {doc_giatri_ds18b20();} 
      ds18a   =  ds18a>>4;
      ds18a   =  ds18a & 0x0ff;
      xuat_4led_7doan_giaima_xoa_so0(ds18a); 
      GM_LED_QUET();
      hien_thi_8led_7doan_quet_all();
      if ((ds18a>gh_nda_tren)&&(ttqn==0))
      {
         ttqn = 1;
         xuat_32led_don_1dw(0x0000ffff);
      }
      else if ((ds18a<gh_nda_duoi)&&(ttqn==1)) 
      {
         ttqn = 0;
         xuat_32led_don_1dw(0xffff0000);
      }
      hien_thi_8led_7doan_quet_all();
   }
}
