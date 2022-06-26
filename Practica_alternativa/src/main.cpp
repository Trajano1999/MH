//-------------------------------------------------------------------------------------------------
//  Universidad de Granada
//  Escuela Superior de Ingeniería Informática y Telecomunicaciones 
//  Curso 2021/2022 
//  
//  Metaheurísticas. Práctica Alternativa
//  Análisis de una metaheurística : Algoritmo Big Bang-Big Crunch
//
//  Juan Manuel Mateos Pérez
//-------------------------------------------------------------------------------------------------

# include "problema.h"

using namespace std;

//-------------------------------------------------------------------------------------------------
// CONSTANTES GLOBALES
//-------------------------------------------------------------------------------------------------

const unsigned RAMDOM_SEMILLA = 0;

//-------------------------------------------------------------------------------------------------
// MAIN
//-------------------------------------------------------------------------------------------------

int main(int narg, char * arg[])
{
    Problema problema(RAMDOM_SEMILLA, arg[1]);

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
        vector<int> BB_BC = problema.solucionBB_BC();
    }

    return 0;
}
