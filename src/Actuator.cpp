//
// Created by gpereira on 4/30/18.
//

#include "Actuator.h"

bool Actuator::ActuatorExists(string device, int room_id) {
  Database db;
  std::vector<std::string> info = db.Select("actuator", "room_id = " + std::to_string(room_id) + " AND device = '" +
                                                        device + "'")[0];
  return !info.empty();
}
