#ifndef Votaciones_h
#define Votaciones_h


#include "MQTT.h"
MQTT myMqtt;

#include "MyRTCLib.h"
DS1307_RTC myrtc;

#include "Actuadores.h"
actuadores ACT;

#include "Menu.h"
Menu myMenu;

#include "JSON.h"
json_factory fac;

#include "MicroSD.h"
MicroSD MSD;

#include "Tasks.h"
millis_tasks TSK;

#include "PROXIMITY.h"  
Proximity proximity;




#endif 