#include "Graph.hpp"

#ifdef DIJKSTRA
#include "PriorityQueue.hpp"
#endif

#ifdef DIAL
#include "Buckets.hpp"
#endif

#ifdef RADIXHEAP
#include "RadixHeap.hpp"
#endif

void dijkstra(Graph& graph, vertex s, long* d, vertex* pred);
const char* alg_name();