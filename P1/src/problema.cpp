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

//-------------------------------------------------------------------------------------------------
// CONSTANTES GLOBALES
//-------------------------------------------------------------------------------------------------

// máximo valor de un double en c++
const double VALOR_GRANDE = 1.7976931348623158e+308;
const unsigned MAX_EVALUACIONES = 100000;

//-------------------------------------------------------------------------------------------------
// MÉTODOS PRIVADOS GREEDY
//-------------------------------------------------------------------------------------------------

int Problema::randomGreedy(unsigned sem, int min, int max){
    // utilizamos srand() para modificar la semilla
    srand(sem);
    return rand() % (max-min+1) + min;
}

double Problema::valorMaximo(const vector<double> & v){
    double valor_max = 0.0;

    for(unsigned i=0; i<v.size(); ++i)
        if(v[i] > valor_max)
            valor_max = v[i];
        
    return valor_max;
}

double Problema::valorMinimo(const vector<double> & v){
    double valor_min = VALOR_GRANDE;

    for(unsigned i=0; i<v.size(); ++i)
        if(v[i] < valor_min && v[i] > 0)
            valor_min = v[i];
        
    return valor_min;
}

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

//-------------------------------------------------------------------------------------------------
// MÉTODOS PRIVADOS BL
//-------------------------------------------------------------------------------------------------

void Problema::intercambio(vector<int> & v, int valor1, int valor2){
    for(unsigned i=0; i<v.size(); ++i)
        if(v[i] == valor1)
            v[i] = valor2;
}

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

int Problema::calcularPosicion(const vector<int> & v, int elem){
    int res = -1;
    for(unsigned i=0; i<v.size(); ++i)
        if(v[i] == elem)
            res = i;
    return res;
}

double Problema::dispersion(const vector<int> & v){
    vector<double> sigmas_seleccionados = sigmaSeleccionados(v);
    return v.size() > 2 ? valorMaximo(sigmas_seleccionados) - valorMinimo(sigmas_seleccionados) : valorMaximo(sigmas_seleccionados);
}

double Problema::dispersionIntercambiarElementos(const vector<int> & sol, int elem_eliminar, int elem_aniadir){
    unsigned tamanio_sol = sol.size();
    unsigned pos_eliminado = calcularPosicion(sol, elem_eliminar);
    double distancia,
           suma = 0.0;
    vector<double> distancias = sigmaSeleccionados(sol);
    
    // modificamos las distancias para eliminar un elemento
    for(unsigned i=0; i<tamanio_sol; ++i){
        if(i != pos_eliminado)
            distancias[i] -= matriz[sol[i]][elem_eliminar] == 0 ? matriz[elem_eliminar][sol[i]] : matriz[sol[i]][elem_eliminar];
        else
            distancias[i] = 0;
    }

    // modificamos las distancias para añadir un elemento
    for(unsigned i=0; i<tamanio_sol; ++i){
        if(i != pos_eliminado){
            distancia = matriz[sol[i]][elem_aniadir] == 0 ? matriz[elem_aniadir][sol[i]] : matriz[sol[i]][elem_aniadir];
            distancias[i] += distancia;
            suma += distancia;
        }
    }
    distancias[pos_eliminado] = suma;

    return tamanio_sol > 2 ? valorMaximo(distancias) - valorMinimo(distancias) : valorMaximo(distancias);
}

//-------------------------------------------------------------------------------------------------
// CONSTRUCTOR
//-------------------------------------------------------------------------------------------------

Problema::Problema(unsigned sem, const char * dir_fich){
    // almacenamos la semilla
    semilla = sem;

    // rellenamos la matriz
    setMatriz(dir_fich);
}

//-------------------------------------------------------------------------------------------------
// OBSERVADORES
//-------------------------------------------------------------------------------------------------

unsigned Problema::getSemilla(){
    return semilla;
}

unsigned Problema::getElementosSeleccionados(){
    return elem_sel;
}

vector<vector<double> > Problema::getMatriz(){
    return matriz;
}

//-------------------------------------------------------------------------------------------------
// MODIFICADORES
//-------------------------------------------------------------------------------------------------

void Problema::setSemilla(unsigned sem){
    semilla = sem;
}

void Problema::setMatriz(const char * dir_fich){
    int elem_totales;
    
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
// MÉTODOS PARA RESOLVER EL PROBLEMA
//-------------------------------------------------------------------------------------------------

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

    // buscamos los vecinos de cada selección para mejorar la solución
    for(unsigned i=0; i<tamanio_sol; ++i){
        encontrado = false;
        for(unsigned j=0; j<tamanio_cand && !encontrado; ++j){
            if(candidatos[j] != -1 && num_evaluaciones < MAX_EVALUACIONES){
                // calculo el coste inicial
                if(calcular)
                    coste_anterior = dispersion(sol);

                // calculamos coste del vecino
                coste_nuevo = dispersionIntercambiarElementos(sol, sol[i], candidatos[j]);

                // si el coste nuevo es mejor, lo intercambiamos, sino, lo dejamos como estaba
                if(coste_nuevo < coste_anterior){
                    auxiliar = sol[i];
                    intercambio(sol, sol[i], candidatos[j]);

                    // aplicamos el intercambio
                    encontrado = true;
                    candidatos[j] = -1;
                    candidatos[auxiliar] = auxiliar;

                    // almacenamos el coste nuevo obetenido para no recalcularlo en la siguiente iteración
                    coste_anterior = coste_nuevo;
                    calcular = false;
                }else
                    calcular = true;  

                num_evaluaciones++;
            }
        }
    }

    return sol;
}