//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_32led_don.c>
signed ttct = 1;
unsigned int8 t0_tam, t0;
unsigned int8 donvi, chuc, tram;

void  giai_ma_hien_thi (unsigned int16 tam)
{
   donvi = ma7doan[tam %10];
   chuc  = ma7doan[tam/10%10]; 
   tram  = ma7doan[tam/100];
   if (tram==0xc0)
   {
      tram=0xff;
      if (chuc==0xc0)   chuc=0xff;
   }
   xuat_4led_7doan_3so(tram,chuc,donvi);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void phim_up()
{
   if (!input(BT1) && (ttct < 7))
   {
      delay_ms(10);
      if (!input(BT1))
      {
         ttct++;
         while (!input(BT1));
      }
   }
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void phim_dw()
{
   if (!input(BT2) && (ttct > 1))
   {
      delay_ms(10);
      if (!input(BT2))
      {
         ttct--;
         while (!input(BT2));
      }
   }
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void phim_clr()
{
   if (!input(BT3) && (ttct > 1))
   {
      delay_ms(10);
      if (!input(BT3))
      {
         ttct = 1;
         reset_toan_bo_bien();
         set_timer0(0); 
         t0_tam = t0 = 0;
         giai_ma_hien_thi(t0);
         while (!input(BT3));
      }
   }
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   setup_timer_0 (t0_ext_l_to_h | t0_div_1| t0_8_bit); 
   set_timer0(0);
   t0_tam = t0 = 0;
   giai_ma_hien_thi(t0);
   while (true)
   {
      t0 = get_timer0();
      if (t0 != t0_tam)
      {
         t0_tam = 0;
         giai_ma_hien_thi(t0);
         if (t0 >= 10) set_timer0(1);
      }
      if (ttct == 1) sang_tat_32led(10,0);
      if (ttct == 2) sang_tat_dan_pst_32led(10,0);
      if (ttct == 3) sang_tat_dan_tsp_32led(10,0);
      if (ttct == 4) sang_tat_dan_ngoai_vao_32led(10,0);
      if (ttct == 5) sang_tat_dan_trong_ra_32led(10,0);
      if (ttct == 6) sang_don_pst_32led(10,0);
      if (ttct == 7) sang_don_tsp_32led(10,0);
      phim_dw();
      phim_up();
      phim_clr();
   }
}
