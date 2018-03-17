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

typedef struct
{
  int id;
  float battery;
  float temperature;
  float humidity;
  float visibleLight;
  float infraredLight;
} sensor;

sensor *devices;
pthread_t dataThread, actuatorsThread;

void *readData(void *file);
void *defineActuators(void *out);

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    printf("Wrong usage!\nUsage: ./a.out /dev/pts/x /dev/pts/y\n");
    return 0;
  }
  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "w");
  while (1)
  {
    pthread_create(&dataThread, NULL, readData, (void *)in);
    pthread_create(&actuatorsThread, NULL, defineActuators, (void *)out);
    pthread_join(dataThread, NULL);
    pthread_join(actuatorsThread, NULL);
  }
  fclose(in);
  fclose(out);
  return 0;
}

void *readData(void *f)
{
  FILE *file = (FILE *)f;
  char *buf = NULL;
  size_t len = 0;
  char *token;
  const char delimiter[2] = " ";
  int id;
  getline(&buf, &len, file);
  token = strtok(buf, delimiter);
  for (int i = 0; token != NULL; i++)
  {
    switch (i)
    {
    case 5:
      strcat(token, strtok(NULL, delimiter));
      id = strtol(token, NULL, 16);
      if (sizeof(devices) / sizeof(sensor) < id)
      {
        devices = (sensor *)realloc(devices, sizeof(sensor) * id);
      }
      devices[id - 1].id = id;
      i++;
      break;
    case 10:
      strcat(token, strtok(NULL, delimiter));
      devices[id - 1].battery = (float)strtol(token, NULL, 16) / 4096 * 1.5;
      i++;
      break;
    case 12:
      strcat(token, strtok(NULL, delimiter));
      devices[id - 1].visibleLight = (float)strtol(token, NULL, 16) / 4096 * 0.625 * 1.5 * pow(10, 6) / 100;
      i++;
      break;
    case 14:
      strcat(token, strtok(NULL, delimiter));
      devices[id - 1].infraredLight = (float)strtol(token, NULL, 16) / 4096 * 0.769 * 1.5 * pow(10, 5) / 100;
      i++;
      break;
    case 16:
      strcat(token, strtok(NULL, delimiter));
      devices[id - 1].temperature = (float)strtol(token, NULL, 16) * 0.01 - 39.6;
      i++;
      break;
    case 18:
      strcat(token, strtok(NULL, delimiter));
      float reading = (float)strtol(token, NULL, 16);
      devices[id - 1].humidity = -2.0468 + 0.0367 * reading - 1.5955 * pow(10, -6) * pow(reading, 2);
      i++;
      break;
    }
    token = strtok(NULL, delimiter);
  }
  printf("New Data has been read\n");
}

void *defineActuators(void *f)
{
  FILE *file = (FILE *)f;
  char *buf = NULL;
  for (int i = 0; i < sizeof(devices) / sizeof(sensor); i++)
  {
    printf("%d", i);
    if (devices[i].temperature < TEMP_LOW)
    {
    }
    if (devices[i].temperature > TEMP_HIGH)
    {
    }
    if (devices[i].humidity < HUM_LOW)
    {
    }
    if (devices[i].humidity > HUM_HIGH)
    {
    }
    if (devices[i].visibleLight < LIGHT_TRESH && devices[i].infraredLight > INFRA_TRESH)
    {
      //ligar as luzes
    }
  }
  strcat(buf, "lala ");
  fputs(buf, file);
}