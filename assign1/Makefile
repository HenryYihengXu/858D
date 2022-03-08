all:
	g++ -O3 src/testBitVector.cpp -o bin/testBitVector -std=c++20
	g++ -O3 src/test.cpp src/rank_support.cpp src/select_support.cpp src/util.cpp -o bin/test -std=c++20

debug:
	g++ src/testBitVector.cpp -o bin/testBitVector -std=c++20 -g -D_GLIBCXX_ASSERTIONS -D_GLIBCXX_DEBUG
	g++ src/test.cpp src/rank_support.cpp src/select_support.cpp src/util.cpp -o bin/test -std=c++20 -g -D_GLIBCXX_ASSERTIONS -D_GLIBCXX_DEBUG

clean:
	rm bin/*
	