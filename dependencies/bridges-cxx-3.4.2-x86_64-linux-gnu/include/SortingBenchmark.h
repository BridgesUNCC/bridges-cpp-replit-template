#ifndef SORTINGBENCHMARK_H
#define SORTINGBENCHMARK_H

#include <LineChart.h>
#include <limits>
#include <vector>
#include <chrono>
#include <stdlib.h>

namespace bridges {
	namespace benchmark {
		using namespace bridges::datastructure;

		/**
		 * @brief Benchmarks sorting algorithm
		 *
		 * Benchmarks sorting algorithms and add time series to a LineChart.
		 *
		 * The benchmark goes from an initial size controlled by
		 * setBaseSize() to a largest size controlled by setMaxSize(). One
		 * can also set a maximum time spent on a particular run using
		 * setTimeCap().
		 *
		 * The benchmark goes from a array size of n to the next one of
		 * geoBase * n + increment, where the base is controlled by
		 * setGeometric() and increment is controlled by
		 * setIncrement(). For simpler use one can set a purley linear
		 * sampling with linearRange() or a purely geometric one with
		 * geometricRange().
		 *
		 * The sorting algorithms must have for prototype:
		 *  void (*sort)(int* array, int arraysize);
		 * and can be passed to the run function for being benchmarked. A typical use would look something like
		 *
		 * \code{.cpp}
		 * void mysort(int* array, int arraysize);
		 * LineChart lc;
		 * SortingBenchmark sb (lc);
		 * sb.linearRange (100, 1000, 5);
		 * sb.run("mysortingalgorithm", mysort);
		 * \endcode
		 *
		 * @author Erik Saule
		 * @date 07/20/2019
		 *
		 **/
		class SortingBenchmark {
			private:
				LineChart& plot;

				int maxSize;
				int baseSize;
				int increment;
				double geoBase;
				double time_cap;
		  std::string generatorType;
		  
				void generateRandom(int* arr, int n) {
					for (int i = 0; i < n; i++) {
						arr[i] = ((double)rand()) / RAND_MAX * (2 * n);
					}
				}

		  void generateInOrder(int* arr, int n) {
		    for (int i = 0; i < n; i++) {
		      arr[i] = i;
		    }
		  }
		  void generateReverseOrder(int* arr, int n) {
		    for (int i = 0; i < n; i++) {
		      arr[i] = n-i;
		    }
		  }
		  void generateFewValues(int* arr, int n) {
		    for (int i = 0; i < n; i++) {
		      arr[i] = ((double)rand()) / RAND_MAX * (4);
		    }
		  }
		  void generateAlmostSorted(int* arr, int n) {
		    if (n < 20) {
		      generateRandom(arr, n);
		    } else {
		      int i;
		      for (i = 0; i < n-20; i++) {
			arr[i] = i;		    
		      }
		      for (; i < n; i++) {
			arr[i] = ((double)rand()) / RAND_MAX * (2 * n);
		      }		      
		    }		    
		  }
		  
		    
		  		void generate(int* arr, int n) {
				  if (generatorType == "random") {
				    generateRandom(arr, n);
				  } else if (generatorType == "inorder") {
				    generateInOrder(arr, n);
				  } else if (generatorType == "reverseorder") {
				    generateReverseOrder(arr, n);
				  } else if (generatorType == "fewdifferentvalues") {
				    generateFewValues(arr, n);
				  } else if (generatorType == "almostsorted") {
				    generateAlmostSorted(arr, n);
				  } else {
				    throw std::string("unknown generator");
				  }
				  
				}

				bool check (int* arr, int n) {
					bool ok = true;
					for (int i = 1; i < n; ++i) {
						if (arr[i] < arr[i - 1]) {
							ok = false;
						}
					}
					return ok;
				}

			public:
				SortingBenchmark(LineChart& p)
					: plot (p) {
					p.setXLabel("Size of Array");
					p.setYLabel("Runtime (in s)");

					//r = new Random();

					maxSize = 1;
					baseSize = 1;
					increment = 1;
					geoBase = 1.;
					time_cap = std::numeric_limits<double>::max();
					setGenerator("random");
				}

		  /**
		   *
		   *  @param generatorName possible values are "random", "inorder", "reverseorder", "fewdifferentvalues", "almostsorted"

		   **/
		  void setGenerator(const std::string& generatorName) {
		    generatorType = generatorName;
		  }
		  
		  std::string getGenerator() const {
		    return generatorType;
		  }		  
				/**
				 * @brief Puts a cap on the largest array to be used
				 *
				 * @param size Maximum size considered
				 **/
				void setMaxSize(int size) {
					maxSize = size;
				}

				/**
				 * @brief Smallest array to be used
				 *
				 * @param size of the smallest array to use/
				 **/
				void setBaseSize(int size) {
					baseSize = size;
				}


				/**
				 * @brief Sets the increment for the benchmark size
				 *
				 * @param inc new value of the increment
				 **/
				void setIncrement(int inc) {
					increment = inc;
				}

				/**
				 * @brief Sets a geometric progression for the benchmark size
				 *
				 * @param base new base of the geometric progression
				 **/
				void setGeometric(double base) {
					geoBase = base;
				}

				/**
				 * @brief The benchmark will sample a range with a fixed number of
				 * points.
				 *
				 * The benchmark will sample about nbPoint equally distributed in
				 * the range [baseSize; maxSize]
				 *
				 * @param baseSize lower bound of the range sampled
				 * @param maxSize upper bound of the range sampled
				 * @param nbPoint number of sample
				 */
				void linearRange(int baseSize, int maxSize, int nbPoint) {
					setBaseSize (baseSize);
					setMaxSize (maxSize);
					setIncrement ((maxSize - baseSize) / nbPoint);
					setGeometric (1.0);
				}

				/**
				 * @brief The benchmark will sample a range using in geometrically
				 * increasing sequence
				 *
				 * The benchmark will sample the range [baseSize; maxSize] using a
				 * geometric distribution in base base. That is to say, it will
				 * sample baseSize, base*baseSize, base*base*baseSize, ...
				 *
				 * @param baseSize lower bound of the range sampled
				 * @param maxSize upper bound of the range sampled
				 * @param base base of the geometric increase
				 */
				void geometricRange(int baseSize, int maxSize, double base) {
					setBaseSize (baseSize);
					setMaxSize (maxSize);
					setIncrement (0);
					setGeometric (base);
					if (base <= 1.0) {
						std::cerr << "base should be > 1.0\n";
					}
				}

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
				 * @brief benchmark one implementation
				 *
				 * @param algoName screen name of the algorithm to be used in the visualization
				 * @param runnable pointer to the sorting function to benchmark
				 **/
				void run(std::string algoName, void (*runnable)(int*, int)) {
					std::vector<double> time;
					std::vector<double> xData;

					//	System.out.println(geoBase);
					//	System.out.println(increment);

					for (int n = baseSize; n <= maxSize;
						n = std::max((int)(geoBase * n) + increment, n + 1)) {

						//System.out.println(n);
						std::vector<int> arr(n);

						generate(&arr[0], n);

						std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

						runnable(&arr[0], n);

						std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

						std::chrono::duration<double> elapsed_seconds = end - start;

						if (! check(&arr[0], n)) {
							std::cerr << "Sorting algorithm " << algoName << " is incorrect\n";
						}

						time.push_back ((double)elapsed_seconds.count() );
						xData.push_back ( (double)n );

						if (elapsed_seconds.count() > time_cap) {
							break;
						}
					}
					plot.setXData(algoName, xData);
					plot.setYData(algoName, time);
				}

		};
	}
}

#endif
