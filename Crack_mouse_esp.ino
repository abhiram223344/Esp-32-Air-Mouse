#include <BleCombo.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
const int l = 33;
const int r = 33;
const int b2 = 13;
const int b1 = 15;
const int fn = 12;
const int b3 = 27;
const int b4 = 14;
int mouseClickFlag = 0;

long lastDebounceTime1 = 0;  // the last time the output pin was toggled
long lastDebounceTime2 = 0;  
long lastDebounceTime3 = 0;  
long lastDebounceTime4 = 0;
long lastDebounceTimel = 0; 
long lastDebounceTimer = 0;
long lastDebounceTimefn = 0;
long debounceDelay = 500;    // the debounce time; increase if the output flickers





//Set the old button state to be LOW/false; which means not pressed
boolean oldPinState1 = LOW;
boolean oldPinState2 = LOW;
boolean oldPinState3 = LOW;
boolean oldPinState4 = LOW;
boolean oldPinStatel = LOW;
boolean oldPinStater = LOW;
boolean oldPinStatefn = LOW;

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
int vx, vy;


void setup() {
  Serial.begin(115200);
  Serial.println(" Crack_mouse Starting work!");
  Keyboard.begin();
  Mouse.begin();
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) { while (1); }
  
  pinMode(l, INPUT_PULLDOWN);
  pinMode(r, INPUT_PULLDOWN);
  pinMode(b2, INPUT_PULLDOWN);
  pinMode(b1, INPUT_PULLDOWN);
  pinMode(fn, INPUT_PULLDOWN);
  pinMode(b3, INPUT_PULLDOWN);
  pinMode(b4, INPUT_PULLDOWN);
}

void loop() {
   mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  vx = (gx+100)/150;  // change 300 from 0 to 355
  vy = -(gz-100)/150; // same here about "-100"  from -355 to 0

  Serial.print("gx = ");
  Serial.print(gx);
  Serial.print(" | gz = ");
  Serial.print(gz);
  
  Serial.print("        | X = ");
  Serial.print(vx);
  Serial.print(" | Y = ");
  Serial.println(vy);
  
  Mouse.move(vx, vy);
  
  delay(20);

  if(Keyboard.isConnected()) {

    if (digitalRead(b2) == HIGH) {
      //If the button pin is pressed (since it is pulled down, it is pressed when it is high
      
   if ( (millis() - lastDebounceTime2) > debounceDelay) { 
      if (oldPinState2 == LOW) {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.write('a');
        lastDebounceTime2 = millis(); //set the current time;
        Keyboard.release(KEY_LEFT_CTRL);
      }
      oldPinState2 = HIGH;
      }
    } 
    else {
      oldPinState2 = LOW;
    }
    

    if (digitalRead(b1) == HIGH) {
      //If the button pin is pressed (since it is pulled down, it is pressed when it is high

       if ( (millis() - lastDebounceTime1) > debounceDelay) {
      if (oldPinState1 == LOW) {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.write('c');
        lastDebounceTime1 = millis(); //set the current time;
        Keyboard.release(KEY_LEFT_CTRL);
      }
      oldPinState1 = HIGH;
     }
    }
    else {
      oldPinState1 = LOW;
    }
    
    if (digitalRead(b3) == HIGH) {
      //If the button pin is pressed (since it is pulled down, it is pressed when it is high
      if ( (millis() - lastDebounceTime3) > debounceDelay) {
      if (oldPinState3 == LOW) {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.write('s');
        lastDebounceTime3 = millis(); //set the current time;
        Keyboard.release(KEY_LEFT_CTRL);
      }
      oldPinState3 = HIGH;
     }
    }
    else {
      oldPinState3 = LOW;
    }
    
     if (digitalRead(b4) == HIGH) {
      //If the button pin is pressed (since it is pulled down, it is pressed when it is high
        if ( (millis() - lastDebounceTime4) > debounceDelay) {
      if (oldPinState4 == LOW) {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.write('z');
        lastDebounceTime4 = millis(); //set the current time;
        Keyboard.release(KEY_LEFT_CTRL);
      }
      oldPinState4 = HIGH;
      }
     }
    else {
      oldPinState4 = LOW;
    }
     if ((digitalRead(fn) == HIGH) && (digitalRead(b1)== HIGH)) {
        if ( (millis() - lastDebounceTimefn) > debounceDelay)   {
      
      
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.write('v');
        //lastDebounceTimefn = millis();
        lastDebounceTimefn = millis();
        }
        Keyboard.release(KEY_LEFT_CTRL);
     }
     
      if ((digitalRead(fn) == HIGH) && (digitalRead(b4)== HIGH)) {
         if ( (millis() - lastDebounceTimefn) > debounceDelay)   {
               
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.write('y');
        lastDebounceTimefn = millis();
         }
        Keyboard.release(KEY_LEFT_CTRL);
     }
     if ((digitalRead(fn) == HIGH) && (digitalRead(b3)== HIGH)) {
      //If the button pin is pressed (since it is pulled down, it is pressed when it is high
        if ( (millis() - lastDebounceTimefn) > debounceDelay)   {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_RIGHT_SHIFT);
        Keyboard.write('s');
        lastDebounceTimefn = millis();
         }
        Keyboard.releaseAll();
     }

     
     if (digitalRead(l) == HIGH) { // if the joystick button is pressed
  
    
    Mouse.press(MOUSE_LEFT);  // click the left button down
  }
         else if (digitalRead(l) == LOW ){ // if the joystick button is not pressed
  
    
    Mouse.release(MOUSE_LEFT);  // release the left button
  }
 
   if (digitalRead(r) == HIGH) { // if the joystick button is pressed
  
    
    Mouse.press(MOUSE_RIGHT);  // click the left button down
  }
         else if (digitalRead(l) == LOW ){ // if the joystick button is not pressed
         Mouse.release(MOUSE_RIGHT);  // release the left button
  }
  }
  
}
