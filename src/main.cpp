#include <fstream>
#include <iostream>
#include "Database.h"
#include "Data.h"
#include "Actuator.h"

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
    Actuator act;
    char reading[100] = "";
    fileIn.getline(reading, 100);
    Data data(reading);
    data.moteId -= 1;
    act.setActuators(data);
  }

  fileIn.close();

  return 0;
}

