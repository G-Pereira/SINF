#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
  int id;
  float battery;
  float temperature;
  float humidity;
  float visibleLight;
  float infraredLight;
} sensor;

int main() {
  sensor devices[5];
  char *buf = NULL;
  size_t len = 0;
  char *token;
  const char delimiter[2] = " ";
  FILE *file = fopen("/dev/pts/3", "r");
  while(1){
    getline(&buf, &len, file);
    printf("\nNEW SENSOR DATA\n");
    token = strtok(buf, delimiter);
    int id;
    int reading;
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
          devices[id-1].battery = strtol(token, NULL,16)/4096*1.5;
          printf("Battery: %d\n", devices[id-1].battery);
          i++;
          break;
        case 12:
          strcat(token, strtok(NULL, delimiter));
          devices[id-1].temperature = strtol(token, NULL,16)*0.01-39.6;
          printf("Temperature: %d\n", devices[id-1].temperature);
          i++;
          break;
        case 14:
          strcat(token, strtok(NULL, delimiter));
          reading = strtol(token, NULL,16);
          devices[id-1].humidity = -2.0468+0.0367*reading-1.5955*pow(10,-6)*pow(reading,2);
          printf("Humidity: %d\n", devices[id-1].humidity);
          i++;
          break;
        case 16:
          strcat(token, strtok(NULL, delimiter));
          devices[id-1].visibleLight = strtol(token, NULL,16)/4096*0.625*1.5*pow(10,6)/100;
          printf("Visible Light: %d\n", devices[id-1].visibleLight);
          i++;
          break;
        case 18:
          strcat(token, strtok(NULL, delimiter));
          devices[id-1].infraredLight = strtol(token, NULL,16)/4096*0.769*1.5*pow(10,5)/100;
          printf("Infrared Light: %d\n", devices[id-1].infraredLight);
          i++;
          break;
        }
        token = strtok(NULL, delimiter);
      }
    }
  return 0;
}