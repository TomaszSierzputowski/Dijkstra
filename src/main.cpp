#include "dijkstra.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#define NO_PROBLEM -1
#define SS 0
#define P2P 1

using namespace std;
using namespace std::chrono;

void ss(istream& d, istream& in, ostream& out, string file_names);
void p2p(istream& d, istream& in, ostream& out, string file_names);

int main(int argc, char* argv[]) {
    fstream* d = nullptr;
    fstream* in = nullptr;
    fstream* out = nullptr;
    fstream* f = nullptr;
    int in_problem = NO_PROBLEM;
    int out_problem = NO_PROBLEM;
    string d_file;
    string in_file;
    for (int i = 1; i < argc - 1; i++) {
        string flag(argv[i]);
        if (flag == "-d") {
            if (d != nullptr) {
                warning("Data file should be defined only once (ignoring further definitions)");
                continue;
            }
            i++;
            f = new fstream(argv[i], fstream::in);
            if (!f->is_open()) {
                error("Specified data file doesn't exist");
            }
            d = f;
            d_file = argv[i];
        } else if (flag == "-ss") {
            if (in != nullptr) {
                warning("Problem input file should be defined only once (ignoring further definitions)");
                continue;
            }
            i++;
            f = new fstream(argv[i], fstream::in);
            if (!f->is_open()) {
                error("Specified problem input file doesn't exist");
            }
            in = f;
            in_problem = SS;
            in_file = argv[i];
        } else if (flag == "-p2p") {
            if (in != nullptr) {
                warning("Problem input file should be defined only once (ignoring further definitions)");
                continue;
            }
            i++;
            f = new fstream(argv[i], fstream::in);
            if (!f->is_open()) {
                error("Specified problem input file doesn't exist");
            }
            in = f;
            in_problem = P2P;
            in_file = argv[i];
        } else if (flag == "-oss") {
            if (out != nullptr) {
                warning("Problem output file should be defined only once (ignoring further definitions)");
                continue;
            }
            i++;
            f = new fstream(argv[i], fstream::out);
            if (!f->is_open()) {
                error("Cannot open or create specified problem output file");
            }
            out = f;
            out_problem = SS;
        } else if (flag == "-op2p") {
            if (out != nullptr) {
                warning("Problem output file should be defined only once (ignoring further definitions)");
                continue;
            }
            i++;
            f = new fstream(argv[i], fstream::out);
            if (!f->is_open()) {
                error("Cannot open or create specified problem output file");
            }
            out = f;
            out_problem = P2P;
        } else {
            warning("The only command line arguments allowed are flags -d, -ss, -p2p, -oss, -op2p and their contents (ignoring others)");
        }
    }
    if (d == nullptr) {
        error("You have to specify a data file, use -d");
    }
    if (in == nullptr) {
        error("You have to specify a problem input file, use -ss or -p2p");
    }
    if (out == nullptr) {
        warning("You should specify a problem input file, use -oss or -op2p (now printing on std::cout)");
    } else if (in_problem != out_problem) {
        warning("Problem input and output files specified with opposing flags (-ss and -op2p or -p2p and -oss) (now printing on std::cout)");
    }

    if (in_problem == SS) {
        ss(*d, *in, (out != nullptr ? *out : cout), d_file + " " + in_file);
    } else {
        p2p(*d, *in, (out != nullptr ? *out : cout), d_file + " " + in_file);
    }

    d->close();
    delete d;
    in->close();
    delete in;
    if (out != nullptr) {
        out->close();
        delete out;
    }

    return 0;
}

