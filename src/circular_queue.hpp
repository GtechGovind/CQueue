#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <stdexcept>
#include <memory>
#include <string>

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
template<typename T>
class circular_queue {

    std::unique_ptr<T[]> arr;                           ///< Array that holds the queue elements
    int front{}, rear{}, size{}, capacity{};            ///< Indices for the front, rear, size, and capacity of the queue
    std::function<void(const std::string &)> logger;    ///< Optional callback for logging events

public:

    /**
     * @brief Constructor that initializes the circular queue with a fixed size.
     *
     * Initializes the queue with the given capacity. Optionally, a callback
     * function can be passed to log various events (enqueue, dequeue, etc.).
     *
     * @param n The maximum size of the queue.
     * @param callback An optional callback function to log events.
     * @throws std::invalid_argument if the given size is less than or equal to 0.
     */
    explicit circular_queue(int n, const std::function<void(const std::string &)> &callback = nullptr)
        : front(-1), rear(-1), capacity(n), logger(callback) {
        if (n <= 0) {
            throw std::invalid_argument("Queue capacity must be greater than 0.");
        }
        arr = std::make_unique<T[]>(n);
    }

    /**
     * @brief Checks if the queue is full.
     *
     * @return True if the queue is full, false otherwise.
     */
    bool is_full() const {
        return size == capacity;
    }

    /**
     * @brief Checks if the queue is empty.
     *
     * @return True if the queue is empty, false otherwise.
     */
    bool is_empty() const {
        return size == 0;
    }

    /**
     * @brief Adds an element to the rear of the queue.
     *
     * If the queue is full, the oldest element (front) will be overwritten.
     * This ensures that the queue never grows beyond its fixed capacity.
     *
     * @param value The element to be added to the queue.
     * @throws std::overflow_error if the queue is full and cannot add the new element.
     */
    void enqueue(T value) {
        if (is_full()) {
            // If the queue is full, overwrite the oldest element (front)
            front = (front + 1) % capacity;
            size--; // Decrease size temporarily to allow inserting at the rear
        }

        if (is_empty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % capacity;
        }

        arr[rear] = value;
        size++;

        if (logger) {
            logger("Enqueued: " + std::to_string(value));
        }
    }

    /**
     * @brief Removes and returns the front element of the queue.
     *
     * If the queue is empty, an underflow error will be thrown.
     *
     * @return The element removed from the front of the queue.
     * @throws std::underflow_error if the queue is empty.
     */
    T dequeue() {
        if (is_empty()) {
            throw std::underflow_error("Queue is empty");
        }

        T value = arr[front];
        if (front == rear) {
            front = rear = -1; // Queue becomes empty after dequeue
        } else {
            front = (front + 1) % capacity;
        }
        size--;

        if (logger) {
            logger("Dequeued: " + std::to_string(value));
        }

        return value;
    }

    /**
     * @brief Retrieves the front element without removing it.
     *
     * This allows you to inspect the element at the front of the queue
     * without removing it. Throws an underflow error if the queue is empty.
     *
     * @return The front element of the queue.
     * @throws std::underflow_error if the queue is empty.
     */
    T peek() const {
        if (is_empty()) {
            throw std::underflow_error("Queue is empty");
        }
        return arr[front];
    }

    /**
     * @brief Displays the current elements of the queue.
     *
     * This function prints all the elements in the queue, starting from
     * the front to the rear. It displays a message if the queue is empty.
     */
    void display() const {
        if (is_empty()) {
            std::cout << "Queue is empty" << std::endl;
            return;
        }

        std::cout << "Queue elements: ";
        for (int i = 0; i < size; ++i) {
            std::cout << arr[(front + i) % capacity] << " ";
        }
        std::cout << std::endl;
    }

    /**
     * @brief Clears the queue by resetting its front and rear pointers.
     *
     * This function empties the queue and logs the clearing event if a logger
     * callback is provided.
     */
    void clear() {
        front = rear = -1;
        size = 0;
        if (logger) {
            logger("Queue cleared");
        }
    }

    /**
     * @brief Retrieves all elements currently in the queue as a vector.
     *
     * This function returns a snapshot of all elements in the queue, starting
     * from the front to the rear. The queue is not modified.
     *
     * @return A vector containing all elements in the queue.
     */
    std::vector<T> get_all_elements() const {
        std::vector<T> elements;
        for (int i = 0; i < size; ++i) {
            elements.push_back(arr[(front + i) % capacity]);
        }
        return elements;
    }

    /**
     * @brief Retrieves the element at a specific index in the queue.
     *
     * The index is relative to the front of the queue. If the index is out of
     * range (i.e., less than 0 or greater than or equal to the size), an exception
     * will be thrown.
     *
     * @param index The index of the element to retrieve (0-based, relative to the front).
     * @return The element at the specified index.
     * @throws std::out_of_range if the index is invalid.
     */
    T get_element_at(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return arr[(front + index) % capacity];
    }

    /**
     * @brief Resizes the queue to a new capacity.
     *
     * If the new capacity is less than the current size, an exception is thrown.
     * This ensures that the queue does not lose any elements in the process.
     *
     * @param new_capacity The new capacity of the queue.
     * @throws std::invalid_argument if new_capacity is less than the current size.
     */
    void resize(int new_capacity) {
        if (new_capacity < size) {
            throw std::invalid_argument("New capacity cannot be less than the current size");
        }

        auto new_arr = std::make_unique<T[]>(new_capacity);
        for (int i = 0; i < size; ++i) {
            new_arr[i] = arr[(front + i) % capacity];
        }

        arr = std::move(new_arr);
        capacity = new_capacity;
        front = 0;
        rear = size - 1;

        if (logger) {
            logger("Queue resized to capacity: " + std::to_string(new_capacity));
        }
    }

    /**
     * @brief Returns the current size of the queue.
     *
     * This function returns the number of elements in the queue.
     *
     * @return The current size of the queue.
     */
    int get_size() const {
        return size;
    }

    /**
     * @brief Returns the maximum capacity of the queue.
     *
     * This function returns the maximum number of elements the queue can hold.
     *
     * @return The capacity of the queue.
     */
    int get_capacity() const {
        return capacity;
    }

};
