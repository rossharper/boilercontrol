LIBRARY=libboilerControl.a

all: callforheat $(LIBRARY)

objects = TransmitPinFactory.o boilercontrol.o

ifeq ($(PLATFORM),pi)
	objects += RaspberryPiTransmitPin.o
	CXXFLAGS = -DRASPBERRY_PI
	LDLIBS = -lwiringPi
else
	objects += StubTransmitPin.o
endif

$(LIBRARY): $(objects)
	ar rcs $(LIBRARY) $(objects)
	ranlib $(LIBRARY)

callforheat: $(objects) callforheat.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ $(LDLIBS)

clean: 
	$(RM) *.o callforheat $(LIBRARY)