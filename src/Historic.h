#ifndef SINF_HISTORIC_H
#define SINF_HISTORIC_H

#include <string>

class Historic {
  std::string mote_id;
  std::string room_id;
  std::string timestamp;
  int temp;
  int hum;
  int lum;
  int infra;
  int ac;
  int blinds;
  int dehum;
  int lights;
};


#endif //SINF_HISTORIC_H
