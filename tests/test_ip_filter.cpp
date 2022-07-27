#include "../ip_filter.h"
#include "gtest/gtest.h"
#include <iostream>
#include <sstream>
#include <string>

TEST(TestSimple, TestGetIpPool){

    std::istringstream data(
    "1.1.1.1\t234\t45\n"
    "1.2.1.1\t1.1.1.1\t45\n"
    "1.1.3.1\t234\t1.1.1.1\n"
    "1.1.1.4\t\t45\n"
    "1.1.1.1\t234\t\n"
    "2.2.2.2\t234\t45\n"
    "9009\t234\t45\n"
    "1.2.3.4\t234\t.\n");
    auto backup = std::cin.rdbuf();
    std::cin.rdbuf(data.rdbuf());
    auto result = get_ip_pool(std::cin);
    decltype(result) expected = {
        {"1", "1", "1", "1"},
        {"1", "2", "1", "1"},
        {"1", "1", "3", "1"},
        {"1", "1", "1", "4"},
        {"1", "1", "1", "1"},
        {"2", "2", "2", "2"},
        {{"9009"}},
        {"1", "2", "3", "4"}
    };
    std::cin.rdbuf(backup);
    show_ip_pool(result);
    EXPECT_EQ(result, expected);
}


TEST(TestSimple, TestShowIpPool){

    std::vector <std::vector<std::string>> input_pool = 
    {
        {"10", "10", "10", "10"},
        {"1", "2", "3", "4"},
        {"1", "3", "1"},
        {"4", "8", "15", "16"},
        {"23", "42", "4", "8"},
        {"15", "16", "23", "42"},
        {{"656"}},
        {"1", "2", "3", "4"}
    };

    std::string expected = 
        "10.10.10.10\n"
        "1.2.3.4\n"
        "1.3.1\n"
        "4.8.15.16\n"
        "23.42.4.8\n"
        "15.16.23.42\n"
        "656\n"
        "1.2.3.4\n";

    auto backup = std::cout.rdbuf();
    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    show_ip_pool(input_pool);
    auto result = buffer.str();
    std::cout.rdbuf(backup);
    EXPECT_EQ(result, expected);
}