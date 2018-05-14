#include <fstream>
#include <iostream>
#include "Database.h"
#include "Data.h"
#include "Actuator.h"
#include "Config.h"

using namespace std;

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Wrong usage!\nUsage: ./a.out /dev/pts/x\n");
    return 0;
  }
  printf("Welcome to HomeAuto!\nSystem Starting up...\n");
  std::ifstream fileSensors;
  fileSensors.open(argv[1]);

  while (1) {
    Actuator act;
    char reading[100] = "";
    fileSensors.getline(reading, 100);
    Data data(reading);
    data.moteId -= 1;
    act.setActuators(data);
  }

  fileSensors.close();
  return 0;
}

