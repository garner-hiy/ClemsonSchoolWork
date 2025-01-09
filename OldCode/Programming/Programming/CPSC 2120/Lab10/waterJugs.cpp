/*
 * Name: AJ Garner
 * Date Submitted: 4/24/2023
 * Lab Section: 004
 * Assignment Name: Lab 10: Using Breadth-First Search to Solve Puzzles
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// Reflects what each node represents...
// First value units of water in A, second units of water in B
typedef pair<int,int> state;

// Each string in edge_label must be one of the following:
const string actions[] = {"Fill A",
                          "Fill B",
                          "Empty A",
                          "Empty B",
                          "Pour A->B",
                          "Pour B->A"};

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from source_node)
void search(state source_node)
{
  queue<state> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  
  while (!to_visit.empty()) {
    state curnode = to_visit.front();
    to_visit.pop();
    for (state n : nbrs[curnode])
      if (!visited[n]) {
	pred[n] = curnode;
	dist[n] = 1 + dist[curnode];
	visited[n] = true;
	to_visit.push(n);
      }
  }
}

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << "[" << t.first << "," << t.second << "]\n";
  } else {
    cout << "Initial state: " << "[" << s.first << "," << s.second << "]\n";
  }
}
//This function will build the graph needed to fill the different sized buckets
//First it will fill bucket A, next it will fill B, then empty A, then empty B,
//next it will pour A into B, and lastly pour B into A.
void build_graph(void){
  
  int A = 3, B = 4;
  state term = make_pair(A,B);
  state curState = make_pair(0,0);

  while(curState != term) {
    //the next state
    state n;

    // first you need to fill A
    n = make_pair(A,curState.second);

    if(n != curState) {
      pair<state,state> edge = make_pair(curState,n);
      nbrs[curState].push_back(n);
      edge_label[edge] = actions[0];
    }

    // next you need to fill B
    n = make_pair(curState.first,B);

    if(n != curState) {
      pair<state,state> edge = make_pair(curState,n);
      nbrs[curState].push_back(n);
      edge_label[edge] = actions[1];
    }

    // next, empty A
    n = make_pair(0,curState.second);

    if(n != curState) {
      pair<state,state> edge = make_pair(curState,n);
      nbrs[curState].push_back(n);
      edge_label[edge] = actions[2];
    }

    // then, empty B
    n = make_pair(curState.first,0);

    if(n != curState) {
      pair<state,state> edge = make_pair(curState,n);
      nbrs[curState].push_back(n);
      edge_label[edge] = actions[3];
    }

    // next you need to pour A into B
    int newA = curState.first;
    int newB = curState.second;
    if(curState.second < B) {
      while(newA > 0 && newB < B) {
        newA--;
        newB++;
      }
      n = make_pair(newA,newB);

      if(n != curState) {
        pair<state,state> edge = make_pair(curState,n);
        nbrs[curState].push_back(n);
        edge_label[edge] = actions[4];
      }
    }

    //lastly pour B into A
    newA = curState.first;
    newB = curState.second;
    if(curState.first < A) {
      while(newA < A && newB > 0) {
      newA++;
      newB--;
      }
      n = make_pair(newA,newB);

      if(n != curState) {
        pair<state,state> edge = make_pair(curState,n);
        nbrs[curState].push_back(n);
        edge_label[edge] = actions[5];
      }
    }

    if(curState.second == B){
      curState = make_pair(curState.first + 1,0);
    }
    else{
      curState = make_pair(curState.first, curState.second + 1);
    }
  }
}

