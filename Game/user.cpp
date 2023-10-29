module user;
import <format>;

using game::User;
using game::Points;

User::User() {
    m_name = "";
    m_password = ""; 
}

User::~User() {
    // Destructor
}

std::string User::getName() const {
    return m_name;
}

std::string User::getPassword() const {
    return m_password;
}

Points User::getPoints() const {

    return m_points;
}

void User::setName(const std::string& name) {
    m_name = name;
}

void User::setPassword(const std::string& password) {
    m_password = password;
}

void User::setPoints(const Points& points) {
    m_points = points;
}