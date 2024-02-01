#ifndef SCHEDULE_HPP
#define SCHEDULE_HPP

#include <set>
#include <string>
#include <vector>
#include "timeslot.hpp"

class Schedule {
public:
  Schedule() = default;
  
  void MarkBusy(TimeSlot time);
  void MarkAvailable(TimeSlot time);
  bool IsAvailable(TimeSlot time) const;
private:
  std::set<TimeSlot> times_;
};

#endif