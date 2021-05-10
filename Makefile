make: SelfDrivingCar.c
	gcc SelfDrivingCar.c -lwiringPi -lm

run: SelfDrivingCar.c
	./a.out
clean: SelfDrivingCar.c
	rm a.out