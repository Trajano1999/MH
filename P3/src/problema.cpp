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

/*// jjj muestra un vector int
void mostrarVectorInt(const vector<int> & v)
{
    cout << "( ";
    for(unsigned i=0; i<v.size(); ++i)
        cout << v[i] << " ";
    cout << ")"; 
}

// jjj muestra un vector double
void mostrarVectorDouble(const vector<double> & v)
{
    cout << "( ";
    for(unsigned i=0; i<v.size(); ++i)
        cout << v[i] << " ";
    cout << ")"; 
}

// jjj muestra una matriz int
void mostrarMatrizInt(const vector<vector<int> > & m)
{
    for(unsigned i=0; i<m.size(); ++i)
    {
        cout << "( ";
        for(unsigned j=0; j<m[i].size(); ++j)
            cout << m[i][j] << " ";
        cout << ")" << endl;
    }
}
*/

//-------------------------------------------------------------------------------------------------
// CONSTANTES GLOBALES
//-------------------------------------------------------------------------------------------------

// máximo valor de un double en c++
const double VALOR_GRANDE     = 1.7976931348623158e+308,
             PROB_CRUCE_AGG   = 0.7,
             PROB_CRUCE_AGE   = 1.0,
             PROB_MUTACION    = 0.1,
             PROB_BL_MEMETICO = 0.1;
            
const unsigned MAX_EVALUACIONES      = 100000,
               MAX_EVAL_MEMETICOS    = 400,
               TAMANIO_POBLACION_GEN = 50,
               TAMANIO_POBLACION_EST = 2,
               TAMANIO_POBLACION_MM  = 10,
               MAX_EVALUCAIONES_BMB  = 10000;

//-------------------------------------------------------------------------------------------------
// MÉTODOS PRIVADOS GENERALES
//-------------------------------------------------------------------------------------------------

double Problema::valorMaximo(const vector<double> & v)
{
    double valor_max = 0.0;

    for(unsigned i=0; i<v.size(); ++i)
        if(v[i] > valor_max)
            valor_max = v[i];

    return valor_max;
}

double Problema::valorMinimoPositivo(const vector<double> & v)
{
    double valor_min = VALOR_GRANDE;

    for(unsigned i=0; i<v.size(); ++i)
        if(v[i] < valor_min && v[i] > 0)
            valor_min = v[i];
        
    return valor_min;
}

int Problema::posicionMinimoPositivo(const vector<double> & v)
{
    int pos_min = 0;
    double valor_min = VALOR_GRANDE;

    for(unsigned i=0; i<v.size(); ++i)
        if(v[i] < valor_min && v[i] > 0)
        {
            valor_min = v[i];
            pos_min = i;
        }
        
    return pos_min;
}

void Problema::intercambio(vector<int> & v, int valor1, int valor2)
{
    for(unsigned i=0; i<v.size(); ++i)
        if(v[i] == valor1)
            v[i] = valor2;
}

bool Problema::estaEnVector(vector<int> vector, int valor)
{
    for(unsigned i=0; i<vector.size(); ++i)
        if(vector[i] == valor)
            return true;

    return false;
}

int Problema::calcularPosicion(const vector<int> & v, int elem)
{
    int res = -1;

    for(unsigned i=0; i<v.size(); ++i)
        if(v[i] == elem)
            res = i;

    return res;
}

vector<int> Problema::generarVectorPoblacionAleatorio(unsigned tamanio_vector)
{
    unsigned random;
    vector<int> resultado(tamanio_vector, 0);

    for(unsigned i=0; i<elem_sel; ++i)
    {
        // el do-while es para que no se repitan los aleatorios
        do{
            random = rand() % tamanio_vector;
        }while(resultado[random] == 1);

        resultado[random] = 1; 
    }

    return resultado;
}

vector<int> Problema::generarVectorPueblosAleatorio()
{
    return transformacionVectorPueblos(generarVectorPoblacionAleatorio(elem_tot));
}

//-------------------------------------------------------------------------------------------------
// MÉTODOS PRIVADOS GREEDY
//-------------------------------------------------------------------------------------------------

int Problema::randomGreedy(unsigned sem, int min, int max)
{
    // utilizamos srand() para modificar la semilla
    srand(sem);
    return rand() % (max-min+1) + min;
}

vector<double> Problema::sigmaNoSeleccionados(const vector<int> & cand, const vector<int> & sol)
{
    unsigned tamanio_cand = cand.size(),
             tamanio_sol = sol.size();
    double suma = 0.0;
    vector<double> res (tamanio_cand, 0.0);

    for(unsigned i=0; i<tamanio_cand; ++i)
        if(cand[i] != -1)
        {
            for(unsigned j=0; j<tamanio_sol; ++j)
                suma += matriz[sol[j]][cand[i]] == 0 ? matriz[cand[i]][sol[j]] : matriz[sol[j]][cand[i]];
            
            res[i] = suma;
            suma = 0.0;
        }
    
    return res;
}

