#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

struct Node {
  char data = '\0';         // NOLINT
  Node* next = nullptr;     // NOLINT
  Node(char data): data(data) { count++; isDeleted = false; std::cout << "adding " << data << ' ' << this  << " count=" << count << std::endl; }
  Node(char data, Node* next): data(data), next(next) { count++; isDeleted = false; std::cout << "adding " << data << ' ' << this << " count=" << count << std::endl; }

  std::string GetData() { 
    if(isDeleted){
      std::cout << " ***** ACCESSING DELETED ******" << data << '\n';
    }
    std::string result;
    result += data;
    return result;
  }
  ~Node() { 
    count--; 
    if(isDeleted){
      std::cout << "****** DOUBLE DELETING " << data << " ******\n";
    } 

    std::cout << "deleting " << this << " " << data << "->" << next << " count=" << count << std::endl; 
    
    data = '*';
    isDeleted = true; 
  }

  bool isDeleted;

  inline static int count = 0;
};

#endif