#ifndef TAG_COMPONENT_HPP
#define TAG_COMPONENT_HPP

#include <string> // std::string

/**
 * @struct TagComponent
 * @brief The TagComponent struct represents a tag for an entity.
 */
struct TagComponent {
   std::string tag; /**< The tag for the entity. */

   /**
    * @brief Construct a new TagComponent object
    * @param tag The tag for the entity
    */
   TagComponent(const std::string& tag = "") {
    this->tag = tag;
   }
};

#endif // TAG_COMPONENT_HPP