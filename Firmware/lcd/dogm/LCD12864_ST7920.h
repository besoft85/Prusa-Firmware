#ifndef LCD12864_ST7920_h
#define LCD12864_ST7920_h

#include "../../fastio.h"
#include "arduino.h"

#include "small5x7_font.h"

#define ST7920_CLK_PIN  LCD_PINS_D4
#define ST7920_DAT_PIN  LCD_PINS_ENABLE
#define ST7920_CS_PIN   LCD_PINS_RS

//#define LCD_WIDTH 20
//#define LCD_HEIGHT 4


// ST7920 Commands
#define LCD_CLS         0x01
#define LCD_HOME        0x02
#define LCD_ADDRINC     0x06
#define LCD_DISPLAYON   0x0C
#define LCD_DISPLAYOFF  0x08
#define LCD_CURSORON    0x0E
#define LCD_CURSORBLINK 0x0F
#define LCD_BASIC       0x30
#define LCD_NON_EXTEND  0x20
#define LCD_EXTEND      0x24
#define LCD_GFXMODE     0x26
#define LCD_TXTMODE     0x34
#define LCD_STANDBY     0x01
#define LCD_SCROLL      0x03
#define LCD_SCROLLADDR  0x40
#define LCD_ADDR        0x80
#define LCD_LINE0       0x80 //80H..8FH
#define LCD_LINE1       0x90 //90H..9FH
#define LCD_LINE2       0x88 //A0H..AFH
#define LCD_LINE3       0x98 //B0H..BFH

#define LCD_PIXEL_WIDTH 128
#define LCD_PIXEL_HEIGHT 64

#define INFO_FONT_HEIGHT 8
#define INFO_FONT_WIDTH 6

//set optimization so ARDUINO optimizes this file
#pragma GCC optimize (3)

#define CPU_ST7920_DELAY_1 DELAY_NS(0)
#define CPU_ST7920_DELAY_2 DELAY_NS(0)
#define CPU_ST7920_DELAY_3 DELAY_NS(63)


#ifndef ST7920_DELAY_1
  #define ST7920_DELAY_1 CPU_ST7920_DELAY_1
#endif
#ifndef ST7920_DELAY_2
  #define ST7920_DELAY_2 CPU_ST7920_DELAY_2
#endif
#ifndef ST7920_DELAY_3
  #define ST7920_DELAY_3 CPU_ST7920_DELAY_3
#endif

#define ST7920_SND_BIT \
  WRITE2(ST7920_CLK_PIN, LOW);        ST7920_DELAY_1; \
  WRITE2(ST7920_DAT_PIN, val & 0x80); ST7920_DELAY_2; \
  WRITE2(ST7920_CLK_PIN, HIGH);       ST7920_DELAY_3; \
  val <<= 1

static void ST7920_SWSPI_SND_8BIT(uint8_t val) {
  ST7920_SND_BIT; // 1
  ST7920_SND_BIT; // 2
  ST7920_SND_BIT; // 3
  ST7920_SND_BIT; // 4
  ST7920_SND_BIT; // 5
  ST7920_SND_BIT; // 6
  ST7920_SND_BIT; // 7
  ST7920_SND_BIT; // 8
}

#define ST7920_DELAY() _delay_us(10)

#define ST7920_CS()              { WRITE2(ST7920_CS_PIN,1); ST7920_DELAY(); }
#define ST7920_NCS()             { WRITE2(ST7920_CS_PIN,0); }
#define ST7920_SET_CMD()         { ST7920_SWSPI_SND_8BIT(0xF8); ST7920_DELAY(); }
#define ST7920_SET_DAT()         { ST7920_SWSPI_SND_8BIT(0xFA); ST7920_DELAY(); }
#define ST7920_WRITE_BYTE(a)     { ST7920_SWSPI_SND_8BIT((uint8_t)((a)&0xF0u)); ST7920_SWSPI_SND_8BIT((uint8_t)((a)<<4u)); ST7920_DELAY(); }
#define ST7920_WRITE_BYTES(p,l)  { for (uint8_t i = l + 1; --i;) { ST7920_SWSPI_SND_8BIT(*p&0xF0); ST7920_SWSPI_SND_8BIT(*p<<4); p++; } ST7920_DELAY(); }

