#include <ost4ml5b32a.h>

Color c;
Pixels pixels(13, 12, 3);
char x[10];
char y = 1;
bool b = true;
void setup() {
  Serial.begin(115200);
  pixels.begin();
}
void loop() {
  pixels.setBrightness(255);
  for (int i = 0; i < 255; i++) {
    pixels.setPixelColor(0, 255 - i, 0, i);
    pixels.setPixelColor(1, 0, i, 255 - i);
    pixels.setPixelColor(2, i, 255 - i, 0);
    pixels.show();
    delay(10);
  }
  for (int i = 0; i < 255; i++) {
    pixels.setPixelColor(0, 0, i, 255 - i);
    pixels.setPixelColor(1, i, 255 - i, 0);
    pixels.setPixelColor(2, 255 - i, 0, i);
    pixels.show();
    delay(10);
  }
  for (int i = 0; i < 255; i++) {
    pixels.setPixelColor(0, i, 255 - i, 0);
    pixels.setPixelColor(1, 255 - i, 0, i);
    pixels.setPixelColor(2, 0, i, 255 - i);
    pixels.show();
    delay(10);
  }


  c = pixels.getPixelColor(0);
  Serial.print("red:");
  Serial.print(c.red);
  Serial.print(" green:");
  Serial.print(c.green);
  Serial.print(" blue:");
  Serial.println(c.blue);
  delay(1000);
}
