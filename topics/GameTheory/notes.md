# GameTheory  | Numero de Grundy
**Dr Carlos Segura**
**Jueves 03 Septimebre**

--- 
## 1. Restriccionenes


**Juegos combinatoriales:**
* 2 jugadores alternando turnos.
* Información completa.
* Sin elementos de azar.
* Finito.
* Siempre hay un ganador (sin empates).


**Según el tipo de movimientos:**
* **Imparciales:** Ambos jugadores tienen exactamente el mismo conjunto de movimientos legales desde cualquier estado.
* **Partidarios (Partisan):** Desde un mismo estado, el Jugador A puede realizar un conjunto de movimientos distinto al del Jugador B.

**Juegos Imparciales:**
* **Convención Normal:** El jugador que realiza el último movimiento gana.
* **Convención Misère:** El jugador que realiza el último movimiento pierde.

> *A partir de este punto, nos centraremos exclusivamente en juegos imparciales bajo convención normal (el último en mover gana).*


## 2. Representacion de grafo

**Construcción:**
* Los **nodos** representan estados del juego y las **aristas** representan movimientos válidos.
* Los nodos sin aristas salientes (sin movimientos posibles) son **nodos perdedores**.


**Propagación de Estados:**
Desde un nodo dado:
* Si **sale al menos una arista** a un nodo perdedor, es un **nodo ganador**.
* Si **todas sus aristas** van a nodos ganadores, es un **nodo perdedor**.


Sobre laimplementacion:
* Propagar estados utilizando un orden topológico inverso.



## 3. Ideas mas UTILES

Buscar una **propiedad** tal que
1. Desde un estado con la propiedad, **todos** los movimientos llevan a estados que **no** la tienen.
2. Desde un estado sin la propiedad, **existe al menos un** movimiento que lleva a un estado que **sí** la tiene.
3. El estado (o estados) terminal perdedor **posee** la propiedad.

Otra idea muy util: **Representación en Binario:**
* Analizar la paridad de los bits en las cantidades de elementos (Base del juego de NIM)

## 4. Multiplesjuegos independientes

Cuando el estado global se compone de $N$ juegos combinatoriales independientes, y en cada turno el jugador:
1. Elige uno de los sub-juegos.
2. Realiza un movimiento válido en ese sub-juego.



## 4.1 Numeros de Grundy

En la representacion de grafo descrita anteriormente (3) hacemos lo siguiente
* **Nodos terminales (sin salidas):** Se etiquetan con $0$.
* **Demás nodos:** Se etiquetan con el $\text{MEX}$ (Minimum Excludant) de las etiquetas de sus nodos adyacentes salientes:
  $$\text{MEX}(S) = \min \{ x \in \mathbb{N}_0 \mid x \notin S \}$$

> **Importante:** Si el problema no define explícitamente los estados perdedores en términos de 'no tener movimientos' (por ejemplo, el objetivo es mover una ficha a una casilla determinada), debemos transformar el juego identificando los nodos que **obligan** a dejar al oponente en una posición ganadora. Dichos nodos actuarán como nuestros estados terminales ($G = 0$).
> Notar que es diferente 'mover una ficha a una posicion ganadora (posicion en la que no puede hacer mas movimientos esa ficha)' a decir 'gana el ultimo que no pueda realizar movimientos'.
> En general si sabemos exactamente en que nodos ganamos al un movimeinto ganador, encontramos los nodos que nos obligen a ir a esos nodos ganadores, esos seran nuestros estados finales, e ignoramos los nodos ganadores mencionados previamente

**Propiedades:**
* **Estado Perdedor ($P$):** $\text{Grundy} = 0$
* **Estado Ganador ($N$):** $\text{Grundy} \neq 0$

**Teorema de Sprague-Grundy:**
Para evaluar la posición global de $N$ juegos independientes, se calcula el $\text{XOR}$ ($\oplus$) de los números de Grundy de cada sub-juego:
$$G_{\text{total}} = G(s_1) \oplus G(s_2) \oplus \dots \oplus G(s_k)$$

