/*-----------------------------------------------------------------------------
 * Umicom Education Studio Module
 * File: src/console/lessons.c
 *
 * PURPOSE:
 *   Present Framework-owned lessons without a second catalogue or executor.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/teacher/foundations_curriculum.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This frontend displays metadata only. It never executes a lesson or Git. */
int main(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        puts("Umicom Education lessons: --list | --lesson ID");
        puts("Content and progression contracts are owned by Umicom Framework.");
        return EXIT_SUCCESS;
    }
    if (argc == 2 && strcmp(argv[1], "--list") == 0) {
        size_t count = umi_teacher_foundations_curriculum_count();
        printf("%zu lessons from Umicom Framework\n", count);
        for (size_t index = 0U; index < count; ++index) {
            const UmiTeacherFoundationsLesson *lesson =
                umi_teacher_foundations_curriculum_at(index);
            if (lesson == NULL) return EXIT_FAILURE;
            printf("%u. %s [%s]\n", lesson->sequence, lesson->title, lesson->id);
        }
        return ferror(stdout) ? EXIT_FAILURE : EXIT_SUCCESS;
    }
    if (argc == 3 && strcmp(argv[1], "--lesson") == 0) {
        const UmiTeacherFoundationsLesson *lesson =
            umi_teacher_foundations_curriculum_find(argv[2]);
        if (lesson == NULL) {
            fputs("Lesson not found in Framework catalogue.\n", stderr);
            return EXIT_FAILURE;
        }
        printf("%s\n%s\nPractice: %s\nSource resource: %s\n",
            lesson->title, lesson->summary, lesson->exercise, lesson->resource_path);
        puts("Read the Framework HTML lesson and run its documented compiler commands manually.");
        puts("Installed content: share/umicom-framework/docs/learning under the installation prefix.");
        return ferror(stdout) ? EXIT_FAILURE : EXIT_SUCCESS;
    }
    fputs("Usage: umicom-education-lessons --list | --lesson ID | --help\n", stderr);
    return 2;
}
