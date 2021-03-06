#include <iostream>
#include <queue>
#include <unordered_map>
#include "edge.hpp"
using namespace std;
typedef long long ll;

template<class T>
class PR{

private:
	int V; // the number of vertices
	int source, sink;
	unordered_map<int, int>height; // key is the id of vertex, value is the vertex's height
	unordered_map<int,T>excess; // key is the id of vertex, value is the excess flow of that vertex
	unordered_map<int, vector<edge<T>> >Graph; // adjaceny list of Graph
	const int inf;
public:
	PR(int V):inf(0x3f3f3f3f){
		this->V = V;
	}
	void setSource(int source){ // set source
		this->source = source;
	}
	void setSink(int sink){ // set sink
		this->sink = sink;
	}
	void addEdge(int from, int to, T cap){ // add an edge
		Graph[from].push_back( edge<T>(to, cap, 0, Graph[to].size()) );
		// Add the reverse edge.
		Graph[to].push_back( edge<T>(from, 0, 0, Graph[from].size()-1) );
	}

	// Create an initial preflow in the flow network
	void preflow(){
		height.clear();
		excess.clear();
		height[source] = V;
		for(int i=0; i<Graph[source].size(); i++){
			auto &e = Graph[source][i];
			e.flow = e.cap;
			//update the excess
			excess[e.to] += e.cap;
			excess[source] -= e.cap;
			// update the reversed edge
			Graph[e.to][e.rev_id].flow = -e.flow;
		}
		return;
	}
	bool push_relabel(int u){
		int h = inf;
		// First, check if it needs relabel
		for(int i=0; i<Graph[u].size(); i++){
			auto e = Graph[u][i];
			if(e.cap > e.flow){
				h = min(h, height[e.to]);
			}
		}
		
		if(h == inf) return false;
		height[u] = h + 1; // relabel it
		for(int i=0; i<Graph[u].size(); i++){
			if(excess[u] == 0)break; // no excess any more, just break
			auto e = Graph[u][i];
			if(height[e.to] + 1 == height[u] && e.cap > e.flow){
				push_(u, i); // push some flow to the current edge.
			}
		}
		return true;
	}
	void push_(int u, int index){ // push some flow from the vertex u to the i-th edge of vertex u
		auto &e = Graph[u][index]; // use reference type &.
		T d = min(excess[u], e.cap - e.flow);
		e.flow += d; // update the flow of the edge.
		Graph[e.to][e.rev_id].flow -= d; // update the flow of the reversed edge
		// update the excess array for vertex u and the destination of this edge
		excess[u] -= d;
		excess[e.to] += d;
	}
	T maximum_flow(){
		preflow();
		bool still_relabel = true;
		while(still_relabel){
			still_relabel = false;
			for(int i=0; i < V; i++){
				if(i == source||i == sink)continue; // skip source and sink, any flow arriving at the sink will be stored in the sink
				if(excess[i] > 0)still_relabel = still_relabel || push_relabel(i); // if it has excess flow, push_relabel it
			}
		}
		return excess[sink]; // the flow stored in the sink is the maximum flow.
	}
};


int main(int argc, char *argv[]) {
	
	int n,m,s,t;
	cin>>n>>m>>s>>t;
	PR<ll>mf(n);
	s--;t--; // the vertex is indexed from 1 in the data, so -1 to let them indexed from 0
	mf.setSource(s);
	mf.setSink(t);
	while(m--){
		int u,v,c;
		cin>>u>>v>>c;
		u--;v--;
		mf.addEdge(u, v, c);
	}
	cout<<mf.maximum_flow()<<endl;
	return 0;
}
