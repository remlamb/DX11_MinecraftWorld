#pragma once
#include <array>
#include <vector>

struct vec3_t {
  float x;
  float y;
  float z;

  vec3_t operator+(const vec3_t& other) const {
    vec3_t result;
    result.x = this->x + other.x;
    result.y = this->y + other.y;
    result.z = this->z + other.z;
    return result;
  }
};

struct Vertex {
  float position[3];
  float uv[2];
  float color[3];
};

struct vec2_t {
  float x;
  float y;
};

struct GeometryBuilder {
  std::vector<Vertex> vert;
  std::vector<uint32_t> ind;

  void PushQuad(vec2_t a, vec2_t b, vec2_t c, vec2_t d) {
    uint32_t offset = vert.size();
    vert.push_back({{a.x, a.y, 0.0f}, {20.0f, 20.0f}, {1, 0.1f, 0}});
    vert.push_back({{b.x, b.y, 0.0f}, {20.0f, 0.0f}, {1, 0.1f, 0}});
    vert.push_back({{c.x, c.y, 0.0f}, {0.0f, 20.0f}, {1, 0.1f, 0}});
    vert.push_back({{d.x, d.y, 0.0f}, {0.0f, 0.0f}, {1, 0.1f, 0}});

    ind.push_back(0 + offset);
    ind.push_back(1 + offset);
    ind.push_back(2 + offset);
    ind.push_back(0 + offset);
    ind.push_back(2 + offset);
    ind.push_back(3 + offset);
  }

  void PushQuad(vec3_t a, vec3_t b, vec3_t c, vec3_t d, vec3_t color) {
    uint32_t offset = vert.size();
    vert.push_back(
        {{a.x, a.y, a.z}, {0.0f, 0.0f}, {color.x, color.y, color.z}});
    vert.push_back(
        {{b.x, b.y, b.z}, {20.0f, 0.0f}, {color.x, color.y, color.z}});
    vert.push_back(
        {{c.x, c.y, c.z}, {0.0f, 20.0f}, {color.x, color.y, color.z}});
    vert.push_back(
        {{d.x, d.y, d.z}, {20.0f, 20.0f}, {color.x, color.y, color.z}});

    ind.push_back(0 + offset);
    ind.push_back(1 + offset);
    ind.push_back(2 + offset);

    ind.push_back(0 + offset);
    ind.push_back(3 + offset);
    ind.push_back(2 + offset);
  }

  void PushQuad(vec2_t position) {
    uint32_t offset = vert.size();
    vert.push_back({{0.50f + position.x, +0.50f + position.y, 0.0f},
                    {20.0f, 20.0f},
                    {1, 0, 0}});
    vert.push_back({{+0.50f + position.x, -0.50f + position.y, 0.0f},
                    {20.0f, 0.0f},
                    {0, 1, 0}});
    vert.push_back({{-0.50f + position.x, 0.50f + position.y, 0.0f},
                    {0.0f, 20.0f},
                    {0, 0, 1}});
    vert.push_back({{-0.50f + position.x, -0.50f + position.y, 0.0f},
                    {0.0f, 0.0f},
                    {0.5, 0.6, 0.7}});

    ind.push_back(0 + offset);
    ind.push_back(1 + offset);
    ind.push_back(2 + offset);
    ind.push_back(1 + offset);
    ind.push_back(2 + offset);
    ind.push_back(3 + offset);
  }

  void PushCube(vec3_t position) {
    uint32_t offset = vert.size();

    std::vector<Vertex> cubeVertices = {
        {{-0.50f, -0.50f, 0.50f}, {20.0f, 20.0f}, {1, 0, 0}},
        {{+0.50f, -0.50f, 0.50f}, {20.0f, 0.0f}, {0, 1, 0}},
        {{-0.50f, 0.50f, 0.50f}, {0.0f, 20.0f}, {0, 0, 1}},
        {{0.50f, 0.50f, 0.50f}, {0.0f, 0.0f}, {0.5, 0.6, 0.7}},
        {{-0.50f, -0.50f, -0.50f}, {20.0f, 20.0f}, {1, 0, 0}},
        {{+0.50f, -0.50f, -0.50f}, {20.0f, 0.0f}, {0, 1, 0}},
        {{-0.50f, 0.50f, -0.50f}, {0.0f, 20.0f}, {0, 0, 1}},
        {{0.50f, 0.50f, -0.50f}, {0.0f, 0.0f}, {0.5, 0.6, 0.7}},
    };

    for (auto& vertex : cubeVertices) {
      vertex.position[0] += position.x;
      vertex.position[1] += position.y;
      vertex.position[2] += position.z;
      vert.push_back(vertex);
    }

    std::array<uint32_t, 36> cubeIndices = {
        0, 1, 2, 1, 3, 2,  // Front face
        4, 5, 6, 5, 7, 6,  // Back face
        0, 1, 4, 1, 5, 4,  // Left face
        2, 3, 6, 3, 7, 6,  // Right face
        2, 6, 0, 6, 4, 0,  // Top face
        1, 5, 3, 5, 7, 3   // Bottom face
    };

    for (const auto& index : cubeIndices) {
      ind.push_back(index + offset);
    }
  }
};