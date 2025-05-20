//!BT TONG HOP: 
//!1. Do nhiet do bang LM35A, LM35B, cam bien DS1820 hien thi len 8 LED quet, co xu ly so thap phan. 
//!   DS1820   LM35A   LM35B
//!   XX.X   YY.Y   ZZ
//!- Phim 7: tang nhiet do bao hieu
//!- Phim 8: giam nhiet do bao hieu
//!- Khi nhiet do LM35B > nhiet do bao hieu, tat den va bat 8 LED ben trai. 
//!- Khi nhiet do LM35B < nhiet do bao hieu - 2, tat 8 LED ben trai. 
//!- Khi nhiet do LM35B < nhiet do bao hieu - 5, bat den. 
//!2. Dem counter, co cai dat gia tri cai. Hien thi len LCD hang 1
//!- Phim A: reset gia tri counter ve 0, gia tri cai 99
//!- Phim B: Start/Stop counter
//!- Phim C tang gia tri cai
//!- Phim D: giam gia tri cai
//!- Phim E: dao chieu dem
//!3. Real time co chinh thoi gian va gia tri cai dat canh bao.
//!- Phim 0: chon che do chinh ngay gio real time (0 -> 10)
//!   + Che do 0: khong chinh
//!   + Che do 1, 2, 3: chinh giay, phut, gio hien tai
//!   + Che do 4, 5, 6, 7: chinh ngay, thang, nam, thu
//!   + Che 8, 9, 10: chinh giay, phut, gio bao hieu
//!- Phim 1: tang gia tri 
//!- Phim 2: giam gia tri
//!- Khi gio, phut, giay bao hieu trung voi gio, phut, giay hien tai thi 8 LED ben phai sang 5s sau do tat.
//!- Khi gia tri mod khac 0, se nhap nhay so o vi tri tuong ung voi che do chinh
//!- Hang 0: che do chinh, gio, phut, giay hien tai
//!- Hang 1: thu, ngay, thang, nam hien tai
//!- Hang 2: gio, phut, giay cai dat bao hieu
//!4. Dong co buoc. Dong co co 9 cap do, cap 0 dong co khong quay. So buoc hien thi len 3 LED phai module 4 led 7 doan, 
//!led trai hien thi cap do
//!   Cap do   So buoc
//!   A.   BBB
//!- Phim 3: dao chieu dong co buoc
//!- Phim 4: tang cap do (toc do) dong co
//!- Phim 5: giam cap do (toc do) dong co
//!- Phim 6: dong co ngung
//!5. Font to: hien thi phut giay do bang DS1307 o hang 2, 3 goc trai
//!- Phim F: dao chieu hien thi
//!6. Do khoang cach. Hien thi len LCD
//!7. Dem giay bang timer1 co su dung xu ly ngat
//!8. Hien thi phim duoc nhan len LCD

#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_ds18b20.c> 
#include <tv_pickit2_shift_key4x4_138.c> 
#include <tv_pickit2_shift_ds1307_i2c.c> // trong thu vien nay da goi thu vien cho LCD
#include <tv_pickit2_shift_step_motor.c>

unsigned int8     j, solan_lm35 = 100, solan_kcach = 20; 
float             lm35a;
unsigned int16    lm35b;
int16             kq_ht_lm35a;
signed int8       giay_canhbao, giay, bdn;
unsigned int8     t0_max, t0;
unsigned int8     nd_max;
signed int8       mp;
unsigned int8     donvi_counter, chuc_counter, donvi_cai, chuc_cai;
unsigned int8     donvi_giay_to, chuc_giay_to, donvi_phut_to, chuc_phut_to;
unsigned int8     donvi_giay, chuc_giay;
unsigned int8     donvi_nd_max, chuc_nd_max;
unsigned int8     donvi_kcach, chuc_kcach;
unsigned int16    kqadc, kcach, chenh_lenh_kcach;
unsigned  char    giatri_mod;
unsigned  char    gio_caidat, phut_caidat, giay_caidat;
signed int8       i;
unsigned int16    so_buoc;
unsigned int16    donvi_motor, chuc_motor, tram_motor, capdo_motor;
unsigned int8     capdo;
int1              TT_SP, TT_HT, TT_DC, TT_DG;

//!Chuong trinh ngat cho timer1
#int_timer1
void interrupt_timer1()
{
    bdn++;
    set_timer1(3036);
} 

