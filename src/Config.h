#ifndef SINF_CONFIG_H
#define SINF_CONFIG_H

#include <string>
#include "User.h"

class Config {
public:
  float room_id;
  float temp_min;
  float temp_max;
  float hum_max;
  float lum_min;
  float infra_min;
  std::string time_change_conf;

  bool updateConfigs(User user, int room_id, std::string timestamp, int);
};


#endif //SINF_CONFIG_H
