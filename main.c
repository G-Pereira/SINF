#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

#define TEMP_LOW 15
#define TEMP_HIGH 25
#define HUM_LOW 60
#define HUM_HIGH 85
#define LIGHT_TRESH 200
#define INFRA_TRESH 350

typedef struct {
  int id;
  double battery;
  double temperature;
  double humidity;
  double visibleLight;
  double infraredLight;
} sensor;

sensor *devices;
pthread_t dataThread, actuatorsThread;

void *readData(void *f);

void *defineActuators(void *f);

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Wrong usage!\nUsage: ./a.out /dev/pts/x /dev/pts/y\n");
    return 0;
  }
  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "w");
  while (1) {
    pthread_create(&dataThread, NULL, readData, (void *) in);
    pthread_create(&actuatorsThread, NULL, defineActuators, (void *) out);
    pthread_join(dataThread, NULL);
    pthread_join(actuatorsThread, NULL);
  }
  fclose(in);
  fclose(out);
  return 0;
}

void *readData(void *f) {
  FILE *file = (FILE *) f;
  char *buf = NULL;
  size_t len = 0;
  char *token;
  const char delimiter[2] = " ";
  int id = 0;
  getline(&buf, &len, file);
  token = strtok(buf, delimiter);
  for (int i = 0; token != NULL; i++) {
    switch (i) {
      case 5:
        strcat(token, strtok(NULL, delimiter));
        id = (int) strtol(token, NULL, 16);
        if (sizeof(devices) / sizeof(sensor) < id) {
          devices = (sensor *) realloc(devices, sizeof(sensor) * id);
        }
        devices[id - 1].id = id;
        i++;
        break;
      case 10:
        strcat(token, strtok(NULL, delimiter));
        devices[id - 1].battery = strtol(token, NULL, 16) / 4096 * 1.5;
        i++;
        break;
      case 12:
        strcat(token, strtok(NULL, delimiter));
        devices[id - 1].visibleLight = strtol(token, NULL, 16) / 4096 * 0.625 * 1.5 * pow(10, 6) / 100;
        i++;
        break;
      case 14:
        strcat(token, strtok(NULL, delimiter));
        devices[id - 1].infraredLight = strtol(token, NULL, 16) / 4096 * 0.769 * 1.5 * pow(10, 5) / 100;
        i++;
        break;
      case 16:
        strcat(token, strtok(NULL, delimiter));
        devices[id - 1].temperature = strtol(token, NULL, 16) * 0.01 - 39.6;
        i++;
        break;
      case 18:
        strcat(token, strtok(NULL, delimiter));
        double reading = strtol(token, NULL, 16);
        devices[id - 1].humidity = -2.0468 + 0.0367 * reading - 1.5955 * pow(10, -6) * pow(reading, 2);
        i++;
        break;
    }
    token = strtok(NULL, delimiter);
  }
  printf("New Data has been read\n");
}

void *defineActuators(void *f) {
  FILE *file = (FILE *) f;
  char *buf = NULL;
  for (int i = 0; i < sizeof(devices) / sizeof(sensor); i++) {
    printf("%d", i);
    if (i == 0) {
      strcat(buf, "[[0,102,0],");
    } else if (i == 1) {
      strcat(buf, "[255,128,0],");
    } else if (i == 2) {
      strcat(buf, "[0,0,153],");
    } else if (i == 3) {
      strcat(buf, "[255,0,127],");
    } else if (i == 4) {
      strcat(buf, "[0,255,0],");
    }
    if (devices[i].temperature < TEMP_LOW) { //ativar aquecedor
      strcat(buf, "[255,0,0],");
    } else
      strcat(buf, "[0,0,0],");
    if (devices[i].temperature > TEMP_HIGH) { //ativar ar condicionado
      strcat(buf, "[0,0,255],");
    } else
      strcat(buf, "[0,0,0],");
    if (devices[i].humidity > HUM_HIGH) { //ativar deshumidificador
      strcat(buf, "[0, 255, 255],");
    } else
      strcat(buf, "[0,0,0],");
    if (devices[i].visibleLight < LIGHT_TRESH && devices[i].infraredLight > INFRA_TRESH) { //ligar as luzes
      strcat(buf, "[255, 255, 255],");
    }
    if (devices[i].infraredLight < INFRA_TRESH) { //lampadas off
      strcat(buf, "[0,0,0],");
    }
    if (i == (sizeof(devices) / sizeof(sensor)) - 1) {
      if (devices[i].visibleLight > LIGHT_TRESH) { //ligar as cortinas
        strcat(buf, "[255,255,0]]");
      } else
        strcat(buf, "[0,0,0]]");
    } else {
      if (devices[i].visibleLight > LIGHT_TRESH) { //ligar as cortinas
        strcat(buf, "[255,255,0],");
      } else
        strcat(buf, "[0,0,0],");
    }
  }
  fputs(buf, file);
}
