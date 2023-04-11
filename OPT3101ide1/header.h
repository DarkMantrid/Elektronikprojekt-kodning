// Include the servo library:
#include <Servo.h> // inkluderar bibliotek för servo
#include <OPT3101.h> // inkluderar bibliotek för sensor
#include <Wire.h>
Servo myservo; // Create a new servo object:
#define servoPin 5 // definerar servos pin
const uint8_t dataReadyPin = 2; // Pin nummer för sensor läsning
int angle = 90; // Döper svängningsvinkel till angle
int leftsensor = 0;
int middlesensor = 1;
int rightsensor = 2;
// Namn för olika sväng vinklar för lättare ändring av svängvinkel
int Straight = 43; // Döper rakt vinkel
int TurnAngle = 40; // Det här är hur mycket servon kan svänga för varje riktning.
int TurnLeft = Straight - TurnAngle; // Rakt - svängvinkel gör att bilen svänger till vänster om TurnLeft anropas.
int TurnRight = Straight + TurnAngle; // Rakt + svängvinkel gör att bilen svänger till höger om TurnRight anropas.
// namn för avstånd mätning
int Near = 150;
int NotSafe = 350;
int Safe = 500;
OPT3101 sensor; // döper sensorn
int16_t distances[3]; // aktiverar tre punkter på sensor och döper dem till distances
volatile bool dataReady = false;
void setDataReadyFlag()
{
dataReady = true;
}