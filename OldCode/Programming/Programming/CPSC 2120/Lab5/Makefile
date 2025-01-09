action:
	g++ -g T$(case).cpp -o T$(case).out
	./T$(case).out
build:
	for t in 1 2 3 4 5 6 9; do \
		g++ -g T$$t.cpp -o T$$t.out; \
		echo T$$t.cpp compiled successfully ; \
	done
run:
	for t in 1 2 3 4 5 6 9; do \
		./T$$t.out; \
		echo T$$t.cpp ran successfully ; \
	done
clean:
	rm -rf *.out
all: build run clean