#pragma once

#include <string>

using namespace std;

namespace gc
{
	namespace web
	{
		class Hash
		{
			string line;

		public:
			Hash(string line);
			string to_hex(unsigned char s);
			string sha256();
		};
	} // namespace web
} // namespace gc