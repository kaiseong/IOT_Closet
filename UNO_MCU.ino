#include <SoftwareSerial.h>
#include <Servo.h>

#define Servo_Pin1 11
#define Servo_Pin2 12
#define Servo_Pin3 13
int cw =8;
int clk=7 ;
int  led =9;
int mode=0;
SoftwareSerial serial_mcu(5,6); //RX, TX Serial 통신 연결
Servo servo1; Servo servo2; Servo servo3; // 서보 객체 3개 생성

void step_cw(int cw, int clk)
{
    digitalWrite(cw,HIGH); 
  for(int x = 0; x < 228;x++) {
    digitalWrite(clk,HIGH); 
    delayMicroseconds(2000); 
    digitalWrite(clk,LOW); 
    delayMicroseconds(2000); 
  }      
}

void step_ccw(int cw, int clk)
{
    digitalWrite(cw,LOW);
     for(int x = 0; x <228; x++) {
    digitalWrite(clk,HIGH); 
    delayMicroseconds(2000); 
    digitalWrite(clk,LOW); 
    delayMicroseconds(2000); 
     }    
}
// 파란색 서보 들어올리기
void servo1_up()
{
    for(int i=5;i<=40;i+=3)
    {
       servo1.write(i);
       delay(70);
    }
}

void servo1_down()
{
    for(int k=40;k>=5;k-=3)
    {
       servo1.write(k);
       delay(70);
    }       
}



// 검은색 서보 옷걸이 쪽으로
void servo2_left(int n)
{
    for(int i=180;i>=n;i-=5)
    {
       servo2.write(i);
       delay(70);
    }
}

void servo2_right()
{
    for(int i=80;i<=180;i+=5)
    {
       servo2.write(i);
       delay(70);
    }
}

void pick_up()
{
    servo1.write(5);
    delay(1000);
    for(int j=0;j<4;j++)
    {
        step_cw(cw,clk);
        delay(1000);
    }
    servo2_left(80); delay(1000);
    servo1_up(); delay(1000);
    servo2_right(); delay(1000);
    servo1_down(); delay(1000);
    
    servo3.write(160);
}

void put_down()
{
    servo3.write(0);
    servo1_up(); delay(1000);
    servo2_left(90); delay(1000);
    servo1_down(); delay(1000);
    servo2_right(); delay(1000);
    servo1_down(); delay(1000);
}

void LEDON(int led)
{
    digitalWrite(led,HIGH);
}
void LEDOFF(int led)
{
    digitalWrite(led,LOW);
}


void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    serial_mcu.begin(115200);
    pinMode(cw,OUTPUT);
    pinMode(clk,OUTPUT);
    pinMode(led,OUTPUT);
    servo1.attach(Servo_Pin1);
    servo2.attach(Servo_Pin2);
    servo3.attach(Servo_Pin3);

    servo1.write(5);
    servo2.write(180);
    servo3.write(0);
}

void loop() {
    // put your main code here, to run repeatedly:
  
    if(serial_mcu.available())
       { mode=serial_mcu.read();
    Serial.println(mode);
   //     running=true;
       
    switch(mode)
    {
        case 1: // 오른쪽으로 1칸
        step_cw(cw,clk);
       delay(1000);
        break;
        case 2: // 왼쪽으로 1칸
        step_ccw(cw,clk);
        delay(1000);
        break;
        case 3: // 옷 빼내기
        pick_up();
        break;
        case 4:
        put_down(); // 옷 다시 걸어두기
        break;
        case 5:
        LEDON(led); // 조명 켜기
        break;
        case 6: // 조명 끄기
        LEDOFF(led);
        break;
        default:
        delay(100);        
        mode=0;
    }
       }   
}   
