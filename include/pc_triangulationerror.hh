#ifndef __PC_TRIANGULATIONERROR_HH__
#define __PC_TRIANGULATIONERROR_HH__

#include "pointclassifier.hh"

namespace sfmsimulator::pointclassifier {

class PC_Triangulationerror : public Pointclassifier {
public:
  PC_Triangulationerror(cameramodel::Cameramodel camera)
      : Pointclassifier(camera) {}

  const array_t
  classifynext(const std::shared_ptr<points::Points2d> image_points_frame_1,
               const std::shared_ptr<points::Points2d> image_points_frame_2,
               const std::shared_ptr<points::Points3d> world_points_frame_1,
               const std::shared_ptr<points::Points3d> world_points_frame_2)
      const override;

  void cluster(const points::Points2d image_points,
               const std::vector<bool> type) const override;

private:
};

} // namespace sfmsimulator::pointclassifier

#endif /* end of include guard: __PC_TRIANGULATIONERROR_HH__ */
