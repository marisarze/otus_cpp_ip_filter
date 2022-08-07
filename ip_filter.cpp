#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
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


std::vector<uint8_t> to_uint8(const std::vector <std::string>& input){
    std::vector<uint8_t> result;
    for (auto& elem:input){
        result.emplace_back((uint8_t)std::stoi(elem));
    }
    return result;
}


std::vector<std::vector<uint8_t>> get_ip_pool(std::istream &input)
{
    std::vector<std::vector<uint8_t>> ip_pool;
    std::string line;
    for(std::string line; std::getline(input, line);)
    {   
        if (line=="end"){
            break;
        }
        auto v = split(line, '\t');
        auto temp = split(v.at(0), '.');
        ip_pool.emplace_back(to_uint8(temp));
    }
    return ip_pool;
}


void show_ip_pool(const std::vector <std::vector <uint8_t>>& ip_pool)
{
    for(auto ip = ip_pool.begin(); ip != ip_pool.end(); ++ip)
    {
        for(auto ip_part = ip->begin(); ip_part != ip->end(); ++ip_part)
        {
            if (ip_part != ip->begin())
            {
                std::cout << ".";
            }
            std::cout << std::to_string(*ip_part);
        }
        std::cout << std::endl;
    }
}


std::vector <std::vector <uint8_t>> reverse_sort(std::vector <std::vector <uint8_t>>& ip_pool)
{
    auto first = ip_pool.begin();
    auto last =  ip_pool.end();
    for (int i=0;i<4;i++){
        for(auto it1 = first; it1 != last; ++it1)
        {
            for(auto it2 = first; it2 != last-(it1-first)-1; ++it2)
            {
                if ((*it2)[i] < (*(it2+1))[i]){
                    std::iter_swap(it2, it2+1);
                }
            }
        }
    }
    return ip_pool;
}


std::vector <std::vector <uint8_t>> filter_by_condition(const std::vector <std::vector <uint8_t>>& ip_pool, bool condition_func(const std::vector <uint8_t>&))
{
    auto first = ip_pool.begin();
    auto last =  ip_pool.end();
    std::vector <std::vector <uint8_t>> result; 
    for(auto it = first; it != last; ++it)
    {
        if (condition_func(*it)){
            result.emplace_back(*it);
        }
    }
    return result;
}