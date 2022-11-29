#include <Wire.h>
#include <Servo.h>

int trig = 2; // attach pin 3 to Trig
int echo = 3; //attach pin 4 to Echo
int servoPin1 = 4; //Attach servoPin1 to digital 4
int servoPin2 = 5; //Attach servoPin2 to digital 5
int ledPin1 = 6; //LED plugged into D6
int ledPin2 = 7; //LED plugged into D7
int buttonState = 0; //hold if a button is pressed or not. 0 = not press, 1 = press!

Servo motor1; //1st servo...
Servo motor2; //2nd servo...

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motor1.attach(servoPin1); //Servo 1 in digital 5
  motor2.attach(servoPin2); //Servo 2 in digital 4

  pinMode(ledPin1, OUTPUT);  //output for LED 1
  pinMode(ledPin2, OUTPUT);  //output for LED 2
    ; //Sets LED on
  digitalWrite(ledPin2, HIGH); //Sets LED on
  motor1.write(0); //Sets motor to 0
  motor2.write(0); //Sets motor to 0
}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, inches, cm;

  // Transducer set up
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);

  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);
  inches = microsecondsToInches(duration);
  Serial.print(inches);
  Serial.print("in, ");
  Serial.println();

  delay(100);

  if (inches > 20) //if distance is greater than 20 inches set motors to 0
  {
    motor1.write(0);
    motor2.write(0);
    Serial.println("Sub 1");
    delay(15);
  }
  if (inches < 20 && inches > 10) //if distance is greater than 10 inches but less than 20 set motors to 45
  {

    motor1.write(45);
    motor2.write(45);
    Serial.println("Sub 2");
    delay(15);
  }
  if (inches < 10) //if distance is greater than 10 inches set motors to 90
  {
    motor1.write(90);
    motor2.write(90);
    Serial.println("Sub 3");
    delay(15);
  }
}

//Convert
long microsecondsToInches(long microseconds)

{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second). This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PI...
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
