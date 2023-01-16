#ifndef GRAPH_ADJ_LIST
#define GRAPH_ADJ_LIST

#include <stdexcept>
#include <sstream>
#include <unordered_map>
#include <JSONutil.h>


using namespace std;

#include "SLelement.h"
#include "Edge.h"

namespace bridges {
	namespace datastructure {
		/** @brief This class provides methods to represent adjacency list
		 *	based graphs.
		 *
		 *
		 *	The GraphAdjList class can be used to represent adjacency list
		 *  based graphs in BRIDGES; it takes 3 generic parameters: (1) K,
		 *  which is an orderable key value used in accessing vertices (in
		 *  constant time) using an STL map. This permits data sets that
		 *  need to be accessed by keys that are strings, (2) E1, for
		 *  maintaining vertex specific data, and (3) E2, for maintaining
		 *  edge specific data.  The class is a wrapper around the C++
		 *  unordered map class and, thus, derives all its operations from it.
		 *  BRIDGES provides methods to visualize the graph and its
		 *  contents.
		 *
		 *  The vertices of the graph are held in a C++ hashmap, for near
		 *  constant time access; this enables us to use strings or integer ids
		 *  for vertices. The adjacency lists are linked lists of SLelemnt type,
		 *  The SLelement contains edge information (stored in its data as a
		 *	generic). Each edge, of type Edge, contains the source,
		 *  destination vertices and link attributes (color, opacity, thickness)
		 *
		 *
		 * Convenience method addVertex() is provided to add vertices to
		 * the graph, and addEdge() is provided to add edges.  Edges are
		 * retrieved by using the map and the adjcency list, given the vertex
		 * ids of the edge. Vertices can be styled directly from the vertex element
		 * returned by getVertex(), and edges are styled from a LinkVisualizer
		 * one can access through getLinkVisualizer(). Here is a simple example:
		 *\code{c}
		 * GraphAdjList<string, Integer, Double> graph = new GraphAdjList<string, int, double> ();
		 *   graph.addVertex("a");
		 *   graph.addVertex("b");
		 *   graph.addEdge("a", "b");
		 *   graph.getVertex("a").setShape("square");
		 *   graph.getLinkVisualizer("a", "b").setColor("yellow");
		 *\endcode
		 *
		 * Adjacency lists are singly linked lists using the BRIDGES
		 * SLelement. Iterators are provided for easy traversal of the
		 * adjacency lists. For instance,
		 *
		 *
		 *\code{c}
		 * GraphAdjList<string, int, double> graph = something();
		 * for (Edge<string, double> e : graph.outgoingEdgeSetOf("a"))
		 *   System.out.println("a -> "+e.getTo());
		 *\endcode
		 *
		 * Graphs can have their nodes and links affected by visual attributes. Nodes
		 * can have color, size, opacity and shape and  detailed in the ElementVisualizer
		 * class. Edges support attributes such as color, thickness and opacity and are
		 * detailed in the LinkVisualizer class.  Element and link attributes are set
		 * using the getVisualizer() and getLinkVisualizer() methods.  For instance,
		 *
		 *\code{c}
		 * GraphAdjList<string, int, double> graph = something();
		 *   graph.addVertex("baskin");
		 *   graph.addVertex("robins");
		 *   graph.addEdge("baskin","robins");
		 *   graph.getVisualizer()->setColor("cyan");
		 *   graph.getVisualizer()->setShape("square");
		 *   graph.getLinkVisualizer("baskin", "robins")->setColor("green");
		 *   graph.getLinkVisualizer("baskin", "robins")->setOpacity("0.5f");
		 *\endcode

		 *
		 *
		 * @param K: used as an index to retrieve vertices,
		 * @param E1: data type used to store vertex specific information,
		 * @param E2: data type used to store edge specific information
		 *
		 * @author Kalpathi Subramanian, Erik Saule
		 * @date Last modified 4/22/18, 7/12/19, 12/28/20, 1/5/21
		 *
		 * There is a tutorial about Graph Adjacency List  :
		 * https://bridgesuncc.github.io/tutorials/Graph.html
		 *
		 *
		 * There are two visualization engines available for
		 * graph. The small graph visualization supports all
		 * attributes of vertices and edges but is
		 * prohibitively slow on large graphs. The large graph
		 * visualization only supports locations (actually
		 * they are mandatory) and colors, all other
		 * attributes are ignored.
		 *
		 * BRIDGES picks the rendering engine
		 * automatically. But it can be forced to pick one
		 * used forceLargeVizualization() and
		 * forceSmallVizualization()
		 *
		 */
		template<typename K, typename E1 = K, typename E2 = E1>
		class GraphAdjList : public DataStructure {
			private:
				// list of graph vertices
				// maintained as a map to accommodate strings
				unordered_map<K, Element<E1>* > vertices;
				// adjacency lists
				unordered_map<K, SLelement<Edge<K, E2> >*> adj_list;

