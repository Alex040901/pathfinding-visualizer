#include<iostream>
#include<vector>
#include<stack>
#include <algorithm>

using namespace std; 

vector<pair<int, int>> dfs(int origenFila, int origenColumna, int destinoFila, int destinoColumna, int mapa[10][10]){
    stack<pair<int, int>> pila;
    bool encontrado = false;
    bool visited[10][10] = {};
    pair<int, int> padre[10][10];

    int df[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    pila.push({origenFila, origenColumna});
    visited[origenFila][origenColumna] = true;

    padre[origenFila][origenColumna] = {-1, -1};

    cout << "=== INICIANDO BUSQUEDA EN PROFUNDIDAD (DFS) ===" << endl
         << endl;

    while(!pila.empty()){
        pair<int, int> actual = pila.top();

        pila.pop();

        cout << "Sale de la pila: ("
        << actual.first << ", "
        << actual.second << ")" << endl;

        if(actual.first == destinoFila && actual.second == destinoColumna){
            cout<<"Destino encontrado ("<<actual.first<< ","<<actual.second<<")"<<endl;
            cout<<endl;
            encontrado = true;
            break;
        }
        
        for(int i=0; i<4; i++){

            int nuevaFila = actual.first + df[i];
            int nuevaColumna = actual.second + dc[i];

            if(nuevaFila>=0 && nuevaFila<10 && nuevaColumna>=0 && nuevaColumna<10){
                if(mapa[nuevaFila][nuevaColumna] == 0 && !visited[nuevaFila][nuevaColumna]){

                    // Marcar vecino como visitado
                    visited[nuevaFila][nuevaColumna] = true;

                    //Metemos al padre en actual
                    padre[nuevaFila][nuevaColumna] = actual;

                    //Meter al vecino en la pila
                    pila.push({nuevaFila, nuevaColumna});
                    
                    cout << "Entra a la pila: ("
                    << nuevaFila << ", "
                    << nuevaColumna << ")" << endl;
                }
            }
        }
    }

    pair<int, int> paso = {destinoFila, destinoColumna};
    vector<pair<int, int>> camino;

    if(encontrado){
        while(paso.first != -1 && paso.second != -1){
            camino.push_back(paso);

            paso = padre[paso.first][paso.second];
            }

            std::reverse(camino.begin(), camino.end());

            for(int i=0; i<camino.size(); i++){
                mapa[camino[i].first][camino[i].second] = 2;
            }
            return camino;
    }else{
        cout<<"La ruta no existe!"<< endl;
        return{};
    }
}

int main(){
    
    int mapa[10][10] = {
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0}
    }; 

    vector<pair<int, int>> camino = dfs(0, 0, 9, 9, mapa);

    cout<<"=====RECORRIDO====="<< endl;
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            cout<<mapa[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    if(!camino.empty()){
        cout<<"Camino encontrado con "<< camino.size()-1<<" pasos."<< endl;

        for(int i=0; i<camino.size(); i++){
            cout<<"("<<camino[i].first<<", "<<camino[i].second<<")";
            if(i < camino.size() - 1)cout<< " ->";
    }
    cout<<endl;

    }else{
    cout<<" No existe ruta posible."<<endl;
   }
    
   return 0;
}