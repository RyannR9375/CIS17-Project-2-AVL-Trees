#include "Deck.h"
#include "QuickEvent.h"
#include "LinkedList.h"
#include "AVL.h"
#include <fstream>

using namespace std;

//DECLARE FUNCTIONS
//SLAP JACK
void gameLoopSJ(Deck&, Deck&, Deck&);
void displayRulesSJ();
int slapJackMenu();

//GO FISH
void gameLoopGF(Deck&, Deck&, Deck&);
void displayRulesGF();
void goFishMenu();

//OTHER FUNCTIONS
bool timedInteraction(deque<string>, string, int);
int mainMenu();
int hashFunc(const string key);

//SCOREBOARD AND STAT TRACKING
void showScoreboard(AVL tree);
void welcomeMsg();
void weightedGraph(Deck deck);

//GLOBAL CONSTANTS
AVL ScoreBoard;
string userName{};
const int DECK_SIZE = 52;
const int SUITS = 4;
const int CARD_VALUES = 13;
    

//MAIN
int main(int argc, char** argv) {
    fstream data_store;
    srand(time(0));
    
    //GAME MENU
    int gameChose;
    
    while(gameChose != 5){
        gameChose = mainMenu();
        //CARD DECKS REINITIALIZED EVERY RUN
        Deck GAME_DECK;
        Deck Player;
        Deck Enemy; 
        
        if(gameChose == 1)
            gameLoopSJ(GAME_DECK, Player, Enemy);
        else if(gameChose == 2)
            gameLoopGF(GAME_DECK, Player, Enemy);
        else if(gameChose == 3)
            showScoreboard(ScoreBoard);
        else if(gameChose == 4)
            weightedGraph(GAME_DECK);
        else{
            cout << "Exiting Arcade...";
            exit(0);
        }
    }
    
    return 0;
}

void weightedGraph(Deck deck){
    cout << "Welcome to the weighted graph section!\n";
    
    int input;
    while(input != 2){
        cout << "Type '1' to see the weighted graph statistics.\n"<<
            "Type '2' to go back to the main menu.\n";
        cin >> input;
        if(input == 1){
            deck.printGraph();
        }
    }
}

void showScoreboard(AVL tree){
    cout << "Welcome to the scoreboard!\n";

    int input;
    while(input != 4){
        cout << "Type '1' for the scoreboard.\n"<<
            "Type '2' to see the scoreboard in Binary Tree Format(Rotated 90 degrees).\n" <<
            "Type '3' to see all the nodes in the tree and their relationship.\n" << 
            "Type '4' to go back to the main menu.\n";
        cin >> input;
        
        if(input == 1){
            tree.BalanceTree();
            tree.PrintScores();
        }
        if(input == 2){
            tree.PrintTree2D(10);
        }
        if(input == 3){
            tree.PrintTreeData();
        }
    }
}

