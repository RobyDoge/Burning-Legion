export module lobby;
export import user;

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
            Hard = 0b10
        };
    public:
        Lobby();
        std::string GetIdLobby() const;
        void AddUser(const std::string& name, const uint16_t bestScore, const std::list<int16_t>& lastMatchesPoints);
        void StartGame();
        void SetDifficulty(const GameDifficulty difficulty);						//sets the game difficulty at the start of the game
        GameDifficulty GetDifficulty() const;										//for checking the difficulty


    private:
        void GenerateIdLobby();
    private:
        static constexpr uint8_t ID_SIZE = 5;
        std::vector<User> m_players{};
        std::string m_idLobby{};
        GameDifficulty m_difficulty{};
    };
}

