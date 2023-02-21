#ifndef Abin_VEC0_H
#define Abin_VEC0_H

#include <cstdlib>
#include <cassert>

template <typename T> class AbinVec
{
public:
	typedef int nodo; // índice de la matriz
	// entre 0 y maxNodos-1
	static const nodo NODO_NULO;
	explicit AbinVec(size_t maxNodos); // constructor
	void insertarRaiz(const T& e);
	void insertarHijoIzqdo(nodo n, const T& e);
	void insertarHijoDrcho(nodo n, const T& e);
	void eliminarHijoIzqdo(nodo n);
	void eliminarHijoDrcho(nodo n);
	void eliminarRaiz();
	bool arbolVacio() const;
	const T& elemento(nodo n) const; // acceso a elto, lectura
	T& elemento(nodo n); // acceso a elto, lectura/escritura
	nodo raiz() const;
	nodo padre(nodo n) const;
	nodo hijoIzqdo(nodo n) const;
	nodo hijoDrcho(nodo n) const;
	AbinVec(const AbinVec<T>& A); // ctor. de copia
	AbinVec<T>& operator =(const AbinVec<T>& A); // asig. de árboles
	~AbinVec(); // destructor
	int alturaVec(nodo n);
	int profundidadVec(nodo n);
private:
	struct celda {
		T elto;
		nodo padre, hizq, hder;
	};
	celda* nodos; // vector de nodos
	int maxNodos; // tamaño del vector
	int numNodos; // número de nodos del árbol
};

/* Definición del nodo nulo */
template <typename T>
const typename AbinVec<T>::nodo AbinVec<T>::NODO_NULO(-1);
template <typename T>
inline AbinVec<T>::AbinVec(size_t maxNodos) :
	nodos(new celda[maxNodos]),
	maxNodos(maxNodos),
	numNodos(0)
{}

template <typename T>
inline void AbinVec<T>::insertarRaiz(const T& e)
{
	assert(numNodos == 0); // Árbol vacío
	numNodos = 1;
	nodos[0].elto = e;
	nodos[0].padre = NODO_NULO;
	nodos[0].hizq = NODO_NULO;
	nodos[0].hder = NODO_NULO;
}

