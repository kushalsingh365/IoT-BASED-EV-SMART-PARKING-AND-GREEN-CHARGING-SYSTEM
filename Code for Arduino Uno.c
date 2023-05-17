#define REMOTEXY_MODE__ESP8266_HARDSERIAL_CLOUD
#include <RemoteXY.h>
// RemoteXY connection settings
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "project"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
#define REMOTEXY_CLOUD_TOKEN "fe5e99ff099b96585f4bf5503481fc63"
// RemoteXY configurate
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] = // 73 bytes
{ 255,0,0,4,0,66,0,16,31,0,70,16,12,16,9,9,26,37,0,70,
16,27,16,9,9,26,37,0,70,16,41,16,9,9,26,37,0,70,16,55,
16,9,9,26,37,0,129,0,13,8,60,6,17,80,49,32,32,32,32,80,
50,32,32,32,80,51,32,32,32,32,80,52,0 };
// this structure defines all the variables and events of your control interface
struct {
// output variables
uint8_t led_1; // led state 0 .. 1
uint8_t led_2; // led state 0 .. 1
uint8_t led_3; // led state 0 .. 1
uint8_t led_4; // led state 0 .. 1
// other variable
uint8_t connect_flag; // =1 if wire connected, else =0
} RemoteXY;
#pragma pack(pop)
// include the library code:
#include <LiquidCrystal.h>
int x=0;
#include <Servo.h>
int c=0, y=0, z=0;
Servo myservo; // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 0; // variable to store the servo position
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
void setup() {
// set up the LCD's number of columns and rows:
lcd.begin(16, 2);
// Print a message to the LCD.
lcd.setCursor(0, 0);
lcd.print("PARKING");
lcd.setCursor(0, 1);
lcd.print("PROJECT");
delay(3000);
lcd.clear();
pinMode(A1, INPUT); //ir
pinMode(A2, INPUT); //ir
pinMode(A3, INPUT); //ir
pinMode(2, INPUT); //ir
pinMode(A4, INPUT); // in ir
pinMode(A5, INPUT); // out ir
RemoteXY_Init ();
myservo.attach(3);
myservo.write(0);
}
void loop() {
// set the cursor to column 0, line 1
// (note: line 1 is the second row, since counting begins with 0):
RemoteXY_Handler ();
lcd.setCursor(0, 0);
lcd.print("P1:");
if(digitalRead(A1)==0)
{
lcd.print("N");
RemoteXY.led_1 = 1;
}
else
{
lcd.print("Y");
RemoteXY.led_1 = 0;
}
lcd.setCursor(6, 0);
lcd.print("P2:");
if(digitalRead(A2)==0)
{
lcd.print("N");
RemoteXY.led_2 = 1;
}
else
{
lcd.print("Y");
  RemoteXY.led_2 = 0;
}
lcd.setCursor(12, 0);
lcd.print("P3:");
if(digitalRead(A3)==0)
{
lcd.print("N");
RemoteXY.led_3 = 1;
}
else
{
lcd.print("Y");
RemoteXY.led_3 = 0;
}
lcd.setCursor(0, 1);
lcd.print("P4:");
if(digitalRead(2)==0)
{
lcd.print("N");
RemoteXY.led_4 = 1;
}
else
{
lcd.print("Y");
RemoteXY.led_4 = 0;
}
if(digitalRead(A1)==0 && digitalRead(A2)==0 && digitalRead(A3)==0 && digitalRead(2)==0)
{
x=1;
}
else
{
x=0;
}
if(digitalRead(A4)==0 && x==0 && c<4 && y==0)
{
y=1;
c++;
myservo.write(90);
delay(2000);
myservo.write(0);
}
if(digitalRead(A4)==1 && y==1)
{
y=0;
}
if(digitalRead(A5)==0 && c>0 && z==0)
{
38
z=1;
c--;
myservo.write(90);
delay(2000);
myservo.write(0);
}
if(digitalRead(A5)==1 && z==1)
{
z=0;
}
lcd.setCursor(9, 1);
lcd.print("C:");
lcd.print(c);
// print the number of seconds since reset:
}
