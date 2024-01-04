# A Guide to Programming in Loomine
Welcome to Loomine, an easy to use Console Game Engine Language! Follow this guide to learn how to create your own games!

## Authors
Matthew Kaczmarek, 
Ryan Trader

## What is Loomine?
Loomine is a programming language that lets you easily build custom ASCII art console games! It is a language that compiles down to C++.

## Basic Elements of Loomine
Before you get started, there are a few basic elements you should know to create successful Loomine programs. Let's walk through them...
### Identifier
* An Identifier is a series of characters
* Identifiers must start with lower case letters `a-z`
* After the initial lower case letter, an Identifier may be followed by 0 or more lower case letters `a-z` or numbers `0-9`
* Identifiers are used to declare and  refer to variables
* EX: `myVar`
### Character
* A Character must start and end with a double quote `"`
* Between the starting and ending quote, there must be exactly one ASCII character  
* Characters are used to declare ASCII elements
* EX: `"@"`
### Digit
* A Digit is a series of numbers (0-9)
* A Digit can be of length 1 or more
* Digits are used to declare numerical values
* EX: `129`
### Parentheses
* Parentheses are either `(` or `)`
* Parentheses are used to contain values when declaring data types... more on that later...
### Comma
* A Comma is `,`
* Commas are used to separate values when declaring data types... more on that later...
### AssignOp
* `:=` is the AssignOP
* The Assignment Operator is used to attach values to variables... more on that later...
### End Symbol
* `$$` is the End Symbol
* The End Symbol must be included at the bottom of every program!

## Basic Language
In Loomine, there are two kinds of statements: data type declarations and Run statements. 
### Data Type Declarations
* Data type declarations are written like this: 'Identifier AssigOp data_type_statement'
* See below for the list of data type statements to put in place of 'data_type_statement'
* EX: `pone := player(0,0,"P","W","D","S,","A")`
### Run Statements
* Run statements start with `run` and are followed by either an identifier that is assigned to a game object or a game declaration
* This is how games are run
* Note that a game will run until either all players have made it through a door on the final map of the game or until all players are dead (i.e. all players have been touched by enemies)
* EX: `run game(10) addP player(0,0,"P","W","D","S","A") addM map(10,10,".","*")`

## Data Types
Below you will see a list of Data Types, their functionality, and their possible interactions with other Data Types.

### Door
* A Door is an object that can be added to a Map
* When a Game is running, any player who runs into a Door will disappear
* When all players who are not dead have run into a Door one of two things will happen: if the current Map is the last map in a Game, the Game will end, otherwise, all players who entered a Door will spawn on the next Map at the same location as the Door
* A Door is declared like so: `Identifier := door(Digit,Digit, Character)` where the first Digit represents the door's x position, the second Digit represents the y position, and the Character represents the Door's token (how the Door will appear on the Map)
* EX: `done := door(5,5,"#")`

### Player
* A Player is an object that can be added to a Game
* When a Game is running, a user can control a Player by pressing the keys that correspond to that Player via that Player's declaration
* A Player is declared like so: `Identifier := player(Digit, Digit, Character, Character, Character, Character, Character)` where the first Digit represents the x position at which the Player will spawn on the first Map of a Game, the second Digit represents the y position at which the Player will spawn on the first Map of a Game, the first Character represents the Player's token (how the Player will appear on the Map), the second Character represents the keyboard key that when pressed will move the Player in the up direction, the third Character represents the keyboard key that when pressed will move the Player in the right direction, the fourth Character represents the keyboard key that when pressed will move the Player in the down direction, and the fifth Character represents the keyboard key that when pressed will move the Player in the left direction
* __IMPORTANT__: In order for Player controls to work correctly, the second through fifth Character must be a __capital__ letter representing a valid key on the keyboard
* EX: `pone := player(0,0,"P","W","D","S","A")`

### Enemy
* An Enemy is a computer controlled entity that, if it runs into a Player, will "kill" the Player and take the Player out of the Game
* An Enemy can be added to a Map
* An Enemy will spawn where you tell it and will constantly move towards the closest Player
* An Enemy will never step on a Door
* An Enemy is declared like so: `Identifier := enemy(Digit, Digit, Character, Digit)` where the first Digit represents the x position where the enemy will spawn, the second Digit represents the y position where the enemy will spawn, the first Character represents the Enemy's token (how the Enemy will appear on the Map), and the third Digit represents the "speed" of the Enemy (in essence it represents the number of frames the Enemy will wait before moving, so lower "speed" means the Enemy moves faster)
* EX: `eone := enemy(7,7,"E",5)`

