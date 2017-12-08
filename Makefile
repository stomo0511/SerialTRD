CXX = /usr/local/bin/g++
CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		SerialTRD.o

LIBS =

TARGET =	SerialTRD

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
