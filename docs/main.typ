#import "template/template.typ": *

#show: project.with(
  title: "LibEDD: Librería en C para IIC2133",
  author: "",
  subtitle: "Documentación de la estructura y funcionalidad de LibEDD para facilitar su comprensión y futuro desarrollo.",
  date: "Agosto, 2026",
)

#set text(12pt)

// Aliases and Functions

#let c_code(body) = block(
  fill: rgb("#2b303b"),
  inset: 8pt,
  radius: 2pt,
  raw(
    body.text,
    lang: "c",
    theme: "./template/one_dark.tmTheme"
  )
)

// #c_code(
// ```
// #include <stdio.h>
//
// int main(int argc, char** argv) {
//     printf("Hello, LibEDD!\n");
//     return 0;
// }
// ```
// )

// Main Document

= Preámbulo

A finales del año 2025, en el curso de Estructuras de Datos y Algoritmos (IIC2133), en vista del creciente uso de tecnologías de IA
generativa para la creación de código, el equipo docente tomó la decisión de abandonar la modalidad de tareas para las evaluaciones
prácticas, desarrolladas a lo largo de varias semanas, en favor de talleres presenciales, con una duración aproximada de una hora.
Esto supuso un cambio significativo en la forma y formato de las evaluaciones, y con ello, los supuestos y reglas que se
habían formado en torno al diseño e implementación de las mismas dejaron de ser válidos.

Uno de estos supuestos corresponde a la implementación de las EDD y algoritmos que se utilizan en el curso. Debido a su
complejidad relativa, no es viable que los talleres consistan en que el estudiante implemente desde cero cada una de estas estructuras,
por lo que el enfoque pasó a estar principalmente en extender la funcionalidad ya existente o utilizarlas para problemas donde su uso
es preciso para obtener una solución eficiente.

Naturalmente, esto significó que ya no hace falta reimplementar cada semestre todas estas estructuras, puesto que la
funcionalidad esperada es muy similar. A raíz de esta observación es que nace _LibEDD_: una librería escrita en _C_ que contiene APIs
para todas las EDD y algoritmos necesarios para los talleres. Sus objetivos son: estandarizar las implementaciones de estas estructuras,
focalizar el esfuerzo de desarrollo para aumentar la calidad del código, y facilitar la creación y resolución de los talleres.

Esta librería es *_software libre_*, y está publicada en #link("https://github.com/IIC2133-PUC/libedd")[GitHub] usando la licencia
_GPLv3_. Además, queda *estrictamente prohibido* el uso de LLMs o tecnologías similares de IA generativa para el desarrollo del
proyecto _LibEDD_. Finalmente, este documento escrito en _Typst_ servirá como documentación oficial para la librería, explicando
en detalle la funcionalidad incluida en cada uno de sus módulos, junto con las convenciones que tiene, los supuestos que hace,
y un apartado con información útil para futuros contribuidores y _maintainers_.

= Introducción

= Módulo `err`

= Módulo `cmd`

= Módulo `sll`

= Módulo `dll`

= Módulo `sort`

= Módulo `heap`

= Para contribuidores
