threading: main.cpp
	g++ -o threading main.cpp fivethreads.cpp tenthreads.cpp

clean:
	rm -f threading