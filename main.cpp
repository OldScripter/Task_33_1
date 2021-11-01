#include <iostream>
#include <map>

std::string getArticleFromCin()
{
    std::cout << "Please enter the article.\n";
    std::string value;
    std::getline(std::cin, value);
    return value;
}


int main() {
    std::map<std::string, int> shop;
    std::map<std::string, int> cart;

    //Add good to shop:
    std::string command;
    std::cout << "Enter the goods for shop:\n";
    while (command != "next")
    {

    }

    return 0;
}
