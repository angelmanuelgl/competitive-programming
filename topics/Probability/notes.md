# Probabilidad para Programación Competitiva (CP).
Ángel Manuel González López

### Introducción y Conceptos Fundamentales en Común
Los tres problemas analizados (*Erratic Lights*, *Huron Designs* y *Door 1*) comparten pilares teóricos fundamentales que todo competidor debe dominar:

1. **Linealidad de la Esperanza:** 
   La esperanza de una suma de variables aleatorias es siempre igual a la suma de sus esperanzas individuales, **incluso si no son independientes**. Esto permite descomponer problemas complejos de conteo de costos o tiempos totales (como sumar los toques esperados por cada foco individual) en elementos más sencillos.

2. **Distribución Geométrica y Procesos de Bernoulli:**
   Cuando un evento independiente se repite hasta obtener el primer éxito (por ejemplo, cambiar un foco de color o lograr un estado específico), el número de ensayos necesarios sigue una distribución geométrica. Su valor esperado se calcula mediante la serie aritmético-geométrica $\sum_{i=1}^{\infty} i \cdot (1-p)^{i-1}p = \frac{1}{p}$.

3. **Inferencia Bayesiana y Actualización de Creencias:**
   Ante parámetros desconocidos pero fijos (como la probabilidad $p$ de aparición del hurón gigante distribuida uniformemente en $[0, 1]$), utilizamos distribuciones Beta y la **Regla de Sucesión de Laplace**. Si en $k$ eventos previos se han observado $g$ éxitos, la probabilidad esperada del siguiente evento se suaviza como $\frac{g + 1}{k + 2}$.

4. **Programación Dinámica con Probabilidades (DP + Probabilidad):**
   Las decisiones óptimas a menudo no se toman buscando un resultado determinista, sino maximizando o minimizando el valor esperado de éxito o supervivencia. La DP permite descomponer la línea de tiempo en subproblemas superpuestos evaluando todas las transiciones posibles en cada estado (como decidir esconderse o arriesgarse a buscar recursos), resolviendo las recurrencias en reversa (*backward*) o acumulando probabilidades condicionales hacia adelante.

# Problemas: 

## Problema D: Door 1
- **Contest:** 1ra fecha Mexico 2026
- **URL:** https://codeforces.com/gym/106495/problem/D
- **Estatus:** ACCEPTED
- **Resuelto por:** angelmanuelgl
- **Tema:** Programación Dinámica, Probabilidad Condicional, Teorema de Bayes, Inferencia Bayesiana.
- **Hint:**
  <details>
    <summary>Haz clic para ver la pista</summary>
    El problema involucra una probabilidad desconocida $p$ para el hurón gigante, elegida uniformemente al azar de $[0, 1]$. Sin embargo, a medida que avanzan las horas, podemos actualizar nuestra creencia sobre $p$ usando el Teorema de Bayes o la regla de sucesión de Laplace basándonos en las apariciones observadas.


    <details> <summary> Que debe almacenar cada estado? </summary>
    el número de horas transcurridas $i$, las baterías actuales $s$, el hambre acumulada $h$, y el número de veces $g$ que ha aparecido el hurón gigante hasta el momento.
    </details>

    En cada hora, puedes elegir entre tres acciones: esconderte, buscar batería o buscar comida. Cada acción tiene ramificaciones independientes (hurón sensible a la luz, éxito de búsqueda, envenenamiento y aparición del hurón gigante).
  </details>
