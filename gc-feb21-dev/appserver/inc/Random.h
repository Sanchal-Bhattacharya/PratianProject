#pragma once
#include <string>

using namespace std;

namespace gc
{
	namespace web
	{
		class Random
		{
		public:
			Random();
			string hexConversion(long decimal_number);
			string generateSalt();
		};
	} // namespace web
} // namespace gc