#include  <stdio.h>
#include <stdlib.h>

struct node {
        int num;
        struct node *next;
};

struct node* new(int num) {
        struct node *n = (struct node*) malloc(sizeof(struct node));
        n->num = num;
        n->next = NULL;
        return n;
}

void print(struct node* head) {
        struct node *ptr = head;
        printf("\n");
        while(ptr) {
                printf("%d -> ", ptr->num);
                ptr = ptr->next;
        }
        printf("\n");
}

void rem(struct node *head, int num) {
        struct node* ptr = head;
        struct node *prev = head;

        while (ptr)
        {
                if (ptr->num == num) {
                        // found
                        prev->next = ptr->next;
                        break;
                }
                prev = ptr;
                ptr= ptr->next;
        }

}

void middlenode(struct node *head) {
        struct node *ptr = head;
        struct node *slow = head, *fast = head;
        while(fast != NULL && fast->next != NULL) {
                slow = slow->next;
                fast = fast->next->next;
        }
        printf("Middle node: %d\n", slow->num);
}


void printrev(struct node *head) {
        if (head == NULL) return;
        printrev(head->next);
        printf("%d -> ",head->num);
}

struct node * revlist(struct node * head) {
        struct node *curr  = head, *prev = NULL, *nxt = NULL;
        while(curr != NULL) {
                nxt = curr->next;
                curr -> next = prev;
                prev = curr;
                curr =  nxt;
        }
        struct node *ptr = prev;
        while (ptr !=NULL) {
                printf("%d -> ", ptr->num);
                ptr = ptr->next;
        }

        return prev;
}

void loop(struct node * head, int end1, int end2) {
        struct node *ptr = head;
        struct node *endp1 = NULL, *endp2 = NULL;
        while(ptr) {
                if (ptr->num == end1) endp1 = ptr;
                else if (ptr->num == end2) endp2 = ptr;
                ptr = ptr->next;
        }
        endp2->next = endp1;
}

void loop_detect(struct node* head) {
        struct node *slow = head, *fast = head;
        while(fast != NULL && fast->next != NULL)
        {
                slow = slow->next;
                fast = fast->next->next;
                if (slow == fast)
                {
                        slow  = head;
                        while (slow != fast)
                        {
                                slow =  slow->next;
                                fast = fast->next;
                        }
                        printf ("LOOP at node : %d\n", slow->num);
                        return;;
                }
        }
        return;
}

int main()
{
        struct node *head = new(1);
        struct node *ptr = head;
        for (int i =2 ; i<10; i++) {
                ptr->next = new(i);
                ptr = ptr->next;
        }
        print(head);
        rem(head, 4);
        printf ("=========REMOVE============\n");
        print(head);
        printf ("=========MIDDLE NODE============\n");
        middlenode(head);
        //printf("========= REVERSE PRINT ===========\n");
        //printrev(head);
        printf("\n");

        printf("rev list:\n");
        struct node * rev = revlist(head);
        head = rev;
        printf("\n");
        //print(head);






        loop(head, 3,7);
        printf ("=========LOOP============\n");
        //print(head);
        printf ("=========LOOP DETECT============\n");
        loop_detect(head);
        return 0;


}