vector<double> Problema::sigmaSeleccionados(const vector<int> & sol)
{
    unsigned tamanio_sol = sol.size();
    double suma = 0.0;
    vector<double> res (tamanio_sol, 0.0);
    
    for(unsigned i=0; i<tamanio_sol; ++i)
    {
        for(unsigned j=0; j<tamanio_sol; ++j)
            if(i != j)
                suma += matriz[sol[i]][sol[j]] == 0 ? matriz[sol[j]][sol[i]] : matriz[sol[i]][sol[j]];

        res[i] = suma;
        suma = 0.0;
    }

    return res;
}

int Problema::elementoMenorDispersion(const vector<int> & cand, const vector<int> & sol)
{
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
        if(cand[i] != -1)
        {
            // calculamos el vector de la suma de distancias de los sigma seleccionados 
            // más la distancia de añadir el elemento i no seleccionado
            for(unsigned j=0; j<tamanio_sol; ++j)
            {
                distancia = matriz[sol[j]][cand[i]] == 0 ? matriz[cand[i]][sol[j]] : matriz[sol[j]][cand[i]];
                sigma[j] = sigma_seleccionados[j] + distancia;
            }

            // calculamos el max y min entre los sigmas seleccionados y los sigmas actuales
            max = valorMaximo(sigma);         if(sigma_no_seleccionados[i] > max) max = sigma_no_seleccionados[i];
            min = valorMinimoPositivo(sigma); if(sigma_no_seleccionados[i] < min && sigma_no_seleccionados[i] > 0) min = sigma_no_seleccionados[i];
            
            // la dispersión es 0 si el tamaño del vector solución es 1
            dispersion[i] = tamanio_sol > 2 ? max - min : 0;
        }

    // escogemos el menor valor del vector de dispersion
    return posicionMinimoPositivo(dispersion);
}

//-------------------------------------------------------------------------------------------------
// MÉTODOS PRIVADOS BL
//-------------------------------------------------------------------------------------------------

double Problema::dispersionIntercambiarElementos(const vector<int> & sol, int elem_eliminar, int elem_aniadir)
{
    unsigned tamanio_sol = sol.size();
    unsigned pos_eliminado = calcularPosicion(sol, elem_eliminar);
    double distancia,
           suma = 0.0;
    vector<double> distancias = sigmaSeleccionados(sol);
    
    // modificamos las distancias para eliminar un elemento
    for(unsigned i=0; i<tamanio_sol; ++i)
    {
        if(i != pos_eliminado)
            distancias[i] -= matriz[sol[i]][elem_eliminar] == 0 ? matriz[elem_eliminar][sol[i]] : matriz[sol[i]][elem_eliminar];
        else
            distancias[i] = 0;
    }

    // modificamos las distancias para añadir un elemento
    for(unsigned i=0; i<tamanio_sol; ++i)
        if(i != pos_eliminado)
        {
            distancia = matriz[sol[i]][elem_aniadir] == 0 ? matriz[elem_aniadir][sol[i]] : matriz[sol[i]][elem_aniadir];
            distancias[i] += distancia;
            suma += distancia;
        }

    distancias[pos_eliminado] = suma;
    return tamanio_sol > 2 ? valorMaximo(distancias) - valorMinimoPositivo(distancias) : 0;
}

//-------------------------------------------------------------------------------------------------
// MÉTODOS PRIVADOS AGs
//-------------------------------------------------------------------------------------------------

double Problema::dispersionVectorPoblacion(const vector<int> & vector_poblacion)
{
    unsigned tamanio_poblacion = vector_poblacion.size();
    vector<int> vector_pueblos;

    for(unsigned i=0; i<tamanio_poblacion; ++i)
        if(vector_poblacion[i] == 1)
            vector_pueblos.push_back(i);

    return dispersion(vector_pueblos);
}

vector<double> Problema::dispersionPoblacion(const vector<vector<int> > & poblacion)
{
    unsigned tamanio_poblacion = poblacion.size();
    vector<double> resultado;
    
    for(unsigned i=0; i<tamanio_poblacion; ++i)
        resultado.push_back(dispersionVectorPoblacion(poblacion[i]));
    
    return resultado;
}

