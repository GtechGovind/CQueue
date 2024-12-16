#include "library.h"

/**
 * @brief Constructor that initializes the circular queue with a fixed size and an optional logging callback.
 *
 * Initializes the queue to be empty, allocates memory for the queue array,
 * and sets up the logger callback (if provided).
 *
 * @param n The maximum size of the queue.
 * @param callback An optional callback function for logging queue events.
 */
template <typename T>
circular_queue<T>::circular_queue(const int n, std::function<void(const std::string&)> callback)
    : front(-1), rear(-1), size(n), logger(std::move(callback)) {
    arr = new T[size];  // Dynamically allocate memory for the queue array
}

/**
 * @brief Destructor that deallocates memory used by the queue.
 *
 * Ensures proper memory management by releasing the dynamically allocated memory for the queue array.
 */
template <typename T>
circular_queue<T>::~circular_queue() {
    delete[] arr;  // Deallocate the queue array to avoid memory leaks
}

/**
 * @brief Checks if the queue is full.
 *
 * The queue is considered full if the next position after the rear pointer
 * is equal to the front pointer, indicating that no more elements can be
 * added without overwriting existing elements.
 *
 * @return True if the queue is full, false otherwise.
 */
template <typename T>
bool circular_queue<T>::is_full() const {
    return (rear + 1) % size == front;  // Full condition, considering wrap-around
}

/**
 * @brief Checks if the queue is empty.
 *
 * The queue is empty if the front pointer is set to -1, indicating that
 * there are no elements in the queue.
 *
 * @return True if the queue is empty, false otherwise.
 */
template <typename T>
bool circular_queue<T>::is_empty() const {
    return front == -1;  // Empty condition, front is -1
}

/**
 * @brief Adds an element to the rear of the queue.
 *
 * If the queue is full, the oldest element is dequeued before the new
 * element is added. If the queue was previously empty, the front pointer
 * is initialized to 0.
 *
 * @param value The element to be added to the queue.
 */
template <typename T>
void circular_queue<T>::enqueue(T value) {
    if (is_full()) dequeue();  // Remove the oldest element if the queue is full
    if (front == -1) front = 0;  // Initialize front if the queue was empty
    rear = (rear + 1) % size;  // Update the rear pointer with wrap-around
    arr[rear] = value;  // Insert the new element at the rear
    if (logger) logger("Enqueued: " + std::to_string(value));  // Log the enqueue action
}

/**
 * @brief Removes and returns the front element of the queue.
 *
 * The front element is removed and returned. If the queue becomes empty
 * after the dequeue, both the front and rear pointers are reset to -1.
 *
 * @return The element that was removed from the front of the queue.
 *         If the queue is empty, a default-constructed T is returned.
 */
template <typename T>
T circular_queue<T>::dequeue() {
    if (is_empty()) {
        if (logger) logger("Queue is empty! Cannot dequeue.");  // Log error if the queue is empty
        return T();  // Return a default-constructed T if the queue is empty
    }
    T value = arr[front];  // Store the front element to return later
    if (front == rear) front = rear = -1;  // If only one element remains, reset the queue
    else front = (front + 1) % size;  // Update front pointer with wrap-around
    if (logger) logger("Dequeued: " + std::to_string(value));  // Log the dequeue action
    return value;  // Return the dequeued value
}

/**
 * @brief Retrieves the front element without removing it.
 *
 * This function returns the front element of the queue without removing it.
 * If the queue is empty, a default-constructed T is returned.
 *
 * @return The front element of the queue or a default-constructed T if empty.
 */
template <typename T>
T circular_queue<T>::peek() {
    if (is_empty()) {
        if (logger) logger("Queue is empty! No front element.");  // Log if the queue is empty
        return T();  // Return a default-constructed T if the queue is empty
    }
    if (logger) logger("Peeked at: " + std::to_string(arr[front]));  // Log the peek action
    return arr[front];  // Return the front element without removing it
}

/**
 * @brief Displays the current elements of the queue.
 *
 * This function prints the elements of the queue in order from front to rear.
 * The queue is traversed circularly, considering the wrap-around.
 *
 * If a logger is provided, it logs each element of the queue during the display.
 */
template <typename T>
void circular_queue<T>::display() {
    if (is_empty()) {
        if (logger) logger("Queue is empty!");  // Log if the queue is empty
        return;  // Exit if the queue is empty
    }

    int i = front;
    while (i != rear) {  // Traverse the queue until reaching the rear
        if (logger) logger(std::to_string(arr[i]));  // Log each element during traversal
        i = (i + 1) % size;  // Wrap-around using modulo arithmetic
    }
    if (logger) logger(std::to_string(arr[rear]));  // Log the last element (rear)
    if (logger) logger("Displayed queue elements.");  // Log completion of display
}

/**
 * @brief Clears the queue by resetting its front and rear pointers.
 *
 * This function effectively removes all elements from the queue by resetting
 * the front and rear pointers to -1. Optionally, it logs the clear action.
 */
template <typename T>
void circular_queue<T>::clear() {
    front = rear = -1;  // Reset the queue to its empty state
    if (logger) logger("Queue cleared.");  // Log the clear action
}

template class circular_queue<int>;
template class circular_queue<std::string>;
