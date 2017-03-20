BINDIR= bin
SRCDIR= src

CXX= g++
RM= rm

ARCH= 64
DEFINES= -std=gnu++14
DEBUG=-g -pg -O0
RELEASE=-O3
#WARNINGS=-Wall -Wextra -pedantic -Wno-long-long #-O3 -Weffc++
WARNINGS=-Wall -Wextra -pedantic
INCLUDES= -I./include

EXEC= $(BINDIR)/cpp_test_$(ARCH)bit.exe
OBJS= $(BINDIR)/main.o $(BINDIR)/test_libcurl.o $(BINDIR)/test_uniqueptr.o $(BINDIR)/libcurl_mult_socket_libev.o


CXXFLAGS+= -fpermissive -m$(ARCH) ${DEBUG} ${WARNINGS} ${DEFINES} ${INCLUDES}
LDFLAGS+= -fpermissive -m$(ARCH) ${DEBUG} ${WARNINGS} ${DEFINES}

LIBDIR=
#LIBDIR=-L/usr/local/lib
LDLIBS=-lcurl -lev

#LIBCURL = /usr/local/lib/libcurl.so.4

LDFLAGS+= $(LIBDIR) $(LDLIBS)

#%.o: $(SRCDIR)/%.cpp
#	$(CXX) $(CXXFLAGS) -o $@ $<

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

bin/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@  src/main.cpp

bin/test_libcurl.o: src/test_libcurl.cpp
	$(CXX) $(CXXFLAGS) -c -o $@  src/test_libcurl.cpp

bin/test_uniqueptr.o: src/test_uniqueptr.cpp
	$(CXX) $(CXXFLAGS) -c -o $@  src/test_uniqueptr.cpp

bin/libcurl_mult_socket_libev.o: src/libcurl_mult_socket_libev.cpp
	$(CXX) $(CXXFLAGS) -c -o $@  src/libcurl_mult_socket_libev.cpp

.PHONY: clean
clean:
	$(RM) -f $(EXEC) $(BINDIR)/*.o

