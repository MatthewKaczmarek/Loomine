#include "game.h"
#include "windows.h"

void Game::movePlayer(int plr_ind, char dir) {
    int plr_x_pos = this->game_players[plr_ind].getXPos(); //current player's current x position
    int plr_y_pos = this->game_players[plr_ind].getYPos(); // current player's current y postion
    char plr_token = this->game_players[plr_ind].getToken(); //curent player's token
    
    int new_x;
    int new_y;
    switch(dir){
        case 'U': //case for when moving upwards 
            new_x = this->game_players[plr_ind].getXPos();
            new_y = this->game_players[plr_ind].getYPos() - 1;
        break;
        case 'R': //case for when moving right 
            new_x = this->game_players[plr_ind].getXPos() + 1;
            new_y = this->game_players[plr_ind].getYPos();
        break;
        case 'D': // case for when moving downwards
            new_x = this->game_players[plr_ind].getXPos();
            new_y = this->game_players[plr_ind].getYPos() + 1;
        break;
        case 'L': //case for when moving left
            new_x = this->game_players[plr_ind].getXPos() - 1;
            new_y = this->game_players[plr_ind].getYPos();
        break;
    }
    
    char overwrite_char = this->game_maps[cur_map].getBkndChar();
  
  //makes sure the player's token does not get overwritten by a background char
    for(int i = 0; i < this->game_players.size(); i++){  
        if(i != plr_ind){
            if(plr_x_pos == this->game_players[i].getXPos() && 
                plr_y_pos == this->game_players[i].getYPos()){
                overwrite_char = this->game_players[i].getToken();
                break;
            }
        } 
    }
    //updates the tokens to show that the player has moved and through the map
    if(new_x >= 0 && new_x < this->game_maps[cur_map][0].size() && 
        new_y >= 0 && new_y < this->game_maps[cur_map].size()){
        this->game_maps[cur_map][plr_y_pos][plr_x_pos] = overwrite_char;
        this->game_maps[cur_map][new_y][new_x] = plr_token;
        this->game_players[plr_ind].setPos(new_x, new_y);
    }
}

//sets move direction to up
void Game::movePlayerUp(int plr_ind) {
    this->movePlayer(plr_ind, 'U');
}

//sets move direction to right
void Game::movePlayerRight(int plr_ind){
    this->movePlayer(plr_ind, 'R');
}

//sets move direction to down
void Game::movePlayerDown(int plr_ind){
    this->movePlayer(plr_ind, 'D');
}

//sets move direction to left 
void Game::movePlayerLeft(int plr_ind){
    this->movePlayer(plr_ind, 'L');
}

void Game:: moveEnemies(){
    //pointer to the vector of enemies pertaining to the current map
    vector<Enemy>* enemies = &(this->game_maps[this->cur_map].getEnemies());
    //position update variables 
    int new_enemy_x;
    int new_enemy_y;
    for(int i = 0; i < (*enemies).size(); i++){ //looping through every enemy on the map
        if ((*enemies)[i].getTimeUntilMove() == 0){ // checks to see if its a valid move time
            switch(this->getEnemyMoveDirection((*enemies)[i])){
                case 'U': new_enemy_x = (*enemies)[i].getXPos(); new_enemy_y = (*enemies)[i].getYPos() - 1; break; // move up
                case 'R': new_enemy_x = (*enemies)[i].getXPos() + 1; new_enemy_y = (*enemies)[i].getYPos(); break; // move right 
                case 'D': new_enemy_x = (*enemies)[i].getXPos(), new_enemy_y = (*enemies)[i].getYPos() + 1; break; // move down
                case 'L': new_enemy_x = (*enemies)[i].getXPos() - 1; new_enemy_y = (*enemies)[i].getYPos(); break; // move left 
                case 'X': new_enemy_x = (*enemies)[i].getXPos() - 1; new_enemy_y = (*enemies)[i].getYPos() - 1; break; // move diagonally up and left
                case 'Y': new_enemy_x = (*enemies)[i].getXPos() + 1; new_enemy_y = (*enemies)[i].getYPos() - 1; break; // move diagonally up and right
                case 'Z': new_enemy_x = (*enemies)[i].getXPos() - 1; new_enemy_y = (*enemies)[i].getYPos() + 1; break; // move diagonally down and left
                case 'W': new_enemy_x = (*enemies)[i].getXPos() + 1; new_enemy_y = (*enemies)[i].getYPos() + 1; break; // move diagonally down and right 
            }
            this->game_maps[this->cur_map][(*enemies)[i].getYPos()][(*enemies)[i].getXPos()] = this->game_maps[this->cur_map].getBkndChar(); //setting the enemies previous token location to a background char
            (*enemies)[i].setPos(new_enemy_x, new_enemy_y); // updating the enemy's position
            this->game_maps[this->cur_map][new_enemy_y][new_enemy_x] = (*enemies)[i].getToken(); //updating the enemy's token to appear a the current postion
        }
        (*enemies)[i].tickTime(); //continue to stall movement for set ms
    }
}

