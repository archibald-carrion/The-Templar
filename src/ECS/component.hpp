#ifndef COMPONENT_HPP
#define COMPONENT_HPP

/**
 * @class IComponent
 * @brief The IComponent class is an interface for the Component class.
 */
struct IComponent {
protected:
    static int next_id; // next id for the component
};

/**
 * @class Component
 * @brief The Component class is a template class for the components of an entity.
 */
template<typename TComponent>
class Component : public IComponent {
public:
    /**
     * @brief Get the id of the component
     * @return int The id of the component
     */
    static int get_id() {
        static int id = next_id++;
        return id;
    }
};


#endif // COMPONENT_HPP