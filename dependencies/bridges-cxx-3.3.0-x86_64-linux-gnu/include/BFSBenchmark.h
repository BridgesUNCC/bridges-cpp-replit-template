#ifndef BFS_BENCHMARK_H
#define BFS_BENCHMARK_H

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
		 * @brief Benchmarks Breadth First Search algorithms.
		 *
		 * Benchmarks BFS algorithms and add time series to a LineChart.
		 *
		 * One can also set a maximum time spent on a particular run
		 * using setTimeCap().
		 *
		 * The BFS algorithms must have for prototype:
		 *
		 * void (*bfsalgo)(const GraphAdjList<std::string>& gr,
		 *                 std::string root,
		 *                 std::unordered_map<std::string, int>& level,
		 *                 std::unordered_map<std::string, std::string>& parent);
		 *
		 * and can be passed to the run function for being
		 * benchmarked. A typical use would look something like
		 *
		 * \code{.cpp}
		 * LineChart lc;
		 * BFSBenchmark sb (lc);
		 * sb.run("mybfsalgorithm", bfsalgo);
		 * \endcode
		 *
		 * @author Erik Saule
		 * @date 07/21/2019
		 **/
		class BFSBenchmark : public GraphBenchmark {
			private:
				LineChart& plot;

			public:
				BFSBenchmark(LineChart& p)
					: plot (p) {
					p.setXLabel("Number of Edges");
					p.setYLabel("Runtime (in s)");

				}

				/**
				 * @brief benchmark one implementation
				 *
				 * @param algoName screen name of the algorithm to be used in the visualization
				 * @param bfsalgo pointer to the sorting function to benchmark
				 **/
				void run(std::string algoName,
					void (*bfsalgo)(const GraphAdjList<std::string>& gr,
						std::string root,
						std::unordered_map<std::string, int>& level,
						std::unordered_map<std::string, std::string>& parent)) {
					std::vector<double> time;
					std::vector<double> vtxCounts;
					std::vector<double> edgeCounts;

					for (int years = 0; years < 120; years = 1.2 * years + 1) {
						int year = 2019 - years;
						std::cerr << "*" << std::flush;
						GraphAdjList<std::string> graph;
						long vertexCount;
						long edgeCount;
						std::tie(vertexCount, edgeCount) = generateWikidataMovieActor(year, 2019, graph);

						std::string root = highestDegreeVertex(graph);

						std::unordered_map<std::string, int> level;
						std::unordered_map<std::string, std::string> parent;

						std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

						bfsalgo(graph, root, level, parent);

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
