#ifndef UNTITLED_HELPER_H
#define UNTITLED_HELPER_H

#include <cmath>
#include <iomanip>
#include <stdexcept>
#include<algorithm>
#include<climits>
#include<fstream>
#include<iostream>
#include<sstream>
#include<unistd.h>
#include<cstdint>
#include<cstdlib>

#include<set>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#include<vector>
#include<random>
using namespace std;
using namespace std;

inline void error(const string& errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
}

struct DiGraph{
    unordered_map<int, unordered_map<int, int>> edges;
    unordered_set<int> nodes;
};

typedef unordered_map<int, unordered_map<int, int>> Graph;
typedef enum{CUT, b} MODE;

/*
 * Print useful informations.
 */
void usage();

/*
 * Process an input file.
 * Input: filename.
 * Output: a Graph.
 */
void eval(string file_name, DiGraph& dg);

/*
 * Save graph to a file.
 * Input: filename and graph.
 * Output: txt graph file.
 */
void save(string file_name, DiGraph& dg);

/*
 * Save cut result after applying min-cut algorithm.
 */
void saveCutResult();

/*
 * Generate a random graph by setting numbers of nodes and edge weight ranges.
 * Ensure that every node has at least one edge connected.
 */
void generateRandomGraph(DiGraph& dg);


/*
 * Append a file info into current graph.
 */
void appendToGraph(string& file_name, DiGraph& dg);


/*
 * Cut a graph into several sub-graphs, recursively.
 * ensure the number of nodes in every sub-graph is less than max_nodes.
 * Save result to vector<DiGraph> ans.
 */
void cutGraph(DiGraph& dg, int max_nodes);



/*
 * Get reachable nodes starting from a node.
 */
vector<int> getReachableNodes(DiGraph& dg, int start);


/*
 * Get shortest distance between two nodes.
 * If there is no such thing, return -1;
 */
int getMinDistance(DiGraph& dg, int start, int end);

/*
 * Helper function:
 * Check if a node is in the graph.
 */
bool checkValidNode(DiGraph& dg, int node);

/*
 * Treat the directed graph as an undirected graph, use
 * Stoeer-Wagner Min-Cut Algorithm.
 * Reference: https://www.hackerearth.com/practice/algorithms/graphs/min-cut/tutorial/
 *
 */
pair<DiGraph, DiGraph> minCut(DiGraph& dg);

/*
 * Restore the graph using sub-graph files and deleted edges file.
 * Will print "Valid check!",
 * if the restored graph is consistent with original graph.
 */
void restoreAndCheck(DiGraph& dg);

#endif //UNTITLED_HELPER_H
