#include "seeed_line_chart.h" //include the library
#include "LIS3DHTR.h"

TFT_eSPI tft;
TFT_eSprite spr = TFT_eSprite(&tft); // Sprite

LIS3DHTR<TwoWire>  lis;

#define MAX_SIZE 50 // maximum size of data
doubles data;       // Initilising a doubles type to store data
int brightness;
doubles accelerator_readings[3];

int sound;

const unsigned char home[] = {
  0x00, 0x00, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x07, 
  0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0xFF, 
  0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 
  0x80, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x07, 0x00, 
  0x00, 0x00, 0x00, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
  0x07, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 
  0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x07, 0x00, 0x00, 
  0x00, 0x00, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x07, 
  0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0xFF, 
  0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 
  0x00, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x07, 0x00, 
  0x00, 0x00, 0x00, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xFF, 
  0x07, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 
  0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x07, 0x00, 0x00, 
  0x00, 0x00, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x07, 
  0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0xFF, 
  0xFF, 0x07, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0xE0, 
  0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 
  0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 
  0xFF, 0x0F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0xFE, 
  0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 
  0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0x7F, 
  0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0xC0, 0xFF, 
  0xFF, 0x1F, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 
  0x00, 0xFE, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x03, 0x00, 
  0x00, 0x00, 0x00, 0xFC, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xE0, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x1F, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x80, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 
  0x00, 0x00, };

const unsigned char light[] = {
  0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xC0, 0x03, 0xC0, 0x00, 0x00, 
  0x00, 0x80, 0x07, 0xC0, 0x03, 0xE0, 0x01, 0x00, 0x00, 0x80, 0x0F, 0xC0, 
  0x03, 0xF0, 0x01, 0x00, 0x00, 0x80, 0x1F, 0xC0, 0x01, 0xF8, 0x01, 0x00, 
  0x00, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 
  0x00, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x7C, 0x00, 0x00, 
  0x00, 0x00, 0x18, 0x00, 0x02, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 
  0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x7F, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x80, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 
  0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x07, 0x00, 0x00, 
  0xC0, 0x03, 0xF0, 0xFF, 0xFF, 0x0F, 0xC0, 0x03, 0xC0, 0x1F, 0xF8, 0xFF, 
  0xFF, 0x1F, 0xF8, 0x03, 0xE0, 0x3F, 0xF8, 0xFF, 0xFF, 0x1F, 0xFC, 0x03, 
  0x80, 0x3F, 0xFC, 0xFF, 0xFF, 0x3F, 0xFC, 0x03, 0x00, 0x3E, 0xFC, 0xFF, 
  0xFF, 0x3F, 0x7C, 0x00, 0x00, 0x08, 0xFE, 0xFF, 0xFF, 0x7F, 0x08, 0x00, 
  0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 
  0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 
  0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
  0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 
  0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 
  0xFF, 0x7F, 0x00, 0x00, 0x00, 0x18, 0xFE, 0xFF, 0xFF, 0x7F, 0x18, 0x00, 
  0x00, 0x3F, 0xFC, 0xFF, 0xFF, 0x3F, 0xFC, 0x00, 0xC0, 0x3F, 0xFC, 0xFF, 
  0xFF, 0x3F, 0xFC, 0x03, 0xC0, 0x3F, 0xF8, 0xFF, 0xFF, 0x1F, 0xFC, 0x03, 
  0xC0, 0x0F, 0xF8, 0xFF, 0xFF, 0x1F, 0xF0, 0x03, 0xC0, 0x01, 0xF0, 0xFF, 
  0xFF, 0x0F, 0x80, 0x03, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x07, 0x00, 0x00, 
  0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 
  0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0x01, 0x00, 0x00, 
  0x00, 0x00, 0x80, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xFF, 
  0xFF, 0x38, 0x00, 0x00, 0x00, 0x00, 0x3E, 0xFE, 0x7F, 0x7C, 0x00, 0x00, 
  0x00, 0x00, 0x3E, 0xFE, 0x7F, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFE, 
  0x7F, 0xF8, 0x00, 0x00, 0x00, 0x80, 0x0F, 0xFE, 0x7F, 0xF0, 0x01, 0x00, 
  0x00, 0x80, 0x0F, 0xFE, 0x7F, 0xF0, 0x01, 0x00, 0x00, 0x80, 0x07, 0x7E, 
  0x7E, 0xE0, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 
  0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x7F, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xFE, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 
  0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 
  0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xFC, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 
  0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x03, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, };

