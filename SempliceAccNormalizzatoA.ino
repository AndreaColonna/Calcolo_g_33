/* Misura dei valori di g Arduino LSM9DS1 - Simple Accelerometer
  created 20 Apr 2022
  by Andrea Colonna
*/
#include <phyphoxBle.h>
char board_name[] = "Mobile";
#include <Arduino_LSM9DS1.h>  // library arduino IMU

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  
  if (!IMU.begin()) {
    digitalWrite(LED_BUILTIN,HIGH);
    while (1);
  }

   PhyphoxBLE::start(board_name); // inizia il BLE Server 

}

void loop() {
  float gx = -1;
  float gy = -1;
  float gz = -1;
  float g;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(gx, gy, gz);
    gx=9.540*gx;  // normlizzazione a g
    gy=9.540*gy;  // normalizzazione a g
    gz=9.540*gz;  // normalizzazione a g 
    g=sqrt(pow(gx,2)+pow(gy,2)+pow(gz,2));

    PhyphoxBLE::write(gx,gy,gz,g);
    delay(50);
  }
}
