#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

vector<string> V; //words from wordlist05.txt
//Global variables for bfs distance, bfs predecessor, and neighboring nodes
//Should be unordered_map type
unordered_map<string, bool> vis;
unordered_map<string, int> dist;
unordered_map<string, vector<string>> nb;
unordered_map<string, string> pre;
int helper1(string, string, vector<string>&);
void helper2();



void wordLadder(string s, string t, int &steps, vector<string> &p){
  helper2();
  queue<string> g;
  g.push(s);
  vis[s] = true;
  dist[s] = 0;

  while (!g.empty()) {
    string c = g.front();
    g.pop();
    for (string n : nb[c]){
      if (!vis[n]){
        pre[n] = c;
        dist[n] = 1 + dist[c];
        vis[n] = true;
        g.push(n);
      }
    }
  }
  steps = helper1(s, t, p);
}

int helper1(string s, string e, vector<string> &p){

  if(pre.find(e) == pre.end()){
    return 0;
  }
  if(s.compare(e) != 0) {
    int a = 1 + helper1(s, pre[e], p);
    p.push_back(e);
    return a;
  }
  else {
    p.push_back(e);
    return 0;
  }

}

void helper2(void){
  ifstream input ("wordlist05.txt");
  string cur;

  while(input >> cur){
  V.push_back(cur);
  }

  for(auto w : V) {
    for(int i = 0; i < w.length(); i++) {
      for(char j = 'a'; j <= 'z'; j++) {
        if(j == w.at(i)){
          continue;
        }
      string here = w;
      here.at(i) = j;
      nb[w].push_back(here);
      }
    }
  }
}