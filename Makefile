STATIC_LIBRARY=libboilerControl.a
DYNAMIC_LIBRARY=libboilerControl.so
INSTALLDIR=/usr/local/lib/
EXECINSTALLDIR=/usr/local/bin/
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
	mkdir -p $(HEADERSINSTALLDIR)
	cp -p $(EXPORTHEADERS) $(HEADERSINSTALLDIR)
	chown root callforheat
	chmod 4755 callforheat
	cp -p callforheat $(EXECINSTALLDIR)
ifeq ($(PLATFORM),pi)
	chmod 4755 gpio-init.sh
	sh installStartupGpioConfig.sh
endif

uninstall:
	rm -rf $(HEADERSINSTALLDIR)
	rm $(INSTALLDIR)$(STATIC_LIBRARY)
	rm $(INSTALLDIR)$(DYNAMIC_LIBRARY)
	rm $(EXECINSTALLDIR)callforheat
ifeq ($(PLATFORM),pi)
		sh unInstallStartupGpioConfig.sh
endif

clean:
	$(RM) *.o callforheat $(STATIC_LIBRARY)
