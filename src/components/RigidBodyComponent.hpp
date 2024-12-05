#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP

#include <glm/glm.hpp> // GLM math library, used for vec2

/**
 * @struct RigidBodyComponent
 * @brief The RigidBodyComponent struct represents a rigid body component for an entity.
 */
struct RigidBodyComponent {
  bool is_dynamic; // Whether the object is dynamic or not
  bool is_solid; // Whether the object is solid or not
  bool default_movement { false };
  std::optional<Entity> father;

  glm::vec2 sum_forces = glm::vec2(0, 0); // Sum of all forces acting on the object
  glm::vec2 velocity = glm::vec2(0, 0); // Velocity of the object
  glm::vec2 acceleration = glm::vec2(0, 0); // Acceleration of the object
  glm::vec2 velocity_buffer = glm::vec2(0, 0);

  float mass; // Mass of the object
  float inverse_mass; // Inverse mass of the object

/**
 * @brief Construct a new RigidBodyComponent object
 * @param is_dynamic Whether the object is dynamic or not
 * @param is_solid Whether the object is solid or not
 * @param mass The mass of the object
 */
  RigidBodyComponent(bool is_dynamic = false, bool is_solid = false, float mass = 1)
  {
    this->is_dynamic = is_dynamic;
    this->is_solid = is_solid;
    this->mass = mass;
    // if mass is 0 or negative, set inverse_mass to 0
    if (mass <= 0)
    {
      this->inverse_mass = 0;
    }
    else
    {
      this->inverse_mass = 1 / mass;
    }
  };

  void bufferVelocity()
  {
    if (velocity.x != 0)
    {
      velocity_buffer.x = velocity.x;
    }

    if (velocity.y != 0)
    {
      velocity_buffer.y = velocity.y;
    }
  }
};

#endif // RIGIDBODYCOMPONENT_HPP