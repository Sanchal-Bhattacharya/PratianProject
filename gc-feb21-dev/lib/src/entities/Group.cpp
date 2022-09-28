#include "Group.h"

namespace gc
{
	namespace entities
	{
		Group::Group(std::string name, std::string email)
			: _name(name)
		{
			_emailList.push_back(email);
		}
		/*void Group::setEmail(std::vector<std::string> email)
		{
            _emailList = email;
        }
		*/
		void Group::setName(std::string name)
		{
			_name = name;
		}
		std::vector<std::string> Group::getEmailList() const
		{
			return _emailList;
		}
		std::string Group::getName() const
		{
			return _name;
		}
		long long int Group::getGroupID() const
		{
			return _groupID;
		}
	} // namespace entities
} // namespace gc
