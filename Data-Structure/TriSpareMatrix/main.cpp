#include <iostream>
#include <format>
#include <map>
#include <chrono>
#include <cstring>
class Timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;

public:
    Timer()
    {
        start = std::chrono::high_resolution_clock::now();
    }
    ~Timer()
    {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "Time elapsed: " << duration << " us\n";
    }
};

template <typename T>
class TriSpareMatrix
{
    friend TriSpareMatrix<int> T(const TriSpareMatrix<int> &matrix);

private:
    using Uint = unsigned int;

protected:
    Uint rows, cols, terms;
    struct Trituple
    {
        Uint row, col;
        T value;
        Trituple(Uint r = 0, Uint c = 0) : row(r), col(c) {}
        Trituple(Uint r, Uint c, T v) : row(r), col(c), value(v) {}
    };
    Trituple *TSMatrix;

public:
    TriSpareMatrix(Uint r = 0, Uint c = 0, Uint t = 0, Uint size = 0)
        : rows(r), cols(c), terms(t), TSMatrix(new Trituple[size])
    {
    }

    TriSpareMatrix(const TriSpareMatrix &other)
    {
        rows = other.rows;
        cols = other.cols;
        terms = other.terms;
        TSMatrix = new Trituple[terms];
        for (Uint i = 0; i < terms; ++i)
            TSMatrix[i] = other.TSMatrix[i];
    }

    TriSpareMatrix(TriSpareMatrix &&other)
    {
        rows = other.rows;
        cols = other.cols;
        terms = other.terms;
        TSMatrix = other.TSMatrix;
        other.TSMatrix = nullptr;
    }

    template <size_t CLOS>
    TriSpareMatrix(const T (*arr)[CLOS], int SRCrows, int SRCcols, int num)
    {
        rows = SRCrows;
        cols = SRCcols;
        terms = 0;
        TSMatrix = new Trituple[num];
        for (Uint i = 0; i < rows; ++i)
            for (Uint j = 0; j < cols; ++j)
                if (arr[i][j] != 0)
                    TSMatrix[terms++] = Trituple(i, j, arr[i][j]);
    }

    ~TriSpareMatrix()
    {
        delete[] TSMatrix;
    }

    void print()
    {
        for (Uint i = 0; i < terms; ++i)
            std::cout << std::format("({},{}):{}\n", TSMatrix[i].row, TSMatrix[i].col, TSMatrix[i].value);
    }

    TriSpareMatrix simpleTranspose()
    {
        TriSpareMatrix<T> Tmatrix(cols, rows, 0, terms);
        for (Uint col = 0; col < cols; ++col)
        {
            for (Uint row = 0; row < terms; ++row)
            {
                if (TSMatrix[row].col == col)
                {
                    Tmatrix.TSMatrix[Tmatrix.terms++] = Trituple(TSMatrix[row].col, TSMatrix[row].row, TSMatrix[row].value);
                }
            }
        }

        return Tmatrix;
    }

    TriSpareMatrix FastTranspose()
    {
        TriSpareMatrix<T> Tmatrix(cols, rows, terms, terms);
        Uint *cNum = new Uint[cols + 1]{0};
        Uint *cPos = new Uint[cols + 1];
        // 记录每一列的非零元素个数
        for (Uint i = 0; i < terms; ++i)
            ++cNum[TSMatrix[i].col];
        // 记录每一列的第一个非零元素在转置矩阵中的位置
        cPos[0] = 0;
        for (Uint i = 1; i <= cols; ++i)
            cPos[i] = cPos[i - 1] + cNum[i - 1];

        for (Uint i = 0; i < terms; ++i)
        {
            // 将每一个元素放到转置矩阵中的位置
            // cPos[] ++ 使将要存放的同一列元素位置后移一位
            Tmatrix.TSMatrix[(cPos[TSMatrix[i].col])++] = Trituple(TSMatrix[i].col, TSMatrix[i].row, TSMatrix[i].value);
        }
        delete[] cPos;
        delete[] cNum;
        return Tmatrix;
    }
};

int main()
{
    int arr[][4] = {
        {0, 0, 3, 0},
        {0, 0, 5, 7},
        {0, 2, 0, 0},
        {0, 0, 0, 0},
        {0, 10, 0, 2},
        {0, 0, 0, 0},
        {0, 0, 9, 6},
        {1, 2, 3, 4},
        {0, 0, 0, 0},
        {4, 0, 1, 5},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
        {0, 0, 9, 6},
    };
    TriSpareMatrix<int> matrix1(arr, 35, 4, 15 + 50);
    TriSpareMatrix<int> matrix2(arr, 35, 4, 15 + 50);

    // matrix.print();
    // TriSpareMatrix<int> STmatrix =
    std::cout << "Simple Transpose:" << std::endl;
    // {
    //     Timer t1;
    //     for (int i = 0; i < 1000; ++i)
    matrix1.simpleTranspose();
    // }
    matrix1.print();
    std::cout << '\n';
    // TriSpareMatrix<int> FTmatrix =
    std::cout << "Fast Transpose:" << std::endl;
    // {
    //     Timer t2;
    //     for (int i = 0; i < 1000; ++i)
    matrix2.FastTranspose();
    // }
    matrix2.print();
    return 0;
}