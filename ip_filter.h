#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>


std::vector<std::string> split(const std::string &str, char d);

std::vector<std::vector<std::string>> get_ip_pool(std::istream &input);

void show_ip_pool(std::vector <std::vector <std::string>> &ip_pool);

std::vector <std::vector <std::string>> reverse_sort(std::vector <std::vector <std::string>> ip_pool);

std::vector <std::vector <std::string>> filter_by_condition(std::vector <std::vector <std::string>> ip_pool, bool condition_func(std::vector<std::vector <std::string>>::iterator));
