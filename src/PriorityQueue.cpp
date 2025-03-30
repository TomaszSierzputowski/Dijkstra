#include "PriorityQueue.hpp"
#define PARENT(x) ((x-1)/d)
#define KEY(x) keys[queue[x]]

PriorityQueue::PriorityQueue(int max_size, int _d, long* _keys) {
    queue = new vertex[max_size];
    d = _d;
    keys = _keys;
    v_idx = new int[max_size];
    size = 0;
}

PriorityQueue::~PriorityQueue() {
    delete[] queue;
    delete[] v_idx;
}

void PriorityQueue::insert(vertex v, long key) {
    keys[v] = key;
    int i = size;
    int p = PARENT(i);
    while (i > 0 && KEY(p) > key) {
        queue[i] = queue[p];
        v_idx[queue[i]] = i;
        i = p;
        p = PARENT(i);
    }
    queue[i] = v;
    v_idx[v] = i;
    size++;
}

vertex PriorityQueue::extract_min() {
    vertex ret = queue[0];
    size--;
    vertex v = queue[size];
    long key = keys[v];
    int i = 0;
    int c = i*d + 1;
    int last = c + d;
    long min;
    int cmin = i;
    while (last < size) {
        min = key;
        while (c < last) {
            if (KEY(c) < min) {
                min = KEY(c);
                cmin = c;
            }
            c++;
        }
        if (cmin == i) {
            break;
        }
        queue[i] = queue[cmin];
        v_idx[queue[i]] = i;
        i = cmin;
        c = i*d + 1;
        last = c + d;
    }
    if (last >= size) {
        min = key;
        while (c < size) {
            if (KEY(c) < min) {
                min = KEY(c);
                cmin = c;
            }
            c++;
        }
        if (cmin != i) {
            queue[i] = queue[cmin];
            v_idx[queue[i]] = i;
            i = cmin;
        }
    }
    queue[i] = v;
    v_idx[v] = i;
    return ret;
}

void PriorityQueue::decrese_key(vertex v, long key) {
    keys[v] = key;
    int i = v_idx[v];
    int p = PARENT(i);
    while (i > 0 && KEY(p) > key) {
        queue[i] = queue[p];
        v_idx[queue[i]] = i;
        i = p;
        p = PARENT(i);
    }
    queue[i] = v;
    v_idx[v] = i;
}