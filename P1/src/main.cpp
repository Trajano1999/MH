//-------------------------------------------------------------------------------------------------
//  Universidad de Granada
//  Escuela Superior de Inegeniería Informática y Telecomunicaciones 
//  Curso 2021/2022 
//  
//  Metaheurísticas
//  Práctica 1:
//  Técnicas de Búsqueda Local y Algoritmos Greedy para el Problema de la Mínima Dispersión Diferencial
//
//  Juan Manuel Mateos Pérez
//-------------------------------------------------------------------------------------------------

# include "problema.h"

using namespace std;

//-------------------------------------------------------------------------------------------------
// CONSTANTES GLOBALES
//-------------------------------------------------------------------------------------------------

const unsigned EJECUCIONES_POR_PROBLEMA = 5;
const string DIR_FICHERO_SALIDA = "/home/juanma/Escritorio/datos.txt";

//-------------------------------------------------------------------------------------------------
// FUNCIONES
//-------------------------------------------------------------------------------------------------

// muestra una matriz
void mostrarMatriz(const vector<vector<double> > & m){
    for(unsigned i=0; i<m.size(); ++i){
        cout << "( ";
        for(unsigned j=0; j<m[i].size(); ++j){
            cout << m[i][j] << " ";
        }
        cout << ")" << endl;
    }
}

// muestra un vector
void mostrarVector(const vector<int> & v){
    cout << "( ";
    for(unsigned i=0; i<v.size(); ++i)
        cout << v[i] << " ";
    cout << ")"; 
}

//-------------------------------------------------------------------------------------------------
// MAIN
//-------------------------------------------------------------------------------------------------

int main(int narg, char * arg[]){
    unsigned random_semilla = 0,
             tiempo_antes_greedy,
             tiempo_despues_greedy,
             tiempo_antes_BL,
             tiempo_despues_BL;
    double tiempo_final_greedy = 0.0,
           tiempo_final_BL = 0.0,
           desviacion_final = 0.0;
    const char * dir_fichero = arg[1];
    string nombre_fichero;
    
    // vector con las soluciones ideales proporcionadas por el profesor
    vector<double> soluciones_ideales = { 0, 0, 0, 0, 0, 12.7179599999997, 14.0987499999997, 16.7611899999998, 17.0692099999999, 23.2652299999999, 1.92610000000002, 2.12104000000011,       \
        2.36230999999998, 1.6631999999999, 2.85312999999996, 42.7457799999991, 48.1076099999996, 43.1960899999997, 46.4124499999994, 47.7151099999996, 13.8320199999999, 13.6643400000003,   \
        15.3453799999998, 8.64063999999939, 17.2005099999999, 168.729590000001, 127.09726, 106.379189999999, 137.453159999999, 127.479740000001, 11.7451399999999, 18.7889299999997,         \
        18.5315999999998, 19.4883300000001, 18.1124199999998, 155.434770000002, 198.894619999999, 187.96703, 168.590200000001, 178.193740000003, 23.3460800000003, 26.7894999999996,         \
        26.7544699999996, 25.9355900000005, 27.7730099999994, 227.749309999998, 228.6029, 226.745339999999, 226.409610000003, 248.856619999998 };
    
    // mensajes por pantalla jjj
    string peticion_semilla = "\nIntroduzca la semilla : ",
           solucion_greedy  = "\nSolución por Greedy         : ",
           solucion_BL      = "\nSolución por Búsqueda Local : ";

    // guardamos los datos en un fichero externo
    ofstream fichero(DIR_FICHERO_SALIDA);
    if(!fichero.is_open())
        cerr << "Error al abrir " << DIR_FICHERO_SALIDA << endl;
    fichero << "Documento " << "Tiempo_Greedy " << "Tiempo_BL" << endl;

    Problema problema(random_semilla, dir_fichero);

    for(int i=1; i<narg; ++i){
        dir_fichero = arg[i];
        problema.setMatriz(dir_fichero);

        for(unsigned j=0; j<EJECUCIONES_POR_PROBLEMA; ++j){
            random_semilla = j+1;
            problema.setSemilla(random_semilla);

            tiempo_antes_greedy = clock();
            problema.solucionGreedy();
            tiempo_despues_greedy = clock();

            tiempo_final_greedy += double(tiempo_despues_greedy-tiempo_antes_greedy) / CLOCKS_PER_SEC;

            tiempo_antes_BL = clock();
            problema.solucionBusquedaLocal();
            tiempo_despues_BL = clock();

            tiempo_final_BL += double(tiempo_despues_BL-tiempo_antes_BL) / CLOCKS_PER_SEC;
        }
        
        // calculamos los tiempos
        tiempo_final_greedy = tiempo_final_greedy / EJECUCIONES_POR_PROBLEMA;
        tiempo_final_BL = tiempo_final_BL / EJECUCIONES_POR_PROBLEMA;

        // eliminamos la ruta de los archivos
        nombre_fichero = arg[i];
        cout << "\n" << nombre_fichero;
        nombre_fichero.erase(nombre_fichero.begin(), nombre_fichero.begin()+59);
        
        fichero << nombre_fichero << " " << tiempo_final_greedy << " " << tiempo_final_BL << endl;

        tiempo_final_greedy = 0;
        tiempo_final_BL = 0;
    }

    cout << endl;
}