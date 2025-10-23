# Social Network Influence Analyzer

This C++ project implements fundamental data structures (a generic Singly Linked List and a Stack) and uses them to build a social network simulation. The primary goal of the simulation is to analyze the spread of information (e.g., "fake news") through the network to identify the single most influential user.

## Core Components

The project is built from three main template classes:

1.  **`LinkedList<T>`**: A generic, singly linked list implementation.
2.  **`Stack<T>`**: A generic, linked-list-based stack implementation.
3.  **`OnlinePlatform<T>`**: The main application class that models the social network and runs the influence analysis.

---

### 1. Generic `LinkedList<T>`

This class provides the foundational data structure for storing follower relationships.

**Features:**
* **Internal `Node` Class**: A private nested class to manage individual data nodes.
* **`insert(T val)`**: Adds a new value to the **front** (head) of the list.
* **`remove(T val)`**: Searches for and removes the first occurrence of a specific value.
* **`isEmpty()`**: Checks if the list is empty.
* **`Iterator` Class**: A nested `iterator` class is provided to allow for easy traversal of the list.
    * Overloads operators: `++` (prefix/postfix), `*` (dereference), `==`, and `!=`.
    * Accessible via `begin()` and `end()` methods.
* **Memory Management**: A destructor is included to properly deallocate all nodes and prevent memory leaks.

---

### 2. Generic `Stack<T>`

This class provides a standard Last-In, First-Out (LIFO) stack data structure. It is implemented using its own internal linked-list mechanism.

*(Note: This component is a standalone data structure implementation and is not directly used by the `OnlinePlatform` class in the final program.)*

**Features:**
* **`push(T val)`**: Adds an element to the top of the stack.
* **`pop()`**: Removes the top element from the stack.
* **`topElement()`**: Returns the top element without removing it.
* **`isEmpty()`**: Checks if the stack is empty.
* **`isFull()`**: Checks if the stack has reached its maximum capacity (defined at construction, defaults to 100).
* **Error Handling**:
    * `push` will print a "Stack Overflow" error if full.
    * `pop` will throw a `runtime_error` if the stack is empty.

---

### 3. `OnlinePlatform<T>`

This is the main application class that simulates the social network.

**Data Structure**
The platform's network is stored in `followList`, which is an **array of `LinkedList` objects**.
* The array index represents a `userID`.
* The linked list at `followList[userID]` contains all the `followerID`s for that user.
* Example: `followList[5]` is a linked list containing all users who follow `User 5`.

**Key Functions**
* **`input(const string& path)`**: Reads a formatted text file to build the follower network.
* **`addFollower(T userID, T followerID)`**: Adds a new follower to a user's list.
* **`removeFollower(T userID, T followerID)`**: Removes a follower from a user's list.
* **`showAllFollowers()`**: Prints the complete follower list for every user in the network.
* **`calculateFakeNewsSpread()`**: The core analysis algorithm.

## Algorithm: Fake News Spread Calculation

The `calculateFakeNewsSpread()` function determines the most influential user by simulating how a post from each user would spread through the network.

**Goal**: To find the user who, by posting a message, can reach the maximum number of other users through both direct and indirect followers.

**Process**:
1.  The function iterates through every user (`u`) from 1 to `totalUsers`, treating each one as the potential "patient zero" of the fake news.
2.  For each starting user `u`, it performs a **Breadth-First Search (BFS)** on the follower graph.
3.  An `influence[]` array is used as a `visited` set to ensure no user is "infected" or counted more than once.
4.  A manual array-based queue is used to manage the users to visit at each "level" of the spread.
5.  **Simulation Steps for User `u`**:
    * All **direct followers** of `u` are added to the queue and marked as `influenced`. Their count is added to `reachCount`.
    * The BFS loop begins:
        * A user (`currUser`) is dequeued.
        * The function iterates through all of `currUser`'s followers.
        * Any follower who has not yet been `influenced` is added to the queue, marked as `influenced`, and `reachCount` is incremented.
    * This continues until the queue is empty, meaning the news can spread no further.
6.  After the BFS is complete for user `u`, the total `reachCount` is compared against the `maxReach`.
7.  The program reports the user with the highest `maxReach` as the "Most Influential User."

## How to Run

### 1. Input File (`data.txt`)

This program requires an input file named `data.txt` to be in the same directory.

**Format:**
* The **first line** must contain a single integer: the total number of users.
* Subsequent lines must follow the format: `userID - followerID1 followerID2 followerID3 ...`

**Example `data.txt`:**
