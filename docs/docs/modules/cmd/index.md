# Módulo `cmd`

## > Descripción

En las tareas y talleres del curso, se trabaja con archivos de _input_ y _output_ para manejar los tests con los que se evalúa el funcionamiento de la solución. Para ello, es necesario hacer _parsing_ del archivo de _input_, buscando para cada evento: su función corresponiente en el código, los argumentos requeridos por la función, y añadir el código _boilerplate_ necesario antes y después del llamado en sí.

Dado que este patrón es tan común, dentro de cáda módulo `mod` de _LibEDD_ existe una función `mod_cmd`, que se encarga de manejar esta lógica de _parsing_ y ejecución de comandos para las funciones definidas en los módulos, de forma flexible y configurable.

## > Definiciones

Los contenidos de `libedd_cmd.h` son muy extensos para incluirse aquí, pero para cada módulo `mod` con una función `mod_cmd`, define las siguientes "macros" para las funciones exportadas en `mod`:

- `LIBEDD_CMDNAME_*func*`: El nombre que se le dará a la función `func` en los archivos de input

- `LIBEDD_CMDMSG_GOOD_*func*`: Un string con formato para el mensaje de ^^**éxito**^^ en el archivo de output, para la operación asociada a la función `func`

- `LIBEDD_CMDMSG_ERR_*func*`: Un string con formato para el mensaje de ^^**fracaso**^^ en el archivo de output, para la operación asociada a la función `func`

Un ejemplo de cada una de estas definiciones para la función `sll_at`:

```c
#define LIBEDD_CMDNAME_SLL_AT     "GET-AT"

#define LIBEDD_CMDMSG_GOOD_SLL_AT "El nodo en el indice %zu es: %d\n"
#define LIBEDD_CMDMSG_ERR_SLL_AT  "El nodo en el indice %zu es: (nil)\n"
```

Los nombres de funciones y mensajes por defecto actualmente se encuentran en inglés, pero pueden ser modificados para ajustarse a las necesidades de cada taller. Para que estos cambios sean aplicados, ^^la librería debe recompilarse^^ con la versión de `libedd_cmd.h` con los nuevos nombres de las funciones y mensajes de éxito y fracaso.

## > Funciones

Todas las funciones `*_cmd` se encuentran definidas al final de sus respectivos módulos, en los archivos _header_ y los de código:

- 01) `sll_cmd`
- 02) `dll_cmd`
- 03) `sort_cmd`
- 04) `heap_cmd`
