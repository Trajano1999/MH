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

// jjj
void mostrarVector(const vector<double> & v){
    cout << "( ";
    for(unsigned i=0; i<v.size(); ++i)
        cout << v[i] << " ";
    cout << ")"; 
}

// jjj
void mostrarVectorInt(const vector<int> & v){
    cout << "( ";
    for(unsigned i=0; i<v.size(); ++i)
        cout << v[i] << " ";
    cout << ")"; 
}

//-------------------------------------------------------------------------------------------------
// CONSTANTES GLOBALES
//-------------------------------------------------------------------------------------------------

// máximo valor de un double en c++
const double VALOR_GRANDE = 1.7976931348623158e+308;
const unsigned MAX_EVALUACIONES = 100000;

//-------------------------------------------------------------------------------------------------
// MÉTODOS PRIVADOS
//-------------------------------------------------------------------------------------------------

// jjj
// devuelve un valor aleatorio entre los parámetros recibidos
int Problema::randomGreedy(unsigned sem, int min, int max){
    // utilizamos srand() para modificar la semilla
    srand(sem);
    return rand() % (max-min+1) + min;
}

// devuelve el mayor valor del vector
double Problema::valorMaximo(const vector<double> & v){
    double valor_max = 0.0;

    for(unsigned i=0; i<v.size(); ++i)
        if(v[i] > valor_max)
            valor_max = v[i];
        
    return valor_max;
}

// devuelve el menor valor del vector (sin tener en cuenta el 0)
double Problema::valorMinimo(const vector<double> & v){
    double valor_min = VALOR_GRANDE;

    for(unsigned i=0; i<v.size(); ++i)
        if(v[i] < valor_min && v[i] > 0)
            valor_min = v[i];
        
    return valor_min;
}

// devuelve la posición del menor valor del vector (sin tener en cuenta el 0)
int Problema::posicionMinima(const vector<double> & v){
    int pos_min = 0;
    double valor_min = VALOR_GRANDE;

    for(unsigned i=0; i<v.size(); ++i)
        if(v[i] < valor_min && v[i] > 0){
            valor_min = v[i];
            pos_min = i;
        }
        
    return pos_min;
}

// calcula la suma de distancias de los elementos no seleccionados a los seleccionados
vector<double> Problema::sigmaNoSeleccionados(const vector<int> & cand, const vector<int> & sol){
    unsigned tamanio_cand = cand.size(),
             tamanio_sol = sol.size();
    double suma = 0.0;
    vector<double> res (tamanio_cand, 0.0);

    for(unsigned i=0; i<tamanio_cand; ++i)
        if(cand[i] != -1){
            for(unsigned j=0; j<tamanio_sol; ++j)
                suma += matriz[sol[j]][cand[i]] == 0 ? matriz[cand[i]][sol[j]] : matriz[sol[j]][cand[i]];
            
            res[i] = suma;
            suma = 0.0;
        }
    
    return res;
}

// calcula la suma de distancias entre los elementos seleccionados
vector<double> Problema::sigmaSeleccionados(const vector<int> & sol){
    unsigned tamanio_sol = sol.size();
    double suma = 0.0;
    vector<double> res (tamanio_sol, 0.0);
    
    for(unsigned i=0; i<tamanio_sol; ++i){
        for(unsigned j=0; j<tamanio_sol; ++j){
            if(i != j)
                suma += matriz[sol[i]][sol[j]] == 0 ? matriz[sol[j]][sol[i]] : matriz[sol[i]][sol[j]];
        }

        res[i] = suma;
        suma = 0.0;
    }

    return res;
}

// calcula el elemento con menor dispersión
int Problema::elementoMenorDispersion(const vector<int> & cand, const vector<int> & sol){
    double distancia, max, min;
    unsigned tamanio_cand = cand.size(),
             tamanio_sol = sol.size();
    vector<double> sigma (tamanio_sol, 0.0),
                   dispersion (tamanio_cand, 0.0);

    // calculamos el vector de la suma de distancias de cada elemento no seleccionado a los seleccionados
    vector<double> sigma_no_seleccionados = sigmaNoSeleccionados(cand, sol);

    // calculamos el vector de la suma de distancias de cada elemento seleccionado con el resto
    vector<double> sigma_seleccionados = sigmaSeleccionados(sol);

    for(unsigned i=0; i<tamanio_cand; ++i)
        if(cand[i] != -1){
            // calculamos el vector de la suma de distancias de los sigma seleccionados 
            // más la distancia de añadir el elemento i no seleccionado
            for(unsigned j=0; j<tamanio_sol; ++j){
                distancia = matriz[sol[j]][cand[i]] == 0 ? matriz[cand[i]][sol[j]] : matriz[sol[j]][cand[i]];
                sigma[j] = sigma_seleccionados[j] + distancia;
            }

            // calculamos el max y min entre los sigmas seleccionados y los sigmas actuales
            max = valorMaximo(sigma); if(sigma_no_seleccionados[i] > max) max = sigma_no_seleccionados[i];
            min = valorMinimo(sigma); if(sigma_no_seleccionados[i] < min && sigma_no_seleccionados[i] > 0) min = sigma_no_seleccionados[i];
            
            // la dispersión es 0 si el tamaño del vector solución es 1
            dispersion[i] = tamanio_sol > 1 ? max - min : max;
        }

    // escogemos el menor valor del vector de dispersion
    return posicionMinima(dispersion);
}

