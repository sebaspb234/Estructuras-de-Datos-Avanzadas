#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Fibonacci
{

private:
    T** A = new T* [2]; // Matriz que se usará para el Fibonacci logaritmico
    T** aux = new T* [2]; // Matriz auxiliar para obtener la potencia de A


public:
    Fibonacci();
    T fib_exponencial(T a); // Fibonacci recursivo - exponencial
    T fib_lineal(T num); // Fibonacci lineal iterativo
    T fib_lineal_array(T n); // Fibonacci lineal iterativo con array
    void printMatrix(T** A, T filas, T columnas); // Funcion para imprimir una matriz
    void mult(T** A, T** B); // Funcion que multiplica 2 matrices y el resultado se almacena en A
    void pow(T** A, T n); // Funcion que eleva a la potencia a la matriz A
    T fib_logaritmico(T n); // Fibonacci logaritmico
};

template <typename T>
Fibonacci<T>::Fibonacci() // Constructor
{
    for (T i = 0; i < 2; i++)
    {
        A[i] = new T[2];
        aux[i] = new T[2];
    }

    aux[0][0] = 0;
    aux[0][1] = 1;
    aux[1][0] = 1;
    aux[1][1] = 1;

    A[0][0] = 0;
    A[0][1] = 1;
    A[1][0] = 1;
    A[1][1] = 1;
}

template <typename T>
T Fibonacci<T>::fib_exponencial(T a) // Fibonacci recursivo - exponencial
{
    if (a == 1 || a == 0)
        return 1;
    else
        return fib_exponencial(a - 1) + fib_exponencial(a - 2); 
}

template <typename T>
T Fibonacci<T>::fib_lineal(T num) // Fibonacci lineal iterativo
{
    T a = 0;
    T b = 1;
    T c = 0;
    for (T i = 0; i <= num; i++)
    {
        c = a + b;
        b = a;
        a = c;
    }
    return c;
}

template <typename T>
T Fibonacci<T>::fib_lineal_array(T n) // Fibonacci lineal iterativo con array
{
    T base[] = { 0,1 };
    for (T i = 2; i <= n+1; ++i)
    {
        T next = base[0] + base[1];
        base[0] = base[1];
        base[1] = next;
    }
    return base[1];
}

template <typename T>
void Fibonacci<T>::printMatrix(T** M, T filas, T columnas) // Funcion para imprimir una matriz
{
    for (T i = 0; i < filas; i++)
    {
        for (T j = 0; j < columnas; j++)
        {
            cout << M[i][j] << " ";
        }cout << endl;
    }
}

template <typename T>
void Fibonacci<T>::mult(T** A, T** B) // Funcion que multiplica 2 matrices y el resultado se almacena en A
{
    T x = A[0][0] * B[0][0] + A[0][1] * B[1][0];
    T y = A[0][0] * B[0][1] + A[0][1] * B[1][1];
    T z = A[1][0] * B[0][0] + A[1][1] * B[1][0];
    T w = A[1][0] * B[0][1] + A[1][1] * B[1][1];

    A[0][0] = x;
    A[0][1] = y;
    A[1][0] = z;
    A[1][1] = w;
}

template <typename T>
void Fibonacci<T>::pow(T** A, T n) // Funcion que eleva a la potencia a la matriz A
{
    if (n == 0 || n == 1) return;
    
    pow(A, n / 2);
    mult(A, A);

    if (n % 2 != 0)
        mult(A, aux);
}

template <typename T>
T Fibonacci<T>::fib_logaritmico(T n) // Fibonacci logaritmico
{
    if (n == 0 || n == 1) return 1;
    pow(A, n);
    return A[1][1];
}

int main() {
    Fibonacci<int> fib;
    int n = 6;
    cout << "Exponencial(Recursivo) - Fibonacci de: " << n << " es: " << fib.fib_exponencial(n) << endl;
    cout << "Lineal(Iterativo) - Fibonacci de: " << n << " es: " << fib.fib_lineal(n) << endl;
    cout << "Lineal(Iterativo con array) - Fibonacci de: " << n << " es: " << fib.fib_lineal_array(n) << endl;
    cout << "Logaritmico - Fibonacci de: " << n << " es: " << fib.fib_logaritmico(n) << endl;

    return 0;
}
