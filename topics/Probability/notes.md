# Probabilidad para Programación Competitiva (CP).
AMGL



### Problema D: Door 1
* **Contest:** 1ra fecha Mexico 2026
* **URL:** https://codeforces.com/gym/106495
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

### Problema H: Huron Designs
* **Contest:** 1ra Fecha 2025 HHuron Designs
* **URL:** https://codeforces.com/gym/105873/standings
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

### Problema E: Erratic Lights
* **Contest:** 2025-2026 ICPC Northwestern European Regional Programming Contest (NWERC 2025)
* **URL:** https://codeforces.com/gym/106353
* **Estatus:** Resuelto
* **Resuelto por:** angelmanuelgl
* **Tema:** Probabilidad, Valor Esperado, Linealidad de la Esperanza, Distribución Geométrica, Distribución Binomial, Combinatoria.
* **Hint:**
  <details>
  <summary>Haz clic para ver la pista</summary>
  El problema se puede dividir en dos fases utilizando la linealidad de la esperanza y una estrategia codiciosa (greedy) sobre las frecuencias de los colores:

  1 Primero que piensa si solo tienes dos colores  ¿Cuántos toques se necesitan para transformar una luz de un color fijo a otro color específico?

  2. Lo mejor es eliminar primero todas las luces del color menos frecuente (sea $r$).

  3. ¿Cuál es el valor esperado de toques para que una luz roja cambie a **cualquier otro color**? Una vez libre de red, cada luz tiene equiprobabilidad ($1/2$) de haber terminado en green o blue.

  4. Tras eliminar el color red, el problema se reduce a dejar solo 2 colores (gree y blue).
  </details>
