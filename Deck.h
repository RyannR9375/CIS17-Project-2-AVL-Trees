//MAJOR LIBRARIES
#include <cstdlib>
#include <iostream>
#include <iomanip>

//SUPPORTING FUNCTION LIBRARIES
#include <chrono>
#include <random>
#include <algorithm>
#include <unistd.h>

//CONTAINER LIBRARIES
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <list>

using namespace std;

struct Card{
public:
    map<string,string> newCard;
    string thisCard;

    Card(){
        //thisCard = getRandomCard();
    }

    inline deque<string> getCardList() { return m_card; }
    inline deque<string> getSuitList() { return m_suit; }
    inline int getUniqueCards() { return numOfUniqueCards; }
    
    inline string getRandomCardVal(){
        const int randomCard = rand()%(m_card.size());

        return m_card.at(randomCard);
    }
private:
    const deque<string> m_card ={
        "Ace","2","3","4","5","6","7","8","9","10","Jack","Queen","King"
    };
    
    const deque<string> m_suit ={
        " of Clubs",
        " of Spades",
        " of Hearts",
        " of Diamonds"
    };

    inline string getRandomCard(){ 
        const int randomCard = rand()%(m_card.size()) + 1; //RANDOM INDEX CARD
        const int randomSuit = rand()%(m_suit.size()) + 1; //RANDOM INDEX SUIT
        
        // CARD NUMBER (KEY)        = CARD SUIT (VALUE)
        newCard[m_card[randomCard]] = m_suit[randomSuit];
        
        return newCard[m_card[randomCard]] + newCard.at(m_card[randomCard]);
    }
    
    const int numOfUniqueCards = m_suit.size();
};
        
class Deck{
public:
    typedef map<string,int> card;
    deque<string> cards;
    list<string> pickedCards;
    
    queue<string> goFishCards;
    const string goalCard = "Jack";
    
    //CONSTRUCTORS
    Deck(){

    }
    
    //OVERLOAD OPERATORS
    Deck& operator+=(string whatCard){
        cards.push_back(whatCard);
        
        return *this;
    }
    
    Deck& operator-=(string whatCard){
        deque<string>::iterator itr = find(cards.begin(), cards.end(), whatCard);
        
        if(itr != cards.end())
            cards.erase(itr);
        
        return *this;
    }
    
    Deck& operator--(){
        cards.pop_back();
        
        return *this;
    }
    
    //PUBLIC CLASS FUNCTIONS
    void createDeck();
    void setUpStandard();
    void splitDeck(Deck&, Deck&);
    void assignGoFish(Deck&, Deck&);
    void takePile(deque<string>&);
    void printDeck();
    void printDeckStats();
    void pickCards(int);
    void printGraph();
    
    bool checkFour(string);
    bool takeFromDeck(Deck&, Deck& , string, int&);
    
    string getCardValue(string);
    string pickCard();
    
    //GET FUNCTIONS
    inline int inDeck(){ return cards.size(); }
private:
    //PRIVATE MEMBER VARIABLES
    const static int default_size = 52;
    const int m_goFishDeckSize   = 7;
    const int m_goFishMatch = 4;
    int m_size = 0;
    card m_cards = {};
    bool hasMadeDeck;
    vector<pair<string, int>> m_weightedGraph[default_size];
    void populateCardIndexes();
    
    //PRIVATE MEMBER FUNCTIONS
    bool findCard(Deck&, Deck&, string, string);
    int addEdge(string vertex1, string vertex2, int weight);
    void determineEdges();
    map<string,int> m_cardIndexes;
};