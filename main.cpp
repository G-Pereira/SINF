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

int main(int argc, char** argv) {
  sensor* devices;
  char *buf = NULL;
  size_t len = 0;
  char *token;
  const char delimiter[2] = " ";
  int id;
  if(argc <= 1){
    printf("Please Specify Socket to Read\nUsage: ./a.out /dev/pts/x\n");
    return 0;
  }

  FILE *file = fopen(argv[1], "r");
  while(1){
    getline(&buf, &len, file);
    printf("\nNEW SENSOR DATA\n");
    token = strtok(buf, delimiter);

    for(int i = 0; token != NULL; i++ ) {
      switch(i){
        case 5:
          strcat(token, strtok(NULL, delimiter));
          id = strtol(token, NULL,16);
          if(sizeof(devices)/sizeof(sensor)<id){
            devices = (sensor*) realloc(devices, sizeof(sensor)*id);
          }
          devices[id-1].id = id;
          i++;
          printf("ID: %d\n", id);
          break;
        case 10:
          strcat(token, strtok(NULL, delimiter));
          devices[id-1].battery = (float)strtol(token, NULL,16)/4096*1.5;
          printf("Battery: %f\n", devices[id-1].battery);
          i++;
          break;
        case 12:
          strcat(token, strtok(NULL, delimiter));
          devices[id-1].visibleLight = (float)strtol(token, NULL,16)/4096*0.625*1.5*pow(10,6)/100;
          printf("Visible Light: %f\n", devices[id-1].visibleLight);
          i++;
          break;
        case 14:
          strcat(token, strtok(NULL, delimiter));
          devices[id-1].infraredLight = (float)strtol(token, NULL,16)/4096*0.769*1.5*pow(10,5)/100;
          printf("Infrared Light: %f\n", devices[id-1].infraredLight);
          i++;
          break;
        case 16:
          strcat(token, strtok(NULL, delimiter));
          devices[id-1].temperature = (float)strtol(token, NULL,16)*0.01-39.6;
          printf("Temperature: %f\n", devices[id-1].temperature);
          i++;
          break;
        case 18:
          strcat(token, strtok(NULL, delimiter));
          float reading = (float)strtol(token, NULL,16);
          devices[id-1].humidity = -2.0468+0.0367*reading-1.5955*pow(10,-6)*pow(reading,2);
          printf("Humidity: %f\n", devices[id-1].humidity);
          i++;
          break;
        }
        token = strtok(NULL, delimiter);
      }
      for(int i = 0; i < sizeof(devices)/sizeof(sensor);i++){
        if(devices[i].temperature){

        }
      }
    }
  return 0;
}