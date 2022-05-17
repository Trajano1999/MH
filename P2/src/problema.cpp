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

// jjj muestra un vector int
void mostrarVectorInt(const vector<int> & v){
    cout << "( ";
    for(unsigned i=0; i<v.size(); ++i)
        cout << v[i] << " ";
    cout << ")"; 
}

// jjj muestra una matriz int
void mostrarMatrizInt(const vector<vector<int> > & m){
    for(unsigned i=0; i<m.size(); ++i){
        cout << "( ";
        for(unsigned j=0; j<m[i].size(); ++j){
            cout << m[i][j] << " ";
        }
        cout << ")" << endl;
    }
}

// jjj muestra un vector double
void mostrarVector(const vector<double> & v){
    cout << "( ";
    for(unsigned i=0; i<v.size(); ++i)
        cout << v[i] << " ";
    cout << ")"; 
}

//-------------------------------------------------------------------------------------------------
// CONSTANTES GLOBALES
//-------------------------------------------------------------------------------------------------

// máximo valor de un double en c++
const double VALOR_GRANDE   = 1.7976931348623158e+308,
             PROB_CRUCE_AGG = 0.7,
             PROB_CRUCE_AGE = 1,
             PROB_MUTACION  = 0.1;
            
const unsigned MAX_EVALUACIONES  = 100000,
               TAMANIO_POBLACION_GENERACIONAL = 50,
               TAMANIO_POBLACION_ESTACIONARIA = 2;

//-------------------------------------------------------------------------------------------------
// MÉTODOS PRIVADOS GENERALES
//-------------------------------------------------------------------------------------------------

double Problema::valorMaximo(const vector<double> & v){
    double valor_max = 0.0;

    for(unsigned i=0; i<v.size(); ++i)
        if(v[i] > valor_max)
            valor_max = v[i];
        
    return valor_max;
}

double Problema::valorMinimoPositivo(const vector<double> & v){
    double valor_min = VALOR_GRANDE;

    for(unsigned i=0; i<v.size(); ++i)
        if(v[i] < valor_min && v[i] > 0)
            valor_min = v[i];
        
    return valor_min;
}

int Problema::posicionMinimoPositivo(const vector<double> & v){
    int pos_min = 0;
    double valor_min = VALOR_GRANDE;

    for(unsigned i=0; i<v.size(); ++i)
        if(v[i] < valor_min && v[i] > 0){
            valor_min = v[i];
            pos_min = i;
        }
        
    return pos_min;
}

void Problema::intercambio(vector<int> & v, int valor1, int valor2){
    for(unsigned i=0; i<v.size(); ++i)
        if(v[i] == valor1)
            v[i] = valor2;
}

int Problema::calcularPosicion(const vector<int> & v, int elem){
    int res = -1;
    for(unsigned i=0; i<v.size(); ++i)
        if(v[i] == elem)
            res = i;
    return res;
}

vector<int> Problema::generarVectorAleatorio(unsigned tamanio_vector){
    unsigned random;
    vector<int> resultado(tamanio_vector, 0);

    for(unsigned i=0; i<elem_sel; ++i){
        random = rand() % tamanio_vector;
        resultado[random] = 1; 
    }

    return resultado;
}

//-------------------------------------------------------------------------------------------------
// MÉTODOS PRIVADOS GREEDY
//-------------------------------------------------------------------------------------------------

int Problema::randomGreedy(unsigned sem, int min, int max){
    // utilizamos srand() para modificar la semilla
    srand(sem);
    return rand() % (max-min+1) + min;
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
            max = valorMaximo(sigma);         if(sigma_no_seleccionados[i] > max) max = sigma_no_seleccionados[i];
            min = valorMinimoPositivo(sigma); if(sigma_no_seleccionados[i] < min && sigma_no_seleccionados[i] > 0) min = sigma_no_seleccionados[i];
            
            // la dispersión es 0 si el tamaño del vector solución es 1
            dispersion[i] = tamanio_sol > 1 ? max - min : max;
        }

    // escogemos el menor valor del vector de dispersion
    return posicionMinimoPositivo(dispersion);
}

