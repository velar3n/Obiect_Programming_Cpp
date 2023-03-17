#include <iostream>
#include <cstring>
#include <vector>
#include <functional>
#include <set>

// ZADANIE 1. Podaj implementacje funkcji maxdla różnego typu argumentów. Skorzystaj z możliwości przeciążania i specjalizacji szablonów funkcji

template <typename T>   // normalne
T max(T a, T b) {
    if(a > b){
        return a;
    }
    return b;
}

template <typename T>   // wskazniki
T* max(T *a, T *b) {
    if(a > b){
        return a;
    }
    return b;
}

template <typename T>   // kontener o rozmiarze - użycie auto bez size?
T max(T *data, size_t n) {
    T temp = data[0];
    for(size_t i=0; i<n; i++) {
        if(data[i] > temp) {
            temp = data[i];
        }
    }
    return temp;
}

template <>     //stringi (ciągi char) - strcmp porównuje string char po char <0 gdy a większe, =0 gdy równe, >0 gdy b większe
char *max(char *a, char *b) { 
    if(strcmp(a, b) < 0) {
        return a;
    }
    return b;
}

template <>
const char *max(const char *a, const char *b) {
    if(strcmp(a, b) < 0) {
        return a;
    }
    return b;
}

template <typename T>
const T *max(T *a, const T *b) {
    if(a > b){
        return a;
    }
    return b;
}

template <>
const char *max(char *a, const char *b) {
    if(strcmp(a, b) < 0) {
        return a;
    }
    return b;
}



// ZADANIE 2 - Na przykładzie szablonu funkcji convert pokazać, że jest możliwe zdefiniowanie dwóch funkcji o tej samej nazwie i argumentach wywołania, różniących się tylko zwracanym typem (na wykładzie jest że nie można definiować dwóch takich samych funkcji z różnymi tylko zwracanymi typami, ale można różne specjalizacje napisać?)

template<typename T,typename U> 
T convert(U u) {
  return static_cast<T>(u);
}

template<> 
int convert<int, int>(int u) {
    return static_cast<int>(u);
}

template<> 
double convert<double, int>(int u) {
    return static_cast<double>(u);
}



// ZADANIE 3 - W  przeciwieństwie  do  szablonów  funkcji,  szablony  klas  nie  mogą  być przeciążane, a jedynie specjalizowane. Oznacza to, że w programie może istnieć  tylko  jeden  szablon  podstawowy  o  danej  nazwie.  Proszę zaimplementować specjalizację częściową, która jest dozwolona  tylko  dla szablonów klas, dla podanych podzbiorów parametrów

template<typename T, int N = 100>    // szablon podstawowy
class Stack {
    private:
        T array[N];
        int top;
    public:
        Stack() : top(0) {};
        void created_stack() {
            std::cout<<"Szablon podstawowy"<<std::endl;
        }
};      

template<typename T>        // kolejne specjalizacje w zależności od parametrów szablonu podstawowego, istnieje hierarchia np. double, 666 -> T, 666 -> T, N
class Stack<T, 666> {
    private:
        T array[666];
        int top;
    public:
        Stack() : top(0) {};
        void created_stack() {
            std::cout<<"Szablon <T, 666>"<<std::endl;
        }
}; 

template<typename T,int N>  
class Stack<T*, N> {
    private:
        T* array[N];
        int top;
    public:
        Stack() : top(0) {};
        void created_stack() {
            std::cout<<"Szablon <T*, N>"<<std::endl;
        }
};

template<int N>             
class Stack<double, N> {
    private:
        double array[N];
        int top;
    public:
        Stack() : top(0) {};
        void created_stack() {
            std::cout<<"Szablon <double, N>"<<std::endl;
        }
};

template<int N>             
class Stack<int*, N> {
    private:
        int* array[N];
        int top;
    public:
        Stack() : top(0) {};
        void created_stack() {
            std::cout<<"Szablon <int*, N>"<<std::endl;
        }
};

