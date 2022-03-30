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

# include <iostream>
# include <fstream>

using namespace std;

void MostrarInicio(){
    cout << "Hola" << endl;
}

int main(int narg, char * arg[]){
    MostrarInicio();
    const char * dir_fich = arg[1];
    
    // abrimos el fichero
    ifstream fichero(dir_fich);
    if(!fichero.is_open()){
        cout << "Error al abrir" << dir_fich << endl;
        exit(EXIT_FAILURE);
    }

    // variables del fichero
    string num_elem_total, num_elem_selec;

    cout << "archivo : " << dir_fich << endl;
    fichero >> num_elem_total;
    cout << "Num     : " << num_elem_total << endl;

    fichero >> num_elem_selec;
    cout << "Num_sel : " << num_elem_selec << endl;
}

// cout << narg << " " << arg[0] << arg[1] << endl;