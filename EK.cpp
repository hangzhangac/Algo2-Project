#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include "edge.hpp"
using namespace std;
typedef long long ll;

template<class T>
class EK{
	
private:
	int V;
	int source, sink;
	vector<pair<int,int>>pre;
	vector<T>flow;
	unordered_map<int, vector<edge<T>> >Graph;
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
		// Add the reverse edge.
		Graph[to].push_back( edge<T>(from, 0, 0, Graph[from].size()-1) );
	}
	void init(){
		pre.clear();flow.clear();
		for(int i=0; i < V; i++){
			pre.push_back({-1,-1});
		}
		for(int i=0; i < V; i++){
			flow.push_back(0);
		}
	}
	bool bfs(){
		for(int i=0; i < V; i++){
			flow[i] = 0;
		}
		queue<int>q;
		q.push(source);
		flow[source] = inf;
		// pre[source] = {-1,-1};
		while(!q.empty()){
			int u = q.front();q.pop();
			for(int i=0; i<Graph[u].size(); i++){
				auto e = Graph[u][i];
				if(flow[e.to]==0 && e.cap > e.flow){
					pre[e.to] = {u,i};
					flow[e.to] = min(flow[u], e.cap - e.flow);
					q.push(e.to);
				}
			}
			if(flow[sink])break;
		}
		if(flow[sink] == 0)return false;
		return true;
	}
	T maximum_flow(){
		init();
		T mf = 0;
		while(bfs()){
			
			T increment = flow[sink];
			mf += increment;
			int u = sink;
			while(u!=source){
				int from = pre[u].first;
				int index = pre[u].second;
				Graph[from][index].flow += increment;
				Graph[u][Graph[from][index].rev_id].flow -= increment;
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