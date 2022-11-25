#include <stdio.h>
#include <stdlib.h>

size_t *tableGet(size_t *table, size_t rowSize, size_t row, size_t column)
{
    return table + rowSize * row + column;
}

size_t min(size_t a, size_t b)
{
    return a < b ? a : b;
}

int main()
{
    const size_t MAX = __UINT64_MAX__;

    size_t n, m;
    scanf("%lu %lu", &n, &m);
    size_t *table = calloc(n * n, sizeof(size_t));

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            if (i == j)
            {
                continue;
            }
            *tableGet(table, n, i, j) = __UINT64_MAX__;
        }
    }

    for (size_t i = 0; i < m; ++i)
    {
        size_t first, last;
        size_t len;
        scanf("%lu %lu %lu", &first, &last, &len);
        *tableGet(table, n, first, last) = len;
    }

    size_t k;
    scanf("%lu", &k);

    size_t *capitals = calloc(k, sizeof(size_t));

    for (size_t i = 0; i < k; ++i)
    {
        scanf("%lu", capitals + i);
    }

    for (size_t l = 0; l < n; ++l)
    {
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = 0; j < n; ++j)
            {
                size_t *a = tableGet(table, n, i, j);
                size_t *b = tableGet(table, n, i, k);
                size_t *c = tableGet(table, n, k, j);

                if (*b < MAX && *c < MAX && *a < *b + *c)
                {
                    *a = *b + *c;
                }
            }
        }
    }

    size_t t = n - k;
    for (size_t i = 0; i < t; ++i)
    {
    }
}