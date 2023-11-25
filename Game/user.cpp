module user;

using server::User;
using server::Points;

User::User()
{
    m_name = "";
    m_password = ""; 
}

User::~User()
{
    // Destructor
}

User::User(const User& other) :
    m_name{ other.m_name },
    m_password{ other.m_password },
    m_points{ other.m_points }
{
}

User& User::operator=(const User& other)
{
    User tempUser{ other };
    Swap(tempUser);
    return *this;
}

User::User(User&& other) noexcept
{
    this->Swap(other);
}

User& User::operator=(User&& other) noexcept
{
    this->Swap(other);
    return *this;
}

void User::Swap(User& other) noexcept
{
    using std::exchange;
    m_password = exchange(other.m_password, m_password);
    m_name = exchange(other.m_name, m_name);
    m_points.Swap(other.m_points);
}

std::string User::GetName() const
{
    return m_name;
}

std::string User::GetPassword() const
{
    return m_password;
}

Points& User::GetPoints()
{

    return m_points;
}

void User::SetName(const std::string& name)
{
    m_name = name;
}

void User::SetPassword(const std::string& password)
{
    m_password = password;
}

void User::SetPoints(const Points& points)
{
    m_points = points;
}