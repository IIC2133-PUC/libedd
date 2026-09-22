# Módulos de LibEDD

_LibEDD_ está compuesta de diferentes _módulos_ que encapsulan la funcionalidad base de alguna estructura de datos, algoritmo o código que conforma la infraestructura de la librería en sí. Actualmente los módulos que se encuentran disponibles son:

- [`err`](err/index.md): Arquitectura de errores para toda la librería
- [`cmd`](cmd/index.md): Configuración de nombres de comandos y mensajes para funciones `*_cmd`
- [`sll`](sll/index.md): Implementación de listas ligadas simples
- [`dll`](dll/index.md): Implementación de listas ligadas dobles
- [`sort`](sort/index.md): Implementación de MergeSort para arreglos, SLLs, y DLLs
- [`heap`](heap/index.md): Implementación de heaps binarios (min y max)
- [`bst`](bst/index.md): Implementación de árboles de búsqueda binarios y árboles AVL

Un aspecto importante es que la implementación actual de estas estructuras y algoritmos están ^^**diseñados exclusivamente alrededor del tipo de datos `int`**^^. Por ejemplo, en las listas ligadas dobles (DLLs), el dato que cada nodo de la estructura tiene asociado es un número `int`. Es posible que en el futuro se extienda para más tipos de datos, pero de momento sólo se trabajará con números enteros.

En la página de cada uno de estos, se explicará la función que cumple, las definiciones importantes (como `struct`s e `enum`s), y cada función contenida en la librería con su firma, descripción, el listado de errores que pueda arrojar, y el código que la define, ^^excluyendo el **_error handling_**^^ para facilitar su lectura.

Las únicas funciones que estén en el _header file_ de un módulo y no se incluyan en la documentación, serán aquellas que estén pensandas para ^^**NO** ser usadas directamente por el programador^^.

Por último, cabe destacar que el módulo `cmd` probablemente sea sólo de interés para los ayudantes, por lo que si es un estudiante del curso, siéntase libre de saltarse esa página.
