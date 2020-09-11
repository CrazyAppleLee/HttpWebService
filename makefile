src = $(wildcard ./*.cpp) $(wildcard utils/*.cpp)
obj = $(patsubst %.cpp, %.o, $(src))
#obj = $(src:%.c=%.o)
target = WebServer
CC = g++
CFLAGS  = -std=c++11 -g -Wall -O3 -D_PTHREADS -lpthread

$(target): $(obj)
	$(CC) $(obj) -o $(target) $(CFLAGS)
%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)
.PHONY: clean  
clean:  
	rm -rf $(obj) $(target)
.PHONY: echo
echo:
	echo $(obj) $(target)