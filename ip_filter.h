#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>


std::vector<std::string> split(const std::string &str, char d);

std::vector<std::vector<uint8_t>> get_ip_pool(std::istream &input);

void show_ip_pool(const std::vector <std::vector <uint8_t>>& ip_pool);

std::vector <std::vector <uint8_t>> reverse_sort(std::vector <std::vector <uint8_t>>& ip_pool);

std::vector <std::vector <uint8_t>> filter_by_condition(const std::vector <std::vector <uint8_t>>& ip_pool, bool condition_func(const std::vector <uint8_t>&));
