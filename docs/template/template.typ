#let project(
  title: "",
  author: "",
  subtitle: "",
  date: none,
  logo: none,
  body,
) = {
  set document(author: author, title: title)
  set page(paper: "us-letter", numbering: "1", number-align: center, margin: 1in)
  set par(leading: 0.55em, spacing: 1em, justify: true)
  set text(font: "New Computer Modern", lang: "es")
  set heading(numbering: "1.")
  show link: set text(fill: rgb("#0066cc"))
  show raw: set text(font: "RecMonoLinear Nerd Font Mono")
  show heading: set block(above: 1.4em, below: 1em)

  v(0.6fr)
  if logo != none {
    align(right, image(logo, width: 26%))
  }

  v(9.6fr)
  text(1.1em, date)

  v(1.2em, weak: true)
  text(2em, weight: 700, title)

  v(0.3fr)
  text(1.3em, style: "italic", subtitle)

  v(0.7em)
  text(1.3em, weight: 700, author)

  v(2.4fr)
  pagebreak()

  outline(depth: 4)
  pagebreak()

  set par(justify: true)

  body
}
