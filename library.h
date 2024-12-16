#pragma once

#include <iostream>
#include <functional>

/**
 * @brief A template-based circular queue implementation with a fixed size and callback support.
 *
 * This class implements a circular queue with the capability of storing elements
 * of any type. It efficiently manages the data by reusing space when the queue
 * wraps around. The queue is fixed-size, and its size is defined at the time of
 * construction. Optionally, a callback function can be registered to log events
 * such as enqueue, dequeue, and state changes.
 *
 * @tparam T The type of elements in the queue (e.g., int, std::string).
 */
template <typename T>
class circular_queue {

    T* arr;                                             ///< Array that holds the queue elements
    int front, rear, size;                              ///< Indices for the front, rear, and size of the queue
    std::function<void(const std::string&)> logger;     ///< Optional callback for logging

public:

    /**
     * @brief Constructor that initializes the circular queue with a fixed size.
     *
     * @param n The maximum size of the queue.
     * @param callback An optional callback function to log events.
     */
    explicit circular_queue(int n, std::function<void(const std::string&)> callback = nullptr);

    /**
     * @brief Destructor that deallocates the memory used by the queue.
     */
    ~circular_queue();

    /**
     * @brief Checks if the queue is full.
     * @return True if the queue is full, false otherwise.
     */
    bool is_full() const;

    /**
     * @brief Checks if the queue is empty.
     * @return True if the queue is empty, false otherwise.
     */
    bool is_empty() const;

    /**
     * @brief Adds an element to the rear of the queue.
     * @param value The element to be added to the queue.
     */
    void enqueue(T value);

    /**
     * @brief Removes and returns the front element of the queue.
     * @return The element removed from the front of the queue.
     */
    T dequeue();

    /**
     * @brief Retrieves the front element without removing it.
     * @return The front element of the queue.
     */
    T peek();

    /**
     * @brief Displays the current elements of the queue.
     */
    void display();

    /**
     * @brief Clears the queue by resetting its front and rear pointers.
     */
    void clear();

};