const unsigned char soundicon[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xC0, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 
  0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xFC, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 
  0x3F, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0xF0, 0x00, 
  0x00, 0x00, 0x80, 0xFF, 0x7F, 0x00, 0xF0, 0x01, 0x00, 0x00, 0xE0, 0xFF, 
  0x3F, 0x00, 0xF0, 0x03, 0x00, 0x00, 0xF0, 0xFF, 0x3F, 0x00, 0xE0, 0x03, 
  0x00, 0x00, 0xF8, 0xFF, 0x7F, 0x00, 0xC0, 0x07, 0x00, 0x00, 0xFC, 0xFF, 
  0x3F, 0x80, 0xC1, 0x0F, 0x00, 0x00, 0xFF, 0xFF, 0x7F, 0xC0, 0x83, 0x0F, 
  0x00, 0x80, 0xFF, 0xFF, 0x7F, 0xC0, 0x07, 0x1F, 0xF8, 0xFF, 0xFF, 0xFF, 
  0x3F, 0xC0, 0x07, 0x1E, 0xFE, 0xFF, 0xFF, 0xFF, 0x3F, 0x80, 0x0F, 0x3E, 
  0xFE, 0xFF, 0xFF, 0xFF, 0x7F, 0x80, 0x1F, 0x3C, 0xFF, 0xFF, 0xFF, 0xFF, 
  0x3F, 0x00, 0x1F, 0x3C, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x3E, 0x7C, 
  0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x00, 0x3E, 0x78, 0xFF, 0xFF, 0xFF, 0xFF, 
  0x7F, 0x00, 0x3C, 0x78, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x00, 0x7C, 0xF8, 
  0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x00, 0x78, 0x78, 0xFF, 0xFF, 0xFF, 0xFF, 
  0x3F, 0x00, 0x78, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x78, 0xF8, 
  0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x00, 0xF8, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 
  0x3F, 0x00, 0x78, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x00, 0xF8, 0xF0, 
  0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x78, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 
  0x3F, 0x00, 0x78, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x00, 0x78, 0xF8, 
  0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x00, 0x78, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 
  0x7F, 0x00, 0x7C, 0x78, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x00, 0x3C, 0x78, 
  0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x00, 0x3E, 0x78, 0xFF, 0xFF, 0xFF, 0xFF, 
  0x3F, 0x00, 0x3E, 0x7C, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x1F, 0x3C, 
  0xFE, 0xFF, 0xFF, 0xFF, 0x3F, 0x00, 0x1F, 0x3E, 0xFE, 0xFF, 0xFF, 0xFF, 
  0x7F, 0xC0, 0x0F, 0x3E, 0xF8, 0xFF, 0xFF, 0xFF, 0x7F, 0xC0, 0x07, 0x1F, 
  0x00, 0x80, 0xFF, 0xFF, 0x3F, 0xC0, 0x07, 0x1F, 0x00, 0x00, 0xFF, 0xFF, 
  0x3F, 0xC0, 0x83, 0x0F, 0x00, 0x00, 0xFC, 0xFF, 0x7F, 0x80, 0x80, 0x0F, 
  0x00, 0x00, 0xF8, 0xFF, 0x3F, 0x00, 0xE0, 0x07, 0x00, 0x00, 0xF0, 0xFF, 
  0x7F, 0x00, 0xE0, 0x03, 0x00, 0x00, 0xE0, 0xFF, 0x7F, 0x00, 0xF0, 0x01, 
  0x00, 0x00, 0x80, 0xFF, 0x3F, 0x00, 0xF0, 0x01, 0x00, 0x00, 0x00, 0xFF, 
  0x3F, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x7F, 0x00, 0x20, 0x00, 
  0x00, 0x00, 0x00, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 
  0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x3F, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xC0, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
  0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };

