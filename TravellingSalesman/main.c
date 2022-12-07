#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <float.h>
#include <stdbool.h>

int n = 5;

void greedy_FindShortestRoute();

void generateRandomMatrix(int N, int maxCost);

int ranCostMatrix[5][5];
//int ranCostMatrix[5][5] = {
//        {-1, 10, 15, 20},
//        {10, -1, 35, 25},
//        {15, 35, -1, 30},
//        {20, 25, 30, -1}};

void generateRandomMatrix(int N, int maxCost) {
    srand(time(0));

    int tempRanCost = 0.0;


    bool edgeAdded[N + 1][N + 1];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            edgeAdded[i][j] = false;
            edgeAdded[j][i] = false;

            if (i == j) {
                ranCostMatrix[i][j] = -1;
                edgeAdded[i][j] = true;
                edgeAdded[j][i] = true;
            }
            if (edgeAdded[j][i] == false) {
                //tempRanCost = ((int) rand() / (int) (RAND_MAX) * maxCost);
                tempRanCost = 1 + (rand() % maxCost);
                ranCostMatrix[i][j] = tempRanCost;
                ranCostMatrix[j][i] = tempRanCost;
                edgeAdded[i][j] = true;
                edgeAdded[j][i] = true;
            }


        }
    }

    printf("\n");
    printf("The Randomly generated Cost Matrix is: \n");
    for (int i = 0; i < N; i++) {
        printf("Vertex: %d-->", i);

        for (int j = 0; j < N; j++) {
//            printf("%12.2lf ", ranCostMatrix[i][j]);
            printf("%12d ", ranCostMatrix[i][j]);
        }
        printf("\n");

    }
    printf("\n");
}

// I refered to the code at https://www.geeksforgeeks.org/travelling-salesman-problem-greedy-approach/ to help write
// this algorithm
void greedy_FindShortestRoute() {
    int totalDistance = 0.0;
    int counter = 0;
    int j = 0, i = 0;
    //int min = FLT_MAX;
    int min = INT_MAX;
//    int min = 100;
    bool visitRouteList[n][n];
    int vertexDegree[n];
    int degree = 1;

    // Starting from the 0th indexed
    // city i.e., the first city
    //visitedRouteList[0] = 1;
    int travelRoute[n];
    for (int k = 0; k < n; k++) {
        for (int d = 0; d < n; d++) {
            visitRouteList[k][d] = false;
            visitRouteList[d][j] = false;
        }
    }

    for (int k = 0; k < n; k++) {
        vertexDegree[k] = 0;
    }

    // Traverse the adjacency
    while (i < n && j < n) {


        if (i == j) {
            //visitRouteList[i][j] = true;
            //visitRouteList[j][i] = true;

        }
        // Corner of the Matrix
        if (counter >= n - 1) {
            break;
        }

        // If this path is unvisited then
        // and if the cost is less then min
        // update the cost

            if (j != i) {
                if (visitRouteList[i][j] != true && vertexDegree[i] < 2 && vertexDegree[j] < 2) {
                    if (ranCostMatrix[i][j] <= min) {
                        min = ranCostMatrix[i][j];
                        travelRoute[counter] = j;

                        visitRouteList[i][j] = true;
                        visitRouteList[j][i] = true;
                    }
                    visitRouteList[i][j] = true;
                }

            }
            if (j < n - 1) {
                j++;
            }
        }

//     Check all paths from the
//     ith indexed city
        // if at the last element in the column calculate the total distance
        if (j == n - 1) {
            vertexDegree[i] += degree;
            vertexDegree[travelRoute[i]] += degree;
            totalDistance += min;
//            min = FLT_MAX;
            min = INT_MAX;
            j = 0;
            degree = 1;
            i++;
            counter++;
        }
    }// end of while loop

//     Update the ending city in array
//     from city which was last visited
//    i = travelRoute[counter - 1];
//
//    for (j = 0; j < n; j++) {
//
//        if ((i != j) && ranCostMatrix[i][j] < min) {
//            min = ranCostMatrix[i][j];
//            travelRoute[counter] = j;
//        }
//    }
//    totalDistance += min;

    // Started from the node where
    // we finished as well.

    printf("Minimum Cost is: ");
//    printf("%.2lf", totalDistance);
    printf("%d", totalDistance);

    for (int m = 0; m < 5; m++) {
        printf("\nTravel Route:              Vertex Degree: ");
        printf("\n%d<-->%d                   %d has %d degrees", m, travelRoute[m], m, vertexDegree[m]);

    }
}

// Driver Code
int main() {

    // Input Matrix


    int vertices = 5;
    int maxCost = 100.0;
    generateRandomMatrix(vertices, maxCost);
    // Function Call
    //greedy_FindShortestRoute(travellingSalesmanMatrix);
    greedy_FindShortestRoute();


}

