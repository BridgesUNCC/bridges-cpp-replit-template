#ifndef SOCKET_CONNECTION_H
#define SOCKET_CONNECTION_H

#include "sio_client.h"
#include "internal/sio_packet.h"
#include <Bridges.h>
#include <GameGrid.h>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

#include <unistd.h>


namespace bridges {
	namespace game {

		///@brief This is meant to be an internal class, not something
		/// that the library user will use. Provides support for input
		/// handling for the Game API
		class KeypressListener {
			public:
				virtual void keyup(std::string JSONmessage) = 0;
				virtual void keydown(std::string JSONmessage) = 0;
		};

		///@brief This is meant to be an internal class, not something
		/// that the library user will use
		///
		///  This class provide  functionality for making socket connections
		///	 to the Bridges Game server
		///
		/// @author Erik Saule, David Burlinson
		/// @date 2019, 12/29/20
		class SocketConnection {
				bool debug = false;
				sio::client client;
				sio::socket::ptr current_socket;

				bridges::Bridges& bridges;

				std::mutex _lock;

				std::condition_variable_any _cond; //condition used to wait on connection to be established
				bool connect_finish = false;

				std::list<KeypressListener*> key_listeners;

			private:
				///This is a trick to convert a SocketIO message back to a JSON object (which it was originally.)
				///This will make the future interface a lot easier to manage.
				std::string getJSON( sio::message::ptr msg ) {
					//This function is from SocketIO's issues.
					static sio::packet_manager manager;
					static std::mutex packetLock;
					std::lock_guard< std::mutex > guard( packetLock );


					std::stringstream ss;
					sio::packet packet( "/", msg );
					manager.encode( packet, [&](bool isBinary, std::shared_ptr<const std::string> const & json) {
						ss << *json;
						assert( !isBinary );
					});
					manager.reset();

					// Need to strip off the message type flags (typically '42',
					// but there are other possible combinations).
					std::string result = ss.str();
					std::size_t indexList = result.find( '[' );
					std::size_t indexObject = result.find( '{' );
					std::size_t indexString = result.find( '"' );
					std::size_t index = indexList;
					if ( indexObject != std::string::npos && indexObject < index )
						index = indexObject;
					if ( indexString != std::string::npos && indexString < index )
						index = indexString;

					if ( index == std::string::npos ) {
						std::cerr << "Error decoding json object" << std::endl << " Body: " << result << std::endl;
						return "";
					}
					return result.substr(index);
				}

			public:

				//Bridges object should have been initialized with correct
				//credentials and server at this point.
				SocketConnection(bridges::Bridges& b)
					: bridges(b) {
					client.set_open_listener(std::bind(&SocketConnection::on_connected, this));
					client.set_close_listener(std::bind(&SocketConnection::on_close, this, std::placeholders::_1));
					client.set_fail_listener(std::bind(&SocketConnection::on_fail, this));

					std::string serverURL = bridges.getServerURL();

					if (debug)
						std::cerr << "connecting SocketIO with " << serverURL << "\n";

					client.connect(serverURL); //get from bridges object

					wait_on_connection();

					usleep(100000);

					current_socket = client.socket();

					current_socket->on("keyup", std::bind(&SocketConnection::forwardKeyUp, this, std::placeholders::_1));
					current_socket->on("keydown", std::bind(&SocketConnection::forwardKeyDown, this, std::placeholders::_1));
					current_socket->on("announcement", std::bind(&SocketConnection::on_announcement, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

					sendCredentials();
				}

				void registerKeyListener(KeypressListener* p) {
					std::lock_guard< std::mutex > guard( _lock );

					key_listeners.push_back(p);
				}

				void forwardKeyUp(sio::event & e) {
					std::lock_guard< std::mutex > guard( _lock );

					std::string jsonmsg = getJSON(e.get_message());

					if (debug)
						std::cerr << "forwardKeyUp:" << e.get_nsp() << " " << e.get_name() << " : " << jsonmsg << "\n";

					for (auto& ptr : key_listeners)
						ptr->keyup(jsonmsg);
				}

				void forwardKeyDown(sio::event & e) {
					std::lock_guard< std::mutex > guard( _lock );

					std::string jsonmsg = getJSON(e.get_message());

					if (debug)
						std::cerr << "forwardKeyDown:" << e.get_nsp() << " " << e.get_name() << " : " << jsonmsg << "\n";

					for (auto& ptr : key_listeners)
						ptr->keydown(jsonmsg);
				}


				~SocketConnection() {
					client.sync_close();
					client.clear_con_listeners();
				}

				void sendCredentials() {
					std::lock_guard< std::mutex > guard( _lock );
					if (debug)
						std::cerr << "Sending credentials\n";

					std::string user = bridges.getUserName();
					std::string apikey = bridges.getApiKey();

					auto assID = bridges.getAssignment();

					current_socket->emit("credentials",
						"{\"user\":\"" + user
						+ "\",\"apikey\":\"" + apikey
						+ "\",\"assignment\":\"" + std::to_string(assID)
						+ "\"}");
					if (debug)
						std::cerr << "Credentials sent\n";
				}

				void on_connected() {
					std::lock_guard< std::mutex > guard( _lock );
					if (debug)
						std::cout << "connected!!\n";

					_cond.notify_all();
					connect_finish = true;
				}
				void on_close(sio::client::close_reason const& reason) {
					std::cout << "sio closed\n";
					exit(0);
				}

				void on_fail() {
					std::cout << "sio failed\n";
					exit(0);
				}

				void on_announcement (std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp) {
					if (debug)
						std::cerr << "announcement something\n";
				}

				void wait_on_connection () {
					//can't use lock guard since we need to wait on a condition
					_lock.lock();
					if (!connect_finish) {
						_cond.wait(_lock);
					}
					_lock.unlock();

				}

				void sendGameGrid(const GameGrid& gg) {
					if (debug)
						std::cerr << "Sending GameGrid\n";
					std::string gridjson = "{" + gg.getDataStructureRepresentation();

					current_socket->emit("gamegrid:recv", gridjson);
				}
		};
	}
}

#endif
