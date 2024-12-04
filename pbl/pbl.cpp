#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;


struct Road {
    int destination;
    int weight;  
};

class TrafficNetwork {
private:
    vector<vector<Road> > adjList;  
    int numIntersections;

public:
    
    TrafficNetwork(int n) {
        numIntersections = n;
        adjList.resize(n);
    }
    void addRoad(int source, int destination, int weight) {
        adjList[source].push_back(Road{destination, weight});
        adjList[destination].push_back(Road{source, weight}); 
    }

    vector<int> dijkstra(int start) {
        vector<int> dist(numIntersections, INT_MAX);
        vector<bool> visited(numIntersections, false);
        dist[start] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
        pq.push(make_pair(0, start));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            if (visited[u]) continue;
            visited[u] = true;

            // Relax all the edges of the vertex u
            for (unsigned int i = 0; i < adjList[u].size(); i++) {
                int v = adjList[u][i].destination;
                int weight = adjList[u][i].weight;

                if (!visited[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        return dist;  
    }
    void optimizeTrafficLights() {
        for (int i = 0; i < numIntersections; i++) {
            vector<int> distances = dijkstra(i);
            cout << "Traffic light optimization for intersection " << i << ":\n";
            cout << "Shortest paths to other intersections:\n";
            for (int j = 0; j < numIntersections; j++) {
                if (distances[j] == INT_MAX) {
                    cout << "No path from " << i << " to " << j << "\n";
                } else {
                    cout << "Intersection " << j << ": " << distances[j] << " units of time\n";
                }
            }
            cout << "------------------------------\n";
        }
    }
    void simulateTraffic(int startIntersection) {
        auto start = high_resolution_clock::now();
        vector<int> shortestPaths = dijkstra(startIntersection);

        cout << "Simulating traffic from intersection " << startIntersection << ":\n";
        for (int i = 0; i < numIntersections; i++) {
            if (shortestPaths[i] == INT_MAX) {
                cout << "No path to intersection " << i << ".\n";
            } else {
                cout << "Shortest path to intersection " << i << ": " << shortestPaths[i] << " units.\n";
            }
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Simulation completed in " << duration.count() << " microseconds.\n";
    }
};

// Main function
int main() {
    srand(time(0)); 

    TrafficNetwork network(5);
    network.addRoad(0, 1, rand() % 10 + 1);  
    network.addRoad(1, 2, rand() % 10 + 1);
    network.addRoad(2, 3, rand() % 10 + 1);
    network.addRoad(3, 4, rand() % 10 + 1);
    network.addRoad(0, 3, rand() % 10 + 1);
    network.addRoad(1, 4, rand() % 10 + 1);

   
    network.simulateTraffic(0);  
    network.optimizeTrafficLights();  
    return 0;
}
