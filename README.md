*Este proyecto ha sido creado como parte del currículo de 42 por gigarcia, rodde-fr.*

#Push_Swap

## Descripción

Este proyecto una implementación en C cuyo objetivo es ordenar una
secuencia de enteros usando únicamente las operaciones permitidas sobre dos pilas:
push (pa, pb), swap (sa, sb, ss), rotate (ra, rb, rr) y reverse-rotate (rra, rrb, rrr).
El reto es producir una secuencia válida de operaciones que ordene la entrada con el
menor número posible de movimientos, cumpliendo las normas del proyecto.

Este repositorio contiene una solución multi-estrategia que elige entre algoritmos
óptimos para tamaños pequeños, una estrategia "chunking" para tamaños medianos y un
quicksort adaptado que actúa como estrategia compleja para entradas con una métrica de desorden alta.

## Autores y reparto de trabajo

### gigarcia
- Desarrollo general del proyecto
- Implementación de operaciones (`src/operations/`)
- Implementación de algoritmos (`simple`, `medium`, `complex`)
- Métricas y lógica de selección de estrategia
- Integración del sistema

### rodde-fr
- Parsing y validación de entrada
- Implementación de `src/setup/parsing.c`
- Manejo de errores (inputs inválidos, duplicados, overflow)
- Inicialización de estructuras

# Estructura del Proyecto

```text
.
├── Makefile
├── README.md
├── .gitignore
├── .gitmodules
├── include/
│   ├── algorithms.h
│   ├── instructions.h
│   └── push_swap.h
├── src/
│   ├── main.c
│   ├── algorithms/
│   │   ├── complex.c
│   │   ├── complex_utils.c
│   │   ├── medium.c
│   │   ├── metrics.c
│   │   ├── quicksort_cases_a.c
│   │   ├── quicksort_cases_b.c
│   │   └── simple.c
│   ├── operations/
│   │   ├── output.c
│   │   ├── output_bench.c
│   │   ├── push.c
│   │   ├── rev_rotate.c
│   │   ├── rotate.c
│   │   └── swap.c
│   └── setup/
│       ├── flags.c
│       ├── memory.c
│       ├── parsing.c
│       ├── stack_init.c
│       └── stack_utils.c
├── bonus/
│   ├── checker_main.c
│   └── checker_utils.c
└── libft/
    ├── Makefile
    ├── libft.h
    ├── get_next_line.c
    ├── get_next_line.h
    └── [Múltiples archivos fuente ft_*.c ...]

## Instrucciones

Requisitos previos:
- Un compilador C compatible (la Makefile usa `cc`).
- La carpeta `libft/` con la biblioteca está incluida y se compila automáticamente.

Compilar (desde la raíz del repositorio):

```bash
make
```

Esto compilará `push_swap`. El Makefile también incluye la regla `bonus` para compilar
el ejecutable `checker` si se desea:

```bash
make bonus
```

Limpieza:

```bash
make clean    # elimina objetos
make fclean   # elimina objetos y binarios
make re       # fclean + all
```

Ejecución básica:

```bash
./push_swap 3 2 1 0
# salida: lista de instrucciones que, aplicadas a la pila A, producen la pila ordenada

