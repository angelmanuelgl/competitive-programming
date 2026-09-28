# 2026 ICPC Gran Premio de México - 2da Fecha

## Información General

* **Evento:** 2026 ICPC Gran Premio de México (2da Fecha)
* **Fecha:** Sábado 16 de Mayo
* **Modalidad:** Contest Oficial
* **Lugar:** CIMAT
* **Link Codeforces:** [Gym 106540](https://codeforces.com/gym/106540)

---

##  Lista de Problemas


### Problema A: A simple problem
* **Estatus:** ACCEPTED upsolveado
* **Resuelto por:** Rogelio
* **Tema:**  KMP | strings | dp 
* **Hint:**
  <details>
  <summary>Haz clic para ver la pista</summary>
  - Pensar en que prefijos se pueden generar con otros prefijos
  </details>

* **Idea de solución:**
  <details>
  <summary>Haz clic para ver la idea de solución</summary>
    - dp[ l ] = cantidad de palabras de esas longitud

    - encontrar la "BASE de prefijos" con KMP // O(N)

    - para las transcione usar esa base de prefijos

    - $dp[ l ] =  \sum_{prefjo \in base} ( dp[ l - longitud_de_prefijo ] )$

    - hay K estados y N transcione
  </details>

---

### Problema B: Baus Stream
* **Estatus:** ACCEPTED upsolving
* **Resuelto por:**  Angel
 **Tema:** Trie | Tree DP | Knapsack

* **Hint:**
  <details>
  <summary>Haz clic para ver la pista</summary>

  Cada prefijo representa un subárbol del trie. Buscar ese prefijo elimina todos los usernames dentro de dicho subárbol.

  </details>

* **Idea de solución:**
  <details>
  <summary>Haz clic para ver la idea de solución</summary>

  - Construimos un trie y calculamos `cnt[u]`, la cantidad de usernames en el subárbol de `u`.

  - Definimos `dp[u][i]` como el mínimo número de búsquedas para eliminar exactamente `i` usernames del subárbol de `u`.

  - Combinamos cada hijo `v` como tree knapsack:
    $$ndp[a+b]=\min(ndp[a+b],dp[u][a]+dp[v][b]).$$

  - También podemos buscar directamente el prefijo `u`, eliminando `cnt[u]` usernames con una sola búsqueda:
    $$dp[u][cnt[u]]=\min(dp[u][cnt[u]],1).$$

  - La respuesta es `dp[root][k]`.

  - **Complejidad:** $O(SK)$ tiempo y $O(SK)$ memoria, donde $S$ es la suma de las longitudes de los usernames.

  </details>

---

### Problema C: Counting heroes
* **Estatus:** ACCEPTED in contest
* **Resuelto por:** Angel (idea) y Jorge (implemtacion)
* **Tema:** Combinatoria Exponenciacion Binaria Inverso modular
* **Hint:**
  <details>
  <summary>Haz clic para ver la pista</summary>
  Los test son independientes, producto de probabilidades. Piensa en como calcular la probabilidad de un test para un N fijo. 
  
  Que pasa si fijas C?
  </details>
* **Idea de solución:**
  <details>
  <summary>Haz clic para ver la idea de solución</summary>
    Si fijas $c$ tienes $piso((c-1)/2)$ formas de elgir $a$ y $b$, asi tienes $\sum_{i=1}^{c-1} piso(i/2)$.

    Haces casos favorables entre posibles y listo.
  </details>

---

### Problema D: Dragon King's Palace
* **Estatus:** ACCEPTED in contest
* **Resuelto por:** 
* **Tema:** 
<!-- * **Hint:**
  <details>
  <summary>Haz clic para ver la pista</summary>
   - 
  </details>
* **Idea de solución:**
  <details>
  <summary>Haz clic para ver la idea de solución</summary>
  -
  </details> -->

---

### Problema E: Evil "Taquero"
* **Estatus:** ACCEPTED in contest
* **Resuelto por:** 
* **Tema:** 
<!-- * **Hint:**
  <details>
  <summary>Haz clic para ver la pista</summary> 
  -
  </details>
* **Idea de solución:**
  <details>
  <summary>Haz clic para ver la idea de solución</summary>  
  -
  </details> -->

---

### Problema F: Forever in love
* **Estatus:** Pendiente
* **Resuelto por:** 
* **Tema:** 
<!-- * **Hint:**
  <details>
  <summary>Haz clic para ver la pista</summary>
  -
  </details>
* **Idea de solución:**
  <details>
  <summary>Haz clic para ver la idea de solución</summary> 
  -
  </details> -->

---

### Problema G: Group forming
* **Estatus:** ACCEPTED in contest
* **Resuelto por:**  Angel y Rogelio (idea) y Jorge (Implemetacion)
* **Tema:** Grafos, Ad-hoc
* **Hint:**
  <details>
  <summary>Haz clic para ver la pista</summary>
  Mirar que pasa con las componentes conexas del grafo, segun el tamaño de la mas grande.
  </details>
* **Idea de solución:**
  <details>
  <summary>Haz clic para ver la idea de solución</summary> 
  Si la componente conexa mas grande tiene menos O igual que N/2 entonces se pueden hacer N/2 parejas.

  Si la componente conexa mas grande tiene tamaño digamos cnt mayor estricto que N/2, entonces solo se podra hacer N - cnt numero de parejas
  </details>

---

### Problema H: Huron Airlines
* **Estatus:** ACCEPTED Upsolving
* **Resuelto por:** Angel
* **Tema:** Implementacion, Ad-hoc
* **Hint:**
  <details>
  <summary>Haz clic para ver la pista</summary>
  Piensa en como implementar la simulacion.
  </details>
* **Idea de solución:**
  <details>
  <summary>Haz clic para ver la idea de solución</summary>
  Usar un Bit para calcular maximos en $[0:b]$.
  </details>

---

### Problema I: I don't have the name I was supposed to have
* **Estatus:** ACCEPTED in contest
* **Resuelto por:** 
* **Tema:** 
<!-- * **Hint:**
  <details>
  <summary>Haz clic para ver la pista</summary>
  -
  </details>
* **Idea de solución:**
  <details>
  <summary>Haz clic para ver la idea de solución</summary>
  -
  </details> -->

---


### Problema J: Jorge likes "sum over all subarrays" problems

* **Estatus:** ACCEPT Upsolving
* **Resuelto por:** Angel
* **Tema:** Combinatoria | Polinomios | Divide y vencerás | NTT
* **Hint:**
  <details>
  <summary>Haz clic para ver la pista</summary>

  Fija un subconjunto de tamaño $k$. ¿En cuántas permutaciones sus elementos aparecen juntos como un bloque? Después, piensa qué representan los coeficientes de $\prod_{i=1}^{n}(1+ix)$.

  </details>

* **Idea de solución:**
  <details>
  <summary>Haz clic para ver la idea de solución</summary>

  - Un subconjunto de tamaño $k$ aparece como bloque en $k!(n-k+1)!$ permutaciones: $k!$ formas de ordenar sus elementos y $(n-k+1)!$ formas de acomodar el bloque con los elementos restantes.

  - Construimos $P(x)=\prod_{i=1}^{n}(1+ix)$. El coeficiente $P[k]$ suma los productos de todos los subconjuntos de tamaño $k$.

  - Para construirlo, usamos divide y vencerás: cada hoja representa un factor $(1+ix)$ y combinamos los productos de ambas mitades mediante convolución con NTT.

  - Precalculamos factoriales y obtenemos la respuesta:
    $$\sum_{k=1}^{n} P[k]\cdot k!\cdot(n-k+1)!\pmod{998244353}.$$

  Sea $S_n$ el conjunto de todas las permutaciones de $\{1,\dots,n\}$. Definimos:

    $$
    \begin{aligned}
    \mathrm{Ans}
    &=\sum_{\text{permutación }\pi}
      \sum_{\text{intervalo }[l,r]}
      \prod_{j=l}^{r}\pi_j\\
    &=\sum_{k=1}^{n}
      \sum_{\substack{S\subseteq[n]\\|S|=k}}
      \#(\text{apariciones de }S)\prod_{a\in S}a\\
    &=\sum_{k=1}^{n}
      \sum_{\substack{S\subseteq[n]\\|S|=k}}
      \underbrace{k!(n-k+1)!}_{w_k}\prod_{a\in S}a\\
    &=\sum_{k=1}^{n}w_k
      \underbrace{\left(
      \sum_{\substack{S\subseteq[n]\\|S|=k}}
      \prod_{a\in S}a\right)}_{v_k}\\
    &=\boxed{\sum_{k=1}^{n}w_kv_k}.
    \end{aligned}
    $$

  - $w_k=k!(n-k+1)!$: ordenamos los $k$ elementos dentro de un bloque y luego acomodamos ese bloque con los $n-k$ elementos restantes.
  - $v_k=[x^k]\prod_{i=1}^{n}(1+ix)$: elegir $k$ factores que aporten $ix$ equivale a elegir un subconjunto de tamaño $k$. Calculamos estos coeficientes con divide y vencerás y NTT. 




  - **Complejidad:** $O(n\log^2 n)$ tiempo y $O(n)$ espacio por caso.

  </details> 
---

### Problema K: K Vertices
* **Estatus:** Pendiente
* **Resuelto por:** 
* **Tema:** 
<!-- * **Hint:**
  <details>
  <summary>Haz clic para ver la pista</summary> 
  -
  </details>
* **Idea de solución:**
  <details>
  <summary>Haz clic para ver la idea de solución</summary>
  
  -
  </details> -->

---

### Problema L: Landau's Fourth Problem
* **Estatus:** Pendiente
* **Resuelto por:** 
* **Tema:** 
<!-- * **Hint:**
  <details>
  <summary>Haz clic para ver la pista</summary>
  -
  </details>
* **Idea de solución:**
  <details>
  <summary>Haz clic para ver la idea de solución</summary>
  -
  </details> -->