- **Solución:**
  <details>
    <summary>Haz clic para ver la idea de solución</summary>

    ### 1. Modelación 
    Tenemos un total de $N$ horas de supervivencia, un límite de capacidad de baterías $K$, baterías iniciales $S$, y un umbral máximo de hambre $H$. 

    Definimos nuestra función de programación dinámica `dpr(i, s, h, g)` como la **máxima probabilidad de sobrevivir** desde el inicio de la hora $i$ hasta el final, encontrándonos bajo los siguientes parámetros:
    - `i`: Hora actual en la que nos encontramos ($1 \le i \le N$).
    - `s`: Cantidad actual de baterías en nuestra bolsa ($0 \le s \le K$).
    - `h`: Horas transcurridas desde la última comida exitosa ($0 \le h < H$).
    - `g`: Número acumulado de veces que el hurón gigante ha aparecido en las horas anteriores ($0 \le g < i$).

    #### 1.1 Inferencia Bayesiana del Hurón Gigante
    Esta es la parte que ocupa teoria no basica: El problema establece que la probabilidad $p$ de que aparezca el hurón gigante fue elegida uniformemente al azar del intervalo $[0, 1]$. Si modelamos $p$ como una variable aleatoria con distribución previa $\text{Beta}(1, 1)$ (que corresponde a una uniforme en $[0,1]$), y observamos $g$ apariciones del hurón gigante en $i-1$ horas previas, la distribución posterior de $p$ sigue una distribución $\text{Beta}(1 + g, 1 + (i-1) - g)$. 

    Por lo tanto, la probabilidad estimada de que el hurón gigante aparezca en la hora actual $i$ dado que ha aparecido $g$ veces previamente está dada por la esperanza de esta distribución posterior (Regla de Sucesión de Laplace):
    $$p_{\text{GF}} = \frac{1 + g}{1 + i}$$
    Y la probabilidad de que no aparezca es:
    $$p_{\text{NoGF}} = 1 - p_{\text{GF}}$$

    **Intuicion:** 
    A mi me gusta pensarlo como lanzar una moneda con una probabilidad desconocida de que caiga cara. Si en $k$ tiradas ha caído $g$ veces cara, la probabilidad estimada de que vuelva a caer cara es 
    $$ \frac{g + 1}{k + 2}  $$
    (agregando un éxito y un fracaso ficticios por la distribución previa uniforme). 
    
    Dado que en nuestro estado actual de la programación dinámica llevamos evaluadas $i - 1$ horas previas, sustituimos $k = i - 1$, obteniendo directamente la probabilidad de aparición del hurón gigante:
    $$p_{\text{GF}} = \frac{g + 1}{(i - 1) + 2} = \frac{1 + g}{1 + i}$$
    Y la probabilidad de que no aparezca es:
    $$p_{\text{NoGF}} = 1 - p_{\text{GF}}$$


    #### 1.2 Acciones Disponibles en Cada Hora
    Al comienzo de cada hora, evaluamos tres opciones posibles y tomamos la que maximice la probabilidad de supervivencia:

    ##### Opción 1: Esconderse (`Hide`)
    Te mantienes en una cámara segura. Ningún hurón puede atacarte, pero el tiempo transcurre y el hambre aumenta. Dependiendo de si el hurón gigante aparece o no (lo cual se registra aunque estés a salvo):
    - Si aparece: $p_{\text{GF}} \times \text{dpr}(i+1, s, h+1, g+1)$
    - Si no aparece: $p_{\text{NoGF}} \times \text{dpr}(i+1, s, h+1, g)$

    ##### Opción 2: Buscar Batería (`Search for a battery`)
    Exploras los túneles. Existe la probabilidad de hallar una batería ($b_i$) o no ($1 - b_i$), y también la amenaza de que aparezca un hurón sensible a la luz con probabilidad $q_i$. 
    - Si aparece el hurón sensible a la luz y tenemos al menos $2$ baterías ($s \ge 2$), consumimos $2$ baterías para sobrevivir. De lo contrario, si $s < 0$, la rama muere.
    - Dependiendo de si encontramos o no batería, el inventario se ajusta en $+1$ o $0$ (acotado por el máximo $K$).

    ##### Opción 3: Buscar Comida (`Search for food`)
    Buscamos algo comestible con probabilidad $c_i$, pero con riesgo de envenenamiento $v_i$. El éxito total de comer sin morir es $p_{\text{Comer}} = c_i \cdot (1 - v_i)$. 
    - Si se logra comer con éxito, el contador de hambre $h$ se reinicia a $0$.
    - Si falla o hay envenenamiento, el hambre aumenta en $1$ ($h + 1$).

    #### 1.3 Transición y Casos Base
    La relación de recurrencia toma el máximo sobre las opciones válidas:
    $$\text{dpr}(i, s, h, g) = \max(\text{Esconderse}, \text{Buscar Batería}, \text{Buscar Comida})$$

    Guardando quien fue el maximo podemos obtener la serie de acciones que nos conviene hacer.

    **Casos Base:**
    - Si $s < 0$ (nos quedamos sin baterías ante un hurón): la probabilidad de sobrevivir es **$0.0$**.
    - Si $h \ge H$ (morimos de hambre): la probabilidad de sobrevivir es **$0.0$**.
    - Si $i > N$ (sobrevivimos con éxito todas las horas requeridas): la probabilidad de sobrevivir es **$1.0$**.


    #### Importante
    Vale la pena destacar que esta programación dinámica se calcula **de atrás hacia adelante (en reversa respecto al tiempo)**: la función resuelve el estado de la hora actual $i$ consultando los resultados óptimos de las horas futuras (`i + 1`) hasta alcanzar los casos base en $N$. La respuesta global del problema se obtiene directamente de la llamada inicial en el punto de partida original: `dpr(1, iniBaterias, 0, 0)`, la cual evalúa la probabilidad máxima de supervivencia recorriendo todas las decisiones óptimas a lo largo de las $N$ horas.

    #### Complejidad
    - **Tiempo:** $\mathcal{O}(N^2 \cdot K \cdot H)$. Dado que $N \le 500$, $K \le 12$, y $H \le 12$, el número total de estados de la programación dinámica es acotado de manera eficiente gracias a la memorización, permitiendo una ejecución fluida dentro del límite de 4 segundos.
    - **Espacio:** $\mathcal{O}(N^2 \cdot K \cdot H)$ para almacenar la tabla de DP y los indicadores de visita (`dp` y `dpcheck`).
  </details>


