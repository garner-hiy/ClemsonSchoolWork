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
#include <bitset>
using namespace std;

// Reflects what each node represents...
// int with each bit == 0 left of river, bit == 1 right of river
typedef int state;

// Bit position representation for wolf/goat/cabbage/me
bool bit(int x, int i) { return (x>>i) & 1; }
const int wolf=0, goat=1, cabbage=2, me=3;

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from curnode)
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

string state_string(state s)
{
  string items[4] = { "wolf", "goat", "cabbage", "you" }, result = "";
  for (int i=0; i<4; i++)
    if (!bit(s, i)) result += items[i] + " ";
  result += " |river| ";
  for (int i=0; i<4; i++)
    if (bit(s, i)) result += items[i] + " ";
  return result;
}

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << state_string(t) << "\n";
  } else {
    cout << "Initial state: " << state_string(s) << "\n";
  }
}

string neighbor_label(int s, int t)
{
  string items[3] = { "wolf", "goat", "cabbage" }, which_cross;
  if (bit(s,me) == bit(t,me)) return "";  // must cross river
  int cross_with = 0;
  for (int i=0; i<3; i++) {
    if (bit(s,i) != bit(t,i) && bit(s,i)==bit(s,me)) { cross_with++; which_cross = items[i]; }
    if (bit(s,i) != bit(t,i) && bit(s,i)!=bit(s,me)) return "";
  }
  if (cross_with > 1) return "";
  if (cross_with == 0) return "Cross alone";
  else return "Cross with " + which_cross;
}

//this is the helper function for the build_graph function that will use
//bitsets to determine the postioning of the targets and determine if the 
//pattern will result in the proper changing of the targets.
bool helper(bitset<4> position){

  if(position[wolf] == position[goat]){
    if(position[me] == position[wolf] && position[me] == position[goat]){
      return true;
    }
  }

  else if(position[goat] == position[cabbage]){
    if(position[me] == position[goat] && position[me] == position[cabbage]){
      return true;
    }
  }

  else{
    return true;
  }

  return false;
}

//This is the main function that will handle building the graph and it will 
//call the helper fucntion to dtermine if there is a vaild move or not.
void build_graph(void){
  //this const is needed for the bitset
  const int thing = 4;

  bitset<thing> curState;
  bitset<thing> term ("1111");

  while(curState != term) {
    for(int i = 0; i < thing; i++) {
      if(curState[me] == curState[i]) {
        //this is the next state that will be used
      bitset<thing> nState = curState;

      nState[me].flip();
      i != me ? nState[i].flip() : false;


      // Check for valid next state using the helper function
        if(helper(nState)) {

          int curr = (int)curState.to_ulong();
          int next = (int)nState.to_ulong();
          nbrs[curr].push_back(next);
          edge_label[make_pair(curr,next)] = neighbor_label(curr,next);

        }
      }
    }
    curState = (int)curState.to_ulong() + 1;
  }
}

