//
// Created by gpereira on 5/7/18.
//

#include <vector>
#include <boost/algorithm/string.hpp>
#include <cmath>
#include <iostream>
#include "Data.h"

void Data::Data(std::string input) {
  std::vector<std::string> fields;
  boost::split(fields, input, boost::is_any_of(" "));

  moteId = std::stoi(fields[5] + fields[6]);
  battery = std::stod(fields[10] + fields[11]) * 1.5 / 4096;
  if (battery <= 0) return;
  visibleLight = std::stod(fields[12] + fields[13]) * pow(10, 6) * 1.5 / 100 / 4096 * 0.625;
  infraredLight = std::stod(fields[14] + fields[15]) * 1.5 / 100 * 0.769 / 4096;
  temperature = std::stod(fields[16] + fields[17]) * 0.01 - 39.6;
  humidity = -2.0468 + 0.0367 * std::stod(fields[18] + fields[19]) -
             1.5955 * pow(10, -6) * pow(std::stod(fields[18] + fields[19]), 2);
}