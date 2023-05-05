CPP=g++

main: main.cpp mcmf.o
	$(CPP) $< mcmf.o -o $@

mcmf.o: mcmf.cpp
	$(CPP) $< -c $@

clean:
	rm main
