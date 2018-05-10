//
// Created by gpereira on 5/7/18.
//

#include <vector>
#include <boost/algorithm/string.hpp>
#include <cmath>
#include <iostream>
#include "Data.h"

Data::Data(std::string input) {
  std::vector<std::string> fields;
  boost::split(fields, input, boost::is_any_of(" "));

  moteId = std::stoi(fields[5] + fields[6]);
  battery = (float) std::stoi(fields[10] + fields[11], 0, 16) * 1.5 / 4096;
  if (battery <= 0) return;
  visibleLight = (float) std::stoi(fields[12] + fields[13], 0, 16) * pow(10, 6) * 1.5 / 100 / 4096 * 0.625;
  infraredLight = (float) std::stoi(fields[14] + fields[15], 0, 16) * 1.5 / 100 * 0.769 / 4096 * 1000000;
  temperature = (float) std::stoi(fields[16] + fields[17], 0, 16) * 0.01 - 39.6;
  humidity = -2.0468 + 0.0367 * (float) std::stoi(fields[18] + fields[19], 0, 16) -
             1.5955 * pow(10, -6) * pow((float) std::stoi(fields[18] + fields[19], 0, 16), 2);
}