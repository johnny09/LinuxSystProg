#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <iostream>
#include <string>
class Sales_data
{
friend std::istream& read(std::istream& is, Sales_data& sd);
public:
    Sales_data() = default;
    Sales_data(const std::string &s, unsigned n, double p);
    Sales_data(const std::string &s);
    Sales_data(std::istream&);
    
    //~Sales_data();
    
    std::string isbn() const;
    //Sales_data& combine(const Sales_data&);
    double avg_price() const;
    double getRevenue();
private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

#endif