const unsigned char accelicon[] = {
  0x00, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 
  0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xBF, 0xFB, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0x78, 0x81, 0x81, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x80, 
  0x01, 0x78, 0x00, 0x00, 0x00, 0x80, 0x07, 0x80, 0x01, 0xE0, 0x00, 0x00, 
  0x00, 0xC0, 0x01, 0x80, 0x01, 0x80, 0x03, 0x00, 0x00, 0x70, 0x00, 0x80, 
  0x01, 0x00, 0x07, 0x00, 0x00, 0x30, 0x00, 0xF0, 0x0F, 0x00, 0x0C, 0x00, 
  0x00, 0x1C, 0x00, 0x7C, 0x3E, 0x00, 0x38, 0x00, 0x00, 0x0E, 0x00, 0x0E, 
  0x70, 0x00, 0x70, 0x00, 0x00, 0x03, 0x00, 0x03, 0xE0, 0x00, 0xE0, 0x00, 
  0x80, 0x03, 0x80, 0x01, 0x80, 0x01, 0xC0, 0x01, 0x80, 0x01, 0x80, 0x01, 
  0x80, 0x01, 0x80, 0x01, 0xC0, 0x00, 0xC0, 0x00, 0x00, 0x03, 0x00, 0x03, 
  0x60, 0x00, 0x60, 0x00, 0x00, 0x06, 0x00, 0x02, 0x60, 0x00, 0x60, 0x00, 
  0x00, 0x06, 0x00, 0x06, 0x30, 0x00, 0x30, 0x00, 0x00, 0x06, 0x00, 0x0C, 
  0x30, 0x00, 0x30, 0x00, 0x00, 0x0C, 0x00, 0x0C, 0x18, 0x00, 0x10, 0x00, 
  0x00, 0x0C, 0x00, 0x18, 0x18, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x18, 
  0x08, 0x00, 0x18, 0xFE, 0xBF, 0x18, 0x00, 0x10, 0x0C, 0x00, 0xF8, 0xFF, 
  0xFF, 0x1F, 0x00, 0x30, 0x0C, 0x00, 0xFE, 0x00, 0x00, 0xFF, 0x00, 0x30, 
  0x0C, 0xC0, 0x0F, 0x00, 0x00, 0xF0, 0x03, 0x20, 0x06, 0xF0, 0x0C, 0x00, 
  0x00, 0x30, 0x0F, 0x60, 0x06, 0x38, 0x0C, 0x00, 0x00, 0x30, 0x1C, 0x60, 
  0x06, 0x0E, 0x0C, 0x00, 0x00, 0x30, 0x38, 0x60, 0x06, 0x06, 0x0C, 0x80, 
  0x00, 0x30, 0x60, 0x40, 0x02, 0x03, 0x04, 0xE0, 0x01, 0x20, 0xC0, 0x60, 
  0x07, 0x03, 0x04, 0x30, 0x03, 0x30, 0xC0, 0xE0, 0xFF, 0x01, 0x0C, 0x30, 
  0x06, 0x20, 0x80, 0xFF, 0xFF, 0x01, 0x06, 0x30, 0x06, 0x60, 0xC0, 0xFF, 
  0x03, 0x03, 0x04, 0xE0, 0x03, 0x30, 0xC0, 0xC0, 0x03, 0x03, 0x0C, 0xE0, 
  0x03, 0x20, 0xC0, 0x60, 0x06, 0x06, 0x04, 0x00, 0x00, 0x30, 0x60, 0x60, 
  0x06, 0x0E, 0x0C, 0x00, 0x00, 0x30, 0x30, 0x60, 0x06, 0x38, 0x0C, 0x00, 
  0x00, 0x30, 0x1C, 0x60, 0x04, 0xF0, 0x0C, 0x00, 0x00, 0xB0, 0x0F, 0x20, 
  0x06, 0xC0, 0x0F, 0x00, 0x00, 0xF0, 0x03, 0x30, 0x0C, 0x00, 0x7F, 0x00, 
  0x80, 0x7E, 0x00, 0x30, 0x0C, 0x00, 0xF8, 0xFF, 0xFF, 0x1F, 0x00, 0x30, 
  0x08, 0x00, 0x18, 0xFA, 0x5F, 0x18, 0x00, 0x10, 0x18, 0x00, 0x18, 0x00, 
  0x00, 0x18, 0x00, 0x18, 0x18, 0x00, 0x30, 0x00, 0x00, 0x08, 0x00, 0x18, 
  0x30, 0x00, 0x30, 0x00, 0x00, 0x0C, 0x00, 0x0C, 0x30, 0x00, 0x30, 0x00, 
  0x00, 0x0C, 0x00, 0x0C, 0x60, 0x00, 0x60, 0x00, 0x00, 0x06, 0x00, 0x06, 
  0x60, 0x00, 0x60, 0x00, 0x00, 0x06, 0x00, 0x02, 0xC0, 0x00, 0xC0, 0x00, 
  0x00, 0x03, 0x00, 0x03, 0x80, 0x01, 0x80, 0x01, 0x80, 0x03, 0x80, 0x01, 
  0x00, 0x03, 0x80, 0x03, 0x80, 0x01, 0xC0, 0x01, 0x00, 0x07, 0x00, 0x07, 
  0xE0, 0x00, 0x60, 0x00, 0x00, 0x0C, 0x00, 0x0E, 0x70, 0x00, 0x70, 0x00, 
  0x00, 0x1C, 0x00, 0x3C, 0x3C, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0xF0, 
  0x0F, 0x00, 0x0C, 0x00, 0x00, 0xE0, 0x00, 0x80, 0x01, 0x00, 0x07, 0x00, 
  0x00, 0xC0, 0x01, 0x80, 0x01, 0x80, 0x03, 0x00, 0x00, 0x80, 0x07, 0x80, 
  0x01, 0xE0, 0x01, 0x00, 0x00, 0x00, 0x1E, 0x80, 0x01, 0x78, 0x00, 0x00, 
  0x00, 0x00, 0xF8, 0x80, 0x01, 0x1F, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xBF, 
  0xFD, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x7F, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xE0, 0x03, 0x00, 0x00, 0x00, };

