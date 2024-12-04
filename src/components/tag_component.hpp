#ifndef TAG_COMPONENT_HPP
#define TAG_COMPONENT_HPP

#include <string> // std::string

/**
 * @struct TagComponent
 * @brief The TagComponent struct represents a tag for an entity.
 */
struct TagComponent {
    std::string tag; /**< The tag for the entity. */
    std::string e_class;

   /**
    * @brief Construct a new TagComponent object
    * @param tag The tag for the entity
    */
   explicit TagComponent(const std::string& tag = "", const std::string& e_class = "") :
        tag(tag), e_class(e_class){
   }
};

#endif // TAG_COMPONENT_HPP