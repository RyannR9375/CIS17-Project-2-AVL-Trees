#include <set>
#include <string>

class QuickEvent{
private:
    //PRIVATE MEMBER VARIABLES
    string m_difficulty;
    const float m_easyTime = 7;
    const float m_mediumTime = 5;
    set<string>* wordSetPtr = &wordsEasy;
    
public:
    //CONSTRUCTORS
    QuickEvent(){
        m_difficulty = "Easy";
    }
    
    QuickEvent(int difficulty){
        if(difficulty == 1){
            m_difficulty == "Easy";
            wordSetPtr = &wordsEasy;
        }
        else if(difficulty == 2){
            m_difficulty == "Medium";
            wordSetPtr = &wordsMedium;
        }
        else if(difficulty == 3){
            m_difficulty == "Hard";
            wordSetPtr = &wordsHard;
        }
        else{
            m_difficulty == "Easy";
            wordSetPtr = &wordsEasy;
        }
    }
    
    //WORD BANKS
    set<string> wordsEasy = {
        "Sugar",
        "Fish",
        "Shark",
        "Sock",
        "Fudge",
        "Cow",
        "Bat",
        "Kiss",
        "Jelly"
    };
    set<string> wordsMedium = {
        "Fortune",
        "Butter",
        "Burger",
        "Defend",
        "Counter",
        "Penguin",
        "Button",
        "Dinosaur",
        "Country",
        "Monster"
    };
    set<string> wordsHard = {
        "Gingerbread",
        "Megalodon",
        "FrickerFracker",
        "Portuguese",
        "Distinguish",
        "Collaborate",
        "Mischievous",
        "Nauseous",
        "Onomatopoeia"
    };
    
    //PUBLIC MEMBER FUNCTIONS
    inline string chooseRandom(){
        auto it = wordSetPtr->begin();
        int random = rand()% + wordSetPtr->size();
        
        for(int i=0;i < random;i++)
            it++;
        
        return *it;
    }
    inline float getTime() { 
        if(m_difficulty == "Easy") return m_easyTime;
        else return m_mediumTime;
    }
};