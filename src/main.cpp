#include <iostream>
#include <cmath>
#include <pthread.h>
#include <fstream>
#include "Database.h"
#include "Sensor.h"

#define TEMP_LOW 24
#define TEMP_HIGH 27
#define HUM_HIGH 40
#define LIGHT_TRESH 380
#define INFRA_TRESH 330

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Wrong usage!\nUsage: ./a.out /dev/pts/x /dev/pts/y\n");
    return 0;
  }
  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "w");
  Database db("sinfa23", "eVrzWLCM");

  Sensor sensor;

  while (1) {
    sensor.readData(in);
    sensor.defineActuators(out);
  }

  fclose(in);
  fclose(out);
  return 0;
}


