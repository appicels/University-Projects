#ifndef _ROLLERCOASTER_H
#define _ROLLERCOASTER_H
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "pthread.h"



pthread_mutex_t coaster;
pthread_cond_t carLoad;
pthread_cond_t carIsFull;
pthread_cond_t carUnload;
pthread_cond_t carReady;
pthread_cond_t rideFinished;
int passengerWaiting;
int carNeedsPassengers;

int passengerInCar;
int init;
int numGotOff;

typedef struct passenger_data
{
  int ID;
  int num_pass;
  int num_seats;
} pdata_t;

typedef struct car_data
{
  int num_pass;
  int num_seats;
} cdata_t;

typedef pdata_t * PASSENGER;
typedef cdata_t * CAR;

void passenger(PASSENGER info);
void car(CAR info);
void takeRide(PASSENGER info);
void load(CAR info);
void unload(CAR info);












#endif