bool Problema::comprobarValor(const vector<int> & v, int valor){
    bool encontrado = false;

    for(unsigned i=0; i<v.size() && !encontrado; ++i){
        if(v[i] == valor)
            encontrado = true;
    }

    return encontrado;
}

// jjj
// devuelve m valores aleatorios distintos entre los parámetros recibidos
set<int> Problema::randomBL(int min, int max){
    unsigned la_semilla = semilla;
    set<int> res;
    
    while(res.size() < elem_sel){
        res.insert(randomGreedy(la_semilla, min, max));
        // cambiamos la semilla por un valor random (basado en la semilla anterior)
        la_semilla = rand();
    }
    
    return res;
}

// intercambia un valor de un vector por otro
void Problema::intercambio(vector<int> & v, int valor1, int valor2){
    for(unsigned i=0; i<v.size(); ++i)
        if(v[i] == valor1)
            v[i] = valor2;
}

// calcula la dispersión de un vector solución dado
double Problema::dispersion(const vector<int> & v){
    vector<double> sigmas_seleccionados = sigmaSeleccionados(v);
    return valorMaximo(sigmas_seleccionados) - valorMinimo(sigmas_seleccionados);
}

// calcula la dispersion al añadir un elemento
double Problema::dispersionAniadirElemento(const vector<int> & sol, int elem){
    unsigned tamanio_sol = sol.size();
    double suma = 0.0;
    vector<double> sigmas_seleccionados = sigmaSeleccionados(sol),
                   distancias_elem (tamanio_sol, 0.0);

    // calculamos las distancias del nuevo elemento a todos los demás
    for(unsigned i=0; i<tamanio_sol; ++i){
        distancias_elem[i] = matriz[elem][sol[i]] == 0 ? matriz[sol[i]][elem] : matriz[elem][sol[i]];
        suma += distancias_elem[i];
    }

    // añadimos esas distancias al vector de sigmas
    for(unsigned i=0; i<tamanio_sol; ++i)
        sigmas_seleccionados[i] += distancias_elem[i];
    
    // añadimos la suma de distancias del elem nuevo respecto al resto
    sigmas_seleccionados.push_back(suma);

    cout << "\nDispersion añadir   : " << valorMaximo(sigmas_seleccionados) - valorMinimo(sigmas_seleccionados);
    return valorMaximo(sigmas_seleccionados) - valorMinimo(sigmas_seleccionados);
}

// calcula la dispersion al eliminar un elemento
double Problema::dispersionEliminarElemento(const vector<int> & sol, int elem){
    unsigned pos = 0;
    vector<double> sigmas_seleccionados = sigmaSeleccionados(sol);

    // calculo la posición del elemento a eliminar
    for(unsigned i=0; i<sol.size(); ++i){
        if(sol[i] == elem)
            pos = i;
    }

    // restamos la distancia del elemento eliminado al resto de elementos
    for(unsigned i=0; i<sigmas_seleccionados.size(); ++i){
        if(i != pos)
            sigmas_seleccionados[i] -= matriz[sol[i]][elem] == 0 ? matriz[elem][sol[i]] : matriz[sol[i]][elem];
        else
            sigmas_seleccionados[i] = 0;
    }
    cout << "\nDispersion eliminar : " << valorMaximo(sigmas_seleccionados) - valorMinimo(sigmas_seleccionados);
    return valorMaximo(sigmas_seleccionados) - valorMinimo(sigmas_seleccionados);
}

//-------------------------------------------------------------------------------------------------
// CONSTRUCTOR
//-------------------------------------------------------------------------------------------------

