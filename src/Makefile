CXX=g++
CPPFLAGS=-std=c++17 -Os
LDFLAGS=-lcrypto

jdecrypt: *.cpp
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm jdecrypt