### Map
* A Map is a play area that can be added to a Game
* A Map represents all the places that entities can move about during a Game
* A Map is declared like so: `Identifier := map(Digit, Digit, Character, Character)`  where the first Digit represents the number of rows in the map, the second Digit represents the number of columns in the map, the first Character represents the background ASCII character of the Map, and the second Character represents the border ASCII character of the Map
* EX: `mone := map(10,10,".","*")` 


#### Map Interactions with Other Data Types
Map has two Interactions with Other Data Types. A Door can be added to a Map through the `addD` command like so: 

`map_identifier addD door_identifier`

This interaction returns a Map, so to use it, you must set an Identifier equal to this statement

EX: 

`mone := map(10,10,".","*")`

`done := door(5,5,"#")`

`mone := mOne addD dOne`

An Enemy can be added to a Map through the `addE` command like so: 

`map_identifier addE enemy_identifier`

This interaction returns a Map, so to use it, you must set an Identifier equal to this statement

EX: 

`mone := map(10,10,".","*")`

`eone := enemy(7,7,"E",5)`

`mone := mOne addE eOne`

## Game
* A Game is a playable set of Maps, Players, Enemies, and Doors
* A Game is declared like so: `Identifier := game(Digit)` where Digit represents the "speed" of the Game (in essence, the Digit determines how many milliseconds the Game will sleep for during the main Game loop, so a lower "speed" means a faster framerate)
* EX: `g := game(30)`

### Game Interactions with Other Data Types
Game has two Interactions with Other Data Types. A Player can be added to a Game through the `addP` command like so: 

`game_identifier addP player_identifier`

This interaction returns a Game, so to use it, you must set an Identifier equal to this statement

EX: 

`pone := player(0,0,"P","W","D","S","A")`

`g := game(30)`

`g := g addP pOne`

A Map can be added to a Game through the `addM` command like so: 

`game_identifier addM map_identifier`

This interaction returns a Game, so to use it, you must set an Identifier equal to this statement

Note that when a Map is added to a Game, it is placed at the end of that Game's Map queue, so to access that Map, a Player must pass through Doors from the Maps before it to traverse to that Map

EX: 

`mone := map(10,10,".","*")`

`g := game(30)`

`g := g addM mone`

## Runtime Errors
Loomine supports several different runtime errors. A runtime error will occur if...
* If a Game is run that has a Player's initial position that is outside the bounds of the first Map added to that Game
* If an Enemy or Door's initial position is out of bounds of the Map that they are being added to
* If a Map is initialized that has either zero columns or zero rows
* If a Game is run that has a Door in one Map whose location is out of bounds in the next Map (this was implemented since the Door's location is where the Player will spawn on the next Map)
* If a Game is run that would have an Enemy spawn on top of a Door (i.e. if the Enemy's initial position matches the position of a Door on that map)
* A Game is run that does not have any Players or Maps added to it

## Writing Loomine
Loomine code should be written in the test.expr file under the gameengine directory 

### Rebuilding Compiler (Only if Necessary)
This shouldn't need to be performed, but if for any reason the Loomine compiler needs to be rebuilt, run the build_compiler.bat file in the gameengine directory

### Compiling and Running Loomine
To compile and run Loomine code written in test.expr, run the compile_and_run.bat file in the gameengine directory.

## Example Program
```
pone := player(0,0,"P","W","D","S","A")
ptwo := player(5,5,"Q","I","L","K","J")
mone := map(10,10,".","*")
done := door(9,1,"#")
dtwo := door(2,6,"#")
mone := mone addD done
mone := mone addD dtwo
mtwo := map(20,20,"-","|")
eone := enemy(13,14,"E",20)
etwo := enemy(18,19,"A",20)
dthree := door(17,17,"#")
mtwo := mtwo addE eone
mtwo := mtwo addE etwo
mtwo := mtwo addD dthree
mthree := map(18,18,"^","+")
ethree := enemy(1,1,"B",20)
efour := enemy(1,9,"C",20)
efive := enemy(9,1,"D",20)
dfour := door(5,5,"#")
mthree := mthree addE ethree
mthree := mthree addE efour
mthree := mthree addE efive
mthree := mthree addD dfour
g := game(30)
g := g addM mone
g := g addM mtwo
g := g addM mthree
g := g addP pone
g := g addP ptwo
run g
$$
```
