#include <fstream>
#include <iostream>
#include "Database.h"
#include "Data.h"
#include "Historic.h"
#include "Mote.h"
#include "Config.h"
#include "Actuator.h"
#include <chrono>

using namespace std;

void readData(std::string in);

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Wrong usage!\nUsage: ./a.out /dev/pts/x /dev/pts/y\n");
    return 0;
  }
  printf("Welcome to HomeAuto!\nSystem Starting up...\n");
  std::ifstream fileIn;
  fileIn.open(argv[1]);

  while (1) {
    char reading[100] = "";
    Historic hist;
    Mote mote;
    fileIn.getline(reading, 100);
    Data data(reading);
    hist.mote_id = data.moteId;
    hist.room_id = mote.CheckRoom(data.moteId);
    Config conf(hist.room_id);
    Actuator act;
    if (act.ActuatorExists("AC", hist.room_id) &&
        (data.temperature < conf.temp_min || data.temperature > conf.temp_max))
      hist.ac = 1;
    else hist.ac = 0;
    if (act.ActuatorExists("BLINDS", hist.room_id) && (data.visibleLight > conf.lum_min)) hist.blinds = 1;
    else hist.blinds = 0;
    if (act.ActuatorExists("DEHUM", hist.room_id) && (data.humidity > conf.hum_max)) hist.dehum = 1;
    else hist.dehum = 0;
    if (act.ActuatorExists("LIGHTS", hist.room_id) && (data.visibleLight > conf.hum_max) &&
        data.infraredLight > conf.infra_min)
      hist.lights = 1;
    else hist.lights = 0;

    hist.temp = data.temperature;
    hist.hum = data.humidity;
    hist.lum = data.visibleLight;
    hist.infra = data.infraredLight;
    hist.timestamp = to_string(std::time(0));
    hist.Submit();
  }

  fileIn.close();

  return 0;
}

