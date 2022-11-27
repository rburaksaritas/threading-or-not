#include <iostream>
#include <pthread.h>
#include <vector>
#include <chrono>

int findMin(std::vector<int> integers);
int findMax(std::vector<int> integers);
int findRange(std::vector<int> integers);
int findMode(std::vector<int> integers);
double findMedian(std::vector<int> integers);
int findSum(std::vector<int> integers);
double findArithmeticMean(std::vector<int> integers);
double findHarmonicMean(std::vector<int> integers);
float findStandardDeviation(std::vector<int> integers);
double findInterquartileRange(std::vector<int> integers);

struct threadArgs1{
    std::vector<int> integers;
    int &result;
};

struct threadArgs2{
    std::vector<int> integers;
    double &result;
};

void *block01(void *voidArgs){
    threadArgs1 *args1 = (threadArgs1*)voidArgs;
    args1->result = findMin(args1->integers);
    pthread_exit(0);
}

void *block02(void *voidArgs){
    threadArgs1 *args1 = (threadArgs1*)voidArgs;
    args1->result = findMax(args1->integers);
    pthread_exit(0);
}

void *block03(void *voidArgs){
    threadArgs1 *args1 = (threadArgs1*)voidArgs;
    args1->result = findRange(args1->integers);
    pthread_exit(0);
}

void *block04(void *voidArgs){
    threadArgs1 *args1 = (threadArgs1*)voidArgs;
    args1->result = findMode(args1->integers);
    pthread_exit(0);
}

void *block05(void *voidArgs){
    threadArgs2 *args1 = (threadArgs2*)voidArgs;
    args1->result = findMedian(args1->integers);
    pthread_exit(0);
}

void *block06(void *voidArgs){
    threadArgs1 *args1 = (threadArgs1*)voidArgs;
    args1->result = findSum(args1->integers);
    pthread_exit(0);
}

void *block07(void *voidArgs){
    threadArgs2 *args1 = (threadArgs2*)voidArgs;
    args1->result = findArithmeticMean(args1->integers);
    pthread_exit(0);
}

void *block08(void *voidArgs){
    threadArgs2 *args1 = (threadArgs2*)voidArgs;
    args1->result = findHarmonicMean(args1->integers);
    pthread_exit(0);
}

void *block09(void *voidArgs){
    threadArgs2 *args = (threadArgs2*)voidArgs;
    args->result = findStandardDeviation(args->integers);
    pthread_exit(0);
}

void *block10(void *voidArgs){
    threadArgs2 *args = (threadArgs2*)voidArgs;
    args->result = findInterquartileRange(args->integers);
    pthread_exit(0);
}

/**
 * Function that runs the functions in 10 seperate pthreads.
*/
int tenThreads(std::vector<int> integers, int &min, int &max, int &range, 
            int &mode, double &median, int &sum, double &arithmeticMean, 
            double &harmonicMean, double &standardDeviation, double &interquartileRange, 
            std::chrono::duration<double> &elapsed){

    pthread_t t_id1, t_id2, t_id3, t_id4, t_id5, t_id6, t_id7, t_id8, t_id9, t_id10; // IDs of the threads.
    pthread_attr_t attr; // Gets default attributes of the thread.
    pthread_attr_init(&attr); // initialize the thread attributes with default configuration
    
    // Create argument structs.
    threadArgs1 args1 = {integers, min};
    threadArgs1 args2 = {integers, max};
    threadArgs1 args3 = {integers, range};
    threadArgs1 args4 = {integers, mode};
    threadArgs2 args5 = {integers, median};
    threadArgs1 args6 = {integers, sum};
    threadArgs2 args7 = {integers, arithmeticMean};
    threadArgs2 args8 = {integers, harmonicMean};
    threadArgs2 args9 = {integers, standardDeviation};
    threadArgs2 args10 = {integers, interquartileRange};

    std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
    
    pthread_create(&t_id1, &attr, block01, &args1);
    pthread_create(&t_id2, &attr, block02, &args2);
    pthread_create(&t_id3, &attr, block03, &args3);
    pthread_create(&t_id4, &attr, block04, &args4);
    pthread_create(&t_id5, &attr, block05, &args5);
    pthread_create(&t_id6, &attr, block06, &args6);
    pthread_create(&t_id7, &attr, block07, &args7);
    pthread_create(&t_id8, &attr, block08, &args8);
    pthread_create(&t_id9, &attr, block09, &args9);
    pthread_create(&t_id10, &attr, block10, &args10);

    // Wait for the threads to exit.
    pthread_join(t_id1, NULL);
    pthread_join(t_id2, NULL);
    pthread_join(t_id3, NULL);
    pthread_join(t_id4, NULL);
    pthread_join(t_id5, NULL);
    pthread_join(t_id6, NULL);    
    pthread_join(t_id7, NULL);
    pthread_join(t_id8, NULL);
    pthread_join(t_id9, NULL);
    pthread_join(t_id10, NULL);
    
    std::chrono::steady_clock::time_point finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;

    return 0;
}