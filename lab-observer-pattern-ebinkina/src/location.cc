#include "news_agent.hpp"

// no need to modify this function
Location::Location(std::string name): name_(name) {}

// no need to modify this function
std::string Location::GetName() const { return name_; }

void Location::AddAgent(NewsAgent* agent) {
  // TODO : implement
}

void Location::RemoveAgent(NewsAgent* agent) {
  // TODO : implement
}

void Location::Event(std::string date,
                     std::string subject,
                     std::string action) {
  // TODO : implement
}
