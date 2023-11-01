module user;
import <format>;

using game::User;
using game::Points;

User::User()
{
    m_name = "";
    m_password = ""; 
}

User::~User()
{
    // Destructor
}

std::string User::GetName() const
{
    return m_name;
}

std::string User::GetPassword() const
{
    return m_password;
}

Points User::GetPoints() const
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