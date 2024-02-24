#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <algorithm>

#include <string>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

// https://www.cplusplus.com/reference/cstdlib/rand/

int main()
{
    int normal_wait_duration_minutes = 3600;
    std::string PASSWORD = "JESUS_ANGELS_MY_MOTHER_MARY";

    // 1. Print time:
    auto timer = std::chrono::system_clock::now();
    std::time_t startTime = std::chrono::system_clock::to_time_t(timer);
    std::cout<< std::ctime(&startTime) << "\n";

    std::string filename_normal_sleep_duration_minutes = "/etc/password_sleep_duration";

    std::ifstream file_normal_sleep_dur(filename_normal_sleep_duration_minutes);
    std::string whole_line1;
    if (file_normal_sleep_dur.is_open())
    {
        while (std::getline(file_normal_sleep_dur, whole_line1))
        {
            // Remove all spaces:
            std::string::iterator end_pos = std::remove(whole_line1.begin(), whole_line1.end(), ' ');
            whole_line1.erase(end_pos, whole_line1.end());
            normal_wait_duration_minutes = std::stoi(whole_line1);
            break;
        }
    }
    else
    {
        std::cout << "Unable to open file " << filename_normal_sleep_duration_minutes << "\n";
        return 0;
    }

    // 2. Print info:
    std::string outputFile = "~/Documents/password.txt";

    std::cout<< "1. Will sleep for: [" << normal_wait_duration_minutes << "] minutes (" << normal_wait_duration_minutes/60 << " hours). If computer sleeps, time is not counted.\n\n";
    std::cout<< "2. Then overwrite/create: [" << outputFile << "]\n";

    // 3. Sleep: (note that if computer sleeps, time is not counted)
    std::this_thread::sleep_for(std::chrono::minutes(normal_wait_duration_minutes));

    // 4. Save password to file:
    std::ofstream myfile(outputFile);
    myfile << PASSWORD;
    myfile.close();

    // std::cout<< PASSWORD << "\n";

    return 0;
}
