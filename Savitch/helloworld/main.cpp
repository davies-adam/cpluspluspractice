#include <iostream>

class Item
{
public:
    Item(int v) {value = v;};
    int value = 0;
    Item* previous = nullptr;
    Item* next = nullptr;
};

Item const& getItem(Item* first, int index)
{
    if(first == nullptr)
    {
        throw(1);
    }
    Item* current = first;
    for(int i = 0; i<index; i++) {current = current->next;};
    return *current;
}

void addItem(Item* head, Item* newone)
{
    Item* current = head;
    for(int i = 0; i < (3 - 1); i++) {current = current->next;};
    current->next = newone;
    newone->previous = current;
}

Item* destination = nullptr;

void copyList(Item* head, int length)
{
    Item* oldCursor = head;
    Item* newCursor = nullptr;
    Item* newLagging = nullptr;
    for(int i = 0; i < length; i++)
    {
        if(i == 0)
        {
            destination = new Item(oldCursor->value);
            newCursor = destination;
        }
        else
        {
            Item* newLagging = newCursor;
            newCursor->next = new Item(oldCursor->value);
            newCursor = newCursor->next;
            newCursor->previous = newLagging;
        }
        oldCursor = oldCursor->next;
    }
}


int main()
{
    auto x = new Item(3);
    auto y = new Item(4);
    auto z = new Item(5);

    x->next = y;
    y->previous = x;
    y->next = z;
    z->previous = y;

    auto q = new Item(0);

    addItem(x, q);

    copyList(x, 4);
    return 0;
}
