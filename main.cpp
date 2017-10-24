#include <iostream>

class A {
public:
    int& operator[](std::ptrdiff_t i) {
        return a[i];
    }

    int& operator*() {
        return a[0];
    }

    A* operator&() {
        return this;
    }

    A* operator->() {
        return this;
    }

    template <typename T1, typename T2>
    T1& operator->*(T1 T2::* p) {
        return this->*p;
    }

    int a[6] = {0, 1, 2, 3, 4, 5};
    static int const i = 10;
    static int const j;
};

int const A::j = 15;

class B: public A {
};

B& operator*(B& t) {
    return t;
}

template <typename T1, typename T2>
T1& operator->*(B& b, T1 T2::* p) {
    std::cout << __func__ << std::endl;
    return b.*p;
}

int main() {
    A a;
    B b;

    /* Subscript inside class definition */
    std::cout << a[0] << std::endl;

    {
        /* Built-in Subscript outside class definition */

        // T& operator[](T*, std::ptrdiff_t);
        // T& operator[](std::ptrdiff_t, T*);

        int a[6] = {0, 1, 2, 3, 4, 5};
        auto p = &a[2];
        std::cout << p[1] << p[-1] << 1[p] << (-1)[p] << std::endl;
    }

    /* Indirection inside class definition */
    std::cout << *a << std::endl;

    /* Indirection outside class definition */
    std::cout << (*b)[1] << std::endl;

    /* Address-of inside class definition */
    std::cout << (&a)->a[2] << std::endl;

    /* Member of object */
    std::cout << a.i << std::endl;
    std::cout << *(&a.j) << std::endl; // ODR-use

    /* Member of pointer inside class definition */
    std::cout << a->a[1] << std::endl;

    int (A::* a_)[6] = &A::a;

    /* Built-in Pointer to member of object */
    std::cout << (a.*a_)[2] << std::endl;

    /* Pointer to member of pointer inside class definition */
    std::cout << (a->*a_)[3] << std::endl;

    /* Built-in pointer to member of pointer */
    auto pa = &a;
    std::cout << (pa->*a_)[4] << std::endl;

    /* Pointer to member of pointer outside class definition */
    auto pb = &b;
    std::cout << (pb->*a_)[5] << std::endl;
}
