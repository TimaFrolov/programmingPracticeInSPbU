#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

#define uint unsigned int

// *a = 0xffffffffffffffffUL => b = <table> pointer
// *a = 0xfffffffffffffffeUL => b = <capital> pointer
// In other cases, compare a and b
int closerTo(const void *a, const void *b)
{
    static Graph *graph = NULL;
    static uint capital = 0;

    if (*(uint *)a < 0xfffffffeUL)
    {
        return graphGet(graph, capital, *(uint *)a) - graphGet(graph, capital, *(uint *)b);
    }

    switch (*(uint *)a)
    {
    case 0xffffffffUL:
    {
        graph = (Graph *)b;
        return 0;
    }
    case 0xfffffffeUL:
    {
        capital = *(uint *)b;
        return 0;
    }
    }
    return 0;
}

int main()
{
    char fileName[101] = {0};
    printf("Enter file path with data (no longer than 100 symbols): ");
    int scanResult = scanf("%s", fileName);
    while (scanResult == 0 || fileName[100] != 0)
    {
        printf("Incorrect input! Enter no more than 100 symbols: ");
        for (size_t i = 0; i < 101; ++i)
        {
            fileName[i] = 0;
        }
        scanResult = scanf("%s", fileName);
    }

    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Can't open file on given path!\n");
        return -1;
    }

    uint nodesAmount;
    size_t verticesAmount;
    fscanf(file, "%u %lu", &nodesAmount, &verticesAmount);

    Graph *graph = NULL;
    Error error = createGraph(&graph, nodesAmount);
    if (error == MemoryAllocationError)
    {
        printf("Error allocating memory\n");
        fclose(file);
        return -1;
    }

    for (size_t i = 0; i < verticesAmount; ++i)
    {
        uint first, second;
        size_t len;
        fscanf(file, "%u %u %lu", &first, &second, &len);
        graphSet(graph, first, second, len);
    }

    uint capitalsAmount;
    fscanf(file, "%u", &capitalsAmount);

    uint *capitals = calloc(capitalsAmount, sizeof(uint));
    bool *usedCities = calloc(nodesAmount, sizeof(bool));
    if (capitals == NULL || usedCities == NULL)
    {
        printf("Error allocating memory\n");
        fclose(file);
        graphFree(graph);
        free(capitals);
        free(usedCities);
        return -1;
    }

    for (uint i = 0; i < capitalsAmount; ++i)
    {
        fscanf(file, "%u", capitals + i);
        usedCities[capitals[i]] = -1;
    }

    fclose(file);

    graphCalculate(graph);

    uint *closestTable = calloc(capitalsAmount * (nodesAmount - capitalsAmount), sizeof(uint));
    if (closestTable == NULL)
    {
        printf("Error allocating memory\n");
        graphFree(graph);
        free(capitals);
        free(usedCities);
        return -1;
    }

    for (uint city = 0,
              curIndex = 0;
         city < nodesAmount; ++city)
    {
        if (!usedCities[city])
        {
            for (uint capital = 0; capital < capitalsAmount; ++capital)
            {
                closestTable[(nodesAmount - capitalsAmount) * capital + curIndex] = city;
            }
            ++curIndex;
        }
    }

    uint *countries = calloc(nodesAmount, sizeof(uint));
    if (countries == NULL)
    {
        printf("Error allocating memory\n");
        graphFree(graph);
        free(capitals);
        free(usedCities);
        free(closestTable);
        return -1;
    }

    uint code = 0xffffffffUL;
    closerTo((void *)&code, (void *)graph);
    code--;
    for (uint i = 0; i < capitalsAmount; ++i)
    {
        closerTo((void *)&code, (void *)&capitals[i]);
        qsort(closestTable + (size_t)i * (nodesAmount - capitalsAmount), nodesAmount - capitalsAmount, sizeof(uint), closerTo);
    }

    graphFree(graph);

    // Before <amountOfBigCountries>, country size equals to <countrySize> + 1, after it equals to <countrySize>
    uint amountOfBigCountries = (nodesAmount - capitalsAmount) % capitalsAmount;
    uint countrySize = nodesAmount / capitalsAmount;
    if (amountOfBigCountries == 0)
    {
        amountOfBigCountries = capitalsAmount;
        countrySize--;
    }

    for (uint i = 0; i <= amountOfBigCountries; ++i)
    {
        countries[(countrySize + 1) * i] = capitals[i];
    }
    for (uint i = amountOfBigCountries + 1; i < capitalsAmount; ++i)
    {
        countries[countrySize * i + amountOfBigCountries] = capitals[i];
    }

    free(capitals);

    uint *curIndicies = calloc(capitalsAmount, sizeof(uint));
    if (curIndicies == NULL)
    {
        printf("Error allocating memory\n");
        free(usedCities);
        free(closestTable);
        free(countries);
        return -1;
    }

    for (uint i = 0; i < countrySize + 1; ++i)
    {
        for (uint capital = 0; capital <= amountOfBigCountries; ++capital)
        {
            while (curIndicies[capital] < nodesAmount - capitalsAmount && usedCities[closestTable[(nodesAmount - capitalsAmount) * capital + curIndicies[capital]]])
            {
                ++curIndicies[capital];
            }
            if (curIndicies[capital] == nodesAmount - capitalsAmount)
            {
                break;
            }
            countries[(countrySize + 1) * capital + i + 1] = closestTable[(nodesAmount - capitalsAmount) * capital + curIndicies[capital]];
            usedCities[closestTable[(nodesAmount - capitalsAmount) * capital + curIndicies[capital]]] = capital + 1;
            ++curIndicies[capital];
        }
        for (uint capital = amountOfBigCountries + 1; capital < capitalsAmount; ++capital)
        {
            while (curIndicies[capital] < nodesAmount - capitalsAmount && usedCities[closestTable[(nodesAmount - capitalsAmount) * capital + curIndicies[capital]]])
            {
                ++curIndicies[capital];
            }
            if (curIndicies[capital] == nodesAmount - capitalsAmount)
            {
                break;
            }
            countries[countrySize * capital + amountOfBigCountries + i + 1] = closestTable[(nodesAmount - capitalsAmount) * capital + curIndicies[capital]];
            usedCities[closestTable[(nodesAmount - capitalsAmount) * capital + curIndicies[capital]]] = capital + 1;
            ++curIndicies[capital];
        }
    }

    free(usedCities);
    free(closestTable);
    free(curIndicies);

    for (uint i = 0; i < amountOfBigCountries; ++i)
    {
        printf("Государство %i: ", i);
        for (size_t j = 0; j < countrySize + 1; ++j)
        {
            printf("%u ", countries[(countrySize + 1) * i + j]);
        }
        printf("\n");
    }
    for (uint i = amountOfBigCountries; i < capitalsAmount; ++i)
    {
        printf("Государство %u: ", i);
        for (size_t j = 0; j < countrySize; ++j)
        {
            printf("%u ", countries[countrySize * i + amountOfBigCountries + j]);
        }
        printf("\n");
    }

    free(countries);

    return 0;
}