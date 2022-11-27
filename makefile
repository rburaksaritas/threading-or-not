start: threading echoer

threading: main.cpp
	g++ -o threading main.cpp fivethreads.cpp tenthreads.cpp

echoer: 
	@echo "Running format: ./threading <number_of_integers>"

clean:
	rm -f threading