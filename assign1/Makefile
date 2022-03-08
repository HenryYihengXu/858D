all:
	g++ -O3 src/test.cpp src/rank_support.cpp src/select_support.cpp src/util.cpp -o bin/test -std=c++20
	g++ -O3 src/evaluate.cpp src/rank_support.cpp src/select_support.cpp src/util.cpp -o bin/evaluate -std=c++20

debug:
	g++ src/test.cpp src/rank_support.cpp src/select_support.cpp src/util.cpp -o bin/test -std=c++20 -g -D_GLIBCXX_ASSERTIONS -D_GLIBCXX_DEBUG
	g++ src/evaluate.cpp src/rank_support.cpp src/select_support.cpp src/util.cpp -o bin/evaluate -std=c++20 -g -D_GLIBCXX_ASSERTIONS -D_GLIBCXX_DEBUG

test:
	g++ src/test.cpp src/rank_support.cpp src/select_support.cpp src/util.cpp -o bin/test -std=c++20 -g -D_GLIBCXX_ASSERTIONS -D_GLIBCXX_DEBUG

evaluate:
	g++ -O3 src/evaluate.cpp src/rank_support.cpp src/select_support.cpp src/util.cpp -o bin/evaluate -std=c++20

clean:
	rm bin/*
	