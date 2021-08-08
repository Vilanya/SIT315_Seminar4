#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>


using namespace std::chrono;
using namespace std;

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

int main(){

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


    // The loop will go through each element of v1 and v2.
    // The sum of these two elements during each loop is assigned to the element in v3.
    // i.e. Filling out v3
    for (int i = 0; i < size; i++)
    {
        v3[i] = v1[i] + v2[i];
    }

    auto stop = high_resolution_clock::now();

    // By using the stop and start variables, the total duration of the processing is calculated,
    // and assigned to the auto variable duration in microseconds.
    auto duration = duration_cast<microseconds>(stop - start);


    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

    return 0;
}