uint8_t scr[LCD_PIXEL_WIDTH*LCD_PIXEL_HEIGHT/8];

//uint8_t lcd_currline; //declared on lcd.cpp

uint8_t lcd_currCol_line_0;
uint8_t lcd_currCol_line_1;
uint8_t lcd_currCol_line_2;
uint8_t lcd_currCol_line_3;
uint8_t lcd_currCol_line_4;
uint8_t lcd_currCol_line_5;
uint8_t lcd_currCol_line_6;
uint8_t lcd_currCol_line_7;

uint8_t lcd_currCol[8] = {
  lcd_currCol_line_0,
  lcd_currCol_line_1,
  lcd_currCol_line_2,
  lcd_currCol_line_3,
  lcd_currCol_line_4,
  lcd_currCol_line_5,
  lcd_currCol_line_6,
  lcd_currCol_line_7
};

int OFFSET_LEFT = 4; //4 for 2004, 0 for 2008
int OFFSET_TOP = 16; //16 for 2004, 0 for 2008

#define read_font_byte(x) pgm_read_byte(&cfont.font[x])

struct _propFont
{
  const uint8_t* font;
  int8_t xSize;
  uint8_t ySize;
  uint8_t firstCh;
  uint8_t lastCh;
  uint8_t minCharWd;
  uint8_t minDigitWd;
};

bool (*isNumberFun)(uint8_t ch);
_propFont  cfont;
uint8_t cr;  // carriage return mode for printStr
uint8_t dualChar;
uint8_t invertCh;
uint8_t spacing = 1;

byte scrWd = 128/8;
byte scrHt = 64;

bool isNumber(uint8_t ch)
{
  return isdigit(ch) || ch==' ';
}

void lcd_setFont(const uint8_t* font)
{
    cfont.font = font;
    cfont.xSize = read_font_byte(0);
    cfont.ySize = read_font_byte(1);
    cfont.firstCh = read_font_byte(2);
    cfont.lastCh  = read_font_byte(3);
    cfont.minDigitWd = 0;
    cfont.minCharWd = 0;
    isNumberFun = &isNumber;
    spacing = 1;
    cr = 0;
    invertCh = 0;

    /*Serial.print("xSize: ");Serial.println(cfont.xSize);
    Serial.print("ySize: ");Serial.println(cfont.ySize);
    Serial.print("firstCh: ");Serial.println(cfont.firstCh);
    Serial.print("lastCh: ");Serial.println(cfont.lastCh);*/

}

void lcd_set_cursor(uint8_t col, uint8_t row) 
{
    if(row > (LCD_HEIGHT -1)) {
        row--;
    }

    if(row < 0) {
        row = 0;
    }

    if(col > (LCD_WIDTH -1)) {
        col--;
    }

    if(col < 0) {
        col = 0;
    }

    lcd_currline = row;
    lcd_currCol[lcd_currline] = col;
}

void lcd_reset()
{
    //Serial.println("lcd_reset called");
    int buf = 0;
    byte i,j,b = 0;

    ST7920_CS();

    int y = 0;
    int x = 0;

    for(j=0; j<(LCD_PIXEL_HEIGHT) / 2; j++) 
    {
        y = j+buf*64;

        if(y>=32    && y<64)    { y-=32; x+=8; Serial.print("case1");} else
        if(y>=64    && y<64+32) { y-=32; x+=0; Serial.print("case2");} else
        if(y>=64+32 && y<64+64) { y-=64; x+=8; Serial.print("case3");}

        ST7920_SET_CMD();
        ST7920_WRITE_BYTE(LCD_ADDR | y); //set y // 6-bit (0..63)
        ST7920_WRITE_BYTE(LCD_ADDR | x); //set x // 4-bit (0..15)

        for(i=0;i<16;i++) 
        {  // 16 bytes from line #0+
            scr[i+j*16] = b;
            ST7920_SET_DAT();
            ST7920_WRITE_BYTE(b);
        }

        for(i=0;i<16;i++) 
        {  // 16 bytes from line #32+
            scr[i+(j+32)*16] = b; 
            ST7920_SET_DAT();
            ST7920_WRITE_BYTE(b);
        }
    }

    ST7920_NCS();
}

void set_mode_2008(void)
{
    OFFSET_TOP = 0;
    OFFSET_LEFT = 4;
    lcd_set_cursor(0,0);
}

