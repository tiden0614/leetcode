#define EDGE_LIST_SIZE 5
#define NULL 0
typedef struct {
    // out edges
    int* pres;
    int  size;
    int  capacity;
    int  visited;
    int  taken;
} course;

// recursively traverse the graph
void take_courses(int num_courses, course* courses, int first_course, int* ret_list, int* ret_start) {
    // corner conditions
    if (first_course < 0 || first_course >= num_courses || courses[first_course].visited == 1) {
        return;
    }
    course* n = &(courses[first_course]);
    n->visited = 1;
    int i;
    int take_this_course = 1;
    for (i = 0; i < n->size; i++) {
        take_courses(num_courses, courses, n->pres[i], ret_list, ret_start);
        if (courses[n->pres[i]].taken == 0) {
            take_this_course = 0;
        }
    }
    if (take_this_course == 1) {
        n->taken = 1;
        ret_list[(*ret_start)++] = first_course;
    }
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findOrder(int numCourses, int** prerequisites, int prerequisitesRowSize, int prerequisitesColSize, int* returnSize) {
    *returnSize = 0;
    if (numCourses <= 0) return NULL;
    int* ret_list = (int*) malloc(numCourses * sizeof(int));
    if (numCourses == 1) {
        *ret_list = 0;
        *returnSize = 1;
        return ret_list;
    }
    
    // use an adjacency list to represent courses and prerequisites
    course* courses = (course*) malloc(numCourses * sizeof(course));
    // init the list
    int i;
    for (i = 0; i < numCourses; i++) {
        courses[i].pres = NULL;
        courses[i].size = 0;
        courses[i].capacity = 0;
        courses[i].visited = 0;
        courses[i].taken = 0;
    }
    // construct the graph using the input
    int  j;
    int  k;
    int  c;
    int* p;
    for (i = 0; i < prerequisitesColSize; i++) {
        for (j = 0; j < prerequisitesRowSize; j++) {
            if (j == 0) {
                // the course itself
                c = prerequisites[i][j];
            } else {
                // prerequisites of the course
                // increase the capacity of the array if needed
                if (courses[c].size >= courses[c].capacity) {
                    p = courses[c].pres;
                    courses[c].pres = (int*) malloc(courses[c].capacity + EDGE_LIST_SIZE);
                    courses[c].capacity += EDGE_LIST_SIZE;
                    for (k = 0; k < courses[c].size; k++) {
                        courses[c].pres[k] = p[k];
                    }
                    if (p != NULL) {
                        free(p);
                    }
                }
                courses[c].pres[courses[c].size++] = prerequisites[i][j];
            }
        }
    }
    // traverse the graph to decide the order of courses
    for (i = 0; i < numCourses; i++) {
        take_courses(numCourses, courses, i, ret_list, returnSize);
    }
    return ret_list;
}

void main() {
    int size = 0;
    int* pres = (int*) malloc(2*sizeof(int));
    *pres = 1;
    *(pres+1) = 0;
    int* ret = findOrder(2, &pres, 2, 1, &size);
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", ret[i]);
    }
    printf("\n");
    free(pres);
    free(ret);
}