#ifndef SINF_HISTORIC_H
#define SINF_HISTORIC_H

#include <string>

class Historic {
public:
  int mote_id;
  int room_id;
  std::string timestamp;
  float temp;
  float hum;
  float lum;
  float infra;
  int ac;
  int blinds;
  int dehum;
  int lights;

  void Submit();
};

#endif //SINF_HISTORIC_H
