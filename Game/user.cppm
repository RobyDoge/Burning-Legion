export module user;
export import points;

import <string>;


namespace server 
{
	export class User 
	{
	public:
		User();												//default constructor
		~User();											//destructor
		User(const User& other);							//copy constructor
		User& operator=(const User& other);					//operator= for copy
		User(User&& other) noexcept;
		User& operator=(User&& other) noexcept;
		void Swap(User& other) noexcept;					//swap for copy and move  operators

		std::string GetName() const;						//returns m_name
		std::string GetPassword() const;					//returns m_password
		Points& GetPoints();								//returns m_points

		void SetName(const std::string& name);				//Sets m_name
		void SetPassword(const std::string& password);		//Sets m_password
		void SetPoints(const Points& points);				//Sets m_points


	private:
		std::string m_name;									//the name and display name of a user
		std::string m_password;								//the password for logging in
		Points m_points;									//an object for storing different type of points
	};
}