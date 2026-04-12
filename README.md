# new_push_swap

├── Makefile                # Módulo 0: Reglas all, clean, fclean, re y bonus
├── include/                # Archivos .h
│   ├── push_swap.h         # Prototipos generales y estructuras de datos
│   ├── instructions.h      # Definiciones de movimientos
│   └── algorithms.h        # Prototipos de los diferentes algoritmos
├── src/                    # Archivos .c organizados por módulos
│   ├── main.c              # Punto de entrada y lógica del Módulo 1 (Adaptive)
│   ├── setup/              # Módulo 1: Infraestructura
│   │   ├── parsing.c       # Validación de int y duplicados
│   │   ├── flags.c         # Lógica de selectores (--simple, --bench, etc.)
│   │   ├── stack_utils.c   # Inicialización de listas doblemente enlazadas
│   │   └── memory.c        # Funciones de liberación (free) y gestión de errores
│   ├── operations/         # Módulo 2: Instrucciones
│   │   ├── push.c          # pa, pb
│   │   ├── swap.c          # sa, sb, ss
│   │   ├── rotate.c        # ra, rb, rr
│   │   ├── rev_rotate.c    # rra, rrb, rrr
│   │   └── output.c        # Gestión de impresión en stdout vs silent (--bench)
│   ├── algorithms/         # Módulo 3 y 4: Lógica de ordenación
│   │   ├── metrics.c       # Cálculo de Disorder Metric
│   │   ├── algo_simple.c   # O(n²) para pocos elementos
│   │   ├── algo_medium.c   # O(n root 2) - Chunks / Bloques
│   │   ├── algo_complex.c  # O(n log n) - Radix o Turk Algorithm
│   │   └── costs.c         # Cálculo de costes y optimización de movimientos
├── bonus/                  # Módulo 5: Checker
│   ├── checker_main.c      # Main del programa bonus
│   └── checker_utils.c     # Lectura de stdin y validación final
├── libft/                  # Tu librería de funciones auxiliares (si la usas)
└── obj/                    # Archivos objeto (.o) generados (creada por Makefile)