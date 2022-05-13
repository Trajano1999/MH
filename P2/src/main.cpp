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

// muestra una matriz int
void mostrarMatrizInt(const vector<vector<int> > & m){
    for(unsigned i=0; i<m.size(); ++i){
        cout << "( ";
        for(unsigned j=0; j<m[i].size(); ++j){
            cout << m[i][j] << " ";
        }
        cout << ")" << endl;
    }
}

// muestra una matriz double
void mostrarMatrizDouble(const vector<vector<double> > & m){
    for(unsigned i=0; i<m.size(); ++i){
        cout << "( ";
        for(unsigned j=0; j<m[i].size(); ++j){
            cout << m[i][j] << " ";
        }
        cout << ")" << endl;
    }
}

// muestra un vector int
void mostrarVector(const vector<int> & v){
    cout << "( ";
    for(unsigned i=0; i<v.size(); ++i)
        cout << v[i] << " ";
    cout << ")"; 
}

//-------------------------------------------------------------------------------------------------
// MEDICIONES DE TIEMPOS
//-------------------------------------------------------------------------------------------------

// realiza las mediciones de los métodos de la P1 y devuelve tanto los tiempos comos las desviaciones
vector<string> tiemposP1(char * arg, int i, Problema problema, vector<double> soluciones_ideales){
    unsigned tiempo_antes_greedy,
             tiempo_despues_greedy,
             tiempo_antes_BL,
             tiempo_despues_BL;
    double tiempo_final_greedy = 0.0,
           tiempo_final_BL = 0.0,
           desviacion_final_greedy = 0.0,
           desviacion_final_BL = 0.0,
           valor_algoritmo_greedy,
           valor_algoritmo_BL;

    string nombre_fichero;
    vector<string> resultados;
    
    problema.setMatriz(arg);

    // ejecutamos EJECUCIONES_POR_PROBLEMA veces cada archivo
    for(unsigned j=0; j<EJECUCIONES_POR_PROBLEMA; ++j){
        // modificamos la semilla
        problema.setSemilla(j+1);
        
        // ejecutamos Greedy
        tiempo_antes_greedy = clock();
        problema.solucionGreedy();
        tiempo_despues_greedy = clock();

        tiempo_final_greedy += double(tiempo_despues_greedy-tiempo_antes_greedy) / CLOCKS_PER_SEC;
        valor_algoritmo_greedy = problema.dispersion(problema.solucionGreedy());
        desviacion_final_greedy += (valor_algoritmo_greedy - soluciones_ideales[i-1]) / valor_algoritmo_greedy;

        // ejecutamos Búsqueda Lineal
        tiempo_antes_BL = clock();
        problema.solucionBusquedaLocal();
        tiempo_despues_BL = clock();
        
        tiempo_final_BL += double(tiempo_despues_BL-tiempo_antes_BL) / CLOCKS_PER_SEC;
        valor_algoritmo_BL = problema.dispersion(problema.solucionBusquedaLocal());
        desviacion_final_BL += (valor_algoritmo_BL - soluciones_ideales[i-1]) / valor_algoritmo_BL;
    }
    
    // calculamos los tiempos
    tiempo_final_greedy = tiempo_final_greedy / EJECUCIONES_POR_PROBLEMA;
    tiempo_final_BL     = tiempo_final_BL     / EJECUCIONES_POR_PROBLEMA;

    // calculamos la desviación típica
    desviacion_final_greedy = 100*desviacion_final_greedy;
    desviacion_final_BL     = 100*desviacion_final_BL;

    // eliminamos la ruta de los archivos
    nombre_fichero = arg;
    nombre_fichero.erase(nombre_fichero.begin(), nombre_fichero.begin()+59);

    // agrupamos los valores de tiempo y desviación
    resultados.push_back(nombre_fichero);
    resultados.push_back(to_string(tiempo_final_greedy));
    resultados.push_back(to_string(tiempo_final_BL));
    resultados.push_back(to_string(desviacion_final_greedy));
    resultados.push_back(to_string(desviacion_final_BL));

    return resultados;
}

//-------------------------------------------------------------------------------------------------
// MAIN
//-------------------------------------------------------------------------------------------------

int main(int narg, char * arg[]){
    unsigned random_semilla = 0;
    const char * dir_fichero = arg[1];
    vector<string> resultadosP1;

    Problema problema(random_semilla, dir_fichero);

    // vector con las soluciones ideales proporcionadas por el profesor
    vector<double> soluciones_ideales = { 0, 0, 0, 0, 0, 12.7179599999997, 14.0987499999997, 16.7611899999998, 17.0692099999999, 23.2652299999999, 1.92610000000002, 2.12104000000011,       \
        2.36230999999998, 1.6631999999999, 2.85312999999996, 42.7457799999991, 48.1076099999996, 43.1960899999997, 46.4124499999994, 47.7151099999996, 13.8320199999999, 13.6643400000003,   \
        15.3453799999998, 8.64063999999939, 17.2005099999999, 168.729590000001, 127.09726, 106.379189999999, 137.453159999999, 127.479740000001, 11.7451399999999, 18.7889299999997,         \
        18.5315999999998, 19.4883300000001, 18.1124199999998, 155.434770000002, 198.894619999999, 187.96703, 168.590200000001, 178.193740000003, 23.3460800000003, 26.7894999999996,         \
        26.7544699999996, 25.9355900000005, 27.7730099999994, 227.749309999998, 228.6029, 226.745339999999, 226.409610000003, 248.856619999998 };

    // guardamos los datos en un fichero externo
    ofstream fichero(DIR_FICHERO_SALIDA);
    if(!fichero.is_open())
        cerr << "Error al abrir " << DIR_FICHERO_SALIDA << endl;
    fichero << "Documento : " << "Tiempo_Greedy : " << "Tiempo_BL : " << "Desv_Tipica_Greedy : " << "Desv_Tipica_BL" << endl << endl;

    // recorremos los archivos
    for(int i=1; i<narg; ++i){

        // medimos los tiempos para la P1
        resultadosP1 = tiemposP1(arg[i], i, problema, soluciones_ideales);
        fichero << resultadosP1[0] << " : " << resultadosP1[1] << " : " << resultadosP1[2] << " : " << resultadosP1[3] << " : " << resultadosP1[4] << endl;
    }

    // jjj
    cout << "Poblacion " << endl;
    mostrarMatrizInt(problema.creacionPoblacion(2));

    cout << endl;
}