#include "InAnalog.h"

int pin = A0;
int par_raw_min = 103; //inicio em 0.5 v
int par_raw_max = 920; //fim em 4.5 v
float par_esc_min = 0;
float par_esc_max = 122; //1.2 MPa
float par_alr_HH = 100;//maxima pressão de cano PVC
float par_alr_H = 50; //maximo valor recomendado
float par_alr_L = 10;// minimo valor recomendado
float par_alr_LL = 0.5;// falta dágua
float par_offset = 0;



void setup() {
  
Serial.begin(9600);

}

void loop() {

InAna PIT_1( pin,  par_raw_min,  par_raw_max,  par_esc_min, par_esc_max, par_alr_HH, par_alr_H,  par_alr_L,  par_alr_LL,  par_offset);
float x = PIT_1.st_val_eng();
float y = PIT_1.st_val_perc();
int z = PIT_1.st_val_geral();
PIT_1.cm_val_man(5);
PIT_1.cm_geral(0b0000000000000000);
Serial.println(x);
Serial.println(y);
Serial.println(z,BIN);
Serial.println(" ");
Serial.println(" ");
delay(1000);

}
