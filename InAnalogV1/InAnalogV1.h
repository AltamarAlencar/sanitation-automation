#ifndef InAnalogV1_h
#define InAnalogV1_h
#include "Arduino.h"

class InAna

{
  public: InAna();

  void par_raw (int16_t par_raw_min, int16_t par_raw_max);
  void par_esc (float par_esc_min, float par_esc_max, float par_offset);
  void par_alr (float par_alr_HH, float par_alr_H, float par_alr_L, float par_alr_LL);
  void cm(int16_t cm_geral, float cm_valor_manual);

  float st_val_eng (int16_t pin,int16_t MA);
  float st_val_inst ();
  float st_val_perc ();
  int16_t st_val_geral ();
  boolean st_alarm_L ();
  boolean st_alarm_H ();


  private:
  int16_t _ValorAnalogico;
  int16_t _pin;
  int16_t _par_raw_min;
  int16_t _par_raw_max = 1023;
  float _par_esc_min;
  float _par_esc_max = 1023;
  float _par_alr_HH = 0.975 * _par_esc_max; //dois desvios padrões
  float _par_alr_H = 0.84 * _par_esc_max; // um desvio padrão
  float _par_alr_L = 0.16 * _par_esc_max;
  float _par_alr_LL = 0.025 * _par_esc_max ;
  float _par_offset;

  float _st_val_eng;
  float _st_val_inst;
  float _st_val_perc;
  int16_t _st_man;
  int16_t _alarmeativo;
  int16_t _st_error;
  int16_t _st_hold;// não usado
  int16_t _st_alarm_HH;
  int16_t _st_alarm_H;
  int16_t _st_alarm_L;
  int16_t _st_alarm_LL;


  float _cm_valor_manual;
  int16_t _cm_limita;
  int16_t _cm_aloca;
  int16_t _cm_alr_deslig;
  int16_t _cm_fal_deslig;
  int16_t _cm_hold;
  int16_t _cm_modo_man;
  int16_t _cm_ack;

  float _Matriz[30];
  float _SomaMatriz;
  boolean _Ciclo_1;
  int16_t _MA_ciclo;
};

#endif