---

## Problema H: Huron Designs
* **Contest:** 1ra Fecha 2025 Huron Designs
* **URL:** https://codeforces.com/gym/105873/problem/H
* **Estatus:** ACCEPTED
- **Resuelto por:** angelmanuelgl
- **Tema:** Programación Dinámica con Máscaras de Bits (Bitmask DP), Probabilidad, Valor Esperado, Linealidad de la esperanza, Integral
- **Hint:**
  <details>
    <summary>Haz clic para ver la pista</summary>
    
    1. Dado que el número de solicitudes es pequeño ($n \le 20$), podemos representar cualquier subconjunto de tareas completadas mediante una máscara de bits de tamaño $2^n$. 

    2. Piensa en el orden en que se ejecutan las tareas: si fijamos el conjunto de tareas realizadas, ¿importa el orden de ejecución para conocer el tiempo total acumulado? de que depende el tiempo total transcurrido al finalizar un subconjunto de tareas? depende únicamente de cuáles tareas se han hecho, no del orden en que se programaron.
    
    3. Para calcular la ganancia esperada de una tarea $i$ completada en un tiempo exacto `tiempo`, debes analizar la intersección del tiempo de finalización con el intervalo de bonificación $[ly_i, ry_i]$ y el valor esperado de la bonificación uniforme en $[lx_i, rx_i]$.
  </details>
  <!-- SOLUCION -->
