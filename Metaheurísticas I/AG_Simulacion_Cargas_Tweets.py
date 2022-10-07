import numpy
import random
 
'''
------------------------------------------
 Población original: se generan 8 soluciones aleatoriamente
 Calcular la aptitud: calcular el valor de la aptitud de 8 soluciones
 Elija padre: 2 de las soluciones con mayor aptitud
 Genere descendencia: el cruce y la mutación de los padres generan 2 nuevas soluciones
 Nueva población: 2 padres + 2 hijos
------------------------------------------
'''
 
equation_inputs = [1]
 
new_population = [] 

def get_random_combination(procesadores, max_tweets):
    combinacion = []
    for c in range(procesadores):
        combinacion.append(random.randint(1, max_tweets+1))
    return combinacion

def is_valid_combination(combinacion, total_tweets):

    if sum(combinacion) != total_tweets:
        return False
        
    return True

f = False

while f==False:
    combinacion = get_random_combination(8, 800)
    if is_valid_combination(combinacion, 1000):
        new_population.append(combinacion)
        f = True


def cal_pop_fitness(pop):
    fitness = []
    fitness.append(numpy.mean(pop)) 
    fitness.append(numpy.std(pop)) 
    
    return fitness
 
a = cal_pop_fitness(new_population)
print("Initial population:")
print(new_population, 'PROM: ', numpy.mean(new_population), ' Desv: ', numpy.std(new_population),'\n') 

population = []
n_popluation = 20

for i in range(50):
    f = 0
    while f != n_popluation:
        combinacion = get_random_combination(8, 500)
        if is_valid_combination(combinacion, 1000):
            if numpy.std(new_population) > numpy.std(combinacion):               
                population.append(combinacion)
                f += 1

    f = 0
    
    
    padre_1 = []
    padre_2 = []
    padre_1 = population[0]
    

    l = 0
    k = 0
    for c in population:
        if numpy.std(c) < numpy.std(padre_1):
            padre_1 = c
            k = l

        l += 1
    
           
    population.pop(k)
    padre_2 = population[0]
    for c in population:
        if (numpy.std(c) < numpy.std(padre_2)) & (c != padre_1):
            padre_2 = c

    
    print('\n','Generacion ',i+1)
    print('Padres')
    print(padre_1, 'PROM: ', numpy.mean(padre_1), ' Desv: ', numpy.std(padre_1))
    print(padre_2, 'PROM: ', numpy.mean(padre_2), ' Desv: ', numpy.std(padre_2))

    r = random.randint(1,6)

    hijo_1 = numpy.zeros(8)
    hijo_2 = numpy.zeros(8)

    #Cruzamiento
    hijo_1 = padre_1[:r] + padre_2[r:]
    hijo_2 = padre_2[:r] + padre_1[r:]

    print('Hijos')        
    print(hijo_1, 'PROM: ', numpy.mean(hijo_1), ' Desv: ', numpy.std(hijo_1))
    print(hijo_2, 'PROM: ', numpy.mean(hijo_2), ' Desv: ', numpy.std(hijo_2))

    r = random.randint(0,7)
    r2 = random.randint(0,7)
    
    hijo_1[r] = 0
    hijo_2[r2] = 0

    hijo_1[r] = 1000 - sum(hijo_1)
    hijo_2[r2] = 1000 - sum(hijo_2)

    print('Mutaciones')        
    print(hijo_1, 'PROM: ', numpy.mean(hijo_1), ' Desv: ', numpy.std(hijo_1))
    print(hijo_2, 'PROM: ', numpy.mean(hijo_2), ' Desv: ', numpy.std(hijo_2))
    
    population = []
    
    population.append(padre_1)
    population.append(padre_2)
    population.append(hijo_1)
    population.append(hijo_2)

    
    n_popluation = 16
    
        
