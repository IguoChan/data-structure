#include "list.h"

list_t *list_create(void)
{
    list_t *list;

    list = malloc(sizeof(list_t));
    if (!list)
        return NULL;

    list->head = list->tail = NULL;
    list->cnt = 0;

    return list;
}

/*
1. Set the node's successor node (node->next) to NULL;
2. If the linked list is empty, it shows this node is the first node, point the head pointer (list->head) of the linked list to this node; 
    else, set the successor node of the node pointed to by the tail pointer of the linked list (list-> >tail->next) set to this node;
3. Set the predecessor node of this node to the node pointed to by the tail pointer of the linked list;
4. Point the tail pointer of the linked list to this node;
*/
int list_append(list_t *list, void *data)
{
    node_t *node;

    if (!list || !data)
        return -1;

    node = malloc(sizeof(node_t));
    if (!node)
        return -1;
    node->data = data;

    /* step 1 */
    node->next = NULL;

    /* step 2 */
    if (!list->head)
        list->head = node;
    else
        list->tail->next = node;

    /* step 3 */
    node->prev = list->tail;

    /* step 4 */
    list->tail = node;

    list->cnt++;

    return 0;
}

/*
1. Set the predecessor node (node->prev) of this node to NULL;
2. If the linked list is empty, it shows this node is the first node, point the tail pointer (list->tail) of the linked list to this node; 
    else, set the predecessor node of the node pointed to by the head pointer of the linked list (list-> >head->prev) set to this node;
3. Set the successor node of this node to the node pointed to by the head pointer of the linked list;
4. Point the head pointer of the linked list to this node;
*/
int list_prepend(list_t *list, void *data)
{
    node_t *node;

    if (!list || !data)
        return -1;

    node = malloc(sizeof(node_t));
    if (!node)
        return -1;
    node->data = data;

    /* step 1 */
    node->prev = NULL;

    /* step 2 */
    if (!list->tail)
        list->tail = node;
    else
        list->head->prev = node;

    /* step 3 */
    node->next = list->head;

    /* step 4 */
    list->head = node;

    list->cnt++;

    return 0;
}

/*
Similar to an array, we define the position of the linked list as 0~Count-1 (Count represents the number of nodes in the linked list), that is, we can insert data into the position pos in the range of 0~Count (when 0 is taken, it is inserted at the head, when Count is taken That means insert at the end). The logic of insertion is as follows:

1. If pos is 0, call the list_prepend function; if pos is list->cnt, call the list_append function; and return;
2. Find the node with position pos and record it as f_node;
3. Set the predecessor node of the inserted node (denoted as i_node) to the predecessor node of f_node, and set the successor node to f_node;
4. Set the successor node of the predecessor node of f_node to i_node;
5. Set the predecessor node of f_node to i_node;
*/
int list_insert_at(list_t *list, unsigned int pos, void *data)
{
    int i;
    node_t *f_node;
    node_t *i_node;

    if (!list || !data || pos > list->cnt) return -1;

    /* step 1 */
    if (pos == 0)
        return list_prepend(list, data);
    if (pos == list->cnt)
        return list_append(list, data);

    /* step 2 */
    f_node = list->head;
    for (i = 0; i < pos && f_node; i++)
        f_node = f_node->next;
    if (!f_node) return -1;

    i_node = malloc(sizeof(node_t));
    if (!i_node) return -1;

    /* step 3-5 */
    i_node->data = data;
    i_node->prev = f_node->prev;
    i_node->next = f_node;
    f_node->prev->next = i_node;
    f_node->prev = i_node;

    list->cnt++;

    return 0;
}

/*
1. Judge whether the specific node is the head node of the linked list, if it is, call the list_prepend function directly and return directly;
2. Set the predecessor node of the inserted node as the predecessor node of the specific node, and set the successor node as the specific node;
3. Set the successor node of the predecessor node of the specific node as the insertion node;
4. Set the predecessor node of a specific node as an insert node;
*/
int list_insert_before(list_t *list, node_t *node, void *data)
{
    node_t *i_node;

    if (!list || !node || !data)
        return -1;

    /* step 1 */
    if (node == list->head)
        return list_prepend(list, data);

    i_node = malloc(sizeof(node_t));
    if (!i_node) return -1;

    /* step 2-4 */
    i_node->data = data;
    i_node->prev = node->prev;
    i_node->next = node;
    node->prev->next = i_node;
    node->prev = i_node;

    list->cnt++;

    return 0;
}

