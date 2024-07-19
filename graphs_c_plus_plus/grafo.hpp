#pragma once

#include <iostream>
#include "nodoVertice.hpp"
#include "nodoArco.hpp"
#include <list>
#include <vector>
#include <queue>

template <typename T>
class Grafo{
    private:
        int nVertices, nArcos;
        NodoVertice<T> * primero;
    public:
//######################################################################################
        Grafo(){
            nVertices=0;
            nArcos=0;
            primero = nullptr;
        }
//######################################################################################
        Grafo(NodoVertice<T>* newPrimero){
            nVertices=1;
            nArcos=0;
            primero = newPrimero;
        }
//######################################################################################
    void insertarVertice(T newInfo){
        NodoVertice<T> * aux;
        bool encontrado = false;
        aux = primero;

        //Si no hay otro vertices
        if(primero == nullptr){
            primero = new NodoVertice(newInfo);
            nVertices = nVertices + 1;

            //hay almenos un vertice
        }else{

            //revisando que no exista ya el vertice
            while(aux!=nullptr && !encontrado){
                if(aux->getInfo() == newInfo){
                    encontrado = true;
                }else{
                    aux = aux->getProx();
                }
            }

            //si no se encontro
            if(!encontrado){
                //añadiendolo de primero
                aux = new NodoVertice(newInfo);
                aux->setProx(primero);
                primero = aux;

                nVertices = nVertices + 1;
            }
        }

    }
//######################################################################################
    void insertarArco(T vInicio , T vFinal, float peso){
        NodoVertice<T>*aux1,*aux2, *recorredor;
        NodoArco<T> *auxArco1;
        bool encontrado1 = false;
        bool encontrado2 = encontrado1;
        recorredor = primero;

        //recorriendo buscando el vertice de inicio y de final
        while(recorredor != nullptr && (!encontrado1||!encontrado2)){

            if(recorredor->getInfo()==vInicio){

                aux1 = recorredor;
                encontrado1 =true;
            }
            if(recorredor->getInfo()==vFinal){

                aux2 = recorredor;
                encontrado2 = true;
            }
            recorredor = recorredor->getProx();
        }

        //si ambos vertices se encontraron
        if(encontrado1 && encontrado2){
        
            //recorriendo los arcos revisando si ya existe
            auxArco1 = aux1->getListaAdj();
            encontrado1=false;
            while(auxArco1!=nullptr && !encontrado1){

                if(auxArco1->getInfo()== vFinal){
                    encontrado1 = true;
                }else{
                    auxArco1 = auxArco1->getProx();
                }
            }

            //Si no existia el arco entonces se añade
            if(!encontrado1){

                //añadiendo el arco
                auxArco1 = new NodoArco(aux2, peso);
                auxArco1->setProx(aux1->getListaAdj());
                aux1->setListaAdj(auxArco1);

                //Aumentando por los arcos añadidos
                nArcos= nArcos + 1;
            }
        }
    }
//######################################################################################
void eliminarArco(T vInicio, T vFinal){
    NodoVertice<T> * aux;
    NodoArco<T> * auxArco, *arcoAnterior;
    bool encontradoVertice = false;
    bool encontradoArco = false;
    aux = primero;

    //recorriendo hasta encontrar vInicio
    while(aux!=nullptr && !encontradoVertice){

        //Si se encuentra vInicio se obtienen sus arcos
        if(aux->getInfo()==vInicio){

            encontradoVertice = true;
            auxArco = aux->getListaAdj();

            //validando que tiene arcos
            if(auxArco!=nullptr){

                //si el primer arco es el que termina en vFinal entonces se elimina
                if(auxArco->getInfo()==vFinal){
                    aux->setListaAdj(auxArco->getProx());
                    delete auxArco;
                    nArcos = nArcos - 1;

                }else{

                    //Si esta en cualquier otra posicion
                    arcoAnterior = auxArco;
                    auxArco = auxArco->getProx();

                    //recorriendo el resto de arcos
                    while(auxArco!=nullptr && !encontradoArco){

                        //Si se encuentra se elimina
                        if(auxArco->getInfo()==vFinal){
                            arcoAnterior->setProx(auxArco->getProx());
                            encontradoArco = true;
                            delete auxArco;
                            nArcos = nArcos - 1;

                        }else{//Sino se sigue avanzando
                            arcoAnterior = auxArco;
                            auxArco = auxArco->getProx();
                        }
                    }
                }
            }
        }else{//Avanzado con el sigueinte vertice
            aux = aux->getProx();
        }
    }
}

//######################################################################################
    void eliminarVertice(T v){
        NodoVertice<T> * recorrido = primero;
        NodoVertice<T> * aux, *anterior;
        NodoArco<T> *auxArco, *arcoAnterior;
        bool encontrado, verticeEncontrado;
        
        aux = nullptr;
        verticeEncontrado = false;

        // recorriendo todos los vertices y eliminando los arcos que apunten a V
        while(recorrido!=nullptr){

            //Si se encuentra el nodo vertice objetivo, se deja marcado con un apuntador
            if(recorrido->getInfo()==v){

                aux = recorrido;
                verticeEncontrado = true;

            }else{

                encontrado = false;
                auxArco = recorrido->getListaAdj();

                //Si el primer nodoArco apunta a V, se elimina
                if(auxArco!=nullptr){
                    if(auxArco->getInfo()==v){

                        recorrido->setListaAdj(auxArco->getProx());
                        delete auxArco;
                        encontrado = true;

                        //actualizando la cantidad de arcos
                        nArcos = nArcos - 1;

                    }else{
                        //Donde es cualquier otro nodoArco el que apunta a V

                        arcoAnterior = auxArco;
                        auxArco = auxArco->getProx();

                        //recorriendo el resto de nodosArco para eliminar el que apunta a v
                        while(auxArco!=nullptr && !encontrado){

                            //eliminando el arco
                            if(auxArco->getInfo()==v){

                                arcoAnterior->setProx(auxArco->getProx());
                                delete auxArco;
                                encontrado = true;

                                //actualizando la cantidad de arcos
                                nArcos = nArcos - 1;

                            }else{
                                
                                //moviendose al siguiente arco
                                arcoAnterior = auxArco;
                                auxArco = auxArco->getProx();
                            }
                        }
                    }
                }
            }
            //avanzando de vertice
            if(!verticeEncontrado){
                anterior = recorrido;
            }
            recorrido = recorrido ->getProx();
        }
    
        //Si el vertice existe entonces se elimina
        if(aux!=nullptr){

            // primero eliminando los arcos del vertice objetivo
            auxArco = aux->getListaAdj();
            while(auxArco!=nullptr){

                aux->setListaAdj(auxArco->getProx());
                delete auxArco;
                auxArco = aux->getListaAdj();
                nArcos = nArcos - 1;
            }
            
            //Si el vertice a eliminar esta de primero
            if(aux == primero){

                primero = aux->getProx();
                delete aux;
                
                
            }else{

                //si esta en cualquier otra posicion
                anterior->setProx(aux->getProx());
                delete aux;
            }

            //actualizando el numero de vertices
            nVertices = nVertices - 1;
        }
        
    }

//######################################################################################
    std::list<T> getVertices(){
        std::list<T> vertices;
        NodoVertice<T> *recorrido;
        recorrido = primero;

        //recorriendo los vertices y guardandolos en una lista
        while(recorrido!=nullptr){

            vertices.push_back(recorrido->getInfo());
            recorrido = recorrido->getProx();
        }
        return vertices;
    }
//######################################################################################
// camino mas corto (en peso) dado dos vertices         Nota:El grafo debe estar mapeado
    void caminoMasCorto(T vInicio, T vFinal, std::list<T> &camino, float &acum, Grafo<T> &g){
        std::vector<float> acumulado;
        std::vector<T> anterior; 
        std::queue<T> recorrido;
        std::list<T> sucesores;
        T sucesor, actual;

        //reservando el tamaño igual a la cantidad de vertices
        anterior.reserve(nVertices);
        acumulado.reserve(nVertices);

        //inicializando los vectores
        for(int i = 0; i<acumulado.capacity();i++){
            acumulado[i]=-1;
            anterior[i]=-1;
        }

        //Cambiando el acumulado de donde empieza el camino
        acumulado[vInicio]=0;
        //el -2 indica que es el punto de inicio y no se cambiara durante el recorrido
        anterior[vInicio]=-2;
        //Insertandolo como primero en la cola
        recorrido.push(vInicio);

        
        while(!recorrido.empty()){
            
            //Se obtiene el siguiente en el recorrido
            actual = recorrido.front();

            //se obtienen sus sucesores
            sucesores = g.getSucesores(actual);

            //mientras tenga sucesores
            while(!sucesores.empty()){ 

                //Se obtiene el siguiente sucesor
                sucesor = sucesores.front();

                //Se comprueba si el camino es de menor peso que el ya usado o si es el primero en ser usado
                if(acumulado[sucesor]>(g.getPeso(actual,sucesor) + acumulado[actual]) || acumulado[sucesor]==-1){
                    
                    //se actualiza el acumulado
                    acumulado[sucesor] = g.getPeso(actual,sucesor) + acumulado[actual];

                    //Se actualiza el anterior
                    anterior[sucesor] = actual;

                    //se añade el sucesor a la cola
                    recorrido.push(sucesor);
                }

                //se elimina el sucesor actual de la lista para poder obtener el siguiente
                sucesores.pop_front();
            }
            //Se elimina el frente de la cola para seguir el recorrido
            recorrido.pop();
        }

        //obteniendo el maximo acumulado
        acum = acumulado[actual];

        //Guardando el camino conseguido  
        actual = vFinal;

       while(actual!=-2 && actual != -1){
            camino.push_front(actual);
            actual = anterior[actual];
        }
    }
//######################################################################################
    void caminoCortoRestriccion(T vInicio, T vFinal, std::list<T> &camino, float &acum, Grafo<T> &g, std::list<T> restricciones){
        std::vector<float> acumulado;
        std::vector<T> anterior; 
        std::queue<T> recorrido;
        std::list<T> sucesores;
        bool encontrado;
        std::list<int>::iterator it;
        T sucesor, actual;

        //reservando el tamaño igual a la cantidad de vertices
        anterior.reserve(nVertices);
        acumulado.reserve(nVertices);

        //inicializando los vectores
        for(int i = 0; i<acumulado.capacity();i++){
            acumulado[i]=-1;
            anterior[i]=-1;
        }

        //Cambiando el acumulado de donde empieza el camino
        acumulado[vInicio]=0;
        //el -2 indica que es el punto de inicio y no se cambiara durante el recorrido
        anterior[vInicio]=-2;
        //Insertandolo como primero en la cola
        recorrido.push(vInicio);

        
        while(!recorrido.empty()){
            
            //Se obtiene el siguiente en el recorrido
            actual = recorrido.front();

            //se obtienen sus sucesores
            sucesores = g.getSucesores(actual);

            //mientras tenga sucesores
            while(!sucesores.empty()){ 

                //Se obtiene el siguiente sucesor
                sucesor = sucesores.front();

                //verificando si esta en la lista de restricciones
                encontrado = false;
                it = restricciones.begin();

                while(it!=restricciones.end()){

                    if(*it == sucesor){

                        encontrado = true;
                    }
                    it++;
                }
                
                //Se comprueba si el camino es de menor peso que el ya usado o si es el primero en ser usado
                if((acumulado[sucesor]>(g.getPeso(actual,sucesor) + acumulado[actual]) || acumulado[sucesor]==-1) && !encontrado){
                    
    
                    //se actualiza el acumulado
                    acumulado[sucesor] = g.getPeso(actual,sucesor) + acumulado[actual];

                    //Se actualiza el anterior
                    anterior[sucesor] = actual;

                    //se añade el sucesor a la cola
                    recorrido.push(sucesor);
                }

                //se elimina el sucesor actual de la lista para poder obtener el siguiente
                sucesores.pop_front();
            }
            //Se elimina el frente de la cola para seguir el recorrido
            recorrido.pop();
        }

        //obteniendo el maximo acumulado
        acum = acumulado[actual];

        //Guardando el camino conseguido  
        actual = vFinal;

       while(actual!=-2 && actual != -1){
            camino.push_front(actual);
            actual = anterior[actual];
        }
    }

//######################################################################################
    //camino mas largo (en peso) para dos vertices dados        Nota:El grafo debe estar mapeado
    void caminoMasLargo(T vInicio, T vFinal, Grafo<T> &g, std::list<T> &caminoMax , float &acumMax){
        std::list<T> caminoAux;
        float acumAux = 0;
        std::vector<bool> visitados;

        //creando el vector de visitados y inicializandolo
        visitados.reserve(g.getNvertices());
        for(int i = 0; i < g.getNvertices();i++){
            visitados[i]=false;
        }

        //añadiendo el primero al camino
        visitados[vInicio]=true;
        caminoAux.push_back(vInicio);
        acumMax= 0;

        //encontrando el camino
        caminoLargo(vInicio,vFinal, g , visitados, caminoMax, caminoAux, acumMax, acumAux);

    }

