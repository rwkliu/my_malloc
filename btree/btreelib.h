/*
 * btreelib.h
 */

/*
 * data must be malloced separately so library is flexible to handle arbitrary
 *  number of data fields
 */
typedef struct node_s {
    void *data;
    struct node_s *left;
    struct node_s *right;
} NODE;
