//
// Created by gpereira on 4/30/18.
//

#include "Actuator.h"

bool Actuator::ActuatorExists(int device, int room_id) {
  Database db;
  std::vector<std::string> info = db.Query(
    "SELECT * FROM homeauto.actuator WHERE room_id = " + std::to_string(room_id) + " AND device = " +
    std::to_string(device))[0];
  return !info.empty();
}