//!Module 8 led 7 doan quet: DS1820, LM35A, LM35B. Co xu ly phan thap phan cho DS1820 va LM35A
void giai_ma_gan_cho_8led_quet()
{
      //!   Luu ket qua do duoc tu LM35A de hien thi ra LED 
      led_7dq[2] = ma7doan[kq_ht_lm35a %10];
      led_7dq[3] = ma7doan[kq_ht_lm35a/10%10] & 0x7F; 
      led_7dq[4] = ma7doan[kq_ht_lm35a/100];
      
      //!   Luu ket qua do duoc tu LM35B de hien thi ra LED 
      led_7dq[0] = ma7doan[lm35b %10];
      led_7dq[1] = ma7doan[lm35b/10]; 
      
      //!   Luu ket qua do duoc tu DS1820 de hien thi ra LED 
      //!   Muon lay bao nhieu so thap phan thi chinh sua trong thu vien,sau do xu ly luu so, o day in ra 1 so thap phan
      led_7dq[5] = ma7doan [tp];
      led_7dq[6] = ma7doan [nguyen % 10]& 0x7F;
      led_7dq[7] = ma7doan [nguyen / 10];
 
//!      xoa so 0 vo nghia
//!if (led_7dq[7] == 0xc0) led_7dq[7] = 0xff;
}

//!Module 4 led 7 doan: In ra cap do va so buoc cua motor
void  giai_ma_hien_thi ()
{
//!   Luu so de hien thi ra LED 
   donvi_motor = ma7doan[so_buoc%10];
   chuc_motor  = ma7doan[so_buoc/10%10]; 
   tram_motor  = ma7doan[so_buoc/100%10]; 
   capdo_motor  = ma7doan[capdo]; 
   
//!   Xoa so 0 vo nghia
   if (tram_motor == 0xc0)   
      {
         tram_motor = 0xff;
         if (chuc_motor == 0xc0)   
            chuc_motor = 0xff;
      }
   xuat_4led_7doan_4so(capdo_motor&0x7f, tram_motor, chuc_motor, donvi_motor);
}

//!Bat, tat den de tang giam nhiet do cua LM35. LED don de bao hieu qua nhiet
void so_sanh_dk_den() 
{
   if (lm35b > nd_max) 
   {
      triac_2_off(); //Tat den
      xuat_32led_don_2word(0xff,0);
   }
   else if (lm35b < (nd_max-2))
   {
      xuat_32led_don_2word(0,0);
   }
   if (lm35a < (nd_max - 5)) 
      triac_2_on(); //Bat den
}

//!Do nhiet do LM35A o kenh 0
void doc_nd_lm35a() 
{
   set_adc_channel(0); 
   lm35a = 0;
   delay_ms(1);
   for (j=0; j<solan_lm35; j++) 
   {
      lm35a = lm35a + read_adc(); 
      hien_thi_8led_7doan_quet(); 
//!   cau lenh phia tren neu khong co LED quet, thay bang lenh 
//!   delay_us(10);
   }
   lm35a = lm35a /2.046; 
   lm35a = lm35a /solan_lm35;
   
//!   lenh de lay so thap phan
//!   neu khong yeu cau xu ly so thap phan thi bo dong nay, chinh lai khai bao bien lm35a la unsigned int8
   kq_ht_lm35a = (int16) (lm35a*10); 

}

//!Do nhiet do LM35B o kenh 1
void doc_nd_lm35b() 
{
   set_adc_channel(1); 
   delay_ms(1);
   lm35b = 0;
   for (j=0; j<solan_lm35; j++) 
   {
      lm35b = lm35b + read_adc(); 
      hien_thi_8led_7doan_quet();
//!   cau lenh phia tren neu khong co LED quet, thay bang lenh 
//!   delay_us(10);
   }
   lm35b = lm35b /2.046; 
   lm35b = lm35b /solan_lm35;
}

