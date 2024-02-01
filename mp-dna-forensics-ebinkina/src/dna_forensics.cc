#include <iostream>
#include <cctype> 
#include <cassert> 
#include <fstream> 
#include <map> 
#include <string> 
#include <vector> 


#include "functions.hpp"
#include "utilities.hpp"
using namespace std;




int main(int argc, char* argv[]) {
  if (argc != 3) {std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]" << std::endl; return 1; } 
  
  string file_name(argv[1]); string dna(argv[2]);
  vector<OnePerson> people;
  map<int, string> mapping;
  vector<string> list_of_strands;
  std::ifstream ifs{file_name};
  bool readheader = false;
  for(std::string line; std::getline(ifs, line); line = "") {
    if (!readheader) {
      readheader = true;
      ParseHeader( line, mapping, list_of_strands);
      continue;
    } else {
        AddOnePerson(line, mapping, people); 
    }
  }

  std::map<string,int> finalresult = GetStrands( dna, list_of_strands);
  
  for (size_t i = 0; i < people.size(); ++i) { 
    if (MatchesOnePerson(finalresult, people[i])) {
      cout << people[i].name << endl;
      return 0;
    }
  }
  cout << "No match" << endl;
  
  return 0;
}