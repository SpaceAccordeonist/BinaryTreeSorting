#include <iostream>
#include <ctime>
#include <stack>
#include <cmath>

using namespace std;

struct Tree {
private:
    float value = NAN;				//Значение данного узла дерева
    Tree *leftBranch = nullptr;		//Ссылка на левую ветвь
    Tree *rightBranch = nullptr;	//Ссылка на правую ветвь
    bool isInizialased = false;		//Записывалось ли значение вершины (Пришлось ввести из-за проблем с NaN)
    void GetValueToStack(stack <float>* stack) {	//Заполнение отсортированного стека
        if (leftBranch == nullptr && rightBranch == nullptr) {	//Если ссылки на ветви нулевые, значит мы на крайних ветвях
            stack->push(value);									//Поэтому выписываем значение
        }
        else {
            if (leftBranch != nullptr) {				//Иначе спускаемся влево до конца и выписываем значения
                leftBranch->GetValueToStack(stack);
            }
            stack->push(value);							//Затем значения этого узла
            if (rightBranch != nullptr) {
                rightBranch->GetValueToStack(stack);	//А потом спускаемся в правую ветвь. И так для всех узлов
            }
        }
    }

public:
    Tree() {
        isInizialased = false;
        value = NAN;
        leftBranch = nullptr;
        rightBranch = nullptr;
    }
    Tree(float num) {
        isInizialased = true;
        value = num;
        leftBranch = nullptr;
        rightBranch = nullptr;
    }

    /*Добаление нового члена дерева*/
    void AddToTree(float num) {
        if (isInizialased == false) {	//Если у вершины нет значения, то присваиваем
            value = num;
            isInizialased = true;
        }
        else {							//Иначе ищем неиницилизированную вершину
            if (value > num) {			//Если value > num спускаемся в левую ветвь
                if(leftBranch == nullptr) {leftBranch = new Tree;}
                leftBranch->AddToTree(num);
            }
            if (value <= num) {			//Если value < num спускаемся в правую ветвь
                if(rightBranch == nullptr) {rightBranch = new Tree;}
                rightBranch->AddToTree(num);
            }
        }
    }

    /*Метод для вывода сразу в консоль, экономит немного памяти*/
    void Show() {
        if (leftBranch == nullptr && rightBranch == nullptr) {
            cout << value << " ";
        }
        else {
            if (leftBranch != nullptr) {
                leftBranch->Show();
            }
            cout << value << " ";
            if (rightBranch != nullptr) {
                rightBranch->Show();
            }
        }
    }

    /*Вывод в массив по ссылке*/
    enum SortingParams{MinToMax, MaxToMin};	//Параметры для вывода по возрастанию или по убыванию
    void OutputToArray(float** arrayAdress, int size, SortingParams sp) {
        stack <float> stack;
        GetValueToStack(&stack);
        if (sp == MaxToMin) {
            for (int i = 0; i < size; i++) {
                *(i+*arrayAdress) = stack.top();
                stack.pop();
            }
        }
        else if (sp == MinToMax) {
            for (int i = size - 1; i >= 0; i--) {
                *(i+*arrayAdress) = stack.top();
                stack.pop();
            }
        }
    }
};

int main() {

    cout << "Enter count of array members: ";	//Ввод количества элементов массива
    int size = 0;
    cin >> size;
    float *arr = new float[size];

    cout << "Array before sorting: ";	//Вывод изначального массива
    srand((int)time(0));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;			//Заполнение случайными числами
        cout << arr[i] << " ";
    }

    cout << endl << "Array after sorting: ";
    int start_time = clock();	//Засекаем время начала сортировки
    Tree bin_tree = Tree(arr[0]);	//Создаём новое дерево
    for (int i = 1; i < size; i++) {
        bin_tree.AddToTree(arr[i]);		//Заполняем дерево элементами массива
    }
    bin_tree.OutputToArray(&arr, size, bin_tree.MinToMax);	//Выводим отсортированные данные в массив по ссылке
    int finish_time = clock();	//Засекаем время конца сортировки

    for (int i = 0; i < size; i++) {	//Вывод отсортированного массива
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Runtime: " << (finish_time - start_time)/ 1000.0 << endl;	//Время выполнения сортировки

    delete(arr);
    system("pause");

}