// jjj arreglar P2
void Problema::reparacion(vector<int> & hijo)
{
    unsigned contador = 0,
             mejor_posicion = 0,
             tamanio = hijo.size();
    double dispersion, 
           menor_dispersion = dispersionVectorPoblacion(hijo);
    
    for(unsigned i=0; i<tamanio; ++i)
        if(hijo[i] == 1)
            contador++;

    while(contador > elem_sel)
    {
        menor_dispersion = VALOR_GRANDE;

        // buscamos el elemento que más dispersión tenga y lo eliminamos
        for(unsigned i=0; i<tamanio; ++i)
            if(hijo[i] == 1)
            {
                hijo[i] = 0;
                dispersion = dispersionVectorPoblacion(hijo);
                if(dispersion < menor_dispersion)
                {
                    menor_dispersion = dispersion;
                    mejor_posicion = i;
                }
                hijo[i] = 1;
            }
        
        hijo[mejor_posicion] = 0;
        contador--;
    }

    while(contador < elem_sel)
    {
        menor_dispersion = VALOR_GRANDE;

        // buscamos el elemento que menos dispersión sume y lo añadimos
        for(unsigned i=0; i<tamanio; ++i)
            if(hijo[i] == 0)
            {
                hijo[i] = 1;
                dispersion = dispersionVectorPoblacion(hijo);
                if(dispersion < menor_dispersion)
                {
                    menor_dispersion = dispersion;
                    mejor_posicion = i;
                }
                hijo[i] = 0;
            }
        
        hijo[mejor_posicion] = 1;
        contador++;
    }
}

vector<int> Problema::mejorVectorPoblacion(const vector<vector<int> > & poblacion)
{
    unsigned posicion = 0, 
             tamanio_poblacion = poblacion.size();
    double mejor_dispersion = VALOR_GRANDE;
    vector<double> dispersiones;

    // calculamos la dispersion de todos los vectores de la poblacion
    dispersiones = dispersionPoblacion(poblacion);

    // buscamos el mínimo valor del vector dispersiones
    for(unsigned i=0; i<tamanio_poblacion; ++i)
        if(dispersiones[i] < mejor_dispersion)
        {
            mejor_dispersion = dispersiones[i];
            posicion = i;
        }

    return poblacion[posicion];
}

vector<int> Problema::peorVectorPoblacion(const vector<vector<int> > & poblacion)
{
    unsigned posicion = 0, 
             tamanio_poblacion = poblacion.size();
    double peor_dispersion = 0;
    vector<double> dispersiones;

    // calculamos la dispersion de todos los vectores de la poblacion
    dispersiones = dispersionPoblacion(poblacion);

    // buscamos el máximo valor del vector dispersiones
    for(unsigned i=0; i<tamanio_poblacion; ++i)
        if(dispersiones[i] > peor_dispersion)
        {
            peor_dispersion = dispersiones[i];
            posicion = i;
        }

    return poblacion[posicion];
}

vector<int> Problema::transformacionVectorPueblos(const vector<int> & vector_poblacion)
{
    unsigned tamanio_vector = vector_poblacion.size();
    vector<int> resultado;

    for(unsigned i=0; i<tamanio_vector; ++i)
        if(vector_poblacion[i] == 1)
            resultado.push_back(i);
    
    return resultado;
}

vector<int> Problema::transformacionVectorPoblacion(const vector<int> & vector_pueblos)
{
    unsigned tamanio = vector_pueblos.size();
    vector<int> resultado(elem_tot, 0);
    
    for(unsigned i=0; i<tamanio; ++i)
        resultado[vector_pueblos[i]] = 1;
    
    return resultado;
}

vector<vector<int> > Problema::creacionPoblacion(unsigned tamanio_poblacion)
{
    vector<vector<int> > resultado;
    
    for(unsigned i=0; i<tamanio_poblacion; ++i)
        resultado.push_back(generarVectorPoblacionAleatorio(elem_tot));

    return resultado;
}

