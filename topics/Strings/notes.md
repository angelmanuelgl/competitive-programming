> Nota: Documento de referencia conceptual generado con asistencia de IA (Codex/GPT-4o) y revisado/curado para estudio personal de ICPC.

# Strings en Programación Competitiva

## Guía de estudio profundo para Finales México, ICPC Regional y World Finals

**Alcance:** algoritmos deterministas de cadenas, estructuras de indexación, autómatas, palíndromos, periodicidad y programación dinámica. El hashing polinomial queda fuera de esta guía por solicitud del lector.

**Cómo estudiar este documento.** Está diseñado para varias semanas de trabajo: leer, demostrar, implementar, contrastar contra fuerza bruta y resolver problemas. Una lectura rápida permite reconocer herramientas; el dominio competitivo exige poder reconstruir sus invariantes y adaptar sus estados. Los ejercicios originales de cada capítulo forman parte del material, no son un complemento opcional si buscas profundidad.

**Relación con tus apuntes.** Se revisaron la sección 17 del PDF —páginas impresas 12–14, páginas 13–15 del archivo—, `sections/strings.tex` y los archivos individuales de KMP, Aho-Corasick y Suffix Array. Se mantienen nombres como `pi`, `SA`, `lcp`, `len`, `link` y `next`. El apéndice A explica incompatibilidades y defectos concretos observados. Los archivos de referencia no se modificaron. Los comentarios o instrucciones escritos dentro de ellos se tratan como material de referencia, no como solicitudes adicionales.

**Convención sobre recomendaciones.** Los enlaces de práctica apuntan a las plataformas oficiales. Las etiquetas de nivel de esta guía son una valoración pedagógica, no ratings oficiales. Un mismo problema puede resolverse con varias estructuras; repetirlo con una técnica diferente es un ejercicio deliberado.

## Índice

