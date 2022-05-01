#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include "edge.hpp"
using namespace std;
typedef long long ll;

template<class T>
class PR{

private:
	int V;
	int source, sink;
	unordered_map<int, int>height;
	unordered_map<int,T>excess;
	unordered_map<int, vector<edge<T>> >Graph;
	const int inf;
public:
	PR(int V):inf(0x3f3f3f3f){
		this->V = V;
	}
	void setSource(int source){
		this->source = source;
	}
	void setSink(int sink){
		this->sink = sink;
	}
	void addEdge(int from, int to, T cap){
		Graph[from].push_back( edge<T>(to, cap, 0, Graph[to].size()) );
		// Add the reverse edge.
		Graph[to].push_back( edge<T>(from, 0, 0, Graph[from].size()-1) );
	}
	void preflow(){
		height.clear();
		excess.clear();
		height[source] = V;
		for(int i=0; i<Graph[source].size(); i++){
			auto &e = Graph[source][i];
			e.flow = e.cap;
			excess[e.to] += e.cap;
			excess[source] -= e.cap;
			Graph[e.to][e.rev_id].flow = -e.flow;
		}

	}
	bool relabel(int u){
		int h = inf;
		for(int i=0; i<Graph[u].size(); i++){
			auto e = Graph[u][i];
			if(e.cap > e.flow){
				h = min(h, height[e.to]);
			}
		}
		
		if(h == inf) return false;
		height[u] = h + 1;
		for(int i=0; i<Graph[u].size(); i++){
			if(excess[u] == 0)break;
			auto e = Graph[u][i];
			if(height[e.to] + 1 == height[u] && e.cap > e.flow){
				push_(u, i);
			}
		}
		return true;
	}
	void push_(int u, int index){
		auto &e = Graph[u][index];
		T d = min(excess[u], e.cap - e.flow);
		e.flow += d;
		Graph[e.to][e.rev_id].flow -= d;
		excess[u] -= d;
		excess[e.to] += d;
	}
	T maximum_flow(){
		preflow();
		bool still_relabel = true;
		while(still_relabel){
			still_relabel = false;
			for(int i=0; i < V; i++){
				if(i == source||i == sink)continue;
				if(excess[i] > 0)still_relabel = still_relabel || relabel(i);
			}
		}
		return excess[sink];
	}
};


int main(int argc, char *argv[]) {
	
	int n,m,s,t;
	cin>>n>>m>>s>>t;
	PR<ll>mf(n);
	s--;t--;
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
