#ifndef POOL_HPP
#define POOL_HPP

#include <vector> // std::vector

/**
 * @class IPool
 * @brief The IPool class is an interface for the Pool class.
 */
class IPool {
public:
    /**
     * @brief Destroy the IPool object
     */
    virtual ~IPool() = default;

    /**
     * @brief Clear the pool
     */
    virtual void clear() = 0; // Add this pure virtual function
};

/**
 * @class Pool
 * @brief The Pool class is a template class for the pool of components.
 */
template <typename TComponent>
class Pool: public IPool {
private:

    std::vector<TComponent> data; // data

public:
    /**
     * @brief Construct a new Pool object
     * @param size The size of the pool
     */
    Pool(int size= 1000) {
        data.resize(size);
    }

    /**
     * @brief Destroy the Pool object
     */
    virtual ~Pool() = default;

    /**
     * @brief Check if the pool is empty
     * @return true if the pool is empty, false otherwise
     */
    bool is_empty() const {
        return data.empty();
    }

    /**
     * @brief Get the size of the pool
     * @return int The size of the pool
     */
    int get_size() {
        return data.size();
    }

    /**
     * @brief Resize the pool
     * @param size The size of the pool
     */
    void resize(int size) {
        data.resize(size);
    }

    /**
     * @brief Clear the pool
     */
    void clear() {
        data.clear();
    }

    /**
     * @brief Add a component to the pool
     * @param component The component to be added
     */
    void add_component(const TComponent& component) {
        data.push_back(component);
    }

    /**
     * @brief Set a component at an index
     * @param index The index
     * @param component The component
     */
    void set(unsigned int index, TComponent component) {
        data[index] = component;
    }

    /**
     * @brief Get a component at an index
     * @param index The index
     * @return TComponent The component
     */
    TComponent& get(unsigned int index) {
        return data[index];
    }

    /**
     * @brief Get a component at an index
     * @param index The index
     * @return TComponent The component
     */
    TComponent& operator[](unsigned int index) {
        return data[index];
    }

};    

#endif // POOL_HPP