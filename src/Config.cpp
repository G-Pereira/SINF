#include <iostream>
#include <fstream>
#include "Config.h"
#include "Database.h"
#include <nlohmann/json.hpp>

using namespace nlohmann;

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
  //CheckNew();
}

void Config::CheckNew() {
  char configRead[60] = "";
  std::ifstream fileConfigs;
  fileConfigs.open("/home/gpereira/Documents/FEUP/3/SINF/SINF/configs/SensorRules.json");

  json j;

  fileConfigs >> j;

  for (auto &element : j) {
    for (auto &room : element) {
      string str = room["name"];
      Database db;
      int r_id = stoi(db.Select("room", "name = '" + str + "'")[0][0]);
      std::vector<std::string> results;
      results = db.Select("configs", "room_id = " + to_string(r_id))[0];
      string temp_min = room["temp_min"];
      string temp_max = room["temp_max"];
      string hum_max = room["hum_max"];
      string lum_min = room["lum_min"];
      string infra_min = room["infra_min"];
      if (r_id != stoi(results[0]) || stof(temp_min) != stof(results[2]) ||
          stof(temp_max) != stof(results[3]) ||
          stof(hum_max) != stof(results[4]) ||
          stof(lum_min) != stof(results[5]) ||
          stof(infra_min) != stof(results[6])) {
        db.Insert("configs", "room_id, time_change_conf, temp_min, temp_max, hum_max, lum_min, infra_min",
                  to_string(r_id) + ", " + to_string(std::time(0)) + ", " + temp_min + ", " + temp_max + ", " +
                  hum_max + ", " + lum_min + ", " + infra_min);
      }
    }
  }
  fileConfigs.close();
}


