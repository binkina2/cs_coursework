#include "seam_carver.hpp"

// implement the rest of SeamCarver's functions here

const ImagePPM& SeamCarver::GetImage() const {
  return image_;
}

int SeamCarver::GetHeight() const {
  return height_;
}

int SeamCarver::GetWidth() const {
  return width_;
}

int SeamCarver::GetEnergy(int row, int col) const { //passing coordinates to a single pixel 

  int prev_row = row - 1;
  if(prev_row < 0) {
    prev_row =  height_-1;
  }

  int next_row = row + 1;
  if(next_row > height_ - 1) {
    next_row = 0;
  }

  int b_row = image_.GetPixel(prev_row,col).GetBlue() - image_.GetPixel(next_row, col).GetBlue() ;
  int g_row = image_.GetPixel(prev_row,col).GetGreen() - image_.GetPixel(next_row, col).GetGreen();
  int r_row = image_.GetPixel(prev_row,col).GetRed() - image_.GetPixel(next_row, col).GetRed();
  int delta_row = (r_row * r_row) + (g_row * g_row) + (b_row * b_row);

  int prev_col = col - 1;
  if (prev_col < 0) {
    prev_col = width_ - 1;
  }

  int next_col = col + 1;
  if (next_col > width_ - 1) {
    next_col = 0;
  }

  int b_col = image_.GetPixel(row, prev_col).GetBlue() - image_.GetPixel(row, next_col).GetBlue() ;
  int g_col = image_.GetPixel(row, prev_col).GetGreen() - image_.GetPixel(row, next_col).GetGreen();
  int r_col = image_.GetPixel(row, prev_col).GetRed() - image_.GetPixel(row, next_col).GetRed();
  int delta_col = (r_col * r_col) + (g_col * g_col) + (b_col * b_col);

//  std::cout << "computing energy(row=" << row << ",col=" << col << "):\n" << 
//    "\tb_row=" << b_row << " g_row=" << g_row << " r_row=" << r_row << '\n' <<
//    "\tb_col=" << b_col << " g_col=" << g_col << " r_col=" << r_col << '\n' <<
//    "\tdelta_row=" << delta_row << " delta_col=" << delta_col << std::endl;

  return (delta_row + delta_col);
}

void Print(int** matrix, int height, int width)
{
  for(int i=0; i<height; i++) {
    for(int j=0; j<width; j++) {
      std::cout << matrix[i][j] <<  "\t";
    }
    std::cout << std::endl;
  }
}

int* SeamCarver::GetVerticalSeam() const {
  const int kMaxInt = 999999;

  int** energy_matrix = new int*[ GetHeight() ];
  for(int i = 0; i < GetHeight(); i++) { energy_matrix[i] = new int[ GetWidth() ]; }
  for(int i = 0; i < GetHeight(); i++) { for( int j=0; j<GetWidth(); j++) { energy_matrix[i][j] = GetEnergy(i, j); } }
  
  int** values = new int*[ GetHeight() ];
  for(int i = 0; i < GetHeight(); i++) { values[i] = new int[ GetWidth() ];}

  for(int i = 0; i< GetWidth(); ++i){ values[GetHeight()-1][i] = energy_matrix[GetHeight()-1][i];}
  for(int row = GetHeight()-2; row>=0; row--) {
    for(int i = 0; i< GetWidth(); ++i){
      int left = kMaxInt; if(i > 0) { left = values[row + 1][i-1]; }
      int down = values[row + 1][i];
      int right = kMaxInt; if(i < GetWidth() - 1) {right = values[row + 1][i+1];}
      int min = std::min(left, std::min(down, right));
      values[row][i] = energy_matrix[row][i] + min;
    }
  }
  int best_col = 0;  int min_val = kMaxInt;
  for(int i=0; i< GetWidth(); i++) { if(values[0][i] < min_val) { min_val = values[0][i]; best_col = i;}}

  int* h_seam = new int[GetHeight()];
  for(int i=0; i< GetHeight(); i++) {
    h_seam[i] = best_col;
    if(i == GetHeight()-1) { continue; }
    int left = kMaxInt; if(best_col > 0) { left = values[i + 1][best_col - 1]; }
    int down = values[i + 1][best_col];
    int right = kMaxInt; if(best_col < GetWidth()-1) { right = values[i + 1][best_col + 1]; }

    if(down <= left && down <= right) { }
    else if(left <= right) { best_col--; }
    else { best_col++; }
  }  
  for(int i = 0; i < GetHeight(); ++i) { delete [] energy_matrix[i]; } delete [] energy_matrix;
  for(int i = 0; i < GetHeight(); ++i) { delete [] values[i];} delete [] values;
  return h_seam;
}

