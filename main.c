#include <stdio.h>
#include "data.h"

int main() {
    List list;
    int choice;
    const char *filename = "exams.dat";

    init(&list);

    if (loadFromFile(&list, filename)) {
        printf("Данные загружены из файла.\n");
    } else {
        printf("Файл не найден. Создан новый список.\n");
    }

    do {
        printf("\n===== МЕНЮ =====\n");
        printf("1. Добавить экзамен\n");
        printf("2. Показать все\n");
        printf("3. Редактировать\n");
        printf("4. Поиск по предмету\n");
        printf("5. Сортировка по предмету\n");
        printf("6. Сохранить в файл\n");
        printf("7. Загрузить из файла\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");

        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addExam(&list);
                break;
            case 2:
                showAll(&list);
                break;
            case 3:
                editExam(&list);
                break;
            case 4:
                searchBySubject(&list);
                break;
            case 5:
                sortBySubject(&list);
                break;
            case 6:
                if (saveToFile(&list, filename)) {
                    printf("Данные сохранены.\n");
                }
                break;
            case 7:
                if (loadFromFile(&list, filename)) {
                    printf("Данные загружены.\n");
                } else {
                    printf("Не удалось загрузить файл.\n");
                }
                break;
            case 0:
                if (saveToFile(&list, filename)) {
                    printf("Состояние списка сохранено перед выходом.\n");
                }
                printf("Выход из программы.\n");
                break;
            default:
                printf("Неверный пункт меню.\n");
        }

    } while (choice != 0);

    freeList(&list);
    return 0;
}