const unsigned char music[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x1F, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 
  0x87, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xFF, 0xEF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 
  0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xE0, 0x0F, 0xFF, 0xE3, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x07, 0xFE, 0xC0, 0x0F, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x03, 
  0x7C, 0x80, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xF0, 0x03, 0x38, 0x80, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x01, 0x00, 0x00, 0x1F, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x01, 
  0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xF0, 0x03, 0x00, 0x80, 0x1F, 0x00, 0x00, 0x00, 0x1C, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x03, 0x00, 0x80, 0x0F, 0x00, 
  0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x07, 
  0x00, 0xC0, 0x0F, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xE0, 0x0F, 0x00, 0xE0, 0x0F, 0x00, 0x00, 0xBC, 0xFF, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x1F, 0x00, 0xF0, 0x07, 0x00, 
  0x00, 0xFE, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 
  0x00, 0xF8, 0x03, 0x00, 0x00, 0xFE, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 
  0x02, 0x00, 0x00, 0x7F, 0x00, 0xFC, 0x03, 0x00, 0x00, 0xFC, 0xFF, 0x07, 
  0x00, 0x00, 0x00, 0xC0, 0x0F, 0x00, 0x00, 0xFE, 0x01, 0xFF, 0x00, 0x00, 
  0x00, 0xF8, 0xE3, 0x1F, 0x00, 0x00, 0x00, 0xF8, 0x1F, 0x00, 0x00, 0xFC, 
  0x83, 0x7F, 0x00, 0x00, 0xE0, 0xFC, 0xC7, 0x1F, 0x00, 0x00, 0x00, 0xFF, 
  0x1F, 0x00, 0x00, 0xF8, 0xC7, 0x3F, 0x00, 0x00, 0xF0, 0xFF, 0x8F, 0x3F, 
  0x00, 0x00, 0xE0, 0xFF, 0x0F, 0x00, 0x00, 0xF0, 0xFF, 0x1F, 0x00, 0x00, 
  0xF0, 0xFF, 0x1F, 0x7F, 0x00, 0x00, 0xF8, 0xFF, 0x1F, 0x00, 0x00, 0xE0, 
  0xFF, 0x07, 0x00, 0x00, 0xF0, 0xFF, 0x1F, 0xFE, 0x00, 0x80, 0xFF, 0xFF, 
  0x0F, 0x00, 0x00, 0x80, 0xFF, 0x03, 0x00, 0x00, 0xE0, 0x1F, 0x7F, 0xFC, 
  0x00, 0xE0, 0xFF, 0x8F, 0x1F, 0x00, 0x00, 0x00, 0xFF, 0x01, 0x00, 0x00, 
  0xE0, 0x1F, 0xFE, 0xFE, 0x00, 0xF0, 0xFF, 0x01, 0x0F, 0x00, 0x00, 0x00, 
  0x7C, 0x00, 0x00, 0x00, 0xF0, 0x3F, 0xFE, 0x7F, 0x00, 0xF0, 0x3F, 0x80, 
  0x1F, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0xF8, 0x7F, 0xF8, 0x3F, 
  0x00, 0xF0, 0x0F, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xFC, 0xFF, 0xF8, 0x1F, 0x00, 0xF0, 0x01, 0x80, 0x1F, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xF1, 0x0F, 0x00, 0xF0, 0x01, 0x00, 
  0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xF8, 0xF3, 0x1F, 
  0x00, 0xF0, 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
  0xFF, 0xF8, 0xFF, 0x1F, 0x00, 0xF0, 0x01, 0x80, 0x0F, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xC0, 0xFF, 0xE1, 0xFF, 0x3F, 0x00, 0xF0, 0x01, 0x00, 
  0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xC3, 0xFF, 0x3E, 
  0x00, 0xF0, 0x01, 0x80, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 
  0xFF, 0x87, 0x7F, 0x1E, 0x00, 0xF0, 0x01, 0x00, 0x0F, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xF8, 0xE7, 0xCF, 0x7F, 0x00, 0x00, 0xF0, 0x01, 0x80, 
  0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xC1, 0xDF, 0xFF, 0x00, 
  0x00, 0xF0, 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 
  0xC0, 0xFF, 0xFF, 0x00, 0x00, 0xF0, 0x01, 0x80, 0x0F, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x7F, 0x00, 0xFF, 0xFF, 0x01, 0x00, 0xF0, 0x01, 0x7E, 
  0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0xFE, 0xF3, 0x00, 
  0x00, 0xF0, 0x81, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x3F, 
  0x00, 0xFE, 0x61, 0x00, 0x00, 0xF0, 0xC1, 0xFF, 0x1F, 0x00, 0x00, 0x00, 
  0x7F, 0x00, 0xE0, 0x1F, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xF0, 0xE1, 0xFF, 
  0x0F, 0x00, 0x00, 0xF0, 0xFF, 0x07, 0xF0, 0x07, 0x00, 0x7F, 0x00, 0x00, 
  0x00, 0xF0, 0xE1, 0xFF, 0x1F, 0x00, 0x00, 0xFC, 0xFF, 0x3F, 0xF8, 0x03, 
  0x80, 0x3F, 0x00, 0x00, 0x00, 0xF0, 0xF1, 0xC7, 0x0F, 0x00, 0x00, 0xFE, 
  0xFF, 0x7F, 0xFC, 0x03, 0xC0, 0x1F, 0x00, 0x00, 0x00, 0xF0, 0xF1, 0x81, 
  0x0F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0xE0, 0x0F, 0x00, 0x00, 
  0xE0, 0xFF, 0xF1, 0x81, 0x1F, 0x00, 0x80, 0xFF, 0x80, 0xFF, 0x7F, 0x00, 
  0xF0, 0x07, 0x00, 0x00, 0xF8, 0xFF, 0xF9, 0x01, 0x1F, 0x00, 0xC0, 0x3F, 
  0x00, 0xFC, 0x7F, 0x00, 0xF8, 0x03, 0x00, 0x00, 0xFC, 0xFF, 0xF1, 0x81, 
  0x0F, 0x00, 0xE0, 0x0F, 0x00, 0xF0, 0x1F, 0x00, 0xFC, 0x01, 0x00, 0x00, 
  0xFE, 0xFF, 0xF1, 0x81, 0x0F, 0x00, 0xF0, 0x07, 0x00, 0xE0, 0x1F, 0x00, 
  0xFE, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xF1, 0xC7, 0x0F, 0x00, 0xF0, 0x03, 
  0x00, 0xF0, 0x07, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x3E, 0xFC, 0xE1, 0xFF, 
  0x07, 0x00, 0xF8, 0x01, 0x00, 0xF8, 0x07, 0x80, 0x3F, 0x00, 0x00, 0x00, 
  0x3F, 0xF0, 0xE1, 0xFF, 0x07, 0x00, 0xFC, 0x00, 0x00, 0xFC, 0x01, 0xC0, 
  0x1F, 0x00, 0x00, 0x00, 0x1F, 0xF8, 0xC1, 0xFF, 0x03, 0x00, 0xFC, 0x00, 
  0x00, 0xFE, 0x00, 0xE0, 0x0F, 0x00, 0x00, 0x00, 0x1F, 0xF0, 0x81, 0xFF, 
  0x01, 0x00, 0x7E, 0x00, 0x00, 0x7F, 0x00, 0xF0, 0x07, 0x00, 0x00, 0x00, 
  0x1F, 0xF0, 0x01, 0x7E, 0x00, 0x00, 0x3F, 0x00, 0x80, 0x7F, 0x00, 0xF8, 
  0x03, 0x00, 0x00, 0x00, 0x3F, 0xF8, 0x01, 0x00, 0x00, 0x80, 0x3F, 0x00, 
  0xC0, 0x1F, 0x00, 0xFC, 0x01, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00, 
  0x00, 0xC0, 0x1F, 0x00, 0xE0, 0x1F, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 
  0xFE, 0xFF, 0x00, 0x00, 0x00, 0xC0, 0x0F, 0x00, 0xF0, 0x07, 0x00, 0x7F, 
  0x00, 0x00, 0x00, 0x00, 0xFC, 0x7F, 0x00, 0x00, 0x00, 0xF0, 0x0F, 0x00, 
  0xF8, 0x07, 0xC0, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x3F, 0x00, 0x00, 
  0x00, 0xF8, 0x03, 0x00, 0xFC, 0x01, 0xC0, 0xFF, 0x00, 0x00, 0x00, 0x00, 
  0xF0, 0x1F, 0x00, 0x00, 0x00, 0xFC, 0x03, 0x00, 0xFE, 0x00, 0xE0, 0xFF, 
  0x00, 0x00, 0x00, 0x00, 0x80, 0x02, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 
  0x7F, 0x00, 0xF0, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xC0, 0xFF, 0x00, 0x80, 0x7F, 0x00, 0xF8, 0xFB, 0x01, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F, 0x00, 0xC0, 0x1F, 0x00, 0xFC, 0xF1, 
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x1F, 0x00, 0xE0, 
  0x0F, 0x00, 0xFE, 0xF0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 
  0xFF, 0x07, 0x00, 0xF0, 0x07, 0x00, 0x7F, 0xE0, 0x03, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xFC, 0xFF, 0x03, 0x00, 0xF8, 0x07, 0x80, 0x3F, 0xE0, 
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x00, 0xFC, 
  0x01, 0xC0, 0x1F, 0xE0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 
  0x1F, 0x00, 0x00, 0xFE, 0x00, 0xE0, 0x0F, 0xC0, 0x07, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xE0, 0xFF, 0x01, 0x00, 0xF0, 0x7F, 0x00, 0xF0, 0x07, 0xE0, 
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F, 0x00, 0x00, 0xFE, 0xFF, 
  0x00, 0xF8, 0x03, 0xC0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x07, 
  0x00, 0x00, 0xFF, 0xFF, 0x01, 0xFC, 0x01, 0xC0, 0x07, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xFE, 0x03, 0x00, 0x80, 0xFF, 0xFF, 0x03, 0xFF, 0x00, 0xC0, 
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 
  0x07, 0x7F, 0x00, 0xC0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 
  0x00, 0xE0, 0x1F, 0xF0, 0x8F, 0x3F, 0x00, 0xE0, 0x07, 0x00, 0x00, 0x00, 
  0x00, 0x80, 0x3F, 0x00, 0x00, 0xF0, 0x07, 0xC0, 0xDF, 0x1F, 0x00, 0xE0, 
  0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x1F, 0x00, 0x00, 0xF0, 0x03, 0x80, 
  0xFF, 0x0F, 0x00, 0xE0, 0x03, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x0F, 0x00, 
  0x00, 0xF0, 0x01, 0x00, 0xFF, 0x07, 0x00, 0xF0, 0x03, 0x00, 0x00, 0x00, 
  0x00, 0xE0, 0x07, 0x00, 0x00, 0xF8, 0x01, 0x00, 0xFF, 0x03, 0x00, 0xF0, 
  0x03, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x07, 0x00, 0x00, 0xF8, 0x00, 0x00, 
  0xFE, 0x01, 0x00, 0xF8, 0x01, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x03, 0x00, 
  0x00, 0xF8, 0x00, 0x00, 0xFE, 0x00, 0x00, 0xFC, 0x01, 0x00, 0x00, 0x00, 
  0x00, 0xF0, 0x03, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x7E, 0x00, 0x00, 0xFE, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x01, 0x00, 0x00, 0xF8, 0x00, 0x00, 
  0x3C, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x01, 0x00, 
  0x00, 0x7C, 0x00, 0x00, 0x3E, 0x00, 0xC0, 0x3F, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xF8, 0x01, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x3E, 0x00, 0xE0, 0x1F, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x01, 0x00, 0x00, 0xF8, 0x00, 0x00, 
  0x3E, 0x00, 0xF0, 0x0F, 0x00, 0x1C, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 
  0x00, 0xF8, 0x01, 0x00, 0x3F, 0x00, 0xF8, 0x07, 0x00, 0xFE, 0x00, 0x00, 
  0x00, 0xF8, 0x00, 0x00, 0x00, 0xF8, 0x01, 0x00, 0x3F, 0x00, 0xF8, 0x03, 
  0x00, 0xFE, 0x07, 0x00, 0x00, 0xF8, 0x01, 0x00, 0x00, 0xF0, 0x03, 0x80, 
  0x1F, 0x00, 0xF0, 0x00, 0x00, 0xFE, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x00, 
  0x00, 0xF0, 0x07, 0xC0, 0x1F, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x3F, 0x00, 
  0x00, 0xF8, 0x00, 0x00, 0x00, 0xE0, 0x0F, 0xE0, 0x0F, 0x00, 0x00, 0x00, 
  0x00, 0xFE, 0x3F, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x80, 0xC1, 0xFF, 0xFE, 
  0x07, 0x00, 0x00, 0x00, 0x00, 0xBE, 0x3F, 0x00, 0x00, 0xF8, 0x00, 0x00, 
  0xC0, 0x87, 0xFF, 0xFF, 0x03, 0x70, 0x00, 0x00, 0x00, 0x3E, 0x1C, 0x00, 
  0x00, 0xF8, 0x01, 0x00, 0xC0, 0x07, 0xFF, 0xFF, 0x01, 0xF0, 0x00, 0x00, 
  0x00, 0x3E, 0x00, 0x00, 0x00, 0xF0, 0x01, 0x00, 0xC0, 0x0F, 0xFE, 0xFF, 
  0x00, 0xF8, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0xF0, 0x01, 0x78, 
  0xC0, 0x3F, 0xF8, 0x1F, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 
  0x00, 0xF0, 0x01, 0xFC, 0x80, 0x3F, 0x80, 0x02, 0x00, 0x70, 0x00, 0x00, 
  0x00, 0x3E, 0x00, 0x00, 0x00, 0xF0, 0x03, 0xF8, 0x01, 0x7F, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0xE0, 0x03, 0xF8, 
  0x03, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 
  0x00, 0xE0, 0x03, 0xF0, 0x07, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x3E, 0x00, 0x00, 0x00, 0xE0, 0x07, 0xE0, 0x0F, 0x78, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0xC0, 0x07, 0xC0, 
  0x1F, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 
  0x00, 0xC0, 0x0F, 0x80, 0x3F, 0x00, 0x00, 0x00, 0xC0, 0x07, 0x00, 0x00, 
  0x00, 0x3E, 0x00, 0x00, 0x00, 0x80, 0x0F, 0x00, 0x7F, 0x00, 0x00, 0x00, 
  0xC0, 0x07, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x80, 0x1F, 0x00, 
  0xFE, 0x00, 0x00, 0x00, 0xC0, 0x07, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 
  0x00, 0x00, 0x3F, 0x00, 0xFC, 0x01, 0x00, 0x00, 0xC0, 0x07, 0x00, 0x00, 
  0x10, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0xF8, 0x03, 0x00, 0x00, 
  0xE0, 0x07, 0x00, 0x00, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 
  0xF0, 0x07, 0x00, 0x00, 0xE0, 0x03, 0x00, 0x00, 0xFF, 0x3F, 0x00, 0x00, 
  0x00, 0x00, 0xFC, 0x00, 0xE0, 0x0F, 0x00, 0x00, 0xE0, 0x03, 0x00, 0x80, 
  0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x01, 0xC0, 0x1F, 0x00, 0x00, 
  0xF0, 0x03, 0x00, 0xC0, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x03, 
  0x80, 0x0F, 0x00, 0x00, 0xF0, 0x03, 0x00, 0xC0, 0xFF, 0x3F, 0x00, 0x00, 
  0x00, 0x00, 0xF0, 0x03, 0x00, 0x0F, 0x00, 0x00, 0xF0, 0x01, 0x00, 0xE0, 
  0x07, 0x3F, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x0F, 0x00, 0x04, 0x00, 0x00, 
  0xF8, 0x01, 0x00, 0xE0, 0x03, 0x3F, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x0F, 
  0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0xE0, 0x03, 0x3E, 0x00, 0x00, 
  0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0xE0, 
  0x03, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00, 
  0x7E, 0x00, 0x00, 0xE0, 0x03, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 
  0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0xE0, 0x07, 0x1F, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xFC, 0x03, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0xC0, 
  0xEF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x07, 0x00, 0x00, 0xC0, 
  0x1F, 0x00, 0x00, 0xC0, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 
  0x1F, 0x00, 0x00, 0xE0, 0x0F, 0x00, 0x00, 0x80, 0xFF, 0x0F, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xE0, 0x7F, 0x00, 0x00, 0xF8, 0x07, 0x00, 0x00, 0x00, 
  0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x03, 0x00, 0xFE, 
  0x07, 0x00, 0x00, 0x00, 0xFE, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xFF, 0x3F, 0xC0, 0xFF, 0x01, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0x7F, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xC0, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x7F, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };

