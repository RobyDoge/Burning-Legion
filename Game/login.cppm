export module login;
import user;

import <iostream>;
import <string>;

using game::User;

namespace game
{
    export class Login
    {
    public:
        Login(const User& user);
        ~Login();          

        bool Authenticate(const std::string& password) const;
        void ChangePassword(const std::string& newPassword);
        void ReadPassword(std::ostream& output) const;

    private:
        User m_user; 
    };
}

