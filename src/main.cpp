#include <fstream>
#include "Database.h"
#include "Data.h"

void readData(std::string in);

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Wrong usage!\nUsage: ./a.out /dev/pts/x /dev/pts/y\n");
    return 0;
  }
  printf("Welcome to HomeAuto!\nSystem Starting up...\nThis wont take long\n");
  std::ifstream fileIn;
  fileIn.open(argv[1]);
  char reading[100];

  Data data;

  while (1) {
    fileIn.getline(reading, 100);
    std::string s(reading);
    data.readData(s);
  }

  fileIn.close();
  return 0;
}

