#include "stm32f4xx_hal.h" // Adjust this include according to your STM32 series

#include <stdint.h>
#include <stdbool.h>

typedef struct{
    GPIO_TypeDef *DC_port;
    uint16_t DC_pins;
    GPIO_TypeDef *RES_port;
    uint16_t RES_pins;
    GPIO_TypeDef *CS_port;
    uint16_t CS_pins;
    GPIO_TypeDef *BL_port;
    uint16_t BL_pins;
    SPI_HandleTypeDef *spi;
}TFT_pins;

void ST7735_BL_on(TFT_pins *pins,bool on);
void _ST7735_Write_Cmd(TFT_pins *pins,uint8_t cmd);
void _ST7735_Write_Data(TFT_pins *pins,uint8_t *data,uint16_t size);
void _ST7735_Hard_Reset(TFT_pins *pins);
void ST7735_Init(TFT_pins *pins);
void ST7735_Fill_Screen(TFT_pins *pins,uint16_t color,uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end);
void ST7735_Show_img(TFT_pins *pins,const uint8_t *img,uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end);