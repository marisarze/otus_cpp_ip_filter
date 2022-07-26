#include "ip_filter.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    try
    {
        auto ip_pool = get_ip_pool(std::cin);
        //std::cout << "Size original: " << ip_pool.size() << std::endl;
        show_ip_pool(ip_pool);
        // std::cout << "---------------------------------" << std::endl;
        auto new_pool = reverse_sort(ip_pool);
        //std::cout << "Size after reverse: " << new_pool.size() << std::endl;
        show_ip_pool(new_pool);
        auto condition_func1 = [](std::vector<std::vector <std::string>>::iterator it)-> bool {return (*it)[0]=="1";};
        new_pool = sort_by_condition(new_pool, condition_func1);
        //std::cout << "Size after codition 1: " << new_pool.size() << std::endl;
        show_ip_pool(new_pool);
        auto condition_func2 = [](std::vector<std::vector <std::string>>::iterator it)-> bool {return (*it)[0]=="46" && (*it)[1]=="70";};
        new_pool = sort_by_condition(new_pool, condition_func2);
        std::cout << "Size after codition 2: " << new_pool.size() << std::endl;
        //show_ip_pool(new_pool);
        auto condition_func3 = [](std::vector<std::vector <std::string>>::iterator it)-> bool {
            for (int i=0;i<4;i++){
                if ((*it)[i]=="46") return true;
            }
            return false;
        };
        new_pool = sort_by_condition(new_pool, condition_func3);
        std::cout << "Size after codition 3: " << new_pool.size() << std::endl;
        //show_ip_pool(new_pool);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
