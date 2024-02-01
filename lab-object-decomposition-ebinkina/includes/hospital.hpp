#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include <set>
#include <string>
#include <vector>
#include "schedule.hpp"
#include "doctor.hpp"
#include "appointment.hpp"


class Hospital {
public:
  Hospital() = default;

  void RemoveAppointment(TimeSlot time, std::string patient);
  void AddAppointment(TimeSlot time, std::string patient);
  Doctor* GetAvailableDoctor(TimeSlot time);
  void AddDoctor(Doctor& d);

private:
std::vector<Doctor*> doctors_;
std::vector<Appointment> appointments_; 
};

#endif