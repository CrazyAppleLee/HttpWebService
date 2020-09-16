SRC1 = $(wildcard ../*.cpp) $(wildcard ../utils/*.cpp)
src = $(filter-out ../Main.cpp,$(SRC1))
obj = $(patsubst %.cpp,%.o,$(src))
#obj = $(src:%.c=%.o)
target = test
MAINCPP = test.cpp
CC = g++
CFLAGS  = -std=c++11 -g -Wall -D_PTHREADS -lpthread -O3 -D_REENTRANT

$(target): $(obj) $(MAINCPP)
	$(CC) $(obj) $(MAINCPP) -o $(target) $(CFLAGS)
%.o: %.cpp 
	$(CC) -c $< -o $@ $(CFLAGS)
#%.d : %.c
#	@set -e;
#	gcc -MM $@ > $@.$$$$;
#	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;
#	rm -f $@.$$$$
.PHONY: clean  
clean:  
	rm -rf $(obj) $(target)
.PHONY: echo
echo:
	echo $(src) $(obj) $(target)