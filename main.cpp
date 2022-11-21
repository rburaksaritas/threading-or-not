#include <iostream>
#include <pthread.h>
#include <sstream>
#include <random>
#include <vector>

/**
 * Generates a random integer between 1000 and 10000.
 * @return generated number
*/
int generateNumber(){
    std::random_device seed;     // initialises (seed) engine.
    std::mt19937 engine(seed());    // Random-number engine (Mersenne-Twister).
    std::uniform_int_distribution<int> numberRange(1000, 10000); // Guaranteed unbiased.
    return numberRange(engine);
}

/**
 * Generates a random number N times and puts them in vector numbers of integer.
 * @param N number of integers to generate.
 * @param integers vector<int> to store the integers passed by reference.
*/
int generateNumbers(int N, std::vector<int> &integers){
    for (int i = 0; i<N; i++){
        integers.push_back(generateNumber());
    }
    return 1;
}

/**
 * Returns the first (smallest) element of sorted vector<int> integers.
*/
int findMin(std::vector<int> integers){
    return integers[0];
}

/**
 * Returns the last (largest) element of sorted vector<int> integers.
*/
int findMax(std::vector<int> integers){
    return integers[integers.size()-1];
}

/**
 * Returns the range of integers. (max-min)
*/
int findRange(std::vector<int> integers){
    return (integers[integers.size()-1] - integers[0]);
}

/**
 * Returns the mode of sorted vector<int> integers.
*/
int findMode(std::vector<int> integers){
    int currentNumber = integers[0];
    int mode = currentNumber;
    int currentCount = 0;
    int maxCount = 0;
    for (int i = 0; i<integers.size(); i++){
        if (currentNumber == integers[i]){
            currentCount++;
        } else{
            if(currentCount>maxCount){
                maxCount = currentCount;
                mode = currentNumber;
            }
            currentNumber = integers[i];
            currentCount = 1;
        }
    }
    return mode;
}

/**
 * Returns the median of sorted vector<int> integers.
*/
double findMedian(std::vector<int> integers){
    int size = integers.size();
    if (size % 2 == 0){
        return ((double)(integers[size/2-1] + integers[size/2])/(double)2);
    } else{
        return (integers[size/2]);
    }
}
 /**
  * Sums up all elements of vector<int> and returns result.
 */
int findSum(std::vector<int> integers){
    int size = integers.size();
    int sum = 0;
    for (int i = 0; i<size; i++){
        sum += integers[i];
    }
    return sum;
}

/**
 * Returns sum of integers divided by number of integers.
*/
double findArithmeticMean(int sum, int size){
    return ((double)sum/(double)size);
}

/**
 * Returns number of integers divided by sum of (1/integer) for each integer.
*/
double findHarmonicMean(std::vector<int> integers){
    double sum = 0; 
    int size = integers.size();
    for (int i = 0; i < size; i++){
        sum += double(1)/integers[i];
    }
    return ((double)size/sum);
}

/**
 * Returns standard deviation of integers.
*/
float findStandardDeviation(std::vector<int> integers, double arithmeticMean) {
    int size = integers.size();
    double sum = 0;
    for(int i = 0; i < size; i++) {
        sum += pow(integers[i] - arithmeticMean, 2);
    }
    return sqrt((double)sum/(size - 1));
}

/**
 * Returns interquartile range of integers.
*/
double findInterquartileRange(std::vector<int> integers){
    int halfSize = integers.size()/2;
    std::vector<int> lowerHalf(integers.begin(), integers.begin() + halfSize);
    if (integers.size()%2!=0){
        halfSize++;
    }
    std::vector<int> higherHalf(integers.begin() + halfSize, integers.end());
    double lowerMedian = findMedian(lowerHalf);
    double higherMedian = findMedian(higherHalf);
    return (higherMedian - lowerMedian);
}

/**
 * Executes the functions in one thread.
*/
int oneThread(std::vector<int> integers){
    // time start
    int size = integers.size();
    int min = findMin(integers);
    int max = findMax(integers);
    int range = findRange(integers);
    int mode = findMode(integers);
    double median = findMedian(integers);
    int sum = findSum(integers);
    double arithmeticMean = findArithmeticMean(sum, size);
    double harmonicMean = findHarmonicMean(integers);
    double standardDeviation = findStandardDeviation(integers, arithmeticMean);
    double interquartileRange = findInterquartileRange(integers);
    // time end
    printf("%d\n", min);
    printf("%d\n", max);
    printf("%d\n", range);
    printf("%d\n", mode);
    printf("%g\n", median);
    printf("%d\n", sum);
    printf("%.5f\n", arithmeticMean);
    printf("%.5f\n", harmonicMean);
    printf("%.5f\n", standardDeviation);
    printf("%g\n", interquartileRange);
    // print time
    return 1;
}

/**
 * Main driver program.
*/
int main(int argc, char *argv[]){
    int numberOfIntegers = atoi(argv[1]);
    if (argv[2]){
        int numberOfThreads = atoi(argv[2]); // Optional functionality.  
    }
    
    std::vector<int> integers; // Stores randomly generated integers.
    generateNumbers(numberOfIntegers, integers); // Generate and store integers.
    std::sort(integers.begin(), integers.end()); // Sort integers in ascending order.

    oneThread(integers); // execute functions in a single thread.

    return 1;
}

