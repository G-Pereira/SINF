#ifndef SINF_CONFIG_H
#define SINF_CONFIG_H

#include <string>
#include "Room.h"

class Config {
public:
  int room_id;
  int temp_min;
  int temp_max;
  int hum_max;
  int lum_min;
  int infra_min;
  std::string time_change_conf;
};


#endif //SINF_CONFIG_H
