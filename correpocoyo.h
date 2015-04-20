#ifndef CORREPOCOYO_H_
#define CORREPOCOYO_H_

#include <iostream>
#include <cassert>
using namespace std;

/*
 * Se puede asumir que el tipo T tiene constructor por copia y operator==
 * No se puede asumir que el tipo T tenga operator=
 */
template<typename T>
class CorrePocoyo{

  public:

	/*
	 * Crea una nueva carrera
	 */
	CorrePocoyo();

	/*
	 * Una vez copiada, ambas CorrePocoyos deben ser independientes,
	 * es decir, cuando se borre una no debe borrar la otra.
	 */
	CorrePocoyo(const CorrePocoyo<T>&);

	/*
	 * Acordarse de liberar toda la memoria!
	 */
	~CorrePocoyo();

	/*
	 * Agrega un nuevo corredor al CorrePocoyo. Lo agregará al final
	 */
	void nuevoCorredor(const T&);

	/*
	 * Agrega un nuevo corredor al CorrePocoyo. El primer T es el corredor a agregar y lo hace delante del segundo
	 *
	 * PRE: Existe el segundo corredor
	 */
	void nuevoCorredor(const T&, const T&);

	/*
	 * Elimina del pocoyo al que se envía
	 *
	 * PRE: Existe el corredor
	 */
	void seCansa(const T&);

	/*
	 * El corredor pasa al que está adelante
	 *
	 * PRE: Existe un corredor delante de él y T es un corredor
	 */
	void sobrepasar(const T&);

	/*
	 * Devuelve el corredor que está siendo filmado.
	 *
	 * PRE: Hay adeptos en la CorrePocoyo.
	 */
	const T& corredorFilmado() const;

    /*
	 * Devuelve el próximo elemento según el orden dado.
	 * Pasa a filmar al corredor de atás
	 *
	 * PRE: Hay corredore en la CorrePocoyo.
	 */
	void filmarProxPerdedor();

	/*
	 * Devuelve el próximo elemento según el orden dado.
	 * Pasa a filmar al corredor de adelante
	 *
	 * PRE: Hay corredore en la CorrePocoyo.
	 */
	void filmarProxExitoso();

	/*
	 * Devuelve al Primero.
	 *
	 * PRE: Hay elementos
	 */
	const T& damePrimero() const;

	/*
	 * Devuelve la posición del elemento pasado por parámetro.
	 *
	 * PRE: Existe ese corredor
	 */
	int damePosicion(const T& ) const;

	/*
	 * Devuelve el corredor de la posición.
	 *
	 * PRE: Existe al menos esa cantidad de corredores en la carrera
	 */
	const T& dameCorredorEnPos(int) const;

	/*
	 * Dice si la CorrePocoyo tiene o no corredores.
	 */
	bool esVacia() const;

	/*
	 * Devuelve la cantidad de corredores de la CorrePocoyo.
	 */
	int tamanio() const;

	/*
	 * Devuelve true si las CorrePocoyos son iguales.
	 */
	bool operator==(const CorrePocoyo<T>&) const;

	/*
	 * Debe mostrar la carrera por el ostream (y retornar el mismo).
	 * CorrePocoyo vacio: []
	 */
	ostream& mostrarCorrePocoyo(ostream&) const;


  private:
	/*
	 * No se puede modificar esta funcion.
	 */
	CorrePocoyo<T>& operator=(const CorrePocoyo<T>& otra) {
		assert(false);
		return *this;
	}

	/*
	 * Aca va la implementación del nodo.
	 */
	struct Nodo {
		T corredor;
		Nodo* siguiente;
		Nodo* anterior;
	};

	int cantidadCorredores;
	Nodo* primero;
	Nodo* ultimo;
	Nodo* camara;
};

template<class T>
ostream& operator<<(ostream& out, const CorrePocoyo<T>& a) {
	return a.mostrarCorrePocoyo(out);
}

