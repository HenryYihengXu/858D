all:
	mkdir -p bin
	g++ -O3 src/buildsa.cpp src/suffix_array.cpp src/util.cpp -o bin/test -std=c++20 -I/usr/local/include -L/usr/local/lib -lsdsl -ldivsufsort -ldivsufsort64

debug:
	mkdir -p bin
	g++ src/test.cpp src/rank_support.cpp src/select_support.cpp src/util.cpp -o bin/test -std=c++20 -g -D_GLIBCXX_ASSERTIONS -D_GLIBCXX_DEBUG
	g++ src/evaluate.cpp src/rank_support.cpp src/select_support.cpp src/util.cpp -o bin/evaluate -std=c++20 -g -D_GLIBCXX_ASSERTIONS -D_GLIBCXX_DEBUG

test:
	mkdir -p bin
	g++ src/test.cpp src/rank_support.cpp src/select_support.cpp src/util.cpp -o bin/test -std=c++20 -g -D_GLIBCXX_ASSERTIONS -D_GLIBCXX_DEBUG

evaluate:
	mkdir -p bin
	g++ -O3 src/evaluate.cpp src/rank_support.cpp src/select_support.cpp src/util.cpp -o bin/evaluate -std=c++20

clean:
	rm bin/*
	
