#include "miscellaneous.hpp"

class Buckets {
private:
    struct elem{
        vertex v;
        elem* prev;
        elem* next;
    };
    typedef struct {
        struct elem* first = nullptr;
        int size = 0;
    } bucket;
    int no_buckets;
    int no_elements;
    int current_bucket = 0;
    int size_of_all_buckets = 0;
    bucket* buckets;
    struct elem** fst_pnt;
    long* keys;
public:
    Buckets(int _no_buckets, int _no_elements, long* _keys);
    ~Buckets();
    void insert(vertex v, long key);
    vertex extract_min();
    void decrese_key(vertex v, long key);
    bool is_empty() {return size_of_all_buckets == 0;}
};