char Game::getEnemyMoveDirection(Enemy e) {
    vector<pair<int,char>> directions; //vector to hold position direction pair 
    pair<int,char> valid_dir; //position direction pair 
    for(Player p: this->game_players){
        // check valid up direction
        if(p.isActive()){
            if(this->validEnemyPos(e, 'U')){ 
                valid_dir.first = this->getDistance(e.getXPos(), e.getYPos() - 1, p); // set distance
                valid_dir.second = 'U'; // set direction 
                directions.push_back(valid_dir); // add to movement vector 
            }
            // check valid right direction
            if(this->validEnemyPos(e, 'R')){
                valid_dir.first = this->getDistance(e.getXPos() + 1, e.getYPos(), p); // set distance
                valid_dir.second = 'R'; //set direction 
                directions.push_back(valid_dir); // add to movement vector 
            }
            //check valid down direction
            if(this->validEnemyPos(e, 'D')){
                valid_dir.first = this->getDistance(e.getXPos(), e.getYPos() + 1, p); // set distance
                valid_dir.second = 'D'; // set direction 
                directions.push_back(valid_dir); // add to movement vector
            }
            //check valid left direction
            if(this->validEnemyPos(e,'L')){
                valid_dir.first = this->getDistance(e.getXPos() - 1, e.getYPos(), p); //set distance 
                valid_dir.second = 'L'; // set direction 
                directions.push_back(valid_dir); // add to movement vector
            }
            //check valid Up and Left direction
            if(this->validEnemyPos(e,'X')){
                valid_dir.first = this->getDistance(e.getXPos()-1, e.getYPos()-1, p); //set distance
                valid_dir.second = 'X'; // set direction 
                directions.push_back(valid_dir); // add to movement vector
            }
            //check valid Up and Right direction
            if(this->validEnemyPos(e,'Y')){ 
                valid_dir.first = this->getDistance(e.getXPos()+1, e.getYPos()-1, p); // set distance
                valid_dir.second = 'Y'; // set direction 
                directions.push_back(valid_dir); // add to movement vector 
            }
            //check valid Down and Left direction
            if(this->validEnemyPos(e,'Z')){
                valid_dir.first = this->getDistance(e.getXPos()-1, e.getYPos()+1, p); //set distance 
                valid_dir.second = 'Z'; // set direction 
                directions.push_back(valid_dir); // add to movement vector
            }
            //check valid Down and Right direction
            if(this->validEnemyPos(e,'W')){
                valid_dir.first = this->getDistance(e.getXPos()+1, e.getYPos()+1, p); // set distance 
                valid_dir.second = 'W'; // set direction 
                directions.push_back(valid_dir); // add to movement vector
            }
        }
    }
    return this->minDistanceDirection(directions); // find the closest player object based off of movement vector 
}

