#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> bfs(int origenFila, int origenColumna, int destinoFila, int destinoColumna, int mapa[10][10]){
    queue<pair<int, int>> cola;
    bool encontrado = false;
    // Matriz booleana para registrar las celdas ya exploradas
    bool visitado[10][10] = {};
    pair<int, int> padre[10][10];
    // Definimos los desplazamientos en el grid (Arriba, Abajo, Izquierda, Derecha)
    int df[4] = {-1, 1, 0, 0}; // filas
    int dc[4] = {0, 0, -1, 1}; // columnas

    // Ingresamos la coordenada de inicio a la cola
    cola.push({origenFila, origenColumna});

    // Marcamos la celda de inicio como visitada
    visitado[origenFila][origenColumna] = true;

    // Padre de 0, 0
    padre[origenFila][origenColumna] = {-1, -1};

    cout << "=== INICIANDO BUSQUEDA EN ANCHURA (BFS) ===" << endl
         << endl;

    while (!cola.empty())
    {
        // Copiamos la coordenada del frente a actual
        pair<int, int> actual = cola.front();

        // Quitamos la coordenada del frente de la cola
        cola.pop();

        cout << "Explorando: ("
             << actual.first << ", "
             << actual.second << ")" << endl;

        if (actual.first == destinoFila && actual.second == destinoColumna){
            cout << "Destino encontrado! " << actual.first << " ," << actual.second;
            encontrado = true;
            break;
        }

        // Recorremos los 4 movimientos posibles alrededor de la celda actual
        for (int i = 0; i < 4; i++)
        {

            // Calculamos las coordenadas de la celda vecina
            int nuevaFila = actual.first + df[i];
            int nuevaColumna = actual.second + dc[i];

            // Restricción de movimientos en grid
            if (nuevaFila >= 0 && nuevaFila < 10 && nuevaColumna >= 0 && nuevaColumna < 10)
            {
                // Validacion de celda transitable y no visitada
                if (mapa[nuevaFila][nuevaColumna] == 0 && !visitado[nuevaFila][nuevaColumna])
                {

                    // Marcamos la celda vecina como visitada
                    visitado[nuevaFila][nuevaColumna] = true;

                    // Guardamos las coordenadas actuales en la matriz padre
                    padre[nuevaFila][nuevaColumna] = actual;
                    cout << "Padre: " << nuevaFila << " ," << nuevaColumna << endl;

                    // Agregamos la celda vecina a la cola
                    cola.push({nuevaFila, nuevaColumna});

                }
                else if (mapa[nuevaFila][nuevaColumna] == 0 && visitado[nuevaFila][nuevaColumna])
                {
                    cout << "La posicion " << nuevaFila << ", " << nuevaColumna << " ya se visito" << endl;
                }
                else
                {
                    cout << "La posicion " << nuevaFila << ", " << nuevaColumna << " es obstaculo" << endl;
                }
            }
            else
            {
                cout << "La posicion " << nuevaFila << ", " << nuevaColumna << " esta fuera del grid" << endl;
            }
        }
    }
    cout << endl;
    pair<int, int> paso = {destinoFila, destinoColumna};
    // Guardar coordenadas de la ruta
    vector<pair<int, int>> camino;

    if(encontrado){
    while (paso.first != -1 && paso.second != -1){
        camino.push_back(paso); // Guardar las coordenadas actuales
        paso = padre[paso.first][paso.second]; // Retrocedemos a la celda anterior
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

int main()
{
    // Definimos la matriz que representa al grid
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

   vector<pair<int, int>> camino = bfs(0, 0, 9, 9, mapa);

   for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            cout<<mapa[i][j]<<" ";
        }
        cout<<endl;
   }
   
   if (!camino.empty()){
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