    //backtracking para encontrar el camino mas largo entre dos vertices
    void caminoLargo(T vInicio, T vFinal, Grafo<T> &g, std::vector<bool> &visitados, std::list<T> &caminoMax, std::list<T> &caminoAct,float &acumMax, float acumAux ){
        T vecino;
        std::list<T> vecinos;

        //obteniendo los vecinos del primero
        vecinos = g.getSucesores(vInicio);

        //mientras haya vecinos
        while(!vecinos.empty()){

            vecino = vecinos.front();
            //se revisa si el vecino no ha sido visitado
            if(!visitados[vecino]){
                
                //Si no se ha visitado entonces es una opcion valida
                visitados[vecino] = true;
                acumAux = acumAux + g.getPeso(vInicio,vecino);
                caminoAct.push_back(vecino);
                
                //verificando si es solucion
                if(vecino == vFinal){

                    //verificando si es la mejor solucion
                    if(acumMax==0 || acumMax< acumAux){

                        acumMax = acumAux;
                        caminoMax.clear();
                        caminoMax = caminoAct;
                    }

                }else{//si no es solucion entonces se sigue 
                    caminoLargo(vecino, vFinal, g, visitados, caminoMax, caminoAct,acumMax,acumAux);
                }
                //borrando paso
                visitados[vecino]=false;
                acumAux = acumAux - g.getPeso(vInicio,vecino);
                caminoAct.pop_back();
            }
            //moviendote al siguiente vecino
            vecinos.pop_front();
        }
    }

//######################################################################################
//El grafo debe estar mapeado y ser no dirigido
void componentesConexas(Grafo<T> &g, int &nComponentes){ 
    std::vector<T> visitados;
    std::queue<T> recorrido;
    std::list<T> vecinos, componenteActual;
    std::list<std::list<T>> componentes;

    T vecino, actual;

    //inicializando el vector de visitados

    visitados.reserve(g.getNvertices());
    for(int i = 0; i < g.getNvertices(); i++){
        visitados[i]=false;
    }

    //recorriendo el grafo desde cada vertice 
    for(int i = 0; i < g.getNvertices();i++){

        if(!visitados[i]){//si el vertice no se ha visitado entonces se puede hacer el recorrido empezando por el

            //se añade el primero y se marca como visitado
            recorrido.push(i);
            visitados[i]=true;
            componenteActual.push_back(i);

            while(!recorrido.empty()){
                
                //se obtienen sus vecinos
                actual = recorrido.front();
                vecinos = g.getSucesores(actual);

                while(!vecinos.empty()){

                    vecino = vecinos.front();
                    //Si el vecino no se ha visitado entonces se añade a la componente y se marca
                    if(!visitados[vecino]){

                        visitados[vecino]=true;
                        recorrido.push(vecino);
                        componenteActual.push_back(vecino);

                    }
                    //obteniendo el siguiente vecino
                    vecinos.pop_front();
                }
                //siguiendo con el recorrido
                recorrido.pop();
            }
            //guardando la componente y limpiando la lista actual para el siguiente recorrido
            componentes.push_back(componenteActual);
            componenteActual.clear();
        }
    }

    //el numero de componentes es igual al numero de elementos de la lista 
    nComponentes = componentes.size();
}
//######################################################################################
    void encontrarArcosPuente(Grafo<T> &g, std::list<std::list<T>> &arcosPuente){
        int componentes;
        std::vector<bool> visitados;
        std::list<T> vecinos, arco;
        T vecino;
        float peso;

        //inicializando el vector de visitados
        visitados.reserve(g.getNvertices());
        for(int i = 0; i < g.getNvertices();i++){
            visitados[i]=false;
        }

        for(int i = 0; i < g.getNvertices();i++){

            //se marca como visitado al que se le va a revisar todos los arcos
            visitados[i]=true;
            //y se obtienen sus arcos
            vecinos = g.getSucesores(i);

            while(!vecinos.empty()){

                vecino = vecinos.front();
                //Si el arco no es con un vertice que ya se reviso
                if(!visitados[vecino]){

                    //se borra el arco
                    peso = g.getPeso(i,vecino);
                    g.eliminarArco(i,vecino);
                    g.eliminarArco(vecino,i);

                    //se busca la cantidad de componentes
                    componentesConexas(g,componentes);

                    //Si es arco puente entonces se guarda
                    if(componentes>1){
                        arco.push_back(i);
                        arco.push_back(vecino);
                        arcosPuente.push_back(arco);
                        arco.clear();
                    }

                    //restaurando el arco
                    g.insertarArco(i,vecino,peso);
                    g.insertarArco(vecino,i,peso);
                }

                //obteniendo el siguiente
                vecinos.pop_front();
            }
        }
    }
//######################################################################################
    void ordenamientoTopologico(Grafo<T> &g, std::list<T> elementos, std::list<T> &elementosOrdenados){
        T menor;
        std::vector<int> vertices;
        vertices.reserve(elementos.size());


        for(int i = 0; i < vertices.capacity(); i++){
            vertices[i]=elementos.front();
            g.insertarVertice(elementos.front());
            elementos.pop_front();
        }


        for(int i = 0 ; i < vertices.capacity(); i++){
            for(int j = 0; j < vertices.capacity(); j++){
                if(vertices[i]<vertices[j]){

                    g.insertarArco(vertices[i],vertices[j],0);
                }
            }
        }

        menor = vertices[0];
        for(int i = 0; i < vertices.capacity();i++){
            if(vertices[i]< menor){
                menor = vertices[i];
            }
        }



        modDFS(g,menor, elementosOrdenados);

    }