//FUNCTION LOGIC
void gameLoopSJ(Deck& GAMEDECK, Deck& player, Deck& enemy){
    const string slapCard = "SLAP";
    //GAME MENU
    int difficulty = slapJackMenu();
    
    //ACTUAL GAME LOGIC
    GAMEDECK.createDeck(); //CREATE THE DECK OF 52 CARDS
    GAMEDECK.splitDeck(player, enemy); //SPLIT THE DECK BETWEEN THE TWO PLAYERS
    deque<string> pile;
    
    //CACHE VARIABLES
    int round = 1;
    string userDraw;
    bool userSlapped;
    bool enemySlapped;
    
    //STOP THIS LOOP WHEN EITHER OF THE DECK SIZES REACH 0
    while((player.cards.size() > 0 && enemy.cards.size() > 0)){
        //WHOSE DECK ARE WE DRAWING FROM
        Deck& turn = 
            round % 2 == 0 ?
                player : enemy;
        
        string who =
            round % 2 == 0 ?
                "Player" : "Enemy";

        //ROUND START ANNOUNCEMENT
        cout << "\n\n" << setw(20) << setfill(' ') << "ROUND " << round << "\n";
        cout << setw(20) << setfill(' ') << "Drawing from " << who << " deck.\n";
        cout << setw(40) << setfill('-') << " \n";
        //IF IT'S THE PLAYER'S TURN, MAKE THEM INTERACT TO DRAW A CARD
        if(round % 2 == 0){
            //cout << "It's YOUR turn.\n";
            //cin >> userDraw;
            
            string current = turn.pickCard(); //DRAW ONE CARD
            pile.push_back(current); //ADD TO THE PILE
            cout << "Card Drawn: " << current << "\n"; //OUTPUT CARD
            
            cout << "Type SLAP to slap this card, and anything else to pass!\n";
            cin >> userDraw;
            
            //IF THE USER SLAPS THE CARD,
            if(userDraw == slapCard){
                bool slapCorrect = timedInteraction(pile, current, difficulty);
                
                //IF THE USER CHOOSES TO SLAP THIS CARD AND IT'S A JACK
                if(current.find("Jack") != string::npos && slapCorrect){ //AND THEY SLAP A JACK
                    cout << "THE CARD YOU SLAPPED WAS A JACK!";
                    player.takePile(pile);
                }else{ //IF THE USER CHOOSES TO SLAP THIS CARD AND IT'S NOT A JACK
                    cout << "THE CARD YOU SLAPPED WAS NOT A JACK!\n";
                }
            }else{ //IF THE USER DOESN'T SLAP THIS CARD
                userSlapped = false;
                
                //AND IT'S A JACK
                if(current.find("Jack") != string::npos){
                    
                    //THE ENEMY WILL SLAP THE JACK
                    cout << "THE ENEMY HAS SLAPPED THE JACK!\n";
                    cout << pile.size() << " CARDS HAVE BEEN ADDED TO THE ENEMY DECK.\n";
                    enemy.takePile(pile);
                    
                    enemySlapped = true;
                }
            }
        }else{
            //ROUND IF IT'S THE ENEMY'S PULL AND WE DID NOT SLAP
            if(!userSlapped && !enemySlapped ){
                string current = turn.pickCard(); //DRAW ONE CARD
                pile.push_back(current); //ADD TO THE PILE
                cout << "Card Drawn: " << current << "\n"; //OUTPUT CARD

                //IF A JACK APPEARS
                if(current.find("Jack") != string::npos){
                    if(timedInteraction(pile, current, difficulty)){ //IF THE PLAYER PASSES THE TIMED INTERACTION
                        player.takePile(pile); //TAKE ALL THE CARDS FROM THE DECK
                    }else{
                        enemy.takePile(pile); //ELSE ADD THE CARDS TO THE ENEMY'S DECK
                    }

                    cout << "YOUR DECK SIZE: " << player.cards.size() << '\n'; //DISPLAY PLAYER'S DECK SIZE
                }
            }
        }
        
        //ADD ROUND COUNT
        round++;
        
        //DELAY SO THE USER CAN READ THE CARDS
        sleep(1);
    }
    
    //AFTER LOOP BREAKS, CHECK WHOSE DECK RAN OUT FIRST
    if(player.cards.size() <= 0){
        cout << "\n--------\nYOU LOST!!!\n--------\n";
    }
    else{
        cout << "\n---------\nYOU WIN!!!\n---------\n";
    }
}
void displayRulesSJ(){
    
}
int slapJackMenu(){
    const string startStr = "START";
    cout << "\n\nWELCOME TO SLAP-JACK!\n\n";
    welcomeMsg();
    
    //RULES
    cout << "To read the rules type 1, or type anything else to continue.";
    
    string rules;
    cin >> rules;
    
    if(rules == "1")
        displayRulesSJ();
    
    //START GAME
    cout << "\n\nTO START THE GAME TYPE '" << startStr << "'\n\n";
    
    string startGameStr;
    cin >> startGameStr;
    
    while(startGameStr != startStr){
        cin >> startGameStr;
    }

    cout << "\nGAME START.\n";
    
    string difficulty;
    while(difficulty != "Easy" && difficulty != "Medium" && difficulty != "Hard"){
        cout << "Please choose a Difficulty.\nType 'Easy', 'Medium', or 'Hard':  ";
        cin >> difficulty;
    }
    
    cout << "\nYou chose " << difficulty << " difficulty.\n";
    
    if(difficulty == "Easy")
        return 1;
    else if(difficulty == "Medium")
        return 2;
    else if(difficulty == "Hard")
        return 3;
    else
        return 1;
            
}

