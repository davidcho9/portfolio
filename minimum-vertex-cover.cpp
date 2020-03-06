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