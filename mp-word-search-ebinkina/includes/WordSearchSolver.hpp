#ifndef WORDSEARCHSOLVER_HPP
#define WORDSEARCHSOLVER_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "WordLocation.hpp"

enum class CheckDirection { kHorizontal, kVertical, kLeftDiag, kRightDiag };

class WordSearchSolver {

public:
  WordSearchSolver(const std::vector<std::vector<char>>& puzzle);
  WordLocation FindWord(const std::string& word);
  WordLocation FindWord(const std::string& word, CheckDirection direction);
  bool LocationInBounds(size_t row, size_t col) const;

//private:
  // vertical
  WordLocation VerticalSearch(const std::string& word);
  WordLocation CreateVerticalCharPositions(const std::string& word,size_t start_x, size_t start_y);

  // horizontal 
  WordLocation HorizontalSearch(const std::string& word);
  WordLocation CreateHorizontalCharPositions(const std::string& word, size_t start_x, size_t start_y);

  // left diag
  WordLocation LeftDiagSearch(const std::string& word);
  WordLocation CreateLeftDiagCharPositions(const std::string& word, size_t start_x, size_t start_y);

  // right diag 
  WordLocation RightDiagSearch(const std::string& word);
  WordLocation CreateRightDiagCharPositions(const std::string& word, size_t start_x, size_t start_y);

  private: 
  
  std::vector<std::vector<char>> puzzle_;
  size_t puzzle_height_;
  size_t puzzle_width_;
};



#endif