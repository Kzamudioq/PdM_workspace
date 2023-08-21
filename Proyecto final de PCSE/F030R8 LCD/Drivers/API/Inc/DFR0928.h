#ifndef __DFR0928_H__
#define __DFR0928_H__

#include "fonts.h"
#include "stm32f0xx_hal.h"
#include <stdbool.h>

#define DFR0928_MADCTL_MY  0x80
#define DFR0928_MADCTL_MX  0x40
#define DFR0928_MADCTL_MV  0x20
#define DFR0928_MADCTL_ML  0x10
#define DFR0928_MADCTL_RGB 0x00
#define DFR0928_MADCTL_BGR 0x08
#define DFR0928_MADCTL_MH  0x04

/*** Redefine if necessary ***/
#define DFR0928_SPI_PORT hspi1
extern SPI_HandleTypeDef DFR0928_SPI_PORT;

#define CS_Pin GPIO_PIN_7
#define CS_GPIO_Port GPIOC
#define DC_Pin GPIO_PIN_6
#define DC_GPIO_Port GPIOB
#define RT_Pin GPIO_PIN_9
#define RT_GPIO_Port GPIOB


//#define DFR0928_SPI_PORT hspi2
//extern SPI_HandleTypeDef DFR0928_SPI_PORT;
//
//#define RT_Pin       GPIO_PIN_2
//#define RT_GPIO_Port GPIOA
//#define CS_Pin        GPIO_PIN_4
//#define CS_GPIO_Port  GPIOA
//#define DC_Pin        GPIO_PIN_3
//#define DC_GPIO_Port  GPIOA


// AliExpress/eBay 1.8" display, default orientation

#define DFR0928_IS_160X128 1
#define DFR0928_WIDTH  128
#define DFR0928_HEIGHT 160
#define DFR0928_XSTART 0
#define DFR0928_YSTART 0
#define DFR0928_ROTATION (DFR0928_MADCTL_MX | DFR0928_MADCTL_MY)


// AliExpress/eBay 1.8" display, rotate right
/*
#define DFR0928_IS_160X128 1
#define DFR0928_WIDTH  160
#define DFR0928_HEIGHT 128
#define DFR0928_XSTART 0
#define DFR0928_YSTART 0
#define DFR0928_ROTATION (DFR0928_MADCTL_MY | DFR0928_MADCTL_MV)
*/

// AliExpress/eBay 1.8" display, rotate left
/*
#define DFR0928_IS_160X128 1
#define DFR0928_WIDTH  160
#define DFR0928_HEIGHT 128
#define DFR0928_XSTART 0
#define DFR0928_YSTART 0
#define DFR0928_ROTATION (DFR0928_MADCTL_MX | DFR0928_MADCTL_MV)
*/

// AliExpress/eBay 1.8" display, upside down
/*
#define DFR0928_IS_160X128 1
#define DFR0928_WIDTH  128
#define DFR0928_HEIGHT 160
#define DFR0928_XSTART 0
#define DFR0928_YSTART 0
#define DFR0928_ROTATION (0)
*/

// WaveShare DFR0928S-based 1.8" display, default orientation
/*
#define DFR0928_IS_160X128 1
#define DFR0928_WIDTH  128
#define DFR0928_HEIGHT 160
#define DFR0928_XSTART 2
#define DFR0928_YSTART 1
#define DFR0928_ROTATION (DFR0928_MADCTL_MX | DFR0928_MADCTL_MY | DFR0928_MADCTL_RGB)
*/

// WaveShare DFR0928S-based 1.8" display, rotate right
/*
#define DFR0928_IS_160X128 1
#define DFR0928_WIDTH  160
#define DFR0928_HEIGHT 128
#define DFR0928_XSTART 1
#define DFR0928_YSTART 2
#define DFR0928_ROTATION (DFR0928_MADCTL_MY | DFR0928_MADCTL_MV | DFR0928_MADCTL_RGB)
*/

// WaveShare DFR0928S-based 1.8" display, rotate left
/*
#define DFR0928_IS_160X128 1
#define DFR0928_WIDTH  160
#define DFR0928_HEIGHT 128
#define DFR0928_XSTART 1
#define DFR0928_YSTART 2
#define DFR0928_ROTATION (DFR0928_MADCTL_MX | DFR0928_MADCTL_MV | DFR0928_MADCTL_RGB)
*/

// WaveShare DFR0928S-based 1.8" display, upside down
/*
#define DFR0928_IS_160X128 1
#define DFR0928_WIDTH  128
#define DFR0928_HEIGHT 160
#define DFR0928_XSTART 2
#define DFR0928_YSTART 1
#define DFR0928_ROTATION (DFR0928_MADCTL_RGB)
*/

// 1.44" display, default orientation
//#define DFR0928_IS_128X128 1
//#define DFR0928_WIDTH  128
//#define DFR0928_HEIGHT 128
//#define DFR0928_XSTART 2
//#define DFR0928_YSTART 3
//#define DFR0928_ROTATION (DFR0928_MADCTL_MX | DFR0928_MADCTL_MY | DFR0928_MADCTL_BGR)

