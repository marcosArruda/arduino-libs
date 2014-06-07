/*
  IRArruda.h - Biblioteca com todos os IRCodes dos controles remotos de casa :-).
  Created by Marcos Faria Arruda, Aug 25, 2013.
  Biblioteca privada.
*/
#ifndef IRArruda_h
#define IRArruda_h

#include "Arduino.h"

class IRArruda
{
  public:
    IRArruda();
    static const int NET_ONOFF[150];
    static const int NET_CHANNEL_UP[150];
    static const int NET_CHANNEL_DOWN[150];
    static const int NET_PORTAL[150];
    static const int NET_MOSAICO[150];
    static const int NET_INFO[150];
    static const int NET_MUTE[150];
    static const int NET_VOLTAR[150];
    static const int NET_VOL_UP[150];
    static const int NET_VOL_DOWN[150];
    static const int NET_SAIR[150];
    static const int NET_NETTV[150];
    static const int NET_UP[150];
    static const int NET_LEFT[150];
    static const int NET_DOWN[150];
    static const int NET_RIGHT[150];
    static const int NET_OK[150];
    static const int NET_iTV[150];
    static const int NET_AUDIO[150];
    static const int NET_AGORA[150];
    static const int NET_LEGENDA[150];
    static const int NET_MSS_BLUE_BT[150];
    static const int NET_NUMERIC_1[150];
    static const int NET_NUMERIC_2[150];
    static const int NET_NUMERIC_3[150];
    static const int NET_NUMERIC_4[150];
    static const int NET_NUMERIC_5[150];
    static const int NET_NUMERIC_6[150];
    static const int NET_NUMERIC_7[150];
    static const int NET_NUMERIC_8[150];
    static const int NET_NUMERIC_9[150];
    static const int NET_NUMERIC_0[150];
    static const int NET_NUMERIC_FAV[150];
    static const int NET_NUMERIC_MENU[150];
    static const int NET_PPV[150];
    static const int NET_VOD[150];
    static const int NET_MUSICA[150];

    static const int TV_ONOFF[150];
    static const int TV_SOURCE[150];
    static const int TV_HDMI[150];
    static const int TV_VOL_UP[150];
    static const int TV_VOL_DOWN[150];
    static const int TV_CHANNEL_UP[150];
    static const int TV_CHANNEL_DOWN[150];
    static const int TV_NO1[150];
    static const int TV_NO2[150];
    static const int TV_NO3[150];
    static const int TV_NO4[150];
    static const int TV_NO5[150];
    static const int TV_NO6[150];
    static const int TV_NO7[150];
    static const int TV_NO8[150];
    static const int TV_NO9[150];
    static const int TV_NO0[150];
    static const int TV_PreCh[150];
    static const int TV_ChList[150];
    static const int TV_MUTE[150];
    static const int TV_PLAY[150];
    static const int TV_PAUSE[150];
    static const int TV_STOP[150];
    static const int TV_FF[150];
    static const int TV_RW[150];
    static const int TV_UP[150];
    static const int TV_DOWN[150];
    static const int TV_LEFT[150];
    static const int TV_RIGHT[150];
    static const int TV_ENTER[150];
    static const int TV_MENU[150];
    static const int TV_RETURN[150];
    static const int TV_EXIT[150];
    static const int TV_BACK[150];
    void exempleMethod();
  private:
    int _pin;
};

#endif