				// large graph related
				static const int LargeGraphVertSize = 2000;

				bool forceLargeViz = false;
				bool forceSmallViz = false;


				GraphAdjList(const GraphAdjList& gr) = delete; //would not be correct
				const GraphAdjList& operator= (const GraphAdjList& gr) = delete; //would not be correct
			public:

				GraphAdjList() = default;
				GraphAdjList(GraphAdjList&& gr) = default;

				virtual ~GraphAdjList() override {
					for (auto& v : vertices) {
						if (adj_list[v.first]) {
							// discard the edges in the adj. list
							SLelement<Edge<K, E2>> *tmp;
							for (SLelement<Edge<K, E2>> *sle =
									adj_list[v.first]; sle != nullptr; ) {
								tmp = sle;
								sle = sle->getNext();
								delete tmp;
							}
							adj_list[v.first] = nullptr;
						}
						delete vertices[v.first]; // free the element at v
						vertices[v.first] = nullptr;

					}
				}
				/**
				 *	@brief Get the string representation of this data structure type.
				 *
				 *	@return The string representation of this data structure type
				 */
				virtual const string getDStype() const override {
					if (forceLargeViz || (!forceSmallViz &&
							vertices.size() > LargeGraphVertSize &&
							areAllVerticesLocated())) {
						return "largegraph";
					}
					return "GraphAdjacencyList";
				}

