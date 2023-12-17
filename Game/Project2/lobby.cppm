export module lobby;
import player;

import <vector>;
import <deque>;
import <string>;
import <cstdint>;


namespace game_logic
{
    export class Lobby
    {
    public:
        enum class GameDifficulty : uint8_t				//difficulty for the game
        {
            NoDifficulty = 0b00,
            Easy = 0b01,
            Medium = 0b10,
            Hard = 0b11
        };
        enum class GameLanguage : uint8_t				//language for the game
        {
            English = 0b00,
            Romanian = 0b01,
            Spanish = 0b10
        };

    public:
        Lobby() = default;
        ~Lobby() = default;

        void SetDifficulty(const uint8_t difficulty);				//sets the game difficulty at the start of the game
        void SetLanguage(const uint8_t language);              //sets the game language at the start of the game
        void SetPlayers(const std::vector<Player>& players);  	    //sets the players at the start of the game

        GameLanguage GetLanguage() const;                           //for checking the language 
        GameDifficulty GetDifficulty() const;						//for checking the difficulty
        std::vector<Player>& GetPlayers();						//for checking the players

        void AddPlayer(const std::string& name);                      //adds a player to the lobby
        void RemovePlayer(const std::string& name);                   //removes a player from the lobby

    private:
        std::vector<Player> m_players{};
        GameDifficulty m_difficulty{};
        GameLanguage m_language{};
    };


}
