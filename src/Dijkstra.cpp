#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

using DPair = std::pair<int, int>;
using DPairVect = std::vector<DPair>;
constexpr static auto INF = std::numeric_limits<int>::max();

class Graph {
  int verticeCount_;
  std::vector<DPairVect> vertices_;

public:
  Graph(int verticeCount)
      : verticeCount_{verticeCount}, vertices_{verticeCount_} {}

  void addEdge(int a, int b, int weight) {
    vertices_[a].emplace_back(b, weight);
    vertices_[b].emplace_back(a, weight);
  }

  // Prints shortest paths from src to all other vertices
  void printShortestPath(int srcVertice) {
    using namespace std;

    // https://www.geeksforgeeks.org/implement-min-heap-using-stl/
    priority_queue<DPair, vector<DPair>, greater<DPair>> pq;
    vector<int> dist(verticeCount_, INF);
    pq.emplace(0, srcVertice);
    dist[srcVertice] = 0;

    while (!pq.empty()) {
      int u = pq.top().second;
      pq.pop();

      // 'i' is used to get all adjacent vertices of a vertex
      for (auto i = vertices_[u].begin(); i != vertices_[u].end(); ++i) {
        // Get vertex label and weight of current adjacent
        // of u.
        int v = (*i).first;
        int weight = (*i).second;

        //  If there is shorted path to v through u.
        if (dist[v] > dist[u] + weight) {
          // Updating distance of v
          dist[v] = dist[u] + weight;
          pq.push(make_pair(dist[v], v));
        }
      }
    }

    // Print shortest distances stored in dist[]
    cout << "Vertex\tDistance from Source" << endl;
    for (int i = 0; i < verticeCount_; ++i) {
      cout << i << "\t" << dist[i] << endl;
    }
  }
};

int main() {
  Graph g{9};

  g.addEdge(0, 1, 4);
  g.addEdge(0, 7, 8);
  g.addEdge(1, 2, 8);
  g.addEdge(1, 7, 11);
  g.addEdge(2, 3, 7);
  g.addEdge(2, 8, 2);
  g.addEdge(2, 5, 4);
  g.addEdge(3, 4, 9);
  g.addEdge(3, 5, 14);
  g.addEdge(4, 5, 10);
  g.addEdge(5, 6, 2);
  g.addEdge(6, 7, 1);
  g.addEdge(6, 8, 6);
  g.addEdge(7, 8, 7);

  g.printShortestPath(0);

  return 0;
}