void ss(istream& d, istream& in, ostream& out, string file_names) {
    Graph graph(d);
    int size = graph.get_size();

    std::string line;
    vertex* starts;
    int no_starts = 0;
    int temp_starts = 0;
    while (getline(in, line)) {
        int len = line.length();
        if (len == 0) {
            warning("Problem input file shouldn't contain empty lines (ignoring that line)");
        } else if (line[0] == 's') {
            if (no_starts == 0) {
                error("Problem input file cannot contain starting vertex definition before problem definition");
            }
            if (temp_starts == no_starts) {
                warning("Problem input file shouldn't contain more starting vertex definitions than described in problem line (ignoring redundant vertex)");
            }
            if (line[1] != ' ') {
                error("Starting vertex in problem input file has to be defined as 's <vertex>'");
            }
            int s = 0;
            int i = 2;
            while (i < len && line[i] >= '0' && line[i] <= '9') {
                s *= 10;
                s += line[i] - '0';
                i++;
            }
            if (i < len || s == 0 || s > size) {
                error("Starting vertex in problem input file has to be defined as 's <vertex>'");
            }
            starts[temp_starts] = s - 1;
            temp_starts++;
        } else if (line[0] == 'p') {
            if (no_starts > 0) {
                warning("Problem in problem input file should be defined only once (ignoring further definitions)");
                continue;
            }
            if (line.substr(1, 11) != " aux sp ss ") {
                error("Problem in problem input file has to be defined as 'p aux sp ss <no_starting_vertices>'");
            }
            int i = 12;
            while (i < len && line[i] >= '0' && line[i] <= '9') {
                no_starts *= 10;
                no_starts += line[i] - '0';
                i++;
            }
            if (i < len || no_starts == 0) {
                error("Problem in problem input file has to be defined as 'p aux sp ss <no_starting_vertices>'");
            }
            starts = new vertex[no_starts];
        } else if (line[0] != 'c') {
            warning("Problem input file's lines should always start with p, s or c (ignoring other lines)");
        }
    }
    if (no_starts == 0) {
        error("Problem input file has to define a problem like 'p aux sp ss <no_starting_vertices>'");
    }
    if (temp_starts < no_starts) {
        error("Problem input file has to define as many starting vertices as declared in problem line");
    }

    long* dists = new long[size];
    vertex* pred = new vertex[size];
    high_resolution_clock::time_point timer_start;
    duration<double, milli> time;
    for (int i = 0; i < no_starts; i++) {
        timer_start = high_resolution_clock::now();
        dijkstra(graph, starts[i], dists, pred);
        time += high_resolution_clock::now() - timer_start;
    }
    time /= no_starts;

    int edges = graph.get_edges();
    int Cmin = graph.get_Cmin();
    int Cmax = graph.get_Cmax();
    out << "p res sp ss " << alg_name() << endl;
    out << "f " << file_names << endl;
    out << "g " << size << ' ' << edges << ' ' << Cmin << ' ' << Cmax << endl;
    out << "c time is in milliseconds" << endl;
    out << "t " << time.count() << endl;
}

void p2p(istream& d, istream& in, ostream& out, string file_names) {
    Graph graph(d);
    int size = graph.get_size();

    std::string line;
    struct pair{vertex s; vertex e;}* pairs;
    int no_pairs = 0;
    int temp_pairs = 0;
    while (getline(in, line)) {
        int len = line.length();
        if (len == 0) {
            warning("Problem input file shouldn't contain empty lines (ignoring that line)");
        } else if (line[0] == 'q') {
            if (pairs == 0) {
                error("Problem input file cannot contain point to point definition before problem definition");
            }
            if (temp_pairs == no_pairs) {
                warning("Problem input file shouldn't contain more point to point definitions than described in problem line (ignoring redundant pairs)");
            }
            if (line[1] != ' ') {
                error("Point to point in problem input file has to be defined as 'q <from_vertex> <to_vertex>'");
            }
            int from = 0, to = 0;
            int i = 2;
            while (i < len && line[i] >= '0' && line[i] <= '9') {
                from *= 10;
                from += line[i] - '0';
                i++;
            }
            if (i == len || line[i] != ' ' || from == 0 || from > size) {
                error("Point to point in problem input file has to be defined as 'q <from_vertex> <to_vertex>'");
            }
            i++;
            while (i < len && line[i] >= '0' && line[i] <= '9') {
                to *= 10;
                to += line[i] - '0';
                i++;
            }
            if (i < len || to == 0 || to > size) {
                error("Point to point in problem input file has to be defined as 'q <from_vertex> <to_vertex>'");
            }
            pairs[temp_pairs] = {from - 1, to - 1};
            temp_pairs++;
        } else if (line[0] == 'p') {
            if (no_pairs > 0) {
                warning("Problem in problem input file should be defined only once (ignoring further definitions)");
                continue;
            }
            if (line.substr(1, 12) != " aux sp p2p ") {
                error("Problem in problem input file has to be defined as 'p aux sp p2p <no_pairs>'");
            }
            int i = 13;
            while (i < len && line[i] >= '0' && line[i] <= '9') {
                no_pairs *= 10;
                no_pairs += line[i] - '0';
                i++;
            }
            if (i < len || no_pairs == 0) {
                error("Problem in problem input file has to be defined as 'p aux sp p2p <no_pairs>'");
            }
            pairs = new pair[no_pairs];
        } else if (line[0] != 'c') {
            warning("Problem input file's lines should always start with p, q or c (ignoring other lines)");
        }
    }
    if (no_pairs == 0) {
        error("Problem input file has to define a problem like 'p aux sp p2p <no_pairs>'");
    }
    if (temp_pairs < no_pairs) {
        error("Problem input file has to define as many pairs as declared in problem line");
    }

    int edges = graph.get_edges();
    int Cmin = graph.get_Cmin();
    int Cmax = graph.get_Cmax();
    out << "p res sp p2p " << alg_name() << endl;
    out << "g " << size << ' ' << edges << ' ' << Cmin << ' ' << Cmax << endl;

    long* dists = new long[size];
    vertex* pred = new vertex[size];
    for (int i = 0; i < no_pairs; i++) {
        dijkstra(graph, pairs[i].s, dists, pred);
        out << "d " << pairs[i].s + 1 << ' ' << pairs[i].e + 1 << ' ' << dists[pairs[i].e] << endl;
    }
}