#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
#include <list>
#include <map>
#include <set>
#define mem(a,x) memset(a,x,sizeof(a))
#define gi(x) scanf("%d",&x)
#define gi2(x,y) scanf("%d%d",&x,&y)
#define gi3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define gll(x) scanf("%lld",&x)
#define gll2(x,y) scanf("%lld%lld",&x,&y)
using namespace std;
const double eps=1e-8; 
typedef long long ll;
const int MAXV=1205;
const ll mod=1e9+7;

template<class T>
struct edge{
	int to;
	T cap;
	T flow;
	int rev_id;
	edge(){}
	edge(int to, T cap, T flow, int rev_id){
		this->to = to;
		this->cap = cap;
		this->flow = flow;
		this->rev_id = rev_id;
	}
	bool full(){
		return cap == flow;
	}
};

template<class T>
class EK{
	
private:
	int V;
	int source, sink;
	vector<pair<int,int>>pre;
	vector<T>flow;
	vector<edge<T>>Graph[MAXV+1];
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
				int to = Graph[u][i].to;
				if(flow[to]==0 && Graph[u][i].cap > Graph[u][i].flow){
					pre[to] = {u,i};
					flow[to] = min(flow[u], Graph[u][i].cap - Graph[u][i].flow);
					q.push(to);
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
	scanf("%d%d%d%d",&n,&m,&s,&t);
	EK<ll>mf(n);
	s--;t--;
	mf.setSource(s);
	mf.setSink(t);
	while(m--){
		int u,v,c;
		scanf("%d%d%d",&u,&v,&c);
		u--;v--;
		mf.addEdge(u, v, c);
	}
	cout<<mf.maximum_flow()<<endl;
	return 0;
}