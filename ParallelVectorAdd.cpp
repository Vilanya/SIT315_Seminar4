#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <pthread.h>


using namespace std::chrono;
using namespace std;
#define NUM_THREADS 40

struct AddTask{
  int *v1,*v2,*v3;
  int start;
  int end;
};

void randomVector(int vector[], int size)
{
    for (int i = 0; i < size; i++)
    {
        // Given a size and a vector as parameter inputs, 
        // the vector is populated with random values in the range of 0-99.
        // The vector would have the given size.
        vector[i] = rand() % 100;
    }
}

void *AddVector(void* arg){

  AddTask *task = (struct AddTask *) arg;

  for(int i = task->start; i< task->end ; i++){
    task->v3[i] = task->v2[i] + task->v1[i];
  }
}

int main(void){

    pthread_t threads[NUM_THREADS];

    unsigned long size = 100000000;

    srand(time(0));

    int *v1, *v2, *v3;

    // start is an auto type variable. This means that the type of the variable is deduced by the compiler during runtime.
    // start is assigned the time point representing the current time (at execution)
    auto start = high_resolution_clock::now();

    // The three vectors declared previously are being dynamically allocated memory enough to hold 'size' number of integer values. 
    v1 = (int *) malloc(size * sizeof(int *));
    v2 = (int *) malloc(size * sizeof(int *));
    v3 = (int *) malloc(size * sizeof(int *));


    randomVector(v1, size);

    randomVector(v2, size);

    for (size_t i = 0; i < NUM_THREADS; i++) {
      struct AddTask *task = (struct AddTask*)malloc(sizeof(struct AddTask));
      task->v1 = v1;
      task->v2 = v2;
      task->v3 = v3;
      task->start = size/NUM_THREADS * i;
      task->end = i == NUM_THREADS - 1 ? size : (size/NUM_THREADS * (i+1));
      // Creating a thread
      pthread_create(&threads[i],NULL,AddVector,(void*)task);
    }

    for (size_t i = 0; i < NUM_THREADS; i++) {
    // Waits for the threads[i] to terminate
      (void) pthread_join(threads[i], NULL);
    }

    auto stop = high_resolution_clock::now();

    // By using the stop and start variables, the total duration of the processing is calculated,
    // and assigned to the auto variable duration in miliseconds.
    auto duration = duration_cast<microseconds>(stop - start);


    cout << "Number of threads "
         << NUM_THREADS << endl;

    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

    return 0;
}
