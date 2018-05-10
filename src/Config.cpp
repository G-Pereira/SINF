#include <iostream>
#include <fstream>
#include "Config.h"
#include "Database.h"
#include <nlohmann/json.hpp>

using namespace nlohmann;

Config::Config(int r_id) {
  Database db;
  std::vector<std::string> results;
  results = db.Select("configs", "room_id = " + to_string(r_id) + " ORDER BY time_change_conf DESC")[0];
  room_id = stoi(results[0]);
  time_change_conf = results[1];
  temp_min = stof(results[2]);
  temp_max = stof(results[3]);
  hum_max = stof(results[4]);
  lum_min = stof(results[5]);
  infra_min = stof(results[6]);
  CheckNew();
}

void Config::CheckNew() {
  std::ifstream fileConfigs;
  fileConfigs.open("/home/gpereira/Documents/FEUP/3/SINF/SINF/configs/SensorRules.json");

  json j;

  fileConfigs >> j;

  for (auto &element : j) {
    for (auto &room : element) {
      string name = room["name"];
      Database db;
      int nroom_id = stoi(db.Select("room", "name = '" + name + "'")[0][0]);
      std::vector<std::string> results;
      results = db.Select("configs", "room_id = " + to_string(nroom_id) + " ORDER BY time_change_conf DESC")[0];
      string ntemp_min = room["temp_min"];
      string ntemp_max = room["temp_max"];
      string nhum_max = room["hum_max"];
      string nlum_min = room["lum_min"];
      string ninfra_min = room["infra_min"];
      if (nroom_id != stoi(results[0]) || stof(ntemp_min) != stof(results[2]) ||
          stof(ntemp_max) != stof(results[3]) ||
          stof(nhum_max) != stof(results[4]) ||
          stof(nlum_min) != stof(results[5]) ||
          stof(ninfra_min) != stof(results[6])) {
        db.Insert("configs", "room_id, time_change_conf, temp_min, temp_max, hum_max, lum_min, infra_min",
                  to_string(nroom_id) + ", to_timestamp(" + to_string(std::time(0)) + "), " + ntemp_min + ", " +
                  ntemp_max + ", " + nhum_max + ", " + nlum_min + ", " + ninfra_min);
      }
    }
  }
  fileConfigs.close();
}


