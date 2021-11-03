#include <iostream>
#include <map>
#include <exception>

const std::string WHITESPACE = " \t";

/**
 * @fucntion Print the map nto console.
 * @param [in] map std::map
 */
void printMap(const std::map<std::string, int>& map)
{
    if (map.empty()) std::cout << "[empty]\n";
    for (const auto& element : map)
    {
        std::cout << element.first << " : " << element.second << "\n";
    }
}

void printAll(std::map <std::string, int>& shop, std::map <std::string, int>& cart)
{
    std::cout << "\t - Shop table:\n";
    printMap(shop);
    std::cout << "\t - Cart table:\n";
    printMap(cart);
}

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
    if (value.empty()) throw std::invalid_argument("article name is empty");
    if (value.find_first_not_of(WHITESPACE) != 0) throw std::invalid_argument("article is started from whitespace");
    return value;
}

/**
 * @function Get the int input from cin.
 * @throws invalid_argument exception
 * (if quantity is less than 0 or std::stoi conversion fail)
 * @return [out] quantity int
 */
int getQuantityFromInput()
{
    std::cout << "Please enter the quantity:\n";
    std::string input;
    std::getline(std::cin, input);

    int quantity = std::stoi(input);
    if (quantity < 0)
    {
        throw std::invalid_argument("quantity");
    }
    return quantity;
}

/**
 * @function Add article to the cart.
 * @throws invalid_argument exception
 * (if article is not found, quantity is less than 0
 * or quantity in the shop is not enough)
 * @param [in] article const std::string
 * @param [in] quantity const int
 * @param [in/out] shop
 * @param [in/out] cart
 */
void addArticleToCart(const std::string &article, const int quantity, std::map<std::string, int>& shop, std::map<std::string, int>& cart)
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
    std::cout << article << " : " << quantity << " [pcs] added to cart\n";
   printAll(shop, cart);
}

/**
 * @function Remove article from the cart.
 * @throws invalid_argument exception
 * (if article is not found,
 * quantity is less than 0 or quantity in the cart is not enough)
 * @param [in] article const std::string
 * @param [in] quantity const int
 * @param [in/out] shop
 * @param [in/out] cart
 */
void removeArticleFromCart(const std::string& article, int quantity, std::map<std::string, int>& shop, std::map<std::string, int>& cart)
{
    if (quantity < 0) throw std::invalid_argument("quantity < 0");
    auto it_cart = cart.find(article);
    if (it_cart == cart.end()) throw std::invalid_argument("article is not found in cart\n");
    if (it_cart->second < quantity) throw std::invalid_argument("quantity in the cart is not enough\n");

    it_cart->second -= quantity;

    auto it_shop = shop.find(article);
    if (it_shop == shop.end())
    {
        shop.insert(std::make_pair(article, quantity));
    }
    else
    {
        it_shop->second += quantity;
    }

    if (it_cart->second == 0) cart.erase(it_cart->first);

    std::cout << article << " : " << quantity << " [pcs] removed from cart\n";
    printAll(shop, cart);
}

int main()
{
    std::map<std::string, int> shop;
    std::map<std::string, int> cart;

    //Add good to shop:
    std::string article;
    int quantity {0};
    std::cout << "\t - Enter goods for shop:\n";
    while (true)
    {
        try
        {
            std::cout << "(Type \'next\' to finish shop preparation)\n";
            article = getArticleFromCin();
            if (article == "next") break;
            quantity = getQuantityFromInput();
        }
        catch (const std::exception& e)
        {
            std::cerr << "Caught exception: " << e.what() << "\n";
            continue;
        }
        auto it = shop.find(article);
        if (it == shop.end())
            shop.insert(std::make_pair(article, quantity));
        else
            it->second += quantity;
    }

    std::cout << "\t - Shop is prepared. Goods you have:\n";
    printMap(shop);

    while (true)
    {
        std::cout << "\t - Please enter the command (add / remove / exit / print):\n";
        std::string command;
        std::getline(std::cin, command);
        try
        {
        if (command == "exit") break;
        else if (command == "add")
        {
            std::string art = getArticleFromCin();
            int q = getQuantityFromInput();
            addArticleToCart(art, q, shop, cart);
        }
        else if (command == "remove")
        {
            std::string art = getArticleFromCin();
            int q = getQuantityFromInput();
            removeArticleFromCart(art, q, shop, cart);
        }
        else if (command == "print")
        {
            std::cout << "\t - Shop table:\n";
            printMap(shop);
            std::cout << "\t - Cart table:\n";
            printMap(cart);
        }
        else
        {
            std::cerr << "Bad command.\n";
        }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Caught exception: " << e.what() << "\n";
        }
        catch (...)
        {
            std::cerr << "Unknown error.\n";
        }
    }
    std::cout << "Program is finished.\n";

    return 0;
}