# umicom-education-studio-module
Thin C23 Umicom Education Studio application composition over Umicom Framework

## Framework programming lessons

The curriculum, HTML and runnable exercises are supplied by Framework. The new
`umicom-education-lessons` console displays that same catalogue; it does not
copy lesson definitions or execute learner code. The existing application
verification console and native product workspace are unchanged.

After an all-module build with `UMICOM_BUILD_LEARNING_EXAMPLES=ON`:

```text
umicom-education-lessons --list
umicom-education-lessons --lesson foundations.git-workflow
umicom-education-lessons --lesson foundations.bounded-strings
umicom-education-lessons --lesson foundations.assembly-loops
```

Read `framework/docs/learning/programming-workshop.html` in the source checkout.
Installed lessons are at `share/umicom-framework/docs/learning` below the chosen
installation prefix. Installed exercise sources retain the relative
`examples/learning` layout. Studio uses its existing Guided Learning surface
and the same Framework catalogue.

This adds catalogue access and content, not a new Education graphical lesson
browser or an unchecked Run button. Execution uses the documented CMake/compiler
commands. Tests do not automatically award a learner score or update progress.
