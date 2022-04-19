/* Misura dei valori di g 
  Arduino LSM9DS1 - Simple Accelerometer

  This example reads the acceleration values from the LSM9DS1
  sensor and continuously prints them to the Serial Monitor
  or Serial Plotter.

  The circuit:
  - Arduino Nano 33 BLE Sense

  created 20 Apr 2022
  by Andrea Colonna

  This example code is in the public domain.
*/
#include <phyphoxBle.h>
char board_name[] = "Mobile";
#include <Arduino_LSM9DS1.h>  // library arduino IMU

void setup() {
//  Serial.begin(9600);
//  while (!Serial);
//  Serial.println("Started");
  pinMode(LED_BUILTIN,OUTPUT);
  
  if (!IMU.begin()) {
    //Serial.println("Failed to initialize IMU!");
    digitalWrite(LED_BUILTIN,HIGH);
    while (1);
  }

 // Serial.print("Accelerometer sample rate = ");
   PhyphoxBLE::start(board_name); // inizia il BLE Server
 
//  Serial.print(IMU.accelerationSampleRate());
//  Serial.println(" Hz");
//  Serial.println();
//  Serial.println("Acceleration in G's");
//  Serial.println("X\tY\tZ");
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
   // Serial.print(x);
   // Serial.print('\t');
   // Serial.print(y);
   // Serial.print('\t');
   // Serial.print(z);
   // Serial.print('\t');
   // Serial.println(g);
  }
}
