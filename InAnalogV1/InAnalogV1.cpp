#include "InAnalogV1.h"
#include "Arduino.h"


InAna::InAna()
{
/*
//valores iniciais

int16_t _par_raw_min = 0;
int16_t _par_raw_max = 1023;
float _par_esc_min = 0;
float _par_esc_max = 1023;
float _par_alr_HH = 0.975 * _par_esc_max; //dois desvios padrões
float _par_alr_H = 0.84 * _par_esc_max; // um desvio padrão
float _par_alr_L = 0.16 * _par_esc_max;
float _par_alr_LL = 0.025 * _par_esc_max ;
float _par_offset = 0;

float _cm_valor_manual = 0;
int16_t _cm_limita = 0;
int16_t _cm_aloca = 0 ;
int16_t _cm_alr_deslig = 0;
int16_t _cm_fal_deslig = 0;
int16_t _cm_hold = 0;
int16_t _cm_modo_man = 0;
int16_t _cm_ack = 0;

float _st_val_eng = 0;*/

}

// Funções de modificação dos valores iniciais

void InAna::par_raw (int16_t par_raw_min, int16_t par_raw_max){
  _par_raw_min = par_raw_min;
  _par_raw_max = par_raw_max;
}

void InAna::par_esc (float par_esc_min, float par_esc_max, float par_offset){
  _par_esc_min = par_esc_min;
  _par_esc_max = par_esc_max;
  _par_offset = par_offset;
}


void InAna::par_alr (float par_alr_HH, float par_alr_H, float par_alr_L, float par_alr_LL){
  _par_alr_HH = par_alr_HH;
  _par_alr_H = par_alr_H;
  _par_alr_L = par_alr_L;
  _par_alr_LL = par_alr_LL;
}


void InAna::cm(int16_t cm_geral, float cm_valor_manual){
  int16_t _cm_limita = 0b0000000000000001&cm_geral;// não usado
  int16_t _cm_aloca = 0b00000000000000010&cm_geral; // não usado
  int16_t _cm_alr_deslig = 0b00000000000000100&cm_geral;
  int16_t _cm_fal_deslig = 0b00000000000001000&cm_geral;
  int16_t _cm_hold = 0b00000000000010000&cm_geral;// não usado
  int16_t _cm_modo_man = 0b00000000000100000&cm_geral;
  int16_t _cm_ack = 0b00000000001000000&cm_geral;
  _cm_valor_manual = cm_valor_manual;
}


float InAna::st_val_eng (int16_t pin, int16_t MA){
  int16_t _pin = pin;
  _ValorAnalogico = analogRead(_pin);

  if (_cm_modo_man != 0)
  {
  _st_val_eng = _cm_valor_manual;
  _st_man=0b0000000000000001;
  }
  else
  {
  float x1 = (_ValorAnalogico - _par_raw_min);
  float x2 = (_par_raw_max - _par_raw_min);
  float x3 = x1 / x2;
  float x4 = (_par_esc_max - _par_esc_min);
  _st_val_inst = x3 * x4 + _par_offset;
  _st_man=0;
  }



  // processamento da média móvel
  _Matriz[_MA_ciclo] = _st_val_inst;

  for (int x=0;x<MA;x++) {

  _SomaMatriz += _Matriz[x];

  }



  if(_Ciclo_1 == 1) {_st_val_eng = _SomaMatriz / MA;} else {_st_val_eng = _SomaMatriz / (_MA_ciclo + 1);}

  _st_val_eng = _SomaMatriz / MA;

  _SomaMatriz = 0;

  _MA_ciclo++;

  if(_MA_ciclo == MA){_MA_ciclo=0;_Ciclo_1 = 1;}

  return   _st_val_eng;
}

float InAna::st_val_inst (){
return _st_val_inst;
}

float InAna::st_val_perc (){
  // processamento de calculo percentual
  _st_val_perc = (_st_val_eng - _par_alr_LL) / (_par_alr_HH - _par_alr_LL);
  return _st_val_perc;
}

int16_t InAna::st_val_geral (){

  // definição dos status digitais
  if (_st_val_eng >= _par_alr_HH){_st_alarm_HH = 0b0000000000010000;}else{_st_alarm_HH = 0;}
  if (_st_val_eng >= _par_alr_H){_st_alarm_H = 0b0000000000100000;}else{_st_alarm_H = 0;}
  if (_st_val_eng <= _par_alr_L){_st_alarm_L = 0b0000000001000000;}else{_st_alarm_L = 0;}
  if (_st_val_eng <= _par_alr_LL){_st_alarm_LL = 0b00000000010000000;}else{_st_alarm_LL = 0;}
  if (_st_alarm_L+_st_alarm_LL+_st_alarm_H+_st_alarm_HH>0){if (_cm_alr_deslig==0) {_alarmeativo=0b0000000000000010;};}
  //aciona alarme se qualquer alarme estiver ativo e o comando de desligar alarme estiver desligado
  if (_alarmeativo>0){if (_cm_fal_deslig==0) {_st_error=0b0000000000000100;};}
  // quando o alarme ativar, e o comando de alarme não estiver desligado,  o valor de error será um
  if (_cm_ack>0){if (_alarmeativo==0) {_st_error=0;};}
  // quando reconhecer o error, ele voltará para zero, desde que não exista alarme ativo


  return _st_man | _alarmeativo | _st_error | _st_hold  | _st_alarm_HH | _st_alarm_H | _st_alarm_L | _st_alarm_LL;
}

boolean InAna::st_alarm_L (){
return _st_alarm_L;
}

boolean InAna::st_alarm_H (){
return _st_alarm_H;
}
