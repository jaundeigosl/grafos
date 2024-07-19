#pragma once

template<typename T>
class NodoArco;

template <typename T>
class NodoVertice{

    private:
        T info;
        NodoVertice<T> * prox;
        NodoArco<T> * listaAdj;
    public:

//######################################################################################
        NodoVertice(){      //CONSTRUCTOR VACIO
            prox = nullptr;
            listaAdj = nullptr;
        }
//######################################################################################
        NodoVertice( T newInfo){    //CONSTRUCTOR CON INFO
            info = newInfo;
            prox = nullptr;
            listaAdj = nullptr;
        }
//######################################################################################
        void setInfo(T newInfo){        //SETTER INFO
            info = newInfo;
        }
//######################################################################################
        void setProx(NodoVertice<T> * newProx){     //SETER PROX
            prox = newProx;
        }
//######################################################################################
        void setListaAdj(NodoArco<T> * newListaAdj){        //SETTER LISTA ADJ
            listaAdj = newListaAdj;
        }
//######################################################################################
        T getInfo(){        //GETTER INFO
            return info;
        }
//######################################################################################
        NodoVertice<T>* getProx(){     //GETTER PROX
            return prox;
        }
//######################################################################################
        NodoArco<T>* getListaAdj(){        //GETTER LISTA ADJ
            return listaAdj;
        }
//######################################################################################   
        ~NodoVertice(){
            prox = nullptr;
            listaAdj = nullptr;
        }

};