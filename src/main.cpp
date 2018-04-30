#include <iostream>
#include <cmath>
#include <thread>
#include <fstream>
#include "Database.h"

pthread_t dataThread, actuatorsThread;

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Wrong usage!\nUsage: ./a.out /dev/pts/x /dev/pts/y\n");
    return 0;
  }
  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "w");
  Database db("sinfa23", "eVrzWLCM");

  fclose(in);
  fclose(out);
  return 0;
}


