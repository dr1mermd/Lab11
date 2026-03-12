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


void init(List *l) {
    l->a = NULL;
    l->size = 0;
    l->cap = 0;
}

int expand_by(List *l, int add) {
    int newCap = l->cap + add;
    if (newCap <= 0) {
        newCap = add;
    }

    Exam *b = (Exam*)malloc(newCap * sizeof(Exam));
    if (b == NULL) {
        printf("Ошибка: нет памяти!\n");
        return 0;
    }

    for (int i = 0; i < l->size; i++) {
        b[i] = l->a[i];
    }

    free(l->a);
    l->a = b;
    l->cap = newCap;
    return 1;
}


int shrink_to_fit(List *l) {
    if (l->size == 0) {
        free(l->a);
        l->a = NULL;
        l->cap = 0;
        return 1;
    }

    if (l->cap == l->size) {
        return 1;
    }

    Exam *b = (Exam*)malloc(l->size * sizeof(Exam));
    if (b == NULL) {
        printf("Ошибка: не удалось уменьшить память!\n");
        return 0;
    }

    for (int i = 0; i < l->size; i++) {
        b[i] = l->a[i];
    }

    free(l->a);
    l->a = b;
    l->cap = l->size;
    return 1;
}


void clear_and_free(List *l) {
    free(l->a);
    l->a = NULL;
    l->size = 0;
    l->cap = 0;
}


Exam input_exam() {
    Exam e;

    printf("Предмет: ");
    scanf("%49s", e.subject);

    printf("Дата: ");
    scanf("%19s", e.date);

    printf("Аудитория: ");
    scanf("%19s", e.room);

    printf("Количество студентов: ");
    scanf("%d", &e.students);

    return e;
}


void push_back(List *l, Exam e) {
    if (l->size == l->cap) {
        if (!expand_by(l, 5)) {
            return;
        }
    }

    l->a[l->size] = e;
    l->size++;
}


void pop_back(List *l) {
    if (l->size == 0) {
        printf("Список пуст!\n");
        return;
    }

    l->size--;
    shrink_to_fit(l);
}


void insert_at(List *l, int pos, Exam e) {
    if (pos < 0 || pos > l->size) {
        printf("Неверная позиция!\n");
        return;
    }

    if (l->size == l->cap) {
        if (!expand_by(l, 5)) {
            return;
        }
    }

    for (int i = l->size; i > pos; i--) {
        l->a[i] = l->a[i - 1];
    }

    l->a[pos] = e;
    l->size++;
}


void remove_at(List *l, int idx) {
    if (idx < 0 || idx >= l->size) {
        printf("Неверный индекс!\n");
        return;
    }

    for (int i = idx; i < l->size - 1; i++) {
        l->a[i] = l->a[i + 1];
    }

    l->size--;
    shrink_to_fit(l);
}


void print_all(List *l) {
    if (l->size == 0) {
        printf("Список пуст.\n");
        return;
    }

    printf("\nСписок экзаменов:\n");
    for (int i = 0; i < l->size; i++) {
        printf("%d) Предмет: %s | Дата: %s | Аудитория: %s | Студентов: %d\n",
               i,
               l->a[i].subject,
               l->a[i].date,
               l->a[i].room,
               l->a[i].students);
    }

    printf("size = %d, cap = %d\n", l->size, l->cap);
}


void edit(List *l, int idx) {
    if (idx < 0 || idx >= l->size) {
        printf("Неверный индекс!\n");
        return;
    }

    printf("Введите новые данные:\n");
    l->a[idx] = input_exam();
}


