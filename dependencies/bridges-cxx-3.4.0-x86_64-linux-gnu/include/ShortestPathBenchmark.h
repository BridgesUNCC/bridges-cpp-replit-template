#ifndef SHORTESTPATH_BENCHMARK_H
#define SHORTESTPATH_BENCHMARK_H

#include <LineChart.h>
#include <limits>
#include <vector>
#include <chrono>
#include <stdlib.h>
#include <iostream>
#include <GraphBenchmark.h>

namespace bridges {
	namespace benchmark {
		using namespace bridges::datastructure;
		/**
		 * @brief Benchmarks Shortest Path algorithms.
		 *
		 * Benchmarks Shortest Path algorithms and add time series to a LineChart.
		 *
		 * One can also set a maximum time spent on a particular run
		 * using setTimeCap().
		 *
		 * The Shortest Path algorithms must have for prototype:
		 *
		 * void (*spalgo)(const GraphAdjList<int, OSMVertex, double>& gr,
		 *	          int source,
		 *                std::unordered_map<int, double>& distance,
		 *                std::unordered_map<int, int>& parent);
		 *
		 * and can be passed to the run function for being
		 * benchmarked. A typical use would look something like
		 *
		 * \code{.cpp}
		 * LineChart lc;
		 * ShortestPathBenchmark sb (lc);
		 * sb.run("mybfsalgorithm", spalgo);
		 * \endcode
		 *
		 * @author Erik Saule
		 * @date 07/21/2019
		 **/
		class ShortestPathBenchmark : public GraphBenchmark {
			private:
				LineChart& plot;
				DataSource ds;

				int getCenter(const OSMData& osm_data, const GraphAdjList<int, OSMVertex, double>& graph,
					double latc, double lonc) {
					//
					auto distfunction = [ = ](const OSMVertex & v) -> double {
						return (v.getLatitude() - latc) * (v.getLatitude() - latc) + (v.getLongitude() - lonc) * (v.getLongitude() - lonc);
					};

					int minindex = 0;
					double dist = distfunction(graph.getVertex(minindex)->getValue());

					for (int i = 1; i < graph.getVertices()->size(); ++i) {
						double locdist = distfunction(graph.getVertex(i)->getValue());
						if (locdist < dist) {
							minindex = i;
							dist = locdist;
						}
					}

					return minindex;
				}

			public:
				ShortestPathBenchmark(LineChart& p)
					: plot (p) {
					p.setXLabel("Number of Edges");
					p.setYLabel("Runtime (in s)");

				}

				/**
				 * @brief benchmark one implementation
				 *
				 * @param algoName screen name of the algorithm to be used in the visualization
				 * @param spalgo pointer to the sorting function to benchmark
				 **/
				void run(std::string algoName,
					void (*spalgo)(const GraphAdjList<int, OSMVertex, double>& gr,
						int source,
						std::unordered_map<int, double>& distance,
						std::unordered_map<int, int>& parent)) {
					std::vector<double> time;
					std::vector<double> vtxCounts;
					std::vector<double> edgeCounts;

					// double reflat = 39.9713; //Columbus, OH
					// double reflong = -82.99;

					double reflat = 40.74; //New York City, NC
					double reflong = -73.98;


					for (double radius = 0.02; radius < 0.15; radius += 0.02) {
						std::cerr << "*" << std::flush;
						//std::tie(vertexCount, edgeCount)= generateWikidataMovieActor(year, 2019, graph);

						OSMData osm_data = ds.getOSMData(reflat - radius, reflong - radius,
								reflat + radius, reflong + radius);
						GraphAdjList<int, OSMVertex, double> graph;
						osm_data.getGraph (&graph);

						long vertexCount = countVertices(graph);
						long edgeCount = countEdges(graph);


						int root = getCenter(osm_data, graph, reflat, reflong);

						std::unordered_map<int, double> level;
						std::unordered_map<int, int> parent;

						std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

						spalgo(graph, root, level, parent);

						std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

						std::chrono::duration<double> elapsed_seconds = end - start;


						time.push_back ((double)elapsed_seconds.count() );
						vtxCounts.push_back ( (double)vertexCount );
						edgeCounts.push_back ( (double)edgeCount );

						if (elapsed_seconds.count() > time_cap) {
							break;
						}
					}
					plot.setXData(algoName, edgeCounts);
					plot.setYData(algoName, time);
					std::cerr << "\n" << std::flush;
				}
		};
	}
}

#endif
