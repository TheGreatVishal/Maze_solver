// Maze Solver
// we can only move on 1 in this maze

#include <stdio.h>
#include <stdlib.h>

struct position
{
    int r; // current-row
    int c; // current-col
};
typedef struct position pos;

struct node // node for linked list to store visited positions
{
    pos position;
    struct node *next;
};
typedef struct node node;

struct node2 // node for stack to store head of possible paths
{
    node *head;     // head of possible paths
    pos checkpoint; // checkpoint from where these paths originates
    struct node2 *next;
};
typedef struct node2 stack_node;

// insert checkpoint at start (stack)
node *insert_at_start(node *head, pos data)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->position = data;
    temp->next = NULL;

    if (head == NULL)
    {
        head = temp;
    }
    else
    {
        temp->next = head;
        head = temp;
    }

    return head;
}

// inserting at end of linked list to store visited path
// also used to enqueue the coordinates is queue of possible coordinates
node *insert_at_end(node *head, pos data)
{
    node *temp = (node *)malloc(sizeof(node));

    temp->position = data;
    temp->next = NULL;

    if (head == NULL)
    {
        head = temp;
    }
    else
    {
        node *ptr = head;

        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = temp;
    }

    return head;
}

pos latest_position_of_visited_path(node *head)
{
    node *ptr = head;

    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }

    return ptr->position;
}

// to check if a position is already visited
int isPositionVisited(node *visitedPositions, pos newPosition)
{
    node *ptr = visitedPositions;
    while (ptr != NULL)
    {
        if (ptr->position.r == newPosition.r && ptr->position.c == newPosition.c)
        {
            return 1; // Position is visited
        }
        ptr = ptr->next;
    }
    return 0; // Position is not visited
}

int is_coordinate_present_in_possible_coordinate_stack(stack_node *stack_head, pos check_position)
{
    stack_node *ptr = stack_head;
    while (ptr != NULL)
    {
        node *ptr2 = ptr->head;

        while (ptr2 != NULL)
        {
            if ((ptr2->position.r == check_position.r) && ptr2->position.c == check_position.c)
            {
                return 1;
            }
            ptr2 = ptr2->next;
        }

        ptr = ptr->next;
    }
    return 0;
}

int is_coordinate_present_in_tried_path(stack_node *stack_head, pos check_position)
{
    stack_node *ptr = stack_head;
    while (ptr != NULL)
    {
        node *ptr2 = ptr->head;

        while (ptr2 != NULL)
        {
            if ((ptr2->position.r == check_position.r) && ptr2->position.c == check_position.c)
            {
                return 1;
            }
            ptr2 = ptr2->next;
        }

        ptr = ptr->next;
    }
    return 0;
}

