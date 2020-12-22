#include <vector>
#include <unordered_map>

#include "Dispatcher.h"


int main()
{
    Animal* cat1 = new Cat;
    Animal* dog1 = new Dog;
    Animal* cat2 = new Cat;
    Animal* dog2 = new Dog;

    BasicDispatcher<Animal, Animal> basicDispatcher;
    basicDispatcher.add<Dog, Dog>(MeetDog);
    basicDispatcher.add<Cat, Dog>(MeetCatDog);
    basicDispatcher.add<Dog, Cat>(MeetCatDog);
    basicDispatcher.add<Cat, Cat>(MeetCat);

    basicDispatcher.Go(dog1, dog2);
    basicDispatcher.Go(cat1, dog1);
    basicDispatcher.Go(dog2, cat2);
    basicDispatcher.Go(cat1, cat2);

    // Write BasicDispatcher on unordered_map

    return 0;
}