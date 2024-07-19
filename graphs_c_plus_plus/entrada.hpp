
/*

    std::string lectura,valor;
    std::list<std::string> restriccion;
    char auxChar;
    if(!std::cin.eof()){

        //lectura de lista en corchetes (enteros)
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

            auto it = elementos.begin();
            while(it != elementos.end()){
                std::cout << *it << " ";
                it++; 
            }

        }



        //lectura de lista en corchetes (strings)
        std::cin>>lectura;
        std::cin.get(auxChar);
        std::cin.get(auxChar);
        std::cin.get(auxChar);
        std::cin.get(auxChar);

        while(auxChar!='\n'){
            std::cin >> lectura;
            for(int i = 0; i < lectura.size()-1;i++){
                valor = valor + lectura[i];
            }
            restriccion.push_back(valor);
            valor = "";
            std::cin.get(auxChar);

        }


        
        //lectura de vertices y arcos

        std::string vertice1, vertice2;
        Grafo<std::string> g;
        float peso;
        while(!std::cin.eof()){
            std::cin>>vertice1;
            std::cin>>vertice2;
            std::cin>>peso;

            g.insertarVertice(vertice1);
            g.insertarVertice(vertice2);
            g.insertarArco(vertice1,vertice2,peso);
            g.insertarArco(vertice2,vertice1,peso);
        }
    }

    Grafo<int> mapeado;
        std::vector<std::string> vertOriginales;
        std::vector<int>vertMapeados;

        g.mapearGrafo(g,mapeado,vertOriginales,vertMapeados);


    //mapeando la restriccion
    int i = 0;
        std::list<int> restriccionMapeada;
        while(!restriccion.empty()){
            while(restriccion.front()!=vertOriginales[i]){
                i++;
            }
            restriccionMapeada.push_back(i);
            restriccion.pop_front();
            i = 0;
        }



*/