#include <fstream>
#include "Database.h"
#include "Data.h"
#include "Historic.h"
#include "Mote.h"

void readData(std::string in);

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Wrong usage!\nUsage: ./a.out /dev/pts/x /dev/pts/y\n");
    return 0;
  }
  printf("Welcome to HomeAuto!\nSystem Starting up...\n");
  std::ifstream fileIn;
  fileIn.open(argv[1]);
  char reading[100];

  Data data;

  while (1) {
    Historic hist;
    Mote mote;
    fileIn.getline(reading, 100);
    data.readData(reading);

    //Config conf(mote.CheckRoom(data.moteId));
    //printf("%f\n", conf.temp_max);
    // Get Configs
    // check if actuator exists
    //if so check config
    // define on/off accordinggly
  }

  fileIn.close();
  return 0;
}

