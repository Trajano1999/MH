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

// jjj               
const string DIR_FICHERO_SALIDA = "/home/juanma/Escritorio/Uni/Segundo_Cuatri/MH/P2/datos.txt";

// vector con las soluciones ideales proporcionadas por el profesor
const vector<double> SOLUCIONES_PROFESOR = {
    0, 0, 0, 0, 0, 12.7179599999997, 14.0987499999997, 16.7611899999998, 17.0692099999999, 23.2652299999999, 1.92610000000002, 2.12104000000011, 2.36230999999998,                 \
    1.6631999999999, 2.85312999999996, 42.7457799999991, 48.1076099999996, 43.1960899999997, 46.4124499999994, 47.7151099999996, 13.8320199999999, 13.6643400000003,               \
    15.3453799999998, 8.64063999999939, 17.2005099999999, 168.729590000001, 127.09726, 106.379189999999, 137.453159999999, 127.479740000001, 11.7451399999999,                     \
    18.7889299999997, 18.5315999999998, 19.4883300000001, 18.1124199999998, 155.434770000002, 198.894619999999, 187.96703, 168.590200000001, 178.193740000003,                     \
    23.3460800000003, 26.7894999999996, 26.7544699999996, 25.9355900000005, 27.7730099999994, 227.749309999998, 228.6029, 226.745339999999, 226.409610000003, 248.856619999998     \
};

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

/*int main(int narg, char * arg[])
{
    // guardamos los datos en un fichero externo
    ofstream fichero(DIR_FICHERO_SALIDA);
    if(!fichero.is_open())
        cerr << "Error al abrir " << DIR_FICHERO_SALIDA << endl;
    
    // tomamos los datos
    for(int i=1; i<narg; ++i)
    {
        
        problema.setMatriz(arg[i]);
        string nombre_fichero = arg[i];

        // eliminamos la ruta de los archivos
        nombre_fichero.erase(nombre_fichero.begin(), nombre_fichero.begin()+59);
        
        // calculamos las desv. típicas
        valor_greedy = problema.dispersion(v_Greedy);
        desv_tipica_greedy = 100.00 * ( valor_greedy - soluciones_ideales[i-1] ) / valor_greedy;

        valor_BL = problema.dispersion(v_BL);
        desv_tipica_BL = 100.00 * ( valor_BL - soluciones_ideales[i-1] ) / valor_BL;

        valor_AGGU = problema.dispersion(v_AGGU);
        desv_tipica_AGGU = 100.00 * ( valor_AGGU - soluciones_ideales[i-1] ) / valor_AGGU;

        valor_AGGP = problema.dispersion(v_AGGP);
        desv_tipica_AGGP = 100.00 * ( valor_AGGP - soluciones_ideales[i-1] ) / valor_AGGP;

        valor_AGEU = problema.dispersion(v_AGEU);
        desv_tipica_AGEU = 100.00 * ( valor_AGEU - soluciones_ideales[i-1] ) / valor_AGEU;

        valor_AGEP = problema.dispersion(v_AGEP);
        desv_tipica_AGEP = 100.00 * ( valor_AGEP - soluciones_ideales[i-1] ) / valor_AGEP;

        // calculamos las medias
        media_tiempo_greedy += tiempo_greedy;
        media_tiempo_BL += tiempo_BL;
        media_tiempo_AGGU += tiempo_AGGU;
        media_tiempo_AGGP += tiempo_AGGP;
        media_tiempo_AGEU += tiempo_AGEU;
        media_tiempo_AGEP += tiempo_AGEP;

        media_desv_greedy += desv_tipica_greedy;
        media_desv_BL += desv_tipica_BL;
        media_desv_AGGU += desv_tipica_AGGU;
        media_desv_AGGP += desv_tipica_AGGP;
        media_desv_AGEU += desv_tipica_AGEU;
        media_desv_AGEP += desv_tipica_AGEP;

        // añadimos los datos jjj
        //fichero << nombre_fichero << " " << tiem << " " << resultadosP2[2] << " " << resultadosP2[3] << " " << resultadosP2[4] << " " << resultadosP2[5] << " " << resultadosP2[6] << " " << resultadosP2[7] << " " << resultadosP2[8] << " " << resultadosP2[9] << " " << resultadosP2[10] << " " << resultadosP2[11] << " " << resultadosP2[12] << endl;

        cout << "Terminada la iteración : " << i << " de 50 " << endl;
    }

    fichero << "Tiempo_Greedy : " << "Desv_Greedy : " << "Tiempo_BL : " << "Desv_BL : " << "Tiempo_AGGU : " << "Desv_AGGU : " << "Tiempo_AGGP : " << "Desv_AGGP : " << "Tiempo_AGEU : " << "Desv_AGEU : " << "Tiempo_AGEP : " << "Desv_AGEP " << endl << endl;
    fichero << media_tiempo_greedy/50 << " : " << media_desv_greedy/50 << " : " << media_tiempo_BL/50 << " : " << media_desv_BL/50 << " : " << media_tiempo_AGGU/50 << " : " << media_desv_AGGU/50 << " : " << media_tiempo_AGGP/50 << " : " << media_desv_AGGP/50 << " : " << media_tiempo_AGEU/50 << " : " << media_desv_AGEU/50 << " : " << media_desv_AGEU/50 << " : " << media_tiempo_AGEP/50 << " : " << media_desv_AGEP/50 << endl; 

    cout << endl;
    cout << "Media tiempo greedy : " << media_tiempo_greedy/50 << endl;
    cout << "Media tiempo BL     : " << media_tiempo_BL/50 << endl;
    cout << "Media tiempo AGGU   : " << media_tiempo_AGGU/50 << endl;
    cout << "Media tiempo AGGP   : " << media_tiempo_AGGP/50 << endl;
    cout << "Media tiempo AGEU   : " << media_tiempo_AGEU/50 << endl;
    cout << "Media tiempo AGEP   : " << media_tiempo_AGEP/50 << endl;
    cout << endl;
    cout << "Media desv greedy   : " << media_desv_greedy/50 << endl;
    cout << "Media desv BL       : " << media_desv_BL/50 << endl;
    cout << "Media desv AGGU     : " << media_desv_AGGU/50 << endl;
    cout << "Media desv AGGP     : " << media_desv_AGGP/50 << endl;
    cout << "Media desv AGEU     : " << media_desv_AGEU/50 << endl;
    cout << "Media desv AGEP     : " << media_desv_AGEP/50 << endl;
    cout << endl;

    return 0;
}*/