/*
1. Judge whether the specific node is the end node of the linked list, if it is, call the list_append function directly and return directly;
2. Set the predecessor node of the inserted node as a specific node, and set the successor node as the successor node of the specific node;
3. Set the predecessor node of the successor node of a specific node as an insert node;
4. Set the successor node of a specific node as an insert node;
*/
int list_insert_after(list_t *list, node_t *node, void *data)
{
    node_t *i_node;

    if (!list || !node || !data)
        return -1;

    /* step 1 */
    if (node == list->tail)
        return list_append(list, data);

    i_node = malloc(sizeof(node_t));
    if (!i_node) return -1;

    /* step 2-4 */
    i_node->data = data;
    i_node->prev = node;
    i_node->next = node->next;
    node->next->prev = i_node;
    node->next = i_node;

    list->cnt++;

    return 0;
}

/*
For the known nodes in the linked list, we delete the nodes while extracting the data. The basic logic is as follows:
1. If the deleted node is the head node, the head pointer points to the successor node of the node; if it is not the head node, the successor node of the predecessor node of the pointer is set as the successor node of the node;
2. If the deleted node is a tail node, point the tail pointer to the predecessor node of the node; if it is not a tail node, set the predecessor node of the successor node of the pointer as the predecessor node of the pointer;
code show as below:
*/
void *list_retrieve_data(list_t *list, node_t *node)
{
    void *data;

    if (!list || !node)
        return NULL;

    /* step 1 */
    if (node == list->head)
        list->head = node->next;
    else
        node->prev->next = node->next;

    /* step 2 */
    if (node == list->tail)
        list->tail = node->prev;
    else
        node->next->prev = node->prev;

    list->cnt--;
    data = node->data;
    free(node);

    return data;
}

void *list_retrieve_data_at(list_t *list, unsigned int pos)
{
    int i;
    node_t *node;

    if (!list) return NULL;

    node = list->head;
    for (i = 0; i < pos && node; i++)
        node = node->next;

    return list_retrieve_data(list, node);
}

int list_remove_data(list_t *list, void *data)
{
    void *f_data;
    node_t *node;

    if (!list || !data) return -1;

    list_for_each_entry(f_data, list, node)
        if (f_data == data)
            break;

    return list_retrieve_data(list, node) ? 0 : -1;
}

void list_destory(list_t *list)
{
    void *data;
    node_t *node;

    if (!list) return;

    list_for_each_entry(data, list, node) {
        list_retrieve_data(list, node);
    }

    free(list);
}

void *list_get_data(list_t *list, unsigned int pos)
{
    int i;
    node_t *node;

    if (!list) return NULL;

    node = list->head;
    for (i = 0; i < pos && node; i ++)
        node = node->next;

    return node ? node->data : NULL;
}

void *list_get_head(list_t *list)
{
    return (list && list->head) ? list->head->data : NULL;
}

void *list_get_tail(list_t *list)
{
    return (list && list->tail) ? list->tail->data : NULL;
}

void *list_find(list_t *list, void *key, match_t match)
{
    node_t *node;

    if (!list || !match) return NULL;

    for (node = list->head; node; node = node->next)
        if (match(node->data, key))
            break;

    return node ? node->data : NULL;
}

int list_size(list_t *list)
{
    if (!list) return -1;

    return list->cnt;
}

void list_print(list_t *list)
{
    node_t *node;
    int i = 0;
    printf("[CNT:%d]: {Header} ——> ", list->cnt);
    for (node = list->head; node; node = node->next, i++)
        printf("{Node[%d]: %d} ——> ", i, *(int*)(node->data));
    printf("NULL\n");
}