				/**
				 *  @brief Adds a vertex to the graph.
				 *
				 * 	Adds a vertex of key "k" and value "e" to the graph,
				 *	and initializes its adjacency list; If this key already
				 *	exists  then this will not create a new vertex.
				 *
				 *
				 * @param k The vertex key
				 * @param e The vertex data
				 *
				 */
				void addVertex(const K& k, const E1& e = E1()) {
					stringstream conv;
					conv << k;
					if (vertices.find(k) == vertices.end()) {
						// vertex does not exist, create one
						vertices[k] = new Element<E1>(e, conv.str());
						adj_list[k] = nullptr;
					}
				}
				/**
				 * 	@brief Add an edge with data.
				 *
				 *  Note that this function adds the edge regardless of
				 *	the contents of the adjacency list; its the user's responsibility
				 *	to ensure there are no duplicates and ensure consistency.
				 *
				 * @param src The key of the source Vertex
				 * @param dest The key of the destination Vertex
				 * @param data The edge data
				 * @throw out_of_range If "src" or "dest" is non-existent within
				 *	this graph
				 * @throw bad_alloc If allocation of a graph adjacency list item failed
				 */
				void addEdge(const K& src, const K& dest, const E2& data = E2()) {
					try {
						vertices.at(src);
						vertices.at(dest);
						// links structure is redundant and needs
						// to be removed in future implementations!
						vertices[src]->links[vertices.at(dest)]; //In C++ this creates the linkvisualizer

						stringstream conv;
						conv << dest;
						// add the edge
						adj_list.at(src) =
							new SLelement<Edge<K, E2> > (adj_list.at(src),
							Edge<K, E2> (src, dest, &(vertices[src]->links[vertices.at(dest)]), data), conv.str());

					}
					catch ( const out_of_range& ) {
						cerr << "addEdge(): Nonexistent vertex?" << endl <<
							"Create vertices first prior to adding edges that use that vertex" << endl
							<<  "Cannot add edge between non-existent verticies"
							<< endl;
						throw;
					}
				}
				/**
				 * 	@brief Check if there is an edge between the given vertices
				 *
				 *
				 * @param src The key of the source Vertex
				 * @param dest The key of the destination Vertex
				 */
				bool isEdge(const K& src, const K& dest) {
					try {
						vertices.at(src);
						vertices.at(dest);
						for (auto& e : outgoingEdgeSetOf(src))
							if (e.to() == dest) { // found it
								cout << "found it!" << src << "," << dest << endl;
								return true;
							}
					}
					catch ( const out_of_range& ) {
						return false;
					}
					return false;
				}
				/**
				 * @brief Gets vertex data for a graph vertex.
				 *
				 * @param src The key of the source vertex
				 *
				 * @return E1  vertex specific data
				 */
				const E1&  getVertexData (const K& src)& {
					try {
						Element<E1> *el = vertices.at(src);
						return  (vertices.at(src))->getValue();
					}
					catch ( const out_of_range& ) {
						cerr << "getVertexData(): vertex not found" << endl;
						throw;
					}
					// should never reach here
					throw "getVertexData(): vertex not found";
				}
				/**
				 * @brief Loads vertex specific information for a graph vertex.
				 *
				 * @param vertID The key of Vertex
				 * @param data data to set
				 *
				 */
				void setVertexData (const K& vertID, E1 const & data) {
					try {
						Element<E1> *el = vertices.at(vertID);
						el->setValue (data);
					}
					catch ( const out_of_range& ) {
						cerr << "setVertexData(): Nonexistent vertex" << endl;
						throw;
					}
					catch (const char* msg) {
						cerr << msg << endl;
					}
				}
				/**
				 * @brief Gets edge data for the edge from "src" to "dest".
				 *
				 * @param src The key of the source Vertex
				 * @param dest The key of the destination Vertex
				 *
				 * @return   edge specific data
				 */
				E2&  getEdgeData (const K& src, const K& dest) {
					try {
						vertices.at(src);
						vertices.at(dest);
						SLelement<Edge<K, E2> > *sle = adj_list.at(src);
						while (sle) {
							Edge<K, E2> ed = sle->getValue();
							if (ed.to() == dest) { //edge exists
								return ed.getEdgeData();
							}
							sle = sle->getNext();
						}
						throw "Edge not found!";
					}
					catch ( const out_of_range& ) {
						cerr << "getEdgeData(): Edge not found" << endl;
						throw;
					}
					catch (const char* msg) {
						cerr << msg << endl;
					}
					// should never reach here
					throw "getEdgeData(): Edge not found";
				}
				/**
				 * @brief Gets edge data for the edge from "src" to "dest" - const version.
				 *
				 * @param src The key of the source Vertex
				 * @param dest The key of the destination Vertex
				 *
				 * @return edge specific data
				 */
				E2 const&  getEdgeData (const K& src, const K& dest) const {
					try {
						vertices.at(src);
						vertices.at(dest);
						SLelement<Edge<K, E2> > *sle = adj_list.at(src);
						while (sle) {
							Edge<K, E2> ed = sle->getValue();
							if (ed.getVertex() == dest) { //edge exists
								return ed.getEdgeData();
							}
							sle = sle->getNext();
						}
						throw "Edge not found!";
					}
					catch ( const out_of_range& ) {
						cerr << "getEdgeData(): Edge not found" << endl;
						throw;
					}
					catch (const char* msg) {
						cerr << msg << endl;
					}
					// should never reach here
					throw "getEdgeData(): Edge not found";
				}


				/**
				 * @brief Loads edge specific information for the edge from "src" to  "dest".
				 *
				 * @param src The key of the source Vertex
				 * @param dest The key of the destination Vertex
				 * @param data  edge data
				 *
				 */
				void setEdgeData (const K& src, const K& dest, E2& data) {
					try {
						vertices.at(src);
						vertices.at(dest);
						SLelement<Edge<K, E2> > *sle = adj_list.at(src);
						while (sle) {
							Edge<K, E2> ed = sle->getValue();
							if (ed.getVertex() == dest) { //edge exists
								ed.setEdgeData(data); //change edge data
								sle->setValue(ed); //change slelement data
								return;
							}
							sle = sle->getNext();
						}
						throw "getEdgeData(): Edge not found!";
					}
					catch ( const out_of_range& ) {
						cerr << "setEdgeData(): Nonexistent vertices or " <<
							" edge not found" << endl;
						throw;
					}
					catch (const char* msg) {
						cerr << msg << endl;
					}
					// will never reach here, but avoids compiler warnings
					throw "getEdgeData(): Edge not found";
				}
				/**
				 * @brief Return the graph nodes.
				 *
				 * @return The vertex list of this graph
				 */
				unordered_map<K, Element<E1>*>* getVertices() {
					return &vertices;
				}

