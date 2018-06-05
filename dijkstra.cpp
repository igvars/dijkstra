#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SIZE 4

void dijkstra()
{
  int a[SIZE][SIZE]; // матрица связей
  int d[SIZE]; // минимальное расстояние
  int v[SIZE]; // посещенные вершины
  int temp;
  int minindex, min;


  int nodeStart, nodeEnd;
  printf("\nВведите начальную вершину\n");
  scanf("%d", &nodeStart);
  printf("Введите конечную вершину\n");
  scanf("%d", &nodeEnd);

  FILE *myFile;
  myFile = fopen("graf.txt", "r");

  //read file into array
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++) 
    {
      fscanf(myFile, "%d", &a[i][j]);
    } 
  }
  fclose(myFile);
  // Вывод матрицы связей
  for (int i = 0; i<SIZE; i++)
  {
    for (int j = 0; j<SIZE; j++)
      printf("%5d ", a[i][j]);
    printf("\n");
  }
  //Инициализация вершин и расстояний
  for (int i = 0; i<SIZE; i++)
  {
    d[i] = 10000;
    v[i] = 1;
  }
  d[nodeStart-1] = 0;
  // Шаг алгоритма
  do {
    minindex = 10000;
    min = 10000;
    for (int i = 0; i<SIZE; i++)
    { // Если вершину ещё не обошли и вес меньше min
      if ((v[i] == 1) && (d[i]<min))
      { // Переприсваиваем значения
        min = d[i];
        minindex = i;
      }
    }
    // Добавляем найденный минимальный вес
    // к текущему весу вершины
    // и сравниваем с текущим минимальным весом вершины
    if (minindex != 10000)
    {
      for (int i = 0; i<SIZE; i++)
      {
        if (a[minindex][i] > 0)
        {
          temp = min + a[minindex][i];
          if (temp < d[i])
          {
            d[i] = temp;
          }
        }
      }
      v[minindex] = 0;
    }
  } while (minindex < 10000);



  // Вывод кратчайших расстояний до вершин
  printf("\nКратчайшие расстояния до вершин: \n");
  for (int i = 0; i<SIZE; i++)
    printf("%5d ", d[i]);

  // Восстановление пути
  int ver[SIZE]; // массив посещенных вершин
  int end = nodeEnd - 1; // индекс конечной вершины = 5 - 1
  ver[0] = end + 1; // начальный элемент - конечная вершина
  int k = 1; // индекс предыдущей вершины
  int weight = d[end]; // вес конечной вершины

  for (int j = 0; j<SIZE; j++) {
    for(int i=0; i<SIZE; i++) // просматриваем все вершины
    {
      if (a[end][i] != 0)   // если связь есть
      {
        int temp = weight - a[end][i]; // определяем вес пути из предыдущей вершины
        if (temp == d[i]) // если вес совпал с рассчитанным
        {                 // значит из этой вершины и был переход
          weight = temp; // сохраняем новый вес
          end = i;       // сохраняем предыдущую вершину
          ver[k] = i + 1; // и записываем ее в массив
          k++;
        }
      }
    }
  }
  // Вывод пути (начальная вершина оказалась в конце массива из k элементов)
  printf("\nВывод кратчайшего пути\n");
  myFile = fopen("result.txt", "w");
  for (int i = k-1; i>=0; i--) {
    printf("%3d ", ver[i]);
    fprintf(myFile, "%d ", ver[i]);
  }
  fclose(myFile);

} 

int main()
{
  dijkstra();
  getchar(); getchar();
  return 0;
}
