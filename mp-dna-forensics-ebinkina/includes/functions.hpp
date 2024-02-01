#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <string>
#include <map>
#include <vector>

#include "utilities.hpp"
struct OnePerson {
    std::string name;
    std::map<std::string,int> strands;
};

int StrandCounter(std::string input, std::string strand);

std::map<std::string,int> GetStrands(std::string dna, std::vector<std::string> list_of_strands);

void ParseHeader(std::string line, std::map<int, std::string>& mapping, std::vector<std::string>& list_of_strands);

void AddOnePerson(std::string line, std::map<int, std::string>& mapping, std::vector<OnePerson>& people);

bool MatchesOnePerson(std::map<std::string,int>& finalresult, OnePerson& person);

#endif