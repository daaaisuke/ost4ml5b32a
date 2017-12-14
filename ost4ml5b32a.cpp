#include "ost4ml5b32a.h"

//====constructor====
Pixels::Pixels(uint8_t h, uint8_t l, uint8_t numPixels):
  red(0), blue(0), green(0), brightness(0), begun(false)
{
  updatePins(h, l);
  updateLength(numPixels);
}
Pixels::Pixels(void):
  h_pin(NULL), l_pin(NULL), numLeds(0), red(0), blue(0), green(0), brightness(0), begun(false)
{
}




void Pixels::begin(void) {
  if (h_pin >= 0 && l_pin >= 0) {
    pinMode(h_pin, OUTPUT);
    pinMode(l_pin, OUTPUT);
    digitalWrite(h_pin, LOW);
    digitalWrite(l_pin, HIGH);
    delay(10);
  }
  begun = true;
}
void Pixels::show(void) {
  for (int i = 0; i < numLeds; i ++) { //配列のケツから入れていく
    sendRGB(offsetcolor[numLeds - 1 - i][0], offsetcolor[numLeds - 1 - i][1], offsetcolor[numLeds - 1 - i][2]);
  }

  digitalWrite(h_pin, LOW);
  digitalWrite(l_pin, HIGH);
  delay(1);
}

//====getter====
int8_t Pixels::getH_pins(void) {
  return h_pin;
}
int8_t Pixels::getL_pins(void) {
  return l_pin;
}

uint8_t Pixels::getNumPixels(void) {
  return numLeds;
}
Color Pixels::getPixelRawColor(uint8_t num) {
  return Color(color[num][0], color[num][1], color[num][2]);
}
Color Pixels::getPixelColor(uint8_t num) {
  return Color(offsetcolor[num][0], offsetcolor[num][1], offsetcolor[num][2]);
}

uint8_t Pixels::getBrightness(void) {
  return brightness;
}





//====setter====
void Pixels::updatePins(uint8_t h, uint8_t l) {
  if (h_pin != h | l_pin != l) {
    if (begun && (h_pin >= 0) && (l_pin >= 0)) {
      pinMode(h_pin, INPUT);
      pinMode(l_pin, INPUT);
    }
    h_pin = h;
    l_pin = l;
    if (begun) {
      pinMode(h, OUTPUT);
      pinMode(l, OUTPUT);
      digitalWrite(h, LOW);
      digitalWrite(l, LOW);
    }
  }
}

void Pixels::updateLength(uint8_t numPixels) {
  if (numLeds != numPixels) {
    //===メモリ解放===
    for (int i = 0; i < numLeds; i++) {
      delete[] color[i];
      delete[] offsetcolor[i];
    }
    delete[] color;
    delete[] offsetcolor;
    //====新規作成====
    numLeds = numPixels;
    color = new uint8_t* [numLeds];//**colorは配列のアドレスを入れた配列のアドレス
    offsetcolor = new uint8_t* [numLeds];//**colorは配列のアドレスを入れた配列のアドレス
    for (int i = 0; i < numLeds; i++) {
      color[i] = new uint8_t[3];
      offsetcolor[i] = new uint8_t[3];
      memset(color[i], 0, 3);
      memset(offsetcolor[i], 0, 3);
    }
  }
}

void Pixels::setPixelColor(uint8_t num, uint8_t r, uint8_t g, uint8_t b) {
  //================================
  //brightフィルタ処理
  if (num < numLeds) {
    color[num][0] = r;
    color[num][1] = g;
    color[num][2] = b;
    if (brightness) { // See notes in setBrightness()
      offsetcolor[num][0] = (r * brightness) >> 8;//brightnessのフィルタをかける
      offsetcolor[num][1] = (g * brightness) >> 8;
      offsetcolor[num][2] = (b * brightness) >> 8;
    } else {
      offsetcolor[num][0] = r;
      offsetcolor[num][1] = g;
      offsetcolor[num][2] = b;
    }

  }
  //================================
}

void Pixels::setBrightness(uint8_t b) {

  uint8_t newBrightness = b + 1;//0
  if (newBrightness != brightness) {
    uint8_t oldBrightness = brightness - 1;//oldBrightness=99
    //===scaleの決定===
    uint16_t scale;
    if (oldBrightness == 0) scale = 0; // 前回のbが0なら　スケールは0
    else if (b == 255) scale = 65535 / oldBrightness;
    else scale = (((uint16_t)newBrightness << 8) - 1) / oldBrightness;
    //    =================
    for (uint16_t i = 0; i < numLeds; i++) {
      for (uint16_t j = 0; j < 3; j++) {
        offsetcolor[i][j] = (color[i][j] * scale) >> 8;
      }
    }
    brightness = newBrightness;//0
  }
  //================================
}
//=========================================================//
// H(1)信号送出
//=========================================================//
void Pixels::LED_Hi_Bit(void) {
  digitalWrite(h_pin, HIGH);
  digitalWrite(l_pin, HIGH);
  delayMicroseconds(1);
  digitalWrite(h_pin, LOW);
  digitalWrite(l_pin, HIGH);
  delayMicroseconds(1);
}
//=========================================================//
// L(0)信号送出
//=========================================================//
void Pixels::LED_Low_Bit(void) {
  digitalWrite(h_pin, LOW);
  digitalWrite(l_pin, LOW);
  delayMicroseconds(1);
  digitalWrite(h_pin, LOW);
  digitalWrite(l_pin, HIGH);
  delayMicroseconds(1);
}
//=========================================================//
// rgb情報を実際にledに送る関数
//=========================================================//
void Pixels::sendRGB(uint8_t r, uint8_t g, uint8_t b) {
  for (int k = 0; k <= 7; k++) {  //青
    if ((bitRead(b, 8 - k)) == 1) {
      LED_Hi_Bit();
    }
    else {
      LED_Low_Bit();
    }
  }
  for (int k = 0; k <= 7; k++) {  //緑
    if ((bitRead(g, 8 - k)) == 1) {
      LED_Hi_Bit();
    }
    else {
      LED_Low_Bit();
    }
  }
  for (int k = 0; k <= 7; k++) {  //赤
    if ((bitRead(r, 8 - k)) == 1) {
      LED_Hi_Bit();
    }
    else {
      LED_Low_Bit();
    }
  }
}