- **Solución:**
  <details>
    <summary>Haz clic para ver la idea de solución</summary>

    ### 1. Modelación
    Tenemos $n$ solicitudes ($1 \le n \le 20$). Cada solicitud $i$ requiere un tiempo de procesamiento $c_i$, tiene una fecha límite $d_i$, una ganancia base $p_i$, y bonificaciones aleatorias regidas por dos variables uniformes independientes: 
    
    $$ x_i \sim \mathcal{U}(lx_i, rx_i) \quad\text{ y } \quad y_i \sim \mathcal{U}(ly_i, ry_i) $$

    El objetivo es seleccionar un subconjunto de tareas y un orden de ejecución válido (respetando las fechas límite $d_i$) que maximice la **ganancia esperada total**. 

    El tiempo total acumulado para completar cualquier subconjunto exacto de tareas es constante e independiente del orden en que se ejecuten, siempre que se realicen todas. Esto nos permite definir un estado basado en máscaras de bits.

    ##### Cálculo del Valor Esperado de la Ganancia por Tarea (modo intutivio)
    Si la tarea es válida, sumamos la ganancia base $p_i$ más el valor esperado del bono $x_i$ condicionado al momento exacto en que se termina la tarea (`tiempo`):

    1. **Caso 1: El tiempo de finalización es menor o igual al límite inferior del bono ($\text{tiempo} \le ly_i$)**
       Tony termina con suficiente anticipación para asegurar el rango completo del bono. El valor esperado de la bonificación es la media del intervalo $[lx_i, rx_i]$:
       $$\mathbb{E}[\text{ganancia}_i] = p_i + \frac{lx_i + rx_i}{2}$$

    2. **Caso 2: El tiempo cae dentro del rango de incertidumbre ($ly_i < \text{tiempo} < ry_i$)**
       Existe una probabilidad lineal de que el cliente otorgue el bono completo o parcial dependiendo de qué tan temprano se haya finalizado respecto a $ry_i$. El valor esperado se ajusta proporcionalmente:
       $$\mathbb{E}[\text{ganancia}_i] = p_i + \left(\frac{lx_i + rx_i}{2}\right) \cdot \frac{ry_i - \text{tiempo}}{ry_i - ly_i}$$

    3. **Caso 3: El tiempo excede el límite superior del bono ($\text{tiempo} \ge ry_i$)**
       Tony termina demasiado tarde para recibir cualquier bonificación, obteniendo únicamente su ganancia base:
       $$\mathbb{E}[\text{ganancia}_i] = p_i$$

    #### Cálculo del Valor Esperado de la Ganancia por Tarea  (Integrando)
    Para justificar formalmente el valor esperado de la bonificación cuando el tiempo de finalización cae dentro del intervalo de incertidumbre $(ly_i, ry_i)$, podemos calcular la esperanza mediante la integral de la variable aleatoria. 

    Definimos el bono $X$ como una variable aleatoria continua con distribución uniforme 
    $$ X \sim \mathcal{U}(lx_i, rx_i) $$

    y el tiempo límite $Y$ con distribución uniforme 

    $$ Y \sim \mathcal{U}(ly_i, ry_i) $$
    
    donde ambas variables son independientes. Nos interesa calcular el valor esperado de recibir el bono condicionado a que el tiempo de finalización fijo $u$ (en nuestro código representado como `tiempo`) sea menor o igual que el tiempo límite aleatorio $Y$, es decir, evaluamos la esperanza de la variable aleatoria

    $$ X \cdot \mathbb{I}_{u < Y} $$

    Notemos que 
    
    $$\mathbb{E}[X \cdot \mathbb{I}_{u < Y}] = \mathbb{E}[X] \cdot \mathbb{P}(u < Y)$$

    Dado que $X$ es uniforme en $[lx_i, rx_i]$, su esperanza es simplemente el punto medio del intervalo:
    $$\mathbb{E}[X] = \frac{lx_i + rx_i}{2}$$

    Por otro lado, como $Y$ sigue una distribución uniforme en el intervalo $[ly_i, ry_i]$, su función de densidad de probabilidad es:

    $$f_Y(y) = \frac{1}{ry_i - ly_i} \quad \text{para } y \in [ly_i, ry_i]$$

    Calculamos la probabilidad $\mathbb{P}(u < Y)$ integrando la densidad de $Y$ desde el tiempo fijo $u$ hasta el límite superior $ry_i$:

    $$\mathbb{P}(u < Y) = \int_{u}^{ry_i} \frac{1}{ry_i - ly_i} \, dy = \frac{ry_i - u}{ry_i - ly_i}$$

    Multiplicando ambos componentes obtenemos la expresión analítica exacta utilizada en el Caso 2 de la solución:
    $$\mathbb{E}[X \cdot \mathbb{I}_{u < Y}] = \left(\frac{lx_i + rx_i}{2}\right) \cdot \frac{ry_i - u}{ry_i - ly_i}$$


    ### 2.Programación Dinámica con Máscaras de Bits (Bitmask DP)
    Definimos `dp[mask]` como la máxima ganancia esperada alcanzable al completar exactamente el subconjunto de tareas indicado por los bits encendidos en `mask` ($0 \le \text{mask} < 2^n$).

    Para calcular `dp[mask]`, iteramos sobre cada tarea $i$ que esté activa en la máscara (`is_on(mask, i)`). Suponemos que la tarea $i$ fue la **última** en ejecutarse dentro de ese subconjunto. El subproblema anterior corresponde a la máscara sin esa tarea: `prevMask = mask ^ (1 << i)`.

   
    El tiempo total acumulado al terminar todas las tareas de la máscara se calcula sumando las duraciones:
    $$\text{tiempo} = \sum_{j \in \text{mask}} c_j$$

    Para que la transición sea válida, la tarea $i$ debe finalizar a más tardar en su fecha límite:
    $$\text{tiempo} \le d_i$$
    Si esta condición no se cumple, la transición se descarta.

    Para las transiciones:
    Evaluamos todas las opciones posibles para la última tarea ejecutada y tomamos el máximo:
    $$\text{dp[mask]} = \max_{i \in \text{mask}, \, \text{tiempo} \le d_i} \left( \text{dp[prevMask]} + \mathbb{E}[\text{ganancia}_i] \right)$$

    ---

    ### Respuesta Final
    La respuesta global es el valor máximo almacenado en la tabla de DP entre todas las máscaras posibles:
    $$\text{Ans} = \max_{0 \le \text{mask} < 2^n} \text{dp[mask]}$$

    ### Complejidad
    - **Tiempo:** $\mathcal{O}(2^n \cdot n)$, donde $n \le 20$. Con $2^{20} \approx 10^6$ estados y un factor lineal de $n = 20$ transiciones por estado, el número total de operaciones es de alrededor de $2 \cdot 10^7$, ejecutándose holgadamente dentro del límite de 1 segundo.
    - **Espacio:** $\mathcal{O}(2^n)$ para almacenar los arreglos de la programación dinámica `dp` y `dpcheck`.
  </details>


