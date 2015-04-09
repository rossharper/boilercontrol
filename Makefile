LIBRARY=libboilerControl.a
INSTALLDIR=/usr/local/lib/

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

install:
	cp -p $(LIBRARY) $(INSTALLDIR)

clean: 
	$(RM) *.o callforheat $(LIBRARY)
