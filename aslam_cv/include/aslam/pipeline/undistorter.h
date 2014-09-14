#ifndef ASLAM_UNDISTORTER_H_
#define ASLAM_UNDISTORTER_H_

#include <aslam/common/macros.h>
#include <opencv2/core/core.hpp>

namespace aslam {

class Camera;

/// \class Undistorter
/// \brief A base class for image undistortion and resizing.
class Undistorter {
public:
  ASLAM_POINTER_TYPEDEFS(Undistorter);
  ASLAM_DISALLOW_EVIL_CONSTRUCTORS(Undistorter);
  Undistorter();

  /// \brief Construct an undistorter pipeline from the input and output cameras
  ///
  /// \param[in] input_camera  The intrinsics associated with the input image.
  /// \param[in] output_camera The intrinsics associated with the output image.
  Undistorter(const std::shared_ptr<Camera>& input_camera,
              const std::shared_ptr<Camera>& output_camera);
  virtual ~Undistorter();

  /// \brief Produce an undistorted image from an input image.
  virtual void processImage(const cv::Mat& input_image, cv::Mat* output_image) const = 0;

  /// \brief Get the input camera that corresponds to the image
  ///        passed in to processImage().
  ///
  /// Because this processor may do things like image undistortion or
  /// rectification, the input and output camera may not be the same.
  virtual const std::shared_ptr<Camera>& getInputCamera() const { return input_camera_; }

  /// \brief Get the output camera that corresponds to the VisualFrame
  ///        data that comes out.
  ///
  /// Because this pipeline may do things like image undistortion or
  /// rectification, the input and output camera may not be the same.
  virtual const std::shared_ptr<Camera>& getOutputCamera() const { return output_camera_; }

protected:
  /// \brief The intrinsics of the raw image.
  std::shared_ptr<Camera> input_camera_;
  /// \brief The intrinsics of the raw image.
  std::shared_ptr<Camera> output_camera_;
};

} // namespace aslam

#endif // ASLAM_UNDISTORTER_H_