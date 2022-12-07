#include <string>
#include <map>
#include <vector>
using namespace std;

class Graph {
private:
  map<string, int> nodes;
  map<string, vector<pair<string,int>>> edges;
public:
  void insertNode(string word);
  void insertEdge(string from, string to);
  int getPointTo(string word);
  void printMostCommon();
  string getMostCommon(map<string, int> vertices);
  void insertData(string data);
  void clearData();
  void printNodes();
  void findWord(string word);
};

void Graph::insertEdge(string from, string to) {
  edges[from].push_back(make_pair(to,1));
}

void Graph::insertNode(string word) {
  nodes.insert({word,1});
}

int Graph::getPointTo(string word) {
  if(edges.find(word) != edges.end()) {
    return edges.at(word).size();
  }
  else {
    return 1;
  }
}

string Graph::getMostCommon(map<string, int> vertices) {
  auto it = vertices.begin();
  string max = it->first;
  int max_val = it->second;
  while(it != vertices.end()) {
    if(it->second > max_val) {
      max = it->first;
      max_val = it->second;
    }
    it++;
  }
  return max;
}

void Graph::printMostCommon() {
  auto it = nodes.begin();
  while(it != nodes.end()) {
    it->second = getPointTo(it->first);
    it++;
  }
  cout << "The 20 Most Common Words are:" << endl;
  map<string, int> temp = nodes;
  it = temp.begin();
  while(it != temp.end()) {
    if(it->first == "he" || it->first == "she" || it->first == "the" || it->first == "him" || it->first == "her" || it->first == "they" || it->first == "them" || it->first == "or" || it->first == "and") {
      temp.erase(it->first);
    }
    it++;
  }
  for(int i = 1; i <= 20; i++) {
    string most_common = getMostCommon(temp);
    cout << i << ". " << most_common << " (" << temp.at(most_common) << ")"<< endl;
    temp.erase(most_common);
  }
  cout << "Results given by graph" << endl;
}

void Graph::insertData(string data) {
  string word = "";
  vector<string> words;
  for (auto x : data) {
    if (isspace(x)) {
      words.push_back(word);
      word = "";
    }
    else if(ispunct(x)) {
      continue;
    }
    else {
      if(isalpha(x)) {
        word = word + x;
      }
    }
  }
  words.push_back(word);
  for(int i = 0; i < words.size(); i++) {
    if(i != words.size()-1) {
        insertEdge(words.at(i),words.at(i+1));
    }
    insertNode(words.at(i));
  }
  edges.erase(" ");
  nodes.erase(" ");
  edges.erase("  ");
  nodes.erase("  ");
  edges.erase("\t");
  nodes.erase("\t");
  edges.erase("\n");
  nodes.erase("\n");
  nodes.erase("");
}

void Graph::clearData() {
  edges.clear();
  nodes.clear();
}

void Graph::printNodes() {
    auto it = nodes.begin();
    while (it != nodes.end()) {
        cout << it->first << " " << it->second << endl;
        it++;
    }
    cout << "Results given by graph";
}

void Graph::findWord(string word) {
  auto it = nodes.begin();
  while(it != nodes.end()) {
    it->second = getPointTo(it->first);
    it++;
  }
  if(nodes.find(word) != nodes.end()) {
    cout << "The word " << "'" << word << "'" << " appears " << nodes.at(word) << " times." << endl;
  }
  else {
    cout << "The word " << "'" << word << "'" << " does not exist in this work." << endl;
  }
  cout << "Results given by graph" << endl;
}