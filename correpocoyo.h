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
		Nodo* atras;
		Nodo* adelante;
	};

	int cantidadCorredores;
	Nodo* primero;
	Nodo* ultimo;
	Nodo* camara;

	bool estaCorredor(const T&) const;
	Nodo* darNodoConCorredor(const T&);
};

template<class T>
ostream& operator<<(ostream& out, const CorrePocoyo<T>& a) {
	return a.mostrarCorrePocoyo(out);
}

// Implementación a hacer por los alumnos.

	template<typename T>
	CorrePocoyo<T>::CorrePocoyo(){

		this->cantidadCorredores = 0;
		this->primero = NULL;
		this->ultimo = NULL;
		this->camara = NULL;

	}

	template<typename T>
	CorrePocoyo<T>::CorrePocoyo(const CorrePocoyo<T>& otro){

		this->cantidadCorredores = 0;
		this->primero = NULL;
		this->ultimo = NULL;
		this->camara = NULL;

		Nodo *c = otro.primero;

		while (c != NULL) {
			this->nuevoCorredor(c->corredor);
			if (c == otro.camara) {
				this->camara = this->ultimo;
			}
			c = c->atras;
		}
	}

	template<typename T>
	CorrePocoyo<T>::~CorrePocoyo(){
		Nodo* n = this->primero;
		Nodo* bye;
		while (n != NULL) {
			bye = n;
			n = n->atras;
			delete bye;
		}
	}

	template<typename T>
	void CorrePocoyo<T>::nuevoCorredor(const T& corredor){

		if (this->estaCorredor(corredor)) {
			return; // ignora agregar a uno que ya estaba
		}

		Nodo* n = new Nodo();
		n->corredor = T(corredor);
		n->adelante = NULL;
		n->atras = NULL;

		if (this->esVacia()) {
			this->primero = n;
			this->ultimo  = n;
			this->camara  = n;
		} else {
			this->ultimo->atras = n;
			n->adelante  = this->ultimo;
			this->ultimo = n;
		}

		this->cantidadCorredores++;
	}

	template<typename T>
	void CorrePocoyo<T>::nuevoCorredor(const T& corredor, const T& delanteDe){

		if (this->estaCorredor(corredor)) {
			return; // ignora agregar a uno que ya estaba
		}

		Nodo* n = new Nodo();
		n->corredor = corredor;
		n->adelante = NULL;
		n->atras = NULL;

		Nodo *c = darNodoConCorredor(delanteDe);

		n->adelante  = c->adelante;

		if (n->adelante != NULL) {
			n->adelante->atras = n;
		}

		n->atras = c;
		n->atras->adelante = n;

		if (c == this->primero) {
			this->primero = n;
		}

		this->cantidadCorredores++;
	}

	template<typename T>
	void CorrePocoyo<T>::seCansa(const T& corredor){

		Nodo *c = darNodoConCorredor(corredor);

		Nodo* bye = c;
		if (this->camara == bye) {
			if (bye->atras != NULL) {
				this->camara = bye->atras;
			} else {
				this->camara = bye->adelante;
			}
		}

		if (bye == this->primero) {
			this->primero = bye->atras;
		} else {
			bye->adelante->atras = bye->atras;
		}

		if (bye == this->ultimo) {
			this->ultimo = bye->adelante;
		} else {
			bye->atras->adelante = bye->adelante;
		}

		delete bye;
	}

	template<typename T>
	void CorrePocoyo<T>::sobrepasar(const T& corredor){

		Nodo *c = darNodoConCorredor(corredor);

		Nodo * d = c->adelante;

		c->adelante  = d->adelante;
		if (c->adelante != NULL) {
			c->adelante->atras = c;
		}

		d->atras = c->atras;
		if (d->atras != NULL) {
			d->atras->adelante = d;
		}

		c->atras = d;
		d->adelante  = c;

		if (d == this->primero) {
			this->primero = c;
		}

		if (c == this->ultimo) {
			this->ultimo = d;
		}
	}

	template<typename T>
	const T& CorrePocoyo<T>::corredorFilmado() const{

		return this->camara->corredor;
	}

	template<typename T>
	void CorrePocoyo<T>::filmarProxPerdedor(){

		this->camara = this->camara->atras;
		if (this->camara == NULL) {
			this->camara = this->ultimo;
		}
	}

	template<typename T>
	void CorrePocoyo<T>::filmarProxExitoso(){

		this->camara = this->camara->adelante;
		if (this->camara == NULL) {
			this->camara = this->primero;
		}
	}

	template<typename T>
	const T& CorrePocoyo<T>::damePrimero() const{
		return this->primero->corredor;
	}

	template<typename T>
	int CorrePocoyo<T>::damePosicion(const T& corredor) const{
		unsigned int pos = 1;
		Nodo *c = this->primero;

		while (!(c->corredor == corredor)) {
			pos++;
			c = c->atras;
		}

		return pos;
	}

	template<typename T>
	const T& CorrePocoyo<T>::dameCorredorEnPos(int i) const{

		int pos = 1;
		Nodo *c = this->primero;

		while (pos != i) {
			pos++;
			c = c->atras;
		}

		return c->corredor;
	}

	template<typename T>
	bool CorrePocoyo<T>::esVacia() const{
		return this->cantidadCorredores == 0;
	}

	template<typename T>
	int CorrePocoyo<T>::tamanio() const{
		return this->cantidadCorredores;
	}

	template<typename T>
	bool CorrePocoyo<T>::operator==(const CorrePocoyo<T>& otro) const{

		if ( !( (this->primero->corredor == otro.damePrimero())
		   && (this->camara->corredor == otro.corredorFilmado())
		   && (this->cantidadCorredores == otro.tamanio()))
		) {
			return false;
		}

		for (int i=1; i<=(this->cantidadCorredores); i++) {
			if (!(this->dameCorredorEnPos(i) == otro.dameCorredorEnPos(i))) {
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
				c = c->atras;
			}
			o << c->corredor;
		}

		o << "]";
		return o;
	}


	template<typename T>
	bool CorrePocoyo<T>::estaCorredor(const T& corredor) const{

		Nodo *c = this->primero;

		while ((c != NULL) && !(c->corredor == corredor)) {
			c = c->atras;
		}

		return c != NULL;
	}
	
	template<typename T>
	typename CorrePocoyo<T>::Nodo * CorrePocoyo<T>::darNodoConCorredor(const T& corredor){
		Nodo *c = this->primero;
		while (!(c->corredor == corredor)) {
			c = c->atras;
		}
		return c;
	}
#endif //CORREPOCOYO_H_