//-------------------------------------------------------------------------------------------------
// MÉTODOS PRIVADOS BL
//-------------------------------------------------------------------------------------------------

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

    return tamanio_sol > 2 ? valorMaximo(distancias) - valorMinimoPositivo(distancias) : valorMaximo(distancias);
}

//-------------------------------------------------------------------------------------------------
// MÉTODOS PRIVADOS AGs
//-------------------------------------------------------------------------------------------------

double Problema::dispersionVectorPoblacion(const vector<int> & vector_poblacion){
    unsigned tamanio_poblacion = vector_poblacion.size();
    vector<int> vector_pueblos;

    for(unsigned i=0; i<tamanio_poblacion; ++i){
        if(vector_poblacion[i] == 1)
            vector_pueblos.push_back(i);
    }

    return dispersion(vector_pueblos);
}

vector<double> Problema::dispersionPoblacion(const vector<vector<int> > & poblacion){
    unsigned tamanio_poblacion = poblacion.size();
    vector<double> resultado;
    
    for(unsigned i=0; i<tamanio_poblacion; ++i)
        resultado.push_back(dispersionVectorPoblacion(poblacion[i]));
    
    return resultado;
}

void Problema::reparacion(vector<int> & hijo){
    unsigned contador = 0,
             mejor_posicion = 0,
             tamanio = hijo.size();
    double dispersion, 
           mayor_dispersion = 0, 
           menor_dispersion = dispersionVectorPoblacion(hijo);
    
    for(unsigned i=0; i<tamanio; ++i)
        if(hijo[i] == 1)
            contador++;

    while(contador > elem_sel){
        mayor_dispersion = 0;

        // buscamos el elemento que más dispersión tenga y lo eliminamos
        for(unsigned i=0; i<tamanio; ++i){
            if(hijo[i] == 1){
                hijo[i] = 0;
                dispersion = dispersionVectorPoblacion(hijo);
                if(dispersion > mayor_dispersion){
                    mayor_dispersion = dispersion;
                    mejor_posicion = i;
                }
                hijo[i] = 1;
            }
        }
        hijo[mejor_posicion] = 0;
        contador--;
    }

    while(contador < elem_sel){
        menor_dispersion = dispersionVectorPoblacion(hijo);

        // buscamos el elemento que menos dispersión sume y lo añadimos
        for(unsigned i=0; i<tamanio; ++i){
            if(hijo[i] == 0){
                hijo[i] = 1;
                dispersion = dispersionVectorPoblacion(hijo);
                if(dispersion < menor_dispersion){
                    menor_dispersion = dispersion;
                    mejor_posicion = i;
                }
                hijo[i] = 0;
            }
        }
        hijo[mejor_posicion] = 1;
        contador++;
    }
}

vector<vector<int> > Problema::creacionPoblacion(unsigned tamanio_poblacion){
    unsigned tamanio_vector = matriz.size();
    vector<vector<int> > resultado;

    srand(time(nullptr));
    
    for(unsigned i=0; i<tamanio_poblacion; ++i)
        resultado.push_back(generarVectorAleatorio(tamanio_vector));

    return resultado;
}

vector<vector<int> > Problema::seleccion(const vector<vector<int> > & poblacion, const vector<double> & dispersion_poblacion, unsigned num_torneos){
    int aleatorio1, aleatorio2;
    vector<vector<int> > resultado;

    srand(time(NULL));
    for(unsigned i=0; i<num_torneos; ++i){
        
        // seleccionamos 2 aleatorios distintos
        aleatorio1 = rand() % (num_torneos);
        do{
            aleatorio2 = rand() % (num_torneos);
        }while(aleatorio2 == aleatorio1);

        // escogemos el que menos dispersion tenga
        if(dispersion_poblacion[aleatorio1] < dispersion_poblacion[aleatorio2])
            resultado.push_back(poblacion[aleatorio1]);
        else
            resultado.push_back(poblacion[aleatorio2]);
    }

    return resultado;
}

