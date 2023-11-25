export module login;
import user;

import <iostream>;
import <string>;

using server::User;

namespace server
{
    export class Login
    {
    public:
        Login(const User& user);							                //default constructor
        ~Login();                                                           //destructor

        bool Authenticate(const std::string& username,const std::string& password) const;               //compares the provided password with the stored password 
        void ChangePassword(const std::string& newPassword);                //changes the password
        void ReadPassword(std::ostream& output) const;                      //reads a password from the user while obscuring the input

    private:
        User m_user; 
    };
}

