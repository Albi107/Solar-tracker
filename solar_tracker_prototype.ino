
#include <VarSpeedServo.h> //inclusion of servo library

VarSpeedServo Hservo;  //declaration of servo motors
VarSpeedServo Vservo;

// declaration of sensors for physical reception
float Sensor0 = A0; // (North sensor)
float Sensor1 = A1; // (East sensor)
float Sensor2 = A2; // (South sensor)
float Sensor3 = A3; // (West sensor)

//declaration of other variables
float East = 0;
float West = 180;
float North = 0;
float South = 180;
float tolerance = 5;
float pos1,pos2;

float ValA0,ValA1,ValA2,ValA3;
float ValA02,ValA12,ValA22,ValA32;

void setup()
{
  Serial.begin(9600);
  Hservo.attach(10);//Secondary servo
  Vservo.attach(9);//Primary servo
}

void loop()
{

  pos1 = Hservo.read();
  pos2 = Vservo.read();

  ValA02 = map(ValA0 = analogRead(A0), 0, 1023, 10, 170);
  ValA12 = map(ValA1 = analogRead(A1), 0, 1023, 10, 170);
  ValA22 = map(ValA2 = analogRead(A2), 0, 1023, 10, 170);
  ValA32 = map(ValA3 = analogRead(A3), 0, 1023, 10, 170);
  

  Serial.println("                                   ");
  Serial.println(".................................");
  Serial.print("The northern light intensity is  ");
  Serial.println(ValA02);
  Serial.print("The eastern light intensity is  ");
  Serial.println(ValA12);
  Serial.print("The southern light intensity is  ");
  Serial.println(ValA22);
  Serial.print("The western light intensity is  ");
  Serial.println(ValA32);


  if (ValA12 > ValA32)
  {
    Hservo.write(pos1 + 1, 50, true);
    delay(10);
  }
  else if (ValA12 < ValA32)
  {
    Hservo.write(pos1 - 1, 50, true);
    delay(10);
  }
  
  else
  {
    Hservo.write(pos1, 50, true);
    delay(10);
  }


  if (ValA02 > ValA22)
  {
    Vservo.write(pos2 - 1, 50, true);
   delay(10);
  }
  else if (ValA02 < ValA22)
  {
    Vservo.write(pos2 + 1, 50, true);
    delay(10);
  }
  else
  {
    Vservo.write(pos2, 50, true);
    delay(10);
  }

  if ((ValA02 < tolerance) && (ValA12 < tolerance) && (ValA22 < tolerance) && (ValA32 < tolerance))
  {
    Hservo.write(East, 50, true); // Resets dish eastward to catch the next sunrise
    Vservo.write(90, 50, true);
  }

}
