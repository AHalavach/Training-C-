// Templates  v2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>

constexpr size_t CENTS = 100;

struct USD
{
    size_t Dollars;
    size_t Cents;
    const size_t CurrencyCode = 840;
    double ExchangeRateBYN;
    std::string CurrencyName{ "USD" };
};

struct EURO
{
    size_t Euro;
    size_t EuroCents;
    const size_t CurrencyCode = 978;
    double ExchangeRateBYN;
    std::string CurrencyName{ "EUR" };
};


struct BYN
{
    size_t rubley;
    size_t kopeek;
    const size_t CurrencyCode = 933;
    std::string CurrencyName{ "BYN" };

    BYN operator+(const BYN& b)
    {
        BYN temp;
        
        size_t kopeek_value = kopeek + b.kopeek;
        temp.kopeek = kopeek_value % CENTS;
        temp.rubley = kopeek_value / CENTS + rubley + b.rubley;
        
        return temp;
    }
};


template<class T>
class Currency
{
   
    T* m_data;

    BYN ConvertBYN(const T* data)
    {
        std::cout << "GetBYN \r\n";
    }

  public:
    Currency(T info)
    {
        std::cout << "Error \r\n";
    }

    ~Currency()
    {
        delete m_data;
    }

    BYN GetByn()
    {
        return ConvertBYN(m_data);
    }
};

template <>
Currency<EURO>::Currency(EURO info)
{
    m_data = new EURO;
    m_data->Euro = info.Euro,
    m_data->EuroCents = info.EuroCents,
    m_data->ExchangeRateBYN = info.ExchangeRateBYN;
}

template <>
Currency<USD>::Currency(USD info)
{
    m_data = new USD;
    m_data->Dollars = info.Dollars,
    m_data->Cents = info.Cents,
    m_data->ExchangeRateBYN = info.ExchangeRateBYN;
}

template <>
BYN Currency<EURO>::ConvertBYN(const EURO* data)
{
    double sum = static_cast<double>(data->EuroCents);
    sum = (sum / CENTS + static_cast<double>(data->Euro)) * data->ExchangeRateBYN;
 
    double integral_part;
    double fractional_part = std::modf(sum ,&integral_part);
   
    BYN value = {
        .rubley = static_cast<size_t>(integral_part),
        .kopeek = static_cast<size_t>(fractional_part * CENTS)
    };

    std::cout << m_data->CurrencyName << " - " << value.rubley << "," << value.kopeek << value.CurrencyName << std::endl;

    return value;
}


template <>
BYN Currency<USD>::ConvertBYN(const USD* data)
{
    double sum = static_cast<double>(data->Cents);
    sum = (sum / CENTS + static_cast<double>(data->Dollars)) * data->ExchangeRateBYN;

    double integral_part;
    double fractional_part = std::modf(sum, &integral_part);

    BYN value = {
        .rubley = static_cast<size_t>(integral_part),
        .kopeek = static_cast<size_t>(fractional_part * CENTS)
    };

    std::cout << m_data->CurrencyName << " - " << value.rubley << "," << value.kopeek << value.CurrencyName << std::endl;

    return value;
}

int main()
{
    std::cout << "BYN calculator! \r\n";

    EURO example1 = {
        .Euro = 10,
        .EuroCents = 7,
        .ExchangeRateBYN = 3.0 };
    
    USD example2 = {
        .Dollars = 7,
        .Cents = 85,
        .ExchangeRateBYN = 2.57 };

    BYN example3 = {.rubley = 0, .kopeek = 0};

    Currency<EURO> EuroObject(example1);
    Currency<USD>  USDObject(example2);
    
    
    BYN totalBYN = EuroObject.GetByn() + USDObject.GetByn();
    std::cout << "Total: " << totalBYN.rubley << " rubley, " << totalBYN.kopeek << " kopeek" << std::endl;

  return 0;
}


