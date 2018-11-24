#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "pthread.h"

#define NUM_OF_SENSORS 2
#define NUM_OF_CYCLES 10

typedef struct sensor {
  int temp;
  int * number;
  struct sensor * next;
}sensor_t;

typedef sensor_t * SENSORS;
pthread_mutex_t lock;
pthread_cond_t self;

void sensors(int *t);
sensor_t *addToRear(sensor_t *head, sensor_t *newNode);
void addToList(int * t, int cycles);
void waitForCycleToFinish(int * t, int cycles);
void lastSensorInCycle(int* t);
int isMatch(int *t);
