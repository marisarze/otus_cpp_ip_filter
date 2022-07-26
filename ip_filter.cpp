#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "ip_filter.h"

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    r.push_back(str.substr(start));
    return r;
}


std::vector<std::vector<std::string>> get_ip_pool(std::istream &input)
{
    std::vector<std::vector<std::string>> ip_pool;
    std::string line;
    for(std::string line; std::getline(input, line);)
    {   
        if (line=="end"){
            break;
        }
        auto v = split(line, '\t');
        ip_pool.push_back(split(v.at(0), '.'));
    }
    return ip_pool;
}


void show_ip_pool(std::vector <std::vector <std::string>> &ip_pool){
    for(auto ip = ip_pool.begin(); ip != ip_pool.end(); ++ip)
    {
        for(auto ip_part = ip->begin(); ip_part != ip->end(); ++ip_part)
        {
            if (ip_part != ip->begin())
            {
                std::cout << ".";
            }
            std::cout << *ip_part;
        }
    std::cout << std::endl;
    }
}


std::vector <std::vector <std::string>> reverse_sort(std::vector <std::vector <std::string>> ip_pool){
    auto first = ip_pool.begin();
    auto last =  ip_pool.end();
    for (int i=3;i>=0;i--){
        for(auto ip1 = first; ip1 != last; ++ip1)
        {
            for(auto ip2 = first; ip2 != last-(ip1-first)-1; ++ip2)
            {
                if (std::stoi((*ip2)[i]) < std::stoi((*(ip2+1))[i])){
                    std::iter_swap(ip2, ip2+1);
                }
            }
        }
    }
    return ip_pool;
}


std::vector <std::vector <std::string>> sort_by_condition(std::vector <std::vector <std::string>> ip_pool, bool condition_func(std::vector<std::vector <std::string>>::iterator)){
    auto first = ip_pool.begin();
    auto last =  ip_pool.end();
    auto insert_pos = first;
    for(auto ip = first; ip != last; ++ip)
    {
        if (condition_func(ip)){
            auto value = *ip;
            ip_pool.erase(ip);
            ip_pool.insert(insert_pos++, value);
        }
    }
    return ip_pool;
}