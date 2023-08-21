#include "stm32f0xx_hal.h"
#include "DFR0928.h"
#include "DFR0928_GFX.h"
#include "malloc.h"
#include "string.h"

#define DELAY 0x80

// based on Adafruit DFR0928 library for Arduino
static const uint8_t
  init_cmds1[] = {            // Init for 7735R, part 1 (red or green tab)
    15,                       // 15 commands in list:
    DFR0928_SWRESET,   DELAY,  //  1: Software reset, 0 args, w/delay
      150,                    //     150 ms delay
    DFR0928_SLPOUT ,   DELAY,  //  2: Out of sleep mode, 0 args, w/delay
      255,                    //     500 ms delay
    DFR0928_FRMCTR1, 3      ,  //  3: Frame rate ctrl - normal mode, 3 args:
      0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    DFR0928_FRMCTR2, 3      ,  //  4: Frame rate control - idle mode, 3 args:
      0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    DFR0928_FRMCTR3, 6      ,  //  5: Frame rate ctrl - partial mode, 6 args:
      0x01, 0x2C, 0x2D,       //     Dot inversion mode
      0x01, 0x2C, 0x2D,       //     Line inversion mode
    DFR0928_INVCTR , 1      ,  //  6: Display inversion ctrl, 1 arg, no delay:
      0x07,                   //     No inversion
    DFR0928_PWCTR1 , 3      ,  //  7: Power control, 3 args, no delay:
      0xA2,
      0x02,                   //     -4.6V
      0x84,                   //     AUTO mode
    DFR0928_PWCTR2 , 1      ,  //  8: Power control, 1 arg, no delay:
      0xC5,                   //     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
    DFR0928_PWCTR3 , 2      ,  //  9: Power control, 2 args, no delay:
      0x0A,                   //     Opamp current small
      0x00,                   //     Boost frequency
    DFR0928_PWCTR4 , 2      ,  // 10: Power control, 2 args, no delay:
      0x8A,                   //     BCLK/2, Opamp current small & Medium low
      0x2A,
    DFR0928_PWCTR5 , 2      ,  // 11: Power control, 2 args, no delay:
      0x8A, 0xEE,
    DFR0928_VMCTR1 , 1      ,  // 12: Power control, 1 arg, no delay:
      0x0E,
    DFR0928_INVOFF , 0      ,  // 13: Don't invert display, no args, no delay
    DFR0928_MADCTL , 1      ,  // 14: Memory access control (directions), 1 arg:
      DFR0928_ROTATION,        //     row addr/col addr, bottom to top refresh
    DFR0928_COLMOD , 1      ,  // 15: set color mode, 1 arg, no delay:
      0x05 },                 //     16-bit color

