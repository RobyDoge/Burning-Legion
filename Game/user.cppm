export module user;
import <string>;
import "Points.h";

namespace game {
	export class User {
	public:
		User();
		~User();
		std::string getName();
		std::string getPassword();
		Points getPoints();
		void setName(const std::string& name);
		void setPassword(const std::string& password);
		void setPoints(const Points& points);
	private:
		std::string m_name;
		std::string m_password;
		Points m_points;
	};
}