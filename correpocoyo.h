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
	Nodo* nodoPrimero;
	Nodo* nodoUltimo;
	Nodo* camara;
};

template<class T>
ostream& operator<<(ostream& out, const CorrePocoyo<T>& a) {
	return a.mostrarCorrePocoyo(out);
}

// Implementación a hacer por los alumnos.


#endif //CORREPOCOYO_H_
	
	template<typename T>
	CorrePocoyo<T>::CorrePocoyo(){
		cantidadCorredores = 0;
		nodoPrimero = NULL;
		nodoUltimo = NULL;
		camara = NULL;
	}
	
	template<typename T>
	CorrePocoyo<T>::CorrePocoyo(const CorrePocoyo<T>& otro){
	}
	
	template<typename T>
	CorrePocoyo<T>::~CorrePocoyo(){
	}

	template<typename T>
	void CorrePocoyo<T>::nuevoCorredor(const T& corredor){
		Nodo* nodoNuevo = new Nodo;
		nodoNuevo->corredor = corredor;
		nodoNuevo->anterior = NULL;
		if(nodoUltimo == NULL){
			nodoNuevo->siguiente = NULL;

			nodoPrimero = nodoNuevo;
			nodoUltimo = nodoNuevo;

			cantidadCorredores = 1;
			camara = nodoNuevo;
		}	
		else{
			nodoUltimo->anterior = nodoNuevo;
			nodoNuevo->siguiente = nodoUltimo;
			
			nodoUltimo = nodoNuevo;

			cantidadCorredores += 1;
		}
	}

	template<typename T>
	void CorrePocoyo<T>::nuevoCorredor(const T& corredor, const T& otroCorredor){
		Nodo* nodoNuevo = new Nodo;
		nodoNuevo->corredor = corredor;
		
		Nodo* nodoOtro = nodoUltimo;
		while(nodoOtro->corredor != otroCorredor){
			nodoOtro = nodoOtro->siguiente;
		}
		Nodo* nodoSiguienteOtro = nodoOtro->siguiente;

		if(nodoSiguienteOtro != NULL){
			nodoSiguienteOtro->anterior = nodoNuevo;
			nodoNuevo->siguiente = nodoSiguienteOtro;
		}
		else{
			nodoNuevo->siguiente = NULL;
			nodoPrimero = nodoNuevo;
		}

		nodoNuevo->anterior = nodoOtro;
		
		nodoOtro->siguiente = nodoNuevo;

		cantidadCorredores += 1;
	}

	template<typename T>
	void CorrePocoyo<T>::seCansa(const T& corredor){
		Nodo* nodoCansado = nodoUltimo;
		while(nodoCansado->corredor != corredor){
			nodoCansado = nodoCansado->siguiente;
		}

		Nodo* nodoSiguiente = nodoCansado->siguiente;
		Nodo* nodoAnterior = nodoCansado->anterior;
		if(nodoSiguiente != NULL){
			nodoSiguiente->anterior = nodoAnterior;
			if(nodoAnterior != NULL){
				nodoAnterior->siguiente = nodoSiguiente;
			}
			else{
				nodoUltimo = nodoSiguiente;
			}
			if(corredorFilmado() == corredor){
				camara = nodoSiguiente;
			}
		}
		else{
			if(nodoAnterior != NULL){
				nodoAnterior->siguiente = NULL;
				nodoPrimero = nodoAnterior;
				if(corredorFilmado() == corredor){
					camara = nodoAnterior;
				}
			}
			else{
				nodoPrimero = NULL;
				nodoUltimo = NULL;
				if(corredorFilmado() == corredor){
					camara = NULL;
				}
			}
		}
		delete nodoCansado;
	}
	
	template<typename T>
	void CorrePocoyo<T>::sobrepasar(const T& corredor){
		Nodo* nodoCorredor = nodoUltimo;
		while(nodoCorredor->corredor != corredor){
			nodoCorredor = nodoCorredor->siguiente;
		}
		Nodo* nodoSiguiente = nodoCorredor->siguiente;
		Nodo* nodoAnterior = nodoCorredor->anterior;

		nodoSiguiente->anterior = nodoAnterior;

		if(nodoAnterior != NULL){
			nodoAnterior->siguiente = nodoSiguiente;
		}
		else{
			nodoUltimo = nodoSiguiente;
		}

		nodoCorredor->anterior = nodoSiguiente;
		nodoCorredor->siguiente = nodoSiguiente->siguiente;

		nodoSiguiente->siguiente = nodoCorredor;

		if(nodoCorredor->siguiente == NULL){
			nodoPrimero = nodoCorredor;
		}
	}
	
	template<typename T>
	const T& CorrePocoyo<T>::corredorFilmado() const{
		return camara->corredor;
	}
	
	template<typename T>
	void CorrePocoyo<T>::filmarProxPerdedor(){
	}
	
	template<typename T>
	void CorrePocoyo<T>::filmarProxExitoso(){
	}
	
	template<typename T>
	const T& CorrePocoyo<T>::damePrimero() const{
		return nodoPrimero->corredor;
	}
	
	template<typename T>
	int CorrePocoyo<T>::damePosicion(const T& corredor) const{
		return 0;	//TODO
	}
	
	template<typename T>
	const T& CorrePocoyo<T>::dameCorredorEnPos(int i) const{
		return nodoPrimero->corredor;	//TODO
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
		return true;	//TODO
	}

	template<typename T>
	ostream& CorrePocoyo<T>::mostrarCorrePocoyo(ostream& o) const{
		o<<"[";
		Nodo* nodoCorredor = nodoPrimero;
		if(nodoCorredor != NULL){
			o<<nodoCorredor->corredor;
			while(nodoCorredor->anterior != NULL){
				nodoCorredor = nodoCorredor->anterior;
				o<<", "<<nodoCorredor->corredor;
			}
		}
		o<<"]";
		return o;
	}