				/**
				 *  @brief Return the graph nodes - const version.
				 *
				 *	@return The vertex list of this graph
				 */
				const unordered_map<K, Element<E1>*>* getVertices() const {
					return &vertices;
				}
				/**
				 *  @brief Return the vertex corresponding to a key.
				 *
				 *	@return the requested vertex of this graph or nullptr if not found
				 */
				const Element<E1>* getVertex(const K& key) const {
					try {
						return vertices.at(key);
					}
					catch (const std::out_of_range& oor) {
						/* std::cerr << "Out of Range error: " << oor.what() */
						/* 	<< "returning null pointer\n"; */
						return nullptr;
					}
				}


				/**
				 *  Return the requested vertex corresponding to a key - non-const version
				 *	@return the requested vertex of this graph or nullptr if not found
				 *
				 */
				Element<E1>* getVertex(const K& key) {
					try {
						return vertices.at(key);
					}
					catch (const std::out_of_range& oor) {
						/* std::cerr << "Out of Range error: " << oor.what() */
						/* 	<< "returning null pointer\n"; */
						return nullptr;
					}
				}

				/**
				 * @brief Get the edge between src and dest vertices.
				 *
				 * @param src  source vertex of edge
				 * @param dest  destination vertex of edge
				 * @return edge between the vertices
				 */
				Edge<K, E2> getEdge(const K& src, const K& dest) {
					// check to see if the two vertices exist, else
					// return null
					try  {
						// look for the edge
						SLelement<Edge<K, E2>> *sle = adj_list[src];
						while (sle != nullptr) {
							K edge_dest = ((Edge<K, E2>) sle->getValue()).to();
							if (edge_dest == dest)	// found
								return sle->getValue();
							sle = sle->getNext();
						}
					}
					catch (const std::out_of_range& oor) {
						// one or both vertices doesnt exist
						std::cout << "one or both vertices are likely missing from graph\n";
						throw;
					}
					throw "Edge not found";
				}

				/**
				 *  @brief Return the adjacency list.
				 *	@return The adjacency list  of the graph
				 */
				const unordered_map<K, SLelement<Edge<K, E2> >*>&
				getAdjacencyList() const {
					return adj_list;
				}

				/**
				 * @brief Returns adjacency list of a vertex with name k.
				 *
				 * @param k The key of the source vertex
				 * @throw out_of_range If key is non-existent within this graph
				 *
				 * @return The adjacency list of key "k"
				 */
				SLelement<Edge<K, E2> >* getAdjacencyList(const K& k) {
					try {
						return adj_list.at(k);
					}
					catch (const out_of_range& ) {
						cerr <<  "Cannot get adjacencyList of a non-existent vertex -- " << k << "\n";
						throw;
					}
				}

				/**
				 * Returns adjacency list of a vertex with name k - const version
				 *
				 * @param k The key of the source vertex
				 * @throw out_of_range If key is non-existent within this graph
				 *
				 * @return The adjacency list of key "k"
				 */
				const SLelement<Edge<K, E2> >* getAdjacencyList(const K& k) const {
					try {
						return adj_list.at(k);
					}
					catch (const out_of_range& ) {
						cerr <<  "Cannot getAdjacencyList() of a non-existent vertex!"
							<< endl;
						throw;
					}
				}


