#include "elevation_dataset.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <limits>

void ElevationDataset::Init(const std::string& filename)
{
    min_ele_ = std::numeric_limits<int>::max();
    max_ele_ = std::numeric_limits<int>::min();

    std::vector<int> ints_from_file;

    // read from file into vector
    std::ifstream ifs{filename}; // creates a file reader than can read this specific file. 
    if(ifs.fail()) {
        throw std::runtime_error("bad input file");
    }

    int next_int = -1;
    while( ifs >> next_int ) {
        ints_from_file.push_back(next_int);
        
        if( next_int > max_ele_) {
            max_ele_ = next_int;
        }
        if( next_int < min_ele_) {
            min_ele_ = next_int;
        }
    }
    ifs.close();
    // verify the number of ints that we will put into data
    if (ints_from_file.size() != (width_ * height_)) {
        throw std::runtime_error("bad ElevationDataset dimensions");
    }
    // create space for all entries
    data_.resize( height_ );
    for(std::vector<int>& v : data_) {
        v.resize(width_);
    }
    // populate the 2d matrix
    for (size_t i = 0; i < ints_from_file.size() ; ++i) {
        size_t row = i/width_;
        size_t col = i % width_;
        data_[row][col] = ints_from_file[i]; 
    }
}

//constructor
ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height) : 
    width_(width), height_(height), max_ele_(std::numeric_limits<int>::min()), min_ele_(std::numeric_limits<int>::max()) 
    
{
    Init(filename);
}

  size_t ElevationDataset::Width() const {
      return width_;
  }
  size_t ElevationDataset::Height() const {
      return height_;
  }
  int ElevationDataset::MaxEle() const {
      return max_ele_;
  }
  int ElevationDataset::MinEle() const {
      return min_ele_;
  }
  int ElevationDataset::DatumAt(size_t row, size_t col) const {
      return data_[row][col];
  }
  const std::vector<std::vector<int> >& ElevationDataset::GetData() const {
    return data_;
  }