#if (defined(DFR0928_IS_128X128) || defined(DFR0928_IS_160X128))
  init_cmds2[] = {            // Init for 7735R, part 2 (1.44" display)
    2,                        //  2 commands in list:
    DFR0928_CASET  , 4      ,  //  1: Column addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x7F,             //     XEND = 127
    DFR0928_RASET  , 4      ,  //  2: Row addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x7F },           //     XEND = 127
#endif // DFR0928_IS_128X128

#ifdef DFR0928_IS_160X80
  init_cmds2[] = {            // Init for 7735S, part 2 (160x80 display)
    3,                        //  3 commands in list:
    DFR0928_CASET  , 4      ,  //  1: Column addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x4F,             //     XEND = 79
    DFR0928_RASET  , 4      ,  //  2: Row addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x9F ,            //     XEND = 159
    DFR0928_INVON, 0 },        //  3: Invert colors
#endif

  init_cmds3[] = {            // Init for 7735R, part 3 (red or green tab)
    4,                        //  4 commands in list:
    DFR0928_GMCTRP1, 16      , //  1: Gamma Adjustments (pos. polarity), 16 args, no delay:
      0x02, 0x1c, 0x07, 0x12,
      0x37, 0x32, 0x29, 0x2d,
      0x29, 0x25, 0x2B, 0x39,
      0x00, 0x01, 0x03, 0x10,
    DFR0928_GMCTRN1, 16      , //  2: Gamma Adjustments (neg. polarity), 16 args, no delay:
      0x03, 0x1d, 0x07, 0x06,
      0x2E, 0x2C, 0x29, 0x2D,
      0x2E, 0x2E, 0x37, 0x3F,
      0x00, 0x00, 0x02, 0x10,
    DFR0928_NORON  ,    DELAY, //  3: Normal display on, no args, w/delay
      10,                     //     10 ms delay
    DFR0928_DISPON ,    DELAY, //  4: Main screen turn on, no args w/delay
      100 };                  //     100 ms delay

static void DFR0928_Select() {
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
}

void DFR0928_Unselect() {
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
}

static void DFR0928_Reset() {
    HAL_GPIO_WritePin(RT_GPIO_Port, RT_Pin, GPIO_PIN_RESET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(RT_GPIO_Port, RT_Pin, GPIO_PIN_SET);
}

static void DFR0928_WriteCommand(uint8_t cmd) {
    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&DFR0928_SPI_PORT, &cmd, sizeof(cmd), HAL_MAX_DELAY);
}

static void DFR0928_WriteData(uint8_t* buff, size_t buff_size) {
    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
    HAL_SPI_Transmit(&DFR0928_SPI_PORT, buff, buff_size, HAL_MAX_DELAY);
}

static void DFR0928_ExecuteCommandList(const uint8_t *addr) {
    uint8_t numCommands, numArgs;
    uint16_t ms;

    numCommands = *addr++;
    while(numCommands--) {
        uint8_t cmd = *addr++;
        DFR0928_WriteCommand(cmd);

        numArgs = *addr++;
        // If high bit set, delay follows args
        ms = numArgs & DELAY;
        numArgs &= ~DELAY;
        if(numArgs) {
            DFR0928_WriteData((uint8_t*)addr, numArgs);
            addr += numArgs;
        }

        if(ms) {
            ms = *addr++;
            if(ms == 255) ms = 500;
            HAL_Delay(ms);
        }
    }
}

static void DFR0928_SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
    // column address set
    DFR0928_WriteCommand(DFR0928_CASET);
    uint8_t data[] = { 0x00, x0 + DFR0928_XSTART, 0x00, x1 + DFR0928_XSTART };
    DFR0928_WriteData(data, sizeof(data));

    // row address set
    DFR0928_WriteCommand(DFR0928_RASET);
    data[1] = y0 + DFR0928_YSTART;
    data[3] = y1 + DFR0928_YSTART;
    DFR0928_WriteData(data, sizeof(data));

    // write to RAM
    DFR0928_WriteCommand(DFR0928_RAMWR);
}

void DFR0928_Init() {
    DFR0928_Select();
    DFR0928_Reset();
    DFR0928_ExecuteCommandList(init_cmds1);
    DFR0928_ExecuteCommandList(init_cmds2);
    DFR0928_ExecuteCommandList(init_cmds3);
    DFR0928_Unselect();
}

void DFR0928_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    if((x >= DFR0928_WIDTH) || (y >= DFR0928_HEIGHT))
        return;

    DFR0928_Select();

    DFR0928_SetAddressWindow(x, y, x+1, y+1);
    uint8_t data[] = { color >> 8, color & 0xFF };
    DFR0928_WriteData(data, sizeof(data));

    DFR0928_Unselect();
}

static void DFR0928_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor) {
    uint32_t i, b, j;

    DFR0928_SetAddressWindow(x, y, x+font.width-1, y+font.height-1);

    for(i = 0; i < font.height; i++) {
        b = font.data[(ch - 32) * font.height + i];
        for(j = 0; j < font.width; j++) {
            if((b << j) & 0x8000)  {
                uint8_t data[] = { color >> 8, color & 0xFF };
                DFR0928_WriteData(data, sizeof(data));
            } else {
                uint8_t data[] = { bgcolor >> 8, bgcolor & 0xFF };
                DFR0928_WriteData(data, sizeof(data));
            }
        }
    }
}

/*
Simpler (and probably slower) implementation:

static void DFR0928_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color) {
    uint32_t i, b, j;

    for(i = 0; i < font.height; i++) {
        b = font.data[(ch - 32) * font.height + i];
        for(j = 0; j < font.width; j++) {
            if((b << j) & 0x8000)  {
                DFR0928_DrawPixel(x + j, y + i, color);
            }
        }
    }
}
*/

void DFR0928_WriteString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor) {
    DFR0928_Select();

    while(*str) {
        if(x + font.width >= DFR0928_WIDTH) {
            x = 0;
            y += font.height;
            if(y + font.height >= DFR0928_HEIGHT) {
                break;
            }

            if(*str == ' ') {
                // skip spaces in the beginning of the new line
                str++;
                continue;
            }
        }

        DFR0928_WriteChar(x, y, *str, font, color, bgcolor);
        x += font.width;
        str++;
    }

    DFR0928_Unselect();
}

