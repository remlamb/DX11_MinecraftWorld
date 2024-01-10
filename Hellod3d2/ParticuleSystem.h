#pragma once
#include <vector>

#include "geometryBuilder.h"

class ParticuleSystem {
  std::vector<vec3_t> positions_;
  std::vector<vec3_t> velocities_;

  GeometryBuilder builder_;

 public:
  ParticuleSystem(int max_particules) {
    positions_.reserve(max_particules);
    velocities_.reserve(max_particules);
  }

  void Spawn(vec3_t position) { positions_.push_back(position); }

  void UpdateGeometry() {
    float particule_size = 0.5f;
    for (int i = 0; i < positions_.size(); i++) {
      vec3_t center = positions_[i];
      vec2_t a = vec2_t(center.x + -particule_size, center.x + particule_size);
      vec2_t b = vec2_t(center.x + -particule_size, center.x + -particule_size);
      vec2_t c = vec2_t(center.x + particule_size, center.x + particule_size);
      vec2_t d = vec2_t(center.x + particule_size, center.x + -particule_size);
      builder_.PushQuad(a, b, c, d);
    }
  }
};