//!Do khoang cach bang cam bien GP2D12 o kenh 2
void doc_kc() 
{
   set_adc_channel(2); 
   kqadc = 0;
   for (j=0; j<solan_kcach; j++) 
   {
      kqadc = kqadc + read_adc(); 
      hien_thi_8led_7doan_quet(); 
//!   cau lenh phia tren neu khong co LED quet, thay bang lenh 
//!   delay_us(10);
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

//!Chuong trinh con hien thi so to ra LCD
void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
   lcd_goto_xy(x1,y1); 
   for (i=0;i<6;i++)
   {
      if (i==3)   lcd_goto_xy(x1+1,y1); 
      lcd_data(lcd_so_x[lcd_so][i]);
   }
}

//!Xoa so 0 vo nghia cua font to
//!O day xu ly cho bien giay_ds13, phut_ds13
//!Muon xu ly cho bien khac thi thay ten bien can xu ly cho phu hop
void xu_ly_so_to_xoa_0_vo_nghia()
{
   chuc_giay_to  = giay_ds13/10;
   donvi_giay_to = giay_ds13%10;
   //!Tai mang lcd_so_x[10][i] la mang trang nen gan chuc_giay_to = 10 de cho so 0 vo nghia thanh mang trang
   if (chuc_giay_to == 0) chuc_giay_to = 10;
   
   chuc_phut_to  = phut_ds13/10;
   donvi_phut_to = phut_ds13%10;
   //!Tai mang lcd_so_x[10][i] la mang trang nen gan chuc_phut_to = 10 de cho so 0 vo nghia thanh mang trang
   if (chuc_phut_to == 0) chuc_phut_to = 10;
}

//!Module LCD, counter dem san pham: In ra gia tri dem va gia tri cai cua Counter
void hienthi_lcd_counter()
{
//!   Luu so de hien thi ra LCD 
//!   Hien thi gia tri dem  
   donvi_counter = t0%10+0x30;
   chuc_counter  = t0/10+0x30; 
   
//!   Xoa so 0 vo nghia
   if (chuc_counter==0x30)   chuc_counter=0x20;
   
//!   In gia tri dem da xu ly ra LCD
   lcd_goto_xy(1,0);
   lcd_data(chuc_counter); 
   lcd_data(donvi_counter);
   
//!   Luu so de hien thi ra LCD 
//!   Hien thi gia tri cai
   donvi_cai = t0_max%10+0x30;
   chuc_cai  = t0_max/10+0x30; 
   
//!   Xoa so 0 vo nghia
   if (chuc_cai==0x30)   chuc_cai=0x20;
   
//!   In gia tri cai da xu ly ra LCD
   lcd_goto_xy(1,3);
   lcd_data(chuc_cai); 
   lcd_data(donvi_cai);
}

//!Module LCD, Real time bang cam bien DS1307: in ra giay, phut, gio, thu, ngay, thang, nam
void hienthi_lcd_ds13b07 ( )
{     
//!   In gio, phut, giay hien tai o hang 0
      lcd_command (0x8c);
      lcd_data(gio_ds13/16  +0x30);    lcd_data(gio_ds13%16  +0x30);
      lcd_data(' ');
      lcd_data(phut_ds13/16 +0x30);    lcd_data(phut_ds13%16 +0x30);
      lcd_data(' ');
      lcd_data(giay_ds13/16 +0x30);    lcd_data(giay_ds13%16 +0x30);
      
//!   Xu ly va in thu hien tai o hang 1
      lcd_command (0xc9);
      if (thu_ds13 != 1)
      {
         lcd_data(' ');
         lcd_data(thu_ds13 + 0x30);
      }
      else 
         lcd_data("CN");
         
//!   In ngay, thang, nam hien tai o hang 1
      lcd_command (0xcb);
      lcd_data(' ');
      lcd_data(ngay_ds13/16 +0x30);    lcd_data(ngay_ds13%16 +0x30);
      lcd_data(' ');
      lcd_data(thang_ds13/16 +0x30);   lcd_data(thang_ds13%16 +0x30);
      lcd_data(' ');
      lcd_data(nam_ds13/16 +0x30);     lcd_data(nam_ds13%16 +0x30);
      
//!   In ngay, thang, nam cai dat de bao hieu o hang 2
      lcd_command (0xa0);
      lcd_data(gio_caidat/16 +0x30);    lcd_data(gio_caidat%16 +0x30);
      lcd_data(' ');
      lcd_data(phut_caidat/16 +0x30);   lcd_data(phut_caidat%16 +0x30);
      lcd_data(' ');
      lcd_data(giay_caidat/16 +0x30);     lcd_data(giay_caidat%16 +0x30);
}

//!Module LCD, cam bien GP2D12: In ra khoang cach do duoc
void hienthi_lcd_kcach()
{
//!   Luu so de hien thi ra LCD 
//!   Hien thi khoang cach do duoc
   donvi_kcach    = kcach%10+0x30;
   chuc_kcach     = kcach/10+0x30;
   
//!   Xoa so 0 vo nghia
   if (chuc_kcach == 0x30)   chuc_kcach   = 0x20;
   
//!   In khoang cach do duoc da xu ly ra LCD
   lcd_goto_xy(3,15);
   lcd_data(chuc_kcach); 
   lcd_data(donvi_kcach); 
}

//!Module LCD, timer1: In ra giay dem duoc
void hienthi_lcd_demgiay()
{
//!   Luu so de hien thi ra LCD 
//!   Hien thi giay dem duoc
   donvi_giay    = giay%10+0x30;
   chuc_giay     = giay/10+0x30;
   
//!   Xoa so 0 vo nghia
   if (chuc_giay == 0x30)   chuc_giay   = 0x20;
   
//!   In giay da xu ly ra LCD
   lcd_goto_xy(3,18);
   lcd_data(chuc_giay); 
   lcd_data(donvi_giay); 
}

//!Module LCD: In nhiet do canh bao
void hienthi_lcd_nhietdocanhbao()
{
//!   Luu so de hien thi ra LCD 
//!   Hien thi nhiet do canh bao
   donvi_nd_max    = nd_max%10+0x30;
   chuc_nd_max     = nd_max/10+0x30;
   
//!   Xoa so 0 vo nghia
   if (chuc_nd_max == 0x30)   chuc_nd_max   = 0x20;
   
//!   In nhiet do canh bao da xu ly ra LCD
   lcd_goto_xy(3,12);
   lcd_data(chuc_nd_max); 
   lcd_data(donvi_nd_max); 
}

//!Module LCD, ma tran phim: In phim duoc nhan
void hienthi_lcd_phim_nhan()
{
//!Di chuyen con tro LCD toi vi tri in ra man hinh
   lcd_goto_xy(1,6);  
   
//!   Hien thi LCD phim duoc nhan 0 -> 9
   if (mp < 10)
      lcd_data(mp+0x30); 
   else
//!   Hien thi LCD phim duoc nhan A -> F 
      lcd_data(mp+0x37);
}

//!Module LCD: In so the hien che do dieu chinh thoi gian hien tai va thoi gian bao hieu
void hien_thi_gia_tri_mod ( ) 
{
   lcd_command(0x89); 
   lcd_data(giatri_mod/10+0x30);
   lcd_data(giatri_mod%10+0x30);
}

//!Cam bien DS13B07
unsigned  int8 hieu_chinh_so_bcd_tang(unsigned  int8 x ) 
{
    unsigned  int8 y; 
    y = x;
    x = x & 0x0f;
    if  (x==0x0a)   y = y + 6; 
    return(y);
}

//!Cam bien DS13B07
unsigned  int8 hieu_chinh_so_bcd_giam(unsigned  int8 x ) 
{
    unsigned  int8 y; 
    y = x;
    x = x & 0x0f;
    if  (x==0x0f)   y = y - 6; 
    return(y);
}

//!Luu lai gia tri vao bo nho cua cam bien DS13B07 khi thuc hien dieu chinh va hien thi len LCD
void luu_giai_ma_hien_thi_sau_khi_chinh() 
{
   nap_thoi_gian_htai_vao_ds13b07(); 
   hienthi_lcd_ds13b07 ( );
} 

//!Module LCD: chen ky tu trang vao so dang trong che do dieu chinh de tao su nhap nhay so
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
      case 8: lcd_command(0xa6);
              lcd_data("  ");
              break;     
      case 9: lcd_command(0xa3);
              lcd_data("  ");
              break;
      case 10:lcd_command(0xa0);
              lcd_data("  ");
              break;
      default: break;
   }
}