    void modDFS(Grafo<T> &g, T menor,std::list<T> &elementosOrdenados){
        std::list<T> vecinos;
        T nuevoMenor;

        auto it = elementosOrdenados.begin();
        elementosOrdenados.push_back(menor);
        
        for(int i = 1 ; i < g.getNvertices();i++){
            
            vecinos = g.getSucesores(menor);
            nuevoMenor = vecinos.front();
            it = vecinos.begin();
            std::cout<<" menor: "<<menor<<std::endl;

            while(it!=vecinos.end()){
                
                if(nuevoMenor > *it){

                    nuevoMenor = *it;
                }

                it++;
            }

            elementosOrdenados.push_back(nuevoMenor);
            menor = nuevoMenor;
            vecinos.clear();
        }
    }



//######################################################################################

void mostrarArcos(T v){
    NodoVertice<T> *aux;
    aux = primero;
    bool encontrado;
    NodoArco<T> * auxArco;

    //buscando el vertice
    while(aux!=nullptr && !encontrado){
        if(aux->getInfo()==v){
            encontrado = true;
        }else{
            aux = aux->getProx();
        }
    }

    //si el vertice existe entonces recorremos sus arcos y los mostramos
    if(encontrado){
        std::cout<<"vertice: "<<aux->getInfo()<<std::endl;
        auxArco = aux->getListaAdj();
        std::cout<<"arcos:"<<std::endl;
        while(auxArco!=nullptr){
            std::cout<<auxArco->getInfo()<<std::endl;
            auxArco=auxArco->getProx();
        }
    }
}
//######################################################################################    
    void mostrarVertices(){
        NodoVertice<T> *aux;
        aux = primero;
        while(aux!=nullptr){
            std::cout<<aux->getInfo()<<" ";
            aux = aux->getProx();
        }
    }

//######################################################################################
    bool existeVertice(T v){
        NodoVertice<T> * aux;
        bool encontrado;
        aux = primero;
        while(aux!=nullptr && !encontrado){
            if(aux->getInfo()==v){
                encontrado= true;
            }else{
                aux = aux->getProx();
            }
        }
        return encontrado;
    }
//######################################################################################
    bool existeArco(T vInicio, T vFinal){
        NodoVertice<T> * aux;
        NodoArco<T> * auxArco;
        bool encontradoVertice = false;
        bool encontradoArco = false;

        aux = primero;
        //recorriendo los vertices buscando vInicial
        while(aux!=nullptr && !encontradoVertice){

            if(aux->getInfo()==vInicio){

                auxArco = aux->getListaAdj();
                encontradoVertice = true;

                //Si se encuentra se busca su arco con vFinal
                while(auxArco!=nullptr && !encontradoArco){

                    if(auxArco->getInfo()==vFinal){
                        encontradoArco=true;
                    }else{
                        auxArco = auxArco->getProx();
                    }
                }
            }else{
                aux = aux->getProx();
            }
        }

        return encontradoArco;
    }
//######################################################################################
    float getPeso(T vInicio, T vFinal){
        NodoVertice<T> * aux;
        NodoArco<T> * auxArco;
        float pesoValor = -1;
        bool encontradoVertice = false;
        bool encontradoArco = false;

        aux = primero;
        //recorriendo los vertices buscando vInicial
        while(aux!=nullptr && !encontradoVertice){

            //Si estamos parados en vInicio obtenemos sus arcos
            if(aux->getInfo()==vInicio){

                auxArco = aux->getListaAdj();
                encontradoVertice = true;

                //Si se encuentra se busca su arco con vFinal
                while(auxArco!=nullptr && !encontradoArco){

                    //obteniendo el peso si se encuentra el arco deseado
                    if(auxArco->getInfo()==vFinal){

                        encontradoArco=true;
                        pesoValor = auxArco->getPeso();

                    }else{//sino se sigue avanzando
                        auxArco = auxArco->getProx();
                    }
                }
            }else{//sino seguimos buscando
                aux = aux->getProx();
            }
        }

        return pesoValor;
    }

//######################################################################################
    std::list<T> getSucesores(T v){

        NodoVertice<T> * aux = primero;
        NodoArco<T> * auxArco;
        bool encontrado = false;
        std::list<T> sucesores;

        //buscando el vertice deseado
        while(aux !=nullptr && !encontrado){

            //cuando lo encuentra obtenemos sus arcos y se guardan en la lista
            if(aux->getInfo()==v){

                auxArco = aux->getListaAdj();

                while(auxArco!=nullptr){

                    sucesores.push_back(auxArco->getInfo());
                    auxArco = auxArco->getProx();

                }
                encontrado = true;

            }else{//sino seguimos avanzando
                aux = aux->getProx();
            }
        }

        return sucesores;
    }
//######################################################################################
    void vaciar(){
        NodoVertice<T> * aux;
            aux = primero;
            while(aux!=nullptr){
                eliminarVertice(aux->getInfo());
                aux = primero;
            }
            primero = nullptr;
    }
//######################################################################################
    int getNvertices(){
        return nVertices;
    }
//######################################################################################
    int getNarcos(){
        return nArcos;
    }
//######################################################################################
    void mapearGrafo(Grafo<T> &gActual, Grafo<int> &gMapeado, std::vector<T> &vecActuales,std::vector<int> &vecMapeados){
        std::list<T> vertices, sucesores;
        T sucesor;
        int indice;
        float peso;

        vertices = gActual.getVertices();

        //reservando el espacio
        vecActuales.reserve(nVertices);
        vecMapeados.reserve(nVertices);

        //inicializando vertores e insertando los vertices en el grafo mapeado
        for(int i = 0; i < nVertices;i++){
            vecActuales[i] = vertices.front();
            vertices.pop_front();
            vecMapeados[i]=i;
            gMapeado.insertarVertice(i);
        }

        //añadiendo los arcos
        for(int i = 0; i < nVertices;i++){

            //obteniendo los sucesores del vertice actual
            sucesores = gActual.getSucesores(vecActuales[i]);

            //añadiendo todos los arcos del vertice actual con sus sucesores
            while(!sucesores.empty()){

                indice = 0;
                sucesor = sucesores.front();
                peso = gActual.getPeso(vecActuales[i],sucesor);

                //buscando el valor asignado al sucesor
                while(vecActuales[indice]!=sucesor){
                    indice++;
                }

                //insertando el arco entre el vertice actual y el sucesor actual
                gMapeado.insertarArco(i,indice,peso);

                //quitando el sucesor actual para poder obtener el siguiente
                sucesores.pop_front();
            }
        }
    }

//######################################################################################
    ~Grafo(){
        NodoVertice<T> * aux;
        aux = primero;
        while(aux!=nullptr){
            eliminarVertice(aux->getInfo());
            aux = primero;
        }
        primero = nullptr;
    }

};