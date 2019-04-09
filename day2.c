#include<stdio.h>


#include<pthread.h>

#include<stdlib.h>

#include <unistd.h>





pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t  finish_cond  = PTHREAD_COND_INITIALIZER;

int barrier = 0;

int thread_count;

int barrier_size;

int counter=0;

int invoke_barrier = 0;







/*

 * params : number of threads a process is creating.

 * returns : none.

 *

 * Initialize barrier with total number of threads.

 */

void barrier_init(int n_threads)

{

    if ( thread_count < barrier_size ) { barrier = thread_count; return; }

    barrier = n_threads;

}







/*

 * params: none.

 * returns: -1 on failure, 0 on success.

 * decrement the count by 1.

 *

 */

int decrement()

{

    if (barrier == 0) {



        return 0;

    }



    if(pthread_mutex_lock(&lock) != 0)

    {

        perror("Failed to take lock.");

        return -1;

    }



    barrier--;



    if(pthread_mutex_unlock(&lock) != 0)

    {

        perror("Failed to unlock.");

        return -1;

    }



    return 0;

}


