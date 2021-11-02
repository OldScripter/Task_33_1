#include <iostream>
#include <map>
#include <exception>

/**
 * @function Get the article (string) input from cin.
 * @throws invalid_argument exception (if input has zero length).
 * @return [out] article std::string
 */
std::string getArticleFromCin()
{
    std::cout << "Please enter the article:\n";
    std::string value;
    std::getline(std::cin, value);
    if (value.length() == 0) throw std::invalid_argument("article");
    return value;
}

/**
 * @function Get the int input from cin.
 * @throws invalid_argument exception (if quantity < 0 or std::stoi conversion fail)
 * @return [out] quantity int
 */
int getQuantityFromInput()
{
    std::cout << "Please enter the quantity:\n";
    std::string input;
    std::getline(std::cin, input);

    int quantity {0};
    quantity = std::stoi(input);
    if (quantity < 0)
    {
        throw std::invalid_argument("quantity");
    }
    return quantity;
}


void addArticleToCart(std::string article, int quantity, std::map<std::string, int>& shop, std::map<std::string, int>& cart)
{
    if (quantity < 0) throw std::invalid_argument("quantity < 0");
    auto it_shop = shop.find(article);
    if (it_shop == shop.end()) throw std::invalid_argument("article is not found");
    if (it_shop->second < quantity) throw std::invalid_argument("quantity in the shop is not enough");

    it_shop->second -= quantity;
    auto it_cart = cart.find(article);
    if (it_cart == cart.end())
    {
        cart.insert(std::make_pair(article, quantity));
    }
    else
    {
        it_cart->second += quantity;
    }
    std::cout << article << " : " << quantity << "[pcs] added to cart\n";
    std::cout << article << " shop new quantity: " << it_shop->second << "\n";
    std::cout << article << " cart new quantity: " << it_cart->second << "\n";
}

void removeArticleFromCart(std::string article, int quantity, std::map<std::string, int>& shop, std::map<std::string, int>& cart)
{
    if (quantity < 0) throw std::invalid_argument("quantity < 0");
    auto it_cart = cart.find(article);
    if (it_cart == cart.end()) throw std::invalid_argument("article is not found");
    if (it_cart->second < quantity) throw std::invalid_argument("quantity in the cart is not enough");

    it_cart->second -= quantity;
    auto it_shop = shop.find(article);
    it_shop->second += quantity;

    std::cout << article << " : " << quantity << "[pcs] removed from cart\n";
    std::cout << article << " shop new quantity: " << it_shop->second << "\n";
    std::cout << article << " cart new quantity: " << it_cart->second << "\n";
}

void printMap(const std::map<std::string, int>& map)
{
    for (const auto& element : map)
    {
        std::cout << element.first << " : " << element.second << "\n";
    }
}

int main()
{
    std::map<std::string, int> shop;
    std::map<std::string, int> cart;

    //Add good to shop:
    std::string article;
    int quantity {0};
    std::cout << "Enter goods for shop:\n";
    while (true)
    {
        try
        {
            article = getArticleFromCin();
            if (article == "next") break;
            quantity = getQuantityFromInput();
        }
        catch (const std::exception& e)
        {
            std::cerr << "Caught exception: " << e.what();
        }
        shop.insert(std::make_pair(article, quantity));
    }



    while (true)
    {
        std::cout << "Please enter the command (add / remove / exit / print):\n";
        std::string command;
        std::getline(std::cin, command);
        if (command == "exit") break;
        else if (command == "add")
        {

        }
        else if (command == "remove")
        {

        }
        else if (command == "print")
        {
            std::cout << "Shop table:\n";
            printMap(shop);
            std::cout << "Cart table:\n";
            printMap(cart);
        }
        else
        {
            std::cerr << "Bad command.\n";
        }
    }

    for (auto g : shop)
    {
        std::cout << g.first << " : " << g.second << "\n";
    }

    return 0;
}
