#ifndef GRAPH_BENCHMARK_H
#define GRAPH_BENCHMARK_H

#include <GraphAdjList.h>

namespace bridges {
	namespace benchmark {
		using namespace bridges::datastructure;

		/**
		 * @brief Base class for a variety of graph based benchmark.
		 *
		 * This class is not meant to be used directly by students.
		 **/
		class GraphBenchmark {
			protected:
				double time_cap;
				GraphBenchmark()
					: time_cap (std::numeric_limits<double>::max())
				{}

				///@returns a triplet: the graph, the number of vertices, and the number of edges
				std::tuple<long, long> generateWikidataMovieActor (int yearmin, int yearmax, GraphAdjList<std::string>& moviegraph) {
					DataSource ds;
					std::vector<MovieActorWikidata> v = ds.getWikidataActorMovie(yearmin, yearmax);
					long edgeCount = 0;
					long vertexCount = 0;

					//GraphAdjList<std::string, std::string> moviegraph;
					for (auto ma : v) {

						//add the movie vertex
						auto movievertex = moviegraph.getVertex(ma.getMovieURI());
						if (movievertex == nullptr) {
							moviegraph.addVertex(ma.getMovieURI(), ma.getMovieName());
							movievertex = moviegraph.getVertex(ma.getMovieURI());
							vertexCount++;
						}

						//add the actor vertex
						auto actorvertex = moviegraph.getVertex(ma.getActorURI());
						if (actorvertex == nullptr) {
							moviegraph.addVertex(ma.getActorURI(), ma.getActorName());
							actorvertex = moviegraph.getVertex(ma.getActorURI());
							vertexCount++;
						}

						//add bidirectional edge
						moviegraph.addEdge(ma.getMovieURI(), ma.getActorURI());
						moviegraph.addEdge(ma.getActorURI(), ma.getMovieURI());
						edgeCount += 2;
					}

					return std::make_tuple(vertexCount, edgeCount);
				}

				std::string highestDegreeVertex(GraphAdjList<std::string>& gr) {
					long maxdegree = -1;
					std::string ret;

					for (auto k : gr.keySet()) {
						long degree = 0;
						for (auto e : gr.outgoingEdgeSetOf(k))
							degree++;
						if (degree > maxdegree) {
							maxdegree = degree;
							ret = k;
						}
					}

					return ret;
				}

				template<typename GraphType>
				long countVertices (const GraphType& gr) {
					return gr.getVertices()->size();
				}

				template<typename GraphType>
				long countEdges(const GraphType& gr) {
					long edges = 0;
					for (auto k : gr.keySet())
						for (auto e : gr.outgoingEdgeSetOf(k))
							edges++;

					return edges;
				}


			public:
				/**
				 * @brief sets an upper bound to the time of a run.
				 *
				 * The benchmark will end after a run if it takes more than the
				 * given amount of time. So it is possible a particular run takes
				 * more than the alloted time, but that will be the last run.
				 *
				 * @param cap_in_s time limit in seconds
				 **/
				void setTimeCap(double cap_in_s) {
					time_cap = cap_in_s;
				}

				/**
				 * @brief Return time limit of a run.
				 *
				 * The benchmark will end after a run if it takes more than the
				 * given amount of time. So it is possible a particular run takes
				 * more than the alloted time, but that will be the last run.
				 *
				 * @return the time upper bound (in seconds) of a particular run.
				 */
				double getTimeCap() const {
					return time_cap;
				}

		};
	}
}

#endif
