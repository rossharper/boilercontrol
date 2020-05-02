sudo sed -i.bak -e 's/^#Set pin 17 for output and low//' \
 -e 's/^PATH=\/bin:\/usr\/bin//' \
 -e 's/^gpio write 17 0 ; gpio export 17 out//' /etc/rc.local
