#include "ST7735S.h"

void ST7735_BL_on(TFT_pins *pins,bool on){
    if(on){
        HAL_GPIO_WritePin(pins->BL_port,pins->BL_pins,GPIO_PIN_SET);
    }else{
        HAL_GPIO_WritePin(pins->BL_port,pins->BL_pins,GPIO_PIN_RESET);
    }
}

void _ST7735_Hard_Reset(TFT_pins *pins){
    HAL_GPIO_WritePin(pins->RES_port,pins->RES_pins,GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(pins->RES_port,pins->RES_pins,GPIO_PIN_SET);
    HAL_Delay(120);
}

void _ST7735_Write_Cmd(TFT_pins *pins,uint8_t cmd){
    HAL_GPIO_WritePin(pins->DC_port,pins->DC_pins,GPIO_PIN_RESET); //DC low for command
    HAL_SPI_Transmit(pins->spi,&cmd,1,HAL_MAX_DELAY);
    HAL_GPIO_WritePin(pins->DC_port,pins->DC_pins,GPIO_PIN_SET); //DC high for data
}

void _ST7735_Write_Data(TFT_pins *pins,uint8_t *data,uint16_t size){
    HAL_GPIO_WritePin(pins->DC_port,pins->DC_pins,GPIO_PIN_SET);
    HAL_SPI_Transmit(pins->spi,data,size,HAL_MAX_DELAY);
}

void ST7735_Init(TFT_pins *pins){
    //Hard reset
    _ST7735_Hard_Reset(pins);
    //sleep out
    {
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
        _ST7735_Write_Cmd(pins,0x11);
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
        HAL_Delay(120);
    }
    //Frame rate control 80Hz
    {   
        {
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
            _ST7735_Write_Cmd(pins,0xB1);
            uint8_t data[]={0x02,0x35,0x36};
            _ST7735_Write_Data(pins,data,sizeof(data));
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
        }
        HAL_Delay(1);
        {
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
            _ST7735_Write_Cmd(pins,0xB2);
            uint8_t data[]={0x02,0x35,0x36};
            _ST7735_Write_Data(pins,data,sizeof(data));
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
        }
        HAL_Delay(1);
        {
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
            _ST7735_Write_Cmd(pins,0xB3);
            uint8_t data[]={0x02,0x35,0x36,0x02,0x35,0x36};
            _ST7735_Write_Data(pins,data,sizeof(data));
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
        }
        HAL_Delay(1);
    }
    //Dot inversion
    {
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
        _ST7735_Write_Cmd(pins,0xB4);
        uint8_t data[]={0x03};
        _ST7735_Write_Data(pins,data,sizeof(data));
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
        HAL_Delay(1);
    }
    //ST7735S Power Sequence
    {
        {
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
            _ST7735_Write_Cmd(pins,0xC0);
            uint8_t data[]={0xA2,0x02,0x84};
            _ST7735_Write_Data(pins,data,sizeof(data));
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
        }
        HAL_Delay(1);
        {
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
            _ST7735_Write_Cmd(pins,0xC1);
            uint8_t data[]={0xC5};
            _ST7735_Write_Data(pins,data,sizeof(data));
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
        }
        HAL_Delay(1);
        {
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
            _ST7735_Write_Cmd(pins,0xC2);
            uint8_t data[]={0x0D,0x00};
            _ST7735_Write_Data(pins,data,sizeof(data));
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
        }
        HAL_Delay(1);
        {
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
            _ST7735_Write_Cmd(pins,0xC3);
            uint8_t data[]={0x8D,0x2A};
            _ST7735_Write_Data(pins,data,sizeof(data));
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
        }
        HAL_Delay(1);
        {
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
            _ST7735_Write_Cmd(pins,0xC4);
            uint8_t data[]={0x8D,0xEE};
            _ST7735_Write_Data(pins,data,sizeof(data));
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
        }
        HAL_Delay(1);
        {
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
            _ST7735_Write_Cmd(pins,0xC5);
            uint8_t data[]={0x0A};
            _ST7735_Write_Data(pins,data,sizeof(data));
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
        }
        HAL_Delay(1);
    }
    //Memory Data Access Control 
    {
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
        _ST7735_Write_Cmd(pins,0x36);
        uint8_t data[]={0x08};
        _ST7735_Write_Data(pins,data,sizeof(data));
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
        HAL_Delay(1);
    }
    //ST7735S Gamma Sequence
    {
        {
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
            _ST7735_Write_Cmd(pins,0xE0);
            uint8_t data[]={0x12,0x1C,0x10,0x18,0x33,0x2C,0x25,0x28,0x28,0x27,0x2F,0x3C,0x00,0x03,0x03,0x10};
            _ST7735_Write_Data(pins,data,sizeof(data));
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
            HAL_Delay(1);
        }
        {
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
            _ST7735_Write_Cmd(pins,0xE1);
            uint8_t data[]={0x12,0x1C,0x10,0x18,0x2D,0x28,0x23,0x28,0x28,0x26,0x2F,0x3B,0x00,0x03,0x03,0x10};
            _ST7735_Write_Data(pins,data,sizeof(data));
            HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
            HAL_Delay(1);
        }
    }
    //Interface Pixel Format
    {
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
        _ST7735_Write_Cmd(pins,0x3A);
        uint8_t data[]={0x05};
        _ST7735_Write_Data(pins,data,sizeof(data));
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
        HAL_Delay(1);
    }
    //Display On
    {
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
        _ST7735_Write_Cmd(pins,0x29);
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
        HAL_Delay(1);
    }
}

void ST7735_Fill_Screen(TFT_pins *pins,uint16_t color,uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end){
    {
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
        _ST7735_Write_Cmd(pins,0x2A);
        uint8_t data[4];
        data[0] = (x_start>>8)&0xFF;
        data[1] = x_start&0xFF;
        data[2] = (x_end>>8)&0xFF;
        data[3] = x_end&0xFF;
        _ST7735_Write_Data(pins,data,sizeof(data));
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
        HAL_Delay(1);
    }
    {
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
        _ST7735_Write_Cmd(pins,0x2B);
        uint8_t data[4];
        data[0] = (y_start>>8)&0xFF;
        data[1] = y_start&0xFF;
        data[2] = (y_end>>8)&0xFF;
        data[3] = y_end&0xFF;
        _ST7735_Write_Data(pins,data,sizeof(data));
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
        HAL_Delay(1);
    }
    {
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
        _ST7735_Write_Cmd(pins,0x2C);
        uint8_t data[2];
        for(int pixel = 0;pixel<(x_end-x_start+1)*(y_end-y_start+1);pixel++){
            data[0] = (color>>8)&0xFF;
            data[1] = color&0xFF;
            _ST7735_Write_Data(pins,data,sizeof(data));
        }
        _ST7735_Write_Data(pins,data,sizeof(data));
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
        HAL_Delay(1);
    }
}

void ST7735_Show_img(TFT_pins *pins,const uint8_t *img,uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end){
   {
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
        _ST7735_Write_Cmd(pins,0x2A);
        uint8_t data[4];
        data[0] = (x_start>>8)&0xFF;
        data[1] = x_start&0xFF;
        data[2] = (x_end>>8)&0xFF;
        data[3] = x_end&0xFF;
        _ST7735_Write_Data(pins,data,sizeof(data));
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
        HAL_Delay(1);
    }
    {
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
        _ST7735_Write_Cmd(pins,0x2B);
        uint8_t data[4];
        data[0] = (y_start>>8)&0xFF;
        data[1] = y_start&0xFF;
        data[2] = (y_end>>8)&0xFF;
        data[3] = y_end&0xFF;
        _ST7735_Write_Data(pins,data,sizeof(data));
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
        HAL_Delay(1);
    } 
    {
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_RESET);
        _ST7735_Write_Cmd(pins,0x2C);
        _ST7735_Write_Data(pins,img,(x_end-x_start+1)*(y_end-y_start+1)*2);
        HAL_GPIO_WritePin(pins->CS_port,pins->CS_pins,GPIO_PIN_SET);
        HAL_Delay(1);
    }
}
