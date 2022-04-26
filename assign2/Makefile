all:
	mkdir -p bin
	g++ -O3 src/buildsa.cpp src/suffix_array.cpp src/util.cpp -o bin/buildsa -std=c++20 -I/usr/local/include -L/usr/local/lib -lsdsl -ldivsufsort -ldivsufsort64
	g++ -O3 src/querysa.cpp src/suffix_array.cpp src/util.cpp -o bin/querysa -std=c++20 -I/usr/local/include -L/usr/local/lib -lsdsl -ldivsufsort -ldivsufsort64

debug:
	mkdir -p bin
	g++ src/buildsa.cpp src/suffix_array.cpp src/util.cpp -o bin/buildsa -std=c++20 -I/usr/local/include -L/usr/local/lib -lsdsl -ldivsufsort -ldivsufsort64 -g -D_GLIBCXX_ASSERTIONS -D_GLIBCXX_DEBUG
	g++ src/querysa.cpp src/suffix_array.cpp src/util.cpp -o bin/querysa -std=c++20 -I/usr/local/include -L/usr/local/lib -lsdsl -ldivsufsort -ldivsufsort64 -g -D_GLIBCXX_ASSERTIONS -D_GLIBCXX_DEBUG

evaluate:
	mkdir -p bin
	g++ -O3 src/evaluate.cpp src/suffix_array.cpp src/util.cpp -o bin/evaluate -std=c++20

clean:
	rm bin/*
	