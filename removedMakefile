CXX = g++
CXXFLAGS = -std=c++17 -O2
LDFLAGS = -lpthread

all: app

app: main.cpp
    $(CXX) $(CXXFLAGS) main.cpp -o app $(LDFLAGS)

clean:
    rm -f app