// 1.44" display, rotate right
/*
#define DFR0928_IS_128X128 1
#define DFR0928_WIDTH  128
#define DFR0928_HEIGHT 128
#define DFR0928_XSTART 3
#define DFR0928_YSTART 2
#define DFR0928_ROTATION (DFR0928_MADCTL_MY | DFR0928_MADCTL_MV | DFR0928_MADCTL_BGR)
*/

// 1.44" display, rotate left
/*
#define DFR0928_IS_128X128 1
#define DFR0928_WIDTH  128
#define DFR0928_HEIGHT 128
#define DFR0928_XSTART 1
#define DFR0928_YSTART 2
#define DFR0928_ROTATION (DFR0928_MADCTL_MX | DFR0928_MADCTL_MV | DFR0928_MADCTL_BGR)
*/

// 1.44" display, upside down
/*
#define DFR0928_IS_128X128 1
#define DFR0928_WIDTH  128
#define DFR0928_HEIGHT 128
#define DFR0928_XSTART 2
#define DFR0928_YSTART 1
#define DFR0928_ROTATION (DFR0928_MADCTL_BGR)
*/

// mini 160x80 display (it's unlikely you want the default orientation)
/*
#define DFR0928_IS_160X80 1
#define DFR0928_XSTART 26
#define DFR0928_YSTART 1
#define DFR0928_WIDTH  80
#define DFR0928_HEIGHT 160
#define DFR0928_ROTATION (DFR0928_MADCTL_MX | DFR0928_MADCTL_MY | DFR0928_MADCTL_BGR)
*/

// mini 160x80, rotate left
/*
#define DFR0928_IS_160X80 1
#define DFR0928_XSTART 1
#define DFR0928_YSTART 26
#define DFR0928_WIDTH  160
#define DFR0928_HEIGHT 80
#define DFR0928_ROTATION (DFR0928_MADCTL_MX | DFR0928_MADCTL_MV | DFR0928_MADCTL_BGR)
*/

// mini 160x80, rotate right
/*
#define DFR0928_IS_160X80 1
#define DFR0928_XSTART 1
#define DFR0928_YSTART 26
#define DFR0928_WIDTH  160
#define DFR0928_HEIGHT 80
#define DFR0928_ROTATION (DFR0928_MADCTL_MY | DFR0928_MADCTL_MV | DFR0928_MADCTL_BGR)
*/

/****************************/

#define DFR0928_NOP     0x00
#define DFR0928_SWRESET 0x01
#define DFR0928_RDDID   0x04
#define DFR0928_RDDST   0x09

#define DFR0928_SLPIN   0x10
#define DFR0928_SLPOUT  0x11
#define DFR0928_PTLON   0x12
#define DFR0928_NORON   0x13

#define DFR0928_INVOFF  0x20
#define DFR0928_INVON   0x21
#define DFR0928_GAMSET  0x26
#define DFR0928_DISPOFF 0x28
#define DFR0928_DISPON  0x29
#define DFR0928_CASET   0x2A
#define DFR0928_RASET   0x2B
#define DFR0928_RAMWR   0x2C
#define DFR0928_RAMRD   0x2E

#define DFR0928_PTLAR   0x30
#define DFR0928_COLMOD  0x3A
#define DFR0928_MADCTL  0x36

#define DFR0928_FRMCTR1 0xB1
#define DFR0928_FRMCTR2 0xB2
#define DFR0928_FRMCTR3 0xB3
#define DFR0928_INVCTR  0xB4
#define DFR0928_DISSET5 0xB6

#define DFR0928_PWCTR1  0xC0
#define DFR0928_PWCTR2  0xC1
#define DFR0928_PWCTR3  0xC2
#define DFR0928_PWCTR4  0xC3
#define DFR0928_PWCTR5  0xC4
#define DFR0928_VMCTR1  0xC5

#define DFR0928_RDID1   0xDA
#define DFR0928_RDID2   0xDB
#define DFR0928_RDID3   0xDC
#define DFR0928_RDID4   0xDD

#define DFR0928_PWCTR6  0xFC

#define DFR0928_GMCTRP1 0xE0
#define DFR0928_GMCTRN1 0xE1

// Color definitions
#define	DFR0928_BLACK   0x0000
#define	DFR0928_BLUE    0x001F
#define	DFR0928_RED     0xF800
#define	DFR0928_GREEN   0x07E0
#define DFR0928_CYAN    0x07FF
#define DFR0928_MAGENTA 0xF81F
#define DFR0928_YELLOW  0xFFE0
#define DFR0928_WHITE   0xFFFF
#define DFR0928_COLOR565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

typedef enum {
	GAMMA_10 = 0x01,
	GAMMA_25 = 0x02,
	GAMMA_22 = 0x04,
	GAMMA_18 = 0x08
} GammaDef;

#ifdef __cplusplus
extern "C" {
#endif

// call before initializing any SPI devices
void DFR0928_Unselect();

void DFR0928_Init(void);
void DFR0928_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void DFR0928_WriteString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);
void DFR0928_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void DFR0928_FillRectangleFast(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void DFR0928_FillScreen(uint16_t color);
void DFR0928_FillScreenFast(uint16_t color);
void DFR0928_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);
void DFR0928_InvertColors(bool invert);
void DFR0928_SetGamma(GammaDef gamma);
void ShowWelcomeScreen(void);
void ShowCircleScreen(void);

#ifdef __cplusplus
}
#endif

#endif // __DFR0928_H__
