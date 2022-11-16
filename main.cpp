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
int findMin(std::vector<int> &integers){
    return integers[0];
}

/**
 * Returns the last (largest) element of sorted vector<int> integers.
*/
int findMax(std::vector<int> &integers){
    return integers[integers.size()-1];
}

/**
 * Returns the range of integers. (max-min)
*/
int findRange(std::vector<int> &integers){
    return (integers[integers.size()-1] - integers[0]);
}

/**
 * Returns the mode of sorted vector<int> integers.
*/
int findMode(std::vector<int> &integers){
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
    
    return 1;
}

