#include <iostream>
using namespace std;
/************************************************
*												*
*		Template: Clase Stack.					*
*		Autor: patricio Tula					*
*		Materia: Algoritmos y programacion ii	*
*												*
************************************************/
#ifndef __STACK_H__
#define __STACK_H__

template<typename T>
class Stack
{
	private:
		// Clase anidada.
		class StackNode
		{
			friend class Stack;
			private:
				StackNode* under_;
				T data_;
			public:
				StackNode(T const &);
				~StackNode();
		};

	StackNode *top_;

	public:
		typedef T data_t;
		typedef StackNode node_t;

		// Constructores y destructor.
		Stack();
		Stack(const Stack &);
		~Stack();

		// Operadores sobrecargados.
		Stack const &operator=(Stack const &);
		bool operator==(const Stack &)const;
		bool operator!=(const Stack &)const;

		// Funciones generales
		T pop();
		void push(const T &);
		bool empty() const;
		T const top()const;
};


//****************************
// Constructores y destructor.
//****************************
//Constructor parametrizado de la clase nodo del Stack.
template<typename T>
Stack<T>::StackNode::StackNode(const T & t) : under_(0), data_(t)
{
}

//Destructor de la clase nodo del Stack.
template<typename T>
Stack<T>::StackNode::~StackNode()
{
}

//Constructor por defecto de la clase Stack.
template<typename T>
Stack<T>::Stack() : top_(0)
{
}

//Constructor copia de la clase de la clase Stack.
template<typename T>
Stack<T>::Stack(const Stack &orig) : top_(0)//inicializa al primer nodo a 0.
{
	//Este método copia de en profundidad  el Stack original, desde el nodo top_ hasta el nodo que se encuentra más abajo.
	if(!orig.empty())
	{
		//El objeto p apunta a los elementos del Stack original.
		node_t* p = orig.top_;
		//Se copia dinamicamente el contenido del nodo al que apunta p en el top_ del Stack copia.
		top_ = new StackNode(p->data_);
		//El objeto q apunta al top_ recien creado del Stack copia.
		node_t* q = top_;
		//Pasamos al siguiente nodo a copiar en el Stack original.
		p = p->under_;
		//Mientras que p no apunte al elemento que se encuentra en el fondo del Stack, se copiarán uno por uno los elementos del Stack original al copiado.
		while(p)
		{
			q->under_ = new StackNode(p->data_);
			q = q->under_;
			p = p->under_;
		}
	}
	//Si el Stack a copiar esta vacio el constructor copia genera un Stack con su único atributo, top_, en 0.
	//El funcionamiento en este caso será igual que el constructor por defecto de la clase.
}

//Destructor de la clase Stack.
template<typename T>
Stack<T>::~Stack()
{
	//Recorre todos los nodos del Stack destruyendo uno por uno. Desde el top_ hasta el último elemento.
	for (node_t *p = top_; p; )
	{
		node_t *q = p->under_;
		delete p;
		p = q;
	}
}


//****************************
// Funciones en general.
//****************************
//Método para apilar en el Stack.
template<typename T>
void Stack<T>::push(const T &t)
{
	//Crea dinámicamente un nodo con el dato que queremos guardar.
	node_t *p = new StackNode(t);
	//Le asigna al puntero a under_ de la clase StackNode el nodo que se encuentra en el top_ de la estructura.
	p->under_ = top_;
	//Finalmente lo ubica como elemento top_ en el Stack.
	top_ = p;
}

//Método para desapilar en el Stack.
template<typename T>
T Stack<T>::pop()
{
	//Almacena en d el valor del dato que contiene el top_ del Stack.
	data_t d = top_->data_;	
	//El objeto q apunta al nodo que se encuentra abajo del top_.
	node_t *q = top_->under_;
	//Destruimos a top_.
	delete top_;
	//A top_ le asignamos el nodo apuntado por q.
	top_ = q;
	//devuelve el dato desapilado.
	return d;
}

//Método para verificar si el Stack se encuentra vacio.
template<typename T>
bool Stack<T>::empty() const
{
	//verifica si el top_ de la estructura apunta a algo o no.
	return top_ ? false : true;
}

//Método para obtención del elemento top de la clase.
template<typename T>
T const Stack<T>::top()const
{
	return top_->data_;
}

//****************************
// Operadores sobrecargados.
//****************************
//Método de sobrecarga del operador igual.
template<typename T>
Stack<T> const & Stack<T>::operator=(Stack const & orig)
{
	//Verifica que el Stack orig no sea el mismo objeto que al que queremos asignar, si así fuere el método no realiza nada.
	if (this != & orig)
	{
		//Si orig no esta vacio, destruimos los que pueda hacer en el contenido de objeto asignar y copiamos la estructura del objeto asignado en este.
		if(!orig.empty())
		{
			//Si el objeto a asignar se encuentra vacio destruimos su contenido.
			if(!this->empty())
			{
				for (node_t *p = top_; p; )
				{
					node_t *q = p->under_;
					delete p;
					p = q;
				}
			}
			//Copiamos de forma similar que en el constructor copia los elementos de orig al objeto a asignar.
			node_t* p = orig.top_;
			top_ = new StackNode(p->data_);
			node_t* q = top_;
			p = p->under_;
			while(p)
			{
				q->under_ = new StackNode(p->data_);
				q = q->under_;
				p = p->under_;
			}
		}
		//Caso complementario, si orig se encontrara vacio unicamente le asignamos 0 al top de la estructura a asignar.
		else
			top_=0;
	}
	return *this;
}

//Método de sobrecarga del operador igual que.
template<typename T>
bool Stack<T>::operator==(const Stack & comp)const
{
	node_t* p = top_;
	node_t* q = comp.top_;
	//comparamos nodo por nodo en los dos objetos Stack.
	while( p && q )
	{
		if( p->data_ == q->data_ )
		{
			q=q->under_;
			p=p->under_;
			continue;
		}
		else
			return false;
	}
	//Verificamos que ambos objetos sean del mismo tamaño.
	if(!p && q || !q && p)
		return false;

	return true;
}

//Método de sobrecarga del operador distinto de.
template<typename T>
bool Stack<T>::operator!=(const Stack & comp)const
{
	//Caso complementario del operador igual que
	return comp == *this ? false : true;
}


#endif
