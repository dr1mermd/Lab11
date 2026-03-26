#ifndef DATA_H
#define DATA_H

#define STR 50

typedef struct {
    char subject[STR];
    char date[20];
    char room[20];
    int students;
} Exam;

typedef struct {
    Exam *a;
    int size;
    int cap;
} List;

void readLine(char *buf, int size);

void init(List *l);
int expand_by(List *l, int add);
void freeList(List *l);

void inputExam(Exam *e);
void addExam(List *l);
void showAll(const List *l);
void editExam(List *l);
void searchBySubject(const List *l);
void sortBySubject(List *l);

int saveToFile(const List *l, const char *filename);
int loadFromFile(List *l, const char *filename);

#endif