Problema::Problema(unsigned sem, const char * dir_fich){
    int elem_totales;

    // almacenamos la semilla
    semilla = sem;

    // abrimos el fichero
    ifstream fichero(dir_fich);
    if(!fichero.is_open())
        cerr << "Error al abrir " << dir_fich << endl;

    // leemos los primeros valores del fichero
    fichero >> elem_totales;
    fichero >> elem_sel;

    // redimensionamos la matriz
    vector<vector<double> > aux(elem_totales, vector<double>(elem_totales)); 
    matriz = aux;

    int num_lineas = (elem_totales * (elem_totales-1)) / 2;
    int pueblo1,
        pueblo2;
    double distancia;

    // rellenamos la matriz con el resto de valores del fichero
    for(int i=0; i<num_lineas; ++i){
        fichero >> pueblo1;
        fichero >> pueblo2;
        fichero >> distancia;
        matriz[pueblo1][pueblo2] = distancia;
    }
}

//-------------------------------------------------------------------------------------------------
// MÉTODOS PÚBLICOS
//-------------------------------------------------------------------------------------------------

vector<vector<double> > Problema::getMatriz(){
    return matriz;
}

// jjj se puede hacer un un list para que sea más eficiente al eliminar un elemento del vector, en vez de poner el elemento a -1
vector<int> Problema::solucionGreedy(){
    int n_pueblos = matriz.size(),
        mejor_candidato = randomGreedy(semilla, 0, n_pueblos-1);
    vector<int> sol, candidatos;
    
    // rellenamos el vector de candidatos
    for(int i=0; i<n_pueblos; ++i)
        candidatos.push_back(i);

    // añadimos el primer valor aleatorio
    sol.push_back(mejor_candidato);
    candidatos[mejor_candidato] = -1;

    // añadimos los demás pueblos
    while(sol.size() < elem_sel){             
        mejor_candidato = elementoMenorDispersion(candidatos, sol);
        sol.push_back(mejor_candidato);
        candidatos[mejor_candidato] = -1;
    }
    
    return sol;
}

vector<int> Problema::solucionBusquedaLocal(){
    int auxiliar;
    unsigned tamanio_cand = matriz.size();
    set<int> aleatorios = randomBL(0, tamanio_cand-1);
    unsigned tamanio_sol = aleatorios.size();
    set<int>::iterator k;

    vector<int> sol, candidatos;
    double coste_anterior, coste_nuevo;
    unsigned num_evaluaciones = 0;
    bool encontrado = false,
         calcular = true;

    // generamos el primer vector de soluciones aleatorias
    for(k=aleatorios.begin(); k!=aleatorios.end(); ++k)
        sol.push_back(*k);

    // generamos el vector de candidatos
    for(unsigned i=0; i<tamanio_cand; ++i)
        candidatos.push_back(i);
    for(unsigned i=0; i<tamanio_sol; ++i)
        candidatos[sol[i]] = -1;

    cout << endl;
    cout << "\n COMIENZO";
    cout << "\n\tCandidato : ";
    mostrarVectorInt(candidatos);
    cout << "\n\tSolucion  : ";
    mostrarVectorInt(sol);
    cout << endl << endl;

    // buscamos los vecinos de cada selección para mejorar la solución
    for(unsigned i=0; i<tamanio_sol; ++i){
        encontrado = false;
        for(unsigned j=0; j<tamanio_cand && !encontrado; ++j){
            if(candidatos[j] != -1 && num_evaluaciones < MAX_EVALUACIONES){
                // calculo el coste inicial
                if(calcular)
                    coste_anterior = dispersion(sol);
                
                // calculamos coste del vecino
                coste_nuevo = coste_anterior - dispersionEliminarElemento(sol, sol[i]) + dispersionAniadirElemento(sol, candidatos[j]);

                cout << "\nSolucion       : ";
                mostrarVectorInt(sol);
                auxiliar = sol[i];
                intercambio(sol, sol[i], candidatos[j]);
                cout << "\nIntercambio    : ";
                mostrarVectorInt(sol);
                cout << "\nCoste anterior : " << coste_anterior;
                cout << "\nCoste nuevo    : " << coste_nuevo;
                cout << endl;

                // si el coste nuevo es mejor, lo intercambiamos, sino, lo dejamos como estaba
                if(coste_nuevo < coste_anterior){
                    // aplicamos el intercambio
                    encontrado = true;
                    candidatos[j] = -1;
                    candidatos[auxiliar] = auxiliar;

                    // almacenamos el coste nuevo obetenido para no recalcularlo en la siguiente iteración
                    coste_anterior = coste_nuevo;
                    calcular = false;
                }else{
                    intercambio(sol, candidatos[j], auxiliar);
                    calcular = true;
                }      

                num_evaluaciones++;
            }
        }
    }

    return sol;
}