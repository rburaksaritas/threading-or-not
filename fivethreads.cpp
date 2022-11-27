#include <iostream>
#include <pthread.h>
#include <vector>
#include <chrono>

/**
 * @author Ramazan Burak Saritas
 * 2020400321
*/

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
    int &result1;
    int &result2;
};

struct threadArgs2{
    std::vector<int> integers;
    double &result1;
    int &result2;
};

struct threadArgs3{
    std::vector<int> integers;
    double &result1;
    double &result2;
};

void *block1(void *voidArgs){
    threadArgs1 *args1 = (threadArgs1*)voidArgs;
    args1->result1 = findMin(args1->integers);
    args1->result2 = findMax(args1->integers);
    pthread_exit(0);
}

void *block2(void *voidArgs){
    threadArgs1 *args2 = (threadArgs1*)voidArgs;
    args2->result1 = findRange(args2->integers);
    args2->result2 = findMode(args2->integers);
    pthread_exit(0);
}

void *block3(void *voidArgs){
    threadArgs2 *args3 = (threadArgs2*)voidArgs;
    args3->result1 = findMedian(args3->integers);
    args3->result2 = findSum(args3->integers);
    pthread_exit(0);
}

void *block4(void *voidArgs){
    threadArgs3 *args4 = (threadArgs3*)voidArgs;
    args4->result1 = findArithmeticMean(args4->integers);
    args4->result2 = findHarmonicMean(args4->integers);
    pthread_exit(0);
}

void *block5(void *voidArgs){
    threadArgs3 *args5 = (threadArgs3*)voidArgs;
    args5->result1 = findStandardDeviation(args5->integers);
    args5->result2 = findInterquartileRange(args5->integers);
    pthread_exit(0);
}

/**
 * Function that runs the functions in 5 seperate pthreads.
*/
int fiveThreads(std::vector<int> integers, int &min, int &max, int &range, 
            int &mode, double &median, int &sum, double &arithmeticMean, 
            double &harmonicMean, double &standardDeviation, double &interquartileRange, 
            std::chrono::duration<double> &elapsed){

    pthread_t t_id1, t_id2, t_id3, t_id4, t_id5; // IDs of the threads.
    pthread_attr_t attr; // Gets default attributes of the thread.
    pthread_attr_init(&attr); // initialize the thread attributes with default configuration
    
    // Create argument structs.
    threadArgs1 args1 = {integers, min, max};
    threadArgs1 args2 = {integers, range, mode};
    threadArgs2 args3 = {integers, median, sum};
    threadArgs3 args4 = {integers, arithmeticMean, harmonicMean};
    threadArgs3 args5 = {integers, standardDeviation, interquartileRange};

    std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();

    pthread_create(&t_id1, &attr, block1, &args1);
    pthread_create(&t_id2, &attr, block2, &args2);
    pthread_create(&t_id3, &attr, block3, &args3);
    pthread_create(&t_id4, &attr, block4, &args4);
    pthread_create(&t_id5, &attr, block5, &args5);
    // Wait for the threads to exit.
    pthread_join(t_id1, NULL);
    pthread_join(t_id2, NULL);
    pthread_join(t_id3, NULL);
    pthread_join(t_id4, NULL);
    pthread_join(t_id5, NULL);

    std::chrono::steady_clock::time_point finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;

    return 0;
}