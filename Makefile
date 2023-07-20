CXX=g++
CXXFLAGS=-Iinclude -pthread -I/usr/include/piduino/arduino -lpiduino -lcppdb -ldl -ludev -lpthread
IN=src/hdzero.cpp src/fakefc.cpp

fakefc: $(IN)
	$(CXX) $(CXXFLAGS) $(IN) -DDEBUG_HDZERO -o fakefc

clean:
	rm -rf fakefc