#pragma once
#include <istream>
#include "miscellaneous.hpp"

struct node {
    vertex v;
    int c;
    node* next;
};

typedef struct {
    struct node* first = nullptr;
    struct node** add = &first;
} List;

class Graph
{
private:
    int size = 0;
    int edges = 0;
    int C_max = 0;
    int C_min = inf;
    List* Neighbours;
public:
    Graph() {};
    void import(std::istream& file);
    Graph(std::istream& file) {import(file);}
    ~Graph();
    int get_size() {return size;}
    int get_edges() {return edges;}
    int get_Cmax() {return C_max;}
    int get_Cmin() {return C_min;}
    List get_neighbours(vertex v) {return Neighbours[v];}
};