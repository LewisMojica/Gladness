#ifndef Timer_h
#define Timer_h
#include <Arduino.h>

class Timer
{
  private:
  unsigned long _interval;            //intervalo del timer
  unsigned long _pre_millis;          //milllis de referencia
  byte _init_and_initOn; //initOn is the bit in the position 7
  public:
  Timer(unsigned long interval);      //constructor
  void init();                          //funcion que habilita el timer para que retorne un 1 y resetea el timer

  void initOn();
  
  bool check ();                        //funcion que retorna el tiempo que falta para que activie el timer, pero sin resetearlo en ninguna circunstancia

  bool read ();                         //fucion que retorna el estado del timer, si devuelve un true entonces el timer se resetea*/

  void reset ();                        //funcion que comienza la cuenta desde el momento en que se llama

  void end();                           //funcion deshabilita el timer a retornar 1

  bool isRunning();                      //retorna true si el timer esta contando, es decir, si ha sido inicializado y no ha sido terminado

  void setInterval(unsigned long interval);

};


#endif
