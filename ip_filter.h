#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>


std::vector<std::string> split(const std::string &str, char d);

std::vector<std::vector<int>> get_ip_pool(std::istream &input);

void show_ip_pool(const std::vector <std::vector <int>>& ip_pool);

std::vector <std::vector <int>> reverse_sort(std::vector <std::vector <int>>& ip_pool);

std::vector <std::vector <int>> filter_by_condition(const std::vector <std::vector <int>>& ip_pool, bool condition_func(const std::vector <int>&));
