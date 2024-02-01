#include "solution.hpp"

Solution::Solution(const std::vector<   std::pair<std::string, std::string>   >& prerequisites) {
    for (size_t i = 0 ; i < prerequisites.size(); ++i) {

        std::pair my_pair = prerequisites[i];
        std::string key = my_pair.first;
        std::string value = my_pair.second;

        // std::string  <-- adj_.key
        // std::list<std::string>   <--- adj_.value
       
        adj_[key].push_back(value);

        nodes_.insert(key);
        nodes_.insert(value);
    }
}

void Solution::Print() const {
	std::cout << "Prereqs: {\n";
	for(std::map<std::string, std::list<std::string>>::const_iterator it = adj_.begin(); it != adj_.end(); ++it) {
		std::cout << it->first << " --> ";

		const std::list<std::string> kMyList = it->second;
		for(std::string r : kMyList) {
			std::cout << "[" << r << "] ";
		}
	    std::cout << "\n";
	}
	std::cout << "}\n";
}

int Solution::Solve(const std::string& start, const std::string& dest) {

    if(nodes_.find(start) == nodes_.end() || nodes_.find(dest) == nodes_.end()) {
        return -1;
    }

    if(start == dest) {
        return 0;
    }

    std::set<std::string> visited;
    std::list<std::string> my_queue;
    std::list<int> levels;

    std::string current = start;
    int current_level = 0;

    my_queue.push_back(current);
    levels.push_back(current_level); // must maintain parallel relationship btw level and queue

    while (! my_queue.empty()) {

        //if found, success
        //std::cout << "comparing " << current << "<>" << dest << std::endl;
        if (current == dest) {
            return levels.front();
        }
        
        // if it hasent been visited, mark it visited
        if( visited.find(current) == visited.end() ) { //find current in the visited
			visited.insert(current);
		}


        // std::cout << "looking for connections from " << current << std::endl;
        auto it = adj_.find(current);

		if( it == adj_.end() ) { 
            // stop looking at this branch
        } else {
            std::list<std::string> connections = it->second;
            for(const std::string& e : connections) { //exploring all possible next steps
                if( visited.find(e) == visited.end() ) { //if not visited yet, then process it 
                    my_queue.push_back(e);
                    levels.push_back(levels.front() + 1);
                    visited.insert(e);
                }
            }
        }

        my_queue.pop_front();
        levels.pop_front();
		current = my_queue.front();
	}
	return -1;
        
    

}

///////////////////////////////////////////////////////////////////////////////
// Provide function definitions (uncomment to use!)                          //
///////////////////////////////////////////////////////////////////////////////

 void Solution::AddVertex(const std::string& vertex) {
   if (VertexInGraph(vertex))
     throw std::runtime_error("vertex already in graph.");
   adj_.insert(std::pair(vertex, std::list<std::string>()));
 }

 std::list<std::string>& Solution::GetAdjacencyList(const std::string& vertex) {
   return adj_.find(vertex)->second;
 }

 bool Solution::VertexInGraph(const std::string vertex) {
   if (adj_.find(vertex) != adj_.end())
     return true;
   else
     return false;
 }

 std::ostream& operator<<(std::ostream& os, const Solution& sol) {
   os << "Contents:" << std::endl;

   for (const auto& pair : sol.adj_) {
     os << "  " << pair.first << ": [ ";

     for (const auto& list_entry : pair.second) {
       os << list_entry << " ";
     }

     os << "]" << std::endl;
   }

   return os;
 }