# Algo2-Project


### Edmonds-Karp algorithm is implemented in EK.cpp
### Push-Relabel algorithm is implemented in PR.cpp
### Dinic algorithm is implemented in DN.cpp
#### To test:
```bash
chmod +x compile.sh
./compile.sh
python3 test.py pr 1 # Test Push-Relabel algorithm on data1.
python3 test.py dn 1 # Test Dinic algorithm on data1.
python3 test.py ek 1 # Test Edmonds-Karp algorithm on data1.
python3 test.py pr 2 # Test Push-Relabel algorithm on data2.
python3 test.py dn 2 # Test Dinic algorithm on data2.
python3 test.py ek 2 # Test Edmonds-Karp algorithm on data2.
```

#### Input Format:
First line contains 4 numbers, n, m, s, t, separated by space, representing the number of vertices, number of edges, the source, the sink respectively.  
Then, there are m lines following, for the i-th line, there are three numbers separated by space, u<sub>i</sub>, v<sub>i</sub>, c<sub>i</sub>, represents there is an edge from vertex u<sub>i</sub> to vertex v<sub>i</sub> of capacity c<sub>i</sub>.  
The vertex is indexed from 1. 
#### Output Format:
```bash
It will output one number: the maximum flow from the source to the sink.
```
#### Performance (Running Time)
|     | data1  | data2  |
|  ----  | ----  | ----  |
| Edmonds-Karp  | 1.975s | 3481.731s |
|  Dinic | 0.270s | 15.787s |
| Push-Relabel  | 0.427s | 3.663s |
#### Data
data1 is a small scale dataset where n<=100 and m<=5000.  
data2 is a large scale dataset where n<=1200 and m<=36075.  
All the data is from LibreOJ, an online judge platform for International Olympiad in Informatics.
