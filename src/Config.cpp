#include <iostream>
#include "Config.h"
#include "Database.h"

Config::Config(int r_id) {
  Database db;
  std::vector<std::string> results;
  results = db.Select("configs", "room_id = " + to_string(r_id))[0];
  room_id = stoi(results[0]);
  time_change_conf = results[1];
  temp_min = stof(results[2]);
  temp_max = stof(results[3]);
  hum_max = stof(results[4]);
  lum_min = stof(results[5]);
  infra_min = stof(results[6]);
}
