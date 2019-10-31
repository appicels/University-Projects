#include "rollercoaster.h"
#include <assert.h>
#include <unistd.h>


void passenger(PASSENGER info)
{
  takeRide(info);
  printf("Passenger %d is off the ride now leaving the park\n", info->ID);
  pthread_exit(NULL);

}

void car(CAR info)
{
  pthread_mutex_lock(&coaster);
  carNeedsPassengers = 1;
  passengerInCar = 0;
  numGotOff = 0;
  int cycles = 0;
  passengerWaiting = info->num_pass;
  init = 1;
  pthread_cond_broadcast(&carReady);
  pthread_mutex_unlock(&coaster);

  while(passengerWaiting != 0)
  {
    load(info);
    unload(info);
    cycles+= 1;
    puts("\n");
  }


//makes sure all passengers get off the ride
  while(numGotOff != info->num_pass)
  {
    pthread_cond_broadcast(&carUnload);
  }
  printf("The car took %d rides\n",cycles);
  pthread_exit(NULL);

}

void takeRide(PASSENGER info)
{
  pthread_mutex_lock(&coaster);
  while(init == 0)
  {
    pthread_cond_wait(&carReady, &coaster);
  }

  //passengers that didn't get on wait for a car to be free
  while(carNeedsPassengers == 1 || passengerInCar == info->num_seats )
  {

    pthread_cond_wait(&carLoad, &coaster);
  }

  passengerInCar++;
  printf("Passenger %d is going on ride\n", info->ID);


  if(passengerInCar == info->num_seats || passengerWaiting < info->num_seats ) //I am the last one to get on for that ride
  {
    if(passengerWaiting < info->num_seats)
    {
      passengerWaiting = 0;
    }
    if(passengerInCar == info->num_seats)
    {
      passengerWaiting = passengerWaiting - info->num_seats;
    }

    //broadcast that the car is full
    pthread_cond_broadcast(&carIsFull);

  }


  //wakes up when last person comes on
  pthread_cond_wait(&carIsFull, &coaster);


  //printf("passengerInCar: %d\n", passengerInCar);
//waits until unload broadcast so they can get off
  pthread_cond_wait(&carUnload, &coaster);
  numGotOff++;
  //printf("passenger %d got off the ride\n",info->ID );
  pthread_mutex_unlock(&coaster);
}




void load(CAR info)
{
  pthread_mutex_lock(&coaster);

  carNeedsPassengers = 0; //true so it needs passengers

  //notifies if car can load
  if(passengerInCar == 0)
  {
    puts("car is empty and ready for passengers");
    pthread_cond_broadcast(&carLoad);
  }



  //wait for car to be full
  pthread_cond_wait(&carIsFull, &coaster);
  carNeedsPassengers = 1;  //it is false, so it doesn't need passengers

  puts("Car is going for a ride");

  sleep(1);
  //tells passengers the car is done with the ride
  puts("car is done with ride, please remain seated");
  pthread_cond_broadcast(&carIsFull);


  pthread_mutex_unlock(&coaster);

}

void unload(CAR info)
{
  pthread_mutex_lock(&coaster);
  pthread_cond_broadcast(&carUnload);
  puts("You may now get off the ride");
  passengerInCar = 0;
  pthread_mutex_unlock(&coaster);

}
