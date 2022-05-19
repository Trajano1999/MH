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

const unsigned RAMDOM_SEMILLA = 0,
               EJECUCIONES_POR_PROBLEMA = 5;

//-------------------------------------------------------------------------------------------------
// FUNCIONES
//-------------------------------------------------------------------------------------------------

// jjj muestra una matriz int
/*void mostrarMatrizInt(const vector<vector<int> > & m)
{
    for(unsigned i=0; i<m.size(); ++i)
    {
        cout << "( ";
        for(unsigned j=0; j<m[i].size(); ++j)
            cout << m[i][j] << " ";
        cout << ")" << endl;
    }
}

// jjj muestra una matriz double
void mostrarMatrizDouble(const vector<vector<double> > & m)
{
    for(unsigned i=0; i<m.size(); ++i)
    {
        cout << "( ";
        for(unsigned j=0; j<m[i].size(); ++j)
            cout << m[i][j] << " ";
        cout << ")" << endl;
    }
}*/

// jjj muestra un vector int
void mostrarVector(const vector<int> & v)
{
    cout << "( ";
    for(unsigned i=0; i<v.size(); ++i)
        cout << v[i] << " ";
    cout << ")"; 
}

//-------------------------------------------------------------------------------------------------
// MAIN
//-------------------------------------------------------------------------------------------------

int main(int narg, char * arg[])
{
    Problema problema(RAMDOM_SEMILLA, arg[1]);
    double tiempo_antes,
           tiempo_despues,

           tiempo_greedy,
           tiempo_BL,
           tiempo_AGGU,
           tiempo_AGGP,
           tiempo_AGEU,
           tiempo_AGEP;

    // comprobamos que el número de argumentos es correcto
    if(narg <= 1)
    {
        cerr << "./ejecutable <argumento1> ... <argumentoN>";
        return 1;
    }

    // recorremos todos los argumentos
    for(int i=1; i<narg; ++i)
    {
        problema.setMatriz(arg[i]);
        string nombre_fichero = arg[i];

        // eliminamos la ruta de los archivos
        nombre_fichero.erase(nombre_fichero.begin(), nombre_fichero.begin()+36);

        // jjj cout << "\nComienzo del archivo " << i << " de " << narg-1 << endl;

        // calculamos los tiempos
        tiempo_antes = clock();
        vector<int> v_Greedy = problema.solucionGreedy();
        tiempo_despues = clock();
        tiempo_greedy = tiempo_despues - tiempo_antes;

        tiempo_antes = clock();
        vector<int> v_BL = problema.solucionBusquedaLocal();
        tiempo_despues = clock();
        tiempo_BL = tiempo_despues - tiempo_antes;

        tiempo_antes = clock();
        vector<int> v_AGGU = problema.solucionAGGUniforme();
        tiempo_despues = clock();
        tiempo_AGGU = tiempo_despues - tiempo_antes;

        tiempo_antes = clock();
        vector<int> v_AGGP = problema.solucionAGGPosicion();
        tiempo_despues = clock();
        tiempo_AGGP = tiempo_despues - tiempo_antes;

        tiempo_antes = clock();
        vector<int> v_AGEU = problema.solucionAGEUniforme();
        tiempo_despues = clock();
        tiempo_AGEU = tiempo_despues - tiempo_antes;

        tiempo_antes = clock();
        vector<int> v_AGEP = problema.solucionAGEPosicion();
        tiempo_despues = clock();
        tiempo_AGEP = tiempo_despues - tiempo_antes;

        cout << "\nFichero";
        cout << "\n\t" << nombre_fichero;
        cout << "\nTiempos";
        cout << "\n\t" << tiempo_greedy;
        cout << "\n\t" << tiempo_BL;
        cout << "\n\t" << tiempo_AGGU;
        cout << "\n\t" << tiempo_AGGP;
        cout << "\n\t" << tiempo_AGEU;
        cout << "\n\t" << tiempo_AGEP;
        cout << "\nCostes";
        cout << "\n\t" << problema.dispersion(v_Greedy);
        cout << "\n\t" << problema.dispersion(v_BL);
        cout << "\n\t" << problema.dispersion(v_AGGU);
        cout << "\n\t" << problema.dispersion(v_AGGP);
        cout << "\n\t" << problema.dispersion(v_AGEU);
        cout << "\n\t" << problema.dispersion(v_AGEP);
        
        // jjj cout << "\nFin del archivo " << i << " de " << narg-1 << endl;
        if(i<narg-1)
            cout << "\n----------------------------------------------------------------------";
    }

    cout << endl << endl;
    return 0;
}