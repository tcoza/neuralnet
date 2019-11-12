LIBS=m msgpackc getl errorf llist random
OBJECTS=main.o matrix.o neuralnetwork.o output.o info.o load.o msgpack_reader.o train.o help.o select.o new.o get.o set.o crossover.o mutate.o
CFLAGS=-Wshadow -g -I$(USERINC) -O3
LFLAGS=-L$(USERLIB)
USERLIB=/root/lib
USERINC=/root/lib/include
USERBIN=/root/bin

neuralnet: $(OBJECTS) 
	gcc $(LFLAGS) $^ $(patsubst %,-l%,$(LIBS)) -o $@

%.o: %.c
#	curlyorg $<
	gcc $(CFLAGS) $< -c -o $@

.PHONY: run debug clean install uninstall

run: neuralnet
	./neuralnet $(RUNARGS)

debug: neuralnet
	$(DEBUGGER) ./neuralnet $(RUNARGS)

clean:
	rm neuralnet $(OBJECTS)

install: neuralnet
	cp $< $(USERBIN)

uninstall:
	rm $(USERBIN)/neuralnet
