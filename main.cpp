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
    printf("\nNEW SENSOR DATA\n");
    token = strtok(buf, delimiter);
    int id;
    for(int i = 0; token != NULL; i++ ) {
      switch(i){
        case 5:
          strcat(token, strtok(NULL, delimiter));
          id = strtol(token, NULL,16);
          devices[id-1].id = id;
          i++;
          printf("ID: %d\n", id);
        break;
        case 10:
        strcat(token, strtok(NULL, delimiter));
        devices[id-1].battery = strtol(token, NULL,16);
        printf("Battery: %d\n", devices[id-1].battery);
        i++;
        break;
        case 12:
        strcat(token, strtok(NULL, delimiter));
        devices[id-1].temperature = strtol(token, NULL,16);
        printf("Temperature: %d\n", devices[id-1].temperature);
        i++;
        break;
        case 14:
        strcat(token, strtok(NULL, delimiter));
        devices[id-1].humidity = strtol(token, NULL,16);
        printf("Humidity: %d\n", devices[id-1].humidity);
        i++;
        break;
        case 16:
        strcat(token, strtok(NULL, delimiter));
        devices[id-1].visibleLight = strtol(token, NULL,16);
        printf("Visible Light: %d\n", devices[id-1].visibleLight);
        i++;
        break;
        case 18:
        strcat(token, strtok(NULL, delimiter));
        devices[id-1].infraredLight = strtol(token, NULL,16);
        printf("Infrared Light: %d\n", devices[id-1].infraredLight);
        i++;
        break;
        }
        token = strtok(NULL, delimiter);
      }
    }
  return 0;
}