---

## Problema E: Erratic Lights
* **Contest:** 2025-2026 ICPC Northwestern European Regional Programming Contest (NWERC 2025)
* **URL:** https://codeforces.com/gym/106353
* **Estatus:** ACCEPTED
* **Resuelto por:** angelmanuelgl
* **Tema:** Probabilidad, Valor Esperado, Linealidad de la Esperanza, Distribución Geométrica, Distribución Binomial, Combinatoria.
* **Hint:**
  <details>
    <summary>Haz clic para ver la pista</summary>
    El problema se puede dividir en dos fases utilizando la linealidad de la esperanza y una estrategia codiciosa (greedy) sobre las frecuencias de los colores:

    1.  Primero que piensa si solo tienes dos colores  ¿Cuántos toques se necesitan para transformar una luz de un color fijo a otro color específico?

    2. Lo mejor es eliminar primero todas las luces del color menos frecuente (sea $r$).

    3. ¿Cuál es el valor esperado de toques para que una luz roja cambie a **cualquier otro color**? Una vez libre de red, cada luz tiene equiprobabilidad ($1/2$) de haber terminado en green o blue.

    4. Tras eliminar el color red, el problema se reduce a dejar solo 2 colores (greeN y blue).
  </details>
  <!-- SOLUCION -->
