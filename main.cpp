#include "ip_filter.h"
#include <iostream>

int main()
{
    try
    {
        auto ip_pool = get_ip_pool(std::cin);
        auto new_pool = ip_pool;
        new_pool = reverse_sort(new_pool);
        show_ip_pool(new_pool);

        const std::vector <uint8_t> some_val;

        auto condition_func1 = [](decltype(some_val)& input)-> bool {return input[0]==1;};
        new_pool = filter_by_condition(new_pool, condition_func1);
        show_ip_pool(new_pool);

        auto condition_func2 = [](decltype(some_val)& input)-> bool {return input[0]==46 && input[1]==70;};
        new_pool = filter_by_condition(new_pool, condition_func2);
        show_ip_pool(new_pool);

        auto condition_func3 = [](decltype(some_val)& input)-> bool {
            for (int i=0;i<4;i++){
                if ((input)[i]==46) return true;
            }
            return false;
        };
        new_pool = filter_by_condition(new_pool, condition_func3);
        show_ip_pool(new_pool);
        
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
