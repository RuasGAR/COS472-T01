#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define N_MAX 18000

double generate_random_num() {
    double n = (double)rand() / RAND_MAX;
    return n;
}

// FUNÇÕES DE INICIALIZAÇÃO

void fill_vector(double *vec_ptr,int size) {

    for (int i = 0; i < size; i++)
    {
        *(vec_ptr+i) = generate_random_num(); 
    }
    
} 

void fill_matrix(double **matrix_ptr, int size) {
    

    for (int i = 0; i < size; i++)
    {

        *(matrix_ptr+i) = malloc(sizeof(double)*size);        
        
        for (int j = 0; j < size; j++)
        {
            matrix_ptr[i][j] = generate_random_num();
        }
    }

}

// Funções para liberar a memória
void free_all(double **matrix_ptr,double *x_ptr, double *b_ptr,int size){

    for (int i = 0; i < size; i++)
    {
        free(matrix_ptr[i]);
    }
    
    free(matrix_ptr);
    free(b_ptr);
    free(x_ptr);
}



// Multiplicação -> alterada para multiplicar pela coluna
/* 
    Diferentemente do código que estamos acostumados, essa multiplicação funcionará um 
    pouco diferente. 

    Vamos ter de passar por cada coluna, depois iterar sobre cada linha multiplicando
    o item [i][j] pelo correspondente x[i]

 */
void matrix_mult(double **matrix_ptr, double *x_ptr, double*b_ptr, int size) {

    for (int j = 0; j < size; j++)
    {
        int acc = (double)0;
        for (int i = 0; i < size; i++)
        {
            acc += (matrix_ptr[i][j]*x_ptr[j]);         
        }
        b_ptr[j] = acc;
    } 
}



void study_case() {

    int nums[5] = {2000,4000,8000,16000,N_MAX};
    int cur_size;
    clock_t t_start,t_end;
    double exe_time;
    FILE *f;
    char c;

    f = fopen("../../experiments/matrix_column_row_xp_C.txt", "w+");

    for (int i = 0; i < 5 ; i++)
    {
        cur_size = nums[i];

        // Só pra evitar boilerplate do tamanho.
        int vec_size = sizeof(double)*cur_size;
        
        // Alocação para cada um
        double **matrix = malloc(sizeof(double*)*cur_size);
        double *x = malloc(vec_size);
        double *b = malloc(vec_size);


        // Inicialização pra cada um
        fill_matrix(matrix,cur_size);
        fill_vector(x,cur_size);
        fill_vector(b,cur_size);  

        // MULTIPLICAÇÃO
        t_start = clock();
        matrix_mult(matrix, x, b, cur_size);
        t_end = clock();
        exe_time = ((double)(t_end - t_start))/CLOCKS_PER_SEC;

        free_all(matrix, x, b, cur_size);

        fprintf(f,"%d;%0.8lf\n", cur_size,exe_time);

    }
    
    fclose(f);
}

//Main
int main(int argc, char const *argv[])
{
    
    srand(time(NULL));
    study_case();
    
}
