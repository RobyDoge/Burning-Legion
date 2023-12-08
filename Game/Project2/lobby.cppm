export module lobby;
import user;

import <cstdint>;
import std;

namespace server
{
    export class Lobby
    {
    public:
        enum class GameDifficulty : uint8_t				//difficulty for the game
        {
            Easy = 0b00,
            Medium = 0b01,
            Hard = 0b10,
            NoDifficulty = 0b11
        };
    public:
        Lobby();                                                        //constructor;
        std::string GetIdLobby() const;                                 //retuns the lobby Id
        std::vector<User>& GetPlayers();
        void AddPlayer(const std::string& name, const uint16_t bestScore, const std::deque<int16_t>& lastMatchesPoints);       //adds a player to the lobby
        void SetDifficulty(const GameDifficulty difficulty);						//sets the game difficulty at the start of the game
        GameDifficulty GetDifficulty() const;										//for checking the difficulty

    private:
        void GenerateIdLobby();                                                     //randomly generates a lobby id

    private:
        static constexpr uint8_t ID_SIZE = 5;

    private:
        std::vector<User> m_players{};
        std::string m_idLobby;
        GameDifficulty m_difficulty;
    };
}

