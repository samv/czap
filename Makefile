CC=gcc
CFLAGS=-I.
DEPS = buffer.h     czap.h       fields.h     fieldtypes.h helpers.h    levels.h     logger.h     types.h      writers.h
OBJ = czap.o       czap_demo.o  fieldtypes.o helpers.o    logger.o fields.o levels.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

czap_demo: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o czap_demo
