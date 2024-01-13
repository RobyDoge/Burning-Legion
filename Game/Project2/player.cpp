module player;


using game_logic::Player;
using game_logic::Points;

Player::Player()
{
    m_name = "";
}

Player::~Player()
{
    // Destructor
}

Player::Player(const Player& other) :
    m_name{ other.m_name },
    m_points{ other.m_points }
{
}

Player& Player::operator=(const Player& other)
{
    Player tempUser{ other };
    swap(tempUser);
    return *this;
}

Player::Player(Player&& other) noexcept
{
    this->swap(other);
}

Player& Player::operator=(Player&& other) noexcept
{
    this->swap(other);
    return *this;
}

void Player::swap(Player& other) noexcept
{
    using std::exchange;
    m_name = exchange(other.m_name, m_name);
    m_points.swap(other.m_points);
}

std::string Player::GetName() const
{
    return m_name;
}

Points Player::GetPoints() const
{
    return m_points;
}

Points& Player::ChangePoints()
{
	return m_points;
}

void Player::SetName(const std::string& name)
{
    m_name = name;
}


void Player::SetPoints(const Points& points)
{
    m_points = points;
}

void game_logic::swap(Player& first, Player& second) noexcept
{
    first.swap(second);
}
