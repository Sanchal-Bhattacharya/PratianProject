#include "UserSecurity.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
using namespace std;

namespace gc
{
    namespace web
    {
        bool UserSecurity::is_base64(unsigned char c)
        {
            return (isalnum(c) || (c == '+') || (c == '/'));
        }

        std::string UserSecurity::base64_decode(std::string const &encoded_string)
        {
            size_t in_len = encoded_string.size();
            int i = 0;
            int j = 0;
            int in_ = 0;
            unsigned char char_array_4[4], char_array_3[3];
            std::string ret;

            while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_]))
            {
                char_array_4[i++] = encoded_string[in_];
                in_++;
                if (i == 4)
                {
                    for (i = 0; i < 4; i++)
                        char_array_4[i] = base64_chars.find(char_array_4[i]) & 0xff;

                    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
                    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
                    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

                    for (i = 0; (i < 3); i++)
                        ret += char_array_3[i];
                    i = 0;
                }
            }

            if (i)
            {
                for (j = 0; j < i; j++)
                    char_array_4[j] = base64_chars.find(char_array_4[j]) & 0xff;

                char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
                char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

                for (j = 0; (j < i - 1); j++)
                    ret += char_array_3[j];
            }

            return ret;
        }

        void UserSecurity::setParameters(std::string decoded_string)
        {
            this->auth_token = decoded_string.substr(0, 18);
            this->time_stamp = decoded_string.substr(18);
        }

        std::string UserSecurity::generateAuthToken()
        {
            boost::uuids::uuid uuid = boost::uuids::random_generator()();
            std::string id = boost::lexical_cast<std::string>(uuid);

            return id.substr(0, 18);
        }

        UserSecurity::UserSecurity(std::string encoded_string)
        {
            std::string decoded_string = base64_decode(encoded_string);
            setParameters(decoded_string);
        }

        bool UserSecurity::checkTime()
        {
            boost::posix_time::ptime server_time = boost::posix_time::microsec_clock::universal_time();

            string iso = to_iso_extended_string(server_time);
            cout << "Server Time: " << iso << "\n";
            cout << "Request Time: " << time_stamp << "\n";

            boost::posix_time::ptime time_stamp_object(boost::gregorian::date(std::stoi(time_stamp.substr(0, 4)), std::stoi(time_stamp.substr(5, 2)), std::stoi(time_stamp.substr(8, 2))), boost::posix_time::time_duration(std::stoi(time_stamp.substr(11, 2)), std::stoi(time_stamp.substr(14, 2)), std::stoi(time_stamp.substr(17))));
            boost::posix_time::time_duration diff = server_time - time_stamp_object;
            boost::int64_t diff_microseconds = abs(diff.ticks());

            if (diff_microseconds * 1.66667e-8 <= 10)
            {
                //cout<<"Within Range\n";
                return true;
            }
            //cout<<"Difference: "<<diff_microseconds*1.66667e-8 << "\n";
            return false;
        }

        std::string UserSecurity::getAuthToken()
        {
            return this->auth_token;
        }
    } // namespace web
} // namespace gc