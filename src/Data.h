//
// Created by gpereira on 5/7/18.
//

#ifndef SINF_DATA_H
#define SINF_DATA_H

#include <string>

class Data {
public:
  Data(std::string input);

  int moteId;
  float battery = 0;
  float temperature = 0;
  float humidity = 0;
  float visibleLight = 0;
  float infraredLight = 0;

private:
};


#endif //SINF_DATA_H
