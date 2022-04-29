#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;
typedef long long ll;

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
class DN{
	
private:
	int V;
	int source, sink;
	vector<int>level;
	vector<int>iter;
	unordered_map<int, vector<edge<T>> >Graph;
	const long long inf;
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
		// Add the reverse edge.
		Graph[to].push_back( edge<T>(from, 0, 0, Graph[from].size()-1) );
	}
	void init(){
		level.assign(V, -1);
		iter.assign(V,0);
	}
	bool bfs(){
		level.assign(V, -1);
		queue<int>q;
		q.push(source);
		level[source] = 0;
		while(!q.empty()){
			int u = q.front();q.pop();
			for(int i=0; i<Graph[u].size(); i++){
				auto e = Graph[u][i];
				if(level[e.to]==-1 && e.cap > e.flow){
					level[e.to] = level[u] + 1;
					q.push(e.to);
				}
			}
			if(level[sink]!=-1)break;
		}
		if(level[sink] == -1)return false;
		return true;
	}
	T dfs(int u, T f){
		if(u == sink) return f;
		for(int &i = iter[u]; i < Graph[u].size(); i++){
			auto &e = Graph[u][i];
			if(e.cap > e.flow && level[u] + 1 == level[e.to]){
				T d = dfs(e.to, min(f, e.cap - e.flow));
				if(d > 0){
					e.flow += d;
					Graph[e.to][e.rev_id].flow -= d;
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
			iter.assign(V,0);
			T increment = 0;
			while((increment = dfs(source, inf)) > 0)
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
