import login;
import user;
import <iostream>;


using game::Login;
using game::User;

Login::Login(const User& user):
	m_user{user}
{}

Login::~Login() = default;

bool Login::Authenticate(const std::string& password) const 
{
    return m_user.GetPassword() == password;
}

void Login::ChangePassword(const std::string& newPassword)
{
    m_user.SetPassword(newPassword);
}

void Login::ReadPassword(std::ostream& output) const
{
    std::string enteredPassword;
    std::cout << "Enter your password: ";
    char c;
    while ((c = std::getchar()) != '\n') {
        if (c != '\r') {
            enteredPassword.push_back(c);  
            output << "*";
        }
    }
}
