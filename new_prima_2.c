#include <stdio.h>
#include <math.h>
#include <stdlib.h>


//            Побудова мінімального остовного дерева за методом ПРИМА
//            *******************************************************

                                      //           відведення пам'яті
                                      //  --------------------------------------------------
                                      //  m - кількість вузлів на графі
                                      //  int* vis - відвідані вузли
                                      //  int* unVis - невідвідані вузли
                                      //  int* spTree - вузли і вартість ребер остовного дерева
                                      //  int (*mtGraph)[m][m] - матриця суміжності графу 

int main() {

    int* vis;
    int* unVis;
    int m, i, j;
    const int num = 10000;

 
    // Get the number of elements for the array
    printf("Вкажить кількість вузлів на графі:");
    scanf("%d",&m);
    printf("Число узлов на графі = %d\n", m);
 
    // Динамічний розподіл пам'яті з використанням функції malloc()
    vis = (int*)malloc(m * sizeof(int));
    unVis = (int*)malloc(m * sizeof(int));
    int (*spTree)[m][3] = malloc(sizeof *spTree);

    // Перевірка: чи успішно відпрацювала malloc
    if (vis == NULL) {
        printf("Пам'ять для vis[] не виділена.\n");
        exit(0);
    }
    if (unVis == NULL) {
        printf("Пам'ять для unVis[] не виділена.\n");
        exit(0);
    }
                            // формування матриці суміжності (*mtGraph)[row][col] з файлу f18.txt
                            // --------------------------------------------------------
    FILE* prt;
    
    int row = m, col = m;
    int (*mtGraph)[row][col] = malloc(sizeof *mtGraph);
     
    // відкриття файлу f18.txt на читання
    prt = fopen("f19.txt", "r");
    if (prt == NULL) {
        printf("Не вдалося відкрити файл f18.txt ");
        exit(0);
    }
    
    char buf[10];
    char *output;
    for (i = 0; i < row; i++){
        for (j = 0; j < col; j++){
//  читання з файлу char-рядка з елементом матриці
            fscanf(prt, "%s ", buf);             
             
//  перетворення char в integer          
 
            long result = strtol(buf, &output, 10);     
//  запис елементів матриці          
            (*mtGraph)[i][j] = result;
        }  

    }
//  виведення матриці
    for (i = 0; i < row; i++){
        for (j = 0; j < col; j++){
            printf("%d\t  ", (*mtGraph)[i][j]);
            if ((*mtGraph)[i][j] == 0) {(*mtGraph)[i][j] = num;}
        }
        printf("\n");
    }

                             //  підготовка початкового стану vis[], unVis[], spTree[] 
                             //  -----------------------------------------------------
        vis[0] = 0;  vis[1] = -1;
        // Get the elements of the array
        for (i = 0; i < m; ++i) {
            unVis[i] = i;
        }
        unVis[0] = -1;
        for (i = 0; i < m; i++) {
            (*spTree)[i][0] = 0;
            (*spTree)[i][1] = 0;
            (*spTree)[i][2] = 10000;
        }

                         //  побудова мінімального остовного дерева для графу mtGraph[][] 
                         //  -------------------------------------------------------------
int n, q, b, s;

        for (n = 0; n < m-1; n++) {          //  цикл вибору ребер остовного дерева
        q = 0;
        
        while ( q < m ) {              //  цикл відвідування вузлів із списка vis[]
            
            if (vis[q] < 0) {break;}
            i = vis[q];
            s = 0;
            
            while ( s < m ) {              
                                       //  цикл вибору мін ребра від вузла vis[q] до сусідніх 
                                       //  невідвіданих вузлів із списку unVis[] 
                if (unVis[s] > 0) {
                    j = unVis[s];
                    
                    if ((*mtGraph)[i][j] != 10000 && (*mtGraph)[i][j] < (*spTree)[n][2]) 
                    { 
                        (*spTree)[n][2] = (*mtGraph)[i][j];
                        (*spTree)[n][0] = i;
                        (*spTree)[n][1] = j;
                    
                    }    
                }
            s++;
            }     //  ----------------->        end s
        q++;
        }
        //   -------------------------->        end q
         
        vis[q] = (*spTree)[n][1];    //    додати у список відвіданих вузлів
        vis[q+1] = -1;               //    додати признак кінця списку vis[]  
        int k = vis[q];
        unVis[k] = -1;               //    видалити із списку невідвіданих вузлів
        
    
    }              //   -------------------------->        end n

        
        int Sum = 0;
        printf("\n\nМін. остовне дерево\n------------------\nребро  вартість  \n");
        for (j = 0;  j< m-1; j++) {
            for (b = 0; b < 3; b++) {
                    
                    printf("%d", (*spTree)[j][b]);
                    if (b == 1) {printf("     ");}
                    else {printf(" ");}
            }
            Sum = Sum + (*spTree)[j][2];        
                    printf("\n"); 
        }    
        printf("------------\n");
        printf("Мін сума = ");
        printf("%d", Sum);

  free(spTree);
  free(mtGraph);
  return 0;
}