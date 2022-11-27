#include <iostream>
#include <pthread.h>
#include <sstream>
#include <random>
#include <vector>
#include <chrono>

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
double findArithmeticMean(std::vector<int> integers){
    int sum = findSum(integers);
    int size = integers.size();
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
float findStandardDeviation(std::vector<int> integers) {
    double arithmeticMean = findArithmeticMean(integers);
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
 * Prints results to a file.
*/
int printResults(int &min, int &max, int &range, int &mode, double &median, 
            int &sum, double &arithmeticMean, double &harmonicMean, 
            double &standardDeviation, double &interquartileRange, 
            std::chrono::duration<double> &elapsed, int outputCounter){
        
        std::string filename = "output" + std::to_string(outputCounter) + ".txt";
        FILE * output;
        output = fopen(filename.c_str(), "w");
        fprintf(output, "%d\n", min);
        fprintf(output, "%d\n", max);
        fprintf(output, "%d\n", range);
        fprintf(output, "%d\n", mode);
        fprintf(output, "%g\n", median);
        fprintf(output, "%d\n", sum);
        fprintf(output, "%.5f\n", arithmeticMean);
        fprintf(output, "%.5f\n", harmonicMean);
        fprintf(output, "%.5f\n", standardDeviation);
        fprintf(output, "%g\n", interquartileRange);
        fprintf(output, "%.5f", elapsed.count());
        fclose(output);
            
        return 1;
}

/**
 * Executes the functions in one thread.
 * Keeps track of time with the help of <chrono>.
*/
int oneThread(std::vector<int> integers, int &min, int &max, int &range, 
            int &mode, double &median, int &sum, double &arithmeticMean, 
            double &harmonicMean, double &standardDeviation, double &interquartileRange, 
            std::chrono::duration<double> &elapsed){
    std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
    
    min = findMin(integers);
    max = findMax(integers);
    range = findRange(integers);
    mode = findMode(integers);
    median = findMedian(integers);
    sum = findSum(integers);
    arithmeticMean = findArithmeticMean(integers);
    harmonicMean = findHarmonicMean(integers);
    standardDeviation = findStandardDeviation(integers);
    interquartileRange = findInterquartileRange(integers);
    
    std::chrono::steady_clock::time_point finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;

    return 1;
}

int fiveThreads(std::vector<int> integers, int &min, int &max, int &range, 
            int &mode, double &median, int &sum, double &arithmeticMean, 
            double &harmonicMean, double &standardDeviation, double &interquartileRange, 
            std::chrono::duration<double> &elapsed);

 int tenThreads(std::vector<int> integers, int &min, int &max, int &range, 
            int &mode, double &median, int &sum, double &arithmeticMean, 
            double &harmonicMean, double &standardDeviation, double &interquartileRange, 
            std::chrono::duration<double> &elapsed);           

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

    int size, min, max, range, mode, sum = 0;
    double  median, arithmeticMean, harmonicMean, standardDeviation, interquartileRange = 0;
    std::chrono::duration<double> elapsed_1;

    oneThread(integers, min, max, range, mode, median, sum, arithmeticMean, 
    harmonicMean, standardDeviation, interquartileRange, elapsed_1); // execute functions in a single thread.
    printResults(min, max, range, mode, median, sum, arithmeticMean, harmonicMean, 
    standardDeviation, interquartileRange, elapsed_1, 1); // print results to an output file.
    
    size = 0; min = 0; max = 0; range = 0; mode = 0; sum = 0;
    median = 0.0; arithmeticMean = 0.0; harmonicMean = 0.0; standardDeviation = 0.0; interquartileRange = 0.0;
    std::chrono::duration<double> elapsed_2;

    fiveThreads(integers, min, max, range, mode, median, sum, arithmeticMean, 
    harmonicMean, standardDeviation, interquartileRange, elapsed_2); // execute functions in 5 threads.
    printResults(min, max, range, mode, median, sum, arithmeticMean, harmonicMean, 
    standardDeviation, interquartileRange, elapsed_2, 2); // print results to an output file.
    
    size = 0; min = 0; max = 0; range = 0; mode = 0; sum = 0;
    median = 0.0; arithmeticMean = 0.0; harmonicMean = 0.0; standardDeviation = 0.0; interquartileRange = 0.0;
    std::chrono::duration<double> elapsed_3;

    tenThreads(integers, min, max, range, mode, median, sum, arithmeticMean, 
    harmonicMean, standardDeviation, interquartileRange, elapsed_3); // execute functions in 10 threads.
    printResults(min, max, range, mode, median, sum, arithmeticMean, harmonicMean, 
    standardDeviation, interquartileRange, elapsed_3, 3); // print results to an output file.

    return 1;
}