int main(int narg, char * arg[])
{
    Problema problema(RAMDOM_SEMILLA, arg[1]);

    double tiempo_antes,
           tiempo_despues,

           tiempo_greedy;
           //media_tiempo_greedy = 0,
           //valor_greedy,
           //desv_tipica_greedy,
           //media_desv_greedy = 0;

           /*tiempo_BL,
           media_tiempo_BL = 0,
           valor_BL,
           desv_tipica_BL,
           media_desv_BL = 0,

           tiempo_AGGU,
           media_tiempo_AGGU = 0,
           valor_AGGU,
           desv_tipica_AGGU,
           media_desv_AGGU = 0,

           tiempo_AGGP,
           media_tiempo_AGGP = 0,
           valor_AGGP,
           desv_tipica_AGGP,
           media_desv_AGGP = 0,

           tiempo_AGEU,
           media_tiempo_AGEU = 0,
           valor_AGEU,
           desv_tipica_AGEU,
           media_desv_AGEU = 0,

           tiempo_AGEP,
           media_tiempo_AGEP = 0,
           valor_AGEP,
           desv_tipica_AGEP,
           media_desv_AGEP = 0;*/

    // recorremos todos los archivos
    for(int i=1; i<narg; ++i)
    {
        problema.setMatriz(arg[i]);
        string nombre_fichero = arg[i];

        // eliminamos la ruta de los archivos
        nombre_fichero.erase(nombre_fichero.begin(), nombre_fichero.begin()+36);

        // calculamos los tiempos
        tiempo_antes = clock();
        vector<int> v_Greedy = problema.solucionGreedy();
        tiempo_despues = clock();
        tiempo_greedy = tiempo_despues - tiempo_antes;

        /*tiempo_antes = clock();
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
        tiempo_AGEP = tiempo_despues - tiempo_antes;*/

        cout << "Tiempo Greedy : " << tiempo_greedy << endl;
    }

    cout << endl;
    return 0;
}