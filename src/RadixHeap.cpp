#include "RadixHeap.hpp"

RadixHeap::RadixHeap(int _no_buckets, int _no_elements, long* _keys) {
    no_buckets = _no_buckets;
    no_elements = _no_elements;
    keys = _keys;

    buckets = new bucket[no_buckets];
    fst_pnt = new elem*[no_elements];
    long a = 1;
    for (int i = 0; i < no_buckets - 1; i++) {
        buckets[i].end = a;
        a *= 2;
    }
    buckets[no_buckets - 1].end = infl;
}

RadixHeap::~RadixHeap() {
    delete[] buckets;
    delete[] fst_pnt;
}

void RadixHeap::add_to_bucket(int i, struct elem* element) {
    bucket* b = &buckets[i];
    if (b->size > 0) {
        element->prev = b->first->prev;
        element->next = b->first;
        b->first->prev->next = element;
        b->first->prev = element;
    } else {
        element->prev = element;
        element->next = element;
        b->first = element;
    }
    element->bNum = i;
    b->size++;
}

void RadixHeap::insert(vertex v, long key) {
    keys[v] = key;
    int i = no_buckets - 2;
    while (i >= 0 && buckets[i].end > key) {
        i--;
    }
    struct elem* new_elem = new elem;
    new_elem->v = v;
    fst_pnt[v] = new_elem;
    add_to_bucket(i + 1, new_elem);
    size_of_all_buckets++;
}

vertex RadixHeap::extract_min() {
    vertex ret;
    int first_not_empty = 0;
    while (buckets[first_not_empty].size == 0) {
        first_not_empty++;
    }
    bucket* b = &buckets[first_not_empty];
    if (first_not_empty > 1) {
        if (b->size == 1) {
            ret = b->first->v;
            delete b->first;
            b->first = nullptr;
            b->size = 0;
        } else {
            struct elem* tmp = b->first;
            struct elem* min = tmp;
            long min_key = keys[min->v];
            for (int k = 1; k < b->size; k++) {
                tmp = tmp->next;
                if (keys[tmp->v] < min_key) {
                    min = tmp;
                    min_key = keys[min->v];
                }
            }
            ret = min->v;

            int i = 0;
            long a = 1;
            while (i < no_buckets - 1 && min_key + a < b->end) {
                buckets[i].end = min_key + a;
                a *= 2;
                i++;
            }
            for (int k = i; k < first_not_empty; k++) {
                buckets[k].end = b->end;
            }

            tmp = min->next;
            struct elem* next;
            for (int k = 1; k < b->size; k++) {
                int j = i;
                while (j >= 0 && buckets[j].end > keys[tmp->v]) {
                    j--;
                }
                next = tmp->next;
                add_to_bucket(j + 1, tmp);
                tmp = next;
            }
            b->first = nullptr;
            delete min;
            b->size = 0;
        }
    } else {
        struct elem* tmp = b->first;
        ret = tmp->v;
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
    }
    size_of_all_buckets--;
    return ret;
}

void RadixHeap::decrese_key(vertex v, long key) {
    keys[v] = key;
    struct elem* tmp = fst_pnt[v];
    int j = tmp->bNum;
    int i = j - 1;
    while (i >= 0 && buckets[i].end > key) {
        i--;
    }
    i++;
    if (i == j) {
        return;
    }
    bucket* b = &buckets[j];
    b->size--;
    if (b->size > 0) {
        tmp->next->prev = tmp->prev;
        tmp->prev->next = tmp->next;
        b->first = tmp->next;
    } else {
        b->first = nullptr;
    }
    add_to_bucket(i, tmp);
}

#include <iostream>

void RadixHeap::test_print() {
    for (int i = 0; i < no_buckets; i++) {
        std::cout << i << " " << buckets[i].end << ":";
        struct elem* tmp = buckets[i].first;
        for (int k = 0; k < buckets[i].size; k++) {
            std::cout << " (" << tmp->v << ":" << keys[tmp->v] << ")";
            tmp = tmp->next;
        }
        std::cout << std::endl;
    }
    std::cin.ignore();
}