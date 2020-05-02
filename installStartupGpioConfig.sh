sudo sed -i.bak -e 's/^exit 0/#Set pin 17 for output and low\nPATH=\/bin:\/usr\/bin\ngpio write 17 0 ; gpio export 17 out\n\nexit 0/' /etc/rc.local