* **Solución:**
  <details>
    <summary>Haz clic para ver la idea de solución</summary>

    ###  Reducción y Ordenamiento Sin Pérdida de Generalidad
    Contamos las frecuencias iniciales de los tres colores y las ordenamos de menor a mayor: $r \le b \le g$ (donde $r, b, g$ corresponden a rojo, azul y verde respectivamente). Sin perdida de generalidad.

    Dado que $r + b + g = N$ y $r = \min(r, b, g)$, se cumple que $r \le \lfloor N/3 \rfloor \le 33$.



    ###  Caso 0: Todos los focos ya son del mismo color ($r = 0$ y $g = 0$)
    El costo esperado es **$0$**.



    ###  Caso 1: Solo hay 2 colores presentes ($r = 0$)
    Queremos transformar todas las $g$ luces del color minoritario (green) hacia el único otro color presente, el objetivo específico $b$ (blue).

    **Modelación para un solo foco:**
    Definimos la variable aleatoria $T$ como el número de toques necesarios para que un foco 'g' adopte por primera vez el color 'b'' objetivo. Podemos interpretar su distribución de probabilidad $P(T = i)$ de dos formas equivalentes:

    1. **Enfoque de Casos Favorables sobre Casos Totales (Conteo Clásico):**
    En $i$ toques, existen $3^i$ secuencias de colores equiprobables en total. Para requerir exactamente $i$ toques, las primeras $i - 1$ elecciones deben dar cualquier color distinto de azul (rojo o verde, $2$ opciones en cada paso) y el $i$-ésimo toque debe dar estrictamente azul ($1$ opción).
    $$P(T = i) = \frac{2^{i-1} \cdot 1}{3^i} = \frac{2^{i-1}}{3^i}$$
        
    2. **Enfoque de Ensayos Independientes de Bernoulli (Distribución Geométrica):**
    Cada toque es un ensayo independiente con probabilidad de éxito $p = 1/3$ (obtener azul) y probabilidad de fracaso $1 - p = 2/3$. Por ende, $T$ sigue una distribución geométrica $T \sim \text{Geom}(p)$ con masa de probabilidad:
    $$P(T = i) = (1 - p)^{i - 1} p = \left(\frac{2}{3}\right)^{i-1} \left(\frac{1}{3}\right)$$

    **Cálculo del Valor Esperado para un foco:**
    Sumando la serie arithmetico-geométrica sobre todos los posibles valores de $i \ge 1$:
    $$\mathbb{E}[T] = \sum_{i=1}^{\infty} i \cdot P(T = i) = \sum_{i=1}^{\infty} i \cdot \left(\frac{2}{3}\right)^{i-1} \left(\frac{1}{3}\right) =  3$$

    **Costo Total por Linealidad de la Esperanza:**
    Dado que cada una de las $g$ luces verdes cambia de forma independiente, aplicamos linealidad de la esperanza multiplicando la constante previamente calculada 3 por la cantidad total de luces a transformar g:
    $$\text{Ans} = 3 \cdot g$$

  

    ###  Caso 2: Hay 3 colores presentes ($r > 0$)
    La estrategia consiste en dividir el proceso en dos fases: primero eliminar el color con la frecuencia mínima ($r$) convirtiendo cada una de esas luces a cualquier otro color disponible (verde o azul), y posteriormente resolver el sistema resultante con solo dos colores ($g$ y $b$).

    #### Fase A: Eliminar las $r$ luces del color minoritario (rojas)
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

    

    #### Fase B: Condicionar sobre el estado final tras la eliminación (Distribución Binomial)
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
      $$ \frac{ \binom{r}{i}  }{ 2^r} $$

      Sumamos los costos ponderados por la frecuencia de combinación sobre todos los escenarios $0 \le i \le r$:
      $$\sum_{i=0}^{r}  3 \cdot \min(g + i, \, b + r - i) \cdot  \binom{r}{i} \cdot\frac{1}{2^i}$$

    - **Valor esperado de la Fase B:**
      
      $$\mathbb{E}[\text{después de transformar}] =  \frac{1}{2^r} \sum_{i=0}^{r} \binom{r}{i} \cdot 3 \cdot \min(g + i, \, b + r - i)$$


    ---

    ### Respuesta Final
    Sumamos la esperanza de ambas fases independientes por linealidad:
    $$\text{Ans} = \text{transform\_all} + \mathbb{E}[\text{después de transformar}]$$
    
  
    ### Complexidad
    - **Tiempo:** $\mathcal{O}(R^2)  =\mathcal{O}(N^2)$ para precalcular el triángulo de Pascal de las combinatorias $\binom{r}{i}$ y $\mathcal{O}(R)$ para iterar la suma, donde $R = r \le 33$. 
    - **Espacio:** $\mathcal{O}(N^2)$ para la tabla de coeficientes binomiales.
  </details>



----


## Problema N: Did You See My Album?
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