void set_mode_2004(void)
{
    OFFSET_TOP = 16;
    OFFSET_LEFT = 4;
    lcd_set_cursor(0,0);
}

void lcd_init_dogm(void) {

    uint8_t i, y;

    OUT_WRITE(ST7920_CS_PIN, LOW);
    OUT_WRITE(ST7920_DAT_PIN, LOW);
    OUT_WRITE(ST7920_CLK_PIN, HIGH);

    ST7920_CS();
    _delay(120);                 //initial delay for boot up
    ST7920_SET_CMD();
    ST7920_WRITE_BYTE(LCD_NON_EXTEND);       //non-extended mode
    ST7920_WRITE_BYTE(LCD_DISPLAYOFF);       //display off, cursor+blink off
    ST7920_WRITE_BYTE(LCD_CLS);       //clear DDRAM ram
    _delay(15);                    //delay for DDRAM clear
    ST7920_WRITE_BYTE(LCD_EXTEND);       //extended mode
    ST7920_WRITE_BYTE(LCD_GFXMODE);       //extended mode + GDRAM active
    for (y = 0; y < (LCD_PIXEL_HEIGHT) / 2; y++) { //clear GDRAM
        //Serial.print("y0: ");Serial.println(y);
        ST7920_WRITE_BYTE(LCD_ADDR | y); //set y
        ST7920_WRITE_BYTE(LCD_ADDR);     //set x = 0
        ST7920_SET_DAT();
        for (i = 0; i < 2 * (LCD_PIXEL_WIDTH) / 8; i++) //2x width clears both segments
            ST7920_WRITE_BYTE(0);
        ST7920_SET_CMD();
    }
    ST7920_WRITE_BYTE(LCD_DISPLAYON); //display on, cursor+blink off
    ST7920_NCS();

    lcd_setFont(Small5x7);

    #if (LCD_HEIGHT == 8) 
        set_mode_2008();
    #else
        set_mode_2004();
    #endif
}

void setGlyph(uint8_t c, int xpos, int ypos) {

    if(c < cfont.firstCh || c > cfont.lastCh) {
        SERIAL_PROTOCOLLNPGM("Char not printable");
        return;
    }

    int fht8 = (cfont.ySize + 7) / 8, wd, fwd = cfont.xSize;
    if(fwd < 0)  fwd = -fwd;
    int x,y8,b,cdata = (c - cfont.firstCh) * (fwd*fht8+1) + 4;
    wd = read_font_byte(cdata++);

    byte d;
    int wdL = 0, wdR = spacing;

    if((*isNumberFun)(c)) {
        if(cfont.minDigitWd>wd) {
        wdL = (cfont.minDigitWd-wd)/2;
        wdR += (cfont.minDigitWd-wd-wdL);
        }
    } else
    if(cfont.minCharWd>wd) {
        wdL = (cfont.minCharWd-wd)/2;
        wdR += (cfont.minCharWd-wd-wdL);
    }
    if(xpos+wd+wdL+wdR>LCD_PIXEL_WIDTH) wdR = max(LCD_PIXEL_WIDTH-xpos-wdL-wd, 0);
    if(xpos+wd+wdL+wdR>LCD_PIXEL_WIDTH) wd  = max(LCD_PIXEL_WIDTH-xpos-wdL, 0);
    if(xpos+wd+wdL+wdR>LCD_PIXEL_WIDTH) wdL = max(LCD_PIXEL_WIDTH-xpos, 0);

    for(x=0; x<wd; x++) 
    {
        byte mask = 0x80 >> ((xpos+x+wdL)&7);

        for(y8=0; y8<fht8; y8++) 
        {
            d = read_font_byte(cdata+x*fht8+y8);
            int lastbit = cfont.ySize - y8 * 8;
            if (lastbit > 8) lastbit = 8;

            for(b=0; b<lastbit; b++) 
            {   
                if(d & 1) scr[(ypos+y8*8+b)*scrWd+(xpos+x+wdL)/8] |= mask;
                else scr[(ypos+y8*8+b)*scrWd+(xpos+x+wdL)/8] &= ~(mask);
                d>>=1;
            }
        }
    }

    int iX = xpos/16;
    int prevX = (xpos-INFO_FONT_WIDTH)/16;
    int nextX = (xpos+INFO_FONT_WIDTH)/16;
    byte index = 0;

    if(ypos > 31) 
    {
        iX += 8;
        prevX += 8;
        nextX += 8;
    }
    
    ST7920_CS();
    for(int i=0; i<INFO_FONT_HEIGHT; i++)
    {
        int iY = ypos+i;
        if(ypos > 31)  iY -= 32;

        if(prevX > 0 && prevX < iX) {
            ST7920_SET_CMD();
            ST7920_WRITE_BYTE(LCD_ADDR | iY);
            ST7920_WRITE_BYTE(LCD_ADDR | prevX);
            index = 2 * ((xpos-INFO_FONT_WIDTH)/16);
            ST7920_SET_DAT();
            ST7920_WRITE_BYTE(scr[index + (ypos+i) * 16]);
            ST7920_WRITE_BYTE(scr[(index + 1) + (ypos+i) * 16]);
        }
        
        ST7920_SET_CMD();
        ST7920_WRITE_BYTE(LCD_ADDR | iY);
        ST7920_WRITE_BYTE(LCD_ADDR | iX);
        index = 2 * (xpos/16);
        ST7920_SET_DAT();
        ST7920_WRITE_BYTE(scr[index + (ypos+i) * 16]);
        ST7920_WRITE_BYTE(scr[(index + 1) + (ypos+i) * 16]);

        if(nextX > iX) 
        {
            ST7920_SET_CMD();
            ST7920_WRITE_BYTE(LCD_ADDR | iY);
            ST7920_WRITE_BYTE(LCD_ADDR | nextX);
            ST7920_SET_DAT();
            index = 2 * ((xpos+INFO_FONT_WIDTH)/16);
            ST7920_WRITE_BYTE(scr[index + (ypos+i) * 16]);
            ST7920_WRITE_BYTE(scr[(index + 1) + (ypos+i) * 16]);
        }
    }
    ST7920_NCS();
}

