import round;
import word;
import user;
import <vector>;

using game::Round;
using game::WordList;
using game::User;


//the only public funtion that will do everyting by calling other functions that are private
void Round::StartRound(std::vector<User>& players, const WordList& wordList);