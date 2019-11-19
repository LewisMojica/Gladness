#include <Arduino.h>
#include <ESC.h>
#include <Timer.h>

ESC esc_left,esc_right;

Timer com_time_out(1000); //si tardan mas del timepo especificado se concidera que la conexion BT se ha perdido
Timer init_delay(5000);   //tiempo que tarda el robot en comenzar a avanzar luego de que el switch de control es activado
Timer led_blink(200);

//////HARDWARE STATE//////
byte dir,go,puff,speed,rev;

////functions///
//lee los valores en buffer y actualiza el estado del hardware
bool updateData();
//muestra los valores de los parametros por el monitor serie
void showData();
void UpdateHardware();

/////////////P I N S/////////////////
#define pin_esc_left 9
#define pin_esc_right 10
#define control_switch 7
#define pin_led 13

///////////PARAMETER/////////////////
#define escS_max_throttle_micros 1600
#define escS_min_throttle_micros 1530
#define escS_max_reverse_micros 1350
#define escS_min_reverse_micros 1450
#define turn_diferentian_multiplicator 0.5


//valores del las tres velocidades
#define speed_0 33
#define speed_1 66
#define speed_2 100





void setup() {
  esc_left.attach(pin_esc_left);
  esc_left.setMaxThrottleMicros(escS_max_throttle_micros);
  esc_left.setMinThrottleMicros(escS_min_throttle_micros);
  esc_left.setMinReverseMicros(escS_min_reverse_micros);
  esc_left.setMaxReverseMicros(escS_max_reverse_micros);

  esc_right.attach(pin_esc_right);
  esc_right.setMaxThrottleMicros(escS_max_throttle_micros);
  esc_right.setMinThrottleMicros(escS_min_throttle_micros);  
  esc_right.setMinReverseMicros(escS_min_reverse_micros);
  esc_right.setMaxReverseMicros(escS_max_reverse_micros);

  esc_right.setSpeed(0); //enable esc
  esc_left.setSpeed(0); //enable esc

  Serial.begin(9600);

  com_time_out.init();

  pinMode(13,OUTPUT);
  pinMode(control_switch,INPUT_PULLUP);

}

void loop() {
  digitalWrite(pin_led,LOW);

  rev = 0;
  go = 0;
  dir = 1;
  speed = 0;

  UpdateHardware();
  
  while(true == true){
    updateData();
    if(digitalRead(control_switch) == false){
      delay(100);
      if(digitalRead(control_switch) == false && (updateData() == true)){
        break;
        }
    }
    delay(150);
  }

  init_delay.init();
  led_blink.init();

  while (init_delay.check() == false)
  {
    if(led_blink.read() == true) {digitalWrite(pin_led,!digitalRead(pin_led));}
    if(digitalRead(control_switch) == true ){
      delay(100);
      if(digitalRead(control_switch) == true)
        break;
    }
  }
  digitalWrite(pin_led,HIGH);
  
  rev = 0;
  go = 0;
  dir = 1;
  speed = 0;

  if(Serial.available() > 0){
    int i = Serial.available();
    while(i > 0){
      Serial.read();
      i--;
    }
  }
  delay(200);

  while (false != !false){
    if(digitalRead(control_switch) == true){
      delay(100);
      if(digitalRead(control_switch) == true){
        break;
      }
    }
    UpdateHardware();
    if(updateData() == false){
      break;
    };
    
  }
}



void UpdateHardware(){

  int dirr;
  if(rev == 1) dirr = -1; else dirr = 1;
  
  if(dirr == -1){
    esc_right.enableReverse();
    esc_left.enableReverse();
  }

  if(go == 1){
    if(dir == 0){
      if(speed == 0){
        esc_right.setSpeed(speed_0 * dirr);
        esc_left.setSpeed(0);
      }
      else if (speed == 1){
        esc_right.setSpeed(speed_1 * dirr);
        esc_left.setSpeed(speed_1 * turn_diferentian_multiplicator * dirr);
      }
      else if (speed == 2){
        esc_right.setSpeed(speed_2 * dirr);
        esc_left.setSpeed(speed_2 * turn_diferentian_multiplicator * dirr);
      }

    }
    else if(dir == 1){
      if(speed == 0){
        esc_right.setSpeed(speed_0 * dirr);
        esc_left.setSpeed(speed_0 * dirr);
      }
      else if (speed == 1){
        esc_right.setSpeed(speed_1 * dirr);
        esc_left.setSpeed(speed_1 * dirr);
      }
      else if (speed == 2){
        esc_right.setSpeed(speed_2 * dirr);
        esc_left.setSpeed(speed_2 * dirr);
      }

    }
    else if(dir == 2){
      if(speed == 0){
        esc_right.setSpeed(0);
        esc_left.setSpeed(speed_0 * dirr);
      }
      else if (speed == 1){
        esc_right.setSpeed(speed_1 * turn_diferentian_multiplicator * dirr);
        esc_left.setSpeed(speed_1 * dirr);
      }
      else if (speed == 2){
        esc_right.setSpeed(speed_2 * turn_diferentian_multiplicator * dirr);
        esc_left.setSpeed(speed_2 * dirr);
      }

    }
    
  } else{
    esc_right.setSpeed(0);
    esc_left.setSpeed(0);
  }
}


bool updateData(){
  if(Serial.available() >= 6){
    if(Serial.read() == 42){
      com_time_out.init(); //comienza el conteo de verificaciond de conexion
      dir = Serial.read();
      go = Serial.read();
      puff = Serial.read();
      speed = Serial.read();
      rev = Serial.read();
      
      // showData();
      return true;
    }
  }
  else if(com_time_out.check() == true){
    dir = 1;
    go = 0;
    speed = 0;
    rev = 0;
    // Serial.println("BT com failed");
    return false;
  }
  return true;
}

void showData(){
  Serial.print("dir -> ");
  Serial.print(dir);
  Serial.print("   go -> ");
  Serial.print(go);
  Serial.print("   puff -> ");
  Serial.print(puff);
  Serial.print("   speed -> ");
  Serial.print(speed);
  Serial.print("   rev -> ");
  Serial.println(rev);
}

