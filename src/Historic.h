#ifndef SINF_HISTORIC_H
#define SINF_HISTORIC_H

#include <string>

class Historic {
    std::string mote_id;
    std::string room_id;
    std::string timestamp;
    float temp;
    float hum;
    float lum;
    float infra;
    float ac;
    float blinds;
    float dehum;
    float lights;

    void UpdateHistoric(std::string mote_id, std::string room_id, std::string timestamp, float temp, float hum, float lum, float infra, float ac, float blinds, float dehum, float lights);
};

    #endif //SINF_HISTORIC_H
