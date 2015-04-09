STATIC_LIBRARY=libboilerControl.a
INSTALLDIR=/usr/local/lib/
HEADERSINSTALLDIR=/usr/local/lib/libboilerControl
EXPORTHEADERS=TransmitPinFactory.h boilercontrol.h

all: callforheat $(STATIC_LIBRARY)

objects = TransmitPinFactory.o boilercontrol.o

ifeq ($(PLATFORM),pi)
	objects += RaspberryPiTransmitPin.o
	CXXFLAGS = -DRASPBERRY_PI
	LDLIBS = -lwiringPi
else
	objects += StubTransmitPin.o
endif

$(STATIC_LIBRARY): $(objects)
	ar rcs $(STATIC_LIBRARY) $(objects)
	ranlib $(STATIC_LIBRARY)

callforheat: $(objects) callforheat.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ $(LDLIBS)

install:
	cp -p $(STATIC_LIBRARY) $(INSTALLDIR)
	mkdir $(HEADERSINSTALLDIR)
	cp -p $(EXPORTHEADERS) $(HEADERSINSTALLDIR)

clean: 
	$(RM) *.o callforheat $(STATIC_LIBRARY)
