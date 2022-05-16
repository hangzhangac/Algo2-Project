template<class T>
struct edge{
	int to; // destination of this edge
	T cap; // the capacity of this edge
	T flow; // the amount of flow flowing through this edge
	int rev_id; // the reversed edge's index in Graph[to] 
	edge(){} // defalut constructor
	edge(int to, T cap, T flow, int rev_id){ // constructor
		this->to = to;
		this->cap = cap;
		this->flow = flow;
		this->rev_id = rev_id;
	}
};
