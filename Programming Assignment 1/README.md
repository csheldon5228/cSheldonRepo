## How to Build and Run
**Instructions:** Enter these two commands in the terminal to build and run the file.
- `g++ -std=c++17 monopoly_board_S26_template_v2.cpp -o monopoly_board`
- `./monopoly_board`

---

## Data Structure Used
### Circular Linked List
A circular linked list was used to link the monopoly spaces sequentially, where the tail node points to the head node.
The linked list allows for easy manipulation of the board spaces and simple traversal of the player nodes.
The linked list has a limit of 40 spaces on the board.

---

## List Of Functions
### `isEqual(MonopolySpace)`
**Description:** Checks if two MonopolySpaces are equal by name

### `print()`
**Description:** Prints out formatted MonopolySpace information

### `addSpace(T)`
**Description:** Adds a MonopolySpace to the end of the circular linked list

### `isEmpty()`
**Description:** Checks if the linked list is empty

### `isFull()`
**Description:** Checks if the linked list is full

### `addMany(vector<T>)`
**Description:** Takes a vector of MonopolySpaces and adds each element to the linked list

### `movePlayer(int)`
**Description:** Moves the player a certain number of steps down the linked list

### `getPassGoCount()`
**Description:** Checks how many times a player has passed GO

### `printFromPlayer(int)`
**Description:** Prints a certain number of MonopolySpaces ahead of the player

### `printBoardOnce()`
**Description:** Prints each MonopolySpace of the full board from GO

### `removeByName(string)`
**Description:** Searches for a MonopolySpace by its name, then removes it

### `rescuePlayer(Node<T>)`
**Description:** Moves the player to the next MonopolySpace if the current one it is on is going to get removed

### `findByColor(string)`
**Description:** Searches for MonopolySpaces with a color that matches the target, then returns a vector of those MonopolySpaces

### `countSpaces()`
**Description:** Traverses the linked lists and counts how many MonopolySpaces are stored

### `clear()`
**Description:** Traverses the linked list and deletes each node

---

## Traversal & Movement
**Description:** A player moves starts at GO and moves throughout the board by rolling dice to determine step count.
The player is able to move throughout the board via each node's next pointer, as the structure is a linked list.
With the board being a circular linked list, when the player reaches the end of list, they move back to the start to GO.
