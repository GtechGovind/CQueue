# Circular Queue Template Library

## Overview
This library provides a template-based implementation of a circular queue in C++. The `circular_queue` class efficiently manages fixed-size collections of any data type and supports features like enqueue, dequeue, peek, and logging with callbacks.

## Features
- **Generic Template**: Supports any data type.
- **Fixed Size**: Size defined during construction.
- **Efficient Memory Management**: Implements a circular buffer to reuse space.
- **Callback Support**: Register optional logger functions for custom event handling.
- **Utility Methods**: Enqueue, dequeue, peek, clear, and display functionality.

---

## Usage
### Prerequisites
Ensure you have the following:
- C++17 or later.
- A compatible build tool (e.g., GCC, Clang, or MSVC).

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/GtechGovind/CQueue.git
   cd CQueue
   ```

2. Build the project using **CMake**:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

### Integration
To include this library in your project:
1. Add the `circular_queue` header file to your project.
2. Include it in your code:
   ```cpp
   #include "circular_queue.h"
   ```
3. Link the project if you are using the build from this repository.

### FetchContent Integration
If you want to include this project using **CMake FetchContent**, add the following to your `CMakeLists.txt`:
```cmake
include(FetchContent)
FetchContent_Declare(
  circular_queue
  GIT_REPOSITORY https://github.com/GtechGovind/CQueue.git
  GIT_TAG        main # or a specific tag
)
FetchContent_MakeAvailable(circular_queue)

add_executable(your_project main.cpp)
target_link_libraries(your_project PRIVATE circular_queue)
```

### Manual Integration
1. Copy the `circular_queue.h` file into your project directory.
2. Add the include path to your compiler flags, if necessary.
3. Include the header file in your code using:
   ```cpp
   #include "circular_queue.h"
   ```

---

## Documentation

### Class Template
```cpp
template <typename T>
class circular_queue;
```

### Member Functions

#### Constructor
```cpp
explicit circular_queue(int n, std::function<void(const std::string&)> callback = nullptr);
```
- **Parameters**:
  - `n`: Maximum size of the queue.
  - `callback`: Optional logger for events like enqueue or dequeue.

#### Destructor
```cpp
~circular_queue();
```
- Automatically deallocates memory used by the queue.

#### Check Full
```cpp
bool is_full() const;
```
- **Returns**: `true` if the queue is full, otherwise `false`.

#### Check Empty
```cpp
bool is_empty() const;
```
- **Returns**: `true` if the queue is empty, otherwise `false`.

#### Enqueue
```cpp
void enqueue(T value);
```
- **Parameters**:
  - `value`: The element to add to the queue.
- **Throws**: Exception if the queue is full.

#### Dequeue
```cpp
T dequeue();
```
- **Returns**: The front element of the queue.
- **Throws**: Exception if the queue is empty.

#### Peek
```cpp
T peek();
```
- **Returns**: The front element without removing it.
- **Throws**: Exception if the queue is empty.

#### Display
```cpp
void display();
```
- Prints the current elements in the queue.
- **Note**: This function only works if a logger is assigned during construction.

#### Clear
```cpp
void clear();
```
- Resets the queue by clearing all elements.

---

## Example Usage
Here is a simple example demonstrating the usage of `circular_queue`:

```cpp
#include "circular_queue.h"
#include <iostream>

void log_event(const std::string& message) {
    std::cout << "[LOG]: " << message << std::endl;
}

int main() {
    circular_queue<int> queue(5, log_event);

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.display();

    std::cout << "Dequeued: " << queue.dequeue() << std::endl;
    queue.display();

    std::cout << "Peek: " << queue.peek() << std::endl;
    queue.clear();
    queue.display();

    return 0;
}
```

**Output:**
```
[LOG]: Enqueued 10
[LOG]: Enqueued 20
[LOG]: Enqueued 30
Queue: 10 20 30
[LOG]: Dequeued 10
Dequeued: 10
Queue: 20 30
Peek: 20
[LOG]: Queue cleared
Queue:
```

---

## Build and Test
### Run Tests
1. Ensure you have **Google Test** installed.
2. Build and run the tests:
   ```bash
   mkdir build && cd build
   cmake -DBUILD_TESTING=ON ..
   make
   ctest
   ```

---

## Contributing
1. Fork the repository.
2. Create a new branch (`git checkout -b feature/YourFeature`).
3. Commit your changes (`git commit -m 'Add some feature'`).
4. Push to the branch (`git push origin feature/YourFeature`).
5. Open a pull request.

---

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Acknowledgments
- Template-based design inspired by generic programming principles in C++.
- Special thanks to the open-source community for contributions and feedback.

