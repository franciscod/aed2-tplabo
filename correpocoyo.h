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


#endif //CORREPOCOYO_H_
	
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
		primero = NULL;
		ultimo = NULL;
		camara = NULL;

		if(!otro.esVacia()){
			int i = 1;
			while(i <= otro.tamanio()){
				nuevoCorredor(otro.dameCorredorEnPos(i));			
				i++;
			}
			Nodo* enfocado = ultimo;
			while(enfocado->corredor != otro.corredorFilmado()){
				enfocado = enfocado->siguiente;
			}
			camara = enfocado;
		}
	}
	
	template<typename T>
	CorrePocoyo<T>::~CorrePocoyo(){
		Nodo* nodo = ultimo;
		while(nodo != NULL){
			Nodo* nodoABorrar = nodo;
			nodo = nodo->siguiente;
			delete nodoABorrar;
		}
	}

	template<typename T>
	void CorrePocoyo<T>::nuevoCorredor(const T& corredor){
		Nodo* nodoNuevo = new Nodo;
		nodoNuevo->corredor = corredor;
		nodoNuevo->anterior = NULL;
		if(ultimo == NULL){
			nodoNuevo->siguiente = NULL;

			primero = nodoNuevo;
			ultimo = nodoNuevo;

			cantidadCorredores = 1;
			camara = nodoNuevo;
		}	
		else{
			ultimo->anterior = nodoNuevo;
			nodoNuevo->siguiente = ultimo;
			
			ultimo = nodoNuevo;

			cantidadCorredores += 1;
		}
	}

	template<typename T>
	void CorrePocoyo<T>::nuevoCorredor(const T& corredor, const T& otroCorredor){
		Nodo* nodoNuevo = new Nodo;
		nodoNuevo->corredor = corredor;
		
		Nodo* nodoOtro = ultimo;
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
			primero = nodoNuevo;
		}

		nodoNuevo->anterior = nodoOtro;
		
		nodoOtro->siguiente = nodoNuevo;

		cantidadCorredores += 1;
	}

	template<typename T>
	void CorrePocoyo<T>::seCansa(const T& corredor){
		Nodo* nodoCansado = ultimo;
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
				ultimo = nodoSiguiente;
			}
			if(corredorFilmado() == corredor){
				camara = nodoSiguiente;
			}
		}
		else{
			if(nodoAnterior != NULL){
				nodoAnterior->siguiente = NULL;
				primero = nodoAnterior;
				if(corredorFilmado() == corredor){
					camara = nodoAnterior;
				}
			}
			else{
				primero = NULL;
				ultimo = NULL;
				if(corredorFilmado() == corredor){
					camara = NULL;
				}
			}
		}
		delete nodoCansado;
	}
	
	template<typename T>
	void CorrePocoyo<T>::sobrepasar(const T& corredor){
		Nodo* nodoCorredor = ultimo;
		while(nodoCorredor->corredor != corredor){
			nodoCorredor = nodoCorredor->siguiente;
		}
		Nodo* nodoSiguiente = nodoCorredor->siguiente;

		if(corredorFilmado() == corredor){
			camara = nodoSiguiente;
		}

		if(corredorFilmado() == nodoSiguiente->corredor){
			camara = nodoCorredor;
		}

		nodoCorredor->corredor = nodoSiguiente->corredor;
		nodoSiguiente->corredor = corredor;
	}

	template<typename T>
	const T& CorrePocoyo<T>::corredorFilmado() const{
		return camara->corredor;
	}
	
	template<typename T>
	void CorrePocoyo<T>::filmarProxPerdedor(){
		if(camara->anterior != NULL){
			camara = camara->anterior;
		}
	}

	template<typename T>
	void CorrePocoyo<T>::filmarProxExitoso(){
		if(camara->siguiente != NULL){
			camara = camara->siguiente;
		}
	}

	template<typename T>
	const T& CorrePocoyo<T>::damePrimero() const{
		return primero->corredor;
	}
	
	template<typename T>
	int CorrePocoyo<T>::damePosicion(const T& corredor) const{
		Nodo* nodoBuscado = primero;
		int posicion = 1;	
		while(nodoBuscado->corredor != corredor){
			nodoBuscado = nodoBuscado->anterior;
			posicion += 1;
		}
		return posicion;
	}
	
	template<typename T>
	const T& CorrePocoyo<T>::dameCorredorEnPos(int i) const{
		Nodo* nodoBuscado = primero;
		while(i > 1){
			nodoBuscado = nodoBuscado->anterior;
			i -= 1;
		}
		return nodoBuscado->corredor;
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
		bool sonIguales = true;
		if(tamanio() == otro.tamanio()){
			int i = 1;
			while(i <= tamanio()){
				if(dameCorredorEnPos(i) != otro.dameCorredorEnPos(i)){
					sonIguales = false;
					break;
				}
				i++;
			}	
		}
		else{
			sonIguales = false;
		}
		return sonIguales;
	}

	template<typename T>
	ostream& CorrePocoyo<T>::mostrarCorrePocoyo(ostream& o) const{
		o<<"[";
		Nodo* nodoCorredor = primero;
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
