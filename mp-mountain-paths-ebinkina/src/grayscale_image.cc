#include "grayscale_image.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include <cmath>



//constructer
GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
    width_ = dataset.Width();
    height_ = dataset.Height();
    Init( dataset );
 
}

GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width, size_t height) {
    width_ = width;
    height_ = height;

    const ElevationDataset kElevationObject(filename, width, height);
    Init( kElevationObject );
}

void GrayscaleImage::Init(const ElevationDataset& dataset) {
    width_ = dataset.Width();
    height_ = dataset.Height();
    
    //populate the image vector
    
    // create space for all entries
    image_.resize( height_ );
    for(std::vector<Color>& v : image_) {
        v.resize(width_);
    }
     // populate the 2d matrix
    for (size_t row = 0; row < height_; ++row) {
        for (size_t col = 0; col < width_; ++col) {
          
            // compute color for a given cell from dataset
            int elevation_point = dataset.DatumAt(row,col);
            int min_ele = dataset.MinEle();
            int max_ele = dataset.MaxEle();
        
            int shade_of_gray = 0;
            if (max_ele == min_ele) {
                // shade_of_gray = 0
            } else {
                shade_of_gray = (int)std::round( ((double)elevation_point - (double)min_ele) / ((double)max_ele - (double)min_ele) * (double)kMaxColorValue);
            }
            std::cout << "elevation_point=" << elevation_point << ", min_ele=" << min_ele << ", max_ele=" << max_ele << ", shade=" << shade_of_gray << std::endl;
            
            Color my_color(shade_of_gray,shade_of_gray,shade_of_gray);
            // insert computed color into image_            
            image_[row][col] = my_color;
            

        }
    }

}

size_t GrayscaleImage::Width() const {
    return width_;
}
size_t GrayscaleImage::Height() const {
    return height_;
}
unsigned int GrayscaleImage::MaxColorValue() const {
    return kMaxColorValue;
}
const Color& GrayscaleImage::ColorAt(int row, int col) const {
    if (row >= 0 && col >= 0 && row < (int)height_ && col < (int)width_) {
        return image_[row][col];
    } else {
        throw std::runtime_error("not a valid coordinate");
    }
}

const std::vector<std::vector<Color> >& GrayscaleImage::GetImage() const {
    return image_;
}

void GrayscaleImage::ToPpm( const std::string& name ) const {
    std::ofstream myfile;
    myfile.open( name );
    myfile 
        << "P3" << std::endl 
        << width_ << " " << height_ << std::endl
        << kMaxColorValue << std::endl;

    
    for (size_t row = 0; row < height_; ++row) {
        for (size_t col = 0; col < width_; ++col) {
            Color current_color = image_[row][col];
            myfile << current_color.Red() << " " << current_color.Green() << " " << current_color.Blue() << " ";
        }
        myfile << std::endl;
    }

    
        
     
}