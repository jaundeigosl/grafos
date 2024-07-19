#pragma once

template <typename T>
class NodoArco{
    private: 
        NodoVertice<T> * info;
        NodoArco * prox; 
        float peso;
    public:
//######################################################################################
    NodoArco(){
        info = nullptr;
        prox = nullptr;
        peso = 0;
    }
//######################################################################################
    NodoArco(NodoVertice<T> * newInfo){
        info  = newInfo;
        prox = nullptr;
        peso = 0;
    }
//######################################################################################
    NodoArco(NodoVertice<T>* newInfo, float newPeso){
        info = newInfo;
        peso = newPeso;
        prox = nullptr;
    }
//######################################################################################
    void setInfo(NodoVertice<T> * newInfo){
        info = newInfo;
    }
//######################################################################################
    void setProx(NodoArco<T> * newProx){
        prox = newProx;
    }
//######################################################################################
    void setPeso(float newPeso){
        peso = newPeso;
    }
//######################################################################################
    float getPeso(){
        return peso;
    }

//######################################################################################
    T getInfo(){
        return info->getInfo();
    }
//######################################################################################
    NodoVertice<T> * getInfoNodo(){
        return info;
    }

//######################################################################################
    NodoArco<T>* getProx(){
        return prox;
    }
//######################################################################################
    ~NodoArco(){
        info = nullptr;
        prox = nullptr;
        peso = 0;
    }

};