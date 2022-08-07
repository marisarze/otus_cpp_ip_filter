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
    "99\t234\t45\n"
    "1.2.3.4\t234\t.\n");
    auto backup = std::cin.rdbuf();
    std::cin.rdbuf(data.rdbuf());
    auto result = get_ip_pool(std::cin);
    decltype(result) expected = {
        {1, 1, 1, 1},
        {1, 2, 1, 1},
        {1, 1, 3, 1},
        {1, 1, 1, 4},
        {1, 1, 1, 1},
        {2, 2, 2, 2},
        {{99}},
        {1, 2, 3, 4}
    };
    std::cin.rdbuf(backup);
    EXPECT_EQ(result, expected);
}


TEST(TestSimple, TestShowIpPool){

    std::vector <std::vector<int>> input_pool = 
    {
        {10, 10, 10, 10},
        {1, 2, 3, 4},
        {1, 3, 1},
        {4, 8, 15, 16},
        {23, 42, 4, 8},
        {15, 16, 23, 42},
        {{65}},
        {1, 2, 3, 4}
    };

    std::string expected = 
        "10.10.10.10\n"
        "1.2.3.4\n"
        "1.3.1\n"
        "4.8.15.16\n"
        "23.42.4.8\n"
        "15.16.23.42\n"
        "65\n"
        "1.2.3.4\n";

    auto backup = std::cout.rdbuf();
    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    show_ip_pool(input_pool);
    auto result = buffer.str();
    std::cout.rdbuf(backup);
    EXPECT_EQ(result, expected);
}


TEST(TestSimple, TestReverseSort){

    std::vector <std::vector<int>> input_pool = 
    {
        {4,3,2,1},
        {5,4,3,2},
        {6,5,4,3},
        {8,8,8,4},
        {9,8,8,4},
        {4,5,5,6},
        {0,0,0,0},
        {3,5,5,6},
        {4,5,5,6},
        {4,6,6,5},
        {4,6,250,240},
        {6,7,8,9}
    };

    std::vector <std::vector<int>> expected = 
    {   
        {4,6,250,240},
        {6,7,8,9},
        {4,5,5,6},
        {4,5,5,6},
        {3,5,5,6},
        {4,6,6,5},
        {9,8,8,4},
        {8,8,8,4},
        {6,5,4,3},
        {5,4,3,2},
        {4,3,2,1},
        {0,0,0,0},
    };
    auto result = reverse_sort(input_pool);
    EXPECT_EQ(result, expected);
}


TEST(TestSimple, TestFilterByCondition){

    std::vector <std::vector<int>> input_pool = 
    {
        {2,3,4,5},
        {1,2,3,4},
        {3,4,5,6},
        {4,8,8,8},
        {46,70,8,9},
        {6,5,5,4},
        {46,70,0},
        {1,70,7,0},
        {6,5,5,3},
        {46,70,5,4},
        {5,6,46,4},
        {240,250,6,46},
        {1,8,7,46}
    };

    const std::vector <int> some_val;
    auto condition_func1 = [](decltype(some_val)& input)-> bool {return input[0]==1;};
    auto result_1 = filter_by_condition(input_pool, condition_func1);
    decltype(input_pool) expected_1 = 
    {
        {1,2,3,4},
        {1,70,7,0},
        {1,8,7,46}
    };

    auto condition_func2 = [](decltype(some_val)& input)-> bool {return input[0]==46 && input[1]==70;};
    auto result_2 = filter_by_condition(input_pool, condition_func2);
    decltype(input_pool) expected_2 = 
    {
        {46,70,8,9},
        {46,70,0},
        {46,70,5,4}
    };


    auto condition_func3 = [](decltype(some_val)& input)-> bool {
        for (int i=0;i<4;i++){
            if ((input)[i]==46) return true;
        }
        return false;
    };
    auto result_3 = filter_by_condition(input_pool, condition_func3);
    decltype(input_pool) expected_3 = 
    {   
        {46,70,8,9},
        {46,70,0},
        {46,70,5,4},
        {5,6,46,4},
        {240,250,6,46},
        {1,8,7,46}
    };

    EXPECT_EQ(result_1, expected_1);
    EXPECT_EQ(result_2, expected_2);
    EXPECT_EQ(result_3, expected_3);
}