template <typename T>
inline void AbinVec<T>::insertarHijoIzqdo(AbinVec<T>::nodo n, const T& e)
{
	assert(n >= 0 && n < numNodos); // Nodo válido
	assert(nodos[n].hizq == NODO_NULO); // n no tiene hijo izqdo.
	assert(numNodos < maxNodos); // Árbol no lleno
	// Añadir el nuevo nodo al final de la secuencia.
	nodos[n].hizq = numNodos;
	nodos[numNodos].elto = e;
	nodos[numNodos].padre = n;
	nodos[numNodos].hizq = NODO_NULO;
	nodos[numNodos].hder = NODO_NULO;
	++numNodos;
}
template <typename T>
inline void AbinVec<T>::insertarHijoDrcho(AbinVec<T>::nodo n, const T& e)
{
	assert(n >= 0 && n < numNodos); // Nodo válido
	assert(nodos[n].hder == NODO_NULO); // n no tiene hijo drcho.
	assert(numNodos < maxNodos); // Árbol no lleno
	// Añadir el nuevo nodo al final de la secuencia.
	nodos[n].hder = numNodos;
	nodos[numNodos].elto = e;
	nodos[numNodos].padre = n;
	nodos[numNodos].hizq = NODO_NULO;
	nodos[numNodos].hder = NODO_NULO;
	++numNodos;
}
template <typename T>
void AbinVec<T>::eliminarHijoIzqdo(AbinVec<T>::nodo n)
{
	nodo hizqdo;
	assert(n >= 0 && n < numNodos); // Nodo válido
	hizqdo = nodos[n].hizq;
	assert(hizqdo != NODO_NULO); // Existe hijo izqdo. de n.
	assert(nodos[hizqdo].hizq == NODO_NULO && // Hijo izqdo. de
		nodos[hizqdo].hder == NODO_NULO); // n es hoja.
	if (hizqdo != numNodos - 1)
	{
		// Mover el último nodo a la posición del hijo izqdo.
		nodos[hizqdo] = nodos[numNodos - 1];
		// Actualizar la posición del hijo (izquierdo o derecho)
		// en el padre del nodo movido.
		if (nodos[nodos[hizqdo].padre].hizq == numNodos - 1)
			nodos[nodos[hizqdo].padre].hizq = hizqdo;
		else
			nodos[nodos[hizqdo].padre].hder = hizqdo;
		// Si el nodo movido tiene hijos,
// actualizar la posición del padre.
		if (nodos[hizqdo].hizq != NODO_NULO)
			nodos[nodos[hizqdo].hizq].padre = hizqdo;
		if (nodos[hizqdo].hder != NODO_NULO)
			nodos[nodos[hizqdo].hder].padre = hizqdo;
	}
	nodos[n].hizq = NODO_NULO;
	--numNodos;
}
template <typename T>
void AbinVec<T>::eliminarHijoDrcho(AbinVec<T>::nodo n)
{
	nodo hdrcho;
	assert(n >= 0 && n < numNodos); // Nodo válido
	hdrcho = nodos[n].hder;
	assert(hdrcho != NODO_NULO); // Existe hijo drcho. de n.
	assert(nodos[hdrcho].hizq == NODO_NULO && // Hijo drcho. de
		nodos[hdrcho].hder == NODO_NULO); // n es hoja.
	if (hdrcho != numNodos - 1)
	{
		// Mover el último nodo a la posición del hijo drcho.
		nodos[hdrcho] = nodos[numNodos - 1];
		// Actualizar la posición del hijo (izquierdo o derecho)
		// en el padre del nodo movido.
		if (nodos[nodos[hdrcho].padre].hizq == numNodos - 1)
			nodos[nodos[hdrcho].padre].hizq = hdrcho;
		else
			nodos[nodos[hdrcho].padre].hder = hdrcho;
		// Si el nodo movido tiene hijos,
// actualizar la posición del padre.
		if (nodos[hdrcho].hizq != NODO_NULO)
			nodos[nodos[hdrcho].hizq].padre = hdrcho;
		if (nodos[hdrcho].hder != NODO_NULO)
			nodos[nodos[hdrcho].hder].padre = hdrcho;
	}
	nodos[n].hder = NODO_NULO;
	--numNodos;
}
template <typename T>
inline void AbinVec<T>::eliminarRaiz()
{
	assert(numNodos == 1);
	numNodos = 0;
}
template <typename T>
inline bool AbinVec<T>::arbolVacio() const
{
	return (numNodos == 0);
}
template <typename T>
inline const T& AbinVec<T>::elemento(AbinVec<T>::nodo n) const
{
	assert(n >= 0 && n < numNodos);
	return nodos[n].elto;
}
template <typename T>
inline T& AbinVec<T>::elemento(AbinVec<T>::nodo n)
{
	assert(n >= 0 && n < numNodos);
	return nodos[n].elto;
}
template <typename T>
inline typename AbinVec<T>::nodo AbinVec<T>::raiz() const
{
	return (numNodos > 0) ? 0 : NODO_NULO;
}
template <typename T> inline
typename AbinVec<T>::nodo AbinVec<T>::padre(AbinVec<T>::nodo n) const
{
	assert(n >= 0 && n < numNodos);
	return nodos[n].padre;
}
template <typename T> inline
typename AbinVec<T>::nodo AbinVec<T>::hijoIzqdo(AbinVec<T>::nodo n) const
{
	assert(n >= 0 && n < numNodos);
	return nodos[n].hizq;
}
template <typename T> inline
typename AbinVec<T>::nodo AbinVec<T>::hijoDrcho(AbinVec<T>::nodo n) const
{
	assert(n >= 0 && n < numNodos);
	return nodos[n].hder;
}
template <typename T>
AbinVec<T>::AbinVec(const AbinVec<T>& A) :
	nodos(new celda[A.maxNodos]),
	maxNodos(A.maxNodos),
	numNodos(A.numNodos)
{
	// Copiar el vector.
	for (nodo n = 0; n <= numNodos - 1; n++)
		nodos[n] = A.nodos[n];
}
template <typename T>
inline AbinVec<T>::~AbinVec()
{
	delete[] nodos;
}
template <typename T>
AbinVec<T>& AbinVec<T>::operator =(const AbinVec<T>& A)
{
	if (this != &A) // Evitar autoasignación.
	{
		// Destruir el vector y crear uno nuevo si es necesario.
		if (maxNodos != A.maxNodos)
		{
			delete[] nodos;
			maxNodos = A.maxNodos;
			nodos = new celda[maxNodos];
		}
		// Copiar el vector.
		numNodos = A.numNodos;
		for (nodo n = 0; n <= numNodos - 1; n++)
			nodos[n] = A.nodos[n];
	}
	return *this;
}

template <typename T>
int AbinVec<T>::alturaVec(AbinVec<T>::nodo n)
{
	if (n == NODO_NULO)
		return -1;
	else
		return 1 + max(alturaVec(nodos[n].hizq), alturaVec(nodos[n].hder));
}

template <typename T>
int AbinVec<T>::profundidadVec(AbinVec<T>::nodo n)
{
	int i = 0;

	while (n != 0)		// n es un indice, la raiz esta guardada en la pos 0 del vector, por tanto si n = 0, es la raiz. Seria equivalente a que el padre de n sea nodo nulo (es la raiz)
	{
		n = nodos[n].padre;
		i++;
	}
	return i;
}
#endif // AbinVec_VEC0_H