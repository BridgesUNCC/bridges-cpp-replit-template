#ifndef GRAPH_ADJ_MATRIX_H
#define GRAPH_ADJ_MATRIX_H

#include <stdexcept>    //out of range
#include <sstream>      //stringstream

#include "Element.h"    //DataStructure, unordered_map, string, cerr, using std

namespace bridges {
	namespace datastructure {
		/**
		 *	@brief This class provides methods to represent adjacency matrix based
		 *	graphs.
		 *
		 *	The class is simply a wrapper around the C++ STL unordered_map class
		 *	and thus derives all its operations from it.  Given the use of operator
		 *	overloading, the adjacency matrix implementation is almost identical
		 *	to a normal array representation, except that any ordered type can
		 *	be used to index into the matrix.
		 *
		 *  Since the adjacency matrix typically contains only a numerical value,
		 *  we keep edge specific information in a separate map using a generic
		 *	parameter for the type.
		 *
		 *	Generic Parameters:
		 *		K that is used as an index,
		 *		E1 information specific to graph vertices
		 *		E2 information specific to graph edges
		 *
		 *	@author Kalpathi Subramanian, Dakota Carmer
		 *	@date 6/29/15, 7/10/16, 11/27/16, 4/22/18
		 *
		 * There is a tutorial about Graph Adjacency Matrix  :
		 * https://bridgesuncc.github.io/tutorials/Graph_AM.html
		 */
		template <typename K, typename E1 = K, typename E2 = E1>
		class GraphAdjMatrix : public DataStructure {
			private:
				unordered_map<K, Element<E1>* > vertices; // graph vertices
				unordered_map<K, unordered_map<K, int> > matrix; // adjacency matrix
				// maintain edge specific data
				unordered_map<K, unordered_map<K, E2> > edge_data;

			public:
				/**
				 *	@return The string representation of this data structure type
				 */
				virtual const string getDStype() const override {
					return "GraphAdjacencyMatrix";
				}

		  virtual ~GraphAdjMatrix() {
		    for (auto it : vertices)
		      delete it.second;
		  }
		  GraphAdjMatrix() = default;

		  // The default version of these functions would be incorrect.
		  // So marking them delete to avoid problems.
		  // We could write them if necessary
		  GraphAdjMatrix(const GraphAdjMatrix&) = delete;
		  GraphAdjMatrix& operator=(const GraphAdjMatrix&) = delete;

		  
				/**
				 * Adds a vertex of key "k" and value "e" to the graph.
				 * Sets all of its edges to be of weight 0.
				 *
				 * @param k Vertex key
				 * @param e Vertex data
				*/
				void addVertex(const K& k, const E1& e = E1()) {
					stringstream conv;
					conv << k; //Converts key into string
					vertices[k] = new Element<E1>(e, conv.str());
					for (const auto& p : vertices) {
						// edge weights are 0
						matrix[k][p.first] = matrix[p.first][k] = 0;
					}
				}

				/**
				 * Sets the weight of the edge from "src" to "dest", to "wt".
				 * This will overwrite the existing edge weight.
				 *
				 * @param src The key of the source Vertex
				 * @param dest The key of the destination Vertex
				 * @param wt The weight of the edge
				 * @throw out_of_range If "src" or "dest" is non-existent
				 *	within this graph
				 */
				void addEdge(const K& src, const K& dest, const unsigned int& wt) {
					try { 					//create default link data
						vertices.at(src)->links[vertices.at(dest)];
						// add edge
						matrix.at(src).at(dest) = wt;
					}
					catch (const out_of_range& ) {
						cerr << "Cannot addEdge between non-existent verticies." << endl;
						throw;
					}
				}
				/**
				 *  Return the adjacency matrix
				 *	@return The matrix of this graphs edges
				 */
				const unordered_map<K, unordered_map<K, int>>& getMatrix() const {
					return matrix;
				}

				/**
				 *
				 *  Return the adjacency matrix row at Key key
				 *  @param key The input key value that identifies the row being
				 *				retrieved
				 *
				 *	@return The row  of this adjacency matrix corresponding to the
				 *			key
				 */
				const unordered_map<K, int>& getMatrix(K key) const {
					return matrix.at(key);
				}

				/**
				 *  Return the graph vertices
				 *	@return The graph verticies
				 */
				unordered_map<K, Element<E1> *>* getVertices() {
					return &vertices;
				}
				/**
				 *  Return the vertex correspondingto key "key" - const version
				 *  @return the requested vertex of this graph
				 */
				const Element<E1>* getVertex(const K& key) const {
					return vertices.at(key);
				}