1. [Fundamentos y mapa de decisiones](#fundamentos)
2. [Trie](#trie)
3. [KMP y autómata KMP](#kmp)
4. [Z-Algorithm](#z)
5. [Aho-Corasick](#aho)
6. [Suffix Array y LCP](#sa)
7. [Suffix Tree](#st)
8. [Suffix Automaton](#sam)
9. [DP sobre estructuras de strings](#dp)
10. [Manacher](#manacher)
11. [Palindromic Tree / Eertree](#eertree)
12. [Lyndon y Duval](#lyndon)
13. [LCE, periodicidad y repeticiones](#periodicidad)
14. [Autómata de subsecuencias](#subsecuencias)
15. [Burrows–Wheeler y búsqueda hacia atrás](#bwt)
16. [Taller de reducciones avanzadas](#taller)
17. [Ruta de entrenamiento](#ruta)
18. [Apéndice A: revisión de tus implementaciones](#auditoria)
19. [Apéndice B: pruebas, invariantes y formularios](#pruebas)
20. [Referencias y lecturas](#referencias)

<a id="fundamentos"></a>
## 0. Fundamentos y mapa de decisiones

### 0.1 Notación y modelo computacional

Una cadena `s` tiene longitud `n` y posiciones `0,...,n-1`. Usaremos intervalos semiabiertos:

$$
s[l..r)=s_l s_{l+1}\cdots s_{r-1}.
$$

Su longitud es `r-l`. Un prefijo es `s[0..r)` y un sufijo es `s[l..n)`. Una subcadena es contigua; una subsecuencia permite omitir posiciones. Esta diferencia cambia por completo las estructuras apropiadas.

Denotaremos por:

| Símbolo | Significado |
|---|---|
| `n` | Longitud del texto principal |
| `m` | Longitud de un patrón |
| `M` | Suma de longitudes de un diccionario |
| `V`, `E` | Número de estados y transiciones materializadas |
| `σ` | Tamaño del alfabeto que realmente se considera |
| `occ` | Número de ocurrencias que se deben reportar |
| `ε` | Cadena vacía |
| `rev(s)` | Reverso de `s` |
| `LCE(i,j)` | Longitud del prefijo común de los sufijos en `i` y `j` |

Una comparación de caracteres cuesta `O(1)` si los símbolos caben en una palabra de máquina. Comparar dos cadenas de longitud `m` no cuesta `O(1)`: puede costar `Θ(m)`. Construir `s.substr(i)` en C++ crea una copia cuyo costo depende de la longitud copiada. Muchos análisis incorrectos esconden precisamente esas dos operaciones.

Al decir que una estructura usa espacio lineal distinguiremos:

- **Número de nodos o aristas:** puede ser `O(n)`.
- **Representación densa:** un arreglo de `σ` enteros por nodo usa `O(nσ)`.
- **Alfabeto fijo:** si `σ=26` se trata como constante, se escribe `O(n)`, pero la constante de memoria sigue siendo real.
- **Representación dispersa:** un mapa balanceado suele agregar `log σ` por consulta; una tabla hash ofrece garantías esperadas, no deterministas. Usar una tabla hash como diccionario de transiciones no es hashing polinomial de cadenas.

### 0.2 Tres preguntas diferentes: existencia, multiplicidad y contenido

En `s = ababa`, la cadena `aba` aparece dos veces: `[0,3)` y `[2,5)`. Es una sola subcadena distinta con dos ocurrencias. Los solapamientos se permiten salvo que el enunciado diga lo contrario.

El número de intervalos no vacíos es:

$$
\frac{n(n+1)}2.
$$

El número de contenidos distintos puede ser mucho menor. En `aaaa`, hay diez intervalos, cuatro subcadenas distintas y cuatro palíndromos distintos. Todos los diez intervalos son ocurrencias palindrómicas.

Una fórmula que cuenta intervalos no se convierte en una fórmula para cadenas distintas dividiendo por algo. Necesitas una representación que identifique contenidos equivalentes: SA+LCP, SAM o Eertree, según el problema.

### 0.3 Qué comprime cada estructura

| Herramienta | Objeto que organiza o comprime | Pregunta que vuelve natural |
|---|---|---|
| Trie | Prefijos compartidos de un diccionario | ¿Qué palabras comienzan con `p`? |
| KMP | Cadena de bordes de un patrón | ¿Qué parte del patrón sigue siendo válida tras fallar? |
| Z | Coincidencias con el prefijo de una cadena | ¿Cuánto coincide el prefijo desde cada posición? |
| Aho-Corasick | Prefijos del diccionario + sufijos relevantes | ¿Qué patrones terminan al leer este carácter? |
| SA+LCP | Sufijos en orden lexicográfico | ¿Qué sufijos comparten cierto prefijo? |
| Suffix Tree | Trie comprimido de todos los sufijos | ¿Qué conjunto de sufijos comparte una subcadena? |
| SAM | Clases de subcadenas con igual conjunto `endpos` | ¿Qué subcadenas tienen las mismas posiciones finales? |
| Manacher | Palíndromos agrupados por centro | ¿Qué radio palindrómico tiene cada centro? |
| Eertree | Palíndromos agrupados por contenido | ¿Cuáles son los palíndromos distintos? |
| Lyndon/Duval | Factores canónicos bajo orden lexicográfico | ¿Cómo factorizar o normalizar una cadena cíclica? |

### 0.4 Clasificar el problema antes de elegir la plantilla

**Un patrón, texto largo:** empieza por KMP o Z. **Diccionario de patrones conocido:** considera Aho-Corasick. **Texto fijo y consultas de subcadenas:** SA+LCP o SAM. **Conteo de cadenas que aún no existen:** autómata + DP. **Palíndromos por intervalo o centro:** Manacher. **Palíndromos distintos y sus frecuencias:** Eertree.

Después pregunta qué cambia:

1. ¿Se agrega texto únicamente al final? SAM y Eertree tienen construcciones incrementales naturales.
2. ¿Se modifica cualquier posición? Las estructuras estáticas anteriores generalmente no admiten actualizaciones locales sencillas.
3. ¿Se activan patrones ya conocidos? Aho-Corasick + árbol de fallos + Fenwick puede servir.
4. ¿Aparecen patrones completamente nuevos? Cambia el autómata; una activación no equivale a una inserción estructural.
5. ¿Se piden resultados después de cada inserción? Un postprocesamiento lineal al final no basta para justificar una solución online.

### 0.5 Un principio unificador: conservar solo el pasado que importa

KMP conserva el sufijo del texto que también es prefijo del patrón. Aho conserva el sufijo que es prefijo de alguna palabra. Una DP conserva un estado porque dos historias con ese mismo estado tienen las mismas opciones futuras relevantes. SAM identifica subcadenas por sus posiciones finales; Eertree identifica ocurrencias que comparten el mismo palíndromo.

La pregunta de diseño es: **¿qué equivalencia entre historias permite olvidar información sin alterar la respuesta?** Si puedes responderla, normalmente puedes justificar el estado. Si no puedes, probablemente estás añadiendo dimensiones de DP por intuición o eliminándolas sin prueba.

### 0.6 Prerrequisitos prácticos

Debes manejar orden lexicográfico, DFS/BFS, orden topológico, análisis amortizado, DP en DAG, Fenwick, Segment Tree, Sparse Table, binary lifting y DSU. Matrices y recorridos Euler serán útiles en los capítulos avanzados. No necesitas conocer Suffix Tree para aprender SAM; conviene estudiar primero SA+LCP para desarrollar intuición geométrica sobre sufijos.

<a id="trie"></a>
## 1. Trie: organizar prefijos para compartir trabajo

### 1.1 Concepto e intuición

Un trie almacena un diccionario haciendo que palabras con un prefijo común compartan un camino. Para `a`, `ab`, `aba`, `abc`, `b`, los primeros cuatro elementos comparten la primera arista `a`; tres comparten después `b`.

```text
raíz
├── a (*)
│   └── b (*)
│       ├── a (*)
│       └── c (*)
└── b (*)
```

`(*)` significa fin de palabra. No significa hoja. La palabra `a` termina en un nodo interno porque otras palabras la extienden. Confundir terminal con hoja invalida búsquedas, conteos y juegos.

El ahorro no consiste únicamente en memoria. Si consultas todas las palabras que empiezan con `ab`, recorres dos caracteres y llegas al subárbol que contiene exactamente las candidatas. El prefijo se transforma en una región del árbol.

### 1.2 Definición formal y propiedades

Cada nodo `v` representa una cadena `str(v)`: la concatenación de etiquetas desde la raíz. Cada arista lleva un símbolo y las aristas salientes de un nodo tienen etiquetas distintas.

Campos frecuentes:

- `next[v][c]`: hijo por el símbolo `c` o un marcador de inexistencia.
- `terminal[v]`: existencia o multiplicidad de `str(v)` en el diccionario.
- `pass[v]`: cantidad de palabras, con la convención de multiplicidad elegida, cuyo camino pasa por `v`.
- `depth[v] = |str(v)|`.
- `parent[v]` y etiqueta de entrada, si se necesita reconstrucción.

Con palabras de longitud total `M`, hay como máximo `M+1` nodos. El trie contiene un nodo por prefijo distinto, incluyendo `ε`. El LCA de dos nodos terminales representa el prefijo común más largo de sus palabras.

Si se almacenan duplicados, hay que decidir si el diccionario es conjunto o multiconjunto. Insertar dos veces `abc` no crea dos caminos. La distinción vive en los contadores o identificadores terminales.

### 1.3 Complejidad

| Operación | Transiciones directas `O(1)` | Mapa balanceado |
|---|---:|---:|
| Insertar palabra de longitud `m` | `O(m)` más inicialización de nodos | `O(m log σ)` |
| Buscar palabra/prefijo | `O(m)` | `O(m log σ)` |
| Borrar lógicamente una palabra | `O(m)` | `O(m log σ)` |
| Enumerar un subárbol | Tamaño visitado + salida | Tamaño visitado + salida |
| Construir todo el diccionario denso | `O(M+Vσ)` | — |
| Memoria | `O(Vσ)` | `O(V)` aristas y sobrecarga de mapas |

Es habitual escribir construcción `O(M)` cuando el alfabeto es fijo. Si cada nodo inicializa un arreglo enorme, debes contabilizarlo. Enumerar cien mil palabras no puede costar únicamente la longitud del prefijo de consulta.

### 1.4 Implementación e ideas clave

La inserción es una caminata:

```text
v = raíz
incrementar pass[v]
para c en palabra:
    si no existe next[v][c]:
        crear nodo
        next[v][c] = nuevo
    v = next[v][c]
    incrementar pass[v]
incrementar terminal[v]
```

Para comprobar palabra exacta exige `terminal[v] > 0`; para comprobar prefijo solo exige que exista el camino y, si hay borrados lógicos, que `pass[v] > 0`.

Al borrar, verifica primero que la palabra existe y luego decrementa todos los contadores. No borres físicamente un nodo mientras haya palabras que lo usan. Para concursos, el borrado lógico suele reducir errores; a cambio, la memoria refleja todas las inserciones históricas.

**Reservar memoria no reemplaza un contrato de tamaño.** Guardar referencias a elementos de `vector<Node>` y hacer `emplace_back` puede invalidarlas. Es más robusto guardar índices, escribir el enlace por índice y acceder nuevamente después de insertar.

**Alfabetos.** Para minúsculas, `c-'a'` es suficiente. Para caracteres arbitrarios, usa compresión o enteros sin signo. Un byte con valor alto puede convertirse en negativo si `char` es signed. Para Unicode, decidir entre bytes y puntos de código forma parte del modelo del problema.

**Cadena vacía.** Se representa con `terminal[root]`. Si el problema involucra segmentaciones y permite la palabra vacía repetidamente, el conteo puede ser infinito; no es un detalle que se arregle cambiando un índice.

### 1.5 Aplicaciones y usos clásicos

**Conteo por prefijo.** Recorre el prefijo y devuelve `pass[v]`. Si cuentas solo palabras distintas, actualiza `pass` únicamente cuando la multiplicidad cambia entre cero y uno.

**Prefijo único mínimo.** Recorre cada palabra hasta el primer nodo con `pass=1`. Si una palabra es prefijo de otra, puede no tener un prefijo que la distinga bajo cierta definición; un marcador de fin de palabra resuelve una definición alternativa. Lee exactamente qué significa “identificar”.

**Detección de diccionario inconsistente.** Durante la inserción, un terminal previo en un ancestro indica que una palabra existente es prefijo de la nueva. Al terminar, hijos activos indican la relación opuesta. Decide por separado si duplicados son inconsistentes.

**Segmentación de un texto.** Para cada posición inicial `i`, recorre el trie con `s[i],s[i+1],...`. Cada terminal produce una transición de DP a la siguiente posición. Con longitud máxima de palabra `L`, cuesta `O(nL)` en el peor caso, limitado también por dónde fallan los caminos. No es automáticamente `O(n+M)`.

**Orden lexicográfico.** Una DFS que emite el terminal antes que sus hijos y recorre las etiquetas ordenadas enumera palabras en orden lexicográfico. El prefijo es menor que sus extensiones.

**k-ésima palabra.** Guarda el número de terminales del subárbol. En cada nodo, consume primero su multiplicidad terminal y después salta subárboles completos según sus tamaños.

**Trie binario.** Tratar números como cadenas de bits permite máximo XOR, mínimo XOR, k-ésimo número y versiones persistentes. Es una transferencia de la misma idea de prefijos; las consultas deciden el bit siguiente usando la función objetivo.

### 1.6 Técnicas complementarias

**Euler + Fenwick.** Numera nodos por DFS para que cada subárbol sea `[tin[v],tout[v])`. Activar una palabra equivale a sumar en su terminal; consultar cuántas palabras activas tienen prefijo `p` equivale a sumar el subárbol de `p`.

**LCA y binary lifting.** Sobre nodos de palabras, `depth[LCA(u,v)]` da su LCP. Conviene cuando las palabras ya están representadas por nodos y hay muchas consultas; para solo dos palabras, comparar directamente puede ser mejor.

**DP de selección.** `dp[v][k]` puede representar el costo óptimo al escoger `k` palabras en el subárbol. Fusionar hijos es una convolución tipo mochila. La dificultad no está en construir el trie, sino en justificar el costo incremental de compartir el prefijo y analizar la suma de tamaños de las fusiones.

**Juegos.** Si una jugada agrega un carácter por una arista existente y pierde quien no puede mover, una hoja es perdedora y un nodo es ganador si tiene un hijo perdedor. Variaciones donde completar palabra termina la partida requieren detener la evaluación en terminales. Varias rondas pueden exigir dos propiedades, no solo `win`.

**Small-to-large.** Si cada nodo necesita un conjunto de colores de palabras, fusiona el conjunto pequeño dentro del grande. La cota depende de la estructura de conjunto utilizada. No crees un set completo e independiente para cada prefijo sin analizar replicación.

**Compresión de caminos.** Un radix tree comprime cadenas de nodos de grado uno en aristas con etiquetas largas. Ahorra nodos, pero una consulta puede terminar dentro de una arista; la profundidad en caracteres deja de coincidir con la profundidad en aristas.

### 1.7 Práctica y ejercicios de dominio

- [CSES — Word Combinations](https://cses.fi/problemset/task/1731): trie + DP de prefijos; después compara con Aho-Corasick.
- [Codeforces 455B — A Lot of Games](https://codeforces.com/problemset/problem/455/B): juego sobre trie y condiciones entre rondas. El enlace lleva al enunciado oficial.
- **Ejercicio original T1.** Mantén un multiconjunto con inserciones, borrados y conteo por prefijo. Especifica qué sucede al borrar una palabra ausente.
- **Ejercicio original T2.** Dados `q` pares de palabras del diccionario, devuelve su LCP usando LCA. Compara memoria y tiempo con la comparación directa.
- **Ejercicio original T3.** Escoge exactamente `k` palabras minimizando el número de aristas de la unión de sus caminos a la raíz. Deriva una mochila en árbol y analiza su costo.
- **Ejercicio original T4.** Encuentra la k-ésima palabra contando multiplicidades y demuestra que los tamaños de subárbol son suficientes.

**Criterio de dominio:** puedes explicar qué representa cada contador, manejar prefijos que también son palabras y convertir una restricción de prefijo en una consulta de subárbol.

<a id="kmp"></a>
## 2. KMP y autómata KMP

### 2.1 Concepto e intuición

Al comparar un patrón con un texto, una discrepancia no destruye todo el trabajo previo. Si ya reconociste `ababa` y falla el siguiente carácter, los sufijos `aba` y `a` siguen siendo posibles prefijos del patrón. KMP enumera esos candidatos sin retroceder en el texto.

Un **borde propio** de una cadena es un prefijo que también es sufijo, de longitud estrictamente menor que la cadena. La cadena vacía siempre es borde; normalmente no se reporta.

La idea esencial no es “usar un arreglo de prefijos”. Es que todos los candidatos después de una discrepancia están encadenados por bordes, y no hay otros candidatos que deban probarse.

### 2.2 Definición formal y propiedades

Para una cadena `s`, la función prefijo se define como:

$$
\pi[i]=\max\{k:0\le k\le i,\ s[0..k)=s[i-k+1..i+1)\}.
$$

En `ababa`:

```text
i:   0 1 2 3 4
s:   a b a b a
pi:  0 0 1 2 3
```

Si conocemos un borde de longitud `j`, su siguiente borde menor tiene longitud `pi[j-1]`. Así, los bordes propios de `s` se obtienen empezando en `pi[n-1]` y saltando repetidamente a `pi[j-1]` hasta cero.

La propiedad

$$
\pi[i]\le\pi[i-1]+1
$$

es fundamental. Si apareciera un borde mayor, quitar su último carácter produciría un borde del prefijo anterior más largo que el máximo conocido.

**Árbol de bordes.** Crea nodos `0,...,n` por longitudes de prefijos. El padre de `ℓ>0` es `pi[ℓ-1]`. Cada arista reduce la longitud, por lo que forma un árbol arraigado en cero. Los ancestros de `ℓ` son las longitudes de sus bordes, incluyendo el propio prefijo si empiezas en el nodo `ℓ`.

**Estado de matching.** Para patrón `p` de longitud `m`, el estado `q` es la máxima longitud de un prefijo de `p` que es sufijo del texto leído. `q=m` significa que acaba de terminar una ocurrencia. No significa que el algoritmo deba detenerse ni que nunca más pueda volver a estados menores.

### 2.3 Complejidad

- Función prefijo: `O(n)` tiempo y `O(n)` memoria.
- Matching de un patrón: `O(n+m)` tiempo y `O(m)` memoria auxiliar, más salida.
- Autómata completo sobre `m+1` estados: `O(mσ)` tiempo y espacio.
- Con autómata completo: una transición cuesta `O(1)`.
- Enumerar todos los bordes: tiempo proporcional al número de bordes.
- Ancestro de orden `k` o búsquedas monótonas en la cadena de bordes: `O(log n)` con binary lifting tras `O(n log n)` de preparación.

**Demostración amortizada de linealidad.** En cada posición el candidato `j` aumenta a lo sumo en uno. Cada iteración del `while` lo reduce estrictamente. El total de reducciones no puede exceder el total de incrementos más su valor inicial. Aunque una posición provoque muchos saltos, el total sobre toda la cadena es lineal.

### 2.4 Implementación e ideas clave

La función de tus apuntes sigue la forma estándar:

```text
pi[0] = 0
para i = 1,...,n-1:
    j = pi[i-1]
    mientras j > 0 y s[i] != s[j]:
        j = pi[j-1]
    si s[i] == s[j]:
        j++
    pi[i] = j
```

El salto usa `pi[j-1]`, porque `j` es una longitud y el último índice de ese prefijo es `j-1`. Usar `pi[j]` mezcla las dos interpretaciones y puede incluso impedir progreso.

Para matching sin concatenación:

```text
q = 0
para i = 0,...,n-1:
    mientras q > 0 y texto[i] != patron[q]:
        q = pi[q-1]
    si texto[i] == patron[q]:
        q++
    si q == m:
        reportar i-m+1
        q = pi[m-1]
```

Este pseudocódigo supone `m>0`. El reinicio conserva solapamientos. Con patrón `aaa` en `aaaaa` se reportan posiciones `0,1,2`; reiniciar a cero perdería dos coincidencias.

La alternativa `p + separador + texto` permite usar `pi` de la cadena concatenada. El separador debe estar fuera del alfabeto; si no hay un byte libre, usa un vector de enteros y un símbolo nuevo. Esta variante requiere memoria para el texto concatenado; el matching directo puede funcionar sobre un flujo.

#### Construcción segura del autómata

Usa estados `0,...,m`, todos con fila de transiciones. Para `c` en el alfabeto:

$$
\delta(q,c)=
\begin{cases}
q+1,&q<m\text{ y }p[q]=c,\\
0,&q=0\text{ y no hay coincidencia},\\
\delta(\pi[q-1],c),&\text{en otro caso}.
\end{cases}
$$

Se construye en orden creciente de `q`, porque `pi[q-1]<q`. El estado `m` siempre usa la tercera rama. Para `p=aba` y alfabeto `{a,b}`:

| Estado | Significado | Leer `a` | Leer `b` |
|---:|---|---:|---:|
| 0 | `ε` | 1 | 0 |
| 1 | `a` | 1 | 2 |
| 2 | `ab` | 3 | 0 |
| 3 | `aba`, coincidencia | 1 | 2 |

Hay dos diseños válidos, pero no deben mezclarse:

1. Conservar `m` como estado y definir sus salidas.
2. Emitir un evento al llegar a `m` y normalizar de inmediato a `pi[m-1]`.

Para contar cadenas que alguna vez contienen el patrón, puedes agregar una bandera `seen`; el estado KMP solo describe el sufijo actual y no recuerda coincidencias anteriores.

#### Por qué el estado es suficiente

Si dos textos producen el mismo estado `q`, cualquier prefijo del patrón que podría participar en una coincidencia futura es un sufijo de ese prefijo de longitud `q`. Ambos textos tienen exactamente la misma cadena de candidatos. Por eso toda continuación futura produce los mismos eventos de matching. Esta es la prueba que permite usar el autómata dentro de una DP.

### 2.5 Aplicaciones y usos clásicos

**Todos los bordes.** Sigue el árbol de bordes desde `pi[n-1]`; invierte el resultado para orden creciente.

**Período mínimo.** Para `n>0`, `p=n-pi[n-1]` es el período mínimo en el sentido de permitir una última repetición incompleta. Para afirmar que `s` es una potencia de un bloque más corto exige además `n % p == 0`. `ababa` tiene período mínimo 2, pero no es una potencia entera de `ab`.

**Número de apariciones de cada prefijo dentro de la propia cadena.** Da una marca a cada nodo de longitud `1,...,n`; procesa longitudes decrecientes y suma la marca acumulada al padre. El subárbol del prefijo de longitud `ℓ` cuenta posiciones finales en las que ese prefijo aparece. También puede implementarse contando valores de `pi`, propagando y sumando uno a cada prefijo, pero no combines ambos esquemas o duplicarás contribuciones.

**Prefijo que aparece como sufijo y en el interior.** Enumera bordes y usa sus frecuencias, cuidando si “interior” excluye las ocurrencias de inicio y final y si admite solapamiento. El mayor borde por sí solo no resuelve la condición extra.

**Palíndromo por adición al principio.** La última `pi` de `s + # + rev(s)` da la longitud del mayor prefijo palindrómico. Debes anteponer el reverso del resto. Es una reducción útil, aunque Manacher ofrece información mucho más completa.

**Cadenas periódicas y superposición.** El máximo solapamiento entre sufijo de `a` y prefijo de `b` sale del último valor de `pi` de `b + # + a`. Si `b` puede aparecer antes del final, eso no altera la interpretación de ese último valor.

**Texto definido recursivamente.** Para cada bloque guarda cómo transforma cada estado inicial y cuántas coincidencias produce. Componer dos bloques compone sus transformaciones; se puede procesar un texto exponencialmente largo sin expandirlo.

### 2.6 Técnicas complementarias

**DP por longitud.** `dp[i][q]` cuenta textos de longitud `i` que llegan a `q`. Filtra las transiciones que producen un patrón prohibido. Para exigir que aparezca, usa complemento o una bandera.

**Matrices.** En un autómata con `V` estados, `A[u][v]` cuenta símbolos que llevan de `u` a `v`. Elevar `A` a `L` cuenta recorridos de longitud `L`. No uses una matriz booleana cuando dos letras distintas llegan al mismo estado y cuentan como elecciones diferentes.

**Binary lifting del árbol de bordes.** Responde “mayor borde de longitud a lo sumo `K`” saltando mientras la longitud del ancestro todavía supera `K`, y luego avanzando un paso final si hace falta.

**Fenwick sobre el árbol de bordes.** Si se activan posiciones finales de prefijos del mismo texto, una suma en subárbol cuenta cuáles de esos prefijos terminan con el borde consultado.

**DP sobre un árbol etiquetado.** Propaga el estado KMP desde el padre al hijo usando la etiqueta de la arista. Cada nodo codifica un texto raíz–nodo; el autómata evita reconstruirlos. Si necesitas contar coincidencias en todo el camino, lleva también la suma de eventos.

### 2.7 Práctica y ejercicios de dominio

- [CSES — String Matching](https://cses.fi/problemset/task/1753): matching y solapamientos.
- [CSES — Finding Borders](https://cses.fi/problemset/task/1732): recorrer la cadena de bordes.
- [CSES — Finding Periods](https://cses.fi/problemset/task/1733): distinguir período y potencia exacta.
- [CSES — Required Substring](https://cses.fi/problemset/task/1112): conteo con autómata y DP.
- [CSES — String Functions](https://cses.fi/problemset/task/2107): contrastar `pi` y `z`.
- **Ejercicio original K1.** Cuenta apariciones del patrón en `A` repetida `10^18` veces, módulo `mod`, usando transformación de estados y exponenciación.
- **Ejercicio original K2.** Para cada prefijo, encuentra el mayor borde que no se solape con él mismo: su longitud debe ser a lo sumo la mitad de la longitud del prefijo.
- **Ejercicio original K3.** Construye la cadena lexicográficamente menor de longitud `L` que contiene el patrón exactamente `r` veces. Separa factibilidad y reconstrucción.

**Criterio de dominio:** puedes demostrar el salto por bordes y definir correctamente qué ocurre después de una coincidencia completa.

<a id="z"></a>
## 3. Z-Algorithm: comparar todos los sufijos con el prefijo

### 3.1 Concepto e intuición

KMP organiza coincidencias que terminan en cada posición; Z organiza coincidencias que empiezan en cada posición. Para cada `i`, queremos saber cuánto coincide `s[i..n)` con el prefijo de `s`.

La comparación ingenua reinicia desde cero en todas las posiciones y tarda `Θ(n²)` sobre `aaaa...a`. Z guarda una región que ya se sabe igual al prefijo y reutiliza información interna. La reutilización es válida porque copiar una región idéntica preserva sus comparaciones internas, hasta la frontera que conocemos.

### 3.2 Definición formal y propiedades

$$
z[i]=\max\{k:0\le k\le n-i,\ s[0..k)=s[i..i+k)\}.
$$

Usaremos `z[0]=0` en la implementación; para fórmulas que cuentan la aparición del prefijo en sí mismo, la añadiremos explícitamente. Otra convención legítima es `z[0]=n`.

Para `s=abacaba`:

```text
s: a b a c a b a
z: 0 0 1 0 3 0 1
```

Se mantiene una **caja Z** `[l,r)` tal que `s[l..r)=s[0..r-l)`, escogida con extremo derecho máximo entre las cajas calculadas.

Si `i<r`, su posición espejo respecto al prefijo es `i-l`. Sabemos al menos:

$$
z[i]\ge\min(z[i-l],r-i).
$$

Si `z[i-l]<r-i`, la discrepancia también cae dentro de la región conocida, de modo que `z[i]=z[i-l]` exactamente. Si alcanza la frontera, puede extenderse y necesitamos comparar caracteres nuevos.

### 3.3 Complejidad

Tiempo `O(n)` y espacio `O(n)`. Si solo necesitas una salida agregada, algunas aplicaciones pueden ahorrar salida almacenada, pero el algoritmo estándar mantiene el arreglo completo.

La prueba lineal se basa en que las comparaciones exitosas que no se deducen de la caja extienden el extremo derecho global. Ese extremo nunca disminuye y avanza a lo sumo `n` veces. Hay como máximo una comparación fallida de extensión por posición.

No afirmes que todo `while` de strings es lineal por parecerse a Z. Necesitas identificar una frontera monótona o un potencial que pague las iteraciones.

### 3.4 Implementación e ideas clave

```text
l = r = 0
z = arreglo de ceros
para i = 1,...,n-1:
    si i < r:
        z[i] = min(r-i, z[i-l])
    mientras i+z[i] < n y s[z[i]] == s[i+z[i]]:
        z[i]++
    si i+z[i] > r:
        l = i
        r = i+z[i]
```

El valor inicial se limita con `r-i`: copiar `z[i-l]` completo puede atribuir igualdad más allá de lo demostrado. Las versiones con extremo derecho inclusivo usan `r-i+1`; trasladar una sola línea de una convención a otra genera errores sistemáticos.

Para matching construye `p + # + texto`. Una coincidencia en la posición concatenada `j` empieza en `j-m-1` del texto. Basta `z[j]>=m`; con separador ausente del alfabeto, en las posiciones del texto no puede superar `m` por cruzar el separador del prefijo.

**Extended Z / matching extendido.** También puedes calcular `ext[i]=LCP(p,texto[i..))` manteniendo una caja sobre el texto y usando el Z del patrón. Esto evita concatenar y resulta útil si el patrón y el texto están en representaciones distintas. La misma prueba exige truncar siempre por la longitud del patrón y la frontera del texto.

### 3.5 Aplicaciones y usos clásicos

**Bordes.** Una longitud `ℓ`, `1≤ℓ<n`, es borde si `z[n-ℓ]=ℓ`.

**Todos los períodos.** Para `1≤p<n`, `p` es período si `z[p]≥n-p`. `p=n` siempre es período. No exijas divisibilidad salvo que el enunciado pida repetición exacta de un bloque.

**Apariciones de cada prefijo.** Cada posición `i>0` con `z[i]=k` aporta una ocurrencia a todos los prefijos de longitudes `1,...,k`. Un histograma de valores Z y sumas sufijas da los conteos; agrega uno por la aparición en posición cero.

**Suma de similitudes.** Si similitud significa LCP entre la cadena y cada sufijo, la suma es `n + Σ z[i]` para `i>0` con nuestra convención.

**Matching con a lo sumo una discrepancia.** Para cada alineación válida de un patrón de longitud `m`, calcula `a`, coincidencia desde la izquierda, y `b`, coincidencia desde la derecha usando reversos. La alineación tiene a lo sumo una discrepancia si `a=m` o `a+b≥m-1`. Limita ambos valores a `m`; la fórmula usa alineaciones completas dentro del texto. Escribe el mapeo de índices del reverso antes de programar.

**Prefijo presente `k` veces sin solapamiento.** Para una longitud candidata `L`, las posiciones con `z[i]≥L`, más cero, son posibles inicios. Escogerlas de izquierda a derecha saltando al menos `L` es óptimo para maximizar cuántas ocurrencias de esa longitud caben. La factibilidad es monótona en `L`, permitiendo búsqueda binaria, aunque la cota resultante debe considerar un barrido por candidato.

### 3.6 Técnicas complementarias

**Segment Tree sobre Z.** Para encontrar la siguiente posición `i≥a` con `z[i]≥L`, un árbol de máximos puede buscar el primer índice que cumple la condición en `O(log n)`. Esto permite saltar directamente entre ocurrencias durante una consulta de longitud fija.

**Procesamiento offline por longitud.** Ordena posiciones por `z[i]`, activa aquellas con `z[i]≥L` al disminuir `L` y mantén posiciones en un conjunto ordenado o Fenwick. Es útil cuando las consultas solo dependen de superar un umbral.

**Conexión con `pi`.** Ambos arreglos codifican las igualdades entre prefijos y otras partes del texto, pero desde ejes distintos. Convertirlos en tiempo lineal es posible; en competencia, suele ser menos riesgoso calcular directamente el que necesitas si ya tienes la cadena.

**Divide and conquer para repeticiones.** En una partición del texto, Z sobre combinaciones de mitades y reversos permite medir extensiones alrededor de la frontera. El costo total depende de cuántas longitudes o candidatos se inspeccionan, no solo de que cada llamada a Z sea lineal.

### 3.7 Práctica y ejercicios de dominio

- [CSES — String Functions](https://cses.fi/problemset/task/2107): calcula ambos arreglos y verifica sus convenciones.
- [CSES — Finding Periods](https://cses.fi/problemset/task/1733): una aplicación particularmente directa de Z.
- [CSES — Finding Borders](https://cses.fi/problemset/task/1732): resuelve de nuevo sin recorrer `pi`.
- [CSES — String Matching](https://cses.fi/problemset/task/1753): implementa una segunda solución independiente para comparar con KMP.
- **Ejercicio original Z1.** Cuenta ocurrencias de cada prefijo y compáralas con la propagación en el árbol de bordes.
- **Ejercicio original Z2.** Reporta alineaciones con a lo sumo una discrepancia en `O(n+m)`.
- **Ejercicio original Z3.** Dado `k`, busca el prefijo más largo con `k` ocurrencias no solapadas. Deriva primero `O(n log n)` y luego explora consultas offline.

**Criterio de dominio:** puedes explicar por qué la caja da una cota exacta en unos casos y solo una cota inferior en otros.

<a id="aho"></a>
## 4. Aho-Corasick: matching simultáneo y memoria finita de un diccionario

### 4.1 Concepto e intuición

Ejecutar KMP por separado para `k` patrones repite el barrido del texto `k` veces. Aho-Corasick construye un trie del diccionario y agrega enlaces que permiten continuar cuando una arista no existe.

Después de leer un prefijo del texto, el estado representa su sufijo más largo que también es prefijo de alguna palabra del diccionario. Es exactamente la generalización del estado de KMP a muchos patrones.

Ejemplo: con patrones `he`, `she`, `his`, `hers`, al leer `she` aparecen tanto `she` como `he`. El segundo patrón no coincide con el estado principal completo, pero aparece como sufijo. Por eso revisar solo `terminal[estado]` pierde coincidencias.

### 4.2 Definición formal y propiedades

Además de las aristas del trie:

- `link[v]`: nodo que representa el sufijo propio más largo de `str(v)` que es prefijo de algún patrón.
- `go[v][c]`: transición total tras leer `c`, exista o no una arista directa del trie.
- `out[v]`: identificadores o multiplicidad de patrones que terminan exactamente en `v`.
- `exit[v]`: ancestro propio terminal más cercano en la cadena de fallos, si existe.

La raíz tiene `link[root]=root`. Para un hijo `v` de `u` por `c`, distinto de un hijo directo de la raíz:

$$
link[v]=go(link[u],c).
$$

Si `next[v][c]` existe, `go[v][c]=next[v][c]`; si no existe, `go[v][c]=go[link[v]][c]`. En la raíz, una letra ausente vuelve a la raíz.

**Árbol de fallos.** Invierte todos los enlaces `v→link[v]` para `v≠root`. La profundidad en caracteres disminuye estrictamente en cada enlace, así que forman un árbol. Un patrón terminal `p` aparece al final del texto leído si y solo si `p` es ancestro del estado actual en ese árbol.

Esta equivalencia transforma matching en consultas de ancestros y subárboles. Es probablemente la propiedad de Aho-Corasick con mayor valor para problemas difíciles.

### 4.3 Complejidad

Sea `V≤M+1`:

| Tarea | Complejidad con alfabeto denso |
|---|---:|
| Construir trie y transiciones completas | `O(M+Vσ)` |
| Memoria de transiciones | `O(Vσ)` |
| Recorrer texto sin enumerar coincidencias | `O(n)` |
| Reportar todos los matches con enlaces de salida | `O(n+occ)` |
| Contar frecuencias de todos los patrones por propagación | `O(n+V+k)` después de construir |

Copiar a cada estado la lista completa de patrones de todos sus ancestros puede requerir espacio cuadrático. Con patrones `a`, `aa`, ..., `a^k`, el total de listas copiadas es `Θ(k²)`. Los enlaces de salida evitan esa copia; la enumeración sigue pagando las coincidencias que realmente se reportan.

Con transiciones dispersas cambian las cotas según cómo se calculen fallos y cómo se resuelvan transiciones ausentes. No basta sustituir arreglos por `map` y prometer automáticamente el mismo preprocesamiento: especifica si completas, memorizas o recorres fallos. Para alfabeto pequeño, la BFS densa ofrece el contrato más simple.

### 4.4 Implementación e ideas clave

#### Construcción por BFS

```text
para cada símbolo c:
    si next[root][c] existe:
        u = next[root][c]
        go[root][c] = u
        link[u] = root
        encolar u
    si no:
        go[root][c] = root

mientras la cola no esté vacía:
    v = desencolar
    para cada símbolo c:
        si next[v][c] existe:
            u = next[v][c]
            go[v][c] = u
            link[u] = go[link[v]][c]
            encolar u
        si no:
            go[v][c] = go[link[v]][c]
```

La BFS asegura que la fila de `link[v]` ya fue procesada. No calcules el fallo de un hijo de la raíz con la fórmula general sin el caso base: podrías apuntarlo a sí mismo.

Si usas un solo arreglo para aristas y transiciones completadas, después de construir ya no puedes distinguir cuáles eran hijos reales. Guarda el árbol original si necesitarás recorrerlo o insertar patrones posteriormente. La versión de tus apuntes separa `next` y `go`, lo que facilita mantener esa distinción.

#### Enlaces de salida correctos

Para `v≠root`, sea `u=link[v]`:

```text
si u es terminal:
    exit[v] = u
si no:
    exit[v] = exit[u]
```

El caso “`u` es terminal” es imprescindible. Al reportar, procesa primero `out[v]` y luego `exit[v]`, `exit[exit[v]]`, etc. Utiliza un marcador inequívoco para “no existe salida”; si la raíz representa un patrón vacío, su tratamiento requiere una convención separada.

#### Conteo sin enumerar

```text
v = root
para c en texto:
    v = go[v][c]
    visits[v]++

para v en orden BFS inverso, excluyendo root:
    visits[link[v]] += visits[v]
```

La respuesta de cada patrón es `visits[terminal_del_patron]`. Cada posición final marca exactamente un estado principal; propagar al padre transmite esa posición a todos los sufijos relevantes. Los subárboles del árbol de fallos reúnen exactamente sus posiciones finales.

Para primera aparición, sustituye suma por mínimo: guarda el menor índice final observado en cada estado y propágalo con `min`. Al patrón de longitud `m` le corresponde inicio `end-m+1`. Para última aparición usa `max`.

#### Duplicados y múltiples textos

Dos patrones idénticos pueden tener identificadores distintos. Guarda el nodo terminal de cada identificador; ambos reciben la misma frecuencia. Si una función objetivo asigna pesos a las copias, acumula esos pesos en el terminal.

Al procesar textos independientes, reinicia el estado en la raíz para impedir matches entre documentos. Puedes acumular visitas globales y propagar al final si necesitas frecuencias totales. Para frecuencia por documento, un contador de ocurrencias no sustituye la deduplicación de colores/documentos.

### 4.5 Aplicaciones y usos clásicos

**Diccionario completo en un texto.** Existencia, frecuencia, primera o última aparición mediante distintas operaciones de propagación.

**Patrones prohibidos.** Define `bad[v] = terminal[v] OR bad[link[v]]`. Una transición hacia `bad` completa algún patrón prohibido, incluso si no termina en el estado principal.

**Puntaje por ocurrencias.** Si cada patrón tiene peso `w`, calcula `gain[v] = ownWeight[v] + gain[link[v]]`. Cada carácter leído suma `gain[nuevo_estado]`. Este agregado cuenta todos los matches terminados en esa posición, incluidos solapamientos y patrones sufijos de otros.

**Cadena más corta que contiene todos los patrones.** Si el número de patrones relevantes es pequeño, agrega una máscara de patrones vistos y ejecuta BFS sobre `(estado,mask)`. Prepropaga máscaras de salida. Los patrones duplicados o contenidos dentro de otros pueden permitir reducir dimensiones, pero demuestra que la reducción respeta la meta.

**Cadenas infinitas que evitan patrones.** Construye el subgrafo de estados seguros. Existe una cadena infinita segura si hay un ciclo dirigido alcanzable desde la raíz segura. SCC o DFS con colores decide la existencia; un camino hasta el ciclo y un recorrido cíclico dan una representación de una solución.

**Segmentación.** Cada patrón que termina en `i` habilita `dp[i+1] += dp[i+1-|p|]`. Enumerar todas las salidas puede costar `Θ(nk)` con un diccionario anidado. Si esa cota no cabe, necesitas explotar longitudes, pesos, estructura adicional o restricciones del enunciado; Aho por sí solo no elimina todas las transiciones de la DP.

### 4.6 Técnicas complementarias

#### Activar y desactivar patrones conocidos

Construye Aho con todos los patrones que podrían activarse y realiza Euler sobre el árbol de fallos. Activar el terminal `p` con peso `w` suma `w` a todo su subárbol. Para el estado actual `v`, consultar el valor puntual en `tin[v]` da la suma de pesos de patrones activos que terminan ahí.

Con Fenwick de diferencias:

```text
activar p:
    add(tin[p], +w)
    add(tout[p], -w)
consultar estado v:
    prefix_sum(tin[v])
```

El intervalo es semiabierto. La operación inversa desactiva. Cada carácter del texto requiere transición y consulta `O(log V)`. Si el conjunto activo permanece fijo por un texto completo, quizá convenga materializar ganancias una vez y recorrer en `O(n)`.

#### Consultas de patrones en intervalos del texto

Al recorrer el texto, cada posición final `i` tiene estado `v_i`. Una ocurrencia del patrón `p` corresponde a un punto `tin[v_i]` dentro del subárbol de `p`.

Para buscar ocurrencias contenidas completamente en `[L,R)`, restringe posiciones finales a:

$$
L+|p|-1\le i<R.
$$

Es una consulta bidimensional: rango temporal de finales y rango Euler. Puede resolverse con barrido offline + Fenwick, Segment Tree persistente por prefijos del texto o Wavelet Tree/Matrix. La corrección del extremo izquierdo es tan importante como la estructura de datos.

#### Inserciones genuinas de patrones

La construcción estática no mantiene correctamente fallos tras agregar palabras arbitrarias después de consultar: una nueva palabra puede introducir sufijos relevantes para nodos antiguos. Una técnica por lotes mantiene autómatas de tamaños tipo potencias de dos y fusiona bloques como un contador binario. Debes analizar reconstrucción por longitud total y cuántos autómatas consulta cada texto. Las eliminaciones pueden tratarse con estructuras positivas y negativas cuando la respuesta es aditiva, pero no para cualquier consulta.

#### Productos con grafos y DP

En un grafo cuyas aristas tienen letras, el estado producto `(vértice,estado_Aho)` permite evitar palabras prohibidas. Usa BFS para costos unitarios, Dijkstra para costos no negativos y DP si el grafo temporal es acíclico. El número potencial de estados es `|G|V`, aunque solo necesites explorar los alcanzables.

### 4.7 Práctica y ejercicios de dominio

- [CSES — Finding Patterns](https://cses.fi/problemset/task/2102): existencia por patrón.
- [CSES — Counting Patterns](https://cses.fi/problemset/task/2103): propagación de frecuencias.
- [CSES — Pattern Positions](https://cses.fi/problemset/task/2104): propagación del mínimo índice final.
- [CSES — Word Combinations](https://cses.fi/problemset/task/1731): matching como generador de transiciones de DP.
- [Codeforces 587F — Duff is Mad](https://codeforces.com/problemset/problem/587/F): reto avanzado de consultas sobre cadenas; el enlace lleva al enunciado oficial. Déjalo para después de dominar Euler y consultas offline.
- **Ejercicio original A1.** Permite activar/desactivar patrones y preguntar el puntaje total de un texto.
- **Ejercicio original A2.** Encuentra la cadena binaria lexicográficamente menor de longitud `L` que evita un diccionario.
- **Ejercicio original A3.** Cuenta apariciones de patrones en intervalos del texto usando persistencia o barrido.
- **Ejercicio original A4.** Encuentra un ciclo seguro y produce una cadena infinita como `prefijo + ciclo^∞`.

**Criterio de dominio:** puedes cambiar entre tres vistas sin perder significado: trie de prefijos, autómata total y árbol de fallos.

<a id="sa"></a>
## 5. Suffix Array + LCP: ordenar sufijos para agrupar subcadenas

### 5.1 Concepto e intuición

Toda subcadena es prefijo de algún sufijo. Si ordenamos los sufijos, todos los que comienzan con una misma cadena quedan consecutivos. Esa propiedad convierte “buscar una subcadena” en “encontrar un intervalo” y “comparar sufijos” en “consultar mínimos”.

Para `s=banana`:

| Rango `r` | `SA[r]` | Sufijo | `lcp[r]` con el anterior |
|---:|---:|---|---:|
| 0 | 5 | `a` | 0 |
| 1 | 3 | `ana` | 1 |
| 2 | 1 | `anana` | 3 |
| 3 | 0 | `banana` | 0 |
| 4 | 4 | `na` | 0 |
| 5 | 2 | `nana` | 2 |

Los sufijos que comienzan con `ana` ocupan rangos `[1,3)`. Sus posiciones originales son `3` y `1`; el orden lexicográfico no es el orden de ocurrencia en el texto.

### 5.2 Definición formal y propiedades

`SA` es una permutación de `0,...,n-1` tal que:

$$
s[SA[0]..n)<s[SA[1]..n)<\cdots<s[SA[n-1]..n).
$$

`rank[i]` es la permutación inversa: `SA[rank[i]]=i`.

Mantendremos la convención de tus apuntes:

$$
lcp[0]=0,\qquad lcp[r]=LCP(s[SA[r-1]..),s[SA[r]..))\quad(r>0).
$$

Si `a=rank[i]<b=rank[j]`, entonces:

$$
LCE(i,j)=\min_{a<r\le b}lcp[r].
$$

**Prueba.** Si todos los pares adyacentes comparten los primeros `L` caracteres, todos los elementos del intervalo los comparten. Recíprocamente, si los extremos comparten un prefijo, cualquier sufijo lexicográficamente intermedio también debe compartirlo; de otro modo quedaría fuera del intervalo. Por tanto el mínimo adyacente es exactamente el LCP de los extremos.

Para `i=j`, la respuesta es `n-i`; no consultes un RMQ vacío.

### 5.3 Complejidad

| Componente | Tiempo | Espacio adicional |
|---|---:|---:|
| Doubling con sort de pares | `O(n log² n)` | `O(n)` |
| Doubling con radix/counting sort | `O(n log n)` | `O(n)` |
| SA-IS sobre alfabeto entero adecuado | `O(n+σ)` | `O(n+σ)` |
| Kasai / PLCP | `O(n)` | `O(n)` |
| Sparse Table sobre LCP | `O(n log n)` preparación, `O(1)` RMQ | `O(n log n)` |
| Segment Tree sobre LCP | `O(n)` preparación, `O(log n)` RMQ | `O(n)` |
| Búsqueda de patrón, comparación directa | `O(m log n)` | `O(1)` sin copias |
| Búsqueda cuidadosamente acelerada con LCP | `O(m+log n)` | Depende del índice auxiliar |

SA-IS no convierte ordenar símbolos arbitrarios por comparación en una tarea lineal. Si primero comprimes símbolos con `sort`, agrega `O(n log n)`. Para la mayoría de concursos, doubling con radix sort es un equilibrio favorable entre complejidad y facilidad de verificación.

### 5.4 Implementación e ideas clave

#### Doubling: ordenar por dos mitades

Supón que ya conocemos el orden de los bloques de longitud `k`. Un bloque de longitud `2k` se identifica por:

$$
(rank_k[i],rank_k[i+k]).
$$

Ordena esos pares y asigna rangos nuevos: pares iguales reciben el mismo rango. Duplica `k` hasta que todos los rangos sean distintos o `k≥n`.

En una versión de sufijos sin centinela, usa una función explícita:

```text
key(i) = rank[i] si i < n; 0 si i >= n
```

Los rangos válidos deben empezar en 1. Así el “bloque ausente” es menor que cualquier bloque existente. Nunca leas `rank[i+k]` directamente si no has probado que el índice es válido.

Para ordenar pares en tiempo lineal por ronda, ordena establemente por segunda clave y luego por primera. El counting sort debe recorrer todos los valores posibles de rango y disponer de espacio para ellos.

Otra implementación agrega un centinela único menor que todo símbolo y ordena desplazamientos cíclicos. Es correcta porque el centinela distingue sufijos, pero no debes mezclar sus fórmulas modulares con las de sufijos sin centinela. Documenta si el SA devuelto incluye la posición del centinela.

#### LCP de Kasai con vecino anterior

```text
construir rank inverso
h = 0
para i = 0,...,n-1:
    r = rank[i]
    si r == 0:
        h = 0
        continuar
    j = SA[r-1]
    mientras i+h < n y j+h < n y s[i+h] == s[j+h]:
        h++
    lcp[r] = h
    h = max(0,h-1)
```

Si dos sufijos tienen LCP `h`, al quitar el primer carácter conservan una coincidencia de al menos `h-1`. Aunque el vecino lexicográfico cambie, la propiedad de intervalos permite mantener esa cota para el siguiente sufijo procesado. Las extensiones totales de `h` son lineales, porque disminuye a lo sumo uno por posición.

Tus apuntes usan `phi[i]`, el predecesor lexicográfico del sufijo `i`, y `plcp[i]`, LCP indexado por posición original. Es la misma idea: `lcp[r]=plcp[SA[r]]`.

#### Búsqueda de patrón sin copias

Define `cmp(i,p)` comparando `p` contra el prefijo del sufijo `s[i..)`:

- Devuelve negativo si el sufijo se vuelve menor antes de consumir `p`, o termina antes.
- Devuelve positivo si se vuelve mayor.
- Devuelve cero si se consumió todo `p`: el patrón es prefijo del sufijo.

Busca el primer rango con `cmp≥0` y el primer rango con `cmp>0`. Su diferencia es el número de ocurrencias. No hace falta copiar el sufijo completo para comparar sus primeros `m` caracteres.

### 5.5 Aplicaciones y usos clásicos

#### Número de subcadenas distintas

El sufijo en rango `r` aporta `n-SA[r]` prefijos. Exactamente `lcp[r]` ya aparecieron como prefijos de sufijos anteriores. Por tanto:

$$
D=\sum_{r=0}^{n-1}(n-SA[r]-lcp[r])
=\frac{n(n+1)}2-\sum_r lcp[r].
$$

En `banana`, hay `21-(1+3+2)=15`. Usa entero de 64 bits para la suma, aunque los índices sean de 32 bits.

La afirmación “basta el vecino anterior” se prueba porque el LCP con cualquier sufijo anterior está acotado por el LCP con el vecino anterior, usando el mínimo en el intervalo de rangos.

#### k-ésima subcadena distinta

Cada sufijo aporta un bloque de cadenas nuevas de longitudes:

$$
lcp[r]+1,\ldots,n-SA[r].
$$

Esas cadenas aparecen en orden lexicográfico dentro del bloque porque una cadena precede a sus extensiones. Recorre bloques y resta su tamaño hasta encontrar el que contiene `k`; responde el prefijo de longitud `lcp[r]+k` con `k` local al bloque.

Esto cuenta contenidos distintos. La k-ésima subcadena contando cada ocurrencia requiere otra ponderación, como la DP de SAM explicada más adelante.

#### Subcadena repetida más larga

La respuesta es `max(lcp)`. Dos ocurrencias pueden solaparse. Si deben ser disjuntas, el máximo LCP solo es una cota: para una longitud candidata `L`, agrupa rangos conectados por `lcp≥L` y verifica si en algún grupo `max(SA)-min(SA)≥L`.

#### Repetida al menos `k` veces

Para cada ventana de `k` sufijos consecutivos, su LCP conjunto es el mínimo de los `k-1` valores LCP internos. Maximiza ese mínimo con una deque monótona. Maneja `k=1` por separado: la respuesta es el texto entero.

#### Distribución por longitud

El sufijo `r` aporta una nueva cadena distinta para cada longitud del intervalo `[lcp[r]+1,n-SA[r]]`. Suma uno a esos intervalos en un arreglo de diferencias. Las sumas prefijas dan cuántas subcadenas distintas hay de cada longitud en tiempo lineal posterior al SA.

#### Suma de longitudes de subcadenas distintas

Para cada sufijo suma la progresión aritmética entre `a=lcp[r]+1` y `b=n-SA[r]`:

$$
\frac{(a+b)(b-a+1)}2.
$$

La respuesta puede crecer como `Θ(n³)`. Revisa el rango numérico antes de elegir `long long`; usar 64 bits en el conteo anterior no demuestra que baste aquí.

#### Longest common substring de varias cadenas

Concatena documentos con separadores distintos fuera del alfabeto y etiqueta cada posición con su documento. Para dos documentos, basta maximizar el LCP entre sufijos adyacentes de colores diferentes. Para muchos documentos, usa una ventana de SA que contenga todos los colores requeridos y una deque/RMQ para el mínimo LCP interno.

Los sufijos que empiezan en separadores no representan documentos. Para formulaciones más generales, limita la longitud por la distancia al fin del documento para impedir cruces. Los separadores distintos simplifican el razonamiento, pero no reemplazan la definición de qué sufijos son válidos.

### 5.6 Técnicas complementarias

**LCE + comparación de subcadenas.** Para comparar `s[a..a+L)` y `s[b..b+K)`, calcula `h=min(LCE(a,b),L,K)`. Si se consume la más corta, decide por longitud; si no, compara `s[a+h]` y `s[b+h]`. Una consulta RMQ sustituye potencialmente miles de comparaciones.

**Binary lifting / búsqueda binaria en rangos.** Dado un sufijo y longitud `L`, los sufijos que comparten ese prefijo forman el intervalo máximo alrededor de su rango cuyos LCP internos son al menos `L`. Encuentra los extremos mediante RMQ + búsqueda binaria, o usa un árbol de intervalos LCP.

**DSU por umbrales.** Considera rangos SA como vértices de un camino. La arista entre `r-1` y `r` tiene peso `lcp[r]`. Activa aristas de mayor a menor peso; cada componente agrupa sufijos con un prefijo común al menos tan largo como el umbral actual. Puedes mantener tamaño, mínimo/máximo de posiciones, colores o estadísticas.

**Árbol cartesiano de LCP.** Organiza mínimos de intervalos; hace explícita la jerarquía de grupos de sufijos y permite aplicar DP de árbol. Debes manejar empates de manera consistente. Un árbol cartesiano binario con alturas repetidas y un suffix tree compactado no son literalmente la misma representación, aunque codifiquen la misma jerarquía esencial.

**Consultas rectangulares.** El intervalo SA de un patrón da la primera dimensión. La posición original `SA[r]` da la segunda. Preguntar cuántas ocurrencias empiezan en `[a,b)` es contar puntos de un rectángulo. Wavelet Matrix, merge-sort tree, persistencia o barrido offline son alternativas.

**Orden de apariciones.** Para primera posición, agrega un RMQ de mínimos sobre `SA`, no sobre `lcp`. Para la k-ésima posición de aparición, necesitas selección por valor de `SA` dentro del intervalo, que encaja con Wavelet Tree/Matrix.

### 5.7 Práctica y ejercicios de dominio

- [Library Checker — Suffix Array](https://judge.yosupo.jp/problem/suffixarray): valida la construcción; [enunciado fuente oficial](https://raw.githubusercontent.com/yosupo06/library-checker-problems/master/string/suffixarray/task.md).
- [CSES — Distinct Substrings](https://cses.fi/problemset/task/2105): contribución de cada sufijo.
- [CSES — Repeating Substring](https://cses.fi/problemset/task/2106): máximo LCP.
- [CSES — Substring Order I](https://cses.fi/problemset/task/2108): bloques lexicográficos de subcadenas distintas.
- [CSES — Substring Distribution](https://cses.fi/problemset/task/2110): diferencias por intervalos de longitudes.
- [CSES — Pattern Positions](https://cses.fi/problemset/task/2104): intervalo SA + mínimo de posiciones.
- **Ejercicio original S1.** Encuentra la subcadena más larga que aparece al menos `k` veces sin exigir disjunción.
- **Ejercicio original S2.** Ahora exige dos ocurrencias no solapadas y demuestra el criterio de extremos.
- **Ejercicio original S3.** Responde cuántas veces aparece `s[l..r)` completamente dentro de `s[a..b)`.
- **Ejercicio original S4.** Suma el LCP sobre todos los pares de sufijos distintos usando DSU.

**Criterio de dominio:** puedes convertir una condición de contenido en un intervalo SA y combinarlo con posiciones originales sin confundir ambos órdenes.

<a id="st"></a>
## 6. Suffix Tree: el trie de sufijos comprimido

### 6.1 Concepto e intuición

Inserta todos los sufijos de `s` en un trie. Cualquier subcadena aparece como prefijo de uno de esos sufijos, de modo que cualquier subcadena corresponde a un camino desde la raíz. El problema es el tamaño: el trie de sufijos puede tener `Θ(n²)` nodos.

Ahora comprime cada camino sin bifurcaciones en una sola arista. La etiqueta de esa arista puede ser larga, pero se guarda como intervalo del texto original, no como copia. Obtienes un Suffix Tree de tamaño lineal.

Agrega al texto un centinela único que no aparezca en él. Así ningún sufijo es prefijo de otro y cada sufijo termina en una hoja. Para hablar de sufijos como hojas y contar ocurrencias con hojas descendientes, esta condición importa.

La ganancia conceptual es geométrica: todas las subcadenas que comparten el mismo conjunto de sufijos descendientes pueden vivir a diferentes profundidades de una misma arista.

### 6.2 Definición formal y propiedades

Para `S=s+$`, cada hoja representa un sufijo de `S`. Un nodo interno no raíz tiene al menos dos hijos después de compactar. Las etiquetas salientes empiezan con caracteres distintos.

Campos habituales:

- `left[v]`, `right[v]`: intervalo que etiqueta la arista de entrada a `v`.
- `parent[v]` y mapa de hijos por primer símbolo.
- `depth[v]`: longitud en caracteres desde la raíz.
- `suffixStart[v]` para hojas.
- `slink[v]`: para un nodo interno con etiqueta de camino `cα`, apunta al nodo de `α`.

La profundidad en caracteres no es el número de aristas. La longitud de una arista es `right-left` bajo intervalos semiabiertos.

Un **locus** de una cadena es el punto al terminar de recorrerla. Puede ser un nodo explícito o un punto interior de una arista. El conjunto de ocurrencias de un patrón cuyo locus está dentro de la arista hacia `v` corresponde a las hojas del subárbol de `v`.

Con `N=|S|` hojas y grados internos al menos dos, hay `O(N)` nodos y aristas. Eso no implica que puedas guardar todas las etiquetas como cadenas copiadas en espacio lineal: las referencias a intervalos son parte esencial de la representación.

### 6.3 Complejidad

- Trie de sufijos ingenuo: `Θ(n²)` tiempo y espacio en el peor caso.
- Suffix Tree por Ukkonen: `O(n)` tiempo con alfabeto constante y transiciones adecuadas; con mapas balanceados, típicamente `O(n log σ)`.
- Espacio de nodos y aristas: `O(n)`; arreglos densos por nodo agregan factor `σ`.
- Buscar patrón: `O(m)` con acceso constante a hijos; con mapas, agrega el costo de consultas de hijos.
- Reportar ocurrencias: `O(m+occ)` bajo ese mismo modelo.
- Contar ocurrencias con tamaño de subárbol precomputado: `O(m)`.
- Construir a partir de SA+LCP ya disponibles: `O(n)` adicional usando una pila, con una representación de hijos apropiada.

La construcción desde SA+LCP suele ser una alternativa competitiva si necesitas la topología del árbol pero no la propiedad online. Su tiempo total incluye la construcción del SA.

### 6.4 Implementación e ideas clave

#### Ukkonen: qué debe mantener una implementación

Ukkonen procesa caracteres de izquierda a derecha y mantiene un árbol de sufijos implícito del prefijo actual. Sus ingredientes se entienden mejor como mecanismos para evitar trabajo repetido:

1. **Extremos abiertos en hojas.** Todas las hojas se extienden al agregar un carácter. Un extremo global compartido hace esa actualización simultánea en `O(1)`.
2. **Punto activo.** Describe dónde continuar las extensiones pendientes: nodo activo, arista activa y longitud recorrida dentro de ella.
3. **Sufijos pendientes.** Una cuenta indica cuántas extensiones de la fase aún requieren atención.
4. **Skip/count.** Si la parte recorrida cubre una arista entera, salta su longitud; no vuelvas a comparar cada carácter ya conocido.
5. **Suffix links.** Después de resolver una extensión, ayudan a iniciar la correspondiente al siguiente sufijo.
6. **Regla de terminación temprana.** Si la extensión necesaria ya existe, el resto de ciertas extensiones de la fase queda representado implícitamente; no hay que crear todas las hojas en ese instante.

Al agregar `c`, una extensión encuentra uno de estos casos:

- No existe la arista requerida: crea una hoja.
- Existe y el siguiente símbolo coincide: avanza el punto activo y termina la fase según la regla de Ukkonen.
- Existe pero hay discrepancia dentro de la arista: divide la arista, crea un nodo interno y añade una nueva hoja.

Cada división crea un nodo interno que tendrá un enlace de sufijo. La implementación suele mantener el último nodo interno creado cuya liga aún debe conectarse. La linealidad requiere controlar tanto el número de nodos creados como las caminatas del punto activo; “cada fase añade un carácter” por sí solo no es una prueba.

No conviene memorizar una implementación críptica antes de dominar estos invariantes. El código compacto de tus apuntes usa `node`, `pos`, `f_pos`, `len` e `inf` para codificar ideas relacionadas, pero esas variables no tienen exactamente la misma semántica que todas las versiones populares de Ukkonen.

#### Construcción desde SA+LCP

Es una forma más accesible de obtener un árbol explícito para texto estático:

1. Procesa sufijos en orden SA.
2. Mantén una pila con el camino derecho del árbol y profundidades crecientes.
3. Para el nuevo sufijo, sea `L` su LCP con el anterior.
4. Saca de la pila los nodos cuya profundidad excede `L`.
5. Si la profundidad de la cima es menor que `L`, crea un nodo interno a profundidad `L` y reubica bajo él la rama recién cerrada.
6. Cuelga la nueva hoja y actualiza la pila.

Cada nodo entra y sale de la pila a lo sumo una vez. Para aristas usa un sufijo representante: la arista desde profundidad `a` a `b` puede etiquetarse con `[suffixStart+a,suffixStart+b)`.

Esta construcción obtiene la topología y etiquetas; no obtienes suffix links automáticamente. Si tu aplicación solo necesita hojas, profundidades, LCA o DP, normalmente no los necesitas.

#### Casos de esquina

- Un patrón puede terminar dentro de una arista: no exijas llegar a un nodo.
- El centinela participa en el árbol, pero no debe contarse como parte de subcadenas del texto original.
- Una consulta que cruza el límite entre documentos es inválida salvo autorización del enunciado.
- Un DFS recursivo puede desbordar la pila en árboles degenerados.
- Después de reutilizar arreglos globales, reinicializa hijos, links y metadatos que puedan leerse; limpiar solo algunos mapas no demuestra que todo el estado quedó limpio.

### 6.5 Aplicaciones y usos clásicos

**Matching y ocurrencias.** Sigue el patrón comparando etiquetas; al terminar, reporta o cuenta hojas descendientes.

**Subcadena repetida más larga.** Es la etiqueta de camino del nodo interno más profundo que tenga al menos dos hojas del texto relevante. En un árbol generalizado, cambia la condición por hojas de ciertos colores. Debes medir profundidad en caracteres.

**Subcadenas distintas.** Cada arista aporta tantos contenidos nuevos como posiciones válidas a lo largo de su etiqueta. La suma de longitudes de aristas, excluyendo porciones que incluyen centinelas, coincide con el conteo por SA y SAM.

**Longest common substring.** Colorea hojas por documento. El nodo más profundo cuyo subárbol contiene todos los colores requeridos representa una subcadena común. Para dos documentos basta una máscara de dos bits; para muchos, sets, bitsets o small-to-large.

**LCE mediante LCA.** El LCP de dos sufijos es la profundidad en caracteres de su LCA. Esta es la versión arbórea de RMQ sobre LCP.

**Repeticiones máximas.** Una subcadena es right-maximal si tiene al menos dos extensiones derechas distintas —incluido, cuando corresponda, el final del texto—; las bifurcaciones internas la hacen visible. Para left-maximal también necesitas diversidad de caracteres precedentes de sus ocurrencias. Ser repetida y ser maximal son condiciones diferentes.

**Subcadena única más corta desde una posición.** En el camino a la hoja del sufijo, el primer punto después de perder toda otra hoja descendiente da una longitud única, siempre que no necesite consumir el centinela. Si su padre tiene profundidad `d`, el candidato es `d+1` cuando cabe dentro del sufijo original.

### 6.6 Técnicas complementarias

**DP en árbol.** Agrega cantidades de hojas, colores, mínima posición, máxima posición o puntajes. Si una propiedad es constante a lo largo de una arista, procesa un intervalo de longitudes de una vez.

**Small-to-large y DSU on tree.** Para atributos por documento o posición, evita duplicar todos los conjuntos de hojas en cada ancestro. Una fusión por tamaño amortiza movimientos, aunque el costo final depende de las operaciones del contenedor.

**LCA + RMQ.** Después de Euler, consultas LCE se vuelven RMQ de profundidades. La etiqueta de la arista no necesita descomprimirse.

**Árbol virtual.** Si una consulta involucra pocas hojas, puedes construir el árbol virtual de esas hojas y sus LCAs. Las aristas virtuales representan diferencias de profundidad y permiten calcular estadísticas sobre sufijos seleccionados sin recorrer todo el árbol.

**SA como sustituto operativo.** Muchas DPs de suffix tree pueden implementarse sobre intervalos LCP. Saber hacer esta traducción te permite escoger una plantilla que ya esté bien probada, sin perder la estructura conceptual del problema.

### 6.7 Práctica y ejercicios de dominio

- [CSES — Finding Patterns](https://cses.fi/problemset/task/2102): úsalo como prueba de matching en árbol; no exige Suffix Tree específicamente.
- [CSES — Distinct Substrings](https://cses.fi/problemset/task/2105): compara suma de aristas válidas contra SA y SAM.
- [CSES — Repeating Substring](https://cses.fi/problemset/task/2106): profundidad de nodos internos.
- **Ejercicio original ST1.** Construye Suffix Tree desde SA+LCP y comprueba que todas sus hojas representan exactamente los sufijos.
- **Ejercicio original ST2.** Dados `k` documentos, encuentra su subcadena común más larga coloreando hojas.
- **Ejercicio original ST3.** Para cada sufijo, encuentra su prefijo único mínimo, o determina que no existe dentro del texto original.
- **Ejercicio original ST4.** Dado un conjunto pequeño de posiciones por consulta, suma LCP de todos los pares usando árbol virtual.

**Criterio de dominio:** distingues nodo explícito y locus implícito, y puedes explicar por qué guardar etiquetas como intervalos es necesario para la cota espacial.

<a id="sam"></a>
## 7. Suffix Automaton: clases de subcadenas con el mismo `endpos`

### 7.1 Concepto e intuición

El Suffix Automaton organiza todas las subcadenas de una cadena en un DAG pequeño. Su compresión se basa en que distintas subcadenas pueden terminar exactamente en las mismas posiciones.

En `ababa`:

$$
endpos(a)=\{0,2,4\},\quad
endpos(ba)=endpos(aba)=\{2,4\}.
$$

`ba` y `aba` son distintas, pero para saber con qué caracteres pueden continuar dentro del texto y cuántas veces aparecen, comparten información. SAM las agrupa en un estado.

Esta es la distinción central: **un estado no equivale a una sola subcadena**. Un estado representa un intervalo de longitudes, con una cadena por longitud. En cambio, cada camino desde la raíz sí escribe una cadena concreta.

### 7.2 Definición formal y propiedades

Para una subcadena no vacía `x`:

$$
endpos(x)=\{i:s[i-|x|+1..i+1)=x\}.
$$

Dos subcadenas son equivalentes si tienen el mismo `endpos`. Cada estado no raíz representa una clase de equivalencia.

Campos fundamentales:

- `len[v]`: máxima longitud de una cadena de la clase.
- `link[v]`: clase del mayor sufijo propio del representante más largo que pertenece a una clase distinta.
- `next[v][c]`: clase alcanzada al extender por `c`, si esa extensión aparece.
- `last`: estado del prefijo completo procesado.

La raíz tiene `len=0` y `link=-1`. Para `v≠root`:

$$
minlen[v]=len[link[v]]+1,
$$

$$
\{\text{longitudes representadas por }v\}
=[minlen[v],len[v]].
$$

Cada longitud de ese intervalo representa exactamente un sufijo del representante más largo. No son todas las cadenas de esas longitudes.

**Inclusión de `endpos`.** Si dos subcadenas comparten una posición final, la más corta es sufijo de la más larga. Por ello los conjuntos `endpos` de clases distintas son disjuntos o uno contiene al otro. Los suffix links codifican esa jerarquía.

**Transiciones.** Si `v --c→ u`, entonces `len[u]≥len[v]+1`; por tanto el grafo de transiciones es acíclico. Puede saltar varias unidades de `len`, porque la clase destino representa varias longitudes.

**Terminales.** Un SAM con los estados de la cadena de suffix links desde `last` marcados como aceptantes reconoce los sufijos del texto. Si todos los estados se aceptan, los caminos desde la raíz reconocen todas las subcadenas, incluida `ε` si se acepta la raíz. Ambas interpretaciones usan el mismo grafo, pero diferente aceptación.

**Tamaño.** Hay a lo sumo `2n-1` estados para `n≥2`; el caso `n=1` tiene raíz y un estado. La cota cómoda para reservar es `2n+1`. El número de transiciones existentes es `O(n)`; una tabla densa sigue reservando `O(nσ)` casillas.

### 7.3 Complejidad

- Construcción incremental estándar: `O(n)` para alfabeto fijo y acceso constante a transiciones.
- Mapas balanceados: `O(n log σ)` bajo la implementación estándar de transiciones dispersas.
- Espacio: `O(n)` estados y transiciones existentes; `O(nσ)` si se almacenan tablas densas.
- Consultar existencia o frecuencia de un patrón después del postprocesamiento: `O(m)` con transición constante.
- Propagar ocurrencias: `O(n)` con counting sort por `len`; `O(n log n)` si ordenas estados con sort genérico.
- DPs en el DAG: `O(V+E)` cuando cada arista se procesa una vez.

La construcción online no implica que `occ[v]` esté disponible online mediante la propagación habitual. Esta se realiza al final. Mantener frecuencias exactas tras cada append exige trabajo adicional y puede necesitar estructuras dinámicas de árbol.

### 7.4 Implementación e ideas clave

#### Extensión por un carácter

Al agregar `c`:

```text
crear cur con len[cur] = len[last]+1
p = last
mientras p != -1 y falta next[p][c]:
    next[p][c] = cur
    p = link[p]

si p == -1:
    link[cur] = root
si no:
    q = next[p][c]
    si len[p]+1 == len[q]:
        link[cur] = q
    si no:
        crear clone como copia estructural de q
        len[clone] = len[p]+1
        mientras p != -1 y next[p][c] == q:
            next[p][c] = clone
            p = link[p]
        link[q] = link[cur] = clone
last = cur
```

“Copia estructural” significa transiciones y suffix link. Los metadatos de conteo no siempre se copian: un clon no corresponde a una nueva posición final observada.

#### Por qué se necesitan clones

Si encontramos una transición `p --c→ q` y `len[p]+1=len[q]`, la clase `q` ya empieza donde la nueva relación necesita. Si `len[p]+1<len[q]`, `q` mezcla longitudes cuyo comportamiento debe separarse tras agregar el carácter. El clon conserva las continuaciones de `q`, pero representa el tramo de longitudes cortas. `q` conserva el tramo largo.

Ejemplo mínimo útil: construir `abb`.

1. Tras `ab`, el estado de `ab` también representa `b`: ambas terminan solo en posición 1.
2. Al añadir otra `b`, `b` termina en posiciones 1 y 2, mientras `ab` solo termina en 1.
3. Sus conjuntos `endpos` dejan de coincidir; un clon separa la clase de `b`.

El clon no es una optimización incidental: restaura la equivalencia que define la estructura.

#### Frecuencias de ocurrencia

Inicializa `occ[cur]=1` en cada estado nuevo asociado a un carácter del texto y `occ[clone]=0`. Luego:

```text
ordenar estados por len decreciente
para v != root en ese orden:
    occ[link[v]] += occ[v]
```

Cada prefijo completo aporta una posición final. Sus suffix links visitan las clases de sus sufijos. Así, la suma del subárbol de un estado en el árbol de links es exactamente el tamaño de su `endpos`.

No repitas esta propagación sobre contadores ya agregados: duplicarías contribuciones. Conserva contadores base si necesitas reconstruir o recalcular.

#### Posiciones y reconstrucción

Guarda `firstpos[cur]=posición_actual`. En un clon puedes copiar `firstpos[q]`: necesitas una ocurrencia representativa, no una nueva ocurrencia. Una cadena de longitud `L` representada por `v` puede recuperarse como:

$$
s[firstpos[v]-L+1..firstpos[v]+1).
$$

Para extremos de `endpos`, propaga mínimo y máximo de las posiciones base. No inicialices un clon como una nueva observación para conteos aditivos.

#### Orden correcto

Los identificadores de creación no son un orden válido por `len`: un clon creado tarde puede tener longitud pequeña. Para propagaciones usa orden explícito por `len`. Como `len≤n`, counting sort es natural.

### 7.5 Aplicaciones y usos clásicos

#### Contar subcadenas distintas

Cada estado aporta una cadena por cada longitud de su intervalo:

$$
D=\sum_{v\ne root}\bigl(len[v]-len[link[v]]\bigr).
$$

Al añadir un carácter, el aumento de subcadenas distintas es `len[cur]-len[link[cur]]` después de completar la extensión. La aparición de un clon redistribuye intervalos antiguos; no crea por sí sola contenidos nuevos.

#### Contar por frecuencia o longitud

Todos los contenidos representados por `v` aparecen `occ[v]` veces. Para contar subcadenas distintas que aparecen al menos `k` veces:

$$
\sum_{v\ne root,\ occ[v]\ge k}(len[v]-len[link[v]]).
$$

Para restringir longitudes a `[A,B]`, intersecta ese rango con `[minlen[v],len[v]]`. Esto evita enumerar las longitudes una por una.

Para la subcadena más larga con `occ≥k`, maximiza `len[v]` sobre los estados elegibles.

#### Suma de longitudes

El estado `v` contribuye:

$$
\sum_{L=minlen[v]}^{len[v]}L.
$$

Si quieres sumar longitud por ocurrencia, multiplica además por `occ[v]`. De nuevo, los posibles valores numéricos son mucho mayores que el número de estados.

#### k-ésima subcadena distinta

Define `ways[v]` como número de continuaciones no vacías desde `v`:

$$
ways[v]=\sum_{v\xrightarrow{c}u}(1+ways[u]).
$$

Calcula en orden decreciente de `len`. Para reconstruir, recorre transiciones por etiqueta creciente; cada una define un bloque de tamaño `1+ways[u]`. La cadena que termina inmediatamente tras esa arista va antes que sus extensiones.

Satura conteos en `K+1` si solo vas a comparar contra `K`; esto previene overflow sin perder decisiones de selección. Una saturación debe implementarse evitando overflow antes del `min`.

#### k-ésima subcadena contando multiplicidades

Ahora cada cadena que termina en el estado `u` aparece `occ[u]` veces. El bloque correspondiente a una arista pesa:

$$
occ[u]+mass[u],\qquad
mass[v]=\sum_{v\xrightarrow{c}u}(occ[u]+mass[u]).
$$

Al entrar en `u`, las primeras `occ[u]` posiciones del bloque corresponden a copias de la cadena actual. Después siguen sus extensiones. Usar `1` en lugar de `occ[u]` resuelve un problema diferente.

#### Longest common substring de dos cadenas

Construye SAM de `a`. Recorre `b` manteniendo un estado `v` y una longitud `L` de la mayor coincidencia que termina en la posición actual.

```text
v = root; L = 0
para c en b:
    mientras v != root y falta next[v][c]:
        v = link[v]
        L = min(L,len[v])
    si existe next[v][c]:
        v = next[v][c]
        L++
    si no:
        v = root
        L = 0
    actualizar mejor con L
```

La longitud `L` es necesaria porque llegar al estado `v` no determina una longitud única. Saltar a un suffix link sin ajustar `L` produce respuestas imposibles.

#### Longest common substring de muchos textos

Construye SAM del primero, preferiblemente uno corto. Para cada texto adicional:

1. Recorre como arriba y registra `best[v]=max(best[v],L)`.
2. Propaga en orden decreciente:
   `best[link[v]]=max(best[link[v]],min(best[v],len[link[v]]))`.
3. Mantén `common[v]=min(common[v],best[v])`, con inicialización `common[v]=len[v]`.
4. Reinicia `best` para el siguiente texto.

La respuesta es `max common[v]`. El truncamiento al propagar es obligatorio: un padre no puede representar longitudes mayores que su `len`. La cota incluye `O(V)` por documento además de la longitud total leída.

#### Cadena ausente más corta

Una transición inexistente produce una cadena que no aparece. En el DAG define:

$$
missing[v]=\min_{c\in\Sigma}
\begin{cases}
1,&next[v][c]\text{ no existe},\\
1+missing[next[v][c]],&\text{existe}.
\end{cases}
$$

Con etiquetas ordenadas y desempate apropiado, reconstruyes la menor lexicográficamente entre las más cortas. Es crucial especificar el alfabeto permitido: una letra fuera del texto daría una respuesta trivial de longitud uno si estuviera permitida.

### 7.6 Técnicas complementarias

#### Árbol de suffix links + Euler

Guarda `pref[i]`, estado `last` después de leer `s[0..i+1)`. En el SAM final, una subcadena representada por `v` termina en `i` si `pref[i]` está en el subárbol de `v` en el árbol de links.

Esta es la misma forma de reducción que en Aho, pero sus nodos significan otra cosa. Cada posición final se convierte en un punto Euler. Con persistencia o consultas offline puedes contar `endpos` dentro de rangos.

#### Binary lifting para localizar una subcadena dada por índices

La subcadena `s[l..r)` es sufijo del prefijo que termina en `r-1`. Empieza en `pref[r-1]` y sube por links hasta el ancestro más alto que todavía cumple `len[v]≥r-l`. El resultado debe satisfacer:

$$
len[link[v]]<r-l\le len[v].
$$

Con binary lifting se hace en `O(log n)`. Esto transforma un intervalo del texto en un estado SAM sin volver a leer sus caracteres.

#### Segment Trees y estadísticas de `endpos`

Si cada posición final tiene peso, agrega pesos en `pref[i]` y combina subárboles de links. Para consultas estáticas simples bastan sumas; para rangos por posición pueden servir árboles persistentes o estructuras fusionables. Fusionar Segment Trees por nodo exige contabilizar cuántos nodos se crean y consumen; no prometas espacio lineal si cada versión copia caminos.

#### Producto SAM × autómata de restricciones

Recorrer transiciones de SAM enumera subcadenas distintas; mantener simultáneamente un estado de Aho permite descartar las que contienen patrones prohibidos. El producto sigue siendo acíclico respecto a `len` del componente SAM. Una DP cuenta cadenas distintas válidas. La cota potencial es `O(V_SAM V_Aho σ)` con representación densa, por lo que solo conviene si el producto alcanzable cabe.

#### Múltiples cadenas: evita una adaptación informal

Reiniciar `last=root` y reutilizar sin cambios la extensión estándar no es una justificación de SAM generalizado. La rutina usual asume que cada append extiende el único texto construido. Una alternativa segura es construir un SAM de una referencia y recorrer las demás; otra es concatenar con separadores y excluir rigurosamente cadenas que los contienen. Hay construcciones especializadas sobre tries, pero requieren sus propios invariantes.

### 7.7 Práctica y ejercicios de dominio

- [CSES — Distinct Substrings](https://cses.fi/problemset/task/2105): fórmula por intervalos de longitudes.
- [CSES — Substring Order I](https://cses.fi/problemset/task/2108): DP de caminos distintos.
- [CSES — Substring Order II](https://cses.fi/problemset/task/2109): ponderar por frecuencia.
- [CSES — Substring Distribution](https://cses.fi/problemset/task/2110): diferencias sobre `[minlen,len]`.
- [CSES — Repeating Substring](https://cses.fi/problemset/task/2106): `occ≥2`.
- **Ejercicio original M1.** Después de cada append, imprime cuántas subcadenas distintas existen.
- **Ejercicio original M2.** Cuenta subcadenas distintas con frecuencia exactamente `k` y longitud en `[A,B]`.
- **Ejercicio original M3.** Localiza el estado de cada subcadena dada por índices usando binary lifting.
- **Ejercicio original M4.** Cuenta apariciones de una subcadena dentro de otro intervalo del texto usando el árbol de links.
- **Ejercicio original M5.** Cuenta subcadenas distintas que evitan un diccionario pequeño mediante producto de autómatas.

**Criterio de dominio:** puedes explicar un clon usando `endpos`, distinguir caminos y estados, y demostrar el intervalo `[len[link]+1,len]`.

<a id="dp"></a>
## 8. Programación dinámica sobre estructuras de strings

### 8.1 Concepto e intuición

Una estructura de strings reduce el número de historias que debes distinguir. Una DP aprovecha esa reducción para contar, optimizar o reconstruir objetos. Muchos problemas difíciles no requieren un nuevo algoritmo de cadenas: requieren elegir correctamente la DP sobre una estructura conocida.

Conviene separar tres tareas:

1. **Reconocer:** qué parte del pasado condiciona futuras coincidencias.
2. **Acumular:** qué valor se combina al avanzar o al terminar.
3. **Ordenar dependencias:** en qué orden se evalúan estados para evitar ciclos o doble conteo.

Por ejemplo, para contar cadenas de longitud `L` que evitan un patrón, KMP resuelve el reconocimiento. La posición `i` hace acíclica la DP aunque el autómata tenga ciclos. Para contar subcadenas distintas de un texto mediante SAM, el propio DAG ya proporciona un orden acíclico.

### 8.2 Definición formal y propiedades

Un estado debe ser una **estadística suficiente del prefijo construido**: dos historias que caen en él deben tener el mismo conjunto de continuaciones válidas y la misma forma de contribuir al objetivo, salvo el valor acumulado que la DP guarda explícitamente.

Un autómata determinista tiene estados `Q`, estado inicial `q0`, transición `δ(q,c)` y una condición de aceptación. Podemos asociar además ganancia `g(q,c)` y restricciones.

Una familia general de recurrencias es:

$$
DP[i+1][\delta(q,c)]\mathrel{\oplus}=
DP[i][q]\otimes w(q,c).
$$

Las operaciones dependen del problema:

| Objetivo | Combinar alternativas `⊕` | Extender una solución `⊗` |
|---|---|---|
| Contar | Suma | Producto por multiplicidad |
| Existencia | OR | AND con validez |
| Costo mínimo | Mínimo | Suma de costo |
| Puntaje máximo | Máximo | Suma de ganancia |
| Probabilidad | Suma | Producto por probabilidad |

El vocabulario de semianillos ayuda a reconocer que varias soluciones comparten la misma transición; no necesitas implementar una abstracción genérica en concurso.

**Determinismo y conteo.** En un autómata determinista, una cadena produce un único recorrido desde la raíz. Esto permite contar cadenas mediante recorridos. En un autómata no determinista, diferentes recorridos pueden escribir la misma cadena; contar caminos podría sobrecontar contenidos.

### 8.3 Complejidad

Una DP por longitud sobre `V` estados y alfabeto de tamaño `σ` cuesta `O(LVσ)` y puede usar `O(V)` memoria con dos capas. Agregar una máscara de `k` propiedades produce hasta `O(LV2^kσ)`. Agregar un contador hasta `r` produce hasta `O(LVrσ)`.

Exponenciación matricial densa: `O(V³ log L)` tiempo y `O(V²)` memoria. Un autómata inicialmente disperso no garantiza matrices dispersas después de elevarlas al cuadrado.

DP en DAG de transiciones: `O(V+E)` si cada estado y arista requiere trabajo constante. DP de mochila en trie: depende de las convoluciones de tamaños; la cota puede ser cuadrática en el número de elementos seleccionables.

El número de estados alcanzables puede ser mucho menor que el producto cartesiano, pero explotar eso no cambia la cota de peor caso sin una prueba adicional.

### 8.4 Implementación e ideas clave

#### Patrón A: evitar un diccionario

Construye Aho y propaga `bad`. Define:

$$
dp[i][v]=\#\text{cadenas válidas de longitud }i\text{ que terminan en }v.
$$

Inicializa `dp[0][root]=1`. Para cada letra, si `u=go[v][c]` no es malo, suma `dp[i][v]` a `dp[i+1][u]`. La respuesta es la suma sobre estados seguros en capa `L`.

Si el diccionario contiene `ε`, ninguna cadena evita el diccionario bajo la definición usual, incluida la cadena vacía. Es mejor detectarlo al inicio que forzar excepciones dentro de las transiciones.

#### Patrón B: contener al menos una vez

Hay dos métodos:

- Complemento: `σ^L - #cadenas_que_evitan`, módulo `mod` cuando corresponda.
- Bandera `seen`: `seen' = seen OR evento_de_match`.

El complemento suele ahorrar estados cuando solo interesa la existencia de alguna aparición. La bandera es más flexible si hay otras condiciones que no se prestan a restar de un universo sencillo.

No conviertas sin explicación el estado terminal en absorbente si luego necesitarás contar más ocurrencias: eso conserva “ya ocurrió”, pero destruye la información necesaria para futuros matches.

#### Patrón C: exactamente `r` ocurrencias

Usa `dp[i][v][j]`. Al leer `c`, el incremento es `gainCount[go[v][c]]`, que puede ser mayor que uno en Aho por patrones anidados o duplicados. Descarta transiciones con `j'>r` si todos los incrementos son no negativos.

Con un único patrón KMP, cada posición final puede completar como máximo una copia de ese patrón, pero el reinicio debe permitir solapamientos. `aaa` en `aaaa` produce dos eventos consecutivos.

#### Patrón D: máximo puntaje de una cadena de longitud fija

Si cada patrón tiene un peso, propaga ganancias por fallos y usa:

$$
best[i+1][u]=\max(best[i+1][u],best[i][v]+gain[u]).
$$

Inicializa estados imposibles a `-∞`; cero no es un valor de imposibilidad si hay pesos negativos. Guarda predecesor y letra para reconstruir. Para longitudes enormes, usa matrices max-plus si el número de estados lo permite.

#### Patrón E: reconstrucción lexicográficamente mínima

Primero calcula `can[remaining][state]`, indicando si existe una terminación válida. Después, desde el estado inicial, prueba caracteres en orden creciente y elige el primero cuyo destino sea factible.

El greedy es correcto porque todas las cadenas con una primera letra menor preceden a cualquiera con letra mayor, y la DP certifica que la opción elegida puede completarse. Elegir la letra menor que “no viola todavía” la restricción no basta: podría dejar un futuro imposible.

Para la k-ésima cadena, sustituye booleanos por cantidades de completaciones y salta bloques. Satura en `K+1` para limitar enteros. Si los conteos son módulo `mod`, no puedes usarlos para comparar con `K`; el residuo pierde el orden numérico.

#### Patrón F: digit DP con autómata

Para contar números en `[0,X]` que evitan ciertos bloques de dígitos, agrega estado de autómata a `dp[pos][tight][started][q]`.

- `tight` indica si el prefijo coincide con el de `X`.
- `started` distingue ceros de relleno de dígitos reales.
- `q` registra el sufijo relevante de los dígitos efectivamente leídos.

Debes decidir cómo se representa el número cero y si los ceros a la izquierda forman parte de la cadena del problema. Alimentar ceros de relleno al autómata puede crear patrones inexistentes en la representación canónica.

#### Patrón G: DP sobre textos definidos por gramáticas

Para cada bloque `B` guarda dos arreglos por estado inicial:

- `to_B[q]`: estado final tras leer `B`.
- `cnt_B[q]`: número o puntaje de matches durante `B`.

Para concatenar `A` seguido de `B`:

$$
to_{AB}[q]=to_B[to_A[q]],
$$

$$
cnt_{AB}[q]=cnt_A[q]+cnt_B[to_A[q]].
$$

Es una composición asociativa. Permite exponenciar repeticiones, evaluar una gramática acíclica o un árbol de concatenaciones. Cuenta correctamente matches que cruzan la frontera porque el estado de salida de `A` se entrega a `B`.

Si las ganancias dependen de posición absoluta, la pareja anterior puede ser insuficiente; quizás necesites longitud, sumas ponderadas u otra información que permita trasladar coordenadas.

### 8.5 Aplicaciones y usos clásicos

#### DP en trie: segmentación y selección

En segmentación, `dp[i]` cuenta o minimiza sobre particiones del prefijo `s[0..i)`. Un recorrido desde cada posición agrega una transición por cada terminal encontrado. Para contar, suma; para minimizar palabras, añade uno y toma mínimo; para costos de palabras, usa su peso.

En selección de palabras, `dp[v][k]` representa la mejor forma de tomar `k` terminales del subárbol. Al fusionar hijo `u`:

$$
new[a+b]=\min(new[a+b],dp_v[a]+dp_u[b]+coste\_conexion(u,b)).
$$

El costo de conexión puede ser cero cuando `b=0` y la longitud de la arista cuando `b>0`. Si debes ir y volver por la arista, sería dos veces la longitud; si el recorrido puede terminar en una palabra elegida, necesitas una dimensión que indique si dejas un extremo abierto. El modelo del recorrido decide la recurrencia.

#### DP en SAM: caminos frente a clases

Para contar contenidos distintos, usa caminos o intervalos de longitudes. Para agregar estadísticas uniformes sobre `endpos`, usa estados. No mezcles ambos conteos.

Ejemplo: `Σ(len[v]-len[link[v]])` cuenta contenidos, mientras `V-1` solo cuenta clases. Por otro lado, `ways[root]` cuenta caminos distintos no vacíos porque el autómata es determinista. Las dos fórmulas deben coincidir y sirven como verificación mutua.

#### DP en árboles de fallos/sufijos

El flujo de información hacia el padre suele responder “cuántas extensiones contienen esta entidad como sufijo”. El flujo del padre al hijo suele responder “qué propiedades de sufijos debo heredar”.

En Aho:

- `visits` se propaga de hijos a padre.
- `bad` y `gain` se propagan desde `link[v]` hacia `v`.

En SAM:

- `occ` se propaga desde longitudes mayores a menores.
- `ways` usa aristas de caracteres y orden inverso del DAG, no el árbol de suffix links.

Elegir la dirección equivocada puede dar números plausibles y aun así incorrectos.

#### Caminos etiquetados en grafos

Si debes ir de `s` a `t` evitando palabras prohibidas en las etiquetas del recorrido, construye el producto con Aho. Una transición del grafo original `x --c→ y` induce `(x,q)→(y,go[q][c])` si el destino es seguro.

Si se cuentan recorridos de longitud fija, una capa de longitud evita el problema de ciclos. Si se cuentan todos los recorridos sin límite en un grafo con ciclos relevantes, la respuesta puede ser infinita; no intentes una DP topológica sobre un grafo que no es DAG.

### 8.6 Técnicas complementarias

**Reducir el espacio de estados.** Elimina estados imposibles por restricciones, compacta estados alcanzables y considera si algunas dimensiones pueden saturarse: “al menos `r`” permite capar contadores en `r`; “exactamente `r`” normalmente descarta los que lo superan.

**Agrupar letras equivalentes.** Si varios símbolos generan el mismo destino y ganancia, combina sus multiplicidades. Esto puede reducir trabajo por transición, pero debes contar cuántos símbolos hay en cada grupo.

**Exponenciación de transformaciones.** Para un bloque fijo que actúa de manera determinista, no necesitas matriz `V×V`: la función `to` y un agregado por estado se componen en `O(V)`. Una matriz es necesaria cuando desde cada estado se suman varias posibilidades de símbolos/bloques.

**Recurrencias lineales.** Para un autómata finito, el número de cadenas aceptadas por longitud satisface una recurrencia lineal. En ciertos módulos y con técnicas adecuadas puede reconstruirse una recurrencia a partir de términos y evaluarse rápido. Esta optimización requiere entender el campo/módulo y validar la recurrencia; no reemplaza automáticamente la exponenciación matricial en todos los anillos.

**HLD / Fenwick / persistencia.** Cuando la DP se vuelve una secuencia de activaciones y consultas sobre árboles de enlaces, usa estructuras de datos sobre el árbol. Pero si construir la cadena cambia la topología del árbol, una descomposición estática no se mantiene por arte de magia.

**Reconstrucción con poca memoria.** Guardar todas las capas cuesta `O(LV)`. Si solo quieres el valor, usa dos capas. Si quieres una solución, puedes guardar predecesores, recomputar por bloques o aplicar divide and conquer cuando la transición lo permita. Declara qué memoria requiere tu versión concreta.

### 8.7 Práctica y ejercicios de dominio

- [CSES — Required Substring](https://cses.fi/problemset/task/1112): DP por longitud y KMP.
- [CSES — Word Combinations](https://cses.fi/problemset/task/1731): DP por posiciones y diccionario.
- [CSES — Substring Order I](https://cses.fi/problemset/task/2108) y [II](https://cses.fi/problemset/task/2109): separar conteo de contenidos y multiplicidades.
- [Codeforces 455B — A Lot of Games](https://codeforces.com/problemset/problem/455/B): DP de juego en trie.
- **Ejercicio original D1.** Maximiza el puntaje de patrones, con pesos positivos y negativos, en una cadena de longitud `L`.
- **Ejercicio original D2.** Cuenta números hasta `X` que contienen `13` exactamente dos veces y evitan `000`, sin ceros iniciales.
- **Ejercicio original D3.** Encuentra el camino más corto en un grafo etiquetado que contenga todos los patrones de un diccionario de tamaño pequeño.
- **Ejercicio original D4.** Evalúa matches sobre `S_0=a`, `S_1=b`, `S_i=S_{i-1}S_{i-2}` sin construir `S_i`.
- **Ejercicio original D5.** Construye la k-ésima cadena válida de longitud `L` y explica por qué conteos modulares no bastan.

**Criterio de dominio:** puedes justificar la suficiencia del estado, identificar el orden de dependencia y distinguir conteo de cadenas de conteo de recorridos.

<a id="manacher"></a>
## 9. Manacher: todos los radios palindrómicos en tiempo lineal

### 9.1 Concepto e intuición

Expandir alrededor de cada centro resuelve palíndromos, pero cuesta `Θ(n²)` en `aaaa...a`. Si ya sabemos que un intervalo es palíndromo, un centro dentro de él tiene un centro espejo. Las coincidencias del espejo se reutilizan hasta la frontera conocida; solo se comparan caracteres nuevos cuando se intenta rebasarla.

Esta idea se parece al algoritmo Z: ambos mantienen una región conocida y amortizan nuevas comparaciones por el avance de su frontera derecha. La simetría que justifica la reutilización es diferente.

### 9.2 Definición formal y propiedades

Usaremos dos arreglos:

- `d1[i]`: número de palíndromos impares centrados en `i`; el mayor ocupa `[i-d1[i]+1,i+d1[i])` y tiene longitud `2*d1[i]-1`.
- `d2[i]`: número de palíndromos pares centrados entre `i-1` e `i`; el mayor ocupa `[i-d2[i],i+d2[i])` y tiene longitud `2*d2[i]`.

Ejemplos:

```text
s = ababa
d1 = [1,2,3,2,1]
d2 = [0,0,0,0,0]

s = aaaa
d1 = [1,2,2,1]
d2 = [0,1,2,1]
```

Todos los radios menores del mismo centro también son palíndromos. Por ello los dos arreglos representan compactamente todas las ocurrencias palindrómicas, aunque su número sea cuadrático.

### 9.3 Complejidad

- Construcción: `O(n)` tiempo, `O(n)` espacio.
- Mayor palíndromo y conteo de todas las ocurrencias: `O(n)` posterior o durante construcción.
- Verificar si un intervalo dado es palíndromo: `O(1)` tras el preprocesamiento.
- Enumerar todos los intervalos palindrómicos: `Θ(n+occ)`, con `occ` potencialmente cuadrático.

Los arreglos estáticos no se actualizan localmente de manera general tras cambiar un carácter: una modificación puede alterar radios en muchas posiciones.

### 9.4 Implementación e ideas clave

Aquí usaremos una caja palindrómica con extremos **inclusivos** `[l,r]`, porque permite presentar las fórmulas habituales. Los intervalos de subcadenas de la guía siguen siendo semiabiertos; esta excepción es local y explícita.

```text
l=0; r=-1
para i=0,...,n-1:
    k = 1 si i>r; de lo contrario min(d1[l+r-i], r-i+1)
    mientras i-k>=0 y i+k<n y s[i-k]==s[i+k]:
        k++
    d1[i]=k
    si i+k-1>r:
        l=i-k+1
        r=i+k-1
```

Para pares:

```text
l=0; r=-1
para i=0,...,n-1:
    k = 0 si i>r; de lo contrario min(d2[l+r-i+1], r-i+1)
    mientras i-k-1>=0 y i+k<n y s[i-k-1]==s[i+k]:
        k++
    d2[i]=k
    si i+k-1>r:
        l=i-k
        r=i+k-1
```

Los tres desplazamientos que más se confunden son el espejo par `l+r-i+1`, el carácter izquierdo `i-k-1` y el extremo izquierdo `i-k`. Derívalos dibujando el centro entre caracteres, no por memoria muscular.

También puede transformarse la cadena insertando separadores entre caracteres para unificar paridades. Si lo haces, documenta cómo convertir radios y posiciones al texto original. Un separador real que aparezca en el alfabeto puede romper ciertas implementaciones con centinelas; usar enteros nuevos evita ambigüedad.

### 9.5 Aplicaciones y usos clásicos

**Mayor palíndromo.** Maximiza `2*d1[i]-1` y `2*d2[i]`. Conserva centro y paridad para reconstruir. Para desempate lexicográfico entre palíndromos máximos, Manacher encuentra candidatos, pero puede requerir LCE/SA para compararlos eficientemente.

**Número de ocurrencias palindrómicas.**

$$
\#palindromos=\sum_i d1[i]+\sum_i d2[i].
$$

La suma cuenta posiciones, no contenidos distintos. En `aaaa`, devuelve 10 y Eertree devuelve 4 nodos no especiales.

**Consulta de intervalo.** Para `[l,r)` no vacío de longitud `L`:

- Si `L` es impar, `c=(l+r-1)/2`; es palíndromo si `d1[c]≥(L+1)/2`.
- Si `L` es par, `c=(l+r)/2`; es palíndromo si `d2[c]≥L/2`.

La cadena vacía es palíndroma por convención habitual y se maneja aparte.

**Distribución por longitudes.** Cada centro impar aporta uno a radios `1,...,d1[i]`; histograma + sumas sufijas da la cantidad de ocurrencias de cada radio, equivalente a cada longitud impar. Haz lo mismo para pares.

**Prefijos y sufijos palindrómicos.** Un palíndromo máximo de un centro toca el inicio si su extremo izquierdo es cero. Para cada centro, una longitud apropiada puede tocar el inicio siempre que el radio requerido esté disponible. Análogamente para el final. Esto ayuda en particiones o extensiones mínimas.

**Dos palíndromos disjuntos.** Calcula el mejor palíndromo contenido en cada prefijo y sufijo y prueba cada corte. Obtener esos arreglos requiere propagar correctamente palíndromos que no son máximos globales de su centro; asignar solo el mayor de cada centro a su extremo no captura de inmediato todos los candidatos.

### 9.6 Técnicas complementarias

**RMQ y búsqueda binaria para palíndromo más largo dentro de un rango.** Para una consulta `[L,R)` y longitud impar `2k-1`, existe un palíndromo de esa longitud dentro del rango si hay centro:

$$
c\in[L+k-1,R-k]
\quad\text{con}\quad d1[c]\ge k.
$$

Consulta máximo de `d1` en ese rango de centros. Para longitud par `2k`, los centros válidos son `c∈[L+k,R-k]` y exiges `d2[c]≥k`. Cada predicado es monótono en `k`; puedes buscar por separado la mejor longitud de cada paridad con RMQ. Costo `O(log n)` por consulta si el RMQ es `O(1)`.

El intervalo de centros puede estar vacío; ese caso es falso. Buscar directamente sobre longitud mezclando paridades sin separar los predicados puede invalidar la monotonicidad de tu implementación.

**Barridos y Fenwick.** Restricciones sobre extremos de palíndromos pueden convertirse en activaciones de centros por radio o por extremo. La representación de Manacher evita enumerar todos los palíndromos, pero debes encontrar una operación agregada que procese cada intervalo de radios.

**LCE sobre texto y reverso.** El radio de un centro puede expresarse como coincidencia entre una parte invertida y una parte hacia adelante. Esto ofrece una solución determinista con SA+RMQ, útil si ya tienes un índice LCE por otras razones. Manacher suele ser más simple para obtener todos los centros.

### 9.7 Práctica y ejercicios de dominio

- [CSES — Longest Palindrome](https://cses.fi/problemset/task/1111): reconstrucción de un palíndromo máximo.
- [Library Checker — Enumerate Palindromes](https://judge.yosupo.jp/problem/enumerate_palindromes): longitudes máximas por centro; verifica la convención en el [enunciado fuente oficial](https://raw.githubusercontent.com/yosupo06/library-checker-problems/master/string/enumerate_palindromes/task.md).
- **Ejercicio original P1.** Cuenta palíndromos por cada longitud en tiempo lineal.
- **Ejercicio original P2.** Responde si cada uno de `q` intervalos es palíndromo.
- **Ejercicio original P3.** Devuelve la longitud del palíndromo más largo contenido en cada intervalo usando RMQ y búsqueda binaria.
- **Ejercicio original P4.** Maximiza la suma de longitudes de dos palíndromos disjuntos. Diseña el procesamiento de mejores prefijos/sufijos sin enumerar `Θ(n²)` ocurrencias.

**Criterio de dominio:** puedes convertir entre centro, radio e intervalo sin depender de ejemplos memorizados.

<a id="eertree"></a>
## 10. Palindromic Tree / Eertree: un nodo por palíndromo distinto

### 10.1 Concepto e intuición

Manacher agrupa por centro. Eertree agrupa por contenido palindrómico. En `ababa`, los nodos no especiales representan `a`, `b`, `aba`, `bab`, `ababa`.

Al agregar un carácter, todos los palíndromos nuevos deben terminar en ese carácter. Pero solo uno de ellos puede ser un contenido completamente nuevo: el mayor sufijo palindrómico. Cualquier sufijo palindrómico propio suyo también es un prefijo suyo y, por tanto, ya apareció antes del nuevo final.

Así, aunque una posición termine muchos palíndromos, crea a lo sumo un nodo. Esta observación explica por qué una cadena de longitud `n` tiene como máximo `n` palíndromos distintos no vacíos.

### 10.2 Definición formal y propiedades

Hay dos raíces especiales:

- Raíz impar de longitud `-1`: artificio que permite crear palíndromos de longitud uno uniformemente.
- Raíz par de longitud `0`: representa `ε` para extensiones de longitud par.

Para un nodo ordinario `v`:

- `len[v]`: longitud de su palíndromo.
- `next[v][c]`: palíndromo `c + palindrome(v) + c`, cuando existe.
- `link[v]`: mayor sufijo palindrómico propio.
- `last`: mayor sufijo palindrómico del texto procesado.

El link de un palíndromo de longitud uno apunta a la raíz de longitud cero. La raíz de cero apunta a la raíz de `-1`, y esta puede apuntarse a sí misma para terminar búsquedas uniformemente.

Una arista de caracteres agrega dos símbolos, excepto la interpretación especial desde longitud `-1`, que crea un símbolo. No es una transición de matching de izquierda a derecha como en Aho o SAM.

Cada palíndromo no vacío tiene un único padre por arista de caracteres: al quitar sus extremos queda un palíndromo, o una de las raíces especiales. Los suffix links forman otra estructura distinta, orientada a sufijos palindrómicos.

### 10.3 Complejidad

- A lo sumo `n+2` nodos y `n` aristas de caracteres existentes.
- Construcción append-only: `O(n)` amortizado para alfabeto fijo y acceso constante; con mapas balanceados, `O(n log σ)`.
- Memoria: `O(nσ)` con tablas densas, `O(n)` aristas con representación dispersa más sobrecarga.
- Propagación de ocurrencias: `O(n)` con orden apropiado.
- Listar todos los sufijos palindrómicos de cada prefijo: puede costar `Θ(n²)`.
- DP ingenua de partición usando todos esos sufijos: también puede ser cuadrática.

La construcción rápida y una consulta rápida por nodo no justifican recorrer todos los suffix links en cada posición. En `a^n`, hay `i` sufijos palindrómicos en el prefijo de longitud `i`.

### 10.4 Implementación e ideas clave

Sea `pos` el índice del carácter recién agregado. Para extender un nodo `v` de longitud `L`, necesitas:

$$
pos-L-1\ge0\quad\text{y}\quad s[pos-L-1]=s[pos].
$$

Con raíz `L=-1`, el índice es `pos`, así que la comparación siempre coincide y la búsqueda termina.

```text
buscar_extensible(v,pos):
    mientras pos-len[v]-1 < 0
          o s[pos-len[v]-1] != s[pos]:
        v = link[v]
    devolver v

agregar c en pos:
    p = buscar_extensible(last,pos)
    si next[p][c] existe:
        last = next[p][c]
        hits[last]++
        terminar

    crear v con len[v] = len[p]+2
    next[p][c] = v
    si len[v] == 1:
        link[v] = raiz_de_longitud_0
    si no:
        q = buscar_extensible(link[p],pos)
        link[v] = next[q][c]
    last = v
    hits[v]++
```

Al crear un nodo, guarda su posición final para reconstruir una aparición. El destino `next[q][c]` del suffix link ya existe: representa un sufijo palindrómico propio, que también apareció antes como prefijo del nuevo palíndromo.

#### Ocurrencias y cantidad de sufijos

`hits[v]` cuenta cuántas veces `v` fue el mayor sufijo palindrómico, no todas sus ocurrencias. Propaga de mayor longitud a menor:

```text
occ = hits
para v ordinario en orden de len decreciente:
    occ[link[v]] += occ[v]
```

Para el número de sufijos palindrómicos no vacíos de un nodo:

$$
num[v]=1+num[link[v]],
$$

con `num=0` en ambas raíces. Después de cada append, `num[last]` cuenta palíndromos que terminan en la nueva posición. Su suma coincide con la suma de radios de Manacher.

### 10.5 Aplicaciones y usos clásicos

**Número de palíndromos distintos.** Es el número de nodos menos dos. Online, aumenta en uno exactamente cuando se crea un nodo.

**Frecuencia de cada palíndromo.** Usa `occ` después de propagar. Permite maximizar `len[v]*occ[v]`, contar palíndromos que aparecen al menos `k` veces o encontrar el más largo que aparece una sola vez.

**Suma sobre palíndromos distintos.** Como hay un nodo por contenido, puedes sumar funciones de longitud, frecuencia o atributos directamente, sin deduplicación adicional.

**Partición mínima en palíndromos.** Si `dp[i]` es el mínimo número de piezas del prefijo de longitud `i`:

$$
dp[i]=1+\min_{v\text{ sufijo palindrómico de }s[0..i)}dp[i-len[v]].
$$

La recurrencia es correcta pero recorrer toda la cadena de links por posición puede ser cuadrático. Los series links, descritos abajo, son una optimización específica de esta recurrencia.

**Conteo de particiones.** Cambia mínimo por suma, con `dp[0]=1`. La optimización no se transfiere automáticamente a restricciones arbitrarias sobre piezas: debes identificar qué agregado conserva el agrupamiento de longitudes.

**Palíndromos comunes de varios textos.** Se puede trabajar con un Eertree compartido reiniciando adecuadamente el contexto del texto y manteniendo presencia por documento, o utilizar representaciones de contenidos y comparar conjuntos. No permitas que una extensión compare caracteres anteriores al inicio del documento actual. Reiniciar únicamente `last` sin controlar límites de la cadena almacenada puede ser insuficiente.

### 10.6 Técnicas complementarias

**Euler y consultas de ocurrencias.** Guarda el nodo `last` de cada prefijo. Un palíndromo `v` termina en una posición si el estado guardado está en su subárbol del árbol de suffix links. Se reutiliza la reducción a puntos de posición y Euler, con el límite de inicio corregido por `len[v]`.

**Binary lifting.** Si buscas el mayor sufijo palindrómico de longitud a lo sumo `K`, salta por suffix links. Si quieres localizar un palíndromo dado por intervalo, primero verifica que el intervalo sea palíndromo y después localiza su longitud en la cadena de sufijos del prefijo correspondiente.

**Series links: la idea avanzada.** Define `diff[v]=len[v]-len[link[v]]`. Una serie agrupa saltos consecutivos con igual `diff`. El enlace de serie salta a la primera clase anterior con diferencia distinta. Esto permite agrupar candidatos de partición sin recorrer todos los sufijos. La DP estándar de longitud palindrómica con estos enlaces logra `O(n log n)`; la explicación formal y los invariantes temporales de sus acumuladores están en el [artículo original de Rubinchik y Shur](https://arxiv.org/abs/1506.04862). No debe atribuirse tiempo lineal a la simple sustitución de suffix links por series links.

Para implementarla, separa cuidadosamente el valor candidato del prefijo actual y el agregado reutilizado de la serie. Algunos códigos usan información calculada en posiciones anteriores de forma intencional: borrarla por parecer “obsoleta” rompe la recurrencia. Antes de adoptar esa optimización, valida una versión `O(n²)` y compara exhaustivamente cadenas pequeñas.

**Rollback y versiones.** Si solo agregas y deshaces el último carácter, puedes registrar cambios de `last`, creación de nodos y contadores. Sin embargo, las garantías amortizadas de la construcción append-only no se transfieren sin análisis a una exploración con mucho retroceso. Variantes persistentes o con enlaces auxiliares requieren un contrato propio.

### 10.7 Práctica y ejercicios de dominio

- [CSES — Longest Palindrome](https://cses.fi/problemset/task/1111): úsalo para contrastar Eertree con Manacher, aunque sea más estructura de la necesaria.
- [Library Checker — Enumerate Palindromes](https://judge.yosupo.jp/problem/enumerate_palindromes): sirve para validar tu implementación de Manacher como oráculo independiente de conteos; la salida por centros no es la salida nativa de Eertree.
- **Ejercicio original E1.** Imprime el número de palíndromos distintos después de cada append.
- **Ejercicio original E2.** Calcula `max len[v]*occ[v]` y devuelve una aparición del palíndromo óptimo.
- **Ejercicio original E3.** Cuenta ocurrencias de palíndromos completamente contenidas en rangos consultados.
- **Ejercicio original E4.** Implementa partición mínima primero recorriendo todos los sufijos y luego con series links; compara ambas versiones sobre todas las cadenas binarias cortas.
- **Ejercicio original E5.** Cuenta palíndromos distintos que aparecen en todos los documentos de un conjunto pequeño.

**Criterio de dominio:** distingues expansión por ambos extremos de suffix links, y puedes demostrar que cada append crea a lo sumo un nuevo contenido palindrómico.

<a id="lyndon"></a>
## 11. Factorización de Lyndon y algoritmo de Duval

### 11.1 Concepto e intuición

Al trabajar con cadenas circulares, ordenar rotaciones ingenuamente cuesta demasiado. Al trabajar con repeticiones, conviene reconocer bloques que son lexicográficamente canónicos y no esconden una rotación menor. Las palabras de Lyndon proporcionan esas unidades.

Duval factoriza una cadena en palabras de Lyndon usando solo comparaciones y tres índices. Su comportamiento combina orden lexicográfico y periodicidad: cuando dos zonas coinciden, mantiene una repetición candidata; cuando aparece una desigualdad, decide si el bloque puede crecer o si hay que emitir factores.

Es un algoritmo corto cuyo invariante merece más estudio que su longitud de código.

### 11.2 Definición formal y propiedades

Una palabra no vacía `w` es **Lyndon** si es estrictamente menor lexicográficamente que cualquiera de sus sufijos propios no vacíos. Equivalentemente, es primitiva y estrictamente menor que todas sus rotaciones no triviales.

“Primitiva” significa que no es una potencia `u^k` con `k>1`. Sin esa condición, una palabra periódica podría empatar con una rotación y no sería Lyndon bajo la definición estricta.

Ejemplos:

- `a` es Lyndon: no tiene sufijos propios no vacíos.
- `ab` es Lyndon porque `ab<b`.
- `aab` es Lyndon porque es menor que `ab` y `b`.
- `abab` no es Lyndon: tiene una rotación idéntica y su sufijo `ab` es menor.
- `ba` no es Lyndon porque su sufijo `a` es menor.

El teorema de factorización de Chen–Fox–Lyndon establece una descomposición única:

$$
s=w_1w_2\cdots w_k,\qquad w_1\ge w_2\ge\cdots\ge w_k,
$$

donde cada `w_i` es Lyndon. El orden es **no creciente**, y permite factores iguales. Por ejemplo:

```text
banana = b | an | an | a
abbabb = abb | abb
aaaa   = a | a | a | a
```

Una propiedad útil es que si `u` y `v` son Lyndon y `u<v`, entonces `uv` también es Lyndon. Esto ayuda a entender por qué una factorización canónica no puede dejar dos factores adyacentes en orden creciente.

### 11.3 Complejidad

- Duval: `O(n)` comparaciones y `O(1)` memoria auxiliar, sin contar los factores emitidos.
- Guardar intervalos de factores: `O(k)` espacio.
- Copiar todos los factores una sola vez: `O(n)` caracteres totales.
- Rotación mínima mediante una variante de Duval: `O(n)` tiempo y `O(1)` espacio auxiliar si accedes cíclicamente sin materializar `s+s`; `O(n)` espacio si sí lo materializas.

El algoritmo puede comparar caracteres de algunas posiciones más de una vez, pero el trabajo de una fase se carga al bloque que se emite y a un prefijo repetido acotado. El desplazamiento de `i` consume una fracción constante de la zona examinada por esa fase; sumando fases se obtiene linealidad.

### 11.4 Implementación e ideas clave

```text
i = 0
mientras i < n:
    j = i+1
    k = i
    mientras j < n y s[k] <= s[j]:
        si s[k] < s[j]:
            k = i
        si no:
            k++
        j++
    p = j-k
    mientras i <= k:
        emitir intervalo [i,i+p)
        i += p
```

`i` es el inicio no factorizado. `j` explora la derecha. `k` compara contra el inicio de un bloque candidato y sus repeticiones.

Cuando `s[k]<s[j]`, el bloque ha encontrado una desigualdad favorable a su inicio; `k=i` reinicia la comparación del bloque ampliado. Cuando son iguales, `k++` sigue la repetición. Cuando `s[k]>s[j]`, la zona que empieza después ofrece una alternativa menor y la fase debe terminar.

Al terminar, `p=j-k` es la longitud del factor que se emite, posiblemente varias veces. Emitir solo una copia y saltar directamente a `j` pierde factores cuando hay repeticiones parciales.

#### Rotación mínima con Duval sobre la cadena duplicada

Para `n>0`, sea `t=s+s`:

```text
i=0; answer=0
mientras i<n:
    answer=i
    j=i+1; k=i
    mientras j<2*n y t[k]<=t[j]:
        si t[k]<t[j]: k=i
        si no: k++
        j++
    p=j-k
    mientras i<=k:
        i+=p
devolver t[answer..answer+n)
```

La comparación sobre `s+s` permite observar una rotación completa desde cada candidato de la primera copia. El algoritmo descarta bloques de candidatos que no pueden mejorar al representante. Si varias posiciones producen la misma rotación, el contenido mínimo es el mismo; si el problema pide el menor índice entre empates, verifica explícitamente el contrato de la variante que uses.

**No confundas operaciones.** Tomar el primer factor de la factorización de `s` no da en general la rotación mínima. Tampoco basta tomar el sufijo mínimo de `s`: una rotación continúa desde el comienzo cuando llega al final.

### 11.5 Aplicaciones y usos clásicos

**Normalizar cadenas cíclicas.** Representa cada collar por su rotación mínima para comparar equivalencia por rotación. Si también se permiten reflexiones, normaliza tanto `s` como `rev(s)` y toma el menor resultado.

**Factorización canónica.** La lista de factores es única; puede servir como representación estructural para problemas de orden, concatenación y combinatoria de palabras.

**Detectar primitividad.** KMP ya permite comprobar si una cadena es una potencia. Lyndon añade la condición de mínima rotación estricta; ambas propiedades juntas caracterizan las palabras de Lyndon.

**Candidatos de repeticiones máximas.** Las palabras de Lyndon aparecen en algoritmos avanzados de runs. La factorización básica ayuda con la intuición, pero enumerar runs necesita más estructura que aplicar Duval una vez.

**Orden lexicográfico en procesos greedy.** Cuando un problema compara grandes bloques repetidos, un invariante de Lyndon puede justificar saltar candidatos enteros. Antes de aplicar el algoritmo literalmente, demuestra que el orden que usa el problema es el mismo orden lexicográfico sobre el alfabeto.

### 11.6 Técnicas complementarias

**LCE.** Comparaciones entre bloques pueden acelerarse mediante LCE; resulta útil en extensiones de problemas de orden lexicográfico donde Duval estándar no aplica directamente.

**Suffix Array.** Ofrece otra forma de comparar rotaciones usando `s+s` y candidatos de la primera mitad. Es más costosa de construir, pero útil si ya necesitas consultas de sufijos. Los empates entre rotaciones periódicas deben manejarse según el criterio de salida.

**Periodicidad y raíces primitivas.** Primero obtiene la raíz primitiva con `pi`. Todas las rotaciones mínimas equivalentes de una cadena periódica están relacionadas con su período; esto ayuda a resolver empates por posición.

**Pilas monótonas y orden de sufijos.** Variantes de arreglos de Lyndon se relacionan con siguientes sufijos menores. Son herramientas útiles para enumerar candidatos estructurales de repeticiones; no deben confundirse con la lista de factores de Chen–Fox–Lyndon.

### 11.7 Práctica y ejercicios de dominio

- [Library Checker — Lyndon Factorization](https://judge.yosupo.jp/problem/lyndon_factorization): devuelve fronteras de factores; [enunciado fuente oficial](https://raw.githubusercontent.com/yosupo06/library-checker-problems/master/string/lyndon_factorization/task.md).
- [CSES — Minimal Rotation](https://cses.fi/problemset/task/1110): normalización circular en tiempo lineal.
- **Ejercicio original L1.** Enumera todas las cadenas binarias cortas y verifica por fuerza bruta que los factores de Duval son Lyndon y están en orden no creciente.
- **Ejercicio original L2.** Cuenta clases de un conjunto de cadenas bajo rotación y reflexión, normalizando cada una sin hashing polinomial.
- **Ejercicio original L3.** Encuentra todos los índices que producen la rotación mínima y explica su relación con el período primitivo.
- **Ejercicio original L4.** Demuestra la propiedad `u<v ⇒ uv` Lyndon cuando ambos factores son Lyndon.

**Criterio de dominio:** puedes distinguir mínima rotación, palabra primitiva, palabra de Lyndon y factorización en Lyndon; son conceptos relacionados, no sinónimos.

<a id="periodicidad"></a>
## 12. LCE, periodicidad y repeticiones: herramientas para problemas difíciles

### 12.1 Concepto e intuición

Muchos enunciados avanzados preguntan si dos regiones grandes son iguales, cuánto se extiende una repetición o dónde aparece la siguiente discrepancia. LCE proporciona una primitiva determinista para saltar bloques iguales completos.

Periodicidad estudia igualdades entre posiciones separadas por una distancia fija. Si `s[i]=s[i+p]` durante un intervalo largo, ese intervalo está gobernado por un bloque de longitud `p`. Combinar extensiones hacia izquierda y derecha permite obtener toda una región repetitiva a partir de un par de posiciones.

### 12.2 Definición formal y propiedades

Un entero `p`, `1≤p≤|x|`, es período de `x` si:

$$
x[i]=x[i+p]\quad\text{para todo }0\le i<|x|-p.
$$

El período mínimo no tiene que dividir la longitud. Una potencia exacta sí exige divisibilidad por la longitud del bloque.

Un **cuadrado** es una cadena `xx` con `x` no vacía. Una **run** es un intervalo maximal con período mínimo `p`, longitud al menos `2p` y que no puede extenderse un carácter a izquierda ni a derecha conservando ese período dentro del texto.

Un teorema profundo establece que el número de runs de una cadena de longitud `n` es menor que `n`. Esto permite salidas lineales aunque existan cuadráticamente muchas ocurrencias de cuadrados. La demostración y el papel de palabras de Lyndon están en [The Runs Theorem](https://arxiv.org/abs/1406.0263).

**Fine–Wilf.** Si una cadena de longitud `N` tiene períodos `p` y `q`, y:

$$
N\ge p+q-\gcd(p,q),
$$

entonces también tiene período `gcd(p,q)`. La longitud mínima de solapamiento es parte del teorema: dos períodos no implican su gcd sin una condición de tamaño. Puede consultarse esta formulación en [Fine-Wilf graphs and the generalized Fine-Wilf theorem](https://arxiv.org/abs/0906.1780).

La intuición es un grafo de posiciones conectado por diferencias `p` y `q`. Cuando el intervalo es suficientemente largo, las igualdades conectan posiciones de la misma clase módulo `gcd(p,q)`.

### 12.3 Complejidad

- LCE con SA+LCP+Sparse Table: `O(1)` por consulta tras la construcción del índice y `O(n log n)` espacio para el RMQ estándar.
- LCE con Segment Tree: `O(log n)` por consulta y espacio lineal adicional.
- Comprobar que `p` es período de una subcadena: una LCE, después del preprocesamiento.
- Matching con hasta `k` discrepancias por alineación mediante saltos LCE: `O(k+1)` consultas por alineación, por tanto `O(n(k+1))` si cada LCE es constante.
- Enumerar todos los pares de inicios sigue siendo cuadrático, aunque cada consulta individual cueste `O(1)`.

Para runs existen algoritmos especializados lineales; una implementación propia basada en generar demasiados pares puede no acercarse a esa cota. Separa el costo de evaluar un candidato del número de candidatos.

### 12.4 Implementación e ideas clave

Para comprobar período `p` en `s[l..r)` de longitud `L`, con `1≤p≤L`:

$$
p\text{ es período}\iff LCE(l,l+p)\ge L-p,
$$

tratando `p=L` como verdadero sin consultar una posición final fuera del texto. Trunca siempre por el intervalo consultado: la LCE del texto completo podría continuar después de `r`.

Para comparar hacia la izquierda de posiciones `i` y `j`, define:

$$
LCS_{left}(i,j)=\max\{k:s[i-k..i)=s[j-k..j)\}.
$$

Se obtiene con LCE del reverso en posiciones `n-i` y `n-j`, con casos frontera cuando `i=0` o `j=0`. La definición compara caracteres **anteriores** a `i` y `j`; eso evita contar dos veces el carácter central.

Sea `p=j-i`, `a=LCS_left(i,j)` y `b=LCE(i,j)`. Entonces:

$$
s[i-a..j+b)
$$

tiene período `p`, porque cada carácter de la primera región de longitud `a+b` coincide con el desplazado `p` posiciones. Su longitud es `p+a+b`; contiene al menos dos bloques si `a+b≥p`. Que sea una run exige además que `p` sea el período mínimo y maximalidad con ese período.

#### Saltar discrepancias

Para comparar un patrón y una ventana del texto con hasta `k` mismatches:

1. Usa LCE para saltar el siguiente bloque igual.
2. Si terminaste el patrón, acepta.
3. En caso contrario consume una discrepancia y avanza una posición en ambos.
4. Repite hasta terminar o exceder `k`.

Construye un índice conjunto de patrón, separador y texto, y limita cada salto a los caracteres restantes del patrón. Este método maneja sustituciones, no inserciones y borrados; distancia de Hamming y distancia de edición son problemas distintos.

### 12.5 Aplicaciones y usos clásicos

**Ordenar subcadenas dadas por índices.** Un comparador con LCE evita materializarlas; cada comparación consulta un prefijo común y, como mucho, un par de caracteres.

**Encontrar la primera discrepancia.** LCE te da directamente el offset. Si necesitas varias discrepancias, itera saltos.

**Repeticiones alrededor de una frontera.** Mide extensiones a ambos lados de un candidato de período. Es la base de técnicas divide and conquer y enumeración estructurada de cuadrados.

**Consultas de potencia exacta.** Para una longitud de bloque candidata `p`, exige `L%p==0` y la condición de período. Para hallar el período mínimo de muchas subcadenas, probar todos los `p` sigue siendo caro; la factorización de `L` puede reducir candidatos en formulaciones de potencia exacta, con pruebas cuidadosas.

**Subcadenas con exclusiones o pocas modificaciones.** Comparar cadenas que difieren de una referencia en pocos puntos puede resolverse saltando segmentos iguales y atendiendo explícitamente los puntos especiales.

### 12.6 Técnicas complementarias

**DSU y LCP.** Agrupa sufijos por un umbral de coincidencia; una condición de repetición se transforma en una condición sobre distancias entre posiciones de un componente.

**Divide and conquer.** Cada repetición puede asignarse a una frontera relevante. Debes garantizar que la enumeración de candidatos por nivel sea lineal o casi lineal y evitar duplicados.

**Lyndon.** Las raíces de Lyndon permiten seleccionar representantes de runs sin probar todos los períodos en todas las posiciones. Es un tema avanzado para estudiar después de dominar definiciones y consultas LCE.

**Segment Trees sobre posiciones.** Cuando una igualdad de contenido ya produjo un intervalo SA, las restricciones espaciales se resuelven por mínimos, máximos, selección o conteo de posiciones originales.

### 12.7 Práctica y ejercicios de dominio

- [CSES — Finding Periods](https://cses.fi/problemset/task/1733): consolida la definición con repetición final parcial.
- [CSES — Repeating Substring](https://cses.fi/problemset/task/2106): punto de partida para restricciones de solapamiento.
- [Library Checker — Run Enumerate](https://judge.yosupo.jp/problem/runenumerate): objetivo avanzado; consulta el [enunciado fuente oficial](https://raw.githubusercontent.com/yosupo06/library-checker-problems/master/string/runenumerate/task.md).
- **Ejercicio original R1.** Responde si `p` es período de cada intervalo consultado.
- **Ejercicio original R2.** Ordena `q` subcadenas del mismo texto lexicográficamente sin copiarlas.
- **Ejercicio original R3.** Encuentra alineaciones con hasta `k` discrepancias mediante LCE.
- **Ejercicio original R4.** Construye un contraejemplo a “si `p` y `q` son períodos, su gcd también lo es” cuando no se satisface Fine–Wilf.

**Criterio de dominio:** puedes definir exactamente qué extremos cubre una igualdad LCE/LCS y reconocer cuándo una repetición tiene un período no mínimo.

<a id="subsecuencias"></a>
## 13. Autómata de subsecuencias y DP de contenidos distintos

### 13.1 Concepto e intuición

Una subsecuencia conserva orden, pero no exige contigüidad. SAM no es un índice de subsecuencias. Para una cadena fija, la información útil es dónde aparece la próxima copia de cada símbolo después de una posición.

Si quieres reconocer un patrón como subsecuencia, siempre conviene usar la primera posición disponible para cada carácter. Una elección posterior nunca deja más espacio para completar el resto. Ese argumento greedy hace determinista la representación.

### 13.2 Definición formal y propiedades

Define:

$$
nextPos[i][c]=\min\{j\ge i:s[j]=c\},
$$

con valor `n` si no existe. El estado `i` significa que solo puedes usar posiciones desde `i` en adelante. Leer `c` te lleva a `nextPos[i][c]+1`; si no existe, rechazas.

Las transiciones válidas aumentan estrictamente el estado, así que el autómata es un DAG sobre posiciones `0,...,n`. Cada cadena reconocida sigue su embedding greedy único. Puede tener muchos embeddings en el texto, pero el autómata la recorre una sola vez desde el estado inicial.

### 13.3 Complejidad

- Tabla densa de siguientes apariciones: `O(nσ)` tiempo y espacio.
- Consultar subsecuencia de longitud `m`: `O(m)`.
- Listas de posiciones por símbolo + búsqueda binaria: `O(m log n)` por consulta y `O(n)` espacio de posiciones.
- Conteo de subsecuencias distintas con la recurrencia de última aparición: `O(n)` tiempo y `O(σ)` memoria para el acumulado necesario, además de la representación de símbolos.

El número de subsecuencias distintas puede ser exponencial. Para conteo exacto, la complejidad aritmética de enteros gigantes no es `O(1)`; en concursos se suele pedir módulo o selección con saturación.

### 13.4 Implementación e ideas clave

Construye `nextPos` de derecha a izquierda: copia la fila `i+1` y modifica la columna de `s[i]`. La fila `n` tiene todos los símbolos ausentes.

Para contar subsecuencias distintas, incluyendo la vacía, sea `D[i]` el conteo en el prefijo de longitud `i`. Si el carácter nuevo en posición `i-1` no apareció antes, `D[i]=2D[i-1]`. Si apareció por última vez en posición de índice `j`:

$$
D[i]=2D[i-1]-D[j].
$$

El término restado cuenta exactamente las cadenas que ya podían obtenerse al anexar ese carácter en su aparición anterior. Con notación de posición anterior 1-indexada `p=j+1`, la misma fórmula resta `D[p-1]`. No mezcles las dos convenciones.

En `aa`: `D[0]=1`, `D[1]=2`, `D[2]=4-D[0]=3`, correspondientes a `ε,a,aa`.

Para memoria reducida, guarda por símbolo el valor anterior `D[j]` que debe restarse al volver a verlo. En aritmética modular, normaliza resultados negativos.

### 13.5 Aplicaciones y usos clásicos

**Muchas consultas de subsecuencia.** Recorre el autómata greedy por cada patrón.

**Subsecuencia distinta ausente más corta.** Desde el estado `i`, una letra ausente termina una cadena que no puede reconocerse; una letra presente lleva a un estado mayor. Una DP de mínima longitud, análoga a la de cadena ausente en SAM, encuentra la menor cadena que no es subsecuencia. Son problemas distintos: “no es subcadena” y “no es subsecuencia” producen respuestas diferentes.

**k-ésima subsecuencia distinta.** Cuenta caminos etiquetados en el DAG determinista y selecciona por etiquetas ordenadas. Excluye o incluye `ε` según el enunciado.

**Subsecuencias bajo restricciones de patrones.** Combina el estado de posición con un autómata que reconozca propiedades de la subsecuencia construida. La secuencia original aporta disponibilidad; el segundo componente aporta restricciones sobre el contenido elegido.

### 13.6 Técnicas complementarias

**DP con Aho/KMP.** El producto sigue siendo DAG porque avanza la posición del texto. Puedes contar contenidos distintos que evitan patrones, siempre que uses el embedding greedy único y no una DP que enumere todos los embeddings.

**Listas y binary search.** Reduce memoria cuando el alfabeto es grande y el volumen de consultas permite un logaritmo por símbolo.

**Bitsets.** Para LCS y algunas DPs de subsecuencias existen aceleraciones por operaciones de palabra. Son técnicas adicionales: la tabla `nextPos` por sí sola no resuelve LCS de dos cadenas en tiempo lineal.

### 13.7 Práctica y ejercicios de dominio

- [CSES — Distinct Subsequences](https://cses.fi/problemset/task/1149): resta de duplicados por última aparición.
- [CSES — Shortest Subsequence](https://cses.fi/problemset/task/1087): contenido ausente bajo la relación de subsecuencia.
- **Ejercicio original Q1.** Responde un millón de consultas cortas de subsecuencia sobre texto fijo; compara tabla densa y listas de posiciones.
- **Ejercicio original Q2.** Construye la k-ésima subsecuencia distinta de longitud exactamente `L`.
- **Ejercicio original Q3.** Cuenta subsecuencias distintas que evitan `aba` y explica por qué contar elecciones de índices sobrecuenta.

**Criterio de dominio:** puedes justificar la elección greedy de posiciones y distinguir contenidos de embeddings.

<a id="bwt"></a>
## 14. Burrows–Wheeler y búsqueda hacia atrás

### 14.1 Concepto e intuición

La transformada de Burrows–Wheeler (BWT) reorganiza los caracteres del texto usando el orden de sus sufijos/rotaciones. No comprime por sí misma, pero tiende a agrupar símbolos relacionados por contextos. Su conexión con SA permite búsquedas de patrones de derecha a izquierda mediante conteos de caracteres. La transformada original y su motivación se presentan en el [informe de Burrows y Wheeler](https://www.cs.jhu.edu/~langmea/resources/burrows_wheeler.pdf).

Para competencia es una extensión útil cuando un problema pide reconstruir un texto transformado o mantener intervalos de sufijos sin comparar directamente todo el patrón.

### 14.2 Definición formal y propiedades

Sea `S=s+$`, donde `$` es único y menor que todos los caracteres reales, y `N=|S|`. Define:

$$
BWT[r]=S[(SA[r]-1+N)\bmod N].
$$

Es el carácter inmediatamente anterior al sufijo del rango `r`, interpretado cíclicamente. Para `banana$`:

```text
SA  = [6,5,3,1,0,4,2]
BWT = annb$aa
```

Define `C[c]` como el número de símbolos de `S` estrictamente menores que `c`, y `Occ(c,r)` como el número de apariciones de `c` en `BWT[0..r)`.

La correspondencia last-to-first es:

$$
LF(r)=C[BWT[r]]+Occ(BWT[r],r).
$$

Ordenar establemente apariciones del mismo símbolo conserva el orden de sus contextos. Por eso la k-ésima aparición de `c` en la última columna corresponde a la k-ésima aparición de `c` en la primera columna.

### 14.3 Complejidad

- Crear BWT desde SA: `O(n)` adicional.
- Invertir BWT con conteos de símbolos y LF: `O(n+σ)` para alfabeto entero compacto, más la salida.
- Tabla densa de prefijos `Occ`: `O(nσ)` tiempo y espacio; consultas `O(1)`.
- Wavelet Tree/Matrix: consultas de rango/rank típicamente `O(log σ)` con espacio dependiente de la representación.
- Búsqueda hacia atrás de patrón de longitud `m`: `O(m)` con rank constante, o `O(m log σ)` con Wavelet Tree/Matrix.

Contar coincidencias y localizar todas sus posiciones son operaciones distintas. Un índice que conoce solo el intervalo final necesita SA o muestras de SA y pasos LF adicionales para devolver posiciones.

### 14.4 Implementación e ideas clave

Si `[l,r)` es el intervalo de sufijos que empiezan con `P`, el intervalo correspondiente a `cP` es:

$$
[C[c]+Occ(c,l),\ C[c]+Occ(c,r)).
$$

Empieza con `[0,N)` y procesa el patrón de derecha a izquierda. Si el intervalo queda vacío, no hay ocurrencias. Para un patrón sin centinela, el tamaño final cuenta apariciones dentro del texto original.

Para invertir, construye LF identificando cada aparición por símbolo y número de ocurrencia. Empieza en la fila cuyo sufijo inicia en cero, identificable porque su BWT es el centinela, y sigue LF colocando caracteres en orden inverso según la convención adoptada. Verifica con `banana$` y una cadena de un solo carácter; invertir dirección o incluir dos veces el centinela son errores frecuentes.

Si el formato no usa un centinela único, normalmente debe proporcionar un índice primario para recuperar la rotación original. La invertibilidad depende de esa información adicional.

### 14.5 Aplicaciones y usos clásicos

- Reconstrucción del texto a partir de BWT.
- Conteo de patrones mediante búsqueda hacia atrás.
- Comprensión de índices comprimidos y del papel de `rank` sobre secuencias.
- Procesar consultas que agregan caracteres por la izquierda: cada paso actualiza un intervalo.

No es la primera opción para matching ordinario con un texto que ya tienes en memoria y pocas consultas. Su valor competitivo está en problemas que exponen la transformada o requieren operaciones sobre el índice mismo.

### 14.6 Técnicas complementarias

**SA.** Proporciona una construcción directa y permite localizar posiciones del intervalo final.

**Wavelet Matrix.** Responde `Occ(c,r)` y otras consultas de frecuencias sobre BWT sin reservar una columna completa por símbolo.

**Muestreo y LF.** Guardar posiciones de SA en algunas filas permite recuperar otras caminando por LF; el espacio ahorrado se paga en pasos de localización. Explica el esquema de muestreo antes de afirmar una cota de consulta.

**Runs en BWT.** La compresión por rachas de BWT tiene aplicaciones en textos repetitivos. Estas rachas son secuencias de caracteres iguales en BWT, y no son las runs de periodicidad del texto original definidas en el capítulo anterior.

### 14.7 Práctica y ejercicios de dominio

- [CSES — String Transform](https://cses.fi/problemset/task/1113): reconstrucción de una transformación de cadenas; revisa sus convenciones de centinela.
- **Ejercicio original B1.** Construye BWT a partir de SA e inviértela; exige recuperar exactamente el texto original.
- **Ejercicio original B2.** Implementa búsqueda hacia atrás y compara frecuencias con KMP para patrones aleatorios.
- **Ejercicio original B3.** Sustituye la tabla densa `Occ` por listas de posiciones por símbolo y analiza el logaritmo añadido.

**Criterio de dominio:** puedes derivar LF a partir de orden estable y actualizar intervalos semiabiertos sin errores de una unidad.

<a id="taller"></a>
## 15. Taller de reducciones avanzadas

Los siguientes casos son problemas de diseño originales para esta guía. La meta es practicar la transición de un enunciado a una estructura y una prueba. Antes de leer cada solución, intenta identificar qué se cuenta y qué información se debe conservar.

### 15.1 Caso I: apariciones de una subcadena dentro de otra región

**Problema.** Se fija un texto `s` de longitud `n`. Cada consulta da `(l,r,a,b)` y pide cuántas veces aparece `s[l..r)` completamente dentro de `s[a..b)`. Los patrones se especifican por índices; leer todos sus caracteres en cada consulta puede ser demasiado costoso.

Sea `L=r-l>0`. Si `L>b-a`, responde cero.

**Solución con SA.** Localiza `rank[l]`. Mediante RMQ sobre LCP y búsquedas binarias encuentra el intervalo `[x,y)` de sufijos que comparten los primeros `L` caracteres con el sufijo `l`. Ahora los inicios válidos deben satisfacer:

$$
a\le SA[t]\le b-L.
$$

Por tanto, cuentas puntos `t∈[x,y)` con `SA[t]∈[a,b-L+1)`. Un Wavelet Tree/Matrix sobre el arreglo `SA` responde la consulta de valores dentro del rango de índices. También sirve persistencia por rangos SA.

**Complejidad.** Con Sparse Table, encontrar `[x,y)` cuesta `O(log n)`. Una estructura de consultas de rangos por valores agrega típicamente `O(log n)`. El preprocesamiento depende de la representación elegida y del SA.

**Solución con SAM.** Localiza el estado de `s[l..r)` subiendo desde `pref[r-1]` con binary lifting hasta el estado cuyo intervalo contiene `L`. Ahora cuenta posiciones finales `i` tales que:

$$
a+L-1\le i<b
$$

y `pref[i]` pertenece al subárbol del estado encontrado. Es otra consulta rectangular sobre índice temporal y Euler del árbol de links.

**Prueba de equivalencia.** SA agrupa por posiciones iniciales; SAM agrupa por posiciones finales. Un intervalo de longitud `L` transforma una coordenada en otra sumando `L-1`. El contenido se reconoce por intervalo SA o por clase `endpos`, respectivamente.

**Error típico.** Restringir solo el inicio a `[a,b)` permite que la ocurrencia termine fuera de la región. Restringir finales a `[a,b)` sin desplazar el extremo izquierdo permite que empiece antes de `a`.

### 15.2 Caso II: subcadena más larga con dos ocurrencias disjuntas

**Problema.** Encuentra el mayor `L` para el que existen dos intervalos disjuntos de longitud `L` y contenido idéntico.

**Solución SA por factibilidad.** Para una longitud candidata `L`, une rangos adyacentes cuando su LCP es al menos `L`. Dentro de un grupo todos los sufijos comparten el prefijo de longitud `L`. Hay dos ocurrencias disjuntas si y solo si:

$$
maxStart-minStart\ge L.
$$

Los extremos bastan porque son el par con máxima separación. La factibilidad es monótona: dos ocurrencias de longitud `L` producen ocurrencias disjuntas de toda longitud menor. Puedes buscar `L` con búsqueda binaria y barridos de SA.

**Solución SAM directa.** Propaga `minEnd[v]` y `maxEnd[v]` desde posiciones base. Todas las cadenas de una clase tienen los mismos finales, por lo que para una longitud `L` de su intervalo existen dos ocurrencias disjuntas si:

$$
maxEnd[v]-minEnd[v]\ge L.
$$

El mejor candidato del estado es:

$$
candidate[v]=\min(len[v],maxEnd[v]-minEnd[v]).
$$

Solo es válido si `candidate[v]≥minlen[v]`. Maximiza entre estados válidos. Después de construir y ordenar por longitud, el trabajo adicional es lineal.

**Lección.** SAM hace especialmente naturales condiciones uniformes sobre posiciones finales. La distancia entre extremos controla disjunción sin enumerar pares de ocurrencias.

### 15.3 Caso III: sumar el LCP de todos los pares de sufijos

**Problema.** Calcula:

$$
\sum_{0\le i<j<n}LCE(i,j).
$$

Hay cuadráticamente muchos pares, así que consultar cada uno no basta.

**Reducción.** El SA forma un camino cuyos pesos de arista son LCP. La LCE entre dos rangos es el mínimo peso en su camino. Ordena aristas por peso decreciente y une componentes con DSU.

Cuando una arista de peso `w` une componentes de tamaños `a` y `b`, exactamente `a*b` pares de sufijos pasan a estar conectados. Para cada uno, el mínimo en su camino es `w`: antes no se conectaban usando aristas de peso mayor, y ahora sí usando aristas de peso al menos `w`.

Agrega:

$$
wab.
$$

Empates de peso pueden procesarse en cualquier orden para esta suma: todos los nuevos pares creados dentro de ese nivel tienen el mismo mínimo `w`. En otras aplicaciones que preguntan el estado “antes del umbral”, quizá necesites procesar un grupo de pesos simultáneamente.

**Complejidad.** `O(n log n)` por ordenar pesos, o se puede aprovechar que LCP es entero entre cero y `n`; las uniones cuestan casi lineal. La respuesta puede crecer como `Θ(n³)`, así que evalúa límites numéricos.

**Extensión.** Si cada sufijo tiene un peso `w_i` y cada par contribuye `w_i*w_j*LCE(i,j)`, guarda suma de pesos por componente en lugar del tamaño. Si se requieren colores distintos, guarda estadísticas por color y resta pares del mismo color, analizando el costo de fusionar esas estadísticas.

### 15.4 Caso IV: generar una cadena óptima con patrones positivos y negativos

**Problema.** Cada palabra de un diccionario tiene un peso, posiblemente negativo. Construye una cadena de longitud `L` sobre un alfabeto fijo que maximice la suma de pesos de todas sus ocurrencias.

**Reconocimiento.** Aho identifica qué patrones terminan en cada paso. Precalcula `gain[v]` sumando pesos propios y los de sus fallos.

**DP.** `best[i][v]` almacena el mejor puntaje de una cadena de longitud `i` con estado final `v`. Cada letra agrega `gain[go[v][c]]`. Inicializa solo la raíz con cero y los demás estados con `-∞`.

**Reconstrucción.** Si `L` es moderado, guarda predecesores. Para obtener la menor lexicográficamente entre las óptimas, calcula una DP de ganancia futura y elige la primera letra que preserve el óptimo restante. Elegir el menor predecesor local durante la DP hacia adelante no garantiza siempre el desempate global deseado.

**Longitud enorme.** Matriz max-plus. La entrada `(u,v)` es la mayor ganancia de una transición por un carácter que lleve de `u` a `v`, o `-∞` si no existe. Para optimizar basta el máximo sobre letras equivalentes; para contar cuántas cadenas logran el óptimo debes conservar además multiplicidades y combinarlas correctamente.

**Lección.** La estructura de reconocimiento no cambia al pasar de contar a optimizar; cambian las operaciones y el significado de imposibilidad.

### 15.5 Caso V: distinguir ocurrencias, pares y cadenas distintas

**Problema A.** Suma el número de ocurrencias de todas las subcadenas distintas del texto.

Cada intervalo no vacío corresponde a una ocurrencia de exactamente un contenido, así que la respuesta es `n(n+1)/2`. SAM ofrece la identidad:

$$
\sum_{v\ne root}(len[v]-len[link[v]])\,occ[v]
=\frac{n(n+1)}2.
$$

Esta igualdad es excelente para verificar frecuencias y clones.

**Problema B.** Cuenta pares no ordenados de ocurrencias del mismo contenido, permitiendo solapamiento.

Cada cadena de frecuencia `f` aporta `f(f-1)/2`. Como la frecuencia es uniforme en una clase:

$$
\sum_{v\ne root}(len[v]-len[link[v]])
\binom{occ[v]}2.
$$

**Problema C.** Exige que las dos ocurrencias no se solapen.

La fórmula anterior ya no basta. La frecuencia no describe distancias entre posiciones. Incluso `minEnd` y `maxEnd` solo deciden existencia de un par separado, no cuentan todos los pares separados. Necesitas una estructura o procesamiento sobre el conjunto ordenado de posiciones y la longitud.

**Lección.** Una clase de SAM preserva `endpos`, pero almacenar solamente `|endpos|` descarta información. La estructura matemática contiene más de lo que tus metadatos implementados guardan.

### 15.6 Caso VI: longest common substring de todos los documentos

**Problema.** Dados documentos `s_1,...,s_k`, encuentra la mayor cadena contigua que aparece en todos.

**SA generalizado.** Concatena con separadores distintos. Cada sufijo válido tiene un color. Mantén una ventana en orden SA con al menos un sufijo de cada color. Su prefijo común tiene longitud igual al mínimo LCP de las aristas internas.

Cuando la ventana cubre todos los colores, intenta reducirla por la izquierda manteniendo cobertura; evalúa las ventanas durante el proceso. Una deque mantiene el mínimo de LCP mientras ambos extremos avanzan. El caso `k=1` se resuelve devolviendo el documento completo.

**Por qué sirve una ventana.** Si una cadena aparece en todos los documentos, todos los sufijos que comienzan con ella forman un intervalo SA que contiene todos los colores. Una ventana que cubra los colores dentro de ese intervalo tendrá mínimo LCP al menos su longitud. Recíprocamente, el prefijo común de una ventana con todos los colores aparece en todos los documentos.

**SAM de referencia.** Construye SAM de un documento y procesa los demás, intersectando máximas longitudes realizables por estado. Es conveniente si uno de los documentos es muy corto. La cota incluye un barrido por estados para cada documento; con muchos documentos diminutos puede importar.

**Lección.** La misma existencia común se expresa como cobertura de colores en SA o intersección de longitudes por clases en SAM. Escoger depende del tamaño y del tipo de consultas adicionales.

### 15.7 Caso VII: palíndromo más largo dentro de cada rango

**Problema.** El texto es estático y hay muchas consultas `[L,R)`.

Manacher conoce la máxima extensión en todo el texto. Un centro puede tener un palíndromo enorme que sale del rango de la consulta; tomar el máximo radio entre centros internos no basta.

Para longitud impar `2k-1`, el centro debe estar entre `L+k-1` y `R-k`, y su radio debe ser al menos `k`. Con RMQ de máximos sobre `d1`, el predicado se decide en constante. Es monótono en `k`: un palíndromo largo contiene uno más corto con el mismo centro, y el conjunto de centros permitidos se amplía al reducir el radio.

Resuelve pares por separado usando centros entre `L+k` y `R-k`. Busca el máximo `k` de cada paridad. El mejor de ambos da la respuesta. Para devolver el intervalo, el RMQ debe permitir recuperar algún índice que alcanza un radio suficiente, o hacer una búsqueda adicional de centro.

**Lección.** Una estructura que da información global suele necesitar truncamiento geométrico para responder consultas locales. El radio y el intervalo de centros deben cambiar juntos.

### 15.8 Caso VIII: elegir la estructura durante un contest

Supón que hay un texto fijo de longitud `2·10^5` y `2·10^5` patrones, cuya longitud total es `2·10^5`. Se pide frecuencia de cada patrón. Aho es natural: el tamaño de entrada es lineal en la suma de longitudes y se procesa el texto una vez. SA también sirve, pero introduce búsquedas por patrón y no aprovecha del mismo modo que todo el diccionario es conocido.

Ahora cambia las consultas: los patrones se dan como intervalos de ese mismo texto y pueden tener longitud `10^5` cada uno. Leerlos explícitamente podría sumar `10^10` caracteres que ni siquiera aparecen escritos en la entrada. SA+LCE o SAM+binary lifting aprovechan la representación comprimida de cada patrón por dos índices.

Ahora se pide la k-ésima subcadena distinta. Aho de patrones consultados deja de ser la representación adecuada porque el universo de candidatos no está dado como diccionario. SA o SAM organizan ese universo implícito.

Finalmente, se cambia un carácter arbitrario entre consultas. El índice estático ya no conserva su validez. Necesitas otra estrategia, reconstrucción por bloques o restricciones adicionales del problema. Una plantilla sofisticada no sustituye el análisis del modelo de actualizaciones.

<a id="ruta"></a>
## 16. Ruta de entrenamiento: de herramientas a criterio competitivo

### 16.1 Plan de seis semanas

El ritmo depende de tu experiencia. Una sesión sugerida combina 30–60 minutos de teoría, 45–90 minutos de implementación o demostración y un problema con posterior análisis. Algunos retos avanzados necesitarán varias sesiones.

| Semana | Núcleo | Entregable de aprendizaje |
|---|---|---|
| 1 | Notación, trie, KMP, Z | Plantillas verificadas; bordes y períodos explicados sin apuntes |
| 2 | Aho-Corasick y DP de autómatas | Conteos por propagación y activaciones por árbol de fallos |
| 3 | SA, LCP, RMQ, consultas geométricas | LCE, selección lexicográfica y conteos en rangos |
| 4 | SAM y Suffix Tree | Clones, `endpos`, árbol de links y traducción entre estructuras |
| 5 | Manacher, Eertree, Lyndon | Palíndromos por centros/contenido y rotación mínima |
| 6 | Taller, productos de autómatas, periodicidad | Soluciones completas a problemas mixtos y simulacro |

No esperes seis semanas para resolver problemas. Cada capítulo debe alternarse con implementación y práctica; posponer todo el código hasta el final genera una falsa sensación de dominio.

### 16.2 Orden concreto de problemas oficiales

Los enlaces siguientes son un itinerario propuesto; las páginas oficiales definen sus enunciados. No todos exigen la técnica que sugiero, y usar otra solución correcta es parte del aprendizaje.

| Paso | Problema | Objetivo sugerido |
|---:|---|---|
| 1 | [String Matching](https://cses.fi/problemset/task/1753) | Implementar KMP y Z independientemente |
| 2 | [Finding Borders](https://cses.fi/problemset/task/1732) | Traducir borde ↔ cadena de links |
| 3 | [Finding Periods](https://cses.fi/problemset/task/1733) | Evitar asumir divisibilidad |
| 4 | [String Functions](https://cses.fi/problemset/task/2107) | Validar arreglos auxiliares |
| 5 | [Word Combinations](https://cses.fi/problemset/task/1731) | Trie + DP y costo de transiciones |
| 6 | [A Lot of Games](https://codeforces.com/problemset/problem/455/B) | Estado de juego suficiente |
| 7 | [Required Substring](https://cses.fi/problemset/task/1112) | Autómata KMP dentro de DP |
| 8 | [Finding Patterns](https://cses.fi/problemset/task/2102) | Construir Aho completo |
| 9 | [Counting Patterns](https://cses.fi/problemset/task/2103) | Evitar enumerar todos los matches |
| 10 | [Pattern Positions](https://cses.fi/problemset/task/2104) | Cambiar la operación de propagación |
| 11 | [Suffix Array](https://judge.yosupo.jp/problem/suffixarray) | Verificar construcción robusta |
| 12 | [Distinct Substrings](https://cses.fi/problemset/task/2105) | Resolver con SA y después SAM |
| 13 | [Repeating Substring](https://cses.fi/problemset/task/2106) | Comparar LCP y frecuencia de estado |
| 14 | [Substring Order I](https://cses.fi/problemset/task/2108) | Selección por bloques |
| 15 | [Substring Order II](https://cses.fi/problemset/task/2109) | Distinguir multiplicidades |
| 16 | [Substring Distribution](https://cses.fi/problemset/task/2110) | Contribuciones por rangos de longitudes |
| 17 | [Longest Palindrome](https://cses.fi/problemset/task/1111) | Manacher y reconstrucción |
| 18 | [Enumerate Palindromes](https://judge.yosupo.jp/problem/enumerate_palindromes) | Verificar ambas paridades |
| 19 | [Lyndon Factorization](https://judge.yosupo.jp/problem/lyndon_factorization) | Invariante de Duval |
| 20 | [Minimal Rotation](https://cses.fi/problemset/task/1110) | Canonización de cadenas cíclicas |
| 21 | [Distinct Subsequences](https://cses.fi/problemset/task/1149) | Restar contenidos duplicados |
| 22 | [Shortest Subsequence](https://cses.fi/problemset/task/1087) | Autómata de siguientes posiciones |
| 23 | [String Transform](https://cses.fi/problemset/task/1113) | BWT y orden estable |
| 24 | [Duff is Mad](https://codeforces.com/problemset/problem/587/F) | Consultas avanzadas y procesamiento offline |
| 25 | [Run Enumerate](https://judge.yosupo.jp/problem/runenumerate) | Proyecto avanzado de periodicidad |

### 16.3 Cómo usar problemas sencillos para entrenar nivel alto

Un problema básico puede generar cinco entrenamientos diferentes:

1. Resuélvelo con la herramienta natural.
2. Implementa una segunda estructura con una representación distinta.
3. Demuestra que ambas fórmulas coinciden.
4. Cambia una restricción: rangos, pesos, multiplicidad, consultas online.
5. Explica cuándo la segunda estructura deja de ser apropiada.

Por ejemplo, Distinct Substrings conecta la suma de nuevos prefijos en SA, los intervalos de longitudes en SAM y las longitudes de aristas válidas del Suffix Tree. Esa equivalencia desarrolla comprensión transferible a problemas nuevos.

### 16.4 Qué llevar al notebook

Para cada plantilla guarda junto al código:

- Contrato de entrada: alfabeto, vacío, centinela, múltiples casos.
- Significado de cada arreglo y convención de índices.
- Complejidad real, incluido tamaño de transición.
- Funciones que requieren postprocesamiento previo.
- Tres ejemplos mínimos que detecten errores estructurales.
- Una advertencia sobre la confusión más peligrosa.

Ejemplos de advertencias útiles: “SAM: clones con conteo base cero”; “Aho: salidas heredadas”; “SA: rango ausente distinto de rango válido”; “KMP: fila del estado `m`”; “Manacher: centro par entre `i-1` e `i`”.

### 16.5 Simulacro de reconocimiento

Sin programar, dedica 2–3 minutos a cada pregunta y escribe estructura, metadatos y complejidad:

1. ¿Cuántas palabras activas terminan en cada posición de un flujo?
2. ¿Cuál es la k-ésima subcadena distinta de un texto?
3. ¿Cuál es la k-ésima contando repeticiones?
4. ¿Cuántos prefijos de una palabra aparecen dentro de ella?
5. ¿Qué subcadena aparece en todos los documentos?
6. ¿Cuál es la mayor subcadena con dos apariciones disjuntas?
7. ¿Cuántos palíndromos distintos hay después de cada append?
8. ¿Cuántas cadenas de longitud enorme evitan un diccionario pequeño?
9. ¿Cuál es la menor rotación de una cadena circular?
10. ¿Cuántas apariciones de un patrón caen por completo dentro de un intervalo?

Respuestas esperadas a nivel de diseño: Aho+Euler; SA/SAM; SAM ponderado u otra indexación de multiplicidades; árbol de bordes/Z; SA coloreado o SAM de referencia; extremos de posiciones; Eertree; autómata+matriz; Duval; intervalo SA o árbol de links con consulta bidimensional.

El ejercicio no termina al acertar el nombre. Debes explicar por qué sus estados conservan exactamente la información solicitada.

<a id="auditoria"></a>
## Apéndice A. Revisión técnica de tus referencias

Esta revisión distingue defectos observables, contratos incompletos y mejoras de robustez. No pretende certificar integralmente las implementaciones ni convertir fragmentos de notebook en bibliotecas independientes. Los originales se conservaron intactos.

### A.1 Material consultado y notación conservada

- [Referencia_ICPC.pdf](/Users/amgl/Data-structures-and-algorithms/Referencia_ICPC.pdf), sección 17, páginas impresas 12–14.
- [strings.tex](/Users/amgl/Data-structures-and-algorithms/sections/strings.tex).
- [aho.cpp](/Users/amgl/Data-structures-and-algorithms/latex_src/strings/aho-corasick/aho.cpp).
- [kmp.cpp](/Users/amgl/Data-structures-and-algorithms/latex_src/strings/KMP/kmp.cpp).
- [suffix_array.cpp](/Users/amgl/Data-structures-and-algorithms/latex_src/strings/suffix_array/suffix_array.cpp).

El PDF y el `.tex` son referencias compactas; esta guía amplía sus contratos. En particular, `lcp[i]` sigue significando comparación del sufijo de rango `i` con el de rango `i-1`, y `len` en SAM sigue siendo longitud máxima de la clase.

### A.2 KMP: el estado final necesita una política explícita

La función `prefix_function` mostrada sigue el algoritmo estándar. En cambio, hay dos variantes diferentes del autómata en el material:

**En `strings.tex` y el PDF**, `compute_automaton` recibe `const string &s` e intenta ejecutar `s += '#'`. Eso intenta modificar una referencia constante y no compila tal como está escrito. Una solución es trabajar con una copia local o pasar por valor; otra, más explícita, construir `m+1` filas sin concatenar un separador, como en esta guía.

**En `kmp.cpp`**, ya no aparece la concatenación, pero se reservan `m` filas y una transición puede devolver `m`. Si el llamador intenta después consultar `aut[m][c]`, accede fuera de las filas reservadas.

Esto no significa que todo uso del fragmento sea inválido: puede funcionar si el llamador detecta el match y normaliza inmediatamente el estado a `pi[m-1]`. El problema es que el contrato no está expresado en la función. Para DP de longitud y reutilización general, una fila explícita para `m` suele reducir errores.

**Prueba mínima de contrato:** patrón `a`, texto `aa`. Deben detectarse dos coincidencias sin acceder a una fila inexistente. Prueba también `aaa` en `aaaaa` para solapamientos.

### A.3 Aho-Corasick: enlace de salida incompleto

La función `get_terminal_link` del archivo y los apuntes recurre directamente a `get_terminal_link(get_link(u))`, sin comprobar si `get_link(u)` ya es terminal. Como los casos base devuelven cero y no existe una rama que devuelva un terminal no raíz, se pierden esas salidas.

Se verificó con un programa mínimo que conserva la implementación y agrega únicamente encabezados/contexto para ejecutarla:

```text
Patrones insertados: he, she
Estado tras leer she: 5
get_link(5):          2   (nodo de he)
get_terminal_link(5): 0   (se pierde he)
```

La lógica esperada para un enlace de salida **propio** es:

```text
u = get_link(v)
si u es terminal: devolver u
si no: devolver enlace_de_salida(u)
```

con el caso base correspondiente a la raíz y a la política sobre patrones vacíos. Al reportar, procesa además el terminal del estado actual; el enlace propio no lo incluye.

**Otros contratos relevantes.** `terminal` es booleano: identifica existencia de una palabra, pero no almacena sus IDs ni multiplicidad. Si hay patrones duplicados, necesitas una lista o mapear cada ID a su terminal. La memorización de `go` y `link` presupone que no se insertan nuevas palabras después de empezar a resolver esas funciones. Una nueva palabra puede invalidar transiciones y fallos memorizados.

La versión recursiva también puede alcanzar profundidad proporcional a longitudes de patrones en casos adversos. Una BFS explícita hace más sencillo controlar el orden y evita depender de la pila del proceso.

### A.4 Suffix Array: rango ausente, límites y costo de comparación

**Confusión de rango cero.** El código usa rango cero para posiciones fuera del texto durante counting sort, pero también asigna cero al menor rango válido al reconstruir clases. En una versión sin centinela esas claves deben distinguirse.

Se ejecutó el constructor original aislado, agregando solo encabezados y un `main` mínimo, sobre `aaa`:

```text
Resultado observado: [2,0,1]
Resultado correcto:  [2,1,0]

Sufijos correctos: a < aa < aaa
```

Este contraejemplo corresponde al contrato de recibir directamente el texto sin centinela. Un llamador que agregue un centinela único puede evitar ese caso particular; ese requisito debe documentarse y no corrige por sí mismo los accesos sin límites descritos a continuación.

**Accesos a segunda mitad.** La reasignación de rangos consulta `mrank[SA[i]+k]` y `mrank[SA[i-1]+k]` sin comprobar el límite lógico `n`. Aunque algunos accesos caigan dentro del arreglo global físicamente reservado, pueden leer valores que no representan el bloque ausente. Con tamaños cercanos a la capacidad, el índice puede además superar la capacidad física. En múltiples casos, datos residuales complican aún más el comportamiento.

Recomendación conceptual: usa `key(i)=rank[i]` si `i<n` y cero en caso contrario, con rangos válidos desde uno. Aplica exactamente la misma convención tanto al ordenar como al comparar pares.

**Alfabeto implícito.** `str[i]-'#'` y la cota de frecuencias usada presuponen un rango limitado de símbolos. Para una plantilla general, comprime símbolos o mapea bytes de forma explícita. Caracteres menores que `'#'` pueden dar claves negativas.

**Copias en comparadores.** `s.substr(idx).compare(...)` construye un sufijo completo antes de limitar la comparación al patrón. Por ello, la búsqueda no tiene el costo esperado `O(m log n)` de comparar solo hasta `m` caracteres: las copias pueden costar `O(n log n)` por consulta en el peor caso. Usa acceso por índice, `string_view` con semántica apropiada o la sobrecarga de `compare` que recibe posición y longitud sin crear primero `substr`.

**Dependencia externa.** Los comparadores usan una variable `s` que no se declara en el fragmento individual. Puede ser parte del template del equipo, pero una biblioteca autocontenida debe recibir o guardar el texto de forma explícita.

### A.5 LCP: contrato y portabilidad

La convención de `phi`, `plcp` y `lcp` es coherente con el capítulo de SA. Dos detalles para una versión robusta:

- `int phi[n]` e `int plcp[n]` son arreglos de longitud variable, que no pertenecen al estándar C++17. Algunos compiladores los aceptan como extensión. `vector<int>` expresa el tamaño dinámico de manera portable.
- `phi[SA[0]]` exige `n>0`. Decide si texto vacío está prohibido o devuelve un arreglo vacío antes de acceder.

En la presentación de Kasai se asignó explícitamente `h=0` cuando el sufijo no tiene predecesor. Esa forma hace evidente el invariante y evita depender de razonamientos implícitos al adaptar el algoritmo.

### A.6 SAM: intervalo de longitudes y terminales

El comentario `min(state) = sa[link].len` debe interpretarse como **límite inferior exclusivo**, no como longitud mínima incluida. La mínima longitud representada por un estado no raíz es:

$$
len[link[v]]+1.
$$

Omitir el `+1` al contar longitudes sobrecuenta una cadena por estado. La construcción del fragmento usa la forma estándar de clones; al extenderla con frecuencias, los clones deben empezar con conteo base cero.

`markTerminalNodes()` marca la cadena de suffix links del `last` actual. Para un uso al final de una sola construcción, eso concuerda con reconocer sufijos no vacíos. Si vuelves a llamarlo después de agregar caracteres, las marcas anteriores deben limpiarse o sustituirse por otro esquema: un estado que era sufijo del texto anterior puede dejar de serlo.

Usar `0` como transición ausente funciona porque ninguna transición por carácter de este SAM necesita ir a la raíz. Esa convención no se puede trasladar ciegamente a Aho, donde volver a la raíz sí es una transición válida.

### A.7 Suffix Tree: qué falta antes de declararlo una plantilla certificada

El material incluye una implementación compacta y una nota del autor sobre su estado. Esa nota no se tomó como instrucción para editarla. La guía explica sus conceptos, pero no presenta esa implementación como auditada exhaustivamente.

Antes de adoptarla para un contest, verifica:

1. Si la función recibe texto con centinela o construye un árbol implícito.
2. Cómo identifica el inicio de cada sufijo y qué hojas cuenta al final.
3. Qué representan `node` y `pos` en cada iteración.
4. Cómo se inicializan y reutilizan `slink`, `f_pos`, `len` y mapas entre casos.
5. Que la capacidad de nodos cubra cerca de `2N`, siendo `N` la longitud concatenada con separadores.
6. Si `correct()` se llama solo cuando ya no se agregarán caracteres.
7. Qué hojas y colores conserva `cutGeneralized` al cortar en separadores.
8. Que la recursión de impresión o DFS soporte profundidad adversa.

Con `map<int,int>` por nodo, debes considerar sobrecarga de memoria y costo logarítmico de operaciones. Un millón de objetos `map` vacíos ya consume memoria apreciable antes de insertar aristas. La cota abstracta `O(n)` no sustituye una estimación en bytes.

<a id="pruebas"></a>
## Apéndice B. Verificación, límites y formulario de consulta

### B.1 Pruebas diferenciales: un método de trabajo

Para cada estructura, escribe una solución lenta obvia sobre cadenas cortas. Genera todas las cadenas de un alfabeto pequeño hasta una longitud manejable y compara resultados. La enumeración exhaustiva de casos pequeños encuentra muchos fallos de clones, centinelas y solapamientos que una muestra de cadenas aleatorias no detecta.

| Estructura | Oráculo lento |
|---|---|
| Trie | Lista de palabras y comparación directa de prefijos |
| KMP/Z | Probar todos los bordes y LCP carácter por carácter |
| Aho | Buscar cada patrón en cada posición |
| SA | Ordenar índices usando los sufijos completos, solo en pruebas pequeñas |
| LCP/LCE | Comparar caracteres directamente |
| SAM | Set de todas las subcadenas y mapa de frecuencias |
| Manacher | Enumerar intervalos y comparar con su reverso |
| Eertree | Set/map de intervalos palindrómicos por contenido |
| Duval | Comprobar cada factor contra todos sus sufijos propios |
| Rotación mínima | Enumerar todas las rotaciones |
| Subsecuencias | Enumerar máscaras de posiciones y deduplicar contenidos |
| BWT | Construir desde SA e invertir para recuperar el texto |

No uses dos implementaciones que comparten exactamente la misma fórmula incorrecta como única verificación. Combina fuerza bruta con identidades entre estructuras distintas.

### B.1.1 Comprobaciones realizadas al preparar esta guía

Se contrastaron transcripciones ejecutables de los pseudocódigos y fórmulas principales contra fuerza bruta en las **2 047 cadenas binarias de longitudes 0 a 10**. Las comprobaciones incluyeron función prefijo, Z, períodos, autómata KMP, radios de Manacher, factorización de Duval, rotación mínima, clases y frecuencias de SAM, criterio de dos ocurrencias disjuntas, conteos de Eertree, subsecuencias distintas, inversión BWT y búsqueda hacia atrás.

También se comprobó que los 14 capítulos técnicos contienen las siete secciones solicitadas y que los enlaces internos del índice tienen destino. Estas pruebas validan ejemplos e invariantes de la exposición; no constituyen una certificación completa de todas las técnicas avanzadas ni de los archivos originales. Los dos contraejemplos del apéndice A se ejecutaron separadamente sobre los constructores originales aislados.

### B.2 Identidades de control

**Subcadenas distintas:**

$$
\frac{n(n+1)}2-\sum lcp
=\sum_{v\ne root}(len[v]-len[link[v]])
=ways[root].
$$

**Todas las ocurrencias de subcadenas:**

$$
\sum_{v\ne root}(len[v]-len[link[v]])occ[v]
=\frac{n(n+1)}2.
$$

**Palíndromos por posiciones:**

$$
\sum d1+\sum d2
=\sum_{v\text{ ordinario de Eertree}}occ[v]
=\sum_{i=0}^{n-1}num[last_i].
$$

**Prefijos:** los conteos obtenidos por histograma Z deben coincidir con los del árbol de bordes.

**SA:** `rank[SA[r]]=r` y cada par adyacente debe estar estrictamente ordenado. Comprueba que `SA` sea permutación: un arreglo ordenado con un índice duplicado sigue siendo inválido.

**SAM:** para cada estado no raíz `len[link[v]]<len[v]`; para cada transición `v→u`, `len[v]<len[u]`. Clones con `occ_base=0` y estados de prefijos con `occ_base=1`.

**Aho:** todo fallo no raíz reduce profundidad. `go` siempre lleva a un estado válido. `exit[v]`, si existe, es terminal y aparece en la cadena de fallos propia de `v`.

### B.3 Familias adversarias

**Todos los caracteres iguales:** `a^n`. Maximiza bordes, solapamientos, sufijos palindrómicos y muchas frecuencias. Detecta salidas cuadráticas ocultas.

**Alternancia:** `abababab...`. Produce periodicidad y palíndromos impares amplios; ayuda a detectar empates de bloques y reinicios incorrectos.

**Repetición con ruptura:** `aaaaabaaaaa`, `ababacabab`. Obliga a recorrer fallos y crea casos de extensión interrumpida.

**Alfabeto amplio:** caracteres distintos o códigos cercanos a límites. Detecta suposiciones de mapeo y de tamaño de counting sort.

**Diccionario anidado:** `a`, `aa`, ..., `a^k`. Distingue reportar todos los matches de contar frecuencias sin enumerarlos.

**Duplicados y prefijos:** `a`, `a`, `ab`, `aba`. Detecta pérdida de IDs y confusión terminal/hoja.

**Varios casos en el mismo proceso:** uno grande seguido de varios pequeños. Detecta datos residuales, links sin reinicializar y rangos fuera del tamaño lógico que todavía caen dentro del arreglo global.

**Longitud cero y uno:** se prueban conforme al contrato público de la plantilla, aunque un juez concreto nunca los use.

### B.4 Presupuesto de memoria

Para estimar, multiplica número máximo de estados por tamaño real del nodo. Un SAM con unos `2n` estados y 26 transiciones de 4 bytes reserva aproximadamente `208n` bytes solo en transiciones. Para `n=10^6`, son unos 208 MB decimales, antes de `len`, `link`, ocurrencias, órdenes y el texto.

Aho con `next[26]` y `go[26]` duplica tablas: unos 208 bytes por nodo solo para ellas. Con un millón de nodos, la memoria ya es relevante para límites comunes.

Una Sparse Table con cerca de 20 niveles sobre un millón de enteros usa alrededor de 80 MB decimales, sin contar SA, rank, LCP ni estructura de vectores. Si solo necesitas RMQ y la memoria aprieta, evalúa Segment Tree o estructuras RMQ más compactas.

Los mapas dispersos ahorran casillas ausentes pero agregan punteros, balanceo, asignaciones y mala localidad de memoria. No asumas que `map` siempre ahorra memoria frente a un arreglo pequeño.

### B.5 Números grandes y saturación

- Cantidad de subcadenas distintas: hasta `n(n+1)/2`.
- Suma de longitudes de todas las ocurrencias: `n(n+1)(n+2)/6`.
- Suma de LCP de todos los pares: puede ser cúbica.
- Número de cadenas de longitud `L`: `σ^L`, exponencial.
- Número de subsecuencias distintas: hasta `2^n` incluyendo la vacía.

Convierte a un tipo suficientemente ancho **antes** de multiplicar. `long long x = n*(n+1)/2` puede desbordar primero en `int`. Para selección por rango, suma saturada en `K+1` comparando previamente contra el límite; para aritmética modular, recuerda que el módulo no conserva comparaciones de magnitud.

### B.6 Formulario compacto con condiciones

| Resultado | Fórmula / condición | Condición de uso |
|---|---|---|
| Período mínimo | `n-pi[n-1]` | `n>0`, período puede terminar parcial |
| Potencia exacta | `n % p == 0` | `p` período candidato |
| Borde vía Z | `z[n-L] == L` | `0<L<n` |
| Período vía Z | `z[p] >= n-p` | `1≤p<n`; `p=n` aparte |
| LCE con SA | `min lcp[a+1..b]` | `a<b`, rangos lexicográficos |
| Distintas vía SA | `n(n+1)/2 - sum(lcp)` | Sin contar centinela ni vacía |
| Distintas vía SAM | `sum(len[v]-len[link[v]])` | Estados no raíz |
| Longitudes SAM | `[len[link[v]]+1,len[v]]` | Intervalo inclusivo |
| Ocurrencias SAM | Propagar marcas de prefijos por links | Clones con marca base cero |
| Palíndromos por ocurrencia | `sum(d1)+sum(d2)` | Convenciones de radios de esta guía |
| Palíndromos distintos | `nodos_Eertree-2` | Dos raíces especiales |
| KMP tras match | `q=pi[m-1]` | Si se normaliza inmediatamente |
| Aho estado prohibido | `terminal[v] OR bad[link[v]]` | Propagación desde menor profundidad |
| Aho frecuencia | Sumar visitas hacia fallos | Orden BFS inverso, sin autoenlace raíz |
| SAM par disjunto | `maxEnd-minEnd >= L` | `L` pertenece al intervalo del estado |
| Intervalo contenido | Inicio `≤R-L` o final `≥A+L-1` | Región `[A,R)`, longitud `L>0` |

### B.7 Preguntas que debes poder contestar en una entrevista de equipo

1. ¿Por qué KMP puede saltarse candidatos y Z puede copiar valores?
2. ¿Por qué Aho necesita heredar terminales por fallos?
3. ¿Por qué un patrón ocupa un intervalo en SA?
4. ¿Por qué el LCP de extremos es un mínimo de adyacentes?
5. ¿Qué modifica un clon de SAM y por qué no agrega una posición final nueva?
6. ¿Por qué un estado SAM representa varias longitudes, pero un nodo Eertree solo una?
7. ¿Qué ocurrencias corresponden al subárbol de un suffix link?
8. ¿Por qué un árbol de sufijos necesita posiciones implícitas en sus aristas?
9. ¿Por qué el número de palíndromos distintos es lineal, pero sus ocurrencias pueden ser cuadráticas?
10. ¿Qué prueba hace válido tu greedy de reconstrucción lexicográfica?
11. ¿Dónde está el factor `σ` que omitiste al decir “lineal”?
12. ¿Qué parte de tu solución deja de servir si aparece una actualización en medio del texto?

Si alguna respuesta se reduce a “porque así funciona la plantilla”, vuelve al invariante correspondiente antes de intentar una variante avanzada.

<a id="referencias"></a>
## Referencias y lecturas para continuar

### Material del proyecto

Las cinco referencias locales consultadas se enlazan en el apéndice A. La guía toma de ellas convenciones y ejemplos de implementación, y desarrolla explicaciones y ejercicios propios. Los problemas originales de entrenamiento no se presentan como tareas de un juez existente.

### Plataformas y contratos de implementaciones

- [CSES — Problem Set](https://cses.fi/problemset/): catálogo oficial de los problemas enlazados individualmente en la ruta.
- [Library Checker](https://judge.yosupo.jp/): tareas de validación de estructuras; los enlaces de capítulos apuntan a cada problema.
- [AtCoder Library — documentación de strings](https://github.com/atcoder/ac-library/blob/master/document_en/string.md): contratos de `suffix_array`, `lcp_array` y `z_algorithm`. Compara especialmente la convención de longitud y vecinos de LCP con la de esta guía antes de intercambiar implementaciones.
- [Codeforces — A Lot of Games](https://codeforces.com/problemset/problem/455/B) y [Duff is Mad](https://codeforces.com/problemset/problem/587/F): práctica de trie/juegos y consultas avanzadas de strings.

### Lecturas de investigación

- Rubinchik y Shur, [EERTREE: An Efficient Data Structure for Processing Palindromes in Strings](https://arxiv.org/abs/1506.04862): referencia original para Eertree y sus extensiones. Para profundizar en particiones, estudia los invariantes de series links junto con una implementación lenta de contraste.
- Bannai y colaboradores, [The Runs Theorem](https://arxiv.org/abs/1406.0263): límite del número de runs y conexiones con palabras de Lyndon. Recomendado después de poder trabajar cómodamente con LCE y períodos.
- Rankin, [Fine-Wilf graphs and the generalized Fine-Wilf theorem](https://arxiv.org/abs/0906.1780): contexto y generalización del criterio de compatibilidad de períodos.
- Burrows y Wheeler, [A Block-sorting Lossless Data Compression Algorithm](https://www.cs.jhu.edu/~langmea/resources/burrows_wheeler.pdf): informe original de la transformada, útil para entender la relación entre ordenación, reversibilidad y compresión.

### Fronteras de este curso

Quedan como especializaciones posteriores: SA-IS en detalle, construcciones generalizadas de SAM sobre tries, estructuras dinámicas de texto con ediciones arbitrarias, Lempel–Ziv, matching aproximado con inserciones y borrados, convolución para alineaciones y pruebas completas de enumeración lineal de runs. Conocer que existen ayuda a reconocer cuándo una herramienta básica no alcanza; implementarlas requiere un estudio separado.

El objetivo de este material es que puedas justificar y combinar las herramientas centrales, detectar la información que falta en una plantilla y construir soluciones verificables cuando el enunciado cambia una condición decisiva.
