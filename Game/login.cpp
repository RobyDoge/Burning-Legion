import login;
import <iostream>;

using game::Login;

Login::Login(User& user) : m_user(user) {}

Login::~Login() = default;

bool Login::Authenticate(const std::string& password) const 
{
    return m_user.GetPassword() == password;
}

void Login::ChangePassword(const std::string& newPassword)
{
    m_user.SetPassword(newPassword);
}

void Login::ReadPassword() const
{
    std::string enteredPassword;
    std::cout << "Enter your password: ";
    char c;
    while ((c = std::getchar()) != '\n') {
        if (c != '\r') {
            enteredPassword.push_back(c);  
            std::cout << "*"; 
        }
    }
    std::cout << std::endl;
}
