#include "path_image.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <limits>

void PathImage::Init(const GrayscaleImage &image) {
    width_ = image.Width();
    height_ = image.Height();
    
    //copy colors from image into path_image
    
    path_image_.resize( height_ );
    for(std::vector<Color>& v : path_image_) {
        v.resize(width_);
    }

     // populate the 2d matrix
    for (size_t row = 0; row < height_; ++row) {
        for (size_t col = 0; col < width_; ++col) {
            path_image_[row][col] = image.ColorAt(row,col);

        }
    }
}

void PathImage::PopulatePaths(const ElevationDataset &dataset) {
    // for every starting point
    for (size_t row = 0; row < height_; ++row) {
        size_t current_row = row;
        // create a path for this particular starting position
        Path my_path(width_, row); // length, starting_row
        for (size_t current_col = 0; current_col< width_; ++current_col) {
            // record current position
            my_path.SetLoc( current_col, current_row );
            if (current_col == width_ - 1) {
                continue;
            }
            // decide on next step
            int elevation_current = dataset.DatumAt( current_row,  current_col );
            int diff_north = std::numeric_limits<int>::max();
            if(current_row != 0) {
                diff_north = abs( dataset.DatumAt( current_row - 1, current_col + 1) - elevation_current);
            }
            int diff_east = abs( dataset.DatumAt( current_row , current_col + 1) - elevation_current);
            int diff_south = std::numeric_limits<int>::max();
            if(current_row < height_ - 1) {
                diff_south = abs( dataset.DatumAt( current_row + 1 , current_col + 1) - elevation_current);
            }
            // is north the winner
            if( diff_north < diff_east && diff_north < diff_south ) {
                --current_row;
                my_path.IncEleChange( diff_north );
            }
            // is sourth the winner
            else if(diff_south <= diff_north && diff_south < diff_east) {
                ++current_row;
                my_path.IncEleChange( diff_south );
            }
            //east is the winner 
            else {  //current_row stays the same
                my_path.IncEleChange( diff_east );
            }
        }
        paths_.push_back(my_path);
    }
}
  
  PathImage::PathImage(const GrayscaleImage &image, const ElevationDataset &dataset) {
    Init( image );
    PopulatePaths(dataset);
    size_t shortest_path = std::numeric_limits<size_t>::max();
    size_t shortest_path_number = 0;

    for( size_t i=0; i<paths_.size(); ++i) {
        Path& path = paths_[i];

        if (path.EleChange() < shortest_path) {
            shortest_path = path.EleChange();
            shortest_path_number = i;
        }
    }
    // color up all paths
    const int kG = 31;    const int kG1 = 253;    const int kG2 = 13;
    const int kR = 252; const int kR1 = 25; const int kR2 = 63;
    Color green(kG,kG1,kG2);
    Color red(kR,kR1,kR2);

    // print all paths computed color into image_  
    for (size_t path_number=0; path_number < paths_.size(); ++path_number) {
        // prints one individual paths, one after another
        std::vector<size_t> one_path = paths_[path_number].GetPath();        
        for(size_t col = 0; col < one_path.size(); ++col) {
            if(path_number == shortest_path_number) {
                // path_image_[one_path[col]][col] = green;
            } else {
                path_image_[one_path[col]][col] = red;
            }
        }
    }
    // prints winner
    std::vector<size_t> green_path = paths_[shortest_path_number].GetPath();        
    for(size_t col = 0; col < green_path.size(); ++col) {
        path_image_[green_path[col]][col] = green;
    }    
  }


  size_t  PathImage::Width() const {
      return width_;
  }

  size_t  PathImage::Height() const {
      return height_;
  }

  unsigned int  PathImage::MaxColorValue() const {
      return kMaxColorValue;
  }

  const std::vector<Path>&  PathImage::Paths() const {
      return paths_;
  }

  const std::vector<std::vector<Color> >&  PathImage::GetPathImage() const {
      return path_image_;
  }

  void  PathImage::ToPpm(const std::string& name) const {
    std::ofstream myfile;
    myfile.open( name );
    myfile 
        << "P3" << std::endl 
        << width_ << " " << height_ << std::endl
        << kMaxColorValue << std::endl;

    
    for (size_t row = 0; row < height_; ++row) {
        for (size_t col = 0; col < width_; ++col) {
            Color current_color = path_image_[row][col];
            myfile << current_color.Red() << " " << current_color.Green() << " " << current_color.Blue() << " ";
        }
        myfile << std::endl;
    }

  }