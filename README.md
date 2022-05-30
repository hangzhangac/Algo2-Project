# Algo2-Project


### Edmonds-Karp algorithm is implemented in EK.cpp
### Push-Relabel algorithm is implemented in PR.cpp
### Dinic algorithm is implemented in DN.cpp
#### Time Complexity
|  Algorithm   | Time Complexity  |
|  ----  | ----  |
| Edmonds-Karp  | O(nm<sup>2</sup>) |
|  Dinic | O(n<sup>2</sup>m) |
| Push-Relabel  | O(n<sup>3</sup>) |
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
#### Data
data1 is a small scale dataset where n<=100 and m<=5000.  
data2 is a large scale dataset where n<=1200 and m<=36075.  
All the data is from LibreOJ, an online judge platform for International Olympiad in Informatics.
#### Performance (Running Time)
|     | data1  | data2  |
|  ----  | ----  | ----  |
| Edmonds-Karp  | 1.975s | 92.807hours |
|  Dinic | 0.270s | 673.948s |
| Push-Relabel  | 0.427s | 123.060s |

We can see that on data1 (small scale dataset), dinic is faster than push-relabel algorithm, that is possibly because the implementation of dinic has a lower constant.  
When running the code on data2 (large scale dataset), instead of the constant, the time complexity itself plays the decisive role.
#### Reference
[1] CORMEN, T. H., & CORMEN, T. H. (2001). Introduction to algorithms. Cambridge, Mass, MIT Press.  
[2] [Dinic algorithm code](https://www.geeksforgeeks.org/dinics-algorithm-maximum-flow/ "dinics-algorithm-maximum-flow")   
[3] [Push-Relabel algorithm code](https://www.geeksforgeeks.org/push-relabel-algorithm-set-2-implementation/ "Push-Relabel algorithm")
