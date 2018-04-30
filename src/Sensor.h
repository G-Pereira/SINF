#ifndef SINF_SENSOR_H
#define SINF_SENSOR_H

#include <string>

class Sensor {
public:
  int id;
  std::string mote_id;
  std::string type;

  void readData(void * f);
  void defineActuators(void * f);
  Sensor get();
};


#endif //SINF_SENSOR_H
