#ifndef SINF_CONFIG_H
#define SINF_CONFIG_H

#include <string>
#include "User.h"

class Config {
public:
  int room_id;
  std::string time_change_conf;
  float temp_min;
  float temp_max;
  float hum_max;
  float lum_min;
  float infra_min;

  Config(int room_id);

  bool updateConfigs(User user, int room_id, std::string timestamp, int);

};


#endif //SINF_CONFIG_H
