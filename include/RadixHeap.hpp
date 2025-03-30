#include "miscellaneous.hpp"

class RadixHeap {
private:
    struct elem{
        vertex v;
        elem* prev;
        elem* next;
        int bNum;
    };
    typedef struct {
        struct elem* first = nullptr;
        int size = 0;
        long end;
    } bucket;
    int no_buckets;
    int no_elements;
    int size_of_all_buckets = 0;
    bucket* buckets;
    struct elem** fst_pnt;
    long* keys;
    void add_to_bucket(int bucket, struct elem* element);

    void test_print();
public:
    RadixHeap(int _no_buckets, int _no_elements, long* _keys);
    ~RadixHeap();
    void insert(vertex v, long key);
    vertex extract_min();
    void decrese_key(vertex v, long key);
    bool is_empty() {return size_of_all_buckets == 0;}
};