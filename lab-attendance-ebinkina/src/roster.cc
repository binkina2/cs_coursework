#include <iostream>

#include "roster.hpp"
#include <memory>

Roster::Roster(const Student& student) {
 RosterEntry r(student, nullptr);

  std::unique_ptr<RosterEntry> new_roster_entry(new RosterEntry(student, nullptr));
  head_ = std::move(new_roster_entry);
}

void Roster::AddStudent(const Student& student) {

  std::unique_ptr<RosterEntry> new_roster_entry(new RosterEntry(student, nullptr));
 
  if(head_ == nullptr) {
    head_ = std::move(new_roster_entry);
    return;
  }

std::cout << "comparing " << student << " with " << head_->student << ", result=" << (student < head_->student) << std::endl;

 if(student < head_->student) {
   new_roster_entry->next = std::move(head_);
   head_ = std::move(new_roster_entry);
   return;
 }

 RosterEntry* temp = head_.get();
 while(temp != nullptr && temp->next != nullptr && temp->next->student < student) {

   std::cout << "comparing " << temp->next->student << " with " << student << ", result=" << (temp->next->student < student) << std::endl;

   if ( temp->next->student < student ) {
    std::cout << "temp=" << temp->student << ", student=" << student << std::endl;
    temp = temp->next.get();
   }
   else {
     break;
   }
 }
 
 new_roster_entry->next = std::move(temp->next);
 temp->next = std::move(new_roster_entry);
}

Roster::Iterator Roster::begin() const { 
  return Iterator(head_.get()); 
}

Roster::Iterator Roster::end() const { 
  return Iterator(); 
}