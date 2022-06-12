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
// MAIN
//-------------------------------------------------------------------------------------------------

int main(int narg, char * arg[])
{
    Problema problema(RAMDOM_SEMILLA, arg[1]);
    double tiempo_antes,
           tiempo_despues;

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

        // escogemos de toda la ruta, solo con el nombre archivos
        nombre_fichero.erase(nombre_fichero.begin(), nombre_fichero.begin()+36);

        // calculamos los tiempos
        /*
        tiempo_antes = clock();
        vector<int> v_Greedy = problema.solucionGreedy();
        tiempo_despues = clock();
        double tiempo_Greedy = tiempo_despues - tiempo_antes;
        cout << tiempo_Greedy << "\t" << problema.dispersion(v_Greedy) << endl;
        
        tiempo_antes = clock();
        vector<int> v_BL = problema.solucionBusquedaLocal();
        tiempo_despues = clock();
        double tiempo_BL = tiempo_despues - tiempo_antes;
        cout << tiempo_BL << "\t" << problema.dispersion(v_BL) << endl;
        
        tiempo_antes = clock();
        vector<int> v_AGGU = problema.solucionAGGUniforme();
        tiempo_despues = clock();
        double tiempo_AGGU = tiempo_despues - tiempo_antes;
        cout << tiempo_AGGU << "\t" << problema.dispersion(v_AGGU) << endl;        
        
        tiempo_antes = clock();
        vector<int> v_AGGP = problema.solucionAGGPosicion();
        tiempo_despues = clock();
        double tiempo_AGGP = tiempo_despues - tiempo_antes;
        cout << tiempo_AGGP << "\t" << problema.dispersion(v_AGGP) << endl;
        
        tiempo_antes = clock();
        vector<int> v_AGEU = problema.solucionAGEUniforme();
        tiempo_despues = clock();
        double tiempo_AGEU = tiempo_despues - tiempo_antes;
        cout << tiempo_AGEU << "\t" << problema.dispersion(v_AGEU) << endl;
        
        tiempo_antes = clock();
        vector<int> v_AGEP = problema.solucionAGEPosicion();
        tiempo_despues = clock();
        double tiempo_AGEP = tiempo_despues - tiempo_antes;
        cout << tiempo_AGEP << "\t" << problema.dispersion(v_AGEP) << endl;
        
        tiempo_antes = clock();
        vector<int> v_AM1 = problema.solucionAM1();
        tiempo_despues = clock();
        double tiempo_AM1 = tiempo_despues - tiempo_antes;
        cout << tiempo_AM1 << "\t" << problema.dispersion(v_AM1) << endl;
        
        tiempo_antes = clock();
        vector<int> v_AM2 = problema.solucionAM2();
        tiempo_despues = clock();
        double tiempo_AM2 = tiempo_despues - tiempo_antes;
        cout << tiempo_AM2 << "\t" << problema.dispersion(v_AM2) << endl;
        */
        tiempo_antes = clock();
        vector<int> v_AM3 = problema.solucionAM3();
        tiempo_despues = clock();
        double tiempo_AM3 = tiempo_despues - tiempo_antes;
        cout << tiempo_AM3 << "\t" << problema.dispersion(v_AM3) << endl;
        /*
        tiempo_antes = clock();
        vector<int> v_ES = problema.solucionEnfriamientoSimulado(problema.generarVectorPueblosAleatorio());
        tiempo_despues = clock();
        double tiempo_ES = tiempo_despues - tiempo_antes;
        cout << tiempo_ES << "\t" << problema.dispersion(v_ES) << endl;
        
        tiempo_antes = clock();
        vector<int> v_BMB = problema.solucionBusquedaMultiarranque();
        tiempo_despues = clock();
        double tiempo_BMB = tiempo_despues - tiempo_antes;
        cout << tiempo_BMB << "\t" << problema.dispersion(v_BMB) << endl;
        
        tiempo_antes = clock();
        vector<int> v_ILS = problema.solucionILS();
        tiempo_despues = clock();
        double tiempo_ILS = tiempo_despues - tiempo_antes;
        cout << tiempo_ILS << "\t" << problema.dispersion(v_ILS) << endl;
        
        tiempo_antes = clock();
        vector<int> v_ILS_ES = problema.solucionILS_ES();
        tiempo_despues = clock();
        double tiempo_ILS_ES = tiempo_despues - tiempo_antes;
        cout << tiempo_ILS_ES << "\t" << problema.dispersion(v_ILS_ES) << endl;
        */
    }

    return 0;
}