// will return queue's head which contains possible coordinates to move
// void possible_coordinates_to_move(int rows, int cols, int maze[rows][cols], pos current_pos, node *visitedPositions)
node *possible_coordinates_to_move(int rows, int cols, int maze[rows][cols], pos current_pos, node *visitedPositions, stack_node *stack_head, stack_node *tried_path)
{
    node *head = NULL;
    // 1st case
    int r = current_pos.r - 1;
    int c = current_pos.c - 1;
    if (r >= 0 && c >= 0)
    {
        if (maze[r][c] == 1)
        {
            pos check_position;
            check_position.r = r;
            check_position.c = c;
            if ((isPositionVisited(visitedPositions, check_position) == 0) && (is_coordinate_present_in_possible_coordinate_stack(stack_head, check_position) == 0) && (is_coordinate_present_in_tried_path(tried_path, check_position) == 0))
            {
                pos move;
                move.r = r;
                move.c = c;
                head = insert_at_end(head, move);
            }
        }
    }

    // 2nd case
    r = current_pos.r - 1;
    c = current_pos.c;
    if (r >= 0)
    {
        if (maze[r][c] == 1)
        {
            pos check_position;
            check_position.r = r;
            check_position.c = c;
            if ((isPositionVisited(visitedPositions, check_position) == 0) && (is_coordinate_present_in_possible_coordinate_stack(stack_head, check_position) == 0) && (is_coordinate_present_in_tried_path(tried_path, check_position) == 0))
            {
                pos move;
                move.r = r;
                move.c = c;
                head = insert_at_end(head, move);
            }
        }
    }

    // 3rd case
    r = current_pos.r - 1;
    c = current_pos.c + 1;
    if (r >= 0 && c < cols)
    {
        if (maze[r][c] == 1)
        {
            pos check_position;
            check_position.r = r;
            check_position.c = c;
            if ((isPositionVisited(visitedPositions, check_position) == 0) && (is_coordinate_present_in_possible_coordinate_stack(stack_head, check_position) == 0) && (is_coordinate_present_in_tried_path(tried_path, check_position) == 0))
            {
                pos move;
                move.r = r;
                move.c = c;
                head = insert_at_end(head, move);
            }
        }
    }

    // 4th case
    r = current_pos.r;
    c = current_pos.c - 1;
    if (c >= 0)
    {
        if (maze[r][c] == 1)
        {
            pos check_position;
            check_position.r = r;
            check_position.c = c;
            if ((isPositionVisited(visitedPositions, check_position) == 0) && (is_coordinate_present_in_possible_coordinate_stack(stack_head, check_position) == 0) && (is_coordinate_present_in_tried_path(tried_path, check_position) == 0))
            {
                pos move;
                move.r = r;
                move.c = c;
                head = insert_at_end(head, move);
            }
        }
    }

    // 5th case
    r = current_pos.r;
    c = current_pos.c + 1;
    if (c < cols)
    {
        if (maze[r][c] == 1)
        {
            pos check_position;
            check_position.r = r;
            check_position.c = c;
            if ((isPositionVisited(visitedPositions, check_position) == 0) && (is_coordinate_present_in_possible_coordinate_stack(stack_head, check_position) == 0) && (is_coordinate_present_in_tried_path(tried_path, check_position) == 0))
            {
                pos move;
                move.r = r;
                move.c = c;
                head = insert_at_end(head, move);
            }
        }
    }

    // 6th case
    r = current_pos.r + 1;
    c = current_pos.c - 1;
    if (r < rows && c >= 0)
    {
        if (maze[r][c] == 1)
        {
            pos check_position;
            check_position.r = r;
            check_position.c = c;
            if ((isPositionVisited(visitedPositions, check_position) == 0) && (is_coordinate_present_in_possible_coordinate_stack(stack_head, check_position) == 0) && (is_coordinate_present_in_tried_path(tried_path, check_position) == 0))
            {
                pos move;
                move.r = r;
                move.c = c;
                head = insert_at_end(head, move);
            }
        }
    }

    // 7th case
    r = current_pos.r + 1;
    c = current_pos.c;
    if (r < rows)
    {
        if (maze[r][c] == 1)
        {
            pos check_position;
            check_position.r = r;
            check_position.c = c;
            if ((isPositionVisited(visitedPositions, check_position) == 0) && (is_coordinate_present_in_possible_coordinate_stack(stack_head, check_position) == 0) && (is_coordinate_present_in_tried_path(tried_path, check_position) == 0))
            {
                pos move;
                move.r = r;
                move.c = c;
                head = insert_at_end(head, move);
            }
        }
    }

    // 8th case
    r = current_pos.r + 1;
    c = current_pos.c + 1;
    if (r < rows && c < cols)
    {
        if (maze[r][c] == 1)
        {
            pos check_position;
            check_position.r = r;
            check_position.c = c;
            if ((isPositionVisited(visitedPositions, check_position) == 0) && (is_coordinate_present_in_possible_coordinate_stack(stack_head, check_position) == 0) && (is_coordinate_present_in_tried_path(tried_path, check_position) == 0))
            {
                pos move;
                move.r = r;
                move.c = c;
                head = insert_at_end(head, move);
            }
        }
    }
    return head;
}

// inserting at start
stack_node *push(stack_node *head1, node *head_2, pos check_point)
{
    stack_node *temp = (stack_node *)malloc(sizeof(stack_node));
    temp->head = head_2;
    temp->checkpoint = check_point;
    temp->next = NULL;

    if (head1 == NULL)
    {
        head1 = temp;
    }
    else
    {
        temp->next = head1;
        head1 = temp;
    }

    return head1;
}

