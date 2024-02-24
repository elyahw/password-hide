#include <iostream>
#include <string>
#include <regex>

#include <vector>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm>

// Sleeping:
#include <chrono>
#include <thread>

// https://www.cplusplus.com/reference/cstdlib/rand/
// Note it should only print the password nothing else.

std::vector<std::string> split(std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;
    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }
    res.push_back (s.substr (pos_start));
    return res;
}

int main()
{
    std::time_t tnow = std::time(0);
    std::tm* date = std::localtime(&tnow);

    std::string PASSWORD = "JESUS_ANGELS_MY_MOTHER_MARY"; // put password here..
    bool today_on_list = false;
    bool printer_debug = false;
    bool sleep = false;
    int sleep_time_minutes = 360;

    int hour = date->tm_hour;
    int minute = date->tm_min;
    int day = date->tm_wday; // 0 is Sunday, 6 is Saturday
    int year = date->tm_year + 1900;
    int month = date->tm_mon + 1;
    int mday = date->tm_mday;

    if (printer_debug)
    {
        std::cout << "year = " << year << "\n";
        std::cout << "mon  = " << month << "\n";
        std::cout << "mday = " << mday << "\n";
        std::cout << "hour = " << hour << "\n";
        std::cout << "min  = " << minute << "\n";
        std::cout << "day  = " << day << "\n\n";
    }

    std::string filename_allow_days = "/etc/password_days";

    std::string whole_line;
    std::ifstream file_days_to_read (filename_allow_days);
    int counter = 0;
    if (file_days_to_read.is_open())
    {
        while (std::getline(file_days_to_read, whole_line))
        {
            counter++;

            // Remove spaces only from beginning/end of string:
            whole_line = std::regex_replace(whole_line, std::regex(" +$"), "");
            whole_line = std::regex_replace(whole_line, std::regex("^ +"), "");

            // Instead: Split by ' ': (works on a single space only)
            std::vector<std::string> parts = split(whole_line, " ");
            std::string line = parts[0];

            if (printer_debug)
            {
                std::cout << "> Line = [" << line << "]\n";
                std::cout << "----- Parts size = " << parts.size() << '\n';
            }

            if (line == "")
            {
                if (printer_debug)
                {
                    std::cout << ">> Empty line detected..\n";
                }
                continue;
            }

            std::string read_year = line.substr(0, 4);
            std::string read_mon = line.substr(4, 2);
            std::string read_day = line.substr(6, 2);

            int num_year = std::stoi(read_year);
            int num_mon = std::stoi(read_mon);
            int num_day = std::stoi(read_day);

            if (printer_debug)
            {
                std::cout << "year = " << read_year << '\n';
                std::cout << "mon  = " << read_mon << '\n';
                std::cout << "day  = " << read_day << '\n';
                std::cout << num_year << '\n';
                std::cout << num_mon << '\n';
                std::cout << num_day << "\n\n";
            }

            if (year == num_year)
            {
                if (month == num_mon)
                {
                    if (mday == num_day)
                    {
                        if (parts.size() > 1)
                        {
                            today_on_list = false;
                            sleep = true;
                            sleep_time_minutes = std::stoi(parts[1]);
                            std::cout << "Today is listed in [" << filename_allow_days << "] on line " << counter << ": [" << whole_line << "].\n";
                        }
                        else
                        {
                            today_on_list = true;
                            std::cout << "Today is listed in [" << filename_allow_days << "] on line " << counter << ": [" << whole_line << "]. No password for the whole day.\n";
                        }
                        break;
                    }
                }
            }
        }
        file_days_to_read.close();
    }
    else
    {
        std::cout << "Unable to open file " << filename_allow_days << "\n";
        return 0;
    }

    if (day != 0 && day != 6 && !today_on_list) // Exclude Sunday & Saturday & whichever days defined in [filename_allow_days]
    {
        if (hour >= 6 && hour < 17) // (From exactly 6:00am until 5:00pm)
        {
            if (sleep)
            {
                std::cout << "You will need to wait for [" << sleep_time_minutes << "] minutes (" << sleep_time_minutes/60 << " hours).\n";
                std::this_thread::sleep_for(std::chrono::minutes(sleep_time_minutes));
            }
            std::cout << PASSWORD << "\n";
        }
        else
        {
            std::cout << "Out of work hours. No password.\n";
        }
    }
    else
    {
        if (!today_on_list)
        {
            std::cout << "Passwords not allowed on Saturdays and Sundays. No password.\n";
        }
    }

    return 0;
}

