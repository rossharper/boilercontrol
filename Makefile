STATIC_LIBRARY=libboilerControl.a
DYNAMIC_LIBRARY=libboilerControl.so
INSTALLDIR=/usr/local/lib/
HEADERSINSTALLDIR=/usr/local/lib/libboilerControl
EXPORTHEADERS=TransmitPinFactory.h boilercontrol.h

all: callforheat $(STATIC_LIBRARY) $(DYNAMIC_LIBRARY)

objects = TransmitPinFactory.o boilercontrol.o

ifeq ($(PLATFORM),pi)
	objects += RaspberryPiTransmitPin.o
	CXXFLAGS = -DRASPBERRY_PI
	LDLIBS = -L/usr/local/lib -lwiringPi
else
	objects += StubTransmitPin.o
endif

$(STATIC_LIBRARY): $(objects)
	ar rcs $(STATIC_LIBRARY) $(objects)
	ranlib $(STATIC_LIBRARY)

$(DYNAMIC_LIBRARY): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -shared $+ $(LDLIBS) -o $(DYNAMIC_LIBRARY) 

callforheat: $(objects) callforheat.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ $(LDLIBS)

install:
	cp -p $(STATIC_LIBRARY) $(INSTALLDIR)
	cp -p $(DYNAMIC_LIBRARY) $(INSTALLDIR)
	mkdir $(HEADERSINSTALLDIR)
	cp -p $(EXPORTHEADERS) $(HEADERSINSTALLDIR)

uninstall:
	rm -rf $(HEADERSINSTALLDIR)
	rm $(INSTALLDIR)$(STATIC_LIBRARY)
	rm $(INSTALLDIR)$(DYNAMIC_LIBRARY)

clean: 
	$(RM) *.o callforheat $(STATIC_LIBRARY)
