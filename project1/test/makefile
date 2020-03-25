cc = c++ -Wall

main : main.o wavefunction.o
	${cc} -o main.exe main.o wavefunction.o

main.o : main.cpp
	${cc} -c main.cpp

wavefunction.o : wavefunction.cpp
	${cc} -c wavefunction.cpp

clean :
	rm *.o
	rm *.exe
