CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++11
LDLIBS += -lgrpc++ -lgrpc++_reflection

PREFIX = route_guide

SRVR_SRC = $(PREFIX)_server.cc helper.cc
CLNT_SRC = $(PREFIX)_client.cc helper.cc

SRVR_OBJ=$(SRVR_SRC:.cc=.o)
CLNT_OBJ=$(CLNT_SRC:.cc=.o)

all: server client

server: route_guide.pb.o route_guide.grpc.pb.o $(SRVR_OBJ)
	$(CXX) -o $@ $^ $(LDLIBS)

client: route_guide.pb.o route_guide.grpc.pb.o $(CLNT_OBJ)
	$(CXX) -o $@ $^ $(LDLIBS)

%.grpc.pb.cc: %.proto
	protoc --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` $<

%.pb.cc: %.proto
	protoc --cpp_out=. $<

clean:
	rm -f *.o *.pb.cc *.pb.h client server 
	
.PHONEY: all clean