				/**
				 *  Return the vertex correspondingto key "key"
				 *  @return the requested vertex of this graph
				 *
				 */
				Element<E1>* getVertex(const K& key) {
					return vertices.at(key);
				}
				/**
				 * Gets vertex data for a graph vertex
				 *
				 * @param src The key of the source vertex
				 *
				 * @return E  vertex specific data
				 */
				E1  getVertexData (const K& src) {
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
				 * 	Loads vertex specific information for a graph vertex
				 *
				 * @param vID vertex key
				 * @param data data to associate with the vertex
				 */
				void setVertexData (const K& vID, const E1& data) {
					try {
						Element<E1> *el = vertices.at(vID);
						el->setValue (data);
					}
					catch ( const out_of_range& ) {
						cerr << "setVertexData(): Nonexistent vertices or " <<
							" edge not found" << endl;
						throw;
					}
					catch (const char* msg) {
						cerr << msg << endl;
					}
				}
				/**
				 * 	Gets edge data for the edge from "src" to "dest"
				 *
				 * @param src The key of the source Vertex
				 * @param dest The key of the destination Vertex
				 *
				 * @return  edge specific data
				 */
				E2 const & getEdgeData (const K& src, const K& dest) const {
					try {
						vertices.at(src);
						vertices.at(dest);
						return edge_data[src][dest];
					}
					catch ( const out_of_range& oor) {
						cerr << "getEdgeData(): Nonexistent vertices or " <<
							" edge not found" << endl;
						throw;
					}
					catch (const char* msg) {
						cerr << msg << endl;
						throw;
					}
					// should never reach here
					throw "getEdgeData(): Edge not found";
				}
				/**
				 * @brief Loads edge information
				 *
				 * @param src The key of the source Vertex
				 * @param dest The key of the destination Vertex
				 * @param data data to associate with the edge
				 */
				void setEdgeData (const K& src, const K& dest, const E2& data) {
					try {
						vertices.at(src);
						vertices.at(dest);
						edge_data[src][dest] = data;
					}
					catch ( const out_of_range& oor) {
						cerr << "setEdgeData(): Nonexistent vertices or " <<
							" edge not found" << endl;
						throw;
					}
					catch (const char* msg) {
						cerr << msg << endl;
						throw;
					}
				}
				/**
				 *  Returns the  visualizer corresponding to  a graph vertex;
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
					catch (const out_of_range& oor) {
						cerr <<  "Graph vertex " << k << " not found in graph!" << endl;
						throw;
					}
				}
				/**
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
						Element<E1> *el1 = vertices.at(k1);
						Element<E1> *el2 = vertices.at(k2);

						return el1->getLinkVisualizer(el2);
					}
					catch (const out_of_range& oor) {
						cerr <<  "Either source or destination node not found in graph!"
							<< endl;
						throw;
					}
				}

			private:

				/**
				 * Gets the JSON representation of this Graph's nodes and links
				 *
				 * @return A string holding the nodes JSON of the graph
				 */
				virtual const string getDataStructureRepresentation() const override {
					using bridges::JSONUtil::JSONencode;

					// map the nodes to a sequence of ids, 0...N-1
					// then get the JSON string for nodes placeholder
					// nullptr prevents insertion of other nullptrs

					unordered_map<K, int> node_map;
					int i = 0;
					string nodes_JSON = "", links_JSON = "";

					for (const auto& v : this->vertices) {
						if (node_map.emplace(v.first, i).second) {
							i++;
							nodes_JSON += v.second->getElementRepresentation() + COMMA;
						}
					}

					//Remove trailing comma and nullptr entry

					if (nodes_JSON.size()) {
						nodes_JSON = nodes_JSON.erase(nodes_JSON.size() - 1);
					}

					// iterate through the N squared entries vertices and form the links JSON

					for (const auto& src : vertices) {
						for (const auto& dest : vertices) {
							if (matrix.at(src.first).at(dest.first)) {	// link exists
								Element<E1>* src_v = vertices.at(src.first);
								Element<E1>* dest_v = vertices.at(dest.first);
								links_JSON +=  src_v->getLinkRepresentation(
										*(src_v->getLinkVisualizer(dest_v)),
										JSONencode(node_map.at(src.first)),
										JSONencode(node_map.at(dest.first))) + COMMA;
							}
						}
					}

					//Remove trailing comma
					if (links_JSON.size()) {
						links_JSON = links_JSON.erase(links_JSON.size() - 1);
					}

					string graph_amatrix_json =
						QUOTE + "nodes"  + QUOTE + COLON +
						OPEN_BOX + nodes_JSON + CLOSE_BOX + COMMA +
						QUOTE + "links" + QUOTE + COLON + OPEN_BOX +
						links_JSON + CLOSE_BOX +
						CLOSE_CURLY;

					return graph_amatrix_json;
				}
		}; //end of GraphAdjList class
	}
}//end of bridges namespace
#endif
