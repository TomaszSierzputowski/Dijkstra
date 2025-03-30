#include "miscellaneous.hpp"

class PriorityQueue {
private:
    vertex* queue;
    long* keys;
    int* v_idx;
    int size;
    int d;
public:
    PriorityQueue(int max_size, int _d, long* _keys);
    ~PriorityQueue();
    void insert(vertex v, long key);
    vertex extract_min();
    void decrese_key(vertex v, long key);
    bool is_empty() {return size == 0;}
};