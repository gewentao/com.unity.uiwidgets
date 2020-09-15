#include "image_filter.h"

#include "include/effects/SkBlurImageFilter.h"
#include "include/effects/SkImageSource.h"
#include "include/effects/SkPictureImageFilter.h"
#include "matrix.h"

namespace uiwidgets {

fml::RefPtr<ImageFilter> ImageFilter::Create() {
  return fml::MakeRefCounted<ImageFilter>();
}

ImageFilter::ImageFilter() = default;

ImageFilter::~ImageFilter() = default;

void ImageFilter::initImage(CanvasImage* image) {
  filter_ = SkImageSource::Make(image->image());
}

void ImageFilter::initPicture(Picture* picture) {
  filter_ = SkPictureImageFilter::Make(picture->picture());
}

void ImageFilter::initBlur(double sigma_x, double sigma_y) {
  filter_ = SkBlurImageFilter::Make(sigma_x, sigma_y, nullptr, nullptr,
                                    SkBlurImageFilter::kClamp_TileMode);
}

void ImageFilter::initMatrix(const float* matrix4, int filterQuality) {
  filter_ = SkImageFilter::MakeMatrixFilter(
      ToSkMatrix(matrix4), static_cast<SkFilterQuality>(filterQuality),
      nullptr);
}

}  // namespace uiwidgets