static void lcd_send(uint8_t data)
{
    uint8_t x = (lcd_currCol[lcd_currline] * INFO_FONT_WIDTH) + OFFSET_LEFT;
    uint8_t y = ((lcd_currline * INFO_FONT_HEIGHT) + OFFSET_TOP);
    setGlyph(data, x, y);
}

void lcd_write_dogm(uint8_t value) 
{

    if (value == '\n')
	{
		if (lcd_currline > (LCD_HEIGHT - 1)) lcd_currline = -1;
		lcd_set_cursor(0, lcd_currline + 1); // LF
		return;
	}

    //printf_P(PSTR("lcd_write_dogm - value: %x\n"), value);

    lcd_send(value);
    
    lcd_currCol[lcd_currline]++;
    if( lcd_currCol[lcd_currline] >= LCD_WIDTH )
    {
        //Serial.println("maximum cols reached");
        lcd_currCol[lcd_currline] = 0;
    }
}

void lcd_home(void)
{
    lcd_currline = 0;
    lcd_currCol[0] = 0;
    lcd_currCol[1] = 0;
    lcd_currCol[2] = 0;
    lcd_currCol[3] = 0;
    lcd_currCol[4] = 0;
    lcd_currCol[5] = 0;
    lcd_currCol[6] = 0;
    lcd_currCol[7] = 0;
    lcd_set_cursor(0, 0);
}

void lcd_clear(void)
{
    //SERIAL_PROTOCOLLNPGM("lcd_clear called");
    lcd_currline = 0;
    lcd_currCol[0] = 0;
    lcd_currCol[1] = 0;
    lcd_currCol[2] = 0;
    lcd_currCol[3] = 0;
    lcd_currCol[4] = 0;
    lcd_currCol[5] = 0;
    lcd_currCol[6] = 0;
    lcd_currCol[7] = 0;

    lcd_reset();

    lcd_home();
}


void lcd_print_dogm(const char* s)
{
	while (*s) lcd_write_dogm(*(s++));
}

void lcd_print_dogm(const char s)
{
	lcd_write_dogm(s);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void lcd_createChar_P(uint8_t location, const CustomCharacter *char_p)
{
    //SERIAL_PROTOCOLLNPGM("lcd_createChar_P - to be implemented");
}

#pragma GCC reset_options

#endif