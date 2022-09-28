#include <sstream>
#include <openssl/sha.h>

#include "Hash.h"
#include "Random.h"

using namespace std;

namespace gc
{
	namespace web
	{

		//hash:: hash(){}
		Hash::Hash(string line) : line(line)
		{
			line = line;
		}
		string Hash ::to_hex(unsigned char s)
		{
			stringstream ss;
			ss << hex << (int)s;
			return ss.str();
		}

		string Hash ::sha256()
		{
			unsigned char hash[SHA256_DIGEST_LENGTH];
			SHA256_CTX sha256;
			SHA256_Init(&sha256);
			SHA256_Update(&sha256, line.c_str(), line.length());
			SHA256_Final(hash, &sha256);

			string output = "";
			for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
			{
				output += to_hex(hash[i]);
			}
			return output;
		}
	} // namespace web
} // namespace gc