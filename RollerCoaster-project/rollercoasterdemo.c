
#include <stdio.h>
#include <stdlib.h>
#include "rollercoaster.h"




int main(int argc, char *argv[])
{
  int NUM_PASSENGERS;
  int NUM_SEATS;
  if(argc == 3)
  {
    NUM_PASSENGERS = atoi(argv[1]);
    NUM_SEATS = atoi(argv[2]);
  }



  //NUM_SEATS = 2;
  //NUM_PASSENGERS = 10;



  int count = 0;
  pthread_t pass[NUM_PASSENGERS];
  pthread_t tid;
  pthread_mutex_init(&coaster, NULL);
  pthread_cond_init(&carLoad, NULL);
  pthread_cond_init(&carUnload, NULL);
  pthread_cond_init(&carIsFull, NULL);
  pthread_cond_init(&carReady, NULL);
  pthread_cond_init(&rideFinished, NULL);


  //passenger threads
  while (count < NUM_PASSENGERS)
  {
    PASSENGER pdata;
    pdata = (pdata_t *)malloc(sizeof(pdata_t));
    pdata->ID = count;
    pdata->num_pass = NUM_PASSENGERS;
    pdata->num_seats = NUM_SEATS;

    int rc = pthread_create(&(pass[count]), NULL, (void *)passenger, (void *)pdata);
    if(rc)
    {
      puts("error making thread");
      exit(rc);
    }
    count ++;
  }
  //car thread
  CAR cdata;
  cdata = (cdata_t *)malloc(sizeof(cdata_t));
  cdata->num_pass = NUM_PASSENGERS;
  cdata->num_seats = NUM_SEATS;
  pthread_create(&tid, NULL, (void *)car, (void *)cdata);



  /*for(count=0;count<NUM_PASSENGERS;count++)
  {
    pthread_join(pass[count],NULL);
    puts("joining passenger threads");
  }*/

  pthread_join(tid, NULL);



  puts("The ride is closed, please come again soon!");
  exit(0);


}
