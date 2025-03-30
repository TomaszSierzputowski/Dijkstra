#include "Buckets.hpp"

Buckets::Buckets(int _no_buckets, int _no_elements, long* _keys) {
    no_buckets = _no_buckets;
    no_elements = _no_elements;
    keys = _keys;
    buckets = new bucket[no_buckets];
    fst_pnt = new elem*[no_elements];
}

Buckets::~Buckets() {
    delete[] buckets;
    delete[] fst_pnt;
}

void Buckets::insert(vertex v, long key) {
    keys[v] = key;
    bucket* b = &buckets[key % no_buckets];
    if (b->size > 0) {
        struct elem* new_elem = new elem{v, b->first->prev, b->first};
        fst_pnt[v] = new_elem;
        b->first->prev->next = new_elem;
        b->first->prev = new_elem;
    } else {
        struct elem* new_elem = new elem;
        fst_pnt[v] = new_elem;
        *new_elem = {v, new_elem, new_elem};
        b->first = new_elem;
    }
    b->size++;
    size_of_all_buckets++;
}

vertex Buckets::extract_min() {
    while (buckets[current_bucket].size == 0) {
        current_bucket = (current_bucket + 1) % no_buckets;
    }
    bucket* b = &buckets[current_bucket];
    struct elem* tmp = b->first;
    vertex ret = tmp->v;
    b->size--;
    if (b->size > 0) {
        tmp->next->prev = tmp->prev;
        tmp->prev->next = tmp->next;
        b->first = tmp->next;
        delete tmp;
    } else {
        b->first = nullptr;
        delete tmp;
    }
    size_of_all_buckets--;
    return ret;
}

void Buckets::decrese_key(vertex v, long key) {
    bucket* b1 = &buckets[keys[v] % no_buckets];
    struct elem* tmp = fst_pnt[v];
    b1->size--;
    if (b1->size > 0) {
        tmp->next->prev = tmp->prev;
        tmp->prev->next = tmp->next;
        b1->first = tmp->next;
    } else {
        b1->first = nullptr;
    }
    keys[v] = key;
    bucket* b2 = &buckets[key % no_buckets];
    if (b2->size > 0) {
        tmp->prev = b2->first->prev;
        tmp->next = b2->first;
        b2->first->prev->next = tmp;
        b2->first->prev = tmp;
    } else {
        b2->first = tmp;
        tmp->next = tmp;
        tmp->prev = tmp;
    }
    b2->size++;
}