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
};