				/**
				 *  @brief Returns the  visualizer corresponding to  a graph vertex.
				 *	convenient method to set attributes of the graph vertex
				 *
				 *  @param k The key of the graph vertex
				 *
				 *  @return the visualizer that controls the attributes  of this node
				 */
				ElementVisualizer *getVisualizer (const K& k) {
					try {
						Element<E1> *el = vertices.at(k);

						return el->getVisualizer();
					}
					catch (const out_of_range& ) {
						cerr <<  "Graph vertex " << k << " not found in graph!" << endl;
						throw;
					}
				}
				/**
				 *  @brief Returns the link visualizer corresponding to an edge.
				 *  Returns the link visualizer corresponding to two graph
				 *	nodes with an existing link; error returned if no link exists.
				 *
				 *  @param k1 The key of the link source vertex
				 *  @param k2 The key of the link destination  vertex
				 *
				 * @return the visualizer that controls the attributes  of this link
				 */
				LinkVisualizer *getLinkVisualizer (const K& k1, const K& k2) {
					try {
						return getEdge(k1, k2).getLinkVisualizer();
					}
					catch (const out_of_range& ) {
						cerr <<  "Either source or destination node not found in graph!\n";
						throw;
					}
				}
			private:
				/**
				 * Gets the JSON representation of this Graph's nodes and links
				 *
				 * @return A pair holding the nodes and links JSON strings respectively
				 */
				virtual const string getDataStructureRepresentation() const override {
					using bridges::JSONUtil::JSONencode;

					// map the nodes to a sequence of ids, 0...N-1
					// then get the JSON string for nodes placeholder
					// nullptr prevents insertion of other nullptrs

					// check for large graph
					if (forceLargeViz ||
						(!forceSmallViz &&
							vertices.size() > LargeGraphVertSize &&
							areAllVerticesLocated())) {
						return getDataStructureRepresentationLargeGraph();
					}

					unordered_map<K, int> node_map;
					int i = 0;
					string nodes_JSON = "", links_JSON = "";

					for (const auto& v : vertices) {
						if (node_map.emplace(v.first, i).second) {
							i++;
							nodes_JSON += v.second->getElementRepresentation() + COMMA;
						}
					}

					//Remove trailing comma and nullptr entry

					if (nodes_JSON.size()) {
						nodes_JSON = nodes_JSON.erase(nodes_JSON.size() - 1);
					}

					// iterate through the vertices and form the links JSON

					for (const auto& v : vertices) {
						// get adj. list
						Element<E1>* src_vert = vertices.at(v.first);
						// iterate through list and form links
						for (SLelement<Edge<K, E2>>* it = adj_list.at(v.first); it != nullptr;
							it = it->getNext()) {
							Element<E1>* dest_vert = vertices.at(it->getValue().to() );
							links_JSON +=  src_vert->getLinkRepresentation(
									*(src_vert->getLinkVisualizer(dest_vert)),
									JSONencode(node_map.at(v.first)),
									JSONencode(node_map.at(it->getValue().to())) ) + COMMA;
						}
					}

					//Remove trailing comma
					if (links_JSON.size()) {
						links_JSON = links_JSON.erase(links_JSON.size() - 1);
					}

					string graph_alist_json =
						QUOTE + "nodes"  + QUOTE + COLON +
						OPEN_BOX + nodes_JSON + CLOSE_BOX + COMMA +
						QUOTE + "links" + QUOTE + COLON + OPEN_BOX +
						links_JSON + CLOSE_BOX +
						CLOSE_CURLY;


					return graph_alist_json;
				}
				/**
				 *
				 *  For large graphs, we will use a very lean representation,
				 *	just the nodes and links and
				 *  only the color property; currently this is for OSM data
				 *	only. Contain only location and
				 *	color attributes
				 *
				 */

