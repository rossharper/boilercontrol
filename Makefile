all: callforheat

callforheat: RaspberryPiTransmitPin.o TransmitPinFactory.o boilercontrol.o callforheat.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi

clean: 
	$(RM) *.o callforheat