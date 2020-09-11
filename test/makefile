src = $(filter-out Main.cpp $(wildcard ../*.cpp),$(wildcard ../utils/*.cpp))
obj = $(patsubst %.cpp, %.o, $(src))
#obj = $(src:%.c=%.o)
target = test
MAINCPP = test.cpp
CC = g++
CFLAGS  = -std=c++11 -g -Wall -D_PTHREADS -lpthread -O3 -D_REENTRANT

$(target): $(obj) 
	$(CC) $(obj) $(MAINCPP) -o $(target) $(CFLAGS)
%.o: %.cpp $(MAINCPP)
	$(CC) -c $< -o $@ $(CFLAGS)
.PHONY: clean  
clean:  
	rm -rf $(obj) $(target)
.PHONY: echo
echo:
	echo $(src) $(obj) $(target)