void Problema::cruceUniforme(vector<vector<int> > & poblacion_hijos, unsigned tamanio_cruce){
    unsigned tamanio_matriz = matriz.size();
    int aleatorio1, aleatorio2, aleatorio3;
    vector<int> auxiliar(tamanio_matriz, -1);

    srand(time(NULL));

    for(unsigned i=0; i<PROB_CRUCE_AGG*tamanio_cruce; ++i){
        
        // seleccionamos 2 aleatorios distintos
        aleatorio1 = rand() % (tamanio_cruce);
        do{
            aleatorio2 = rand() % (tamanio_cruce);
        }while(aleatorio2 == aleatorio1);

        // rellenamos el vector aux con el cruce de los dos aleatorios
        for(unsigned j=0; j<tamanio_matriz; ++j){
            aleatorio3 = rand() % 2;
            auxiliar[j] = aleatorio3 > 0 ? poblacion_hijos[aleatorio1][j] : poblacion_hijos[aleatorio2][j];

            if( poblacion_hijos[aleatorio1][j] == poblacion_hijos[aleatorio2][j] )
                auxiliar[j] = poblacion_hijos[aleatorio1][j];
        }

        // modificamos el vector poblacion por el auxiliar
        poblacion_hijos[i] = auxiliar;
        reparacion(poblacion_hijos[i]);
    }
}

void Problema::crucePosicion(vector<vector<int> > & poblacion_hijos, unsigned tamanio_cruce){
    unsigned tamanio_matriz = matriz.size();
    int aleatorio1, aleatorio2;
    vector<int> auxiliar(tamanio_matriz, -1);

    srand(time(NULL));

    for(unsigned i=0; i<PROB_CRUCE_AGE*tamanio_cruce; ++i){
        
        // seleccionamos 2 aleatorios distintos
        aleatorio1 = rand() % (tamanio_cruce);
        do{
            aleatorio2 = rand() % (tamanio_cruce);
        }while(aleatorio2 == aleatorio1);

        // rellenamos el vector aux con el cruce de los dos aleatorios // jjj
        for(unsigned j=0; j<tamanio_matriz; ++j){
            auxiliar[j] = poblacion_hijos[aleatorio1][j];

            if( poblacion_hijos[aleatorio1][j] == poblacion_hijos[aleatorio2][j] )
                auxiliar[j] = poblacion_hijos[aleatorio1][j];
        }

        // modificamos el vector poblacion por el auxiliar
        poblacion_hijos[i] = auxiliar;
    }
}

void Problema::mutacion(vector<vector<int> > & poblacion_hijos, unsigned tamanio_mutacion){

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
// MÉTODOS PÚBLICOS
//-------------------------------------------------------------------------------------------------

double Problema::dispersion(const vector<int> & v){
    vector<double> sigmas_seleccionados = sigmaSeleccionados(v);
    return v.size() > 2 ? valorMaximo(sigmas_seleccionados) - valorMinimoPositivo(sigmas_seleccionados) : valorMaximo(sigmas_seleccionados);
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

// jjj
vector<int> Problema::solucionAGGUniforme(){
    //unsigned evaluaciones = 0;
    vector<double> dispersion_poblacion;
    vector<vector<int> > poblacion = creacionPoblacion(TAMANIO_POBLACION_GENERACIONAL),
                         poblacion_hijos;
    
    cout << "\nPoblacion : " << endl;
    mostrarMatrizInt(poblacion);

    //while(evaluaciones < MAX_EVALUACIONES){
        dispersion_poblacion = dispersionPoblacion(poblacion);
        cout << "\nDispersion : " << endl;
        mostrarVector(dispersion_poblacion);
        poblacion_hijos = seleccion(poblacion, dispersion_poblacion, TAMANIO_POBLACION_GENERACIONAL);

        cruceUniforme(poblacion_hijos, TAMANIO_POBLACION_GENERACIONAL);
        
        mutacion(poblacion_hijos, TAMANIO_POBLACION_GENERACIONAL);
        /*
        reemplazamiento();

        evaluaciones++;*/
    //}

    return poblacion[0];

    // faltaria escoger el vector<int> que mejor P(t) tenga del vector<vector<int> >
}