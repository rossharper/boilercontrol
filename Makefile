LIBRARY=libboilerControl.a
INSTALLDIR=/usr/local/lib/
HEADERSINSTALLDIR=/usr/local/lib/libboilerControl
EXPORTHEADERS=TransmitPinFactory.h boilercontrol.h

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
	mkdir $(HEADERSINSTALLDIR)
	cp -p $(EXPORTHEADERS) $(HEADERSINSTALLDIR)

clean: 
	$(RM) *.o callforheat $(LIBRARY)
