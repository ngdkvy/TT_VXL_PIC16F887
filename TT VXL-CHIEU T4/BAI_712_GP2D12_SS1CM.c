#include <tv_pickit2_shift_1.c>

unsigned int8     j, solan_kcach=20; 
unsigned int16    kqadc, kcach, chenh_lenh_kcach;
unsigned int8     dv, ch;

void  giai_ma_hien_thi ()
{
   dv = ma7doan[kcach%10];
   ch  = ma7doan[kcach/10]; 
   xuat_4led_7doan_2so(ch, dv);
}

void doc_kc() 
{
   set_adc_channel(2); 
   kqadc = 0;
   for (j=0; j<solan_kcach; j++) 
   {
      kqadc = kqadc + read_adc(); 
      delay_us(10);
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
   setup_adc(adc_clock_div_32); 
   setup_adc_ports(an0_to_an2|vss_vdd );
   while (true)
   {
      doc_kc();
      giai_ma_hien_thi ();
   }
}
   
