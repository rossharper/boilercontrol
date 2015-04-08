all: callforheat

callforheat: RaspberryPiTransmitPin.o boilercontrol.o callforheat.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi

clean: 
	$(RM) *.o callforheat