test:test.cc
	g++ -o test test.cc

.PHONY:clean
clean:
	rm -f test

