#include<iostream>
#include<queue>
#include<vector>
#include<functional>
#include<utility>
#include<climits>

using namespace std;

int heuristica(int fila, int columna, int destinoFila, int destinoColumna){
    return abs(fila - destinoFila) + abs(columna + destinoColumna);
}

vector<pair<int, int>> astar(int origenFila, int origenColumna, int destinoFila, int destinoColumna, int mapa[10][10], int costos[10][10], int distancia[10][10], pair<int, int> padre[10][10]){
    // Cola de prioridad, elemento con menor peso
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> cola;

    // Booleano para destino encontrado
    bool encontrado = false;

    // Movimientos ortogonales para filas y columnas
    int df[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    // Costo de llegar al origen es 0
    distancia[origenFila][origenColumna] = 0;

    int prioridadInicial = heuristica(origenFila,origenColumna, destinoFila, destinoColumna);

    // Insertar origen a la queue
    cola.push({prioridadInicial, {origenFila, origenColumna}});

    // Definir al padre del origen
    padre[origenFila][origenColumna] = {-1, -1};

    while(!cola.empty()){
        // Obtener el elemento de mayor prioridad
        pair<int, pair<int, int>> actual = cola.top();
        // Extraerlo de la queue
        cola.pop();
        // Recuperar la fila y columna
        int fila = actual.second.first;
        int columna = actual.second.second;
        int actual_priority = distancia[fila][columna] + heuristica(fila, columna, destinoFila, destinoColumna); 

        if(actual_priority < actual.first){
            continue;
        }

        // Comprobar destino
        if(fila == destinoFila && columna == destinoColumna){
            cout<<"Destino encontrado en ("<<fila<<","<<columna<<")"<<endl;
            encontrado = true;
            break;
        }

        // Recorre los 4 vecinos
        for(int i=0; i<4; i++){
            int nuevaFila = fila + df[i];
            int nuevaColumna = columna + dc[i];

            // Restriccion de grid
            if(nuevaFila>=0 && nuevaFila<10 && nuevaColumna>=0 && nuevaColumna<10){
                cout<<"("<<nuevaFila<<","<<nuevaColumna<<") esta dentro del grid"<<endl;

                // Evasion de obstaculos
                if(mapa[nuevaFila][nuevaColumna] != 1){
                    cout<<"("<<nuevaFila<<","<<nuevaColumna<<") es transitable"<<endl;
                    cout<<endl;

                    // Calcular costo tentativo por movimiento
                    int tentative_cost = distancia[fila][columna] + costos[nuevaFila][nuevaColumna];

                    // Calcular la prioridad de cada vecino
                    int priority = tentative_cost + heuristica(nuevaFila, nuevaColumna, destinoFila, destinoColumna);

                    // Si se encuentra un camino ccon menor costo, actualizarlo
                    if(tentative_cost<distancia[nuevaFila][nuevaColumna]){
                        // Actualizar distancia con tentative_cost
                        distancia[nuevaFila][nuevaColumna] = tentative_cost;

                        // Actualizar las coordenadas de padre
                        padre[nuevaFila][nuevaColumna] = {fila, columna};
                        
                        // Insertar priority en la queue
                        cola.push({priority, {nuevaFila, nuevaColumna}});

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
        cout<<"Distancia: "<<distancia[destinoFila][destinoColumna];
        cout<<endl;
        return camino;
    }else{
        cout<<"La ruta no existe!"<<endl;
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

    int costos[10][10]{
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

    // Matriz para reconstruir el camino
    pair<int, int> padre[10][10];

    // Matriz de ditancia
    int distancia[10][10];
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            distancia[i][j] = INT_MAX;
        }
    }

    vector<pair<int, int>> camino = astar(0, 0, 9, 9, mapa, costos, distancia, padre);

    cout<<"=====MAPA====="<<endl;
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            cout<<mapa[i][j]<<" ";
        }cout<<endl;
    }
    cout<<endl;

    cout<<"=====COSTOS====="<<endl;
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            cout<<costos[i][j]<<" ";
        }cout<<endl;
    }    
    cout<<endl;

    if(!camino.empty()){
        cout<<"Camino encontrado con "<<camino.size() - 1<<" pasos"<<endl;

        for(int i=0; i<camino.size(); i++){
            cout<<"("<<camino[i].first<<","<<camino[i].second<<")";
            if(i<camino.size() - 1)
                cout<<"->";
        }
        cout<<endl;
    }else{
        cout<<"No existe una ruta posible"<<endl;
    }

    return 0;
}