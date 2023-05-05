CPP=g++

main: main.cpp
	$(CPP) $< -o $@

clean:
	rm main