//!Chuong trinh de xu ly cac chuc nang cua ma tran phim
void xu_ly_ma_tran_phim()
{
   if (mp == 0)
   {
      if (giatri_mod<10)  giatri_mod++;
      else                giatri_mod=0;
      hien_thi_gia_tri_mod ( );
   }
   if (mp == 1)
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
         case 8:  if (giay_caidat == 0x59) giay_caidat = 0;
                  else
                  {
                     giay_caidat++;
                     giay_caidat=hieu_chinh_so_bcd_tang(giay_caidat);
                  }
                  break;
         
         case 9:  if (phut_caidat == 0x59) phut_caidat = 0;
                  else
                  {
                     phut_caidat++;
                     phut_caidat=hieu_chinh_so_bcd_tang(phut_caidat);
                  }

                  break;
         
         case 10:  if (gio_caidat == 0x23) gio_caidat=0;
                  else
                  {
                     gio_caidat++;
                     gio_caidat=hieu_chinh_so_bcd_tang(gio_caidat);
                  }
                  break;
         default: break;
      }
   }
   if (mp == 2)
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
            case 8:  if (giay_caidat == 0) giay_caidat = 0x59;
                     else
                     {
                        giay_caidat--;
                        giay_caidat=hieu_chinh_so_bcd_giam(giay_caidat);
                     }
                     break;
            
            case 9:  if (phut_caidat == 0) phut_caidat=0x59;
                     else
                     {
                        phut_caidat--;
                        phut_caidat=hieu_chinh_so_bcd_giam(phut_caidat);
                     }
                     break;
            
            case 10:  if (gio_caidat == 0) gio_caidat = 0x23;
                     else
                     {
                        gio_caidat--;
                        gio_caidat=hieu_chinh_so_bcd_giam(gio_caidat);
                     }
                     break;
            default: break;
         }
   }
   if (mp == 3)
   {
      stepmotor_tn=~stepmotor_tn;    
      so_buoc = 0;
      giai_ma_hien_thi ();
   }
   if ((mp == 4) && ( capdo < 9))
   {
      capdo++;   
      stepmotor_delay-=5;
   }
   if ((mp == 5) && (capdo > 0))
   {
      capdo--;    
      stepmotor_delay+=5;
   }
   if (mp == 6)
   {
      capdo = 0;
      so_buoc = 0;
   }
   if (mp == 7)  nd_max++;
   if (mp == 8)  nd_max --;
   if (mp == 9)  TT_DG = ~TT_DG;
   if (mp == 10)
   {
      t0 = 0;
      set_timer0(0);
      t0_max = 99;
   }
   if  (mp == 11)                    TT_SP = ~TT_SP;
   if ((mp == 12) && (t0_max < 99))  t0_max ++;
   if ((mp == 13) && (t0_max > 0))   t0_max --;
   if  (mp == 14)    
   {         
      if (!TT_DC)
            set_timer0(t0_max - t0);
      else 
            set_timer0(t0);
      TT_DC = ~TT_DC;
   }
   if  (mp == 15)    TT_HT = ~TT_HT;
}

