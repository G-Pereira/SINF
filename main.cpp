#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  int id;
  int battery;
  int temperature;
  int humidity;
  int visibleLight;
  int infraredLight;
} sensor;

int main() {
  sensor devices[5];
  char *buf = NULL;
  size_t len = 0;
  char *token;
  const char delimiter[2] = " ";
  FILE *file = fopen("/dev/pts/4", "r");
  while(1){
    getline(&buf, &len, file);
    printf("\n\nNEW SENSOR DATA\n\n");
    token = strtok(buf, delimiter);
    for(int i = 0; token != NULL; i++ ) {
      switch(i){
        case 5:
        char * folowingToken = strtok(NULL, delimiter);
        strcat(token, folowingToken);
        int id = strtol(token, NULL,16);
        i++;
        break;
        }
        token = strtok(NULL, delimiter);
      }
    }
  return 0;
}