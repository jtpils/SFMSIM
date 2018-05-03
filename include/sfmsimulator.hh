#ifndef __SFMSIMULATOR_HH__
#define __SFMSIMULATOR_HH__

#include "cameramodel.hh"
#include "framesimulator.hh"
#include "global.hh"
#include "pointclassifier.hh"
#include "points.hh"

#include <deque>
#include <fstream>
#include <iostream>
#include <memory>

namespace sfmsimulator {

struct Sfmconfig {
  Sfmconfig() = default;
  Sfmconfig(cameramodel::Cameramodel camera) : cameramodel(camera) {}

  pointclassifier::Pointclassifier_type type_pointclassifier;
  cameramodel::Cameramodel cameramodel;

  // 0 camera_poses
  // 1 static_3d_landmarks
  // 2 dynamic_3d_landmarks
  // 3 output_weights
  std::vector<std::string> filepaths;
};

class Sfmsimulator {
public:
  Sfmsimulator(Sfmconfig config);
  Sfmsimulator(std::string config_file_path);

  void run();
  void doSteps(const size_t steps);
  void step();
  inline void enableVisualization() { _visualize = true; }
  inline void disableVisualization() { _visualize = false; }

  ~Sfmsimulator() {
    _fstream_output_weights->close();
    _fstream_output_camera_trajectory->close();
    std::cout << "\n\n\n\n";
  }

private:
  void output(const Sfmreconstruction &reconstruct) const;
  void addNoise(std::shared_ptr<points::Points3d> points,
                std::vector<vec6_t> cameraposes, precision_t amount);

  // model configuration
  const Sfmconfig _config;
  std::unique_ptr<pointclassifier::Pointclassifier> _pointclassifier;
  const cameramodel::Cameramodel _cameramodel;
  framesimulator::Framesimulator _framesimulator;

  // pointweights
  array_t _weights;

  // scene window
  std::deque<std::shared_ptr<points::Points2d>> _scene_window_image;
  std::deque<std::shared_ptr<points::Points3d>> _scene_window_world;
  std::deque<std::shared_ptr<mat44_t>> _scene_window_cameraposes_mat;
  std::deque<vec6_t> _scene_window_cameraposes;

  // simulation variables
  size_t _step = 0;
  bool _visualize = 0;

  // outputstream
  std::string _file_output = "";
  std::unique_ptr<std::ofstream> _fstream_output_weights;
  std::unique_ptr<std::ofstream> _fstream_output_camera_trajectory;
};
} // namespace sfmsimulator

#endif /* end of include guard: __SFMSIMULATOR_HH__ */