				string getDataStructureRepresentationLargeGraph () const {

					using bridges::JSONUtil::JSONencode;
					// map the nodes to a sequence of ids, 0...N-1
					// then get the JSON string for nodes placeholder
					// nullptr prevents insertion of other nullptrs

					unordered_map<K, int> node_map;
					int i = 0;
					string nodes_JSON = "";

					for (const auto& v : vertices) {
						if (node_map.emplace(v.first, i).second) {
							i++;
							const ElementVisualizer *elvis =
								vertices.at(v.first)->getVisualizer();
							string loc_str = "";
							if ( (elvis->getLocationX() != INFINITY) &&
								(elvis->getLocationY() != INFINITY) ) {
								loc_str =
									OPEN_BOX +
									JSONencode(elvis->getLocationX())  + COMMA +
									JSONencode(elvis->getLocationY()) +
									CLOSE_BOX + COMMA;
							}
							nodes_JSON +=  OPEN_BOX + loc_str +
								elvis->getColor().getCSSRepresentation() +
								CLOSE_BOX + COMMA;
						}
					}

					//Remove trailing comma and nullptr entry

					if (nodes_JSON.size()) {
						nodes_JSON = nodes_JSON.erase(nodes_JSON.size() - 1);
					}

					// next link information
					string links_JSON =  "";
					for (const auto& v : vertices) {
						// get adj. list
						Element<E1>* src_vert = vertices.at(v.first);
						// iterate through list and form links
						for (SLelement<Edge<K, E2>>* it = adj_list.at(v.first); it != nullptr;
							it = it->getNext()) {
							Element<E1>* dest_vert = vertices.at(it->getValue().to() );
							LinkVisualizer *lv = src_vert->getLinkVisualizer(dest_vert);
							string src = JSONencode(node_map.at(v.first));
							string dest = JSONencode(node_map.at(it->getValue().to()));
							links_JSON +=  OPEN_BOX +
								src  + COMMA +
								dest + COMMA +
								lv->getColor().getCSSRepresentation() +
								CLOSE_BOX + COMMA;

						}
					}
					//Remove trailing comma
					if (links_JSON.size())
						links_JSON = links_JSON.erase(links_JSON.size() - 1);

					string graph_alist_json =
						QUOTE + "nodes"  + QUOTE + COLON +
						OPEN_BOX + nodes_JSON + CLOSE_BOX + COMMA +
						QUOTE + "links" + QUOTE + COLON +
						OPEN_BOX + links_JSON + CLOSE_BOX +
						CLOSE_CURLY;

					return graph_alist_json;

				}
				/**
				 * @return true if all vertices have both an x and y location
				 */
				bool areAllVerticesLocated() const {
					for (const auto& v : vertices) {
						ElementVisualizer *elvis = v.second->getVisualizer();
						if (elvis->getLocationX() == INFINITY
							|| elvis->getLocationY() == INFINITY)
							return false;
					}
					return true;
				}


			public:

				/**
				*
				* @brief Force the rendering engine to use large graph
				*	visualization.
				*
				* This forces the rendering to a more bandwidth
				* efficient at the cost of having less features. The large
				* graph visualization only renders vertices that have
				* specified locations. The only usable attribute for
				* vertices and edges are colors.
				*
				* @param f set to true to force the visualization engine to
				*  use large graphs visualization. Setting to false does not
				*  prevent large visualization to be used, just does not force it.
				*
				*/
				void forceLargeVisualization(bool f) {
					if (f) {
						forceLargeViz = true;
						forceSmallViz = false;
					}
					else {
						forceLargeViz = false;
					}
				}

				/**
				 *
				 * @brief Force the rendering engine to use small graph
				 * visualization
				 *
				 *
				 * The small visualization uses more bandwidth, have more
				 * features, and support a force directed layout for vertices
				 * which do not have a specified location.
				 *
				 * @param f set to true to force the visualization engine to
				 *	use small graphs visualization. Setting to false does not
				 *	prevent small visualization to be used, just does not
				 *	force it.
				 *
				 */
				void forceSmallVisualization(bool f) {
					if (f) {
						forceSmallViz = true;
						forceLargeViz = false;
					}
					else {
						forceSmallViz = false;
					}
				}

				//	@brief This is a helper class to return sets of vertices
				// 	in a  way that are iterable with range for loops.
				//	Students should not have to use this directly.
				class KeySet_helper {
						std::unordered_map<K, Element<E1>* > const & underlying_map;

					public:
						KeySet_helper (std::unordered_map<K, Element<E1>* > const  & um)
							: underlying_map(um)
						{}

						class const_iterator {
								typename std::unordered_map<K, Element<E1>* >::const_iterator it;
							public:
								const_iterator(typename std::unordered_map<K, Element<E1>* >::const_iterator i )
									: it(i)
								{}

								bool operator!=(const const_iterator& it) const {
									return this->it != it.it;
								}

								const K& operator*() const {
									return it->first;
								}

								const_iterator& operator++() {
									it ++;
									return *this;
								}
						};

						const_iterator begin() const {
							return const_iterator(underlying_map.begin());
						}

						const_iterator end() const {
							return const_iterator(underlying_map.end());
						}
				};

				/**
				 *  Returns a set of all keys  (helper function).
				 *
				 *	Returns a set of all keys (read only) that conforms to
				 *	STL list interface.  That means we can use range for loops
				 *	on graph vertices.
				 *
				 *  @return set all keys
				 */
				KeySet_helper keySet() const {
					return KeySet_helper(this->vertices);
				}

