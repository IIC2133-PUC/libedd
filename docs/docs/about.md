# Estado del Proyecto

Actualmente se encuentran implementados los siguientes módulos:

- [`err`](modules/err/index.md): Arquitectura de errores para toda la librería
- [`cmd`](modules/cmd/index.md): Configuración de nombres de comandos y mensajes para funciones `*_cmd`
- [`sll`](modules/sll/index.md): Implementación de listas ligadas simples
- [`dll`](modules/dll/index.md): Implementación de listas ligadas dobles
- [`sort`](modules/sort/index.md): Implementación de MergeSort para arreglos, SLLs, y DLLs
- [`heap`](modules/heap/index.md): Implementación de heaps binarios (min y max)
- [`bst`](modules/bst/index.md): Implementación de árboles de búsqueda binarios y árboles AVL

Módulos que están planeados para el futuro cercano:

- `ttt`: Implementación de árboles 2-3
- `rbt`: Implementación de árboles rojo-negro
- `bpt`: Implementación de árboles B+
- `hash_table`: Implementación de tablas de hash
- `graph`: Implementación de grafos (matriz de adyacencia y listas de adyacencia)

La librería se considerará ^^**_feature complete_**^^ cuando todos los módulos listados anteriormente estén correcta y completamente implementados. De todas formas, este proyecto está diseñado para ser extensible y adaptado a otras funcionalidades, con lo que se mantiene la posibilidad de añadir más módulos. Podríamos decir que la lista anterior simplemente constituye la versión 1.0 de _LibEDD_, pero que versiones posteriores con nuevos módulos son bienvenidas.

# ¿Por qué existe LibEDD?

A finales del año 2025, en el curso de Estructuras de Datos y Algoritmos (IIC2133), en vista del creciente uso de tecnologías de IA generativa para la creación de código, el equipo docente tomó la decisión de abandonar la modalidad de tareas para las evaluaciones prácticas, desarrolladas a lo largo de varias semanas, en favor de talleres presenciales, con una duración aproximada de una hora. Esto supuso un cambio significativo en la forma y formato de las evaluaciones, y con ello, los supuestos y reglas que se habían formado en torno al diseño e implementación de las mismas dejaron de ser válidos.

Uno de estos supuestos corresponde a la implementación de las EDD y algoritmos que se utilizan en el curso. Debido a su complejidad relativa, no es viable que los talleres consistan en que el estudiante implemente desde cero cada una de estas estructuras, por lo que el enfoque pasó a estar principalmente en extender la funcionalidad ya existente o utilizarlas para problemas donde su uso es preciso para obtener una solución eficiente.

Naturalmente, esto significó que ya no hace falta reimplementar cada semestre todas estas estructuras, puesto que la funcionalidad esperada es muy similar. A raíz de esta observación es que nace _LibEDD_: una librería escrita en C que contiene APIs para todas las EDD y algoritmos necesarios para los talleres. Sus objetivos son: estandarizar las implementaciones de estas estructuras, focalizar el esfuerzo de desarrollo para aumentar la calidad y fiabilidad del código, y facilitar la creación y resolución de los talleres.
