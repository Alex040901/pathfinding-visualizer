#include<iostream>
#include<queue>
#include<vector>
#include<functional>
#include<utility>
#include<climits>

using namespace std;

vector<pair<int, int>> dijkstra(int origenFila, int origenColumna, int destinoFila, int destinoColumna, int mapa[10][10], int costos[10][10]){
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> cola; 
    bool visitado[10][10] = {};
    bool encontrado = false;
    pair<int, int> padre[10][10];
    
    int df[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    int distancia[10][10];
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            distancia[i][j] = INT_MAX;
        }
    }
    distancia[origenFila][origenColumna] = 0;

    cout<<"=====MAPA DISTANCIAS====="<<endl;
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            cout<<distancia[i][j]<<" ";
        }cout<<endl;
    }  
    cout<<endl; 

    cola.push({0, {origenFila, origenColumna}});

    padre[origenFila][origenColumna] = {-1, -1};

    cout << "Distancia origen: "
     << distancia[origenFila][origenColumna] << endl;

    while(!cola.empty()){
        pair<int, pair<int, int>> actual = cola.top();
        cout<<"Actual: "<<endl<<"Distancia: "<<actual.first<<endl<<"Fila: "<<actual.second.first<<endl<<"Columna: "<<actual.second.second<<endl;
        cout<<endl;
        cola.pop();

        if(distancia[actual.second.first][actual.second.second]<actual.first){
            continue;
        }
        
        if(actual.second.first == destinoFila && actual.second.second == destinoColumna){
            cout<<"Destino encontrado en: {"<<actual.second.first<<", "<<actual.second.second<<"}"<<endl;
            encontrado = true;
            break;
        }

        for(int i=0; i<4; i++){
            // Vecina
            int nuevaFila = actual.second.first + df[i];
            int nuevaColumna = actual.second.second + dc[i];

            if(nuevaFila>=0 && nuevaFila<10 && nuevaColumna>=0 && nuevaColumna<10){
                cout<<"{"<<nuevaFila<<","<<nuevaColumna<<"} dentro del grid"<<endl;

                if(mapa[nuevaFila][nuevaColumna] != 1){
                    cout<<"{"<<nuevaFila<<","<<nuevaColumna<<"} transitable"<<endl;
                    cout<<endl;

                    int tentative_cost = actual.first + costos[nuevaFila][nuevaColumna];

                    if(tentative_cost<distancia[nuevaFila][nuevaColumna]){
                        //Actualizar distancia con el menor costo
                        distancia[nuevaFila][nuevaColumna] = tentative_cost;
                        //Guardar las coordenadas padre para reconstruir el camino
                        padre[nuevaFila][nuevaColumna] = {actual.second.first, actual.second.second};
                        //Insertar la coordenada vecina en la cola para explorar después
                        cola.push({tentative_cost, {nuevaFila, nuevaColumna}});

                        cout << "Actualizando {" << nuevaFila << ", "
                        << nuevaColumna << "} con costo "
                        << tentative_cost << endl;
                    }
                }
            }

        }
    }cout<<endl;

    pair<int, int> paso = {destinoFila, destinoColumna};
    vector<pair<int, int>> camino;

    if(encontrado){
    while(paso.first != -1 && paso.second != -1){
        camino.push_back(paso);
        paso = padre[paso.first][paso.second];
    }

    std::reverse(camino.begin(), camino.end());
    int costo_total = 0;
    
    for(int i=0; i<camino.size(); i++){
        mapa[camino[i].first][camino[i].second] = 2;
    }

    for(int i=1; i<camino.size(); i++){
        int fila = camino[i].first;
        int columna = camino[i].second;

        costo_total += costos[fila][columna];
    }
    cout<<"Costo total: "<<costo_total<<endl;
    cout<<"Distancia: "<<distancia[destinoFila][destinoColumna]<<endl;
    cout<<endl;
    return camino;   

}else{
    cout<<"La ruta no existe!"<< endl;
    return{};
}
}

int main(){

    int mapa[10][10] = {
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 0, 0}
    };

    int costos[10][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {5, 1, 9, 1, 5, 9, 9, 1, 1, 1},
        {1, 5, 1, 9, 1, 5, 1, 9, 1, 5},
        {1, 1, 5, 1, 9, 1, 5, 1, 9, 1},
        {9, 1, 1, 5, 1, 9, 1, 5, 1, 1},
        {1, 5, 9, 1, 1, 1, 9, 1, 5, 1},
        {5, 1, 1, 9, 5, 1, 1, 9, 1, 5},
        {1, 9, 1, 1, 5, 9, 1, 1, 5, 1},
        {1, 5, 9, 1, 1, 5, 9, 1, 1, 5},
        {9, 1, 5, 1, 9, 1, 5, 1, 1, 1}
    };

    vector<pair<int, int>> camino = dijkstra(0, 0, 9, 9, mapa, costos);

    cout<<"=====MAPA COSTOS====="<<endl;
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            cout<<costos[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    cout<<"=====MAPA OBSTACULOS====="<<std::endl;
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            cout<<mapa[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    if(!camino.empty()){
        cout<<"Camino encontrado con: "<<camino.size() - 1<<" pasos"<<endl;

        for(int i=0; i<camino.size(); i++){
            cout<<"{"<<camino[i].first<<","<<camino[i].second<<"}";
            if(i<camino.size() - 1)
                cout<<"->";
            }
            cout<<endl;
    }else{
            cout<<"No existe una ruta posible"<<endl;
    }
    
    return 0;
}