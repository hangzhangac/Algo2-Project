#include <iostream>
#include <queue>
#include <unordered_map>
#include "edge.hpp"
using namespace std;
typedef long long ll;

template<class T>
class DN{
	
private:
	int V; // number of vertices
	int source, sink;
	unordered_map<int, int>level; // level array for bfs
	unordered_map<int, int>iter;
	unordered_map<int, vector<edge<T>> >Graph; //adjacency list of the graph
	const long long inf;// a number representing infinity
public:
	DN(int V):inf(0x3f3f3f3f3f3f3f3f){
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
		
		// Add the reversed edge.
		Graph[to].push_back( edge<T>(from, 0, 0, Graph[from].size()-1) );
	}
	void init(){
		level.clear();
		iter.clear();
	}
	bool bfs(){
		level.clear();
		queue<int>q;
		q.push(source); // add the source the the queue
		level[source] = 1; // source is on level 0
		while(!q.empty()){
			int u = q.front();q.pop();
			//traverse all the edges starting from vertex u
			for(int i=0; i<Graph[u].size(); i++){
				auto e = Graph[u][i];
				if(level[e.to]==0 && e.cap > e.flow){ // if the destination is not accessed before
					level[e.to] = level[u] + 1;
					q.push(e.to);
				}
			}
			if(level[sink] != 0)break;// If we have got to the sink, just break
		}
		if(level[sink] == 0)return false; // no augment path any more
		return true;
	}
	T dfs(int u, T f){
		if(u == sink) return f;
		for(int &i = iter[u]; i < Graph[u].size(); i++){
			auto &e = Graph[u][i];
			if(e.cap > e.flow && level[u] + 1 == level[e.to]){
				T d = dfs(e.to, min(f, e.cap - e.flow)); // e.to can receive min(f, e.cap - e.flow) units flow at most.
				if(d > 0){
					e.flow += d; // update the flow of the current edge
					Graph[e.to][e.rev_id].flow -= d; // update the flow of the reversed edge
					return d;
				}
			}
		}
		return 0;
	}
	T maximum_flow(){
		init();
		T mf = 0;
		while(bfs()){
			iter.clear(); //clear the iter
			T increment = 0;
			while((increment = dfs(source, inf)) > 0) // augment on mutiple paths
				mf += increment;
		}
		return mf;
	}
	
};


int main(int argc, char *argv[]) {
	
	int n,m,s,t;
	cin>>n>>m>>s>>t;
	DN<ll>mf(n);
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