* **Idea de solución:**
  <details>
  <summary>Haz clic para ver la idea de solución</summary>

  ####  Reducción y Ordenamiento Sin Pérdida de Generalidad
  Contamos las frecuencias iniciales de los tres colores y las ordenamos de menor a mayor: $r \le b \le g$ (donde $r, b, g$ corresponden a rojo, azul y verde respectivamente). Sin perdida de generalidad.

  Dado que $r + b + g = N$ y $r = \min(r, b, g)$, se cumple que $r \le \lfloor N/3 \rfloor \le 33$.



  ####  Caso 0: Todos los focos ya son del mismo color ($r = 0$ y $g = 0$)
  El costo esperado es **$0$**.



  ####  Caso 1: Solo hay 2 colores presentes ($r = 0$)
  Queremos transformar todas las $g$ luces del color minoritario (green) hacia el único otro color presente, el objetivo específico $b$ (blue).

  **Modelación para un solo foco:**
  Definimos la variable aleatoria $T$ como el número de toques necesarios para que un foco 'g' adopte por primera vez el color 'b'' objetivo. Podemos interpretar su distribución de probabilidad $P(T = i)$ de dos formas equivalentes:

  1. **Enfoque de Casos Favorables sobre Casos Totales (Conteo Clásico):**
  En $i$ toques, existen $3^i$ secuencias de colores equiprobables en total. Para requerir exactamente $i$ toques, las primeras $i - 1$ elecciones deben dar cualquier color distinto de azul (rojo o verde, $2$ opciones en cada paso) y el $i$-ésimo toque debe dar estrictamente azul ($1$ opción).
  $$P(T = i) = \frac{2^{i-1} \cdot 1}{3^i} = \frac{2^{i-1}}{3^i}$$
      
  2. **Enfoque de Ensayos Independientes de Bernoulli (Distribución Geométrica):**
  Cada toque es un ensayo independiente con probabilidad de éxito $p = 1/3$ (obtener azul) y probabilidad de fracaso $1 - p = 2/3$. Por ende, $T$ sigue una distribución geométrica $T \sim \text{Geom}(p)$ con masa de probabilidad:
  $$P(T = i) = (1 - p)^{i-1} p = \left(\frac{2}{3}\right)^{i-1} \left(\frac{1}{3}\right)$$

  **Cálculo del Valor Esperado para un foco:**
  Sumando la serie arithmetico-geométrica sobre todos los posibles valores de $i \ge 1$:
  $$\mathbb{E}[T] = \sum_{i=1}^{\infty} i \cdot P(T = i) = \sum_{i=1}^{\infty} i \cdot \left(\frac{2}{3}\right)^{i-1} \left(\frac{1}{3}\right) =  3$$

  **Costo Total por Linealidad de la Esperanza:**
  Dado que cada una de las $g$ luces verdes cambia de forma independiente, aplicamos linealidad de la esperanza multiplicando la constante previamente calculada 3 por la cantidad total de luces a transformar g:
  $$\text{Ans} = 3 \cdot g$$

 

  ####  Caso 2: Hay 3 colores presentes ($r > 0$)
  La estrategia consiste en dividir el proceso en dos fases: primero eliminar el color con la frecuencia mínima ($r$) convirtiendo cada una de esas luces a cualquier otro color disponible (verde o azul), y posteriormente resolver el sistema resultante con solo dos colores ($g$ y $b$).

  ##### Fase A: Eliminar las $r$ luces del color minoritario (rojas)
  Queremos hallar el número esperado de toques para que una luz roja cambie a **cualquier otro color** (verde o azul).

  **Modelación para un solo foco:**

  Sea $T$ el tiempo de parada para que una luz roja deje de ser roja. Analizamos $P(T = i)$ mediante dos enfoques:

  1. **Enfoque de Casos Favorables sobre Casos Totales (Conteo Clásico):**
  En $i$ toques hay $3^i$ secuencias equiprobables. Para que el primer cambio ocurra exactamente en el $i$-ésimo toque, en los primeros $i - 1$ intentos la luz debe mantenerse en rojo ($1$ opción) y en el toque $i$ debe cambiar a verde o azul ($2$ opciones).
    
  $$P(T = i) = \frac{1^{i-1} \cdot 2}{3^i} = \frac{2}{3^i}$$

  2. **Enfoque de Ensayos Independientes de Bernoulli (Distribución Geométrica):**
  Cualquier toque es un ensayo independiente donde el éxito es obtener verde o azul ($p = 1/3 + 1/3 = 2/3$) y el fracaso es volver a obtener rojo ($1 - p = 1/3$). La masa de probabilidad para $T \sim \text{Geom}(2/3)$ es:
  
  $$P(T = i) = (1 - p)^{i-1} p = \left(\frac{1}{3}\right)^{i-1} \left(\frac{2}{3}\right)$$

  **Cálculo del Valor Esperado por Foco:**
    Sumando la serie arithmetico-geométrica:
    $$\mathbb{E}[T] = \sum_{i=1}^{\infty} i \cdot P(T = i) = \sum_{i=1}^{\infty} i \cdot \left(\frac{1}{3}\right)^{i-1} \left(\frac{2}{3}\right) =  \frac{3}{2} $$

  **Costo Total de la Fase A por Linealidad:**
    Como hay $r$ luces rojas actuando de forma independiente, aplicamos linealidad de la esperanza:
    $$\text{transform\_all} = \frac{3}{2} \cdot r$$

  

  ##### Fase B: Condicionar sobre el estado final tras la eliminación (Distribución Binomial)
  Cuando una luz roja cambia por primera vez de color, finaliza en verde o azul con equiprobabilidad condicional:
  $$P(\text{Verde} \mid \text{Dejar Rojo}) = \frac{1/3}{2/3} = \frac{1}{2}, \quad P(\text{Azul} \mid \text{Dejar Rojo}) = \frac{1/3}{2/3} = \frac{1}{2}$$

  - **Escenarios posibles:**
    Si de las $r$ luces rojas eliminadas, exactamente $i$ se convierten en verde ($0 \le i \le r$), las restantes $r - i$ se convierten en azul.
    - Cantidad final de verdes: $G' = g + i$
    - Cantidad final de azules: $B' = b + r - i$

  - **Costo esperado del nuevo estado:**
    Del Caso 1 sabemos que resolver el estado $(0, G', B')$ convirtiendo el color de menor frecuencia en el otro requiere un costo esperado de $3 \cdot \min(G', B')$. En el código este costo es:
    $$\text{expect\_this\_case\_ans} = 3 \cdot \min(g + i, \, b + r - i)$$

  - **Probabilidad del nuevo estado**
    Existen $2^r$ secuencias posibles de colores destinos.
    La probabilidad de  $i$ luces para convertirse en verde es 
    $$ \frac{ \binom{r}{i}  }{ 2^i} $$

    Sumamos los costos ponderados por la frecuencia de combinación sobre todos los escenarios $0 \le i \le r$:
    $$\sum_{i=0}^{r}  3 \cdot \min(g + i, \, b + r - i) \cdot  \binom{r}{i} \cdot\frac{1}{2^i}$$

  - **Valor esperado de la Fase B:**
    
    $$\mathbb{E}[\text{después de transformar}] =  \frac{1}{2^r} \sum_{i=0}^{r} \binom{r}{i} \cdot 3 \cdot \min(g + i, \, b + r - i)$$



  ##### Respuesta Final
  Sumamos la esperanza de ambas fases independientes por linealidad:
  $$\text{Ans} = \text{transform\_all} + \mathbb{E}[\text{después de transformar}]$$
  
    ---

  #### Complexidad
  - **Tiempo:** $\mathcal{O}(R^2)  =\mathcal{O}(N^2)$ para precalcular el triángulo de Pascal de las combinatorias $\binom{r}{i}$ y $\mathcal{O}(R)$ para iterar la suma, donde $R = r \le 33$. 
  - **Espacio:** $\mathcal{O}(N^2)$ para la tabla de coeficientes binomiales.


  </details>


### Problema N: Did You See My Album?
* **Contest:** I Maratona Nordestina de Programação — 1st Northeastern Brazil Programming Contest
* **URL:** https://codeforces.com/gym/106667
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