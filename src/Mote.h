//
// Created by gpereira on 4/29/18.
//

#ifndef SINF_MOTE_H
#define SINF_MOTE_H

#include <string>
#include <vector>
#include "Sensor.h"

class Mote {
public:
    std::string name;
    int room_id;

    void MoteUpdate(std::string name, int room_id);
};


#endif //SINF_MOTE_H
