#include "ControlCCMV1.h"
#include "Arduino.h"


ControlCCM::ControlCCM(boolean par_cmb01_ligado, boolean par_cmb02_ligado, boolean par_cmb01_falha, boolean par_cmb02_falha, boolean par_mont_alr_L, boolean par_jusa_alr_L, boolean par_jusa_alr_H, boolean par_cmb01_remoto, boolean par_cmb02_remoto,int16_t cm_geral)
{


 // 1. PROCESSAMENTO O COMANDO GERAL


 boolean _cm_cmb01_habilitado=((0b0000000000000001&cm_geral)!=0);
 boolean _cm_cmb02_habilitado=((0b0000000000000010&cm_geral)!=0);
 boolean _cm_AutomaticoManual=((0b0000000000000100&cm_geral)!=0);
 boolean _cm_ComandoRemoto=((0b0000000000001000&cm_geral)!=0);
 boolean _cm_cmb01_LigarManual=((0b0000000000010000&cm_geral)!=0);
 boolean _cm_cmb02_LigarManual=((0b0000000000100000&cm_geral)!=0);

//int16_t _cm_AutomaticoManual=0b0000000000000100&cm_geral;
//if (0b0000000000000001&cm_geral!=0){boolean _cm_cmb01_habilitado=true;} else {boolean _cm_cmb01_habilitado=false;}



 // 2. CONTROLE DO MOTOR

 if (_cm_AutomaticoManual) {

 // 2.1 Partida Automática

 if(!par_mont_alr_L&&par_jusa_alr_L&&_cm_ComandoRemoto) // se nivel montante não baixo e nival jusante baixo ou _cm_ComandoRemoto ativado
 {
   if(!par_cmb01_ligado&&!par_cmb02_ligado) // se nenhum motor ligado
   {

 if(_n_partida%2==0 && par_cmb01_remoto && _cm_cmb01_habilitado)// se vez da partidade, motor em remoto e motor habilitado
   {
   if(!par_cmb01_falha) // se não estiver em falha
      {
      if(!par_cmb02_ligado) // se o outro motor não estiver ligado
        {
        _st_cmb01_ligar = true;
        par_cmb01_ligado = true;
        }
      }
   }

 if(_n_partida%2!=0 && par_cmb02_remoto && _cm_cmb02_habilitado)// se vez da partidade, motor em remoto e motor habilitado
   {
   if(!par_cmb02_falha)
      {
      if(!par_cmb01_ligado)
        {
        _st_cmb02_ligar = true;
        par_cmb02_ligado = true;
        }
      }
   }

 _n_partida ++;


   }
  }
 }

// 2.2 Partida em Remoto-Manual

 else
 {

  if(_cm_cmb01_LigarManual&&_cm_cmb01_habilitado){_st_cmb01_ligar = true;}else {_st_cmb01_ligar = false;}
  if(_cm_cmb02_LigarManual&&_cm_cmb02_habilitado){_st_cmb02_ligar = true;}else {_st_cmb02_ligar = false;}

 }

 // 3. CONDIÇÕES DE PARADA DO MOTOR

 if(par_mont_alr_L||par_jusa_alr_H||!_cm_ComandoRemoto) // DESATIVA se montante baixar ou jusante atingir nível ou _cm_ComandoRemoto desativado
 {
 _st_cmb01_ligar = false;
 _st_cmb02_ligar = false;
 }

 if(par_cmb01_falha||!par_cmb01_remoto) // deve parar quando não remoto, pois o controle deverá ser apenas pelas botoeiras locais
 {
 _st_cmb01_ligar = false;
 }

 if(par_cmb02_falha||!par_cmb02_remoto)
 {
 _st_cmb02_ligar = false;
 }

// PROCESSAMENTO DE STATUS GERAL
_ccm_st_geral = 0;
 if (par_cmb01_ligado){_ccm_st_geral = _ccm_st_geral|1;}else {_ccm_st_geral = _ccm_st_geral&~1;} //bit 0: status motor 01 ligado
 if (par_cmb02_ligado){_ccm_st_geral = _ccm_st_geral|2;}else {_ccm_st_geral = _ccm_st_geral&~2;} //bit 1: status motor 02 ligado
 if (par_cmb01_falha){_ccm_st_geral = _ccm_st_geral|4;}else {_ccm_st_geral = _ccm_st_geral&~4;} // bit 2: alarme de falha motor 01
 if (par_cmb01_falha){_ccm_st_geral = _ccm_st_geral|8;}else {_ccm_st_geral = _ccm_st_geral&~8;} // bit 3: alarme de falha motor 02
 if (par_cmb01_remoto){_ccm_st_geral = _ccm_st_geral|16;}else {_ccm_st_geral = _ccm_st_geral&~16;} // bit 4: status de local/remoto motor 01
 if (par_cmb02_remoto){_ccm_st_geral = _ccm_st_geral|32;}else {_ccm_st_geral = _ccm_st_geral&~32;} // bit 5: status de local/remoto motor 02
 if (_cm_AutomaticoManual){_ccm_st_geral = _ccm_st_geral|64;}else {_ccm_st_geral = _ccm_st_geral&~64;} // bit 6: status de automático/manual
//_ccm_st_geral = _ccm_st_geral|64;

}

 // 4. METODOS


boolean ControlCCM::st_cmb01_ligar (){
return _st_cmb01_ligar;
}

boolean ControlCCM::st_cmb02_ligar (){
return _st_cmb02_ligar;
}

int16_t ControlCCM::n_partidas (){
return _n_partida;
}

int16_t ControlCCM::ccm_st_geral (){

return _ccm_st_geral;
}
