#include "../ip_filter.h"
#include "gtest/gtest.h"


TEST(TestSimple, TestGetIpPool){

    std::stringstream input( 
    "1.1.1.1\t234\t45\n"
    "1.2.1.1\t1.1.1.1\t45\n"
    "1.1.3.1\t234\t1.1.1.1\n"
    "1.1.1.4\t\t45\n"
    "1.1.1.1\t234\t\n"
    "2.2.2.2\t234\t45\n"
    "9009\t234\t45\n"
    "1.2.3.4\t234\t.\n");
    auto result = get_ip_pool(input);
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
    EXPECT_EQ(result, expected);
}



// TEST(TestSimple, TestEquality){

//     std::stringstream buffer;
//     std::string data = 
//     "1.1.1.1\t234\t45\n"
//     "1.1.1.1\t1.1.1.1\t45\n"
//     "1.1.1.1\t234\t1.1.1.1\n"
//     "1.1.1.1\t\t45\n"
//     "1.1.1.1\t234\t\n"
//     "2.2.2.2\t234\t45\n"
//     "9.9.9.9\t234\t45\n"
//     "0.0.0.0\t234\t.\n";
//     buffer << data;
//     std::streambuf *sbuf = std::cout.rdbuf();
//     std::cout.rdbuf(buffer.rdbuf());
//     converter.show_config_info();
//     std::string result = buffer.str();
//     std::cout.rdbuf(sbuf);
//     std::string expected = "search engine name: FastestSearchEngine\n"
//             "search engine version: 0.9999\n";
//     ASSERT_EQ(result, expected);

//     int expected = 1;
//     int result = 1;
//     EXPECT_EQ(result, expected);
// }