void welcomepage()
{
    spr.fillSprite(tft.color565(0,0,0));

    spr.fillRect(0,40,320,95,tft.color565(0,255,0)); //Rectangle fill with dark green 
    spr.setTextColor(tft.color565(0,0,0)); //Setting text color
    spr.setTextSize(3); //Setting text size 
    spr.drawString("WELCOME TO",75,50); //Drawing a text string 
    spr.drawString("WIO TERMINAL",60,100); //Drawing a text string 

    spr.setTextSize(2); //Setting text size
    spr.setTextColor(tft.color565(255,255,255)); //Setting text color
    spr.drawString("Middle Press to",75,170); //Drawing a text string 
    spr.drawString("Get Started",75,200); //Drawing a text string

    spr.drawXBitmap(260,170, home, 50, 50,tft.color565(0,255,0)); 

    spr.pushSprite(0, 0);
    delay(50);
}

void homepage()
{
    spr.fillSprite(tft.color565(0,0,0));

    spr.fillTriangle(160,65,140,95,180,95,tft.color565(0,255,0));
    spr.fillTriangle(160,175,140,145,180,145,tft.color565(0,255,0));
    spr.fillTriangle(220,120,190,100,190,140,tft.color565(0,255,0));
    spr.fillTriangle(100,120,130,100,130,140,tft.color565(0,255,0));

    spr.fillCircle(160,120,15,tft.color565(0,255,0));

    spr.setTextColor(tft.color565(255,255,255));          //sets the text colour to black
    spr.setTextSize(3);   
    spr.drawString("LIGHT", 120, 25);
    spr.drawString("ACCEL", 120, 195);
    spr.drawString("MIC", 35, 110);
    spr.drawString("BUZZ", 235, 110);

    spr.pushSprite(0, 0);
    delay(50);
}

