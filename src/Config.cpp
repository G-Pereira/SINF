#include <iostream>
#include "Config.h"
#include "Database.h"


bool Config::updateConfigs(User user, int room_id, std::string timestamp, int) {
  return false;
}

Config::Config(int r_id) {
  Database db;
  std::vector<std::string> results;
  results = db.QuerySingle("SELECT * FROM homeauto.configs WHERE room_id = " + r_id);
  room_id = stoi(results[0]);
  time_change_conf = results[1];
  temp_min = stof(results[2]);
  temp_max = stof(results[3]);
  hum_max = stof(results[4]);
  lum_min = stof(results[5]);
  infra_min = stof(results[6]);
}
