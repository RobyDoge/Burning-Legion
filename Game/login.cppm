export module login;
import <iostream>;
import <string>;
import user; 

using game::User;

namespace game
{
    export class Login
    {
    public:
        Login(User& user); 
        ~Login();          

        bool Authenticate(const std::string& password) const;
        void ChangePassword(const std::string& newPassword);
        std::string ReadPassword() const;

    private:
        User& m_user; 
    };
}

