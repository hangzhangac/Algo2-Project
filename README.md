# Algo2-Project


### Edmonds-Karp algorithm is implemented in EK.cpp
### Push-Relabel algorithm is implemented in PR.cpp
### Dinic algorithm is implemented in DN.cpp
#### To test:
```bash
chmod +x compile.sh
./compile.sh
python3 test.py pr 1 # Test Push-Relabel algorithm for data1.
python3 test.py dn 1 # Test Dinic algorithm for data1.
python3 test.py ek 1 # Test Edmonds-Karp algorithm for data1.
python3 test.py pr 2 # Test Push-Relabel algorithm for data2.
python3 test.py dn 2 # Test Dinic algorithm for data2.
python3 test.py ek 2 # Test Edmonds-Karp algorithm for data2.
```

#### input format:
```bash
First line contains 4 numbers, n, m, s, t, seperated by space, representing the number of vertices, number of edges, the source, the sink respectively.  
Then, there are m lines following, for the i-th line, there are there numbers seperated by space, u<sub>i</sub>, v<sub>i</sub>, c<sub>i</sub>, represents there is an edge from vertex u<sub>i</sub> to vertex v<sub>i</sub> of capacity c<sub>i</sub>.  
The vertex is indexed from 1. 
```
#### output format:
```bash
It will output one number: the maximum flow from the source to the sink.
```