//modified use of pythagorean theorem to find a shortest path
int Game::getDistance(int new_enemy_x, int new_enemy_y, Player p){
    int x_distance = new_enemy_x - p.getXPos();
    int y_distance = new_enemy_y - p.getYPos();
    return ((x_distance * x_distance) + (y_distance * y_distance));
}

//compares all distances and returns the smallest one 
char Game::minDistanceDirection(vector<pair<int,char>> directions) {
    int min_index = 0;
    for(int i = 1; i < directions.size(); i++){
        if (directions[i].first < directions[min_index].first) {
            min_index = i;
        }
    }
    return directions[min_index].second;
}
// X = up left , Y = up right, Z = down left, W = down right
bool Game:: validEnemyPos(Enemy e, char dir){
    int new_x;
    int new_y;
    switch(dir) {
        case 'U': 
            new_x = e.getXPos();
            new_y = e.getYPos() - 1;
        break;
        case 'R':
            new_x = e.getXPos() + 1;
            new_y = e.getYPos();
        break;
        case 'D':
            new_x = e.getXPos();
            new_y = e.getYPos() + 1;
        break;
        case 'L':
            new_x = e.getXPos() - 1;
            new_y = e.getYPos();
        break;
        case 'X':
            new_x = e.getXPos() - 1;
            new_y = e.getYPos() - 1;
        break;
        case 'Y':
            new_x = e.getXPos() + 1;
            new_y = e.getYPos() - 1;
        break;
        case 'Z':
            new_x = e.getXPos() - 1;
            new_y = e.getYPos() + 1;
        break;
        case 'W':
            new_x = e.getXPos() + 1;
            new_y = e.getYPos() + 1;
        break;
    }
    //variable to determine if a movement is within the bounds of the map 
    bool valid_pos = (new_x >= 0 && new_x < this->game_maps[cur_map][0].size() &&
        new_y >= 0 && new_y < this->game_maps[cur_map].size());
    if(!valid_pos){ // movement is outside of the map
        return false;
    }
    //checking to see if the enemy will move over door 
    vector<Door> doors =  this->game_maps[cur_map].getDoors();
    for(int i = 0; i < doors.size(); i++){
        if (new_x == doors[i].getXPos() && new_y == doors[i].getYPos()){ // if it will move over a door the movement is invalid
            return false;
        }
    }
    //checking to see if the enemy will move over another enemy 
    vector<Enemy> enemies = this->game_maps[cur_map].getEnemies();
    for(int i = 0; i< enemies.size(); i++){
        if(new_x == enemies[i].getXPos() && new_y == enemies[i].getYPos()){ // if it will move over an enemy the movement is invalid 
            return false;
        }
    }
    return true;
}

void Game::handleEnemyPlayerContact(){
    vector<Enemy> enemies = this->game_maps[cur_map].getEnemies();
    for(int i = 0; i < enemies.size(); i++){ //checking for all enemies on a map 
        for(int j = 0; j < this->game_players.size(); j++){
            if(enemies[i].getXPos() == this->game_players[j].getXPos() && //check if an enemy and player's position are overlapping 
                enemies[i].getYPos() == this->game_players[j].getYPos()){
                    this->removePlayer(j); // if yes remove player from the game
                }
        }
    }
    this->game_over = this->game_players.empty(); // if all enemies are removed end the game
}

void Game::removePlayer(int plr_index){  
    int size = this->game_players.size();
    //swapping the last player's position in a vector with the contacted player's position
    this->game_players[plr_index] = this->game_players[size - 1];  
    this->game_players.pop_back(); // removing the contacted player from the game
}

