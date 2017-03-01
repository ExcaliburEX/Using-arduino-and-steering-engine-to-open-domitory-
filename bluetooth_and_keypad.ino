#include <Password.h>
#include <Keypad.h>
#include <Servo.h> //使用舵机
Password password = Password( "132978" ); //解锁密码
Servo servo; //声明 servo
const byte ROWS = 4; // 四行
const byte COLS = 4; // 四列

// 定义键盘
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
int pos = 0;    //循环变量 （角度）
int ReceiveByte=0;
//行
byte rowPins[ROWS] = { 9,8,7,6 };
//列
byte colPins[COLS] = { 5,4,3,2 };

// 建立键盘
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
Serial.begin(9600);
servo.write(0);

servo.attach(10); //舵机digital pin 9

//舵机
keypad.addEventListener(keypadEvent); //增加对键盘的侦听
}

void loop(){
  if (Serial.available() > 0) {
  ReceiveByte=Serial.read();
  switch(ReceiveByte){
      case 0x10:
      for(pos = 0; pos < 180; pos += 5)  // 0-180正转 
  {                                 
    servo.write(pos);              // 设置电机转角为 pos 度
    delay(15);                       // 休息
  } 
 
  for(pos = 180; pos>=1; pos-=5.)     
  {                                
    servo.write(pos);              
    delay(15);                        
  } 
  break;
    }
  }
keypad.getKey();
}
//注意一些特殊的事件
void keypadEvent(KeypadEvent eKey){
switch (keypad.getState()){
case PRESSED:

Serial.print("Enter: ");
Serial.println(eKey);
delay(10);

switch (eKey){
case 'A': checkPassword(); delay(1); break;
case 'B': password.reset(); delay(1); break;
default: password.append(eKey); delay(1);
}
}
}


void checkPassword(){

if (password.evaluate()){
password.reset();delay(1);
Serial.println("Accepted");//如果密码正确开锁
//如果开始工作，运行以下代码
for(pos = 0; pos < 180; pos += 5)  // 0-180正转 
  {                                 
    servo.write(pos);              // 设置电机转角为 pos 度
    delay(15);                       // 休息
  } 
  for(pos = 180; pos>=1; pos-=5)
  {                              
    servo.write(pos);              
    delay(15);                        
  } 

}else{
Serial.println("Denied");
password.reset();delay(1);//如果密码错误保持锁定
//如果没有开始工作，运行以下代码
}}

