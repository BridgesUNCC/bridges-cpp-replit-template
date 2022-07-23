SOCKETIOFLAGS=-D BOOST_DATE_TIME_NO_LIB -D BOOST_REGEX_NO_LIB -D ASIO_STANDALONE -D _WEBSOCKETPP_CPP11_STL_ -D _WEBSOCKETPP_CPP11_FUNCTIONAL_
SOCKETIOINCLUDES=-I ../lib/asio/asio/include -I ../lib/websocketpp -I ../../rapidjson/include

CXXFLAGS=$(SOCKETIOINCLUDES) $(SOCKETIOFLAGS) -std=c++14


all: libsioclient.a

libsioclient.a: sio_client.o sio_socket.o internal/sio_client_impl.o internal/sio_packet.o
	ar qc libsioclient.a sio_client.o sio_socket.o internal/sio_client_impl.o internal/sio_packet.o

