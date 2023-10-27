module user;
import <format>;
using game::User;

User::User() {
    m_name = "";
    m_password = ""; 
}

User::~User() {
    // Destructor
}

std::string User::getName() {
    return m_name;
}

std::string User::getPassword() {
    return m_password;
}

Points User::getPoints() {
    return m_points;
}
