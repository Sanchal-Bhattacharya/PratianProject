#pragma once
#include <stdexcept>
#include <string>

using namespace std;

namespace gc
{
	class GCException : public logic_error
	{
	public:
		GCException(const std::string &msg) : logic_error(msg)
		{
		}
	};
} // namespace gc
