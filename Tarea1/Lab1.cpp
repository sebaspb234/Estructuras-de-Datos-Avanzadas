#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iterator>
#include <map>
#include <unordered_map>
using namespace std;



int raa()
{
    return 1 + rand() % (1000 - 1);
}

template <typename T, typename R>
class Experimento
{

private:
    vector<vector<T>> matrix;

public:
    R roundoff(R value, unsigned char prec);// redondeo
    void generateran(vector<T>& arr);
    void printMatrix(vector<vector<T>> matrix);
    void generaMatriz(T datos, T dimension);
    R eu(vector<T> A, vector <T> B);
    void experimento(T datos, T dimension);
};

template <typename T, typename R>
R Experimento<T, R>::roundoff(R value, unsigned char prec)// redondeo
{
    R pow_10 = pow(10.0f, (R)prec);
    return round(value * pow_10) / pow_10;
}

template <typename T, typename R>
void Experimento<T, R>::generateran(vector<T>& arr)
{
    generate(arr.begin(), arr.end(), raa);
}

template <typename T, typename R>
void Experimento<T, R>::printMatrix(vector<vector<T>> matrix)
{
    typename vector<vector<T>>::iterator it;
    typename vector<T>::iterator i;
    for (it = matrix.begin(); it != matrix.end(); ++it)
    {
        for (i = (*it).begin(); i != (*it).end(); ++i)
        {
            cout << *i << " ";
        }cout << endl;
    }
}

template <typename T, typename R>
void Experimento<T, R>::generaMatriz(T datos, T dimension)
{

    for (int i = 0; i < datos; i++)
    {
        vector<T> arr(dimension);
        for (int j = 0; j < dimension; j++)
        {
            generateran(arr);
        }
        matrix.push_back(arr);
        arr.clear();
    }
}

template <typename T, typename R>
R Experimento<T, R>::eu(vector<T> A, vector <T> B)
{
    R res = 0;
    for (unsigned int i = 0; i < A.size(); i++)
    {
        res += pow((A[i] - B[i]), 2);
    }

    return sqrt(res);
}

template <typename T, typename R>
void Experimento<T, R>::experimento(T datos, T dimension)
{
    generaMatriz(datos, dimension);
    typename vector<vector<T>>::iterator it;
    vector<R> aux;
    for (it = matrix.begin() + 1; it != matrix.end(); it++)
    {
        aux.push_back(roundoff(eu(matrix[0], *it), 1));
    }


    map<R, T> cont;
    for (R i : aux)
        if (i != 0)
            cont[i]++;


    fstream fout;
    fout.open("exp.csv", ios::out | ios::app);

    for (auto i : cont)
    {
        fout << i.first << "\n";
    }
    for (auto i : cont)
    {

        fout << i.second << "\n";
    }
    matrix.clear();
}



int main() {
     
    Experimento<int, float> exp;
    exp.experimento(10000, 10);

    return 0;
}