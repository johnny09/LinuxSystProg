#include "Sales_data.h"

Sales_data::Sales_data(const std::string &s, unsigned n, double p):
                        bookNo(s),units_sold(n),revenue(n*p){}
Sales_data::Sales_data(const std::string &s):bookNo(s){}
Sales_data::Sales_data(std::istream& is)
{
    read(is,*this);
}

std::string Sales_data::isbn() const
{
    return Sales_data::bookNo;
}

inline double Sales_data::avg_price() const
{
    return units_sold? revenue/units_sold : 0;
}
double Sales_data::getRevenue()
{
    return revenue;
}

std::istream& read(std::istream& is, Sales_data& item)
{
    double price = 0.0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}
