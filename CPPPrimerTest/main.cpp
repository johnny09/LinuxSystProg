#include <iostream>
#include "Sales_data.h"

int main()
{
    Sales_data sd;
    Sales_data sdBN("2020121611");
    Sales_data sdBN_US_RN("2020121612",5,2.0);

    std::cout<< "sd's bookNo:" << sd.isbn() << std::endl;
    std::cout<< "sd's revenue" << sd.getRevenue() << std::endl;
    std::cout << "sdBN's bookNo: " << sdBN.isbn() << std::endl;
    std::cout << "sdBN_US_RN's bookNo: " << sdBN_US_RN.isbn() << " sdBN_US_RN's revenue: " << sdBN_US_RN.getRevenue() << std::endl;
}