void lightpage()
{
    while(1){

    spr.fillSprite(tft.color565(0,0,0));

    spr.fillRect(0,0,320,50,tft.color565(204,204,0)); //Rectangle fill with dark green 
    spr.setTextColor(tft.color565(0,0,0)); //Setting text color
    spr.setTextSize(3); //Setting text size 
    spr.drawString("LIGHT INTENSITY",30,15); //Drawing a text string 

    spr.drawXBitmap(25,80, light, 64, 64, tft.color565(204,204,0));

    brightness = analogRead(WIO_LIGHT);

    spr.setTextSize(4);
    spr.setTextColor(tft.color565(204,204,0)); //Setting text color
    spr.drawNumber(brightness,25,180); //Display temperature values 

    if (data.size() > MAX_SIZE)
    {
        data.pop(); // this is used to remove the first read variable
    }
    data.push(brightness); // read variables and store in data

    // Settings for the line graph
    auto content = line_chart(110, 80); //(x,y) where the line graph begins
    content
        .height(150) // actual height of the line chart
        .width(200)         // actual width of the line chart
        .based_on(0.0)                                // Starting point of y-axis, must be a float
        .show_circle(false)                           // drawing a cirle at each point, default is on.
        .value(data)                                  // passing through the data to line graph
        .max_size(MAX_SIZE)
        .color(tft.color565(204,204,0))                               // Setting the color for the line
        .backgroud(tft.color565(0,0,0))
        .draw(&spr);

    spr.pushSprite(0, 0);
    delay(50);

    if (digitalRead(WIO_5S_PRESS) == LOW) {
        homepage();
        break;
    }

    else if (digitalRead(WIO_5S_UP) == LOW or digitalRead(WIO_5S_DOWN) == LOW or digitalRead(WIO_5S_LEFT) == LOW or digitalRead(WIO_5S_RIGHT) == LOW) {
        break;
    }
    }
}