int* SeamCarver::GetHorizontalSeam() const {
  const int kMaxInt = 999999;
  int** energy_matrix = new int*[ GetHeight() ];
  for(int i=0; i< GetHeight(); i++) { energy_matrix[i] = new int[ GetWidth() ];}
  for(int i = 0; i<GetHeight(); i++) { for( int j=0; j<GetWidth(); j++) { energy_matrix[i][j] = GetEnergy(i, j);}}

  int** values = new int*[ GetHeight() ];
  for(int i=0; i< GetHeight(); i++) {values[i] = new int[ GetWidth() ];}
  for(int i = 0; i< GetHeight(); ++i){ values[i][GetWidth()-1] = energy_matrix[i][GetWidth()-1]; }
  for(int col = GetWidth()-2; col>=0; col--) {
    for(int row = 0; row < GetHeight(); ++row){
      int up = kMaxInt; if(row > 0) { up = values[row - 1][col+1]; }
      int right = values[row][col + 1];
      int down = kMaxInt; if(row < GetHeight() - 1) {down = values[row + 1][col+1];}
      int min = std::min(up, std::min(right, down));
      values[row][col] = energy_matrix[row][col] + min;
    }
  }
  int best_row = 0; int min_val = kMaxInt;
  for(int i=0; i< GetHeight(); i++) { if(values[i][0] < min_val) { min_val = values[i][0]; best_row = i; }  }

  int* h_seam = new int[GetWidth()];
  for(int col=0; col< GetWidth(); col++) {
    h_seam[col] = best_row;
    if(col == GetWidth()-1) { continue; }

    int up = kMaxInt; if(best_row > 0) { up = values[best_row - 1][col + 1];}
    int right = values[best_row][col + 1];
    int down = kMaxInt; if(best_row < GetHeight()-1) { down = values[best_row + 1][col + 1]; }

    if(right <= up && right <= down) { }
    else if(up <= down) { best_row--; }    
    else { best_row++; }
  }  

  for(int i = 0; i < GetHeight(); ++i) { delete [] energy_matrix[i]; } delete [] energy_matrix;
  for(int i = 0; i < GetHeight(); ++i) { delete [] values[i];} delete [] values;
  return h_seam;
}

void SeamCarver::RemoveVerticalSeam() {
  int* vertical_seam = GetVerticalSeam();

  std::cout << "*** REMOVING VERTICAL SEAM ***:";

  for(int i=0; i< image_.GetHeight(); i++) {
    std::cout << vertical_seam[i] << ' ';
  }
  std::cout << std::endl;

  image_.RemoveVerticalSeam(vertical_seam);
  width_--;

  delete []vertical_seam;
}


void SeamCarver::RemoveHorizontalSeam() {
  int* horizontal_seam = GetHorizontalSeam();

  std::cout << "*** REMOVING HORIZONTAL SEAM ***:";

  for(int i=0; i< image_.GetWidth(); i++) {
    std::cout << horizontal_seam[i] << ' ';
  }
  std::cout << std::endl;

  image_.RemoveHorizontalSeam(horizontal_seam);
  height_--;

  delete[] horizontal_seam;
}

// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}

