//
// Created by gpereira on 4/30/18.
//

#ifndef SINF_ACTUATOR_H
#define SINF_ACTUATOR_H

#include <string>

class Actuator {
public:
  bool ActuatorExists(int device, int room_id);

private:
  int id;
  int room_id;
  std::string device;
};


#endif //SINF_ACTUATOR_H
