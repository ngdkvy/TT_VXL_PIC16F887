#include <tv_pickit2_shift_1.c>
signed int8       phut, giay, bdn;

#int_timer1
void interrupt_timer1()
{
    bdn++;
    set_timer1(3036);
} 
void giai_ma_gan_cho_8led_quet()
{
    led_7dq[0] = ma7doan [giay %10];
    led_7dq[1] = ma7doan [giay/10];
    led_7dq[2] = ma7doan [phut %10];
    led_7dq[3] = ma7doan [phut/10];
}
void main()
{
    set_up_port_ic_chot();
    setup_timer_1(t1_internal | t1_div_by_8);
    set_timer1(3036);
    enable_interrupts(global); 
    enable_interrupts(int_timer1); 
    giay = 0; phut = 0;
    bdn=0;
    while(true)
    {
        giai_ma_gan_cho_8led_quet();
        if    (bdn<10)    hien_thi_8led_7doan_quet(); 
        else
        {
            bdn = bdn-10;
            giay++;
            if (giay==60)    
            {
               giay = 0;
               phut++;
               if (phut == 60)
                  phut = 0;
            }
        }
    }
}
