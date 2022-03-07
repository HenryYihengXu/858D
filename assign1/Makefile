all:
	g++ src/testBitVector.cpp -o bin/testBitVector -std=c++20 # -g -D_GLIBCXX_ASSERTIONS -D_GLIBCXX_DEBUG
	g++ src/main.cpp src/rank_support.cpp src/select_support.cpp -o bin/main -std=c++20 # -g -D_GLIBCXX_ASSERTIONS -D_GLIBCXX_DEBUG

clean:
	rm bin/*
	