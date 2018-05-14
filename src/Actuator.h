//
// Created by gpereira on 4/30/18.
//

#ifndef SINF_ACTUATOR_H
#define SINF_ACTUATOR_H

#include <string>
#include "Database.h"
#include "Data.h"

class Actuator {
public:
  bool ActuatorExists(string device, int room_id);
  void setActuators(Data data);

private:
  int id;
  int room_id;
  std::string device;
};


#endif //SINF_ACTUATOR_H
