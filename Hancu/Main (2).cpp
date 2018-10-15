#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <vector>
#include <math.h>

#define ROOT 0

#define MATRIX(type,var,n,m)                \
    (var) = new type[(n) * (m)];          \
    for(size_t i = 0; i < (n) * (m); i++)   \
        (var)[i] = rand() % 5 + 1;

using std::vector;

int rank;
int size;

void createType();

struct point {
    point();
    point(int, int);

    int i;
    int j;

    void swap();

    friend bool operator==(point& left, point& right) 
    {
        return left.i == right.i && left.j == right.j;
    }
};

MPI_Datatype MPI_POINT;

void show(int* array, size_t n, size_t m, bool transposed = false);
point* getSolution(int* array, size_t n, size_t m, size_t* count);

int main(int argc, char *argv[])
{
    int n = 4, m = 6;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Type_struct(
        2, 
        (int[]){ 1, 1 }, 
        (MPI_Aint[]){ offsetof(point, i), offsetof(point, j) }, 
        (MPI_Datatype[]){ MPI_INT, MPI_INT }, 
        &MPI_POINT);
    MPI_Type_commit(&MPI_POINT);    
  
    srand(time(NULL));

    int *array_a;
    int *array_b;
    int array_length = n * m;

    if(rank == ROOT)
    {
        MATRIX(int, array_a, n, m)

        std::cout << "A:" << std::endl;
        show(array_a, n, m);
    }

    size_t count_a = 0;
    point* points_a = getSolution(array_a, n, m, &count_a);

    if(rank == ROOT)
    {
        delete[] array_a;

        std::cout << "Max:" << std::endl;
        for(size_t i = 0; i < count_a; i++)
            printf("(%d, %d)\n", points_a[i].i, points_a[i].j);

        MATRIX(int, array_b, m, n)

        std::cout << "B:" << std::endl;
        show(array_b, m, n, true);
    }

    size_t count_b = 0;
    point* points_b = getSolution(array_b, m, n, &count_b);

    if(rank == ROOT)
    {
        delete[] array_b;

        std::cout << "Max:" << std::endl;

        vector<point> result = vector<point>();
        for(size_t i = 0; i < count_b; i++) 
        {
            points_b[i].swap();
            printf("(%d, %d)\n", points_b[i].i, points_b[i].j);
            
            for(size_t j = 0; j < count_a; j++)
                if(points_b[i] == points_a[j])
                    result.push_back(points_a[j]);
            
        }
        printf("Result:\n");
        
        for(vector<point>::iterator itr = result.begin(); itr != result.end(); ++itr)
            printf("(%d, %d)\n", itr->i, itr->j);
        
    }
    
    MPI_Finalize();
}

point::point() {

}

point::point(int32_t i, int32_t j) 
{
    this->i = i;
    this->j = j;
}

void point::swap()
{
    int temp = i;
    i = j;
    j = temp;
}

void show(int* array, size_t n, size_t m, bool transposed) 
{
    if(transposed)
        for(size_t j = 0; j < m; j++, printf("\n"))
            for(size_t i = 0; i < n; i++)
                printf("%3d", array[i * m + j]);
    else
        for(size_t i = 0; i < n; i++, printf("\n"))
            for(size_t j = 0; j < m; j++)
                printf("%3d", array[i * m + j]);
}

point* getSolution(int* array, size_t n, size_t m, size_t* count) 
{
    int* sendcounts;
    int* displs;
    int length = m * (n / size);

        sendcounts = new int[size](); 
        displs = new int[size];
        int offset = 0;
        
        
        for(size_t i = 0; i < n; i++)
            sendcounts[i % size] += m;

        displs[0] = 0;
        for(size_t i = 1; i < size; i++)
            displs[i] = displs[i - 1] + sendcounts[i - 1];
        
    int* buffer = new int[sendcounts[rank]];
    MPI_Scatterv(array, sendcounts, displs, MPI_INT, buffer, sendcounts[rank], MPI_INT, ROOT, MPI_COMM_WORLD);

    //printf("\nI'm %d! I have %d values...\n", rank, sendcounts[rank]);
    
    vector<point> max_idx = vector<point>();
    int k = sendcounts[rank] / m;

    for(size_t i = 0; i < k; i++)
    {
        int max = -2147483647-1;
        vector<point> _max_idx = vector<point>();
        for(size_t j = 0; j < m; j++)
            if(max == buffer[i * m + j])
                _max_idx.push_back(point(displs[rank] / m + i, j));
            else if(max < buffer[i * m + j])
            {
                max = buffer[i * m + j];
                _max_idx.clear();
                _max_idx.push_back(point(displs[rank] / m + i, j));
            }
        
        for(vector<point>::iterator itr = _max_idx.begin(); itr != _max_idx.end(); ++itr)
            max_idx.push_back(*itr);    
    }
    
    int max_idx_length = max_idx.size();

    int* indicies_counts;
    int* offsets;

    if(rank == ROOT)
    {
        indicies_counts = new int[size];
        offsets = new int[size];
    }

    MPI_Gather(&max_idx_length, 1, MPI_INT, indicies_counts, 1, MPI_INT, ROOT, MPI_COMM_WORLD);

    point* results;
    
    if(rank == ROOT)
    {
        int _count = 0;
        for(int i = 0; i < size; i++) {
            offsets[i] = _count;
            _count += indicies_counts[i];            
            //printf("%4d", indicies_counts[i]);
        }
        //printf("\n");
        results = new point[_count];
        *count = (size_t)_count;
    }
    
    MPI_Gatherv(&max_idx[0], max_idx_length, MPI_POINT, results, indicies_counts, offsets, MPI_POINT, ROOT, MPI_COMM_WORLD);
    if(rank == ROOT) 
    {
        delete[] indicies_counts;
        delete[] offsets;
    }
    delete[] buffer;
    delete[] sendcounts;
    delete[] displs;
    return results;
}