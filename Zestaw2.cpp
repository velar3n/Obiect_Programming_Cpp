#include <iostream>
#include <vector>
#include <deque> 
#include <algorithm>
#include <functional>

// Zadanie 1 - definicje najważniejszych pojęć

/*
- Polimorfizm dynamiczny - możliwość decydowania o tym jaka funkcja zostanie wywołana pod daną nazwą w momencie wywołania, a nie kompilacji
    -> czyli to jak dokładnie jakaś funkcja zostanie wywołana, zależy od tego na czym zostanie wywołana -> inaczej funkcja "oblicz_obwod" będzie obliczać obwód koła, a inaczej obwód trójkąta np (mimo że sama nazwa funkcji jest taka sama)

- Polimorfizm statyczny - kompilator decyduje na podstawie typów obiektów jaką funkcję wywołać
    -> jest na tyle wygodny, że nie potrzebujemy mieć ustalonej hierarchii dziedziczenia jak przy dynamicznym - np bazowanie na szablonach

- Klasa abstrakcyjna - jest to klasa zawierająca niezaimplementowane metody (same deklaracje). Te metody potem dopiero implementujemy w klasach po niej dziedziczących

- Funkcja wirtualna - funkcja bez implementacji, które potem implementujemy w klasach pochodnych. Definiowana przez słowo kluczowe "virtual"
*/


// Zadanie 2 - program wykorzystujący polimorfizm statyczny i dynamiczny

class Animal {                                  // dynamiczny
    private:
        int age;
    public:
        Animal(int a): age(a) {};
        int getAge() {return age;}
        virtual void sound() = 0;
};

class Dog : public Animal {
    public: 
        Dog(int a) : Animal(a) {};
        virtual void sound() {
            std::cout<<"woof"<<std::endl;
        }
};

class Cat : public Animal {
    public: 
        Cat(int a) : Animal(a) {};
        virtual void sound() {
            std::cout<<"meow"<<std::endl;
        }
};

template<typename T>                                // statyczny
void make_sound(T animal) {
    animal.sound();
}

class Cow {
    public:
        void sound() {
            std::cout<<"moo"<<std::endl;
        }
};

// Zadanie 3 - implementacja szablonu funkcji 'accumulate', której pierwszy i drugi argument są iteratorami dowolnego kontenera STL. Funkcja ma za zadanie wyliczać sumę wszystkich elementów w przedziale podanych iteratorów

template <class Iterator, class T>
T accumulate(Iterator begin, Iterator end, T typeZero) {
    T sum = typeZero;
    for( ; begin != end; begin++) {
        sum += *begin;
    }
    return sum;
}

// Zadanie 4 - implementacja klasy (funktor typu generator - nie przyjmuje żadnego argumentu) 'SeqenceGen', która wypełnia, za pomocą algorytmu generate_n, wektor sekwencją 20 pierwszych nieparzystych liczb całkowitych. Znajdź element większy od 4 przy wykorzystaniu adaptera bind2nd (std::bind) oraz algorytmu find_if


// MAIN

int main() {

    std::cout<<"Zadanie 2: "<<std::endl;
    Dog* dog = new Dog(10);
    Cat* cat = new Cat(3);
    cat->sound();
    dog->sound();
    Cow cow;
    make_sound(cow);

    std::cout<<std::endl<<"Zadanie 3: "<<std::endl;
    std::vector<int> myVector;
    myVector.push_back(22);
    myVector.push_back(3);
    myVector.push_back(-1);
    std::cout<<accumulate(myVector.begin(), myVector.end(), 0)<<std::endl;
    std::deque<double> myDeque;
    myDeque.push_front(12.88);
    myDeque.push_back(-11.44);
    std::cout<<accumulate(myDeque.begin(), myDeque.end(), 0.0)<<std::endl;

    return 0;
}

