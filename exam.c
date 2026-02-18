#include <stdio.h>
#include <string.h>


#define MAX 10

struct Exam {
    char subject[50];
    char date[20];
    char room[20];
    int students;
};

int main() {
    struct Exam exams[MAX];
    int count = 0;

    int choice;

    while (1) {
        printf("\n1 - Добавить экзамен\n");
        printf("2 - Показать все\n");
        printf("3 - Редактировать\n");
        printf("4 - Поиск по предмету\n");
        printf("0 - Выход\n");
        printf("Выбор: ");
        scanf("%d", &choice);

        if (choice == 0) break;

        if (choice == 1) {
            if (count == MAX) {
                printf("Массив заполнен!\n");
                continue;
            }

            printf("Предмет: ");
            scanf("%s", exams[count].subject);

            printf("Дата: ");
            scanf("%s", exams[count].date);

            printf("Аудитория: ");
            scanf("%s", exams[count].room);

            printf("Студенты: ");
            scanf("%d", &exams[count].students);

            count++;
        }

        else if (choice == 2) {
            for (int i = 0; i < count; i++) {
                printf("\n%d) %s %s %s %d",
                    i,
                    exams[i].subject,
                    exams[i].date,
                    exams[i].room,
                    exams[i].students);
            }
            if (count == 0)
                printf("Список пуст");
        }

        else if (choice == 3) {
            int i;
            printf("Введите номер: ");
            scanf("%d", &i);

            if (i < 0 || i >= count) {
                printf("Ошибка!");
                continue;
            }

            printf("Новый предмет: ");
            scanf("%s", exams[i].subject);

            printf("Новая дата: ");
            scanf("%s", exams[i].date);

            printf("Новая аудитория: ");
            scanf("%s", exams[i].room);

            printf("Новое кол-во студентов: ");
            scanf("%d", &exams[i].students);
        }

        else if (choice == 4) {
            char key[50];
            printf("Введите предмет: ");
            scanf("%s", key);

            int found = 0;
            for (int i = 0; i < count; i++) {
                if (strcmp(exams[i].subject, key) == 0) {
                    printf("\nНайдено: %s %s %s %d",
                        exams[i].subject,
                        exams[i].date,
                        exams[i].room,
                        exams[i].students);
                    found = 1;
                }
            }

            if (!found)
                printf("Ничего не найдено");
        }
    }

    return 0;
}