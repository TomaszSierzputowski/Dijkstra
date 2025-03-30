#include <string>
#include "Graph.hpp"

void Graph::import(std::istream& file) {
    std::string line;
    int temp_edges = 0;
    while (getline(file, line)) {
        int len = line.length();
        if (len == 0) {
            warning("Data file shouldn't contain empty lines (ignoring that line)");
        } else if (line[0] == 'a') {
            if (size == 0) {
                error("Data file cannot contain edge definition before problem definition");
            }
            if (temp_edges == edges) {
                warning("Data file shouldn't contain more edge definitions than described in problem line (ignoring redundant edge)");
            }
            if (line[1] != ' ') {
                error("Edge in data file has to be defined as 'a <from_vertex> <to_vertex> <cost>'");
            }
            int from = 0, to = 0, cost = 0;
            int i = 2;
            while (i < len && line[i] >= '0' && line[i] <= '9') {
                from *= 10;
                from += line[i] - '0';
                i++;
            }
            if (i == len || line[i] != ' ' || from == 0 || from > size) {
                error("Edge in data file has to be defined as 'a <from_vertex> <to_vertex> <cost>'");
            }
            i++;
            while (i < len && line[i] >= '0' && line[i] <= '9') {
                to *= 10;
                to += line[i] - '0';
                i++;
            }
            if (i == len || line[i] != ' ' || to == 0 || to > size) {
                error("Edge in data file has to be defined as 'a <from_vertex> <to_vertex> <cost>'");
            }
            i++;
            while (i < len && line[i] >= '0' && line[i] <= '9') {
                cost *= 10;
                cost += line[i] - '0';
                i++;
            }
            if (i < len || (cost == 0 && line[i-1] != '0')) {
                error("Edge in data file has to be defined as 'a <from_vertex> <to_vertex> <cost>'");
            }
            from--;
            to--;
            struct node* new_edge = new node{to, cost, nullptr};
            *(Neighbours[from].add) = new_edge;
            Neighbours[from].add = &(new_edge->next);
            if (cost > C_max) {
                C_max = cost;
            } else if (cost < C_min) {
                C_min = cost;
            }
            temp_edges++;
        } else if (line[0] == 'p') {
            if (size > 0) {
                warning("Problem in data file should be defined only once (ignoring further definitions)");
                continue;
            }
            if (line.substr(1, 4) != " sp ") {
                error("Problem in data file has to be defined as 'p sp <no_vertices> <no_edges>'");
            }
            int i = 5;
            while (i < len && line[i] >= '0' && line[i] <= '9') {
                size *= 10;
                size += line[i] - '0';
                i++;
            }
            if (i == len || line[i] != ' ' || size == 0) {
                error("Problem in data file has to be defined as 'p sp <no_vertices> <no_edges>'");
            }
            i++;
            while (i < len && line[i] >= '0' && line[i] <= '9') {
                edges *= 10;
                edges += line[i] - '0';
                i++;
            }
            if (i < len || edges == 0) {
                error("Problem in data file has to be defined as 'p sp <no_vertices> <no_edges>'");
            }
            Neighbours = new List[size];
        } else if (line[0] != 'c') {
            warning("Data file's lines should always start with p, a or c (ignoring other lines)");
        }
    }
    if (size == 0) {
        error("Data file has to define a problem like 'p sp <no_vertices> <no_edges>'");
    }
    if (temp_edges < edges) {
        error("Data file has to define as many edges as declared in problem line");
    }
}

Graph::~Graph() {
    struct node *node, *next_node;
    for (vertex v = 0; v < size; v++) {
        node = Neighbours[v].first;
        while (node != nullptr) {
            next_node = node->next;
            delete node;
            node = next_node;
        }
    }
    delete[] Neighbours;
}

