#include <unistd.h>
#include <fstream>
#include <random>
#include "Random.h"

using namespace std;

namespace gc
{
	namespace web
	{
		Random::Random() {}

		// string Random::generateSalt()
		// {
		// 	char buffer1[16];
		// 	//int length =8;
		// 	unsigned char buffer[8];
		// 	ifstream urandom("/dev/urandom", ios::in | ios::binary); //Open stream
		// 	if (urandom)											 //Check if stream is open
		// 	{
		// 		urandom.read((char *)buffer, 8); //Read from urandom
		// 		if (urandom)					 //Check if stream is ok, read succeeded
		// 		{
		// 			//    std::cout << "Read random value: " << buffer<< std::endl;
		// 			//	sprintf(buffer1,"%02x",buffer);
		// 			cout << "Reading random values" << endl;
		// 		}
		// 		else //Read failed
		// 		{
		// 			std::cerr << "Failed to read from /dev/urandom" << std::endl;
		// 		}
		// 		urandom.close(); //close stream
		// 	}
		// 	for (int j = 0, i = 0; i < 8; i++)
		// 	{
		// 		sprintf(buffer1 + j, "%02x", buffer[i]);
		// 		j += 2;
		// 	}

		// 	cout << buffer1 << endl;
		// 	return string(buffer1);
		// }

		string Random::hexConversion(long decimal_number)
		{
			string hex_num = "";
			int remainder;
			char hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
			while(decimal_number>0)
        	{
            	remainder = decimal_number % 16;
            	hex_num = hex[remainder] + hex_num;
            	decimal_number = decimal_number/16;
        	}

			return hex_num;
		}
		
		string Random::generateSalt()
		{
			random_device rd;
			uniform_int_distribution<long> dist;
			//return to_string(dist(rd));
			return hexConversion(dist(rd));
		}
	} // namespace web
} // namespace gc