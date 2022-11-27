**CMPE 322, Project 2: Threading, or Not?** <br />
Ramazan Burak Sarıtaş, 2020400321

The project is written in C++. <br />
Program is composed of three .cpp files: main.cpp, fivethreads.cpp, tenthreads.cpp <br />
Input: number of integers to generate (N). <br />
Output Files: three separate .txt files.  <br />
 	(output1.txt for one thread, output2.txt for 5 threads, output3.txt for 10 threads)

In the project, I created functions generateNumber() (one random number) and generateNumbers() (N random numbers) to generate given number of integers and stored the generated integers in vector<int> integers. The integers vector is sorted using std::sort() once in the main function before running the tasks, so the sorting time is not included in the measured estimated times. Time is measured with the help of chrono library.

**First Part (main.cpp):** <br />
Function oneThread() calculates each requested information one by one from start to end. No additional thread is created in this part since it is basically the same as creating one thread. Time is started right before the first task findMin() is performed
Function printResults(…, 1) prints the results to output1.txt.

**Second Part:** <br />
fivethreads.cpp: Five different function blocks are defined for each pair of tasks. For example, void *block1(void *args) takes the variables in args struct (min and max for block1) and assings the results to the variables. Variables are passed by reference, so they are modified directly in the block. Function fiveThreads() creates 5 struct instances (Example: ThreadArgs1 args = {integers, min, max}) for arguments of pthreads and creates 5 pthreads to run in parallel. Then waits for threats to exit and joins with pthread_join().
tenthreads.cpp: Works very similar to the five threads part, but the function blocks for threads are defined in a way that they perform only one task in each. Argument structures are also defined accordingly.  (Example: ThreadArgs1 args = {integers, min})

**Time Observations:** <br />
For small number of integers like 100, 200, 500; the execution time for one thread is smaller. At first it is confusing, but since the input is relatively small, the required time for task completion is very short that the time for creating five new pthreads takes longer. Therefore, creating threads is not bringing faster execution time. However, for large inputs like 10000, 20000, 100000; the results are as expected. One thread works the slowest, while ten threads work the fastest. Since threads are working in parallel, this is the expected behavior. The speed of execution does not double when the number of threads do. This is because of different time complexities of different task functions. Some tasks take much longer than others, therefore the program waits the longer ones to finish and join to terminate. If the tasks were taking approximately similar amount of time, ten threads part would be much faster than five threads part. 
(Example N=100: 	1t -> 0.00004, 5t -> 0.00010, 10t -> 0.00012).
(Example N=10000: 	1t -> 0.00120, 5t -> 0.00080, 10t -> 0.00051).

