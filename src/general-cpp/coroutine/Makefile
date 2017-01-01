
# -L is the path to the directories containing the libraries. A search path for libraries.
# -l is the name of the library you want to link to.
# -I tells gcc to add the directory ../include to the include path it uses to search for include files.

OS := $(shell uname)

CFLAGS = -std=c++11 -g -Wall
ifeq ($(OS), Darwin)  # OSX
	LDFLAGS = -L/opt/local/lib
	LDLIBS = -lboost_coroutine-mt -lboost_system-mt
	CINCLUDES = -I/opt/local/include
else
	ifeq ($(OS), Linux)
		LDFLAGS = -L/usr/lib/x86_64-linux-gnu/
		LDLIBS = -lboost_coroutine -lboost_system
		CINCLUDES = -I/usr/include/boost
	else
		$(error This operating system is not supported)
	endif

endif
all:
	g++ $(CFLAGS) $(CINCLUDES) $(LDFLAGS) $(LDLIBS)  -o coroutine_simple coroutine_simple.cpp 
	g++ $(CFLAGS) $(CINCLUDES) $(LDFLAGS) $(LDLIBS)  -o coroutine_with_class coroutine_with_class.cpp 

clean:
	rm -rf *.o coroutine_simple coroutine_with_class *.dSYM
