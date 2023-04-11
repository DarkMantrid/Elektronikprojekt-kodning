#include "header.h"

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  myservo.attach(servoPin); //sätter igång servo
  // Wait for the serial port to be opened before printing
  // messages (only applies to boards with native USB).
  while (!Serial) {}

  sensor.init();
  if (sensor.getLastError())
  {
    Serial.print(F("Failed to initialize OPT3101: error "));
    Serial.println(sensor.getLastError());
    while (1) {}
  }

  sensor.setFrameTiming(256);
  sensor.setChannel(0);
  sensor.setBrightness(OPT3101Brightness::Adaptive);

  sensor.startSample();
}

void loop()
{
  leftsensor = distances[0]; // Döper om vänster sensor från distances[0] till leftsensor
  middlesensor = distances[1]; // Döper om mitt sensor från distances[1] till middlesensor
  rightsensor = distances[2]; // Döper om höger sensor från distances[2] till rightsensor
  if (sensor.isSampleDone())
  {
    sensor.readOutputRegs();

    distances[sensor.channelUsed] = sensor.distanceMillimeters;

    if (sensor.channelUsed == 2)
    {
      
      for (uint8_t i = 0; i < 3; i++)
      {
        if (leftsensor<Safe && rightsensor> leftsensor) // if för höger sväng
        {
          angle = map(leftsensor, Safe, Near, Straight, TurnRight);
          myservo.write(angle);
        }
        else if (rightsensor<Safe && rightsensor<leftsensor) // if för vänster sväng
        {
          angle = map(rightsensor, Safe, Near, Straight, TurnLeft);
          myservo.write(angle);
        }
        else if (middlesensor<NotSafe && rightsensor<leftsensor) // if för höger sväng men om väggen framför närmar sig
        {
          angle = map(rightsensor, Safe, Near, Straight, TurnRight);// map funktion för smidigare sväng
          myservo.write(angle);
        }
        else if (middlesensor<NotSafe && rightsensor>leftsensor) // if för vänster sväng men om väggen framför närmar sig
        {
          angle = map(rightsensor, Safe, Near, Straight, TurnLeft);
          myservo.write(angle);
        }
        else myservo.write(Straight); // bilen kör framåt
        /*
        else myservo.write(Straight);
        Serial.print("\n");
        Serial.print("left sensor= ");
        Serial.print(leftsensor);
        Serial.print("\n");
        Serial.print("Middle Sensor= ");
        Serial.print(middlesensor);
        Serial.print("\n");
        Serial.print("Right Sensor= ");
        Serial.print(rightsensor);
        Serial.print("\n");*/
      } 
      Serial.println();
    }
    sensor.nextChannel();
    sensor.startSample();
  }
}
