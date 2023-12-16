#include "Deck.h"

//CREATE A DECK OF 52 UNIQUE CARDS
void Deck::createDeck(){
        Card card;
        
        deque<string> cardList = card.getCardList();
        deque<string> suitList = card.getSuitList();
        int maxCards  = cardList.size();
        int maxSuits  = suitList.size();
        int maxUnique = card.getUniqueCards();
        
        string whatCard;
        for(int i = 0; i < maxCards; i++){
            for(int j = 0; j < maxSuits; j++){
                //map<string,string> newCard = make_pair(cardList[i], suitList[j]);
                whatCard = cardList[i] + suitList[j];
                
                m_cards.insert({cardList[i], maxUnique}); //MAP
                goFishCards.push(whatCard); //QUEUE FOR GO FISH
                
                *this += whatCard;//DEQUE FOR SLAPJACK
            }
        }
        
        hasMadeDeck = true;
    }
    
//FILL THE DECK AND SHUFFLE IT
void Deck::setUpStandard(){
    //FIRST CHECK IF THE DECK HAS BEEN CREATED
    if(!hasMadeDeck)
        createDeck(); //IF NOT, MAKE IT

    //SHUFFLE THE DECK
    std::random_shuffle(cards.begin(), cards.end());
}
    
//SPLIT DECK EVENLY BETWEEN TWO PLAYERS
void Deck::splitDeck(Deck& player, Deck& enemy){  
    setUpStandard();

    //DISTRIBUTE THE AMOUNT OF CARDS BETWEEN PLAYERS
    for(int i = 0; i < default_size; i++){
        if(i % 2 == 0)
            player.cards.push_back(cards[i]);
        else
            enemy.cards.push_back(cards[i]);
    }
}

//GIVE FOUR RANDOM CARDS
void Deck::assignGoFish(Deck& player, Deck& enemy){
    setUpStandard();

    //DISTRIBUTE 4 RANDOM CARDS TO BOTH PLAYERS
    int i = 0;

    for(i = 0; i < m_goFishDeckSize*2; i++){
        Deck& who =
            i % 2 == 0?
                player : enemy;

        who += cards[i];
        *this -= cards[i];
    }

    /*cout << "PLAYER\n";
    player.printDeck();
    cout << "\n\nENEMY\n";
    enemy.printDeck();
    cout << "\n\nDECK";
    printDeck();*/
}

//CHECK IF THE PLAYER'S DECK CONTAINS 4 OF A KIND
bool Deck::checkFour(string whatCard){
    list<string> cardValues;
    map<string,int> cardReccuring;
    set<string, int> cardFreq;

    for(int i = 0; i < m_goFishDeckSize; i++){
        cardValues.push_back(getCardValue(cards[i])); //RETAIN ALL THE CARD VALUES
    }

    //COUNT THE DUPLICATES
    for(const auto& card : cardValues){
        cardReccuring[card]++;
    }

    //CHECK IF THE DUPLIACTES = 4
    for(const auto &[cardVal, cardCount] : cardReccuring){
        if(cardCount == 4){
            whatCard = cardVal;
            return true;
        }
    }
    return false;
}

//RETRIEVE THE CARD VALUE OF THE CARD WITHOUT THE SUIT
string Deck::getCardValue(string whatCard){
    string::size_type pos = whatCard.find("of");

    if (pos != std::string::npos)
    {
        return whatCard.substr(0, pos - 1);
    }
    else
    {
        return whatCard;
    }
}

//ADD CARDS FROM A PILE INTO YOUR DECK
void Deck::takePile(deque<string>& pile){
    for(string card : pile)
        cards.push_back(card);

    pile.clear();
}

//PRINT DECK
void Deck::printDeck(){
    for(string cards : cards)
       cout << cards << '\n';
}

//PRINT DECK STATISTICS, CARD VALUES, AND HOW MANY OF EACH CARD TYPE
void Deck::printDeckStats(){
    for(const auto &[cardVal, suit] : m_cards){
        cout << "CARD: " << cardVal << " REMAINING: " << suit << '\n';
    }
}

//RANDOMLY PICK A CERTAIN NUMBER OF CARDS
void Deck::pickCards(int num){
    //cout << "YOUR " << num << " CARDS\n---------\n";
    for(int i = 0; i < num; i++){
        const int random = (rand() % (cards.size()));

        //ADD THE PICKED CARDS TO A LIST
        pickedCards.push_back(cards[random]);

        //OUTPUT THE GIVEN CARD
        cout << cards[random] << '\n';

        //DELETE THE CARD FROM THE DECK
        deque<string>::iterator itr =  cards.begin() + random;
        cards.erase(itr);
    }
}

//PICK ONE RANDOM CARD
string Deck::pickCard(){
    string pickedCard = "error";
    if(cards.size() > 0){
        int random = (rand() % (cards.size()));

        //ADD THE PICKED CARDS TO A LIST
        pickedCards.push_back(cards.front());

        //DELETE THE CARD FROM THE DECK
        deque<string>::iterator itr = cards.begin() + 0;
        //cout << "DELETED CARD: " << cards[random];
        pickedCard = cards[0];

        cards.erase(itr);

    }

    return pickedCard;
}

//CHECKS FOR CARD AND ADDS IT
bool Deck::takeFromDeck(Deck& to, Deck& from, string card, int& cardsTaken){
    //IF CONTAINS NAME OF CARD VALUE, GIVE TO DECK
    //string::size_type pos = card.find("of");
    //string val = card.substr(0, pos);

    //KEEP GIVING THE PLAYER THE CARDS UNTIL THE DECK HAS NO MORE
    string indx;
    bool didFind = false;
    cardsTaken = 0;

    while(findCard(to, from, card, indx)){
        //to.cards.push_back(indx); //ADD CARD TO THE DECK

        didFind = true;
        cardsTaken++;
    }

    return didFind;
}

//CHECKS FOR CARD AND DELETES IT
bool Deck::findCard(Deck& to, Deck& from, string whatCard, string indx){
    bool didFind = false;

    deque<string> currentCardVals;

    //SAVE THE CARD VALUES
    for(int i = 0; i < from.cards.size(); i++){
        currentCardVals.push_back(getCardValue(from.cards[i]));
    }

    //cout << "\n\nTHESE ARE THE VALUES WE RETAIN\n";
    //for(string whatCards : currentCardVals)
    //  cout << "[" << whatCards << "]\n";

    //TEST THE CARD BEING REQUESTED AGAINST THE CARDS YOU HAVE
    deque<string>::iterator itr;
    if(find(currentCardVals.begin(), currentCardVals.end(), whatCard) != currentCardVals.end())
        itr  = find(currentCardVals.begin(), currentCardVals.end(), whatCard);
    else
        return false;

    //cout << "THE DISTANCE IS " << distance(currentCardVals.begin(), itr) << '\n';
    //cout << "THE END() is " << *currentCardVals.end();

    //string* indxPtr = nullptr;
    //IF THE CARD VALUE DID FIND A MATCH, DELETE IT AT THAT INDEX
    if(itr != currentCardVals.end()){
      deque<string>::iterator itrC = from.cards.begin() + distance(currentCardVals.begin(), itr);

      indx = *itrC;
      to.cards.push_back(indx);


      //itrC = from.cards.erase(itrC);
      itrC = from.cards.erase(std::remove(from.cards.begin(), from.cards.end(), *itrC), from.cards.end());
      indx = "";
      //indx = "";
      //from.cards.erase(itrC);
      didFind = true;
    }

    return didFind;
}