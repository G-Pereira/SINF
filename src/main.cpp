#include <iostream>
#include <cmath>
#include <pthread.h>
#include <fstream>
#include <cstring>
//#include "Database.h"

#define TEMP_LOW 24
#define TEMP_HIGH 27
#define HUM_HIGH 40
#define LIGHT_TRESH 380
#define INFRA_TRESH 330

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
int ndevices = 0;

void *readData(void *f);

void *defineActuators(void *f);

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Wrong usage!\nUsage: ./a.out /dev/pts/x /dev/pts/y\n");
    return 0;
  }
  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "w");
  //Database db("sinfa23", "eVrzWLCM");

  while (1) {
    pthread_create(&dataThread, NULL, readData, (void *) in);
    pthread_join(dataThread, NULL);
    if (ndevices == 5) {
      pthread_create(&actuatorsThread, NULL, defineActuators, (void *) out);
      pthread_join(actuatorsThread, NULL);
    }
  }

  fclose(in);
  fclose(out);
  return 0;
}

void *readData(void *f) {
  FILE *file = (FILE *) f;
  char *buf;
  size_t len = 0;
  char *token;
  const char delimiter[2] = " ";
  int id = 0;
  getline(&buf, &len, file);
  token = strtok(buf, delimiter);
  double battery, reading;
  for (int i = 0; token != NULL; i++) {
    switch (i) {
      case 5:
        strcat(token, strtok(NULL, delimiter));
        id = (int) strtol(token, NULL, 16);
        if (ndevices < id) {
          devices = (sensor *) realloc(devices, sizeof(sensor) * id);
          ndevices = id;
        }
        devices[id - 1].id = id;
        i++;
        break;
      case 10:
        strcat(token, strtok(NULL, delimiter));
        battery = strtol(token, NULL, 16) * 1.5 / 4096;
        if (battery == 0.0) pthread_exit(NULL);
        devices[id - 1].battery = battery;
        i++;
        break;
      case 12:
        strcat(token, strtok(NULL, delimiter));
        devices[id - 1].visibleLight = strtol(token, NULL, 16) * pow(10, 6) * 1.5 / 100 / 4096 * 0.625;
        i++;
        break;
      case 14:
        strcat(token, strtok(NULL, delimiter));
        devices[id - 1].infraredLight = pow(10, 5) * strtol(token, NULL, 16) * 1.5 / 100 * 0.769 / 4096;
        i++;
        break;
      case 16:
        strcat(token, strtok(NULL, delimiter));
        devices[id - 1].temperature = strtol(token, NULL, 16) * 0.01 - 39.6;
        i++;
        break;
      case 18:
        strcat(token, strtok(NULL, delimiter));
        reading = strtol(token, NULL, 16);
        devices[id - 1].humidity = -2.0468 + 0.0367 * reading - 1.5955 * pow(10, -6) * pow(reading, 2);
        i++;
        break;
    }
    token = strtok(NULL, delimiter);
  }
}

void *defineActuators(void *f) {
  FILE *file = (FILE *) f;
  char buf[500] = "";
  for (int i = 0; i < ndevices; i++) {
    printf(
      "New Sensor:\nID: %d\nBattery Level: %lf\nTemperature: %lf\nHumidity: %lf\nVisible Light: %lf\nInfrared Light: %lf\n\n",
      devices[i].id, devices[i].battery, devices[i].temperature, devices[i].humidity, devices[i].visibleLight,
      devices[i].infraredLight);

    if (i == 0) {
      if (devices[i].battery == 0) {
        strcat(buf, "[[0,0,0],");
      } else {
        strcat(buf, "[[0,102,0],");
      }
    } else if (i == 1) {
      if (devices[i].battery == 0) {
        strcat(buf, "[0,0,0],");
      } else {
        strcat(buf, "[255,128,0],");
      }
    } else if (i == 2) {
      if (devices[i].battery == 0) {
        strcat(buf, "[0,0,0],");
      } else {
        strcat(buf, "[0,0,153],");
      }
    } else if (i == 3) {
      if (devices[i].battery == 0) {
        strcat(buf, "[0,0,0],");
      } else {
        strcat(buf, "[255,0,127],");
      }
    } else if (i == 4) {
      if (devices[i].battery == 0) {
        strcat(buf, "[0,0,0],");
      } else {
        strcat(buf, "[0,255,0],");
      }
    }
    if (devices[i].temperature < TEMP_LOW) { //ativar aquecedor
      strcat(buf, "[255,0,0],");
    } else if (devices[i].temperature > TEMP_HIGH) { //ativar ar condicionado
      strcat(buf, "[0,0,255],");
    } else
      strcat(buf, "[0,0,0],");
    if (devices[i].humidity > HUM_HIGH) { //ativar deshumidificador
      strcat(buf, "[0, 255, 255],");  //azul clarinho
    } else
      strcat(buf, "[99, 15, 3],");  //castanho
    if (devices[i].visibleLight < LIGHT_TRESH && devices[i].infraredLight > INFRA_TRESH) { //ligar as luzes
      strcat(buf, "[255, 255, 255],");
    } else {                    //lampadas off
      strcat(buf, "[0,0,0],");
    }
    if (i == ndevices - 1) {
      if (devices[i].visibleLight > LIGHT_TRESH) { //ligar as cortinas
        strcat(buf, "[255,255,0]]");
      } else {
        strcat(buf, "[178, 176, 149]]");
      }
    } else {
      if (devices[i].visibleLight > LIGHT_TRESH) { //ligar as cortinas
        strcat(buf, "[255,255,0],");
      } else
        strcat(buf, "[178, 176, 149],");
    }
  }
  strcat(buf, "\n");
  fputs(buf, file);
}

