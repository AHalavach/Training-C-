#include <iostream>
#include <vector>


constexpr size_t number = 5;
constexpr size_t elements = number + 5;

int main()
{
    std::vector<int> mas;

    std::cout << "K is " << number << std::endl;
    std::cout << "Original vector: \r\n";

    for (int k = 0; k < elements; k++)
    {
        mas.push_back(k);
        std::cout << mas[k] << " ";
    }

    std::cout << std::endl;

    [&mas](size_t quantity) {
    
        for (size_t i = 0; i < quantity; i++)
        {
            mas.push_back(mas.back() + 1);
            mas.erase(mas.begin());
        }
    } (number);

    std::cout << "Transformed vector: \r\n";

    for (auto& i : mas)
        std::cout << i << " ";

    return 0;
}