Para la Demostración conviene pensar primero en el Juego de NIM: 
* En el juego de NIM tenemos $M$ pilas de objetos con varios objetos cada una, podemos quitar la cantidad que queramos de cada pila.
* Lo podemos modelar como $N$ juegos independientes, fijarse en como se ven los grafos (2).
* La suma $\text{XOR}$ de las alturas de las pilas, donde las alturas satisfacen la propiedad invariante de la Sección anterior (3).






## 5. Juegos no combinatorial


Ejemplo:
* [Day 4: Fun Games](https://www.hackerrank.com/contests 5-days-of-game-theory/challenges/fun-game)


## 5.1 Estrategias para Juegos de Maximización / Minimización

Si el juego consiste en elegir elementos alternadamente entre un conjunto de objetos o de alguna forma podemos hacer que cada objeto elegido pertenezca a un grupo

* La estrategia óptima suele requerir **ordenar los objetos** bajo un criterio específico y seleccionarlos de forma *greedy*.


Para ello hay que
1. Formular la dinámica como un problema de maximización/minimización 
2. Osea el Jugador A busca maximizar la función $F$, Jugador B busca minimizarla
3. Analizar el caso base con solo 2 objetos al final del juego (los dos objetos del final)
4. Como son los objetos del final hay que evaluar ambos escenarios: cuándo es el turno del Jugador A y cuándo es del Jugador B.
5. Deducir la condicion de intercambio, es decir cuando nos cionviene elegir tal cosa.
6. Generalizar la demostracion para $N$ objetos.


## 6. Problemas de Práctica

### 6.1 Obligatorios

- [X] [MEX Game 1](https://codeforces.com/contest/1943/problem/A) (Difficulty: 2/5)
- [X] [Kaosar and Game](https://eolymp.com/en/problems/12261)  (Difficulty: 2/5)
- [X] [Everything Nim](https://codeforces.com/contest/1965/problem/A)  (Difficulty: 1/5)
- [X] [Stair Game](https://cses.fi/problemset/task/1099)  (Difficulty: 4/5)
- [X] [Day 5: Final Tower Breakers](https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/final-tower-breakers)  (Difficulty: 3/5) 
- [X] [Day 4: Powers Game](https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/powers-of-two-game/problem)  (Difficulty: 1.5/5)
- [X] [UVA1482: Playing with Stones](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=4228) (Difficulty: 2.5/5) 
- [X] [Marbles](https://codeforces.com/gym/101908/problem/B) (Difficulty: 3/5)
- [X] [Matgame](https://www.spoj.com/problems/MATGAME/) (Difficulty: 3/5) 

### 7.2 Otros sugeridos (Parte 1)

- [ ] [Tower Breakers](https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/tower-breakers)
- [ ] [Day 3: Tower Breakers, Again!](https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/tower-breakers-3)
- [ ] [Summation Game](https://codeforces.com/contest/1920/problem/B)
- [ ] [Poetry Challenge](https://codeforces.com/gym/100500)
- [ ] [Day 3: Digits Square Board](https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/digits-square-board)
- [ ] [Arbitrary Nim](https://atcoder.jp/contests/arc168/tasks/arc168_b)

### 7.3 Otros sugeridos (Parte 2)

- [ ] [Day 1: A Chessboard Game](https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/day-1-a-chessboard-game)
- [ ] [Day 2: Nimble Game](https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/nimble)
- [ ] [1-2-K Game](https://codeforces.com/contest/1194/problem/D)
- [ ] [Day 2: Tower Breakers, Revisited!](https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/tower-breakers-2)
- [ ] [Temporal Paradox](https://codeforces.com/group/Rilx5irOux/contest/622715/problem/D) _(Nota: requiere darse de alta en el [grupo de Codeforces](https://codeforces.com/group/Rilx5irOux))_





# GameTheory  | Numero de Grundy
**Dr Carlos Segura**
**Jueves 03 Septimebre**

----

- [ ] Bob vs. ATM: https://www.codechef.com/AMR16MOS/problems/AMR16J
- [ ] https://lightoj.com/problem/game-of-cs
- [ ] Got root?: https://www.hackerrank.com/greenhackenbush