void search(List *l) {
    if (l->size == 0) {
        printf("Список пуст.\n");
        return;
    }

    int field;
    int found = 0;

    printf("По какому полю искать?\n");
    printf("1 - Предмет\n");
    printf("2 - Дата\n");
    printf("3 - Аудитория\n");
    printf("4 - Количество студентов\n");
    printf("Выбор: ");
    scanf("%d", &field);

if (field == 1) {
        char key[50];
        printf("Введите предмет: ");
        scanf("%49s", key);

        for (int i = 0; i < l->size; i++) {
            if (strcmp(l->a[i].subject, key) == 0) {
                printf("Найдено (%d): %s %s %s %d\n",
                       i,
                       l->a[i].subject,
                       l->a[i].date,
                       l->a[i].room,
                       l->a[i].students);
                found = 1;
            }
        }
    }
    else if (field == 2) {
        char key[20];
        printf("Введите дату: ");
        scanf("%19s", key);

        for (int i = 0; i < l->size; i++) {
            if (strcmp(l->a[i].date, key) == 0) {
                printf("Найдено (%d): %s %s %s %d\n",
                       i,
                       l->a[i].subject,
                       l->a[i].date,
                       l->a[i].room,
                       l->a[i].students);
                found = 1;
            }
        }
    }
    else if (field == 3) {
        char key[20];
        printf("Введите аудиторию: ");
        scanf("%19s", key);

        for (int i = 0; i < l->size; i++) {
            if (strcmp(l->a[i].room, key) == 0) {
                printf("Найдено (%d): %s %s %s %d\n",
                       i,
                       l->a[i].subject,
                       l->a[i].date,
                       l->a[i].room,
                       l->a[i].students);
                found = 1;
            }
        }
    }
    else if (field == 4) {
        int key;
        printf("Введите количество студентов: ");
        scanf("%d", &key);

        for (int i = 0; i < l->size; i++) {
            if (l->a[i].students == key) {
                printf("Найдено (%d): %s %s %s %d\n",
                       i,
                       l->a[i].subject,
                       l->a[i].date,
                       l->a[i].room,
                       l->a[i].students);
                found = 1;
            }
        }
    }
    else {
        printf("Неверное поле!\n");
        return;
    }

    if (!found) {
        printf("Ничего не найдено.\n");
    }
}

int cmp(Exam x, Exam y, int field) {
    if (field == 1) {
        return strcmp(x.subject, y.subject);
    }
    if (field == 2) {
        return strcmp(x.date, y.date);
    }
    if (field == 3) {
        return strcmp(x.room, y.room);
    }
    if (field == 4) {
        return x.students - y.students;
    }

    return 0;
}

void sort_list(List *l, int field) {
    if (l->size <= 1) {
        printf("Сортировка не требуется.\n");
        return;
    }

    for (int i = 0; i < l->size - 1; i++) {
        for (int j = 0; j < l->size - 1 - i; j++) {
            if (cmp(l->a[j], l->a[j + 1], field) > 0) {
                Exam temp = l->a[j];
                l->a[j] = l->a[j + 1];
                l->a[j + 1] = temp;
            }
        }
    }

    printf("Список отсортирован.\n");
}


void menu() {
    printf("\n===== МЕНЮ =====\n");
    printf("1  - Добавить элемент\n");
    printf("2  - Показать все элементы\n");
    printf("3  - Редактировать элемент по индексу\n");
    printf("4  - Поиск\n");
    printf("5  - Удалить последний элемент\n");
    printf("6  - Вставить элемент на позицию\n");
    printf("7  - Удалить элемент по индексу\n");
    printf("8  - Сортировка\n");
    printf("9  - Расширить память на N\n");
    printf("10 - Освободить память вручную\n");
    printf("0  - Выход\n");
    printf("Выбор: ");
}


int main() {
    List l;
    init(&l);

    int choice;

    while (1) {
        menu();
        scanf("%d", &choice);

        if (choice == 0) {
            break;
        }
        else if (choice == 1) {
            Exam e = input_exam();
            push_back(&l, e);
        }
        else if (choice == 2) {
            print_all(&l);
        }
        else if (choice == 3) {
            int idx;
            printf("Введите индекс: ");

scanf("%d", &idx);
            edit(&l, idx);
        }
        else if (choice == 4) {
            search(&l);
        }
        else if (choice == 5) {
            pop_back(&l);
        }
        else if (choice == 6) {
            int pos;
            printf("Введите позицию: ");
            scanf("%d", &pos);
            Exam e = input_exam();
            insert_at(&l, pos, e);
        }
        else if (choice == 7) {
            int idx;
            printf("Введите индекс: ");
            scanf("%d", &idx);
            remove_at(&l, idx);
        }
        else if (choice == 8) {
            int field;
            printf("По какому полю сортировать?\n");
            printf("1 - Предмет\n");
            printf("2 - Дата\n");
            printf("3 - Аудитория\n");
            printf("4 - Количество студентов\n");
            printf("Выбор: ");
            scanf("%d", &field);

            if (field < 1 || field > 4) {
                printf("Неверное поле!\n");
            } else {
                sort_list(&l, field);
            }
        }
        else if (choice == 9) {
            int n;
            printf("Введите N: ");
            scanf("%d", &n);

            if (n > 0) {
                expand_by(&l, n);
            } else {
                printf("N должно быть больше 0.\n");
            }
        }
        else if (choice == 10) {
            clear_and_free(&l);
            printf("Память освобождена вручную.\n");
        }
        else {
            printf("Нет такой команды.\n");
        }
    }

    clear_and_free(&l);
    return 0;
}
