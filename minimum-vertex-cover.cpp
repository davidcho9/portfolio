//
//PROJECT SPECIFICATIONS
//
// Oganesson Dynamics wants to ensure that all of its communications within a network remain private, 
// but this requires extra equipment for at least one end of each communicating pair of sites.

// Given a graph where vertices represent work sites and edges represent pairs of sites that must be able to communicate securely, 
// what are the fewest work sites that can have security-monitoring nodes to guarantee that each pair has at least one?

// Hint: you will need to use a branch-and-bound approach to solving this problem.

// NOTE: For this problem, your program must be guaranteed to output the correct answer 
// (or timeout in the process of searching). If your program's output is incorrect for a single test case, 
// 	it will receive 0 credit on this problem (regardless of how many other test cases it passes). 
// 	Timing out is allowed, however. Test cases on which you time out will result in no points from that test case,
// 	but will not zero out points earned on test cases where your program returned the correct output.

// Input Format:
// The first line contains two values: the number of work sites (N) and the number of pairs of sites that must be
// able to communicate securely (M). The next M lines each describe a pair of communicating sites, indicating the unique id of each.

// Constraints:
// 1 ≤ N ≤ 200
// 1 ≤ M ≤ 10,000
// 0 ≤ Work Site IDs < N

// Output Format:
// A single number indicating the minimum number of work sites that must have security monitoring nodes to ensure that at least one exists for every communicating pair.

// Example 0
// Sample Input:
// 5 6
// 0 1
// 0 2
// 0 4
// 1 4
// 2 3
// 2 4
// Sample Output:
// 3

#include<iostream>
#include<vector>
#include<map>

using namespace std;

class Node{
private:
  int value;
  vector<int> edges;
  bool security;
  
public:
  Node(int v) : value(v){this->security = false;}

  void addEdge(int edge){
    edges.push_back(edge);
  }
  
  int getValue(){
    return this->value;
  }
  vector<int> getEdges(){
    return this->edges;
  }
  
  int edgeCount(){
    return this->edges.size();
  }
  
  void setSecurity(){
    this->security = !this->security;
  }
  
  bool getSecurity(){
    return this->security;
  }
  
  void printNode(){
    cout << "Value: " << value << " || " << "Edges: ";
    for(int i = 0; i<edges.size(); i++){
      cout << edges[i] << " - ";
    }
    cout<<endl;
  }
  
};

class Graph{
private:
  vector<Node> graph;

public:
  Graph(){};
  
  ~Graph(){}
  
  int findNode(int node){
    for(int i=0; i<this->graph.size(); i++){
      if(this->graph[i].getValue() == node){
        return i;
      }
    }
    return -1;
  }
  
  Node* getNode(int index){
    return &this->graph[index];
  }

  vector<Node> getGraph(){
    return this->graph;
  }
  
  
  void addNode(int start, int dest){
    int index = this->findNode(start);
    if(index != -1){
      this->graph[index].addEdge(dest);
    }
    else{
      Node n(start); 
      n.addEdge(dest);
      this->graph.push_back(n);
    }
    
    index = this->findNode(dest);
    if(index != -1){
      this->graph[index].addEdge(start);
    }
    else{
      Node n (dest); 
      n.addEdge(start);
      this->graph.push_back(n);
    }
  }
  
  bool checkSites(vector<int>nodes){
    
    for(int i=0; i<graph.size(); i++){
      for(int j=0; j<graph[i].getEdges().size(); j++){
        int index = this->findNode(graph[i].getEdges()[j]);
        Node dest = *this->getNode(index) ;
        if(!graph[i].getSecurity() && !dest.getSecurity()){
          return false;
        }
      }
    }
    return true;
  }
  
  void printGraph(){
    for(int i=0; i<this->graph.size();i++){
      this->graph[i].printNode();
    }
  }
  
};

int minimum = 999999999;

void minimumSites(const Graph& g, vector<int> include, vector<int> exclude, vector<int> undecided){
  
  Graph graph = g;
  
    for(int i = 0; i<include.size(); i++){
      int index = graph.findNode(include[i]);
      graph.getNode(index)->setSecurity();
    }
  
  if(include.size() >= minimum){
    return;
  }
  
  if(graph.checkSites(include)){
    int possible_minimum = include.size();
    if(possible_minimum < minimum){
      minimum = possible_minimum;
      return;
    }
  }
  
  if(undecided.size() == 0){
  	return;
  }
  
  int node = undecided.back();
	
	undecided.pop_back();
	
	
	include.push_back(node);
	minimumSites(g, include,exclude ,undecided);
	
	include.pop_back();
	exclude.push_back(node);
	
	int index = graph.findNode(exclude.back());
	Node exclude_node = *graph.getNode(index);
	for(int i=0; i<exclude_node.getEdges().size(); i++){
    bool found = false;
    for (int k=0; k<include.size();k++){
      if(include[k] == exclude_node.getEdges()[i]){
        found = true;
      }
    }
    if(found==false){
      include.push_back(exclude_node.getEdges()[i]);
    }
	  for(int j=0; j<undecided.size();j++){
	    if(undecided[j] == exclude_node.getEdges()[i]){
	      undecided.erase(undecided.begin() + j);
	    }
	  }
	}
	
	
  minimumSites(g, include, exclude, undecided);
  

	return;
}

void swap(vector<vector<int>>& vec, int index1, int index2)  
  {  
      vector<int> temp = vec[index1];  
      vec[index1] = vec[index2];  
      vec[index2] = temp;  
  }  
    
void selectionSort(vector<vector<int>>& vec, int n)  
  {  
      int i, j, min_idx;  
    
      // One by one move boundary of unsorted subarray  
      for (i = 0; i < n-1; i++)  
      {  
          // Find the minimum element in unsorted array  
          min_idx = i;  
          for (j = i+1; j < n; j++)  
          if (vec[j][1] < vec[min_idx][1])  
              min_idx = j;  
    
          // Swap the found minimum element with the first element  
          swap(vec,min_idx,i);  
      }  
  }    


int main(){
  int sites;
  int edges;
  
  cin >> sites >> edges;
  
  int start;
  int dest;

  
  Graph graph;
  
  for(int i = 0; i<edges; i++){
    cin >> start >> dest;
    graph.addNode(start,dest);
  }
  
  //Sort by sites with most edges
  vector<vector<int>> unsorted_undecided;
  for(int i=0; i<graph.getGraph().size(); i++){
    vector<int> vec {graph.getGraph()[i].getValue(), graph.getGraph()[i].edgeCount()};
    unsorted_undecided.push_back(vec);
  }
  
  selectionSort(unsorted_undecided, unsorted_undecided.size());
  
  vector<int> undecided;
  for(int i=0; i<unsorted_undecided.size(); i++){
    undecided.push_back(unsorted_undecided[i][0]);
  }
  
  vector<int> include;
  vector<int> exclude;
  minimumSites(graph, include, exclude, undecided);
  cout<<minimum;
}
