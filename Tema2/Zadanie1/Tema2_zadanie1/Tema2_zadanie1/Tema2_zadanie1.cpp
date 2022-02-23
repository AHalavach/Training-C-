// Tema2_zadanie1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

const int VECTOR_SIZE_MAX = 20;
const int VECTOR_SIZE_MIN = 4;
const double WEIGHT_THRESHOLD_KG = 0.01;

using vector_type = std::vector<unsigned int>;

struct Thing_t
{
    std::string name;
    double price;
    double weight_kg;
    bool fraction;
};

class Backpack
{
    double weight;
    std::vector<Thing_t> pack;

public:
    const double weight_limit;

    Backpack(double value) : weight_limit(value), weight(0)
    {}

    void add_thing(Thing_t& item)
    {
        pack.push_back(item);
        weight += item.weight_kg;
    }

    double get_weight(void)
    {
        return weight;
    }

    void print_content(void)
    {
        std::cout << std::endl;
        std::cout << "**** Pack content ****" << std::endl;
        std::cout << "pack weight - " << weight << std::endl;

        for (auto& value : pack)
            std::cout << value.name << " : " << value.weight_kg << std::endl;
    }
};

int main()
{
    // ****** Variant 1 *********
    std::cout << "----- Tema 2, zadanie 1, variant 1 -----\n";

    std::cout << "Enter vector size \r\n";
    std::string buffer{ "" };
    std::getline(std::cin, buffer);

    try
    {
        int vector_size = stoi(buffer);
        if ((vector_size < VECTOR_SIZE_MIN) || (vector_size > VECTOR_SIZE_MAX))
        {
            throw vector_size;
        }

        std::cout << "First vector values:\r\n";
        std::mt19937 mt(time(nullptr));
        vector_type vector1(vector_size, 0);
        for (auto &value : vector1)
        {
            value = mt();
            std::cout << value << std::endl;
        }

        size_t vector2_size = vector_size / 2;
        std::cout << std::endl;
        std::cout << "vector2 size - " << vector2_size << std::endl;
        
        vector_type vector2(vector2_size, 0);
        vector_type::iterator itr = vector1.begin() + vector2_size;
        std::copy_n(itr, vector2_size, vector2.begin());
        std::cout << "Second vector values:\r\n";
        for (auto value : vector2)
        {
            std::cout << value << std::endl;
        }
    }
    catch (int size)
    {
        std::cout << "#1: " << "Vector size is out of range: " << VECTOR_SIZE_MIN << " - " << VECTOR_SIZE_MAX << std::endl;
    }
    catch (std::invalid_argument const& ex)
    {
        std::cout << "#2: " << ex.what() << std::endl;
    }
    catch (const std::out_of_range const& oor)
    {
        std::cerr << "#3: " << oor.what() << '\n';
    }
    

    // ****** Variant 2 *********+
    std::cout << std::endl;
    std::cout << "----- Tema 2, zadanie 1, variant 2 ----- \r\n";
    
    std::vector<Thing_t> things(7);
    things[0] = { "white bread", 15.1, 0.93, true };
    things[1] = { "meat", 56.8, 1.5, true };
    things[2] = { "knife", 78.0, 0.5, false };
    things[3] = { "bottle of water", 68.6, 1.5, false };
    things[4] = { "trousers", 19.3, 0.85, false };
    things[5] = { "shoes", 23.9, 1.1, false };
    things[6] = { "apples", 5.8, 3.1, true };

    std::sort(things.begin(), things.end(), [](Thing_t& a, Thing_t& b) {
        return (a.price / a.weight_kg) > (b.price / b.weight_kg);
    });

    for (auto& value : things)
    {
        std::cout << value.name << " : " << value.price / value.weight_kg << " : " << value.weight_kg << " kg" << std::endl;
    }

    Backpack one(4.3);
    

    for (auto& value : things)
    {
        double delta = one.weight_limit - one.get_weight();

        if (delta > 0)
        {
            double diff = delta - value.weight_kg;
            if ((diff > WEIGHT_THRESHOLD_KG) || (abs(diff) <= WEIGHT_THRESHOLD_KG))
            {
                one.add_thing(value);
            }
            else
            {
                if (value.fraction)
                {
                    Thing_t temp = value;
                    temp.weight_kg += diff;
                    one.add_thing(temp);
                }
            }
        }
        else
        {
            break;
        }
    }

    one.print_content();
    
}
