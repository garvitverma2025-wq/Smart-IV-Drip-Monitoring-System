#include <reg52.h>

sbit LCD_RS = P1^0;
sbit LCD_EN = P1^1;
sbit IR_SENSOR = P2^0;
sbit TRIG = P3^6;
sbit ECHO = P3^7;

unsigned int total_drops, window_drops;
unsigned int distance, level, rate;

void delay_us(unsigned int us)
{
    while(us--) { ; }
}

void delay_ms(unsigned int ms)
{
    unsigned int i;
    while(ms--)
        for(i = 0; i < 120; i++);
}

void lcd_pulse(void)
{
    LCD_EN = 1;
    delay_us(10);
    LCD_EN = 0;
}

void lcd_cmd(unsigned char cmd)
{
    LCD_RS = 0;
    P1 = (P1 & 0x0F) | (cmd & 0xF0);
    lcd_pulse();
    P1 = (P1 & 0x0F) | ((cmd << 4) & 0xF0);
    lcd_pulse();
    delay_ms(2);
}

void lcd_data(unsigned char dat)
{
    LCD_RS = 1;
    P1 = (P1 & 0x0F) | (dat & 0xF0);
    lcd_pulse();
    P1 = (P1 & 0x0F) | ((dat << 4) & 0xF0);
    lcd_pulse();
    delay_ms(2);
}

void lcd_string(char *s)
{
    while(*s) lcd_data(*s++);
}

void lcd_init(void)
{
    delay_ms(20);
    lcd_cmd(0x02);
    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
    delay_ms(5);
}

unsigned int get_distance(void)
{
    unsigned int timeout;
    unsigned long counts;

    TRIG = 0;
    delay_us(5);
    TRIG = 1;
    delay_us(10);
    TRIG = 0;

    timeout = 0;
    while(ECHO == 0)
    {
        if(++timeout > 30000) return 999;
    }

    TMOD = (TMOD & 0xF0) | 0x01;
    TH0 = 0; TL0 = 0; TF0 = 0; TR0 = 1;

    while(ECHO == 1)
    {
        if(TF0 == 1)
        {
            TR0 = 0; TF0 = 0;
            return 999;
        }
    }

    TR0 = 0;
    counts = ((unsigned long)TH0 << 8) | TL0;
    return (unsigned int)(counts / 53);
}

unsigned int calculate_level(unsigned int d)
{
    unsigned long value;

    /* Reference points: full = 1.5 cm, empty = 14 cm.
       Whole-centimetre readings make this an approximation. */
    if(d <= 1) return 100;
    if(d >= 14) return 0;

    value = ((14UL - d) * 100UL) / 12UL;
    if(value > 100) value = 100;
    return (unsigned int)value;
}

void display_rate(unsigned int r)
{
    lcd_cmd(0x80);
    lcd_string("RATE: ");

    if(r >= 100) lcd_data((r / 100) + '0');
    else lcd_data(' ');

    if(r >= 10) lcd_data(((r / 10) % 10) + '0');
    else lcd_data(' ');

    lcd_data((r % 10) + '0');
    lcd_string("/min   ");
}

void display_level(unsigned int l)
{
    lcd_cmd(0xC0);
    lcd_string("LEVEL: ");

    if(l >= 100)
    {
        lcd_data('1'); lcd_data('0'); lcd_data('0');
    }
    else
    {
        lcd_data((l / 10) + '0');
        lcd_data((l % 10) + '0');
        lcd_data(' ');
    }
    lcd_string("%     ");
}

void main(void)
{
    unsigned char previous_state, current_state;
    unsigned int i, ultrasonic_timer;

    total_drops = 0;
    window_drops = 0;
    distance = 999;
    level = 0;
    rate = 0;
    ultrasonic_timer = 0;
    TRIG = 0;

    lcd_init();
    lcd_cmd(0x80);
    lcd_string("IV DRIP MONITOR");
    lcd_cmd(0xC0);
    lcd_string("SYSTEM READY");
    delay_ms(1500);

    previous_state = IR_SENSOR;

    while(1)
    {
        window_drops = 0;
        ultrasonic_timer = 0;

        /* Approximately 8-second measurement window */
        for(i = 0; i < 800; i++)
        {
            current_state = IR_SENSOR;

            if(previous_state == 1 && current_state == 0)
            {
                total_drops++;
                window_drops++;
                delay_ms(20);
            }
            previous_state = current_state;

            /* Refresh distance periodically */
            ultrasonic_timer++;
            if(ultrasonic_timer >= 50)
            {
                ultrasonic_timer = 0;
                distance = get_distance();

                if(distance != 999)
                {
                    level = calculate_level(distance);
                    display_level(level);
                }
                else
                {
                    lcd_cmd(0xC0);
                    lcd_string("LEVEL: NO ECHO ");
                }
            }
            delay_ms(10);
        }

        rate = (window_drops * 60) / 8;
        display_rate(rate);
        delay_ms(200);
    }
}