# Para verificar con el checker (si lo has compilado):
./push_swap 3 2 1 0 | ./checker 3 2 1 0
```

Notas de uso:
- El programa espera enteros válidos; el parser verifica números, duplicados y límites de INT.
- En caso de errores de entrada el programa imprime "Error\n" y sale.

## Estructura principal del código

- `include/` : cabeceras públicas (`push_swap.h`, `algorithms.h`, `instructions.h`).
- `src/` : código fuente dividido en submódulos:
  - `setup/` : parsing, flags, inicialización de pilas y utilidades.
  - `operations/` : implementación de las operaciones permitidas (sa, pa, ra, rra, ...)
  - `algorithms/` : estrategias de ordenación (simple, medium, complex) y utilidades.
- `libft/` : biblioteca de utilidades del autor (se enlaza en el Makefile).
- `bonus/` : implementaciones del `checker` para la validación (opcional).

## Algoritmos implementados — explicación y justificación

Contrato corto (entradas/salidas):
- Input: lista de enteros desde argumentos de línea de comandos.
- Output: secuencia de instrucciones válidas (una por línea) que ordenan la pila A.
- Error modes: imprime "Error\n" y sale para entradas inválidas (no numéricas, duplicados, overflow).

Estrategias y por qué se eligieron (implementadas en `src/algorithms`):

1) Normalización de índices (assign_index)
- Qué hace: mapea los valores originales a índices 0..n-1 preservando orden relativo.
- Justificación: reduce la dependencia del rango de valores y facilita algoritmos basados en bits o índices (por ejemplo, si se implementase radix por bits). Implementado en `algorithms/metrics.c` y usado por las estrategias que operan sobre índices.

2) Estrategia "simple" (función `simple` — `algorithms/simple.c`)
- Para: entradas pequeñas (n ≤ 5 típicamente).
- Aplica soluciones óptimas para 2–3 elementos (`sort_three` / `sort_3_a`) y desplaza
  repetidamente el elemento más pequeño a la pila B hasta reducir a 3 elementos; ordena
  esa subpila y vuelve a extraer desde B con `pa`.
- Justificación: para entradas cortas, es trivial encontrar secuencias mínimas. Evita
  sobrecostes que introduciría una estrategia más genérica.

3) Estrategia "medium" / chunking (función `medium` — `algorithms/medium.c`)
- Para: entradas medianas (por ejemplo, n ≤ ~100 y n > 5), con heurística de chunk size.
- Convierte valores a índices (indices ya asignados por `assign_index`), luego
  mueve elementos en "chunks" desde A a B según su índice; al empujar a B, algunos se
  rotan para facilitar su posterior recolocación; finalmente reconstruye A extrayendo
  de B el mayor índice disponible.
- Parámetros: el código usa chunk_size = 15 para n ≤ 100 y 35 para n > 100. Estos valores balancean número de movimientos frente a rotaciones y son heurísticos comunes.
- Justificación: reduce la cantidad de rotaciones y búsquedas para valores dispersos, y
  suele producir buenos resultados en tests de 100 y 500 elementos.

4) Estrategia "complex", quicksort recursivo (función `complex` — `algorithms/complex.c`)
- Para: entradas grandes o cuando la heurística (métrica de desorden) lo decide.
- Cómo (implementación propia style quicksort-partition):
  - `quicksort_a` y `quicksort_b` hacen particionado por un pivote (mediana calculada
    sobre la sublista con `get_median` en `algorithms/complex_utils.c`).
  - En `quicksort_a` se empujan a B los elementos menores que el pivote y se rotan los
    demás; tras particionar se 'recolocan' (recolocar mediante `rra`/`rrb`) para restaurar el orden relativo, y se recursiona en ambas particiones.
  - Para segmentos de tamaño ≤ 3 se usan funciones `sort_small_a` / `sort_small_b`
    que aplican secuencias mínimas específicas.
- Este enfoque imita el quicksort adaptado al conjunto limitado de
  operaciones (push/rotate). Reduce la profundidad de recursión de forma eficiente y
  es efectivo en entradas grandes donde chunking puede resultar subóptimo.

Métrica de desorden (compute_disorder) — `algorithms/metrics.c`:
- Qué hace: calcula un valor en [0.0, 1.0] que representa el porcentaje de pares
  fuera de orden (inversiones normalizadas).
- Uso: la métrica sirve para seleccionar una estrategia adaptativa (por ejemplo,
  usar `simple` si la secuencia está casi ordenada, `medium` para desorden medio y
  `complex` para casos muy desordenados o grandes).

Decisiones técnicas y trade-offs importantes:
- Elegir chunk sizes heurísticos simplifica la implementación pero requiere ajuste
  para datasets concretos. Los valores elegidos (15/35) son típicos en soluciones
  estudiantiles y equilibran rendimiento en tests de la asignatura.
- Calcular la mediana con copia y ordenación (get_median) es simple y claro, pero
  implica O(m log m) por partición; para tamaños grandes se podrían usar selecciones
  lineales (median-of-medians) si se necesitase optimización extrema.
- El diseño prioriza claridad y corrección dentro de las restricciones del proyecto
  (sin librerías externas, cumpliendo la Norm).

Edge cases cubiertos:
- Entradas ya ordenadas (retorna sin imprimir instrucciones).
- Un solo elemento o 0 elementos.
- Detección de duplicados y argumentos no numéricos (parsing en `src/setup/parsing.c`).

## Recursos

- Documentación y enunciado del proyecto (PDF del sujeto de 42).
- Radix sort: https://en.wikipedia.org/wiki/Radix_sort
- Quick sort: https://en.wikipedia.org/wiki/Quicksort
- Artículos y hilos de 42 sobre `push_swap` y estrategias de chunking / radix.

Uso de IA / declaración sobre IA
- Se utilizó asistencia de IA para tareas no críticas al código fuente:
  - Redacción y traducción de este README.
  - Explicación de las decisiones algorítmicas en lenguaje natural.
  - Sugerencias para tests y estructura del proyecto.
- Todo el código fuente compilado y enviado al repositorio fue escrito y revisado por
  los autores (`gigarcia`, `rodde-fr`). Cualquier salida de IA fue revisada manualmente antes
  de su incorporación en documentación.

## Cómo probar y ejemplos

Ejemplo rápido:

```bash
./push_swap 2 1 3 6 5 8 4
# Devuelve por stdout una lista de instrucciones (ej: sa, pb, ra, ...)

# Verificación con checker (si compilado):
./push_swap 2 1 3 6 5 8 4 | ./checker 2 1 3 6 5 8 4
```

Comprobación de errores:

```bash
# Entrada inválida -> imprime "Error\n"
./push_swap 1 2 three 4
```

## Archivos clave y dónde mirar

- `src/setup/parsing.c` — validación de argumentos y detección de duplicados.
- `src/operations/*` — implementación de `pa/pb`, `sa/sb/ss`, `ra/rb/rr`, `rra/rrb/rrr`.
- `src/algorithms/simple.c` — estrategia para n pequeños.
- `src/algorithms/medium.c` — chunking / estrategia intermedia.
- `src/algorithms/complex.c`, `complex_utils.c` — particionado recursivo y mediana.
- `include/` — estructuras de datos (`t_stack`, `t_node`) y prototipos públicos.


