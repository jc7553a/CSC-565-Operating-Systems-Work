#ifndef BARRIER_H_
#define BARRIER_H_
#define MAX_SLEEP_TIME 5
#define NUMBER_OF_THREADS 5

int barrier_init(int);
void wait_for_others(void );
void *worker (void *param);

#endif