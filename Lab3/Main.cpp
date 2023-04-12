/*Библиотека(поиск статьи по названию)
Метод середины квадрата
Открытая адресация(двойное хеширование)*/

#include <iostream>

struct Item
{
    std::string key;
    int data;

    Item() : key(""), data(0) {};
    Item(std::string const& key, int data) : key(key), data(data) {};
};

#define SIZE 1024
Item table[SIZE];

uint32_t Hash1(std::string const& key)
{
    int tmp = 0;
    for (char ch : key)
        tmp += ch;
    tmp *= tmp;
    tmp >>= 11;
    return tmp % 1024;
}

uint32_t Hash2(std::string const& key)
{
    int tmp = 0;
    for (auto ch : key)
        tmp += ch;
    return tmp % SIZE;
}

void Input(Item const& item)
{
    int h1 = Hash1(item.key);
    int h2 = Hash2(item.key);

    for (int i = 0; i < SIZE; i++)
    {
        if (table[h1].key == "" && !table[h1].data)
        {
            table[h1] = item;
            return;
        }
        h1 = (h1 + h2) % SIZE;
    }
}

Item Search(std::string const& key)
{
    int h1 = Hash1(key);
    int h2 = Hash2(key);

    for (int i = 0; i < SIZE; i++)
    {
        if (table[h1].key == "" && !table[h1].data)
            return Item();
        if (table[h1].key == key)
            return table[h1];
        h1 = (h1 + h2) % SIZE;
    }
    return Item();
}

void Print()
{
    std::cout << "Table:" << std::endl;
    for (int i = 0; i < SIZE; i++)
        std::cout << i << '.' << "[" << table[i].key << "] - " << table[i].data << std::endl;
}

int main()
{
    Input({ "WarAndPeace", 10 });
    Input({ "CrimeAndPunishment", 20 });
    Input({ "TheMasterAndMargarita", 4 });
    Input({ "EugeneOnegin", 100 });
    Input({ "TheThreeMusketeers", 70 });
    Input({ "CaptainsDaughter", 11 });
    Input({ "TarasBulba", 24 });
    Print();

    std::string key;
    std::cout << "Enter the key: "; std::cin >> key;

    Item found = Search(key);
    if (found.key == "" && !found.data)
        std::cout << "Item isn't found" << std::endl;
    else
        std::cout << "Key: " << found.key << std::endl << "Data: " << found.data << std::endl;

    return 0;
}