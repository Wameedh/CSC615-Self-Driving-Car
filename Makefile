
ROOTNAME=SelfDrivingCar
HW=
FOPTION=
RUNOPTIONS=
CC=gcc
CFLAGS= -g -I.
LIBS = -lwiringPi -lpthread -lm
DEPS = SelfDrivingCar.h
OBJ = $(ROOTNAME)$(HW)$(FOPTION).o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ROOTNAME)$(HW)$(FOPTION): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm *.o $(ROOTNAME)$(HW)$(FOPTION)

run: $(ROOTNAME)$(HW)$(FOPTION)
	./$(ROOTNAME)$(HW)$(FOPTION) $(RUNOPTIONS)
