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
	unordered_map<int, int>iter; // iter array, the value of iter[u] means we have augmented all the edges(starting from u) indexed between 0 and iter[u]-1.
	unordered_map<int, vector<edge<T>> >Graph; //adjacency list of the graph
	const long long inf;// a number representing infinity
public:
	DN(int V):inf(0x3f3f3f3f3f3f3f3f){
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
		
		// Add the reversed edge.
		Graph[to].push_back( edge<T>(from, 0, 0, Graph[from].size()-1) );
	}
	void init(){
		level.clear();
		iter.clear();
	}
	bool bfs(){
		level.clear();
		queue<int>q; // the queue for bfs
		q.push(source); // add the source the the queue
		level[source] = 1; // source is on level 1
		while(!q.empty()){
			int u = q.front();q.pop();
			//traverse all the edges starting from vertex u
			for(int i=0; i<Graph[u].size(); i++){
				auto e = Graph[u][i];
				if(level[e.to]==0 && e.cap > e.flow){ // if the destination is not accessed before and the edge is of capacity greater than 0 
					level[e.to] = level[u] + 1; // update the level for the destination vertex
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
		T flow = 0;
		for(int &i = iter[u]; i < Graph[u].size(); i++){ // use reference type &, so when i increases, iter[u] will also increase.  
			auto &e = Graph[u][i];
			if(e.cap > e.flow && level[u] + 1 == level[e.to]){
				T d = dfs(e.to, min(f, e.cap - e.flow)); // e.to can receive min(f, e.cap - e.flow) units flow at most.
				if(d > 0){
					e.flow += d; // update the flow of the current edge
					Graph[e.to][e.rev_id].flow -= d; // update the flow of the reversed edge
					// return d;
					flow += d;
					f -= d;
					if(f == 0)break; // can not provide more flow
				}
			}
		}
		return flow;
	}
	T maximum_flow(){
		init();
		T mf = 0;
		while(bfs()){
			iter.clear(); //clear the iter
			T increment = 0;
			increment = dfs(source, inf); // inject infinite flow to the source, augment on mutiple paths to the sink.
			mf += increment;
		}
		return mf;
	}
	
};


int main(int argc, char *argv[]) {
	
	int n,m,s,t;
	cin>>n>>m>>s>>t;
	DN<ll>mf(n);
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