void gameLoopGF(Deck& GAMEDECK, Deck& player, Deck& enemy){
    //GAME MENU
    goFishMenu();
    
    //ACTUAL GAME LOGIC
    GAMEDECK.createDeck();
    GAMEDECK.assignGoFish(player,enemy);
    //CACHE VARIABLES
    int round = 1;
    int cardsTaken = 0;
    string userDraw;
    deque<string> pile;
    
    //STOP THIS LOOP WHEN EITHER OF THE PLAYERS REACH 4 OF A KIND
    string cardWon;
    while(!player.checkFour(cardWon) && !enemy.checkFour(cardWon)){
        //WHOSE DECK ARE WE DRAWING FROM
        Deck& turn = 
            round % 2 == 0 ?
                player : enemy;
        
        string who =
            round % 2 == 0 ?
                "Player" : "Enemy";
        
        //ROUND START ANNOUNCEMENT
        cout << "\n\n" << setw(20) << setfill(' ') << "ROUND " << round << "\n";
        
        cout << "\nYOUR DECK\n--------------\n";
        sort(player.cards.begin(), player.cards.end());
        player.printDeck();
        
        //cout << "\n ENEMY DECK\n---------\n";
        sort(enemy.cards.begin(), enemy.cards.end());
        //enemy.printDeck();
        
        //CHECK IF THE DECK IS EMPTY
        if(GAMEDECK.cards.size() == 0){
            for(string allCards : pile)
                GAMEDECK += allCards;
            
            cout << "\n\n NOBODY ACHIEVED FOUR OF A KIND BEFORE THE DECK RAN OUT OF CARDS.\nREFILLING THE DECK NOW.";
            std::random_shuffle(GAMEDECK.cards.begin(), GAMEDECK.cards.end());
        }
        
        //IF IT'S THE PLAYER'S TURN, MAKE THEM INTERACT TO DRAW A CARD
        if(round % 2 == 0){
            cout << "\nIt's YOUR turn. Please type what card value you would like to fish for.(EX: King)\n";
            cin >> userDraw;
            
            //TAKE ALL CARDS REQUESTED FROM ENEMY DECK
            if(player.takeFromDeck(player, enemy, userDraw, cardsTaken)){
                cout << "SUCCESSFULLY TOOK " << cardsTaken << " " << userDraw << "'s FROM THE ENEMY.";
                
                ScoreBoard.AddLeaf(stoi(userDraw) * cardsTaken);
            }
            else{
                cout << "Go Fish, Player!\n";
                cout << "You picked up a " << GAMEDECK.cards.front();
                player += GAMEDECK.cards.front();
                pile.push_back(GAMEDECK.cards.front());
                GAMEDECK.cards.pop_front();
            }
        }else{
            //PSEUDO AI
            cout << "\nIt's the ENEMY'S turn.\n";
            Card enemyCardRand;
            string enemyRand = enemyCardRand.getRandomCardVal();
            
            cout << "The enemy is asking you for " << enemyRand << "'s.\n";
            if(enemy.takeFromDeck(enemy, player, enemyRand, cardsTaken))
                cout << "THE ENEMY SUCCESSFULLY TOOK " << cardsTaken << " " << enemyRand << "'s FROM YOU.";
            else{
                cout << "The Enemy has to go fish!\n";
                enemy += GAMEDECK.cards.front();
                pile.push_back(GAMEDECK.cards.front());
                GAMEDECK.cards.pop_front();
            }
        }
        
        //ADD ROUND COUNT
        round++;
        
        //DELAY SO THE USER CAN READ THE CARDS
        sleep(1);
    }
    //CHECK WHO WON
    if(player.checkFour(cardWon)){
        cout << "\n-------------------------\nYOU FOUND FOUR " << cardWon << "'s AND WON!!!\n-------------------------\n";
    }
    else{
        cout << "\n-------------------------\nTHE ENEMY FOUND FOUR " << cardWon << "'s AND WON!!!\n-------------------------\n";
    }
}
void displayRulesGF(){ 
    
}
void goFishMenu(){
    const string startStr = "START";
    cout << "\n\nWELCOME TO GO FISH!\n\n";
    welcomeMsg();
    //RULES
    cout << "To read the rules type 1, or type anything else to continue.";
    
    string rules;
    cin >> rules;
    
    if(rules == "1")
        displayRulesGF();
    
    //START GAME
    cout << "\n\nTO START THE GAME TYPE '" << startStr << "'\n\n";
    
    string startGameStr;
    cin >> startGameStr;
    
    while(startGameStr != startStr){
        cin >> startGameStr;
    }

    cout << "\nGAME START.\n";
}

