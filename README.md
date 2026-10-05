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

## Review linked context values

Education Studio exposes Framework's reviewed context changes through
`umi_education_workspace_context_review`, `umi_education_workspace_context_apply`
and `umi_education_workspace_clear_context` in
`umicom/education/workspace_commands.h`. A context group is a named value that
related panels can share; for example, a host could use `learning.course` with the sample
value `sample-course`. The host must connect that name to its panel consumers.

1. Use a runtime initialised with this product's canonical experience. Prepare
   the requested changes with the review function; preparation changes no live state.
2. Display the copied Framework summary and rows. Keep the runtime and its
   workbench alive while the user reviews the proposed values. If the summary
   reports UI differences, show the captured UI value beside the cached value.
3. Apply only after acceptance, then destroy the review. If the workspace changed,
   prepare a fresh review. Cancelling only destroys the review.

This is a module API; native review screens are separate host work. Context edits
do not execute product commands or external operations. The shared guide at
`framework/docs/guides/REVIEWING_LINKED_CONTEXTS.html` in the Applications checkout
explains capacity, ownership, thread coordination and recovery in more detail.
