#include <iostream>

// zadanie 1 - szablon funkcji wybierającej większy z dwóch argumentów
template <typename T>
T maksimum(T a, T b) {
    if(a > b) {
        return a;
    }
    return b;
}

template <typename T>
T maksimum2(T a, T b) {
    return (a > b) ? a : b;
}

// zadanie 2 - funkcja, której zadaniem jest zmiana typu podanego argumentu funkcji
template <typename T, typename U>       //najpierw T, bo T na pewno trzeba podać, U może kompilator wydedukować dość ez
T convert(U object) {
    return (T) object;
}

// zadanie 3 - implementacja iloczynu skalarnego dwóch wektorów o wymiarze N (pozatypowe parametry szablonów)
template<size_t N,typename T> T dot_product(T *a,T *b) {
    T sum=0.0;
    for(size_t i=0; i<N; i++) {
        sum = sum + a[i]*b[i] ;
    }
    return sum;
};

// zadanie 4 - przykład dedukowania wartości pozatypowych argumentów szablonu (nazwa szablonu jako argument)
template <template <int N> class C, int K>
void f(C<K>) {
    std::cout<<K<<std::endl;
}

/*
template<int N> struct SomeClass {};

main() {
  SomeClass<1>  c1;
  SomeClass<2>  c2;

  f(c1); C=SomeClass K=1
  f(c2);C=SomeClass K=2
  */

// zadanie 5 - implementacja szablonu funkcji sumującego elementy stosu
template<typename T> 
class Stack {
    public:
        static const size_t N = 100;
        typedef T value_type;               //!!! TO
    private:
        T array[N];
        size_t top;
    public:
        Stack() : top(0) {};
        bool is_empty() {
            return (top==0);
        } 
        void push(T val) {
            array[top++] = val;
        }
        T pop() {
            return array[top--];
        }
};

template<typename S> 
void suma_elementow(S s) {
    typename S::value_type total; 
    while(!s.is_empty()) {
        total = total + s.pop();
    }
    return total;
}


int main() {

    int a = 133, b = -1222;
    char c;

    std::cout<<maksimum(a, b)<<std::endl;
    std::cout<<maksimum2(b, a)<<std::endl;

    convert<char>(3);

    double x[3]={2.0,1.0, 13.0};
    double y[3]={9.0,0.0,-1.0};

    std::cout<<dot_product<3>(x,y)<<std::endl;
    std::cout<<dot_product<2>(x,y)<<std::endl;


    return 0;
}