				/**
				 *	@brief This method is useful for iterating through a set of
				 *  outgoing edges from a vertex.
				 */
				typename SLelement<Edge<K, E2>>::SLelement_listhelper
				outgoingEdgeSetOf(K const & k) {
					return typename SLelement<Edge<K, E2>>::SLelement_listhelper(getAdjacencyList(k));
				}

				/**
				 *	@brief This method is useful for iterating through a set of
				 *  outgoing edges from a vertex - const version.
				 */
				typename SLelement<Edge<K, E2>>::SLelement_constlisthelper
				outgoingEdgeSetOf(K const & k) const {
					return typename SLelement<Edge<K, E2>>::SLelement_constlisthelper(getAdjacencyList(k));
				}


				/**
				 *	@brief This is a helper class to return sets of vertices
				 *	in a way that are iterable with range for loops. Students
				 *	should have to use this directly.
				 */
				class VertexElementSet_listhelper {
						typename std::unordered_map<K, Element<E1>* > & underlying_map;

					public:
						VertexElementSet_listhelper (std::unordered_map<K, Element<E1>* > & um)
							: underlying_map(um)
						{}

						/**
						 * 	@brief This is a helper class to return sets of
						 *	vertices in a way that are iterable with range
						 *	for loops. Students should have to use this directly.
						 */
						class iterator {
								typename std::unordered_map<K, Element<E1>* >::iterator it;
							public:
								iterator(typename std::unordered_map<K, Element<E1>* >::iterator i )
									: it(i)
								{}

								bool operator!=(const iterator& it) const {
									return this->it != it.it;
								}

								Element<E1>*  operator*()  {
									return it->second;
								}

								iterator& operator++() {
									it ++;
									return *this;
								}
						};

						/**
						 * @brief This is a helper class to return sets of
						 *	vertices in a way that are iterable with range for
						 *  loops. Students should have to use this directly.
						 */
						class const_iterator {
								typename std::unordered_map<K, Element<E1>* >::const_iterator it;
							public:
								const_iterator(typename std::unordered_map<K, Element<E1>* >::const_iterator i )
									: it(i)
								{}

								bool operator!=(const const_iterator& it) const {
									return this->it != it.it;
								}

								Element<E1> const*  operator*() const {
									return it->second;
								}

								const_iterator& operator++() {
									it ++;
									return *this;
								}
						};


						iterator begin() {
							return iterator(underlying_map.begin());
						}

						iterator end() {
							return iterator(underlying_map.end());
						}

						const_iterator begin() const {
							return const_iterator(underlying_map.begin());
						}

						const_iterator end() const {
							return const_iterator(underlying_map.end());
						}

				};

				/**
				 * Returns a set of vertices (Element<E>) that conforms to
				 *	STL list interface. That means we can use range for
				 */
				VertexElementSet_listhelper vertexSet () {
					return VertexElementSet_listhelper(vertices);
				}


				/**
				 * @brief This is a helper class to return sets of vertices
				 *	in a  way that are iterable with range for loops.
				 * 	Students should not have to use this directly.
				 */
				class constVertexElementSet_listhelper {
						typename std::unordered_map<K, Element<E1>* > const & underlying_map;

					public:
						constVertexElementSet_listhelper (std::unordered_map<K, Element<E1>* > const& um)
							: underlying_map(um)
						{}

						///@brief This is a helper class to return sets of vertices ina  way that are iterable with range for loops. Students should not have to use this directly.
						class const_iterator {
								typename std::unordered_map<K, Element<E1>* >::const_iterator it;
							public:
								const_iterator(typename std::unordered_map<K, Element<E1>* >::const_iterator i )
									: it(i)
								{}

								bool operator!=(const const_iterator& it) const {
									return this->it != it.it;
								}

								Element<E1> const*  operator*() const {
									return it->second;
								}

								const_iterator& operator++() {
									it ++;
									return *this;
								}
						};

						const_iterator begin() const {
							return const_iterator(underlying_map.begin());
						}

						const_iterator end() const {
							return const_iterator(underlying_map.begin());
						}
				};
				/**
				 * Returns a set of vertices (Element<E>) that conforms to STL
				 * 	list interface. That means we can use range for
				 */
				constVertexElementSet_listhelper vertexSet () const {
					return constVertexElementSet_listhelper(vertices);
				}
		};

		//end of GraphAdjList class
	}
}//end of bridges namespace
#endif
