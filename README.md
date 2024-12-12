# Formify: Shaping Creativity

## Deliverable Features

### Real-Time Interactive Computer Graphics
The project is based on interactive computer graphics, allowing users to create and manipulate shapes. This feature is demonstrated in the demo video.

### Layout Organization
The application includes two layouts nested into a root layout for the entire screen.

### Audio Rendering
A green button enables the user to play an audio file pre-loaded into the project.

### Parallelism and Performance Optimizations
- **Parallel Rendering**: Initially, the project parallelized drawing entire objects but later pivoted to parallelizing rows of each object to handle race conditions when multiple threads attempt to draw over the same pixel.
- **Static Polymorphism via CRTP**: Used to eliminate runtime lookups in a vtable, optimizing performance.

### Event-Driven Programming and Responses
Button presses trigger corresponding actions such as playing audio, rotating an image, or creating a random element.

## Deliverable Implementations

### Metaprogramming
Templated linear algebra library supports added data types in the future, enabling type-safe, generic code for different data types.

### Move Semantics and Copying
- **Move Semantics**: Employed via a move constructor in Element classes for efficient data transfer.
- **Copy Assignment**: Used within the linear algebra library for vector operations.

### CRTP
CRTP is implemented in the Event class and its derived classes (e.g., ClickEvent, SoundEvent, ShowEvent) to resolve function calls at compile-time, enhancing execution speed.

### Covariance
The Base Element class defines a clone operation implemented by derived classes with unique return types. This supports future features like a copy/paste functionality.

### Singleton
The EventSystem is a singleton, ensuring only one instance exists to manage the queue of current events.

### Polymorphism and Factories
- **Static Polymorphism**: Implemented via CRTP.
- **Dynamic Polymorphism**: The Element class and its derived classes define specific attributes and behaviors as needed.
- **Factory Pattern**: Abstracts element creation, simplifying user interaction by hiding constructor specifics.

### Containers
1. **Vectors**: Store all elements in a given layout.
2. **Unordered Map**: Tracks the layout-element mapping to repopulate the screen after clearing.
3. **Queue**: Maintains events in EventSystem, processing them in order.

### Iterators
Used with `begin()` and `end()` to loop through vectors when rendering elements on the screen.

### Functors
Used to re-scale elements in Layout 1 depending on the visibility of Layout 2.

### Algorithms
- **min/max**: Identifies starting and ending coordinates for elements.
- **find_if**: Locates which button the user clicked using a `containsPoint` call.

### File I/O
The project supports reading XML files to load layout hierarchies and writing XML files to save the current layout hierarchy with newly created elements.

### Unit Testing
Includes unit tests for:
- Linear algebra library.
- Individual object creation.
- Nested layout creation.

### High Cohesion
Each file is responsible for a specific set of features. For example, `Element.hpp` focuses strictly on element creation, manipulation, and destruction.

### Low Coupling
Modules have low interdependence, ensuring changes in one file do not affect unrelated functionalities. This design simplifies debugging and maintenance.