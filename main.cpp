#include "Store.h"
#include "User.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <chrono>
#include <thread>

#define INTERACTIVE_MODE

void cls()
{
#ifndef INTERACTIVE_MODE
    return;
#endif // INTERACTIVE_MODE

#if defined(_WIN32)
    std::system("cls");
#elif defined(unix)
    std::system("clear");
#endif
}

void interactivePrint(std::ostream& os, const char* msg)
{
#ifdef INTERACTIVE_MODE
    os << msg;
#endif // INTERACTIVE_MODE
}

void pause()
{
#ifndef INTERACTIVE_MODE
    return;
#endif // INTERACTIVE_MODE

#ifdef _WIN32
    std::system("pause");
#else
    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(2s);
#endif // _WIN32
}

void RegisterMenu(std::vector<User>& users)
{
    using std::cin, std::cout;
    std::string username, password, EGN, name, address, phone;
    interactivePrint(cout, "Username: ");
    std::getline(cin, username);
    interactivePrint(cout, "Password: ");
    std::getline(cin, password);
    interactivePrint(cout, "EGN: ");
    cin >> EGN;
    cin.ignore();
    interactivePrint(cout, "Name: ");
    std::getline(cin, name);
    interactivePrint(cout, "Address: ");
    std::getline(cin, address);
    interactivePrint(cout, "Phone: ");
    cin >> phone;
    cin.ignore();
    for(const auto& u: users)
        if(u.getUsername() == username)
            throw std::runtime_error("username already exists");
    users.emplace_back(BankAccount{{EGN, name, address, phone}, 1000}, username, password);
    interactivePrint(cout, "Success, you can now login\n");
    pause();
    cls();
}

void StoreMenu(Store& store, User& u)
{
    using std::cin, std::cout;
    while(cin)
    {
        interactivePrint(cout, R"(1. List all items
2. Filter items by name
3. Filter items by type
4. Filter items by price
5. Add item to cart
6. View cart
7. Delete cart
8. Checkout
9. Logout
)");
        int n;
        cin >> n;
        cin.ignore();
        cls();
        switch(n)
        {
        case 1:
            store.filterByName(cout);
            pause();
            break;
        case 2:
        {
            std::string name;
            interactivePrint(cout, "Enter what you search for: ");
            std::getline(cin, name);
            store.filterByName(cout, name);
            pause();
            break;
        }
        case 3:
            interactivePrint(cout, R"(1. Shoes
2. Bucket
3. Candies
)");
            int n;
            cin >> n;
            switch(n)
            {
                case 1:
                    store.filterByType(cout, Item::Type::Shoes);
                    break;
                case 2:
                    store.filterByType(cout, Item::Type::Bucket);
                    break;
                case 3:
                    store.filterByType(cout, Item::Type::Candies);
                    break;
                default:
                    interactivePrint(cout, "Unknown type\n");
            }
            pause();
            break;
        case 4:
            double minPrice, maxPrice;
            interactivePrint(cout, "min price: ");
            cin >> minPrice;
            interactivePrint(cout, "max price: ");
            cin >> maxPrice;
            cin.ignore();
            store.filterByPrice(cout, minPrice, maxPrice);
            pause();
            break;
        case 5:
            std::size_t index;
            interactivePrint(cout, "Which item do you want to add? ");
            cin >> index;
            cin.ignore();
            interactivePrint(cout, store.addItemToCart(index, u)? "Item added\n": "Item NOT added\n");
            pause();
            break;
        case 6:
            store.printCartOfUser(cout, u);
            pause();
            break;
        case 7:
            u.deleteCart();
            interactivePrint(cout, "Done\n");
            pause();
            break;
        case 8:
            interactivePrint(cout, store.checkout(u)? "Success\n": "You don't have enough money\n");
            pause();
            break;
        case 9:
            return;
        }
    cls();
    }
}

void LoginMenu(Store& store, std::vector<User>& users)
{
    using std::cin, std::cout;
    std::string username, password;
    interactivePrint(cout, "Username: ");
    std::getline(cin, username);
    interactivePrint(cout, "Password: ");
    std::getline(cin, password);
    cls();
    for(auto& u: users)
        if(u.login(username, password))
        {
            StoreMenu(store, u);
            u.logout();
            return;
        }
    interactivePrint(cout, "Incorrect username or password\n");
    pause();
    cls();
}

void mainMenu(Store& store, std::vector<User>& users)
{
    using std::cin, std::cout;
    while(cin)
    {
        interactivePrint(cout, R"(1. Register
2. Login
3. Exit
)");
        int n;
        cin >> n;
        cin.ignore();
        cls();
        switch(n)
        {
        case 1: RegisterMenu(users); break;
        case 2: LoginMenu(store, users); break;
        case 3: return;
        }
    }
}

int main() try
{
    std::ifstream is("items.txt");
    if(!is)
    {
        std::cerr << "Could not open items.txt\n";
        return 1;
    }
    Store store({{"6407291135", "Store owner", "...", "0888888888"}});
    store.loadItems(is);
    is.close();
    is.open("users.txt");
    if(!is)
    {
        std::cerr << "Could not open users.txt\n";
        return 1;
    }
    std::vector<User> users;
    int n;
    is >> n;
    is.ignore();
    if(!is) throw std::runtime_error("Bad state of input files");
    while(n--)
        users.push_back(User::read(is));
    is.close();
    mainMenu(store, users);
    std::ofstream os("items.txt");
	if(!os) throw std::runtime_error("Could not open output file");
    store.showAllItems(os, false);
    os.close();
    os.open("users.txt");
	if(!os) throw std::runtime_error("Could not open output file");
    os << users.size() << '\n';
    for(const auto& u: users)
        os << u << '\n';
}
catch(const std::exception& e)
{
    std::cerr << "Error: " << e.what() << std::endl;
    std::cerr << "Changes are not saved" << std::endl;
}