// Implementación a hacer por los alumnos.

	template<typename T>
	CorrePocoyo<T>::CorrePocoyo(){
		cantidadCorredores = 0;
		primero = NULL;
		ultimo = NULL;
		camara = NULL;
	}

	template<typename T>
	CorrePocoyo<T>::CorrePocoyo(const CorrePocoyo<T>& otro){

		cantidadCorredores = 0;

		Nodo *c = otro.primero;

		Nodo* n = new Nodo();
		n->corredor = c->corredor;

		this->primero = n;
		this->camara = n;

		this->cantidadCorredores++;

		c = c->siguiente;

		Nodo* m;

		while (c != NULL) {
			m = n;
			n = new Nodo();
			n->corredor = c->corredor;

			n->anterior = m;
			m->siguiente = n;

			this->ultimo = n;

			if (c == otro.camara) {
				this->camara = n;
			}

			this->cantidadCorredores++;
			c = c->siguiente;

		}

		this->ultimo = n;

	}

	template<typename T>
	CorrePocoyo<T>::~CorrePocoyo(){
		while (this->primero != NULL) {
			this->seCansa(this->primero->corredor);
		}
	}

	template<typename T>
	void CorrePocoyo<T>::nuevoCorredor(const T& corredor){

		Nodo* n = new Nodo();
		n->corredor = corredor;

		if (this->esVacia()) {
			this->primero = n;
			this->ultimo  = n;
			this->camara  = n;
		} else {
			this->ultimo->siguiente = n;
			n->anterior  = this->ultimo;
			this->ultimo = n;
		}

		this->cantidadCorredores++;
	}

	template<typename T>
	void CorrePocoyo<T>::nuevoCorredor(const T& corredor, const T& delanteDe){

		Nodo* n = new Nodo();
		n->corredor = corredor;

		Nodo *c = this->primero;

		while (c->corredor != delanteDe) {
			c = c->siguiente;
		}

		n->anterior  = c->anterior;

		if (n->anterior != NULL) {
			n->anterior->siguiente = n;
		}

		n->siguiente = c;
		n->siguiente->anterior = n;

		if (c == this->primero) {
			this->primero = n;
		}

		this->cantidadCorredores++;
	}

	template<typename T>
	void CorrePocoyo<T>::seCansa(const T& corredor){

		Nodo *c = this->primero;

		while (c->corredor != corredor) {
			c = c->siguiente;
		}

		Nodo* bye = c;


		if (bye == this->primero) {
			this->primero = bye->siguiente;
		} else {
			bye->anterior->siguiente = bye->siguiente;
		}

		if (bye == this->ultimo) {
			this->ultimo = bye->anterior;
		} else {
			bye->siguiente->anterior = bye->anterior;
		}

		delete bye;
	}

	template<typename T>
	void CorrePocoyo<T>::sobrepasar(const T& corredor){

		Nodo *c = this->primero;

		while (c->corredor != corredor) {
			c = c->siguiente;
		}

		Nodo * d = c->anterior;

		c->anterior  = d->anterior;
		if (c->anterior != NULL) {
			c->anterior->siguiente = c;
		}

		d->siguiente = c->siguiente;
		if (d->siguiente != NULL) {
			d->siguiente->anterior = d;
		}

		c->siguiente = d;
		d->anterior  = c;

		if (d == this->primero) {
			this->primero = c;
		}

		if (c == this->ultimo) {
			this->ultimo = d;
		}
	}

	template<typename T>
	const T& CorrePocoyo<T>::corredorFilmado() const{

		return camara->corredor;
	}

	template<typename T>
	void CorrePocoyo<T>::filmarProxPerdedor(){

		this->camara = this->camara->siguiente;
		if (this->camara == NULL) {
			this->camara = this->primero;
		}
	}

	template<typename T>
	void CorrePocoyo<T>::filmarProxExitoso(){

		this->camara = this->camara->anterior;
		if (this->camara == NULL) {
			this->camara = this->ultimo;
		}
	}

	template<typename T>
	const T& CorrePocoyo<T>::damePrimero() const{
		return primero->corredor;
	}

	template<typename T>
	int CorrePocoyo<T>::damePosicion(const T& corredor) const{
		unsigned int pos = 1;
		Nodo *c = this->primero;

		while (c->corredor != corredor) {
			pos++;
			c = c->siguiente;
		}

		return pos;
	}

	template<typename T>
	const T& CorrePocoyo<T>::dameCorredorEnPos(int i) const{

		int pos = 1;
		Nodo *c = this->primero;

		while (pos != i) {
			pos++;
			c = c->siguiente;
		}

		return c->corredor;
	}

	template<typename T>
	bool CorrePocoyo<T>::esVacia() const{
		return cantidadCorredores == 0;
	}

	template<typename T>
	int CorrePocoyo<T>::tamanio() const{
		return cantidadCorredores;
	}

	template<typename T>
	bool CorrePocoyo<T>::operator==(const CorrePocoyo<T>& otro) const{

		if (  (this->primero->corredor != otro.damePrimero())
		   || (this->camara->corredor != otro.corredorFilmado())
		   || (this->cantidadCorredores != otro.tamanio())
		) {
			return false;
		}

		for (int i=1; i<=(this->cantidadCorredores); i++) {
			if (this->dameCorredorEnPos(i) != otro.dameCorredorEnPos(i)) {
				return false;
			}
		}

		return true;
	}

	template<typename T>
	ostream& CorrePocoyo<T>::mostrarCorrePocoyo(ostream& o) const{
		o << "[";

		Nodo *c = this->primero;
		if (c != NULL) {
			while (c != this->ultimo){
				o << (c->corredor);
				o << ", ";
				c = c->siguiente;
			}
			o << c->corredor;
		}

		o << "]";
		return o;
	}

#endif //CORREPOCOYO_H_
