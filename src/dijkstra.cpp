#include "dijkstra.hpp"

#ifdef DIJKSTRA
void dijkstra(Graph& graph, vertex s, long* d, vertex* pred) {
    int size = graph.get_size();
    int edges = graph.get_edges();
    int k = (edges - 1) / size + 1;
    if (2 > k) {
        k = 2;
    }
    PriorityQueue pq(size, k, d);
    for (vertex v = 0; v < size; v++) {
        d[v] = infl;
    }
    pred[s] = -1;
    pq.insert(s, 0);
    vertex v, w;
    struct node* neighbour;
    long value;
    while (!pq.is_empty()) {
        v = pq.extract_min();
        neighbour = graph.get_neighbours(v).first;
        while (neighbour != nullptr) {
            w = neighbour->v;
            value = d[v] + neighbour->c;
            if (d[w] > value) {
                pred[w] = v;
                if (d[w] == infl) {
                    pq.insert(w, value);
                } else {
                    pq.decrese_key(w, value);
                }
            }
            neighbour = neighbour->next;
        }
    }
}

const char* alg_name(){
    return "dijkstra";
}
#endif

#ifdef DIAL
void dijkstra(Graph& graph, vertex s, long* d, vertex* pred) {
    int size = graph.get_size();
    int C = graph.get_Cmax();
    for (vertex v = 0; v < size; v++) {
        d[v] = infl;
    }
    Buckets bs(C + 1, size, d);
    pred[s] = -1;
    bs.insert(s, 0);
    vertex v, w;
    struct node* neighbour;
    long value;
    while (!bs.is_empty()) {
        v = bs.extract_min();
        neighbour = graph.get_neighbours(v).first;
        while (neighbour != nullptr) {
            w = neighbour->v;
            value = d[v] + neighbour->c;
            if (d[w] > value) {
                pred[w] = v;
                if (d[w] == infl) {
                    bs.insert(w, value);
                } else {
                    bs.decrese_key(w, value);
                }
            }
            neighbour = neighbour->next;
        }
    }
}

const char* alg_name(){
    return "dial";
}
#endif

#ifdef RADIXHEAP
void dijkstra(Graph& graph, vertex s, long* d, vertex* pred) {
    int size = graph.get_size();
    int C = graph.get_Cmax();
    for (vertex v = 0; v < size; v++) {
        d[v] = infl;
    }
    int K = 2;
    while (C > 0) {
        K++;
        C /= 2;
    }
    RadixHeap rh(K, size, d);
    pred[s] = -1;
    rh.insert(s, 0);
    vertex v, w;
    struct node* neighbour;
    long value;
    while (!rh.is_empty()) {
        v = rh.extract_min();
        neighbour = graph.get_neighbours(v).first;
        while (neighbour != nullptr) {
            w = neighbour->v;
            value = d[v] + neighbour->c;
            if (d[w] > value) {
                pred[w] = v;
                if (d[w] == infl) {
                    rh.insert(w, value);
                } else {
                    rh.decrese_key(w, value);
                }
            }
            neighbour = neighbour->next;
        }
    }
}

const char* alg_name(){
    return "radixheap";
}
#endif