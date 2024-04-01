// #include <GyverMAX7219.h>
// MAX7219 <13, 11, 5> led;

// void setup() {
//   led.begin();
//   led.setBright(5);
//   //led.rotate(1);   // 0..3, 90 degrees

//   led.dot(0, 0);
//   led.update();
//   delay(1000);
//   led.clear();
// }

// void loop() {
//   // cross
//   led.line(0, 0, 7, 7);  // (x0, y0, x1, y1)
//   led.line(7, 0, 0, 7);
//   led.update();
//   delay(1000);
//   led.clear();


//   // circle
//   led.circle(3, 3, 3, GFX_STROKE);
//   led.update();
//   delay(1000);
//   led.clear();
//   // full circle
//   led.circle(3, 3, 3, GFX_FILL); // х, у, radius, fill
//   led.update();
//   delay(1000);
//   led.clear();
// }