void soundpage()
{
    while(1){

    spr.fillSprite(tft.color565(0,0,0));

    spr.fillRect(0,0,320,50,TFT_RED); //Rectangle fill with dark green 
    spr.setTextColor(tft.color565(0,0,0)); //Setting text color
    spr.setTextSize(3); //Setting text size 
    spr.drawString("SOUND INTENSITY",30,15); //Drawing a text string 

    spr.drawXBitmap(25,80, soundicon, 64, 64, TFT_RED);

    sound = analogRead(WIO_MIC);

    spr.setTextSize(4);
    spr.setTextColor(TFT_RED); //Setting text color
    spr.drawNumber(sound,25,180); //Display temperature values 

    if (data.size() > MAX_SIZE)
    {
        data.pop(); // this is used to remove the first read variable
    }
    data.push(sound); // read variables and store in data

    // Settings for the line graph
    auto content = line_chart(110, 80); //(x,y) where the line graph begins
    content
        .height(150) // actual height of the line chart
        .width(200)         // actual width of the line chart
        .based_on(0.0)                                // Starting point of y-axis, must be a float
        .show_circle(false)                           // drawing a cirle at each point, default is on.
        .value(data)                                  // passing through the data to line graph
        .max_size(MAX_SIZE)
        .color(TFT_RED)                               // Setting the color for the line
        .backgroud(tft.color565(0,0,0))
        .draw(&spr);

    spr.pushSprite(0, 0);
    delay(50);

    if (digitalRead(WIO_5S_PRESS) == LOW) {
        homepage();
        break;
    }

    else if (digitalRead(WIO_5S_UP) == LOW or digitalRead(WIO_5S_DOWN) == LOW or digitalRead(WIO_5S_LEFT) == LOW or digitalRead(WIO_5S_RIGHT) == LOW) {
        break;
    }
    }
}

