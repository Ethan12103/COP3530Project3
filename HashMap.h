#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <string>
using namespace std;

class HashMapTable 
{
  private:
  
  unordered_map<string, int> hashMap;
  int bucketSize;

public:

  //input of specific book text whihc would then parse anduse the words as keys and compare their values
void insertDataHM(string text_input);

//attemoting to take into account the # of 'he' 'him' 'she' filler words...
//prints most occurences
void Get_HM_mostCommonWord();

void searchWord(string word);
//finished with program
void Done();

};

void HashMapTable::insertDataHM(string text_input)
{
  for (long int i = 0, len = text_input.size(); i < len; i++)
    {
        // check whether parsing character is punctuation
        if (ispunct(text_input[i]))
        {
            text_input.erase(i-1, 1);
            len = text_input.size();
        }
    }
  istringstream ss(text_input);
	string token;

  //going through the text and adding up all the words based on frequency
	while(std::getline(ss, token, ' '))
	{
      ++hashMap[token];
	}
}

void HashMapTable::Get_HM_mostCommonWord()
{ 
  //Get the max word and output.
  hashMap.erase("");
  cout << "The Top 20 Most Common Words are: " << endl;
  for(int i = 1; i < 21; i++) 
  {
    auto it = hashMap.begin();
    string trueCommon = it->first;
    int trueFrq = it->second;
    while(it != hashMap.end()) 
    {
          if(it->second > trueFrq) 
          {
            trueCommon = it->first;
            trueFrq = it->second;
          }
    it++;
    }  
    cout << i << ". " << trueCommon << " (" << trueFrq << ")" << endl;
    hashMap.erase(trueCommon);
  }
  
  //cout << "Hash Map results of most common word is: " << trueCommon << " with " << trueFrq << " occurences " << endl;

  cout << "Results given by Hash Map" << endl;
}

/*void HashMapTable::Get_HM_top20Words()
{
  vector<pair<string,int>> top20(20);
  
  auto it = hashMap.begin();
  string trueCommon = it->first;
  int trueFrq = it->second;
  
  for(int i = 0; i < 20; i++)
  {  
     
  }

  cout << "The Top 20 Most Common Words are: ";
  for(int j = 0; j < 20 ; j++)
    {
      cout << j+1 << ". " << top20[j].first << " (" << top20[j].second << ")"<< endl;
    }
}*/


void HashMapTable::searchWord(string word)
{
  if(hashMap.find(word) != hashMap.end()) {
    cout << "The word " << "'" << word << "'" << " appears " << hashMap[word] << " times." << endl;
  }
  else {
    cout << "The word " << "'" << word << "'" << " does not exist in this work." << endl;
  }
  cout << "Results given by hash map" << endl;
}

void HashMapTable::Done()
{
  hashMap.clear();
}