void main() 
{
//!   Khoi tao ban dau + LCD + ma tran phim
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   setup_lcd();
   
//!   Cai dat bo chia, kenh va nguon dien
   setup_adc(adc_clock_div_32); 
   
//!   Neu chi dung LM35A, LM35B thi khai bao
//!      setup_adc_ports(an0_to_an1|vss_vdd );
//!   Con co them do khoang cach thi khai bao nhu o duoi
   setup_adc_ports(an0_to_an2|vss_vdd );

//!   Khoi tao cho cam bien DS18B20: real time
   khoi_tao_ds18b20(); 
   
   //!   Cai dat Timer1 + Xu ly ngat
   setup_timer_1(t1_internal | t1_div_by_8);
   set_timer1(3036);
   enable_interrupts(global); 
   enable_interrupts(int_timer1); 
   
   //!   Cai dat timer0, gia tri ban dau = 0
   setup_timer_0 (t0_ext_l_to_h | t0_div_1); 
   set_timer0(0);
   
   //!   Luu cac doan a, b, c, e, f, g+d vao CGRAM de tao font to
   lcd_command(0x40); 
   for (i=0;i<64;i++)  {  lcd_data(lcd_ma_8doan[i]); }

   lcd_command(lcd_addr_line1);
   lcd_data("clock:"); 
   
//!   Doc gia tri thoi gian tu cam bien DS18B20: real time va thiet lap lai thoi gian
   doc_thoi_gian_tu_realtime(); 
   if (ma_ds13!=ma_ds)
   {
      thiet_lap_thoi_gian_hien_tai(); 
      nap_thoi_gian_htai_vao_ds13b07();
   }
   
//!   Hien thi che do cai dat thoi gian hien tai
   giatri_mod = 0; 
   hien_thi_gia_tri_mod ( );
   
   //!   Doc gia tri thoi gian tu cam bien DS18B20
   doc_thoi_gian_tu_realtime(); 
   
   //!   Khoi tao gia tri ban dau cho counter, nhiet do bao hieu, thoi gian canh bao, cac trang thai dieu khien
   t0 = 0;
   t0_max = 35;
   nd_max = 38;
   giay_caidat = phut_caidat = gio_caidat = 0;
   TT_SP = TT_HT = TT_DC = TT_DG = 0;
   
//!   Khoi tao gia tri ban dau cho timer1
   giay = bdn = 0;
   
//!   Khoi tao gia tri ban dau dong co buoc
   stepmotor_delay=50;
   stepmotor_onoff=1;   //de khoi canh bao 
   so_buoc = 0;
   capdo = 0;
   stepmotor_tn = 1;
   
   while(true)
   {
//!      doc nhiet do do duoc tu LM35A, LM35B, so sanh nhiet do de bat, tat den; bat, tat LED don canh bao
      doc_nd_lm35a();
      doc_nd_lm35b();
      so_sanh_dk_den();
      
//!      doc khoang cach do duoc tu cam bien GP2D12 va hien thi ra LCD
      doc_kc();
      hienthi_lcd_kcach();

//!      doc thoi gian thuc tu cam bien DS13B07, hien thi gia tri thoi gian thuc va che do dieu chinh thoi gian ra LCD
      doc_thoi_gian_tu_realtime();
      hien_thi_gia_tri_mod ( );
      hienthi_lcd_ds13b07 ( );
      
//!    hien thi ra LCD giay dem duoc tu timer1
      hienthi_lcd_demgiay();

//!      Kiem ra ma tran phim co duoc nhan khong? Co thi xu ly cac chuc nang lien quan va hien thi ra LCD phim duoc nhan
      mp = key_4x4_dw(); // trong while
      if (mp != 0xff)  
      {
         xu_ly_ma_tran_phim();
         hienthi_lcd_phim_nhan();
      }
      
//!      doc nhiet do do duoc tu cam bien DS18B20
      if (touch_present()) 
         doc_giatri_ds18b20();
      
//!      Xu ly dao hien thi phut, giay hien tai
      if (!TT_HT)
      {
         lcd_hienthi_so_z_toado_xy(chuc_phut_to,  2, 0); 
         lcd_hienthi_so_z_toado_xy(donvi_phut_to, 2, 3); 
         lcd_hienthi_so_z_toado_xy(chuc_giay_to,  2, 6); 
         lcd_hienthi_so_z_toado_xy(donvi_giay_to, 2, 9); 
      }
      else
      {
         lcd_hienthi_so_z_toado_xy(chuc_giay_to,  2, 0); 
         lcd_hienthi_so_z_toado_xy(donvi_giay_to, 2, 3); 
         lcd_hienthi_so_z_toado_xy(chuc_phut_to,  2, 6); 
         lcd_hienthi_so_z_toado_xy(donvi_phut_to, 2, 9); 
      }
      
//!      Xu ly cho counter dem hoac ngung dem
      if (!TT_SP) 
         setup_timer_0(t0_off);
      else
         setup_timer_0 (t0_ext_l_to_h | t0_div_1); 
         
//!      Xu ly cho counter dem len hoac xuong, dat lai gia tri khi dat min, max. Hien thi len LCD gia tri counter dem duoc
      if (TT_DC == 0)
         t0 = get_timer0();  
      else 
         t0 = t0_max - get_timer0();
      if ((t0 > t0_max) && (!TT_DC))
         t0 = set_timer0(1);
      if ((!t0) && (TT_DC))
         set_timer0(0);
      hienthi_lcd_counter();   
      
//!  Xet chieu quay, cap do chay nhanh cham, so buoc chay duoc cua dong co buoc
      if (capdo != 0)
      {
         motor_step_run_fs();
         so_buoc++;
         delay_ms(stepmotor_delay);
      }   
      
//!  If va else if de tao xu nhap nhay khi dang trong che do dieu chinh thoi gian
      if    (bdn<5) 
      {
         hienthi_lcd_ds13b07 ( );
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
         hien_thi_8led_7doan_quet();
         if (giay_canhbao != 0)
            giay_canhbao --;
            
//!      Xu ly dao chieu dem giay
         if (!TT_DG)    giay++;
         else           giay --;
         
//!      Dat lai gia tri giay va hien thi giay len LCD
         if (giay == 60)  giay = 0;
         if (giay < 0)    giay = 59;
         hienthi_lcd_demgiay();
      }
      
//!   So sanh thoi gian hien tai va thoi gian dat truoc de bat bao hieu
      if  ((gio_caidat == gio_ds13) &&(phut_caidat == phut_ds13) && (giay_caidat == giay_ds13))
      {
         giay_canhbao = 5;
         xuat_32led_don_2word(0,0xff);
      }
      if (giay_canhbao == 0)
         xuat_32led_don_2word(0,0);
         
      giai_ma_hien_thi ();
      giai_ma_gan_cho_8led_quet();
      hien_thi_8led_7doan_quet();
      hienthi_lcd_nhietdocanhbao();
      xu_ly_so_to_xoa_0_vo_nghia();
   }
}