template<>                  
class Stack<double, 666> {
    private:
        double array[666];
        int top;
    public:
        Stack() : top(0) {};
        void created_stack() {
            std::cout<<"Szablon <double, 666>"<<std::endl;
        }
};

template<>                  
class Stack<double*, 44> {
    private:
        double* array[44];
        int top;
    public:
        Stack() : top(0) {};
        void created_stack() {
            std::cout<<"Szablon <double*, 44>"<<std::endl;
        }
};



// ZADANIE 4 - Zaimplementować szablon klasy Stack wraz z jej specjalizacjami tak aby „działała” ze zwykłymitablicami oraz kontenerami STL

template <typename T, size_t N = 10, typename R = T*> 
class Stack2;

template<typename T, size_t N>      // dla tablicy
class Stack2<T, N> {
    private:
        T array[N];
        size_t top;
    public:
        Stack2() : top(0) {};
        bool is_empty() {
            return (top==0);
        } 
        void push(T val) {
            array[top++] = val;
        }
        T pop() {
            return array[top--];
        }
        void created_stack() {
            std::cout<<"Szablon dla tablicy"<<std::endl;
        }
};

template<typename T, size_t N, template<typename E> class Container>      // dla kontenerów STL
class Stack2<T, N, Container<T>> {
    private:
        Container<T> container_STL;
    public:
        Stack2() {};
        bool is_empty() {
            return container_STL.empty();
        } 
        void push_back(T val) {
            container_STL.push_back(val);
        }
        T pop_back() {
            container_STL.pop_back();
        }
        void created_stack() {
            std::cout<<"Szablon dla kontenera STL"<<std::endl;
        }
};



// ZADANIE 5 - zapoznaj się z rodziną funktorów porównujących, do której  należą np. less<>(), greater<>(), less_equal<>(), greater_equal<>(). Przypomnij sobie pojemnik std::set. Następnie napisz programik korzystający ze zbioru liczb posortowanego odwrotnie (czyli malejąco). 

// funktory zwracają boole w zależności od tego czy warunek jest spełniony, w <> określamy typ - domyślnie void
// std::set - zbiór, nie zawiera duplikatów elementów



int main() {

    std::cout<<"Zadanie 1: "<<std::endl;
    double a=2, b=2.2;
    int array[6]={-1, 0, 13, 2, -100, 12};
    std::cout<<max(a, b)<<std::endl;
    std::cout<<*max(&a,&b)<<std::endl;
    std::cout<<max(array, 6)<<std::endl;

    char *str1 = new char[8];
    char *str2 = new char[6];
    strncpy(str1,"barszcz", 8);
    strncpy(str2,"burak", 6);
    std::cout<<max("barszcz", "burak")<<std::endl;
    std::cout<<max(str1, str2)<<std::endl;
    std::cout<<max(str1, "burak")<<std::endl;


    std::cout<<"\nZadanie 2: "<<std::endl;
    std::cout<<convert<int>(a)<<std::endl;
    std::cout<<convert<double>(a) <<std::endl;


    std::cout<<"\nZadanie 3: "<<std::endl;
    Stack<float, 123> stack0;
    Stack<char, 666> stack1;
    Stack<float*, 55> stack2;
    Stack<double, 22> stack3;
    Stack<int*, 11> stack4;
    Stack<double, 666> stack5;
    Stack<double*, 44> stack6;
    stack0.created_stack();
    stack1.created_stack();
    stack2.created_stack();
    stack3.created_stack();
    stack4.created_stack();
    stack5.created_stack();
    stack6.created_stack();


    std::cout<<"\nZadanie 4: "<<std::endl;
    Stack2<int, 100> s_default;
    s_default.created_stack();
    /*Stack2<int, 0, std::vector<int>> s_container;  
    s_container.created_stack();*/


    std::cout<<"\nZadanie 5: "<<std::endl;
    std::set<double, std::greater<double>> mySet = {1, 14.4, -33.12, 8.7, -1, 0.0};
    for(auto i : mySet) {
        std::cout<<i<<std::endl;
    }


    return 0;
}