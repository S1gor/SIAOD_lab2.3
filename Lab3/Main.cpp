/*Библиотека(поиск статьи по названию)
Метод середины квадрата
Открытая адресация(двойное хеширование)*/

#include <iostream>

struct Item
{
    std::string key;
    int val;

    Item() : key(""), val(0) {};
    Item(std::string const& key, int val) : key(key), val(val) {};
};

const int SIZE = 1024;
Item table[SIZE];
#define null(item) (item.key == "" && !item.val)

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
    for (auto chr : key)
        tmp += chr;
    return tmp % SIZE;
}

void Input(Item const& item)
{
    int h1 = Hash1(item.key);
    int h2 = Hash2(item.key);

    for (int i = 0; i < SIZE; i++)
    {
        if (null(table[h1]))
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
        if (null(table[h1]))
            return Item();
        if (table[h1].key == key)
            return table[h1];
        h1 = (h1 + h2) % SIZE;
    }
    return Item();
}

void Print()
{
    std::cout << "Table" << std::endl;
    for (int i = 0; i < SIZE; i++)
        std::cout << i << '.' << "[" << table[i].key << "]" << table[i].val << '\n';
}

int main()
{
    Input({ "WarAndPeace", 10 });
    Input({ "CrimeAndPunishment", 20 });
    Input({ "TheMasterAndMatgarita", 4 });
    Print();

    /*std::string key;
    std::cout << "Enter the key: ";
    std::cin >> key;

    Item found = Search(key);
    if (null(found))
        std::cout << "Item isn't found\n";
    else
        std::cout << "Key: " << found.key << "\nVal: " << found.val;*/

    return 0;
}