#include <iostream>
#include<map>
#include<stack>
#include <vector>
#include<queue>
#include<fstream>
#include<list>
#include<cstdio>

using namespace std;

class Graph {
private:
	int V; // Number of vertices
	vector <list<pair<int, int>>> adjList;
	vector<int>distance;
	vector<int>DFStrav;
	vector<int>BFStrav;
public:
	Graph(int V = 0) {
		this->V = V;
		adjList.resize(V);
		distance.resize(V, INT_MAX);
	}
	void addEdge(int u, int v, int w) {
		if (max(u, v) >= V) {
			adjList.resize(max(u, v) + 1);
			V = max(u, v) + 1;
		}
		adjList[u].push_back({ v, w });
		adjList[v].push_back({ u, w });
	}
	void display() {
		for (int i = 0; i < V; ++i) {
			for (auto neighbor : adjList[i]) {
				cout <<"Vertex " << i <<" -> " << neighbor.first << " with weight: " << neighbor.second<<endl;
			}
		}
	}
	int NumberOfEdges() {
		int count = 0;
		map<pair<int, int>, bool> mp;
		for (int i = 0; i < V; ++i) {
			for (auto neighbor : adjList[i]) {
				if (mp[{i, neighbor.first}] != true && mp[{neighbor.first, i}] != true) {
					++count;
					mp[{i, neighbor.first}] = true;
					mp[{neighbor.first, i}] = true;
				}
			}
		}
		return count;
	}
	bool CheckIfConnected(int u, int v) {
		for (auto neighbor : adjList[u]) {
			if (neighbor.first == v) {
				return true;
			}
		}
		return false;
	}
	bool RemoveEdge(int u, int v, int w) {
		if (u > V || v > V)
			return false;
		adjList[u].remove({ v,w });
		adjList[v].remove({ u,w });
		return true;
	}
	void DFS() {
		vector<int>vis(V);
		stack<int>s;
		int node = 0;
		vis[node] = true;
		s.push(node);

		while (!s.empty()) {
			node = s.top();
			s.pop();

			for (auto neighbor : adjList[node]) {
				if (!vis[neighbor.first]) {
					vis[neighbor.first] = true;
					s.push(neighbor.first);
				}
			}
			DFStrav.push_back(node);
		}
	}

	void BFS() {
		vector<int>vis(V);
		queue<int>q;
		int node = 0;
		vis[node] = true;
		q.push(node);
		while (!q.empty()) {
			node = q.front();
			q.pop();
			BFStrav.push_back(node);
			for (auto neighbor : adjList[node]) {
				if (!vis[neighbor.first]) {
					vis[neighbor.first] = true;
					q.push(neighbor.first);
				}
			}
		}
	}
	void Dijkstra(int u, int v) {
		priority_queue<pair<int, int>>q; //{distance, node}
		vector<int>vis(V);
		int mn = min(u, v);
		distance[mn] = 0; //Source node
		q.push({ 0,mn });

		while (!q.empty()) {
			int node = q.top().second;
			q.pop();
			if (vis[node])
				continue;
			vis[node] = true;
			for (auto neighbour : adjList[node]) {
				if (distance[node] + neighbour.second < distance[neighbour.first]) {
					distance[neighbour.first] = distance[node] + neighbour.second;
					q.push({ -1 * distance[neighbour.first],neighbour.first });
				}
			}
		}
		cout << "Shortest path between "
			<< u << " & " << v << " is " <<
			max(distance[v], distance[u]) <<endl;
		distance = vector<int>(V, INT_MAX);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	ifstream in("input.txt");
	int e, u, v, w;
	in >> e;
	Graph g(e);
	
	for (int i = 0; i < e; ++i) {
		in >> u >> v >> w;
		g.addEdge(u, v, w);
	}
	cout << "Undirected and Weighted Graph:" << endl;
	g.display();
	g.DFS();
	g.BFS();
	g.Dijkstra(2,4);
	g.Dijkstra(1,3);
	in.close();
}