void accelpage()
{
    while(1){

    spr.fillSprite(tft.color565(0,0,0));

    float x_raw = lis.getAccelerationX();
    float y_raw = lis.getAccelerationY();
    float z_raw = lis.getAccelerationZ();

    spr.fillRect(0,0,320,50,tft.color565(0,255,255)); //Rectangle fill with dark green 
    spr.setTextColor(tft.color565(0,0,0)); //Setting text color
    spr.setTextSize(3); //Setting text size 
    spr.drawString("ACCELEROMETER",40,15); //Drawing a text string 

    spr.drawXBitmap(25,70, accelicon, 64, 64, tft.color565(0,255,255));

    spr.setTextSize(2);
    spr.setTextColor(tft.color565(0,255,255)); //Setting text color
    spr.drawString("X:",15,150);
    spr.drawFloat(x_raw,3,35,150); //Display temperature values 
    spr.setTextColor(tft.color565(204,204,0)); //Setting text color
    spr.drawString("Y:",15,180);
    spr.drawFloat(y_raw,3,35,180); //Display temperature values 
    spr.setTextColor(TFT_RED); //Setting text color
    spr.drawString("Z:",15,210);
    spr.drawFloat(z_raw,3,35,210); //Display temperature values

    if (accelerator_readings[0].size() == MAX_SIZE) {
      for (uint8_t i = 0; i<3; i++){
        accelerator_readings[i].pop(); //this is used to remove the first read variable
      }
    }
    accelerator_readings[0].push(x_raw); //read variables and store in data
    accelerator_readings[1].push(y_raw);
    accelerator_readings[2].push(z_raw);

    // Settings for the line graph
    auto content = line_chart(110, 80); //(x,y) where the line graph begins
    content
        .height(150) // actual height of the line chart
        .width(200)         // actual width of the line chart
        .based_on(0.0)                                // Starting point of y-axis, must be a float
        .show_circle(false)                           // drawing a cirle at each point, default is on.
        .value({accelerator_readings[0],accelerator_readings[1], accelerator_readings[2]})                                  // passing through the data to line graph
        .max_size(MAX_SIZE)
        .color(tft.color565(0,255,255), tft.color565(204,204,0), TFT_RED)                               // Setting the color for the line
        .backgroud(tft.color565(0,0,0))
        .draw(&spr);

    spr.pushSprite(0, 0);
    delay(50);

    if (digitalRead(WIO_5S_PRESS) == LOW) {
        homepage();
        break;
    }

    else if (digitalRead(WIO_5S_UP) == LOW or digitalRead(WIO_5S_DOWN) == LOW or digitalRead(WIO_5S_LEFT) == LOW or digitalRead(WIO_5S_RIGHT) == LOW) {
        break;
    }
    }
}

void playTone(int tone, int duration) {
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
        digitalWrite(WIO_BUZZER, HIGH);
        delayMicroseconds(tone);
        digitalWrite(WIO_BUZZER, LOW);
        delayMicroseconds(tone);
    }
}
 
void playNote(char note, int duration) {
    char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
    int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
 
    // play the tone corresponding to the note name
    for (int i = 0; i < 8; i++) {
        if (names[i] == note) {
            playTone(tones[i], duration);
        }
    }
}

void buzzerpage()
{

    spr.fillSprite(tft.color565(0,0,0));

    spr.fillRect(0,0,320,50,tft.color565(153,51,255)); //Rectangle fill with dark green 
    spr.setTextColor(tft.color565(0,0,0)); //Setting text color
    spr.setTextSize(3); //Setting text size 
    spr.drawString("BUZZER",110,15); //Drawing a text string 

    spr.drawXBitmap(90,80, music, 128, 128, tft.color565(153,51,255));


    spr.pushSprite(0, 0);
    delay(50);
    
    int length = 15;         /* the number of notes */
    char notes[] = "ccggaagffeeddc ";
    int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
    int tempo = 300;

    for(int i = 0; i < length; i++) {
        if(notes[i] == ' ') {
            delay(beats[i] * tempo);
        } else {
            playNote(notes[i], beats[i] * tempo);
        }
        delay(tempo / 2);    /* delay between notes */
    }
}

void setup()
{
    pinMode(WIO_LIGHT, INPUT);
    pinMode(WIO_MIC, INPUT);
    pinMode(WIO_BUZZER, OUTPUT);

    pinMode(WIO_5S_UP, INPUT_PULLUP);
    pinMode(WIO_5S_DOWN, INPUT_PULLUP);
    pinMode(WIO_5S_LEFT, INPUT_PULLUP);
    pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
    pinMode(WIO_5S_PRESS, INPUT_PULLUP);

    tft.begin();
    tft.setRotation(3);
    spr.createSprite(320, 240);
    spr.setRotation(3);

    lis.begin(Wire1);
    lis.setOutputDataRate(LIS3DHTR_DATARATE_25HZ);
    lis.setFullScaleRange(LIS3DHTR_RANGE_2G);

    welcomepage();

}

void loop()
{
    if (digitalRead(WIO_5S_PRESS) == LOW) {
        homepage();
    }
    if (digitalRead(WIO_5S_UP) == LOW) {
        lightpage();
    }  
    else if (digitalRead(WIO_5S_LEFT) == LOW) {
        soundpage();
    }  
    else if (digitalRead(WIO_5S_DOWN) == LOW) {
        accelpage();
    }   
    else if (digitalRead(WIO_5S_RIGHT) == LOW) {
        buzzerpage();
    }   
}