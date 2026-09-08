# GameTheory 

**Dr Carlos Segura**
**Jueves 03 SeptimebreV**



## 1 Restriccionenes


Juegos combinatoriales:
* 2 Jugadores alternando turnos
* Informacion completa
* Sin azar
* Finito
* Siempre hay ganadr


Segun el tipo de movimientos
* Imparciales: Ambos juadores tienen los mismos tipos de movientos
* Partisaos: Desde un mismo estado el jugador A puede realizar un conjunto de mov diferentes al conjunto de mov del jugador B desde es emismo estado


Juegos Imparciales:
* Tipicamente: EL jugador que realiza el ultimo movimeinto gana
* TIpo Misere: el ultimo que mueve pierne.

*apartir de ahora nos centraremos en juegos Imparciales donde el ultimo jugador en mover gana*


## 2. Representacion de grafo

Construccion
* Los Nodos son estados y las aristas movimientos
* Los nodos sin aristas son nodos perdedores

Si desde un nodo...
* sale una arista a un perdedor, entonces es un nodo ganador.
* todas sus aristas van a nodos ganadores entonces es un nodo perdedor.

Como propagar:
* Usar orden topologico inverso



## 3. Ideas mas UTILES

Buscar una **propiedad** tal que
* Desde estados con esa propiedad todos los estados a los que puedes llegar no la tiene
* Desde estados que no tienen esa propiedad siempre se puede ir a un estado que si la tiene
* El estado(s) final (perdedor) tiene esa propiedad

Otra **idea muy util**:
* Representar numeros en binario


## 4. Multiplesjuegos independientes

Si tenemos el caso en que tenemos varios juegos combinatoriales y en cada turno:
* eliges un juego
* en ese juego eliges un movimiento


## 4.1 Numeros de Grundy

En la representacion de grafo descrita anteriormente en (2) hacemos lo siguiente
* Vertices sin aristas (Estados finales): Etiquetar con 0
* Para los demas vertices etiquetamos con el MEX de las etiquetas de sus nodos adyacentes

Notar que
* Estasos perdedores == 0 
* Estados gandores != 0

Para saber si se ganao o no en un estado general compuesto por un nodo de cada juego independiente lo que hacemos es tomar el XOR de los numeros de grundy de cada estado de los jeugos individuales.

Para la dmeostracion conviene pensar primero en el Juego de NIM

*Tenemos M pilas con varios objetos cada una, podemos quitar la cantidad que queramos de cada pila*

esto lo podemos modelar como N juegos independientes, fijarse en como se ven los grafos (2), y en que el XOR del la longitud de la torre cumplen la propiedad en (3).


## 5. Juegos no combinatorial


Ejemplo:
* [Day 4: Fun Games](https://www.hackerrank.com/contests 5-days-of-game-theory/challenges/fun-game)


## 5.1 Ideas para este tipo de juegos
Si el juego se trata de ir eligiendo entre un conjunto de objetos o de alguna forma podeos hacer que cada objeto elegido pertenezca a un grupo o en el que la estrategia optima es maximizar/minimazar

* La estrategia optima suele ser ordenar los objetos bajo cierto orden y elegirlos en ese orden

Para ello hay que
* Formular el problema como un problema de maximacion/minimizacion
* osea hay un jugador que quiere maximizar cierta funcion mientras el otro quiere minimizarla
* Ver que pasa cuando tenemos solo 2 objetos (los dos objetos del final)
* Hay que hacer ambos casos, si le toca mover al jugador A o al jugador B
* Generalizar la demostracion para ams de dos objetos

## 7. Tarea

### 7.1 Obligatorios

- [ X ] [MEX Game 1](https://codeforces.com/contest/1943/problem/A)
- [ X ] [Kaosar and Game](https://eolymp.com/en/problems/12261)
- [ ] [Everything Nim](https://codeforces.com/contest/1965/problem/A)
- [ X ] [Stair Game](https://cses.fi/problemset/task/1099)
- [  ] [Day 5: Final Tower Breakers](https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/final-tower-breakers)
- [ ] [Day 4: Powers Game](https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/powers-of-two-game/problem)
- [ ] [UVA1482: Playing with Stones](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=4228)
- [ ] [Marbles](https://codeforces.com/gym/101908/problem/B)
- [ ] [Matgame](https://www.spoj.com/problems/MATGAME/)

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