void DFR0928_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    // clipping
    if((x >= DFR0928_WIDTH) || (y >= DFR0928_HEIGHT)) return;
    if((x + w - 1) >= DFR0928_WIDTH) w = DFR0928_WIDTH - x;
    if((y + h - 1) >= DFR0928_HEIGHT) h = DFR0928_HEIGHT - y;

    DFR0928_Select();
    DFR0928_SetAddressWindow(x, y, x+w-1, y+h-1);

    uint8_t data[] = { color >> 8, color & 0xFF };
    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
    for(y = h; y > 0; y--) {
        for(x = w; x > 0; x--) {
            HAL_SPI_Transmit(&DFR0928_SPI_PORT, data, sizeof(data), HAL_MAX_DELAY);
        }
    }

    DFR0928_Unselect();
}

void DFR0928_FillRectangleFast(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    // clipping
    if((x >= DFR0928_WIDTH) || (y >= DFR0928_HEIGHT)) return;
    if((x + w - 1) >= DFR0928_WIDTH) w = DFR0928_WIDTH - x;
    if((y + h - 1) >= DFR0928_HEIGHT) h = DFR0928_HEIGHT - y;

    DFR0928_Select();
    DFR0928_SetAddressWindow(x, y, x+w-1, y+h-1);

    // Prepare whole line in a single buffer
    uint8_t pixel[] = { color >> 8, color & 0xFF };
    uint8_t *line = malloc(w * sizeof(pixel));
    for(x = 0; x < w; ++x)
    	memcpy(line + x * sizeof(pixel), pixel, sizeof(pixel));

    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
    for(y = h; y > 0; y--)
        HAL_SPI_Transmit(&DFR0928_SPI_PORT, line, w * sizeof(pixel), HAL_MAX_DELAY);

    free(line);
    DFR0928_Unselect();
}

void DFR0928_FillScreen(uint16_t color) {
    DFR0928_FillRectangle(0, 0, DFR0928_WIDTH, DFR0928_HEIGHT, color);
}

void DFR0928_FillScreenFast(uint16_t color) {
    DFR0928_FillRectangleFast(0, 0, DFR0928_WIDTH, DFR0928_HEIGHT, color);
}

void DFR0928_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data) {
    if((x >= DFR0928_WIDTH) || (y >= DFR0928_HEIGHT)) return;
    if((x + w - 1) >= DFR0928_WIDTH) return;
    if((y + h - 1) >= DFR0928_HEIGHT) return;

    DFR0928_Select();
    DFR0928_SetAddressWindow(x, y, x+w-1, y+h-1);
    DFR0928_WriteData((uint8_t*)data, sizeof(uint16_t)*w*h);
    DFR0928_Unselect();
}

void DFR0928_InvertColors(bool invert) {
    DFR0928_Select();
    DFR0928_WriteCommand(invert ? DFR0928_INVON : DFR0928_INVOFF);
    DFR0928_Unselect();
}

void DFR0928_SetGamma(uint8_t gamma)
{
	DFR0928_Select();
	DFR0928_WriteCommand(DFR0928_GAMSET);
	DFR0928_WriteData(&gamma, sizeof(gamma));
	DFR0928_Unselect();
}

void ShowWelcomeScreen(void)
{
  DFR0928_FillScreen(DFR0928_BLACK);
  DFR0928_WriteString(0, 0, "Temperature", Font_7x10, DFR0928_RED, DFR0928_BLACK);
  DFR0928_WriteString(0, 3*10, "by katazaki", Font_11x18, DFR0928_GREEN, DFR0928_BLACK);
  DFR0928_WriteString(0, 3*10+3*18, "August 2023", Font_16x26, DFR0928_BLUE, DFR0928_BLACK);
  HAL_Delay(3000);
}

void ShowCircleScreen(void)
{
  DFR0928_FillScreen(DFR0928_BLACK);
  drawCircle(50, 55, 20, DFR0928_GREEN);
  drawCircle(50, 55, 21, DFR0928_GREEN);
  drawCircle(50, 55, 22, DFR0928_GREEN);
  drawCircle(50, 55, 23, DFR0928_GREEN);
  drawCircle(50, 55, 24, DFR0928_GREEN);
  drawCircle(50, 55, 25, DFR0928_RED);
  drawCircle(50, 55, 26, DFR0928_RED);
  drawCircle(50, 55, 27, DFR0928_RED);
  drawCircle(50, 55, 28, DFR0928_RED);
  HAL_Delay(10000);
}
