//
// Created by gpereira on 4/30/18.
//

#include <ctime>
#include "Actuator.h"
#include "Config.h"
#include "Mote.h"
#include "Historic.h"

bool Actuator::ActuatorExists(string device, int room_id) {
  Database db;
  std::vector<std::string> info = db.Select("actuator", "room_id = " + std::to_string(room_id) + " AND device = '" +
                                                        device + "'")[0];
  return !info.empty();
}

void Actuator::setActuators(Data data) {
  Historic hist;
  Mote mote;
  hist.room_id = mote.CheckRoom(data.moteId);
  hist.mote_id = data.moteId;
  Config conf(hist.room_id);
  Actuator act;
  if (act.ActuatorExists("AC", hist.room_id) &&
      (data.temperature < conf.temp_min || data.temperature > conf.temp_max))
    hist.ac = 1;
  else hist.ac = 0;
  if (act.ActuatorExists("BLINDS", hist.room_id) && (data.visibleLight > conf.lum_min)) hist.blinds = 1;
  else hist.blinds = 0;
  if (act.ActuatorExists("DEHUM", hist.room_id) && (data.humidity > conf.hum_max)) hist.dehum = 1;
  else hist.dehum = 0;
  if (act.ActuatorExists("LIGHTS", hist.room_id) && (data.visibleLight > conf.hum_max) &&
      data.infraredLight > conf.infra_min)
    hist.lights = 1;
  else hist.lights = 0;

  hist.temp = data.temperature;
  hist.hum = data.humidity;
  hist.lum = data.visibleLight;
  hist.infra = data.infraredLight;
  hist.timestamp = to_string(std::time(0));
  hist.Submit();
}
