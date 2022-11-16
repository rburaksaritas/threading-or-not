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
 * Main driver program.
*/
int main(int argc, char *argv[]){
    int numberOfIntegers = atoi(argv[1]);
    int numberOfThreads = atoi(argv[2]); // Optional functionality.
    
    std::vector<int> integers; // Stores randomly generated integers.
    generateNumbers(numberOfIntegers, integers); // Generate and store integers.
    std::sort(integers.begin(), integers.end()); // Sort integers in ascending order.
    
    return 1;
}