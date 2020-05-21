#ifndef ControlCCMV1_h
#define ControlCCMV1_h
#include "Arduino.h"

class ControlCCM

{
  public:
  ControlCCM(
  boolean par_cmb01_ligado,
  boolean par_cmb02_ligado,
  boolean par_cmb01_falha,
  boolean par_cmb02_falha,
  boolean par_mont_alr_L,
  boolean par_jusa_alr_L,
  boolean par_jusa_alr_H,
  boolean par_cmb01_remoto,
  boolean par_cmb02_remoto,
  int16_t cm_geral);


  int16_t n_partidas ();
  boolean st_cmb01_ligar ();
  boolean st_cmb02_ligar ();
  int16_t ccm_st_geral();



  private:
  int16_t _ccm_st_geral;
  int16_t _n_partida;
  boolean _Matriz[60];
  boolean _cm_cmb01_habilitado;
  boolean _cm_cmb02_habilitado;
  boolean _cm_AutomaticoManual;
  boolean _cm_ComandoRemoto;
  boolean _cm_cmb01_LigarManual;
  boolean _cm_cmb02_LigarManual;
  boolean _st_cmb01_ligar;
  boolean _st_cmb02_ligar;

};

#endif
