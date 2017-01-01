
# -L is the path to the directories containing the libraries. A search path for libraries.
# -l is the name of the library you want to link to.
# -I tells gcc to add the directory ../include to the include path it uses to search for include files.

OS := $(shell uname)

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
CFLAGS = -std=c++11 -g -Wall
# INCLUDE BASE DIRECTORY AND BOOST DIRECTORY FOR HEADERS
all:
	g++ $(CFLAGS) $(CINCLUDES) $(LDFLAGS) $(LDLIBS)  -o coroutine_simple coroutine_simple.cpp 
	g++ $(CFLAGS) $(CINCLUDES) $(LDFLAGS) $(LDLIBS)  -o coroutine_with_class coroutine_with_class.cpp 

clean:
	rm -rf *.o coroutine_simple coroutine_with_class *.dSYM



#CFLAGS= -std=c++11 -g -Wall
# INCLUDE BASE DIRECTORY AND BOOST DIRECTORY FOR HEADERS
#LDFLAGS := -I/opt/local/include
#LDLIBS := -L/opt/local/lib
#LDLIBS := -lboost_system-mt -lboost_coroutine-mt 

#all:
#	g++ $(CFLAGS) -L/opt/local/lib $(LDFAGS) $(LDLIBS)   -o run-this main.cpp 

#clean:
#	rm *.o run-this

