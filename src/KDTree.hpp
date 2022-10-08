// Copyright

#ifndef SRC_KDTREE_HPP_
#define SRC_KDTREE_HPP_

#include <cmath>
#include <iostream>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>
#include "Point.hpp"
using namespace std;

template <size_t N, typename ElemType> 
struct KDTreeNode
{
    Point<N> point; //Punto del nodo de N dimensiones
    ElemType value;
    KDTreeNode<N, ElemType>* nodes[2];
    KDTreeNode(Point<N> p, ElemType x)
    {
        point = p;
        value = x;
        nodes[0] = nodes[1] = nullptr;
    }
};


template <size_t N, typename ElemType>
class KDTree {
 public:
  typedef std::pair<Point<N>, ElemType> value_type;

  KDTree();

  ~KDTree();

  KDTree(const KDTree &rhs);
  KDTree &operator=(const KDTree &rhs);

  size_t dimension() const;

  size_t size() const;
  bool empty() const;

  bool contains(const Point<N> &pt) const;

  void insert(const Point<N> &pt, const ElemType &value);

  ElemType &operator[](const Point<N> &pt);

  ElemType &at(const Point<N> &pt);
  const ElemType &at(const Point<N> &pt) const;

  ElemType knn_value(const Point<N> &key, size_t k) const;

  std::vector<ElemType> knn_query(const Point<N> &key, size_t k) const;

  bool find(const Point<N>& pt, KDTreeNode<N, ElemType>**& p);

  mutable KDTreeNode<N, ElemType>* root;
  void neighbors(const Point<N> key, KDTreeNode<N, ElemType>* current_node, vector<ElemType>& nearest_neighbors_candidates, int depth) const;

 private:
  size_t dimension_;
  size_t size_;
};

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree() {
    root = nullptr;
    dimension_ = N;
    size_ = 0;
  // TODO(me): Fill this in.
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::~KDTree() {
  // TODO(me): Fill this in.
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree(const KDTree &rhs) { // arbol que recibe referencia de otro subarbol
    root = nullptr;
    dimension_ = rhs.dimension_;
    size_ = rhs.size_;
  // TODO(me): Fill this in.
}

template <size_t N, typename ElemType>
KDTree<N, ElemType> &KDTree<N, ElemType>::operator=(const KDTree &rhs) { // operador = para inicializar un arbol
  // TODO(me): Fill this in.
    dimension_ = rhs.dimension_;
    size_ = rhs.size_;
    root = rhs.root;
  return *this;
}

template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::dimension() const {
  // TODO(me): Fill this in.
  return dimension_;
}

template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::size() const {
  // TODO(me): Fill this in.
  return size_;
}

template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::empty() const {
  // TODO(me): Fill this in.
  if(size_) return false;
  return true;
}

// find
template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::find(const Point<N>& pt, KDTreeNode<N, ElemType>**& p){ // devuelve el puntero a puntero en la posicion del nodo
    // TODO(me): Fill this in.
   
    int cont = 0;
    for (p = &root; (*p) && (*p)->point != pt; p = &((*p)->nodes[pt[cont % N] > (*p)->point[cont % N]]), cont++); // Si la coordenada actual es menor al punto, va a la derecha
    return *p != nullptr; // si (*p) lo encontró,  devuelve 1
}

template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::contains(const Point<N> &pt) const { 
  // TODO(me): Fill this in.
    KDTreeNode<N, ElemType>** p;
    int cont = 0;
    for (p = &root; (*p) && (*p)->point != pt; p = &((*p)->nodes[pt[cont % N] > (*p)->point[cont % N]]), cont++); // Si la coordenada actual es menor al punto, va a la derecha
    return *p != nullptr; // si (*p) lo encontró,  devuelve 1


}

template <size_t N, typename ElemType>
void KDTree<N, ElemType>::insert(const Point<N> &pt, const ElemType &value) {
  
  KDTreeNode<N, ElemType>** p;
  int cont = 0;
  for (p = &root; (*p) && (*p)->point != pt; p = &((*p)->nodes[pt[cont % N] > (*p)->point[cont % N]]), cont++);
  if (!(*p))
  {
      *p = new KDTreeNode<N, ElemType>(pt, value); // Si no está el punto, lo añade y size aumenta en uno.
      size_++; 
  }
  else // Si el punto ya existe en el KD-Tree, su valor es sobreescrito
  {
      (*p)->value = value;
  } 
}

template <size_t N, typename ElemType>
ElemType &KDTree<N, ElemType>::operator[](const Point<N> &pt) {
    KDTreeNode<N, ElemType>** p;
    int cont = 0;
    for (p = &root; (*p) && (*p)->point != pt; p = &((*p)->nodes[pt[cont % N] > (*p)->point[cont % N]]), cont++);
    if (!(*p)) // Si el punto no existe, se crea un nodo con el valor por defecto de ElemType
    {
        ElemType element = ElemType(); // Valor por defecto del tipo ElemType
        *p = new KDTreeNode<N, ElemType>(pt, element); // Si no está el punto, lo añade y size aumenta en uno.
        size_++;
    }
    return (*p)->value; //Retorna una referencia al valor asociado
}

template <size_t N, typename ElemType>
ElemType &KDTree<N, ElemType>::at(const Point<N> &pt) {
    KDTreeNode<N, ElemType>** p;
    int cont = 0;
    for (p = &root; (*p) && (*p)->point != pt; p = &((*p)->nodes[pt[cont % N] > (*p)->point[cont % N]]), cont++);
    if (!(*p)) // Si no encuentra el punto, lanza una excepción de fuera de rango
    {
        throw out_of_range(" Estas fuera del rango. ");
    }
    else
        return (*p)->value; // Retorna una referencia al valor asociado
}

template <size_t N, typename ElemType>
const ElemType &KDTree<N, ElemType>::at(const Point<N> &pt) const {
    KDTreeNode<N, ElemType>** p;
    int cont = 0;
    for (p = &root; (*p) && (*p)->point != pt; p = &((*p)->nodes[pt[cont % N] > (*p)->point[cont % N]]), cont++);
    if (!(*p)) // Si no encuentra el punto, lanza una excepción de fuera de rango
    {
        throw out_of_range(" Estas fuera del rango. ");
    }
    else
        return (*p)->value; // Retorna una referencia al valor asociado
}


template <size_t N, typename ElemType>
void KDTree<N, ElemType>::neighbors(const Point<N> key, KDTreeNode<N, ElemType>* current_node, vector<ElemType>& nearest_neighbors_candidates, int depth) const
{
    if (!current_node)
    {
        return;
    }

}

template <size_t N, typename ElemType>
ElemType KDTree<N, ElemType>::knn_value(const Point<N> &key, size_t k) const {
  // TODO(me): Fill this in.
  ElemType new_element;
  return new_element;
}

template <size_t N, typename ElemType>
std::vector<ElemType> KDTree<N, ElemType>::knn_query(const Point<N> &key,
                                                     size_t k) const {
  // TODO(me): Fill this in.
  std::vector<ElemType> values;
  return values;
}

// TODO(me): finish the implementation of the rest of the KDTree class

#endif  // SRC_KDTREE_HPP_
