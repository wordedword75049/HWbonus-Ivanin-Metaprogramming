#pragma once

#include <iostream>
#include <map>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <utility>

#include "TypeList.h"


class Animal
{
    virtual void voice() = 0;
};

class Dog: public virtual Animal
{
    void voice() override
    {
        std::cout << "Bark" << std::endl;
    }
};

class Cat: public virtual Animal
{
    void voice() override
    {
        std::cout << "Meow" << std::endl;
    }
};

class CatDog: public virtual Cat, public virtual Dog
{
    void voice() override
    {
        std::cout << "BarkMeow" << std::endl;
    }
};


class Meeting
{
public:
    static void meet(Dog* one, Dog* two)
    {
        std::cout << "Bark Bark" << std::endl;
    }

    static void meet(Dog* one, Cat* two)
    {
        std::cout << "Bark Meow" << std::endl;
    }

    static void meet(Cat* one, Dog* two)
    {
        std::cout << "Bark Meow" << std::endl;
    }

    static void meet(Cat* one, Cat* two)
    {
        std::cout << "Meow Meow" << std::endl;
    }

    static void meet(Dog* one, CatDog* two)
    {
        std::cout << "Who are you?" << std::endl;
    }

    static void meet(CatDog* one, Dog* two)
    {
        std::cout << "Who are you?" << std::endl;
    }
    static void meet(Cat* one, CatDog* two)
    {
        std::cout << "Who are you?" << std::endl;
    }

    static void meet(CatDog* one, Cat* two)
    {
        std::cout << "Who are you?" << std::endl;
    }

    static void meet(CatDog* one, CatDog* two)
    {
        std::cout << "Who are you?" << std::endl;
    }

    static void meet(...)
    {
        std::cout << "Something bad happend" << std::endl;
    }
};

void MeetDog(Animal* one, Animal* two)
{
    std::cout << "Bark Bark" << std::endl;
}

void MeetCatDog(Animal* one, Animal* two)
{
    std::cout << "Meow Bark" << std::endl;
}

void MeetCat(Animal* one, Animal* two)
{
    std::cout << "Meow Meow" << std::endl;
}

template<
    class BaseLhs,
    class BaseRhs,
    typename ResultType = void,
    typename CallbackType = ResultType (*)(BaseLhs*, BaseRhs*)
>
class BasicDispatcher
{
    using KeyType = std::pair<std::type_index, std::type_index>;
    using MappedType = CallbackType;

    struct KeyTypeHash {
        std::size_t operator () (const KeyType &keyValue) const {
            const auto h1 = std::hash<std::type_index>{}(keyValue.first);
            const auto h2 = std::hash<std::type_index>{}(keyValue.second);
            return h1 ^ h2;
        }
    };

    using MapType = std::unordered_map<KeyType, MappedType, KeyTypeHash>;

    MapType callbackMap;

public:

    template <class TypeLhs, class TypeRhs>
    void add(CallbackType fun)
    {
        callbackMap[KeyType(std::type_index(typeid(TypeLhs)), std::type_index(typeid(TypeRhs)))] = fun;
    }

    template <class TypeLhs, class TypeRhs>
    void remove()
    {
        callbackMap.erase(KeyType(std::type_index(typeid(TypeLhs)), std::type_index(typeid(TypeRhs))));
    }

    ResultType Go(BaseLhs* lhs, BaseRhs* rhs)
    {
        KeyType k(std::type_index(typeid(*lhs)), std::type_index(typeid(*rhs)));
        typename MapType::iterator it = callbackMap.find(k);
        if (it == callbackMap.end())
        {
            std::cerr << "Error. Types not found";
        }

        return (it->second)(lhs, rhs);
    }
};