vector<vector<int> > Problema::seleccion(const vector<vector<int> > & poblacion, const vector<double> & dispersion_poblacion, unsigned num_torneos)
{
    int aleatorio1, aleatorio2;
    vector<vector<int> > resultado;

    for(unsigned i=0; i<num_torneos; ++i)
    {     
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

void Problema::cruceUniforme(vector<vector<int> > & poblacion_hijos, unsigned tamanio_cruce, double probabilidad)
{
    int aleatorio1, aleatorio2, aleatorio3;
    vector<int> auxiliar(elem_tot, -1);

    for(unsigned i=0; i<probabilidad*tamanio_cruce; ++i)
    {    
        // seleccionamos 2 aleatorios distintos
        aleatorio1 = rand() % (tamanio_cruce);
        do{
            aleatorio2 = rand() % (tamanio_cruce);
        }while(aleatorio2 == aleatorio1);

        // rellenamos el vector aux con el cruce de los dos aleatorios
        for(unsigned j=0; j<elem_tot; ++j)
        {
            aleatorio3 = rand() % 2;
            auxiliar[j] = aleatorio3 > 0 ? poblacion_hijos[aleatorio1][j] : poblacion_hijos[aleatorio2][j];
        }

        // reparamos el vector auxiliar y actualizamos la poblacion
        reparacion(auxiliar);
        poblacion_hijos[i] = auxiliar;
    }
}

void Problema::crucePosicion(vector<vector<int> > & poblacion_hijos, unsigned tamanio_cruce, double probabilidad)
{
    int aleatorio1, aleatorio2, aleatorio3;
    vector<int> restos_padre;

    for(unsigned i=0; i<probabilidad*tamanio_cruce; ++i)
    {
        vector<int> auxiliar(elem_tot, -1);
        restos_padre.clear();

        // seleccionamos 2 aleatorios distintos
        aleatorio1 = rand() % (tamanio_cruce);
        do{
            aleatorio2 = rand() % (tamanio_cruce);
        }while(aleatorio2 == aleatorio1);

        for(unsigned j=0; j<elem_tot; ++j)
        {    
            // si tienen el mismo valor, se mantiene en el hijo
            if( poblacion_hijos[aleatorio1][j] == poblacion_hijos[aleatorio2][j] )
                auxiliar[j] = poblacion_hijos[aleatorio1][j];
            
            // sino, lo añadimos al vector restos_padre para barajarlo y añadirlo
            else
                restos_padre.push_back(poblacion_hijos[aleatorio1][j]);
        }

        // recorremos auxiliar y donde haya -1 ponemos un valor aleatorio de restos_padre
        for(unsigned j=0; j<auxiliar.size(); ++j)
            if(auxiliar[j] == -1)
            {
                aleatorio3 = rand() % (restos_padre.size());
                auxiliar[j] = restos_padre[aleatorio3];
                restos_padre.erase(restos_padre.begin()+aleatorio3);
            }
        
        // modificamos el vector poblacion por el auxiliar
        poblacion_hijos[i] = auxiliar;
    }
}

void Problema::mutacionGeneracional(vector<vector<int> > & poblacion_hijos, double probabilidad)
{    
    unsigned aleatorio1, 
             aleatorio2,
             auxiliar;
    
    for(unsigned i=0; i<TAMANIO_POBLACION_GEN*probabilidad; ++i)
    {
        aleatorio1 = rand() % (elem_tot);
        do{
            aleatorio2 = rand() % (elem_tot);
        }while(aleatorio2 == aleatorio1 || poblacion_hijos[i][aleatorio1] == poblacion_hijos[i][aleatorio2]);

        auxiliar = poblacion_hijos[i][aleatorio1];
        poblacion_hijos[i][aleatorio1] = poblacion_hijos[i][aleatorio2];
        poblacion_hijos[i][aleatorio2] = auxiliar;
    }
}

void Problema::mutacionEstacionaria(vector<vector<int> > & poblacion_hijos, double probabilidad)
{
    unsigned vector_elegido,
             aleatorio1, 
             aleatorio2,
             auxiliar;
    
    for(unsigned i=0; i<TAMANIO_POBLACION_EST*probabilidad*elem_tot; ++i)
    {
        vector_elegido = rand() % 2;
        aleatorio1 = rand() % (elem_tot);
        do{
            aleatorio2 = rand() % (elem_tot);
        }while(aleatorio2 == aleatorio1 || poblacion_hijos[vector_elegido][aleatorio1] == poblacion_hijos[vector_elegido][aleatorio2]);

        auxiliar = poblacion_hijos[vector_elegido][aleatorio1];
        poblacion_hijos[vector_elegido][aleatorio1] = poblacion_hijos[vector_elegido][aleatorio2];
        poblacion_hijos[vector_elegido][aleatorio2] = auxiliar;
    }
}

void Problema::reemplazamientoGeneracional(vector<vector<int> > & poblacion, const vector<vector<int> > & poblacion_hijos)
{
    unsigned posicion_peor = 0;
    bool mejor_encontrado = false,
         peor_encontrado = false;
    vector<int> peor_vector_poblacion,
                mejor_vector_poblacion = mejorVectorPoblacion(poblacion);

    poblacion = poblacion_hijos;

    for(unsigned i=0; i<TAMANIO_POBLACION_GEN && !mejor_encontrado; ++i)
        if(poblacion[i] == mejor_vector_poblacion)
            mejor_encontrado = true;

    // si el mejor vector de la iteración anterior no está, lo sustituimos por el peor actual
    if(!mejor_encontrado)
    {
        peor_vector_poblacion = peorVectorPoblacion(poblacion);

        for(unsigned i=0; i<TAMANIO_POBLACION_GEN && !peor_encontrado; ++i)
            if(poblacion[i] == peor_vector_poblacion)
            {
                peor_encontrado = true;
                posicion_peor = i;
            }

        poblacion[posicion_peor] = mejor_vector_poblacion;
    }
}

void Problema::reemplazamientoEstacionario(vector<vector<int> > & poblacion, const vector<vector<int> > & poblacion_hijos)
{
    unsigned peor_posicion = 0,
             tamanio_poblacion = poblacion.size(),
             tamanio_poblacion_hijos = poblacion_hijos.size();
    double peor_dispersion;
    vector<double> dispersiones, 
                   dispersiones_hijos = dispersionPoblacion(poblacion_hijos);

    for(unsigned i=0; i<tamanio_poblacion_hijos; ++i)
    {
        peor_dispersion = 0;
        dispersiones = dispersionPoblacion(poblacion);
        
        for(unsigned j=0; j<tamanio_poblacion; ++j)
            if(dispersiones[i] > peor_dispersion)
            {
                peor_dispersion = dispersiones[i];
                peor_posicion = i;
            }
        
        if(dispersiones[peor_posicion] > dispersiones_hijos[i])
            poblacion[peor_posicion] = poblacion_hijos[i];
    }
}

//-------------------------------------------------------------------------------------------------
// MÉTODOS PRIVADOS AMs
//-------------------------------------------------------------------------------------------------

vector<int> Problema::busquedaLocalP2(const vector<int> & vector_inicio, unsigned max_evaluaciones, unsigned & evaluaciones)
{
    unsigned aleatorio1,
             auxiliar,
             num_evaluaciones = 0,
             coste_anterior,
             coste_nuevo,
             tamanio_resultado = vector_inicio.size();
    vector<int> candidatos,
                elementos_escogidos,
                resultado = vector_inicio;

    // generamos el vector de candidatos
    for(unsigned i=0; i<elem_tot; ++i)
        candidatos.push_back(i);
    for(unsigned i=0; i<tamanio_resultado; ++i)
        candidatos[resultado[i]] = -1;
    
    for(unsigned i=0; i<tamanio_resultado; ++i)
    {   
        // escogemos el aleatorio 
        do{
            aleatorio1 = rand() % (elem_tot);          
            if(!estaEnVector(elementos_escogidos, aleatorio1))
                elementos_escogidos.push_back(aleatorio1);

            coste_anterior = dispersion(resultado);
            coste_nuevo = dispersionIntercambiarElementos(resultado, resultado[i], candidatos[aleatorio1]);
        }while(
            ( coste_anterior <= coste_nuevo || estaEnVector(elementos_escogidos, aleatorio1) || candidatos[aleatorio1] == -1 ) 
            && elementos_escogidos.size() < elem_tot && num_evaluaciones < max_evaluaciones
        );
        
        // si aleatorio1 disminuye la dispersion, intercambiamos
        if(coste_nuevo < coste_anterior)
        {
            auxiliar = resultado[i];
            intercambio(resultado, resultado[i], candidatos[aleatorio1]);
            candidatos[aleatorio1] = -1;
            candidatos[auxiliar] = auxiliar;
            num_evaluaciones++;
        }

        elementos_escogidos.clear();
    }        

    evaluaciones += num_evaluaciones;
    return resultado;
}

vector<int> Problema::mutacionILS(vector<int> & solucion, unsigned t)
{
    unsigned aleatorio,
             pos_eliminar;
    vector<int> resultado = solucion,
                elem_repetidos,
                pos_repetidas;

    for(unsigned i=0; i<t; ++i)
    {
        // buscamos el elem aleatorio
        do{
            aleatorio = rand() % (elem_tot);
        }while(
            estaEnVector(elem_repetidos,aleatorio) || estaEnVector(solucion,aleatorio)
        );
        elem_repetidos.push_back(aleatorio);

        // buscamos la posicion a eliminar
        do{
            pos_eliminar = rand() % (elem_sel);
        }while(
            estaEnVector(pos_repetidas,pos_eliminar)
        );
        pos_repetidas.push_back(pos_eliminar);
        
        resultado[pos_eliminar] = aleatorio;
    }

    return resultado;
}

//-------------------------------------------------------------------------------------------------
// CONSTRUCTOR
//-------------------------------------------------------------------------------------------------

Problema::Problema(unsigned sem, const char * dir_fich)
{
    // almacenamos la semilla
    semilla = sem;

    // rellenamos la matriz
    setMatriz(dir_fich);
}

//-------------------------------------------------------------------------------------------------
// OBSERVADORES
//-------------------------------------------------------------------------------------------------

unsigned Problema::getSemilla()
{
    return semilla;
}

unsigned Problema::getElementosTotales()
{
    return elem_tot;
}

unsigned Problema::getElementosSeleccionados()
{
    return elem_sel;
}

vector<vector<double> > Problema::getMatriz()
{
    return matriz;
}

//-------------------------------------------------------------------------------------------------
// MODIFICADORES
//-------------------------------------------------------------------------------------------------

void Problema::setSemilla(unsigned sem)
{
    semilla = sem;
}

void Problema::setMatriz(const char * dir_fich)
{   
    // abrimos el fichero
    ifstream fichero(dir_fich);
    if(!fichero.is_open())
        cerr << "Error al abrir " << dir_fich << endl;

    // leemos los primeros valores del fichero
    fichero >> elem_tot;
    fichero >> elem_sel;

    // redimensionamos la matriz
    vector<vector<double> > aux(elem_tot, vector<double>(elem_tot)); 
    matriz = aux;

    int num_lineas = (elem_tot * (elem_tot-1)) / 2;
    int pueblo1,
        pueblo2;
    double distancia;

    // rellenamos la matriz con el resto de valores del fichero
    for(int i=0; i<num_lineas; ++i)
    {
        fichero >> pueblo1;
        fichero >> pueblo2;
        fichero >> distancia;
        matriz[pueblo1][pueblo2] = distancia;
    }
}

//-------------------------------------------------------------------------------------------------
// MÉTODOS PÚBLICOS
//-------------------------------------------------------------------------------------------------

double Problema::dispersion(const vector<int> & v)
{
    vector<double> sigmas_seleccionados = sigmaSeleccionados(v);
    return v.size() > 2 ? valorMaximo(sigmas_seleccionados) - valorMinimoPositivo(sigmas_seleccionados) : 0;
}

//-------------------------------------------------------------------------------------------------
// MÉTODOS PARA RESOLVER EL PROBLEMA
//-------------------------------------------------------------------------------------------------

vector<int> Problema::solucionGreedy()
{
    int mejor_candidato = randomGreedy(semilla, 0, elem_tot-1);
    vector<int> sol, candidatos;
    
    // rellenamos el vector de candidatos
    for(unsigned i=0; i<elem_tot; ++i)
        candidatos.push_back(i);

    // añadimos el primer valor aleatorio
    sol.push_back(mejor_candidato);
    candidatos[mejor_candidato] = -1;

    // añadimos los demás pueblos
    while(sol.size() < elem_sel)
    {             
        mejor_candidato = elementoMenorDispersion(candidatos, sol);
        sol.push_back(mejor_candidato);
        candidatos[mejor_candidato] = -1;
    }
    
    return sol;
}

vector<int> Problema::solucionBusquedaLocal()
{
    unsigned evaluaciones = 0;
    vector<int> aleatorio = transformacionVectorPueblos(generarVectorPoblacionAleatorio(elem_tot));
    return busquedaLocalP2(aleatorio, MAX_EVALUACIONES, evaluaciones);
}

vector<int> Problema::solucionAGGUniforme()
{
    unsigned evaluaciones = 0;
    vector<int> vector_poblacion;
    vector<double> dispersion_poblacion;
    vector<vector<int> > poblacion = creacionPoblacion(TAMANIO_POBLACION_GEN),
                         poblacion_hijos;

    while(evaluaciones < MAX_EVALUACIONES)
    {
        dispersion_poblacion = dispersionPoblacion(poblacion);
        poblacion_hijos = seleccion(poblacion, dispersion_poblacion, TAMANIO_POBLACION_GEN);

        cruceUniforme(poblacion_hijos, TAMANIO_POBLACION_GEN, PROB_CRUCE_AGG);
        mutacionGeneracional(poblacion_hijos, PROB_MUTACION);
        reemplazamientoGeneracional(poblacion, poblacion_hijos);
        evaluaciones += 50;
    }

    // transformamos el vector_poblacion en un vector de pueblos
    vector_poblacion = mejorVectorPoblacion(poblacion);
    return transformacionVectorPueblos(vector_poblacion);
}

vector<int> Problema::solucionAGGPosicion()
{
    unsigned evaluaciones = 0;
    vector<int> vector_poblacion;
    vector<double> dispersion_poblacion;
    vector<vector<int> > poblacion = creacionPoblacion(TAMANIO_POBLACION_GEN),
                         poblacion_hijos;

    while(evaluaciones < MAX_EVALUACIONES)
    {
        dispersion_poblacion = dispersionPoblacion(poblacion);
        poblacion_hijos = seleccion(poblacion, dispersion_poblacion, TAMANIO_POBLACION_GEN);

        crucePosicion(poblacion_hijos, TAMANIO_POBLACION_GEN, PROB_CRUCE_AGG);
        mutacionGeneracional(poblacion_hijos, PROB_MUTACION);
        reemplazamientoGeneracional(poblacion, poblacion_hijos);
        evaluaciones += 50;
    }

    // transformamos el vector_poblacion en un vector de pueblos
    vector_poblacion = mejorVectorPoblacion(poblacion);
    return transformacionVectorPueblos(vector_poblacion);
}

vector<int> Problema::solucionAGEUniforme()
{
    unsigned evaluaciones = 0;
    vector<int> vector_poblacion;         
    vector<double> dispersion_poblacion;
    vector<vector<int> > poblacion = creacionPoblacion(TAMANIO_POBLACION_GEN),
                         poblacion_hijos;

    while(evaluaciones < MAX_EVALUACIONES)
    {
        dispersion_poblacion = dispersionPoblacion(poblacion);
        poblacion_hijos = seleccion(poblacion, dispersion_poblacion, TAMANIO_POBLACION_EST);

        cruceUniforme(poblacion_hijos, TAMANIO_POBLACION_EST, PROB_CRUCE_AGE);
        mutacionEstacionaria(poblacion_hijos, PROB_MUTACION);
        reemplazamientoEstacionario(poblacion, poblacion_hijos);
        evaluaciones += 2;
    }

    // transformamos el vector_poblacion en un vector de pueblos
    vector_poblacion = mejorVectorPoblacion(poblacion);
    return transformacionVectorPueblos(vector_poblacion);
}

vector<int> Problema::solucionAGEPosicion()
{
    unsigned evaluaciones = 0;
    vector<int> vector_poblacion;
    vector<double> dispersion_poblacion;
    vector<vector<int> > poblacion = creacionPoblacion(TAMANIO_POBLACION_GEN),
                         poblacion_hijos;

    while(evaluaciones < MAX_EVALUACIONES)
    {
        dispersion_poblacion = dispersionPoblacion(poblacion);
        poblacion_hijos = seleccion(poblacion, dispersion_poblacion, TAMANIO_POBLACION_EST);

        crucePosicion(poblacion_hijos, TAMANIO_POBLACION_EST, PROB_CRUCE_AGE);
        mutacionEstacionaria(poblacion_hijos, PROB_MUTACION);
        reemplazamientoEstacionario(poblacion, poblacion_hijos);
        evaluaciones += 2;
    }

    // transformamos el vector_poblacion en un vector de pueblos
    vector_poblacion = mejorVectorPoblacion(poblacion);
    return transformacionVectorPueblos(vector_poblacion);
}

vector<int> Problema::solucionAM1()
{
    unsigned evaluaciones = 0;
    vector<int> vector_poblacion;
    vector<double> dispersion_poblacion;
    vector<vector<int> > poblacion_hijos,
                         poblacion = creacionPoblacion(TAMANIO_POBLACION_MM);

    while(evaluaciones < MAX_EVALUACIONES)
    {
        dispersion_poblacion = dispersionPoblacion(poblacion);
        poblacion_hijos = seleccion(poblacion, dispersion_poblacion, TAMANIO_POBLACION_MM);

        cruceUniforme(poblacion_hijos, TAMANIO_POBLACION_MM, PROB_CRUCE_AGG);
        mutacionGeneracional(poblacion_hijos, PROB_MUTACION);
                
        // cada 10 generaciones, aplicamos BL a toda la población
        if(evaluaciones % 10 == 0)
            for(unsigned i=0; i<TAMANIO_POBLACION_MM; ++i)  
                poblacion_hijos[i] = transformacionVectorPoblacion(busquedaLocalP2(transformacionVectorPueblos(poblacion_hijos[i]), MAX_EVAL_MEMETICOS, evaluaciones));
        else
            evaluaciones++;

        reemplazamientoGeneracional(poblacion, poblacion_hijos);                
    }

    // transformamos el vector_poblacion en un vector de pueblos
    vector_poblacion = mejorVectorPoblacion(poblacion);
    return transformacionVectorPueblos(vector_poblacion);
}

vector<int> Problema::solucionAM2()
{
    unsigned aleatorio,
             evaluaciones = 0;
    vector<int> vector_poblacion,
                repeticion_aleatorios;
    vector<double> dispersion_poblacion;
    vector<vector<int> > poblacion_hijos,
                         poblacion = creacionPoblacion(TAMANIO_POBLACION_MM);

    while(evaluaciones < MAX_EVALUACIONES)
    {
        dispersion_poblacion = dispersionPoblacion(poblacion);
        poblacion_hijos = seleccion(poblacion, dispersion_poblacion, TAMANIO_POBLACION_MM);

        cruceUniforme(poblacion_hijos, TAMANIO_POBLACION_MM, PROB_CRUCE_AGG);
        mutacionGeneracional(poblacion_hijos, PROB_MUTACION);
                
        // cada 10 generaciones, aplicamos BL a un subconjunto de la población
        if(evaluaciones % 10 == 0)
        {
            for(unsigned i=0; i<TAMANIO_POBLACION_MM*PROB_BL_MEMETICO; ++i)
            {
                // generamos aleatorios distintos
                do{
                    aleatorio = rand() % (TAMANIO_POBLACION_MM);
                }while(estaEnVector(repeticion_aleatorios, aleatorio));

                repeticion_aleatorios.push_back(aleatorio);
                poblacion_hijos[aleatorio] = transformacionVectorPoblacion(busquedaLocalP2(transformacionVectorPueblos(poblacion_hijos[aleatorio]), MAX_EVAL_MEMETICOS, evaluaciones));
            }
            repeticion_aleatorios.clear();
        }
        else
            evaluaciones++;

        reemplazamientoGeneracional(poblacion, poblacion_hijos);                
    }

    // transformamos el vector_poblacion en un vector de pueblos
    vector_poblacion = mejorVectorPoblacion(poblacion);
    return transformacionVectorPueblos(vector_poblacion);
}

vector<int> Problema::solucionAM3()
{
    unsigned mejor_pos,
             evaluaciones = 0;
    vector<int> mejor_vector,
                vector_poblacion;
    vector<double> dispersion_poblacion;
    vector<vector<int> > poblacion_hijos,
                         poblacion = creacionPoblacion(TAMANIO_POBLACION_MM);

    while(evaluaciones < MAX_EVALUACIONES)
    {
        dispersion_poblacion = dispersionPoblacion(poblacion);
        poblacion_hijos = seleccion(poblacion, dispersion_poblacion, TAMANIO_POBLACION_MM);

        cruceUniforme(poblacion_hijos, TAMANIO_POBLACION_MM, PROB_CRUCE_AGG);
        mutacionGeneracional(poblacion_hijos, PROB_MUTACION);
                
        dispersion_poblacion = dispersionPoblacion(poblacion_hijos);
        // cada 10 generaciones, aplicamos BL a los mejores
        if(evaluaciones % 10 == 0)
            for(unsigned i=0; i<TAMANIO_POBLACION_MM*PROB_BL_MEMETICO; ++i)
            {
                mejor_pos = posicionMinimoPositivo(dispersion_poblacion);
                poblacion_hijos[mejor_pos] = transformacionVectorPoblacion(busquedaLocalP2(transformacionVectorPueblos(poblacion_hijos[mejor_pos]), MAX_EVAL_MEMETICOS, evaluaciones));
                dispersion_poblacion.erase(dispersion_poblacion.begin() + mejor_pos);
            }
        else
            evaluaciones++;

        reemplazamientoGeneracional(poblacion, poblacion_hijos);                
    }

    // transformamos el vector_poblacion en un vector de pueblosm
    vector_poblacion = mejorVectorPoblacion(poblacion);
    return transformacionVectorPueblos(vector_poblacion);
}

// jjj
vector<int> Problema::solucionEnfriamientoSimulado()
{
    vector<int> resultado;
    /* unsigned enfriamientos = 0,
             max_vecinos   = 10*elem_tot,
             num_enfriamientos = MAX_EVALUACIONES / max_vecinos;

    double prob_sol_peor     = 0.3,
           max_exitos        = 0.1*max_vecinos,
           temperatura_final = 0.01;
    
    vector<int> resultado;

    while(enfriamientos < MAX_EVALUACIONES) // && nº exitos en enfriamiento actual != 0
    {
        // intercambio de dos elementos aleatorios
        // comparamos la solucio vecina con la actual

        // se enfriará la temperatura si 
        // se genera num max de vecinos (max_vecinos) o 
        // se hayan aceptado demasiados vecinos generados (max_exitos)
        enfriamientos++;
    }*/

    return resultado;
}

vector<int> Problema::solucionBusquedaMultiarranque()
{   
    unsigned evaluaciones = 0;
    double dispersion_actual,
           mejor_dispersion = VALOR_GRANDE;
    vector<int> solucion_actual, 
                mejor_solucion;

    for(unsigned i=0; i<10; ++i)
    {
        solucion_actual = busquedaLocalP2(generarVectorPueblosAleatorio(), MAX_EVALUCAIONES_BMB, evaluaciones);
        dispersion_actual = dispersion(solucion_actual);

        if( dispersion_actual < mejor_dispersion)
        {
            mejor_dispersion = dispersion_actual;
            mejor_solucion = solucion_actual;
        }
    }

    return mejor_solucion;
}

vector<int> Problema::solucionILS()
{
    unsigned evaluaciones = 0,
             tamanio_mutacion = 0.3*elem_sel;
    double dispersion_actual,
           mejor_dispersion;
    vector<int> solucion_mutada,
                solucion_actual,
                mejor_solucion;

    mejor_solucion = busquedaLocalP2(generarVectorPueblosAleatorio(), MAX_EVALUCAIONES_BMB, evaluaciones);
    mejor_dispersion = dispersion(mejor_solucion);

    for(unsigned i=0; i<9; ++i)
    {
        solucion_mutada = mutacionILS(mejor_solucion, tamanio_mutacion);
        solucion_actual = busquedaLocalP2(solucion_mutada, MAX_EVALUCAIONES_BMB, evaluaciones);
        dispersion_actual = dispersion(solucion_actual);

        if( dispersion_actual < mejor_dispersion)
        {
            mejor_dispersion = dispersion_actual;
            mejor_solucion = solucion_actual;
        }
    }

    return mejor_solucion;
}

// jjj
vector<int> Problema::solucionILS_ES()
{
    unsigned evaluaciones = 0,
             tamanio_mutacion = 0.3*elem_sel;
    double dispersion_actual,
           mejor_dispersion;
    vector<int> solucion_mutada,
                solucion_actual,
                mejor_solucion;

    mejor_solucion = solucionEnfriamientoSimulado();
    mejor_dispersion = dispersion(mejor_solucion);

    for(unsigned i=0; i<9; ++i)
    {
        solucion_mutada = mutacionILS(mejor_solucion, tamanio_mutacion);
        // aqui no se si es BL o ES
        solucion_actual = busquedaLocalP2(solucion_mutada, MAX_EVALUCAIONES_BMB, evaluaciones);
        dispersion_actual = dispersion(solucion_actual);

        if( dispersion_actual < mejor_dispersion)
        {
            mejor_dispersion = dispersion_actual;
            mejor_solucion = solucion_actual;
        }
    }

    return mejor_solucion;
}