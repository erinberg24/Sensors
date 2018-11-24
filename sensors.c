#include "sensors.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

sensor_t * head = NULL;

void sensors(int * t) {
  int cycles = 1;
  while (cycles <= NUM_OF_CYCLES) {
    addToList(t, cycles);
    lastSensorInCycle(t);
    waitForCycleToFinish(t,cycles);
    cycles++;
  }
  // printf("all cycles completed %d is done\n", * t);
  pthread_exit(NULL);
}

sensor_t *addToRear(sensor_t *head, sensor_t *newNode) {
  sensor_t * p; // declar 2 node temp and p
  if (head == NULL) {
    return newNode;//when linked list is empty
  }
  p = head;
  while (p->next != NULL) {
      p = p->next; //traverse the list until p is the last node. The last node always points to NULL
  }
  p->next = newNode; //Point the preview node to the new node created
  return head;
}

void addToList(int * t, int cycles) {
  sensor_t *s;
  pthread_mutex_lock(&lock);
  s = (sensor_t *)malloc(sizeof(sensor_t));
  s->temp = 1 + (rand() % 100);
  s->number = t;
  s->next = NULL;
  printf("Temperature is %d degrees", s->temp);
  head = addToRear(head, s);
  pthread_mutex_unlock(&lock);
}

void waitForCycleToFinish(int * t, int cycles) {
  pthread_mutex_lock(&lock);
  while (isMatch(t) == 1) {
    pthread_cond_wait(&self, &lock);
  }
  pthread_mutex_unlock(&lock);
  return;
}

void lastSensorInCycle(int * t) {
  pthread_mutex_lock(&lock);
  int count = 0;
  int average = 0;
  SENSORS temp = head;
  while (temp!=NULL) {
    count++;
    temp = temp->next;
  }
  if (count == NUM_OF_SENSORS) {
    printf("Last sensor in cycle");
    temp = head;
    count = 0;
    while (temp!=NULL) {
      int getTemp = temp->temp;
      average = (average + getTemp);
      count++;
      temp = temp->next;
    }
    average = average/count;
    printf("\nThe average is %d \n \n", average);
    while (head!=NULL){
      temp=head;
      head=head->next;
      free(temp);
  }
  head=NULL;
  pthread_cond_broadcast(&self);
  }
  pthread_mutex_unlock(&lock);
}

int isMatch(int * t) {
  sensor_t * temp;
  temp = head;
  while (temp!=NULL) {
    if (temp->number == t) {
      return 1;
    }
    temp = temp->next;
  }
  if (temp == NULL) {
    return 0;
  }
}