bool timedInteraction(deque<string> pile, string card, int difficulty){
    //INITIALIZE CLOCK
    using Clock = std::chrono::high_resolution_clock;
    
    //INITIALIZE WORD TO BE TYPED AND USER INPUT VARIABLE
    QuickEvent qe(difficulty);
    float inTime = qe.getTime();
    
    string test = qe.chooseRandom();
    string input;
    
    bool isJack = card.find("Jack") != string::npos;
    
    //START THE INTERACTION AND ANNOUNCE A JACK HAS BEEN FOUND
    std::cout << "\n ------------------------------ \n A " << card << " HAS APPEARED \n ------------------------------ \n";
    std::cout << "TYPE: ---" << test << "--- TO SLAP THE CARD!\n";
    
    //START TIMER
    auto start = Clock::now();
    cin >> input; // TAKE IN USER INPUT
    
    //END TIMER
    auto end = Clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
    //CHECK IF THE USER TYPED THE CORRECT WORD AND DID IT IN WITHIN THE TIME FRAME
    bool typedCorrect;
    
    //USER TYPED WRONG WORD
    if(input != test){
        cout << "\n\nYOU SPELLED THE WORD INCORRECTLY!\n";
        typedCorrect = false;
    }
    
    //IF THE USER TYPED THE CORRECT WORD, DID IT IN THE CORRECT TIMEFRAME AND IT WAS A JACK
    if((input == test && (float)ms/1000 <= inTime) && isJack){
        cout << "YOU SLAPPED THE JACK FIRST. IT TOOK YOU " << setprecision(2) << (float)ms/1000 << " seconds!\n";
        cout << pile.size() << " CARDS HAVE BEEN ADDED TO YOUR DECK.\n";
        
        //SCOREBOARD STUFF
        ScoreBoard.AddLeaf(hashFunc(card)); //HASHING INTO AN AVL TREE
        return true;
    }
    //IF THE USER TYPED THE CORRECT WORD, BUT THEY WERE TOO SLOW OR THE CARD WASN'T A JACK
    else{
        if(typedCorrect) 
            cout << "TOO SLOW! YOU TYPED THE WORD IN " << setprecision(2) << (float)ms/1000 << " seconds!\n";
        
        cout << pile.size() << " CARDS HAVE BEEN ADDED TO THE ENEMY DECK.\n";
        return false;
    }
    
    //return false;
}
int mainMenu(){
    cout << "----WELCOME TO THE ARCADE----\n";
    
    cout << ".\nType '1' for SLAPJACK\nType '2' for GO FISH.\nType '3' for SCOREBOARD.\nType '4' for WEIGHTED GRAPHS.\nType anything else to Exit the Arcade.\n";
    
    string input;
    cin >> input;
    
    if(input == "1" || input == "2" || input == "3" || input == "4")
        return stoi(input);
    
    return 0;
}

void welcomeMsg(){
    cout << "Please enter your name: ";
    cin  >> userName;
    ScoreBoard.SetUserName(userName);
}

int hashFunc(const string key){
    const std::vector<int> ABCtoNum = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};
    int hash = 1;
    
    int valOfLetter = 0;
    for(const auto& letter : key){
        valOfLetter += ABCtoNum[letter - 'A']; //CALCULATE WHAT VALUE THIS LETTER HAS BASED ON IT'S TELEPHONE NUMBER VALUE
    }
    hash = (12 + valOfLetter);

    return hash;
}