#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>

using namespace std;

class GrafoNDirigido {
private:
    unordered_map<int, vector<pair<int, int>>> listaAdyacencia; // Lista de adyacencia con pesos

public:
    GrafoNDirigido() {}

    void agregarNodo(int nodo) {
        if (listaAdyacencia.find(nodo) == listaAdyacencia.end()) {
            listaAdyacencia[nodo] = vector<pair<int, int>>();
        }
    }

    void agregarArista(int nodoOrigen, int nodoDestino, int peso) {
        agregarNodo(nodoOrigen);
        agregarNodo(nodoDestino);
        listaAdyacencia[nodoOrigen].push_back({nodoDestino, peso});
        listaAdyacencia[nodoDestino].push_back({nodoOrigen, peso}); // como es no dirigido, también agregamos la arista en sentido inverso
    }

    void dijkstra(int nodoInicio, int nodoFin) {
        unordered_map<int, int> distancia;
        unordered_map<int, int> padre;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        for (auto it = listaAdyacencia.begin(); it != listaAdyacencia.end(); ++it) {
            int nodo = it->first;
            distancia[nodo] = INT_MAX;
            padre[nodo] = -1;
        }

        distancia[nodoInicio] = 0;
        pq.push({0, nodoInicio});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto vecino : listaAdyacencia[u]) {
                int v = vecino.first;
                int pesoUV = vecino.second;

                if (distancia[v] > distancia[u] + pesoUV) {
                    distancia[v] = distancia[u] + pesoUV;
                    padre[v] = u;
                    pq.push({distancia[v], v});
                }
            }
        }

        if (distancia[nodoFin] != INT_MAX) {
            cout << "El camino más corto desde " << nodoInicio << " a " << nodoFin << " tiene un costo de " << distancia[nodoFin] << endl;
            cout << "Camino: ";
            int nodoActual = nodoFin;
            while (nodoActual != -1) {
                cout << nodoActual << " ";
                nodoActual = padre[nodoActual];
            }
            cout << endl;
        } else {
            cout << "No hay camino desde " << nodoInicio << " a " << nodoFin << endl;
        }
    }
};

int main() {
    GrafoNDirigido grafo;

    grafo.agregarArista(1, 2, 5);
    grafo.agregarArista(1, 3, 10);
    grafo.agregarArista(2, 3, 3);
    grafo.agregarArista(2, 4, 9);
    grafo.agregarArista(3, 4, 2);

    char respuesta;
    do {
        int nodoInicio, nodoFin;
        cout << "Ingrese el nodo de inicio: ";
        cin >> nodoInicio;
        cout << "Ingrese el nodo de fin: ";
        cin >> nodoFin;
        grafo.dijkstra(nodoInicio, nodoFin);

        cout << "¿Desea buscar otro camino? (s/n): ";
        cin >> respuesta;
    } while (respuesta == 's' || respuesta == 'S');

    return 0;
}