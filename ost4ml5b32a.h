#ifndef ost4ml5b32a_h
#define ost4ml5b32a_h

#if (ARDUINO >= 100) // Arduino version  >= 1.0.1
#include <Arduino.h>
#else                // Arduino version  >  1.0.0 
#include <WProgram.h>
#include <pins_arduino.h>
#endif

struct Color{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  Color(uint8_t r,uint8_t g,uint8_t b){
    red = r;
    green = g;
    blue = b;
  }
  Color(){
  }
};

//===信号線を幹とするLED群を制御するためのクラス→Pixels
class Pixels {

  public:
    //====Constructor====
    Pixels(uint8_t h, uint8_t l, uint8_t numPixels);//コンストラクタ→ピンの指定、ledの数の指定
    Pixels(void);


    void begin(void);//コンストラクタに入れられない初期設定?(ピンをアウトプットにする,ピンをLOWに設定)
    void show(void);//show()→光らせる


    //====getter====
    int8_t getH_pins(void);
    int8_t getL_pins(void);
    uint8_t getNumPixels(void);// 繋がれているLEDの個数が渡される
    Color getPixelRawColor(uint8_t num);
    Color getPixelColor(uint8_t num);
    uint8_t getBrightness(void);//輝度が渡される



    //====setter====
    void updatePins(uint8_t h, uint8_t l);//ピンをhigh,lowの順で渡すとh_pinとl_pinの値を変えてくれる
    void updateLength(uint8_t numPixels);//ledの個数を変えてくれる
    void setPixelColor(uint8_t num, uint8_t r, uint8_t g, uint8_t b);//ledの番号を指定して、rgbを変更する
    void setBrightness(uint8_t b);//pixelsの輝度を変更する


  private:
  void LED_Hi_Bit(void);
  void LED_Low_Bit(void);
  void sendRGB(uint8_t r, uint8_t g, uint8_t b);

    //==プロパティ
    uint8_t h_pin;// sending high signal pin
    uint8_t l_pin;// sending low signal pin
    uint8_t numLeds;//number of leds
    uint8_t** color;
    uint8_t** offsetcolor;
    uint8_t red;//led red value
    uint8_t green;//led green value
    uint8_t blue;//led blue value
    uint8_t brightness;//value of pixels brightness
    bool begun;//false before execution begin()
};


#endif
