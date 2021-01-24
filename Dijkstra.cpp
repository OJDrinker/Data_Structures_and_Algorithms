#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Data structure to store graph edges
struct Edge {
	int source, dest, weight;
};

// data structure to store heap nodes
struct Node {
	int vertex, weight;
};

// class to represent a graph object
class Graph
{
public:
	// construct a vector of vectors of Edge to represent an adjacency list
	vector<vector<Edge>> adjList;

	// Graph Constructor
	Graph(vector<Edge> const& edges, int N)
	{
		// resize the vector to N elements of type vector<Edge>
		adjList.resize(N);

		// add edges to the undirected graph
		for (Edge const& edge : edges)
		{
			// insert at end
			adjList[edge.source].push_back(edge);
		}
	}
};

void print_route(vector<int> const& prev, int i)
{
	if (i < 0)
		return;

	print_route(prev, prev[i]);
	cout << i << " ";
}

// Comparison object to be used to order the heap
struct comp
{
	bool operator()(const Node& lhs, const Node& rhs) const
	{
		return lhs.weight > rhs.weight;
	}
};

// Run Dijkstra's algorithm on given graph
void shortestPath(Graph const& graph, int source, int N)
{
	// create min heap and push source node having distance 0
	priority_queue<Node, vector<Node>, comp> min_heap;
	min_heap.push({ source, 0 });

	// set infinite distance from source to v initially
	vector<int> dist(N, INT_MAX);

	// distance from source to itself is zero
	dist[source] = 0;

	// boolean array to track vertices for which minimum
	// cost is already found
	vector<bool> done(N, false);
	done[source] = true;

	// stores predecessor of a vertex (to print path)
	vector<int> prev(N, -1);

	// run till min-heap is empty
	while (!min_heap.empty())
	{
		// Remove and return best vertex
		Node node = min_heap.top();
		min_heap.pop();

		// get vertex number
		int u = node.vertex;

		// do for each neighbor v of u
		for (auto i : graph.adjList[u])
		{
			int v = i.dest;
			int weight = i.weight;

			// Relaxation step
			if (!done[v] && (dist[u] + weight) < dist[v])
			{
				dist[v] = dist[u] + weight;
				prev[v] = u;
				min_heap.push({ v, dist[v] });
			}
		}

		// marked vertex u as done so it will not get picked up again
		done[u] = true;
	}

	for (int i = 0; i < N; ++i)
	{
		if (i != source && dist[i] != INT_MAX)
		{
			cout << "Path (" << source << " -> " << i << "): Minimum Cost = "
				<< dist[i] << " and Route is [ ";
			print_route(prev, i);
			cout << "]" << endl;
		}
	}
}

int main()
{
	// initialize edges as per above diagram
	vector<Edge> edges =
	{
		{1,2,4},{1,3,5},{2,3,5},{2,4,6}
	};

	// Number of nodes in the graph
	int N = 3;

	// construct graph
	Graph graph(edges, N);

	int source = 1;
	shortestPath(graph, source, N);

	return 0;
}