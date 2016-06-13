/*
Sigmaz 2016 
Capcitive proximity puzzle for Klues

*/

#include <ADCTouch.h>

int ref0, ref1, ref2, ref3;       //reference values to remove offset
int locked = 1; // started with LOCK_PIN high to drive SSR for mag lock

#define LOCK_PIN 2

void setup()
{
  pinMode (LOCK_PIN, OUTPUT);

  Serial.begin(9600);

  ref0 = ADCTouch.read(A0, 500);    //create reference values to
  ref1 = ADCTouch.read(A1, 500);    //account for the capacitance of the pad
  ref2 = ADCTouch.read(A2, 500);
  ref3 = ADCTouch.read(A3, 500);
}

void loop()
{

  readSensors();
  lockManager();
}


void readSensors()
{
  int value0 = ADCTouch.read(A0);     //no second parameter
  int value1 = ADCTouch.read(A1);     //   --> 100 samples
  int value2 = ADCTouch.read(A2);     //   --> 100 samples
  int value3 = ADCTouch.read(A3);     //   --> 100 samples

  value0 -= ref0;       //remove offset
  value1 -= ref1;
  value2 -= ref2;
  value3 -= ref3;
/*
  Serial.print(value0 > 40);    //return pressed or not pressed
  Serial.print("\t");
  Serial.print(value1 > 40);
  Serial.print("\t");
  Serial.print(value2 > 40);
  Serial.print("\t");
  Serial.print(value3 > 40);
  Serial.print("\t");


  Serial.print(value0);             //return value
  Serial.print("\t");
  Serial.println(value1);
  Serial.print("\t");
  Serial.println(value2);
  Serial.print("\t");
  Serial.println(value3);
  Serial.print("\t");
*/

  if ((value0 > 40) && (value1 > 40) && (value2 > 40) && (value3 > 40))
  {
    locked = 0;
  } else {
    locked = 1;
  }

  delay(100);
}



void lockManager()
{

  if (locked == 0) {
    digitalWrite (LOCK_PIN, LOW);
  } else {
    digitalWrite (LOCK_PIN, HIGH);
  }

}

