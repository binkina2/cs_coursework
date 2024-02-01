#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>

#include "color.hpp"
#include "path.hpp"
#include "grayscale_image.hpp"

class PathImage {
public:
  PathImage(const GrayscaleImage &image, const ElevationDataset &dataset);
  size_t Width() const;
  size_t Height() const;
  unsigned int MaxColorValue() const;
  const std::vector<Path>& Paths() const;
  const std::vector<std::vector<Color> >& GetPathImage() const;
  void ToPpm(const std::string& name) const;

private:
 
  void PopulatePaths(const ElevationDataset &dataset);
  void Init(const GrayscaleImage &image);
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  static const int kMaxColorValue = 255;
  std::vector<std::vector<Color>> path_image_;
};

#endif