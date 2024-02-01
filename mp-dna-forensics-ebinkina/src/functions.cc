#include "functions.hpp"
using namespace std;

bool MatchesOnePerson(std::map<string,int>& finalresult, OnePerson& person) {
  for (std::map<std::string,int>::iterator i = finalresult.begin(), end = finalresult.end(); i != end ; ++i) { 
    if (i->second != person.strands[i->first]) {
        return false;
    }
  }
  return true;
}

void ParseHeader(std::string line, std::map<int, std::string>& mapping, std::vector<std::string>& list_of_strands) {
  std::vector<std::string> header = utilities::GetSubstrs(line, ',');
  int counter = 0;
  for (std::string s : header) {
    if (counter != 0) {
      mapping[counter] = s; 
      list_of_strands.push_back(s);
    }
    counter++;
  }  
}

void AddOnePerson(std::string line, std::map<int, std::string>& mapping, std::vector<OnePerson>& people ) {
  std::vector<string> one_person = utilities::GetSubstrs(line, ',');
  OnePerson me; 
  int counter = 0;
  for (std::string s : one_person) {
    if (counter == 0) { 
      me.name = s;
    } else { 
      me.strands[mapping[counter]] = std::stoi(s); 
    }
    counter++;
  } 
  people.push_back(me);
}

int StrandCounter(std::string input, std::string strand) {
    int count = 0; 
    int max_count = 0;
    size_t pos = 0;
    size_t substr_length = strand.length();
    
    bool done = false;
    while(!done) {
        size_t prev_pos = pos;
        pos = input.find( strand, pos); 
        
        if(pos == string::npos) { 
            done = true;
        } else {
            if (pos == prev_pos) {
                ++count;
                if (count > max_count) {
                    max_count = count;
                }
            }else {
                count = 1;
                if (count > max_count) {
                    max_count = 1;
                }
            }
            pos += substr_length;  
        }
    }
    return max_count;
}

map<string,int> GetStrands(string dna, vector<string> list_of_strands) {
    
    map<string,int> result;
    
    for (string s : list_of_strands) {
        result[s] = StrandCounter(dna,s);
    }
    
    return result;
}