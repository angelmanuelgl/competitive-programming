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