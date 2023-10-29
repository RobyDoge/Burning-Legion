export module user;
import <string>;
import points;


namespace game {
	
	export class User {
	public:
		User();												//default constructor
		~User();											//destructor

		std::string getName() const;						//returns m_name
		std::string getPassword() const;					//returns m_password
		Points getPoints() const;							//returns m_points

		void setName(const std::string& name);				//sets m_name
		void setPassword(const std::string& password);		//sets m_password
		void setPoints(const Points& points);				//sets m_points


	private:
		std::string m_name;									//the name and display name of a user
		std::string m_password;								//the password for logging in
		Points m_points;									//an object for storing different type of points
	};
}