//
// Created by gpereira on 5/7/18.
//

#ifndef SINF_DATA_H
#define SINF_DATA_H

#include <string>

class Data {
public:
  void readData(std::string input);

private:
  int moteId;
  double battery = 0;
  double temperature = 0;
  double humidity = 0;
  double visibleLight = 0;
  double infraredLight = 0;
};


#endif //SINF_DATA_H
