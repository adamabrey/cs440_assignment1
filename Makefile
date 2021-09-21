all:	test.cpp Deque.hpp
	g++ test.cpp -Wl,--no-as-needed -ldl

clean:	
	rm -f a.out
