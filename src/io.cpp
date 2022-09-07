#include "io.h"

#include <iostream>
#include <regex>

vector<string> grep_dir(const string path, const string regex_name, const bool recursive) {
    vector<string> results = {};
    #ifdef __linux__
    std::filesystem::path sandbox = filesystem::path(path);
    if (recursive) {
        //std::cout << "\nrecursive_directory_iterator:\n";
        for (auto const& dir_entry : std::filesystem::recursive_directory_iterator{sandbox}) 
        {
            //std::cout << dir_entry << '\n';
            string dir = dir_entry.path().filename().string();
            regex str_expr (regex_name);
            if (regex_match(dir, str_expr)) {
                results.push_back(dir_entry.path().filename().string());
            }
        }       
    } else {
        //std::cout << "directory_iterator:\n";
        // directory_iterator can be iterated using a range-for loop
        for (auto const& dir_entry : std::filesystem::directory_iterator{sandbox}) 
        {
            string dir = dir_entry.path().filename().string();
            regex str_expr (regex_name);
            if (regex_match(dir, str_expr)) {
                results.push_back(dir_entry.path().filename().string());
            }
        }
    }
        //const std::filesystem::path sandbox{"sandbox"};
  
        /*
        std::cout << "\ndirectory_iterator as a range:\n";
        // directory_iterator behaves as a range in other ways, too
        std::ranges::for_each( std::filesystem::directory_iterator{sandbox},
                               [](const auto& dir_entry) {
                                 std::cout << dir_entry << '\n';
                               } );
        */
    #elif _WIN32
         
    #elif __APPLE__
        
    #else
    #endif

    return results;
}
