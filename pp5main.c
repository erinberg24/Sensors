#include "sensors.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int main(int argc, char *argv[]) {
  int n, *who;
  int count = 0;
  srand(time(NULL));
  pthread_t sen[NUM_OF_SENSORS];
  pthread_mutex_init(&lock, NULL);
  pthread_cond_init(&self, NULL);

  while (count < NUM_OF_SENSORS) {
    who = (int*)malloc(sizeof(int));
    *who = count;
    pthread_create(&(sen[count]), NULL, (void *)sensors, who);
    count++;
    }
  for (count=0; count<NUM_OF_SENSORS; count++){
    pthread_join(sen[count], NULL);}
  puts("all done");
  exit(0);
  }
