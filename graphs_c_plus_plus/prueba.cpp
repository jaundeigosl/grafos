#include <iostream>
#include "nodoVertice.hpp"
#include "nodoArco.hpp"
#include "grafo.hpp"
#include <vector>
#include <list>

int main(){
    /*
    NodoVertice nodo1 (4);  
    NodoVertice<int> * aux = &nodo1;
    NodoArco<int> * auxArco;

    std::cout<<aux->getInfo()<<std::endl;
    nodo1.setProx(new NodoVertice(7));
    aux = aux->getProx();
    std::cout<<aux->getInfo()<<std::endl;
    nodo1.setListaAdj(new NodoArco(nodo1.getProx()));
    aux->setListaAdj(new NodoArco(&nodo1));
    auxArco = nodo1.getListaAdj();
    std::cout<<auxArco->getInfo()<<std::endl;
    auxArco = aux->getListaAdj();
    std::cout<<auxArco->getInfo()<<std::endl;
    */
    /*
   Grafo<int> grafo;
   grafo.insertarVertice(1);
   grafo.insertarVertice(3);
   grafo.insertarVertice(2);
   grafo.insertarVertice(4);
   grafo.insertarArco(2,4,0);
   grafo.insertarArco(2,1,0);
   grafo.insertarArco(1,3,0);
   grafo.eliminarVertice(5); 
   std::list<int> algo; 
   algo = grafo.getVertices();
   auto it = algo.begin();
   while(it != algo.end()){
    std::cout<<*it<<std::endl;
    it++;
   }
   grafo.mostrarArcos(3);
   std::cout<<grafo.existeArco(1,4);
    */

    Grafo<std::string> grafo;
    Grafo<int> grafoMapeado;
    std::list<std::string> vertices, sucesores;
    std::string vInicio, vFinal,aux;
    std::vector<std::string>vectorVertices;
    std::vector<int> vectorMapeados;
    int contador = 0;
    int indice = 0;
    float peso;


    //lectura de lista en corchetes
    int lectura;
    std::list<int> elementos;
    char auxChar;
    if(!std::cin.eof()){

        std::cin.get(auxChar);
        while(auxChar!=']'){
            std::cin >> lectura;
            std::cin.get(auxChar);
            elementos.push_back(lectura);
        }       
         
        Grafo<int> g;       
        std::list<int> listaOrdenada;
        g.ordenamientoTopologico(g,elementos,listaOrdenada); 

        auto it = listaOrdenada.begin();
        while(it != listaOrdenada.end()){
            std::cout << *it << " "; 
            it++; 
        }
    }


    return 0; 
}