#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

void readLine(char *buf, int size) {
    if (fgets(buf, size, stdin)) {
        buf[strcspn(buf, "\n")] = '\0';
    }
}

void init(List *l) {
    l->a = NULL;
    l->size = 0;
    l->cap = 0;
}

int expand_by(List *l, int add) {
    int newCap;
    Exam *b;
    int i;

    if (add <= 0) return 0;

    newCap = l->cap + add;
    if (newCap <= 0) newCap = add;

    b = (Exam*)malloc(newCap * sizeof(Exam));
    if (b == NULL) {
        printf("Нет памяти!\n");
        return 0;
    }

    for (i = 0; i < l->size; i++) {
        b[i] = l->a[i];
    }

    free(l->a);
    l->a = b;
    l->cap = newCap;
    return 1;
}

void freeList(List *l) {
    free(l->a);
    l->a = NULL;
    l->size = 0;
    l->cap = 0;
}

void inputExam(Exam *e) {
    printf("Введите предмет: ");
    readLine(e->subject, STR);

    printf("Введите дату: ");
    readLine(e->date, 20);

    printf("Введите аудиторию: ");
    readLine(e->room, 20);

    printf("Введите количество студентов: ");
    scanf("%d", &e->students);
    getchar();
}

void addExam(List *l) {
    if (l->size == l->cap) {
        if (!expand_by(l, 2)) {
            return;
        }
    }

    inputExam(&l->a[l->size]);
    l->size++;
    printf("Экзамен добавлен.\n");
}

void showAll(const List *l) {
    int i;

    if (l->size == 0) {
        printf("Список пуст.\n");
        return;
    }

    for (i = 0; i < l->size; i++) {
        printf("\nЗапись %d\n", i + 1);
        printf("Предмет: %s\n", l->a[i].subject);
        printf("Дата: %s\n", l->a[i].date);
        printf("Аудитория: %s\n", l->a[i].room);
        printf("Студентов: %d\n", l->a[i].students);
    }
}

void editExam(List *l) {
    int index;

    if (l->size == 0) {
        printf("Список пуст.\n");
        return;
    }

    showAll(l);
    printf("\nВведите номер записи для редактирования: ");
    scanf("%d", &index);
    getchar();

    if (index < 1 || index > l->size) {
        printf("Неверный номер.\n");
        return;
    }

    inputExam(&l->a[index - 1]);
    printf("Запись изменена.\n");
}

void searchBySubject(const List *l) {
    char key[STR];
    int i, found = 0;

    if (l->size == 0) {
        printf("Список пуст.\n");
        return;
    }

    printf("Введите предмет для поиска: ");
    readLine(key, STR);

    for (i = 0; i < l->size; i++) {
        if (strcmp(l->a[i].subject, key) == 0) {
            printf("\nНайдена запись %d\n", i + 1);
            printf("Предмет: %s\n", l->a[i].subject);
            printf("Дата: %s\n", l->a[i].date);
            printf("Аудитория: %s\n", l->a[i].room);
            printf("Студентов: %d\n", l->a[i].students);
            found = 1;
        }
    }

    if (!found) {
        printf("Совпадений не найдено.\n");
    }
}

void sortBySubject(List *l) {
    int i, j;
    Exam temp;

    if (l->size < 2) {
        printf("Сортировка не требуется.\n");
        return;
    }

    for (i = 0; i < l->size - 1; i++) {
        for (j = 0; j < l->size - 1 - i; j++) {
            if (strcmp(l->a[j].subject, l->a[j + 1].subject) > 0) {
                temp = l->a[j];
                l->a[j] = l->a[j + 1];
                l->a[j + 1] = temp;
            }
        }
    }

    printf("Список отсортирован по предмету.\n");
}

int saveToFile(const List *l, const char *filename) {
    FILE *f = fopen(filename, "wb");

    if (f == NULL) {
        printf("Ошибка открытия файла для записи.\n");
        return 0;
    }

    fwrite(&l->size, sizeof(int), 1, f);
    fwrite(l->a, sizeof(Exam), l->size, f);

    fclose(f);
    return 1;
}

int loadFromFile(List *l, const char *filename) {
    FILE *f = fopen(filename, "rb");
    int newSize;

    if (f == NULL) {
        return 0;
    }

    fread(&newSize, sizeof(int), 1, f);

    freeList(l);
    init(l);

    if (newSize > 0) {
        if (!expand_by(l, newSize)) {
            fclose(f);
            return 0;
        }

        fread(l->a, sizeof(Exam), newSize, f);
        l->size = newSize;
    }

    fclose(f);
    return 1;
}