void Game::printGrid() {
    std::string print_out = ""; // start of the grid 
    print_out.append(this->game_maps[cur_map][0].size() + 2, this->game_maps[cur_map].getBorderChar()); // print the top row of the border
    print_out += "\n"; // start new row
    for(int i = 0; i < this->game_maps[cur_map].size(); i++){ // loop through the 2D char vector to make a grid 
        print_out += this->game_maps[cur_map].getBorderChar(); // start with a border char
        for(int j = 0; j < this->game_maps[cur_map][i].size(); j++){  // loop through the number of columns 
            print_out += this->game_maps[cur_map][i][j]; // add in background chars for the number of columns 
        }
        print_out += (this->game_maps[cur_map].getBorderChar()); // add a border char to the end 
        print_out += "\n"; // start new row
    }
    print_out.append(this->game_maps[cur_map][0].size() + 2, this->game_maps[cur_map].getBorderChar()); // add a final row of border chars 
    print_out += "\n"; // finish the grid 
    setCursorPos(0,0);
    cout << print_out << endl; // print out the grid 
}

void Game::detectInput() {
    char dir[4]; // number of possible inputs 
    for(int plr = 0; plr < this->game_players.size(); plr++){ // loop for every player 
        if(this->game_players[plr].isActive()){ // is the player in a door 
            dir[0] = this->game_players[plr].getUpCtr(); // set move up input 
            dir[1] = this->game_players[plr].getRightCtr(); // set move right input
            dir[2] = this->game_players[plr].getDownCtr(); // set move down input
            dir[3] = this->game_players[plr].getLeftCtr(); // set  move left input
            for(int mov_dir = 0; mov_dir < 4; mov_dir++){
                if(GetAsyncKeyState(dir[mov_dir]) & 0x8000) { // check for button press
                    switch(mov_dir){
                        case 0: this->movePlayerUp(plr); break; // is up input pressed
                        case 1: this->movePlayerRight(plr); break; // is right input pressed
                        case 2: this->movePlayerDown(plr); break; // is down input pressed 
                        case 3: this->movePlayerLeft(plr); break; // is left input pressed 
                    }
                }
            }
        }
    }
}

//error checking 
void Game::checkPlayerOutOfBoundsSpawn() const {
    Map first_map = this->game_maps[0];
    for(int i = 0; i < this->game_players.size(); i++){ // loop for every player 
        if(this->game_players[i].getLastDoorXPos() < 0 ||this->game_players[i].getLastDoorXPos() >= first_map[0].size() || 
        this->game_players[i].getLastDoorYPos() < 0 || this->game_players[i].getLastDoorYPos() >= first_map.size()) { // does it have a spawn position within the map 
            setTextColor(4);
            throw invalid_argument("Error: Player " + string(1, this->game_players[i].getToken()) + " has initial " + // if not throw error message
            "spawn location outside of the bounds of the first map!");
        }
    }
}

//error checking 
void Game::checkValidDoorLocations()  {
    vector<Door> doors;
    for(int i = 0; i < this->game_maps.size() - 1; i++){ // for every map 
        doors = this->game_maps[i].getDoors();
        for(int j = 0; j < doors.size(); j++){ // check every door in every map
            if(doors[j].getXPos() >= this->game_maps[i + 1].getNumCols() ||
            doors[j].getYPos() >= this->game_maps[i + 1].getNumRows()) { // does this door have a valid location in the next map to spawn players at
                setTextColor(4);
                // if no throw error message
                throw invalid_argument("Error: Attempted to add door with token '" + string(1, doors[j].getToken()) + "' in a position that does not exist on the next map!");
            }
        }
    }
}

//error checking 
void Game::checkValidEnemySpawn() {
    vector<Enemy> enemies;
    vector<Door> doors;
    for(int i = 0; i < this->game_maps.size(); i++){ // for every map 
        enemies = this->game_maps[i].getEnemies();
        doors = this->game_maps[i].getDoors();
        for(int j = 0; j < doors.size(); j++){ // check every door in every map 
            for(int k = 0; k < enemies.size(); k++){ // check every enemy against every door in every map 
                if(doors[j].getXPos() == enemies[k].getXPos() &&
                doors[j].getYPos() == enemies[k].getYPos()){ // does the enemy spawn in a door
                    setTextColor(4);
                    // if yes throw error message
                    throw invalid_argument("Error: Attempted to spawn enemy with token '" + string(1, enemies[k].getToken()) + "' on top of a door with token '" + doors[k].getToken() + "'!");
                }
            }
        }
    }
}

