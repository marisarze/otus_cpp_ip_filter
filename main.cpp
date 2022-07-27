#include "ip_filter.h"
#include <iostream>

int main()
{
    try
    {
        auto ip_pool = get_ip_pool(std::cin);

        auto new_pool = reverse_sort(ip_pool);
        show_ip_pool(new_pool);

        std::vector<std::vector <std::string>>::iterator some_it;

        auto condition_func1 = [](decltype(some_it) it)-> bool {return (*it)[0]=="1";};
        new_pool = filter_by_condition(ip_pool, condition_func1);
        show_ip_pool(new_pool);

        auto condition_func2 = [](decltype(some_it) it)-> bool {return (*it)[0]=="46" && (*it)[1]=="70";};
        new_pool = filter_by_condition(ip_pool, condition_func2);
        show_ip_pool(new_pool);

        auto condition_func3 = [](decltype(some_it) it)-> bool {
            for (int i=0;i<4;i++){
                if ((*it)[i]=="46") return true;
            }
            return false;
        };
        new_pool = filter_by_condition(ip_pool, condition_func3);
        show_ip_pool(new_pool);
        
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
