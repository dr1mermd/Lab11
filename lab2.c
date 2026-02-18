#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char subject[50];
    char date[20];
    char room[20];
    int students;
} Exam;

typedef struct {
    Exam *a;
    int size;
    int cap;
} List;

/* ====== БАЗА: память ====== */
void init(List *l) {
    l->a = NULL;
    l->size = 0;
    l->cap = 0;
}

// расширить на add элементов (БЕЗ realloc)
int expand_by(List *l, int add) {
    int newCap = l->cap + add;
    if (newCap <= 0) newCap = add;

    Exam *b = (Exam*)malloc(newCap * sizeof(Exam));
    if (!b) { printf("Нет памяти!\n"); return 0; }

    for (int i = 0; i < l->size; i++) b[i] = l->a[i];

    free(l->a);
    l->a = b;
    l->cap = newCap;
    return 1;
}

// уменьшить cap до size (для задания про уменьшение при удалении последнего)
int shrink_to_fit(List *l) {
    if (l->size == 0) {
        free(l->a);
        l->a = NULL;
        l->cap = 0;
        return 1;
    }

    if (l->cap == l->size) return 1;

    Exam *b = (Exam*)malloc(l->size * sizeof(Exam));
    if (!b) { printf("Не удалось уменьшить память!\n"); return 0; }

    for (int i = 0; i < l->size; i++) b[i] = l->a[i];

    free(l->a);
    l->a = b;
    l->cap = l->size;
    return 1;
}

void clear_and_free(List *l) { // очистка и освобождение всей памяти
    free(l->a);
    l->a = NULL;
    l->size = 0;
    l->cap = 0;
}

/* ====== операции со списком ====== */
Exam input_exam() {
    Exam e;
    printf("Предмет: "); scanf("%49s", e.subject);
    printf("Дата: "); scanf("%19s", e.date);
    printf("Аудитория: "); scanf("%19s", e.room);
    printf("Студенты: "); scanf("%d", &e.students);
    return e;
}

// добавить в конец (ЛР2)
void push_back(List *l, Exam e) {
    if (l->size == l->cap) {
        // можно расширять фиксировано (+5), так проще
        if (!expand_by(l, 5)) return;
    }
    l->a[l->size++] = e;
}

// удалить строго последний + уменьшить память (ЛР2)
void pop_back(List *l) {
    if (l->size == 0) { printf("Список пуст!\n"); return; }
    l->size--;
    shrink_to_fit(l);
}

// вставка на позицию (ЛР3)
void insert_at(List *l, int pos, Exam e) {
    if (pos < 0 || pos > l->size) { printf("Неверная позиция!\n"); return; }

    if (l->size == l->cap) {
        if (!expand_by(l, 5)) return;
    }

    for (int i = l->size; i > pos; i--) {
        l->a[i] = l->a[i - 1];
    }
    l->a[pos] = e;
    l->size++;
}

// удаление по индексу со сдвигом (ЛР3)
void remove_at(List *l, int idx) {
    if (idx < 0 || idx >= l->size) { printf("Неверный индекс!\n"); return; }

    for (int i = idx; i < l->size - 1; i++) {
        l->a[i] = l->a[i + 1];
    }
    l->size--;
    shrink_to_fit(l);
}

/* ====== функции по заданию 1й лабы ====== */
void print_all(List *l) {
    if (l->size == 0) { printf("Список пуст\n"); return; }
    for (int i = 0; i < l->size; i++) {
        printf("%d) %s %s %s %d\n", i,
               l->a[i].subject, l->a[i].date, l->a[i].room, l->a[i].students);
    }
    printf("size=%d cap=%d\n", l->size, l->cap);
}

void edit(List *l, int idx) {
    if (idx < 0 || idx >= l->size) { printf("Ошибка!\n"); return; }
    printf("Новые данные:\n");
    l->a[idx] = input_exam();
}

void search_subject(List *l) {
    char key[50];
    printf("Введите предмет: "); scanf("%49s", key);

    int found = 0;
    for (int i = 0; i < l->size; i++) {
        if (strcmp(l->a[i].subject, key) == 0) {
            printf("Найдено (%d): %s %s %s %d\n", i,
                   l->a[i].subject, l->a[i].date, l->a[i].room, l->a[i].students);
            found = 1;
        }
    }
    if (!found) printf("Ничего не найдено\n");
}

/* ====== сортировка (ЛР3) ====== */
int cmp(Exam x, Exam y, int field) {
    if (field == 1) return strcmp(x.subject, y.subject);
    if (field == 2) return strcmp(x.date, y.date);
    if (field == 3) return strcmp(x.room, y.room);
    // field == 4
    return x.students - y.students;
}

void sort_list(List *l, int field) {
    for (int i = 0; i < l->size - 1; i++) {
        for (int j = 0; j < l->size - 1 - i; j++) {
            if (cmp(l->a[j], l->a[j + 1], field) > 0) {
                Exam t = l->a[j];
                l->a[j] = l->a[j + 1];
                l->a[j + 1] = t;
            }
        }
    }
}

/* ====== меню ====== */
int main() {
    List l;
    init(&l);

    int choice;
    while (1) {
        printf("\n1-Добавить(в конец)\n");
        printf("2-Показать все\n");
        printf("3-Редактировать по индексу\n");
        printf("4-Поиск по предмету\n");
        printf("5-Удалить последний\n");
        printf("6-Вставить на позицию\n");
        printf("7-Удалить по индексу\n");
        printf("8-Сортировка\n");
        printf("9-Расширить на N (без realloc)\n");
        printf("10-Освободить память вручную\n");
        printf("0-Выход\n");
        printf("Выбор: ");
        scanf("%d", &choice);

        if (choice == 0) break;

        if (choice == 1) {
            Exam e = input_exam();
            push_back(&l, e);
        }
        else if (choice == 2) {
            print_all(&l);
        }
        else if (choice == 3) {
            int idx;
            printf("Индекс: "); scanf("%d", &idx);
            edit(&l, idx);
        }
        else if (choice == 4) {
            search_subject(&l);
        }
        else if (choice == 5) {
            pop_back(&l);
        }
        else if (choice == 6) {
            int pos;
            printf("Позиция: "); scanf("%d", &pos);
            Exam e = input_exam();
            insert_at(&l, pos, e);
        }
        else if (choice == 7) {
            int idx;
            printf("Индекс: "); scanf("%d", &idx);
            remove_at(&l, idx);
        }
        else if (choice == 8) {
            int field;
            printf("Поле: 1-subject 2-date 3-room 4-students\n");
            printf("Выбор: "); scanf("%d", &field);
            if (field < 1 || field > 4) printf("Неверное поле!\n");
            else sort_list(&l, field);
        }
        else if (choice == 9) {
            int n;
            printf("N: "); scanf("%d", &n);
            if (n > 0) expand_by(&l, n);
            else printf("N должно быть > 0\n");
        }
        else if (choice == 10) {
            clear_and_free(&l);
            printf("Память освобождена вручную.\n");
        }
        else {
            printf("Нет такой команды.\n");
        }
    }

    // ЛР2 пункт 4: очистка и освобождение памяти перед завершением
    clear_and_free(&l);
    return 0;
}