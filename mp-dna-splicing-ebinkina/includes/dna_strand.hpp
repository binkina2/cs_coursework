#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand();
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();

  Node* GetHead();
  Node* GetTail();
  void Abandon();


  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);


  void PushBack(char value);
  bool MatchesAt(Node* start_point, const char* pattern, size_t size) const;
  Node* FindLast(const char* pattern, bool& found_at_head) const;
  void Replace (const char* pattern, size_t pattern_length, DNAstrand& to_splice_in);
  void SetTail();

  void PrintHeader();
  void Print(const char* msg);



private:
  size_t GetArrayLength(const char* str) const;

  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif