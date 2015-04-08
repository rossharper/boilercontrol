all: callforheat

objects = TransmitPinFactory.o boilercontrol.o callforheat.o

ifeq ($(PLATFORM),pi)
	objects += RaspberryPiTransmitPin.o
	LDLIBS = -lwiringPi
else
	objects += StubTransmitPin.o
endif

callforheat: $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ $(LDLIBS)

clean: 
	$(RM) *.o callforheat