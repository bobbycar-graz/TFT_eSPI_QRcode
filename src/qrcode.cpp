#include "qrcode.h"
#include "qrencode.h"

#include <tftinstance.h>

using namespace espgui;

namespace qrcode {

int offsetsX;
int offsetsY;
int screenwidth;
int screenheight;

void QRcode::init()
{
    //((TFT_eSPI *)tft)->init();
    screenwidth = tft.width();
    screenheight = tft.height();
    //tft.setRotation(1);
    //tft.fillScreen(TFT_WHITE);
    int min = screenwidth;
    if (screenheight<screenwidth)
      min = screenheight;
    multiply = min/WD;
    offsetsX = (screenwidth-(WD*multiply))/2;
    offsetsY = (screenheight-(WD*multiply))/2;

}

void QRcode::setMultiply(int m)
{
    multiply = m;
}

void QRcode::render(int x, int y, int color, int borderOffset)
{
  x=(x*multiply)+offsetsX;
  y=(y*multiply)+offsetsY;

  /*
  for (int i=0;i<multiply;i++)
  {
      for (int j=0;j<multiply;j++)
      {
          if(color==1) {
            tft.drawPixel(x+i,y+j,TFT_BLACK);
          }
          else {
            tft.drawPixel(x+i,y+j,TFT_WHITE);
          }
      }
  }
  */
  if (color == 1)
  {
      tft.fillRect(x+borderOffset, y, multiply, multiply, TFT_BLACK);
  }
  else
  {
      tft.fillRect(x+borderOffset, y, multiply, multiply, TFT_WHITE);
  }
}

void QRcode::create(std::string_view message)
{
  // create QR code
  tft.fillScreen(TFT_WHITE);
  // message.toCharArray((char *)strinbuf,260);
  strncpy((char *)strinbuf, message.data(), 699);
  strinbuf[699] = '\0';
  qrencode();
  // print QR Code
  for (byte x = 0; x < WD; x+=2) {
    for (byte y = 0; y < WD; y++) {
      if ( QRBIT(x,y) &&  QRBIT((x+1),y)) {
        // black square on top of black square
        render(x, y, 1);
        render((x+1), y, 1);
      }
      if (!QRBIT(x,y) &&  QRBIT((x+1),y)) {
        // white square on top of black square
        render(x, y, 0);
        render((x+1), y, 1);
      }
      if ( QRBIT(x,y) && !QRBIT((x+1),y)) {
        // black square on top of white square
        render(x, y, 1);
        render((x+1), y, 0);
      }
      if (!QRBIT(x,y) && !QRBIT((x+1),y)) {
        // white square on top of white square
        render(x, y, 0);
        render((x+1), y, 0);
      }
    }
  }
}

void QRcode::createScaleToFit(std::string_view message, uint8_t border)
{
    m_tmpmult = multiply;

    // create QR code
    tft.fillScreen(TFT_WHITE);
    // message.toCharArray((char *)strinbuf,260);
    strncpy((char *)strinbuf, message.data(), 699);
    strinbuf[699] = '\0';
    qrencode();

    multiply = tft.width() - border * 2;
    multiply = multiply / WD;

    const auto offset = border * 2;

    // print QR Code
    for (byte x = 0; x < WD; x+=2) {
      for (byte y = 0; y < WD; y++) {
        if ( QRBIT(x,y) &&  QRBIT((x+1),y)) {
          // black square on top of black square
          render(x, y, 1, offset);
          render((x+1), y, 1, offset);
        }
        if (!QRBIT(x,y) &&  QRBIT((x+1),y)) {
          // white square on top of black square
          render(x, y, 0, offset);
          render((x+1), y, 1, offset);
        }
        if ( QRBIT(x,y) && !QRBIT((x+1),y)) {
          // black square on top of white square
          render(x, y, 1, offset);
          render((x+1), y, 0, offset);
        }
        if (!QRBIT(x,y) && !QRBIT((x+1),y)) {
          // white square on top of white square
          render(x, y, 0, offset);
          render((x+1), y, 0, offset);
        }
      }
    }

    multiply = m_tmpmult;
}

} // namespace
