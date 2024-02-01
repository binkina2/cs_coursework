#include <stdexcept>
#include "dna_strand.hpp"

DNAstrand::DNAstrand() {
  head_ = nullptr; 
  tail_ = nullptr;
}

DNAstrand::~DNAstrand() {
  Node* temp = head_;
  while(head_ != nullptr) {
    temp = head_;
    head_=head_->next;
//    std::cout << "delete mem " << temp << std::endl;
    delete temp;
    temp = nullptr;
  }

  head_ = tail_ = nullptr;
}

//helper functions 


#include <iostream>
void DNAstrand::PrintHeader() {
  std::cout << "head = " << (head_ ?  head_->GetData() : "?") << ' ' << head_ << 
    " tail = " << (tail_ ?  tail_->GetData() : "?") << ' ' << tail_  << "\n";
}

void DNAstrand::Print(const char* msg) {

  std::cout << msg << "\nhead = " << (head_ ?  head_->GetData() : "?") << ' ' << head_ << 
    " tail = " << (tail_ ?  tail_->GetData() : "?") << ' ' << tail_  << " [\n";

  Node* current_node = head_;
  while (current_node != nullptr) {
    std::cout << ' ' << current_node->GetData() << ' ' << current_node << "->" << current_node->next;
    if(current_node->next != nullptr) {
      std::cout << ',';
    }
    std::cout << std::endl;
    current_node = current_node->next;
  }
  std::cout << "]\n";
}


void DNAstrand::PushBack(char value) {
  if (nullptr == head_) { //empty list condition
      head_ = tail_ = new Node(value);
      //std::cout << "added " << head_ << std::endl;
  } else { //existing list condition
    Node* temp = new Node(value);
    //std::cout << "added " << temp << std::endl;
    tail_->next = temp;
    tail_ = temp;
    tail_->next = nullptr;
  }
}

size_t DNAstrand::GetArrayLength(const char* str) const {
  size_t pattern_size=0;
  const char* a = str;
  while(*a != '\0') {
    pattern_size++;
    a++;
  }
  return pattern_size;
}

bool DNAstrand::MatchesAt(Node* start_point, const char* pattern, size_t size) const {

  size_t matches = 0;
  Node* current = start_point;
  for(size_t i=0; i<size && current != nullptr; ++i) {
    if(pattern[i] != current->data) {
      return false;
    } else {
      matches++;
    }
    current = current->next;
  }
  current = nullptr;
  return size == matches;
}

Node* DNAstrand::FindLast(const char* pattern, bool& found_at_head) const { // find the element before the word starts

  found_at_head = false;
  if(head_ == nullptr) {
    return nullptr;
  }

  size_t pattern_length = GetArrayLength(pattern);

  found_at_head = MatchesAt( head_, pattern, pattern_length);

  Node* prev = head_;
  Node* current = head_->next;
  Node* last_found_at = nullptr;
  while( current != tail_->next ) {
    if( MatchesAt( current, pattern, pattern_length ) ) {
      last_found_at = prev;
      found_at_head = false;
    } else {
      //std::cout << "not found" << std::endl;
    }

    current = current->next;
    prev = prev->next;
  }

  return last_found_at;
}

Node* DNAstrand::GetHead() {
  return head_;
}

Node* DNAstrand::GetTail() {
  return tail_;
}

void DNAstrand::Abandon() {
  //std::cout << "abandoning ";
  //Print();
  head_ = tail_ = nullptr;
}

void DNAstrand::Replace (const char* pattern, size_t pattern_length, DNAstrand& to_splice_in) {
  bool found_at_head = false;
  Node* pos = FindLast(pattern, found_at_head);
  if ( !found_at_head && nullptr == pos) {  to_splice_in.~DNAstrand();
    throw std::runtime_error("original list is empty");
  }
  if( found_at_head ) {
    for(size_t i = 0; i < pattern_length; i++) {
      Node* to_delete = head_;
      head_ = head_->next;
      if(to_delete == tail_) {
        tail_ = head_;
      }
      delete to_delete;
      to_delete = nullptr;
    }
    Node* new_head = to_splice_in.GetHead();
    Node* splice_tail = to_splice_in.GetTail();
    splice_tail->next = head_;
    head_ = new_head;
    to_splice_in.Abandon();
  } 
  else // last found is not at head
  {
    for(size_t i = 0; i < pattern_length; i++) {
      Node* to_delete = pos->next;
      pos->next = pos->next->next;
      if(to_delete == tail_) {
        tail_ = pos;
      }
      delete to_delete;
      to_delete = nullptr;
    }
    if(pos == tail_) {
      tail_ = to_splice_in.GetTail();
    }
    to_splice_in.GetTail()->next = pos->next;
    pos->next = to_splice_in.GetHead();
    to_splice_in.Abandon();
  }
}

// pattern --> thing to replace
// to_splice_in --> replacement text
// SpliceIn( "bc", "pqrstuv" );
void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {

  size_t pattern_length = GetArrayLength(pattern);

  if(pattern_length == 0) {
    to_splice_in.~DNAstrand();
    this->~DNAstrand();
    return;
  }

  if(to_splice_in.GetHead() == nullptr) {
    to_splice_in.~DNAstrand();
    this->~DNAstrand();
    return;
  }

  if(to_splice_in.GetHead() == this->GetHead()) {
    to_splice_in.~DNAstrand();
    this->~DNAstrand();
    return;
  }

  Replace( pattern, pattern_length, to_splice_in);
}