int is_queue_empty(node *possible_coordinates)
{
    node *ptr = possible_coordinates;

    int i = 0;
    while (ptr != NULL)
    {
        i++;
        ptr = ptr->next;
    }
    if (i == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// pop function to return top element from stack
pos returning_checkpoint(stack_node **head)
{
    pos returning_position;

    if (*head == NULL)
    {
        printf("No more checkpoints");
        pos fake_position;
        fake_position.r = -1;
        fake_position.c = -1;
        return fake_position;
    }
    else
    {
        if ((*head)->head == NULL) // it means no more possible_coordinates
        {
            // deleting checkpoint
            stack_node *temp = (*head);
            (*head) = (*head)->next;
            free(temp);
        }
        else
        {
            returning_position = (*head)->checkpoint;

            // if ((*head)->head->next == NULL)
            // {
            //     stack_node *temp = (*head);
            //     (*head) = (*head)->next;
            //     free(temp);
            // }
        }

        return returning_position;
    }
}

stack_node *dequeue_stack_node(stack_node *head)
{
    stack_node *temp = head;

    if (head == NULL)
    {
        printf("\nNo more possible coordinates!");

        return head;
    }
    else
    {
        head = head->next;
    }

    free(temp);
    return head;
}

// dequeue the queue which contains possible coordinates
node *dequeue(node *head)
{
    node *temp = head;

    if (head == NULL)
    {
        printf("\nNo more possible coordinates!");

        return head;
    }
    else
    {
        head = head->next;
    }

    free(temp);
    return head;
}

// updates stack by deleting 1st element of queue which is at top
stack_node *updating_stack(stack_node *head1)
{
    if (head1 == NULL)
    {
        printf("Stack is empty, no checkpoints");
        return head1;
    }
    else
    {
        if (head1->head == NULL)
        {
            stack_node *temp = head1;
            head1 = head1->next;
            free(temp);
        }
        else
        {
            head1->head = dequeue(head1->head);
        }
        return head1;
    }
}

void insert_into_tried_path(stack_node **tried_path, node *temp_data, pos target_position)
{
    stack_node *temp = (stack_node *)malloc(sizeof(stack_node));
    temp->head = temp_data;
    temp->checkpoint = target_position;
    temp->next = NULL;

    if (*tried_path == NULL)
    {
        *tried_path = temp;
    }
    else
    {
        temp->next = *tried_path;
        *tried_path = temp;
    }
}

node *backtrack(node *head, pos target_position, stack_node **tried_path)
{
    node *ptr = head, *temp;

    while (ptr != NULL)
    {
        if ((ptr->position.r == target_position.r) && (ptr->position.c == target_position.c))
        {
            break;
        }
        ptr = ptr->next;
    }
    temp = ptr->next;
    insert_into_tried_path(tried_path, temp, target_position);
    ptr->next = NULL;
    // free(temp);
    return head;
}

node *top_queue_of_stack(stack_node *head1)
{
    return head1->head;
}

pos first_of_queue(node *queue_head)
{
    return queue_head->position;
}

void display_lines()
{
    int i = 0;
    printf("\n");
    while (i != 20)
    {
        printf("------");
        i++;
    }
    printf("\n");
}

int length_of_queue(node *head)
{
    node *ptr = head;
    int len = 0;
    while (ptr != NULL)
    {
        len++;
        ptr = ptr->next;
    }
    return len;
}

void display(node *head)
{
    node *ptr = head;
    // printf("\nDispalying visited positions : \n");
    while (ptr != NULL)
    {

        if (ptr->next == NULL)
        {
            printf("(%d, %d)", ptr->position.r, ptr->position.c);
            break;
        }
        printf("(%d, %d) -> ", ptr->position.r, ptr->position.c);
        ptr = ptr->next;
    }
}

void display2(stack_node *head)
{
    stack_node *ptr = head;
    display_lines();
    // printf("Dispalying Queue stack(top to bottom) :");
    printf("Checkpoint | path to discover\n");
    while (ptr != NULL)
    {
        printf("\n");
        printf("(%d, %d) |  ", ptr->checkpoint.r, ptr->checkpoint.c);
        display(ptr->head);
        ptr = ptr->next;
    }
    display_lines();
}

int main()
{
    pos start_pos, end_pos, current_pos;
    // int rows = 6, cols = 6;
    node *visited_positions = NULL; // head of linked-list (visited positions)
    // node *check_point = NULL;       // head of checkpoints stack
    stack_node *stack_head = NULL; // will store queue of possible_coordinates
    stack_node *tried_path = NULL; // will store queue of tried paths

    current_pos = start_pos; // initializing current position as starting point

    // int maze[6][6] = {
    //     {1, 0, 1, 0, 0, 1},
    //     {1, 0, 1, 0, 0, 0},
    //     {0, 1, 0, 1, 1, 1},
    //     {1, 0, 0, 0, 1, 0},
    //     {0, 1, 0, 1, 0, 1},
    //     {1, 0, 1, 0, 1, 1}};
    // int rows = 6, cols = 6;

    // int maze[3][3] = {
    //     {1, 0, 1},
    //     {1, 1, 1},
    //     {0, 1, 1}};
    // int rows = 3, cols = 3;

    // int maze[][1] = {{1}};
    // int rows = 1, cols = 1;

    // int maze[3][4] = {
    //     {1, 0, 1, 1},
    //     {1, 1, 1, 0},
    //     {0, 1, 0, 1}};
    // int rows = 3, cols = 4;

    // int maze[2][2] = {{1, 1},
    //                 {0, 1}};
    // int rows = 2, cols = 2;

    // int maze[3][3] = {{1, 1, 1},
    //                   {0, 0, 1},
    //                   {0, 0, 1}};
    // int rows = 3, cols = 3;

    // int maze[5][5] = {{1, 0, 1, 1, 0},
    //                  {0, 1, 1, 0, 1},
    //                  {0, 0, 0, 0, 1},
    //                  {0, 0, 0, 1, 0},
    //                  {0, 0, 0, 0, 1}};
    // int rows = 5, cols = 5;

    // int maze[5][5] = {{1, 1, 1, 1, 1},
    //                   {1, 0, 0, 0, 1},
    //                   {1, 0, 0, 0, 1},
    //                   {1, 0, 0, 0, 1},
    //                   {0, 1, 1, 1, 1}};
    // int rows = 5, cols = 5;

    int maze[7][7] = {{1, 0, 0, 0, 0, 0, 0},
                      {0, 1, 1, 1, 1, 1, 1},
                      {0, 1, 0, 0, 0, 0, 0},
                      {0, 1, 0, 0, 0, 0, 0},
                      {0, 1, 1, 1, 1, 1, 1},
                      {0, 1, 0, 1, 0, 0, 0},
                      {0, 1, 1, 1, 1, 1, 1}};
    int rows = 7, cols = 7;

    // int maze[10][10] = {
    //     {1, 1, 1, 0, 1, 0, 1, 0, 1, 0},
    //     {1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    //     {0, 1, 0, 0, 1, 0, 1, 0, 1, 0},
    //     {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    //     {1, 0, 1, 1, 1, 0, 1, 0, 1, 0},
    //     {1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    //     {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
    //     {0, 1, 1, 1, 0, 1, 0, 1, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0, 1, 1}};
    // int rows = 10, cols = 10;

    // int maze[10][10] = {
    //     {1, 1, 0, 0, 1, 1, 1, 0, 0, 0},
    //     {1, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    //     {1, 0, 1, 0, 0, 1, 0, 0, 0, 0},
    //     {1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
    //     {1, 1, 0, 1, 0, 0, 0, 1, 0, 0},
    //     {1, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    //     {1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
    //     {1, 0, 0, 0, 1, 0, 1, 0, 1, 0},
    //     {0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    //     {0, 0, 1, 0, 0, 0, 0, 0, 0, 1}};
    // int rows = 10, cols = 10;

    // int maze[5][5] = {{1, 1, 0, 0, 0},
    //                   {1, 0, 0, 0, 0},
    //                   {0, 0, 0, 0, 0},
    //                   {0, 0, 0, 0, 0},
    //                   {0, 0, 0, 0, 0}};
    // int rows = 5, cols = 5;

    // starting position
    start_pos.r = 0;
    start_pos.c = 0;

    // end position
    end_pos.r = rows - 1;
    end_pos.c = cols - 1;

    display_lines();
    printf("Given maze \n\n");
    for (int i = 0; i < rows; i++)
    {
        if (i == 0)
        {
            printf("    ");
            for (int j = 0; j < cols; j++)
            {
                printf("%d  ", j);
            }
            printf("\n  ");
            for (int j = 0; j < cols; j++)
            {
                printf("---");
            }
            printf("\n");
        }
        printf("%d | ", i);
        for (int j = 0; j < cols; j++)
        {
            printf("%d  ", maze[i][j]);
        }
        printf("\n");
    }
    display_lines();

    printf("Starting Position : (%d, %d)", start_pos.r, start_pos.c);
    printf("\nFinal Position : (%d, %d)", end_pos.r, end_pos.c);
    visited_positions = insert_at_end(visited_positions, start_pos);
    int status = 1;
    int i = 1, j = 1;
    while (1)
    {
        // display_lines();
        // printf("Step %d\n", j);
        j++;
        current_pos = latest_position_of_visited_path(visited_positions);
        if (maze[current_pos.r][current_pos.c] == 0)
        {
            status = 0; // status 0 means maze is invalid
            break;
        }
        if (current_pos.r == end_pos.r && current_pos.c == end_pos.c)
        {
            break;
        }
        // printf("Current Position : (%d, %d)\n", current_pos.r, current_pos.c);
        // making queue to hold possible coordinates
        // printf("\nPossible moves now : \n");

        // queue of possible coordinates
        node *possible_coordinates = possible_coordinates_to_move(rows, cols, maze, current_pos, visited_positions, stack_head, tried_path);

        int len_of_queue = length_of_queue(possible_coordinates);
        // printf("\nNo. of Possible coordinates : %d", len_of_queue);
        if (len_of_queue > 1)
        {
            // pushing multiple possible paths in form of queue with it's checkpoint in stack
            // current position will be checkpoint only if it takes you to multiple paths
            stack_head = push(stack_head, possible_coordinates, current_pos);

            visited_positions = insert_at_end(visited_positions, possible_coordinates->position);

            stack_head = updating_stack(stack_head); // stack of queues
        }
        else if (len_of_queue == 1)
        {
            visited_positions = insert_at_end(visited_positions, possible_coordinates->position);
        }
        else
        {
            if (stack_head == NULL)
            {
                status = 0;
                break;
            }
            // no possible paths are left
            // either we are at final position or we are stucked
            // we have to check
            // printf("\nNo ways to go now");
            node *queue_head = top_queue_of_stack(stack_head);
            pos return_to_checkpoint = returning_checkpoint(&stack_head);
            // printf("\nReturning position : (%d, %d)", return_to_checkpoint.r, return_to_checkpoint.c);

            // getting back to top checkpoint in stack of checkpoints and inserting tried coordinate in tried path also
            visited_positions = backtrack(visited_positions, return_to_checkpoint, &tried_path);

            // fetching top queue of stack of possible_coordinates

            // fetching 1st element of this top queue in visited position
            pos first_position = first_of_queue(queue_head);

            // inserting this first position in visited positions
            visited_positions = insert_at_end(visited_positions, first_position);

            stack_head = updating_stack(stack_head);

            if (stack_head->head == NULL)
            {
                stack_head = dequeue_stack_node(stack_head);
            }
        }

        // display_lines();
        // printf("Possible Coordinates : ");
        // display2(stack_head);
        // // display(possible_coordinates);
        // // printf("\nTried path : ");
        // // display2(tried_path);
        // printf("Visited Positions : ");
        // display(visited_positions);
        // printf("\nPossible Coordinates : ");
        // display2(stack_head);
        // i++;
    }
    // printf("\n\nPossible Coordinates to try : ");
    //     display2(stack_head);
    display_lines();
    if (status == 0)
    {
        printf("Path : Not Found.");
    }
    else
    {
        printf("Path : ");
        display(visited_positions);
        printf(" -> Arrived");
        int steps = length_of_queue(visited_positions);
        printf("\n\nSteps : %d", steps);
    }
    display_lines();
    printf("\n\n");
    return 0;
}