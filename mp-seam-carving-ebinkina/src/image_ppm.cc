#include "image_ppm.hpp"

// implement the rest of ImagePPM's functions here

// given functions below, DO NOT MODIFY

ImagePPM::ImagePPM(const std::string& path) {
  std::ifstream input_file(path);
  input_file >> *this;
  input_file.close();
}

ImagePPM::ImagePPM(const ImagePPM& source) { *this = source; }

ImagePPM& ImagePPM::operator=(const ImagePPM& source) {
  if (this == &source) {
    return *this;
  }

  Clear();

  height_ = source.height_;
  width_ = source.width_;
  max_color_value_ = source.max_color_value_;

  pixels_ = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    pixels_[row] = new Pixel[width_];

    for (int col = 0; col < width_; col++) {
      pixels_[row][col] = source.pixels_[row][col];
    }
  }

  return *this;
}

void ImagePPM::RemoveVerticalSeam(const int* kVerticalSeam) {
  
  auto *new_pixels = new Pixel*[height_];
  
  for (int row = 0; row < height_; row++) {
    new_pixels[row] = new Pixel[width_ - 1];

    for (int col = 0; col < width_; col++) {
      int column_to_remove = kVerticalSeam[row];
      if( col < column_to_remove) {
        new_pixels[row][col] = pixels_[row][col];
      }
      else if (col > column_to_remove){
        new_pixels[row][col - 1] = pixels_[row][col];
      } else {
        // removed col -- skip copying
      }
    }
  }

  Pixel** to_delete = pixels_;
  pixels_ = new_pixels;

  for (int i = 0; i < height_; i++) {
    delete[] to_delete[i];
  }

  delete[] to_delete;

  --width_;
}

void ImagePPM::RemoveHorizontalSeam(const int* kHorizontalSeam) {
  
  //(void)kHorizontalSeam;

  auto* new_pixels = new Pixel*[height_ - 1];

  for (int row = 0; row < height_; row++) {
    if(row < height_ - 1) {
      new_pixels[row] = new Pixel[width_];
    }


    for (int col = 0; col < width_; col++) {

      int row_to_remove = kHorizontalSeam[col];

      if( row < row_to_remove) {
        new_pixels[row][col] = pixels_[row][col];
      }
      else if (row > row_to_remove){
        new_pixels[row - 1][col] = pixels_[row][col];
      } else {
        // removed col -- skip copying
      }
    } 
  }


  Pixel** to_delete = pixels_;
  pixels_ = new_pixels;

  for (int i = 0; i < height_; i++) {
    delete[] to_delete[i];
  }

  delete[] to_delete;

  --height_;
}


ImagePPM::~ImagePPM() { Clear(); }

void ImagePPM::Clear() {
  for (int i = 0; i < height_; i++) {
    delete[] pixels_[i];
  }

  delete[] pixels_;

  height_ = 0;
  width_ = 0;
  pixels_ = nullptr;
}

std::istream& operator>>(std::istream& is, ImagePPM& image) {
  image.Clear();
  std::string line;
  // ignore magic number line
  getline(is, line);
  // check to see if there's a comment line
  getline(is, line);
  if (line[0] == '#') {
    getline(is, line);
  }
  // parse width and height
  int space = line.find_first_of(' ');
  image.width_ = std::stoi(line.substr(0, space));
  image.height_ = std::stoi(line.substr(space + 1));
  // get max color value
  getline(is, line);
  image.max_color_value_ = std::stoi(line);
  // init and fill in Pixels array
  image.pixels_ = new Pixel*[image.height_];
  for (int i = 0; i < image.height_; i++) {
    image.pixels_[i] = new Pixel[image.width_];
  }
  for (int row = 0; row < image.height_; row++) {
    for (int col = 0; col < image.width_; col++) {
      getline(is, line);
      int red = std::stoi(line);
      getline(is, line);
      int green = std::stoi(line);
      getline(is, line);
      int blue = std::stoi(line);

      Pixel p(red, green, blue);
      image.pixels_[row][col] = p;
    }
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const ImagePPM& image)
{
    os << "P3\n" <<  image.GetWidth() << ' ' << image.GetHeight() << std::endl << image.GetMaxColorValue() << std::endl;
    
    for(int i=0; i< image.GetHeight(); i++) {
      for(int j=0; j< image.GetWidth(); j++) {
        Pixel pixel = image.GetPixel(i, j);
        os << pixel.GetRed() << '\n' << pixel.GetGreen() << '\n' << pixel.GetBlue() << '\n';
      }
    }

    return os;
}

void ImagePPM::Print() const
{    
    for(int i=0; i< GetHeight(); i++) {
      for(int j=0; j< GetWidth(); j++) {
        Pixel pixel = GetPixel(i, j);
        std::cout << '(' << pixel.GetRed() << ',' << pixel.GetGreen() << ',' << pixel.GetBlue() << ')';
      }
      std::cout << std::endl;
    }

}

Pixel ImagePPM::GetPixel (int row, int col) const {
  return pixels_[row][col];
}

int ImagePPM::GetMaxColorValue() const {
  return max_color_value_;
}
