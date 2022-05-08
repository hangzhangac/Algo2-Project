#include <iostream>
#include <queue>
#include <unordered_map>
#include "edge.hpp"
using namespace std;
typedef long long ll;

template<class T>
class EK{
	
private:
	int V; // the number of vertices
	int source, sink;
	unordered_map<int, pair<int,int>>pre; // record the edge getting to current vertex
	unordered_map<int, T>flow; // key is the number of vertex, value is the number of flow accumulated in this vertex
	unordered_map<int, vector<edge<T>> >Graph; // adjaceny list of the graph
	const long long inf;
public:
	EK(int V):inf(0x3f3f3f3f3f3f3f3f){
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
		pre.clear();
		flow.clear();
	}
	bool bfs(){
		init();
		queue<int>q;
		q.push(source);
		flow[source] = inf; // Injecting infinite water to the source
		while(!q.empty()){
			int u = q.front();q.pop();
			for(int i=0; i<Graph[u].size(); i++){
				auto e = Graph[u][i];
				if(flow[e.to]==0 && e.cap > e.flow){
					pre[e.to] = {u,i}; // record the edge getting to e.to
					flow[e.to] = min(flow[u], e.cap - e.flow); // inject min(flow[u], e.cap - e.flow) water to e.to
					q.push(e.to); // push it to the queue
				}
			}
			if(flow[sink])break; // If the sink has been injected with flow, break
		}
		if(flow[sink] == 0)return false; // no augment path from the source to the sink
		return true;
	}
	T maximum_flow(){
		T mf = 0;
		while(bfs()){
			
			T increment = flow[sink]; // increment flow
			mf += increment;
			int u = sink;
			while(u!=source){
				int from = pre[u].first;
				int index = pre[u].second;
				Graph[from][index].flow += increment; // update the residual graph
				Graph[u][Graph[from][index].rev_id].flow -= increment; // update the reversed edge
				u = from;
			}
		}
		return mf;
	}
	
};


int main(int argc, char *argv[]) {
	
	int n,m,s,t;
	cin>>n>>m>>s>>t;
	EK<ll>mf(n);
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