void Game::checkMapAndPlayerExistence() {
    if(this->game_maps.size() == 0 || this->game_players.size() == 0) { // does the game have a map and players 
        setTextColor(4);
        throw invalid_argument("Error: Attempted to run game without any players or maps!"); // if no throw error message
    }
}

//functionalizing the error checks 
void Game::checkGameCreationErrors() {
    this->checkMapAndPlayerExistence();
    this->checkPlayerOutOfBoundsSpawn();
    this->checkValidDoorLocations();
    this->checkValidEnemySpawn();
}

Game::Game() : Game(30) {}

Game::Game(int speed){
    this -> speed = speed; // set the refresh rate to the speed inputted 
    this -> cur_map = 0; // set the map index to 0
    this -> game_over = false; // set game over flag to false 
}

//adders
void Game::addMap(Map new_map) {
    this->game_maps.push_back(new_map);
}

void Game::addPlayer(Player new_player) {
    this->game_players.push_back(new_player);
}

void Game::updateMap(){
    cur_map++; // increment map index
    if(cur_map >= this->game_maps.size()){ // are there any more maps 
        game_over = true; // if no end the game
    }
    clearScreen();
}

void Game::spawnPlayers(){
    if(!game_over){ // make sure the game is still active 
        Player plr;
        for(int i = 0; i < this->game_players.size(); i++){ //for every player 
            plr = this->game_players[i];
            this->game_maps[cur_map][plr.getLastDoorYPos()][plr.getLastDoorXPos()] = plr.getToken(); //place player token on the map
            this->game_players[i].toggleActivate(); // set them to an active state
        }
    }
}

bool Game::checkAnyActive() const{
    for(int i = 0; i < this->game_players.size(); i++){ //for every player 
        if(this->game_players[i].isActive()){ //are they still active 
            return true;  // if yes return true
        }
    }
    return false; // if no they have reached door 
}

void Game::checkDoors(){
    vector<Door> doors = this->game_maps[cur_map].getDoors();
    for(int i = 0; i < this->game_players.size(); i++){ // for every player 
        for(int j = 0; j < doors.size(); j++){ // check every door 
            if((this->game_players[i].getYPos() == doors[j].getYPos()) &&
                (this->game_players[i].getXPos() == doors[j].getXPos()) &&
                (this->game_players[i].isActive())){ // has an active player overlapped a door's position 
                    this->game_players[i].toggleActivate(); // if yes toggle inactive 
                    this->game_maps[cur_map][doors[j].getYPos()][doors[j].getXPos()] = doors[j].getToken(); // set player's token to be the door token 
                    this->game_players[i].setLastDoorPos(doors[j].getXPos(), doors[j].getYPos()); // set the player's next spawn location to the doors coords
            }
        }
    }
}

void Game::gameLoop(){
    this->checkGameCreationErrors(); // is this a legal game check 
    clearScreen(); //clear the terminal so there is no overlap 
    bool first_map = true;
    while(!this->game_over){ // while the game conditions have not been met
        if(!this->checkAnyActive()){ // are there still active players 
            if(!first_map){ //are we on the first map of the game 
                this->updateMap(); // if no move to the next map
            }
            else{
                first_map = false; // leave the first map 
            }
            this->spawnPlayers(); //spawn players 
        }
        //run the game until we get a game over (die or quit)
        if(!this->game_over){
            this->printGrid();
            this->detectInput();
            this->moveEnemies();
            this->handleEnemyPlayerContact();
            this->checkDoors();
            Sleep(this->speed);
        }
    }
}

Game& Game::operator=(Game & other){
    this->speed = other.speed;
    this->cur_map = other.cur_map;
    this->game_over = other.game_over;
    this->game_players = other.game_players;
    this->game_maps = other.game_maps;
    return *this;
}