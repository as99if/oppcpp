#include<iostream>

using namespace std;

//task 1
struct list{
    double data;
    struct list *next;
};
typedef struct list node;


//task 2
node* push(node *head, int item){
    node *temp, *prev;
    if(head==NULL){
        head=new node();
        head->data=item;
        head->next=NULL;
        prev=head;
    }
    else{
        temp=new node();
        temp->data=item;
        temp->next=NULL;
        prev->next=temp;
        prev=temp;
    }

return head;
}


//task 3
void del(node *head){
    node *dead;
    cout<<"delete :";
    while(head != NULL){
        cout<<" "<<head->data;
        dead = head;
        head = head->next;

        delete(dead);
    }
    cout<<endl;
}


//task 4
double continuedFraction(node *head)
{   node *last;

    last = head;

    while(last->next != NULL){
        last=last->next;
    }

    double fraction = (double)last->data;

    if(head->next->next != NULL){
        fraction = continuedFraction(head->next);
    }

    fraction = head->data + 1/fraction;
return fraction;
}


//task 5
node* construct(){
    node *head;
    head = NULL;
    int input = 0;
    int k = 0;                                                        // task 5
    cout<<"Continued fraction, enter the first value f_"<<k<<" : ";
    cin>>input;
    head = push(head, input);           // push korte partese

    while(head){
        cout<<"enter next part denominator f_"<<k<<" (<=0 for end): ";
        cin>>input;
        head = push(head, input);       // push korte partese na****
        if(input <= 0)
            break;
    }

return head;
}

void display(node *head){
    cout<<"Display"<<endl;
    while(head != NULL){
        cout<<head->data;
        head = head->next;
    }
    cout<<endl;
}

// task6
int main(){
    node *cf1, *cf2, *cf3;

    cout.precision(15);

    cout<<"start"<<endl;
    cf1 = NULL;
    cf1 = push(cf1, 1);
    cf1 = push(cf1, 4);
    cf1 = push(cf1, 2);
    cf1 = push(cf1, 1);
    cf1 = push(cf1, 7);
    cout<<"cf1 = 123/100 = "<<continuedFraction(cf1)<<endl;
    del(cf1);

    cf2 = NULL;
    cf2 = push(cf2, 1);
    cf2 = push(cf2, 1);
    cf2 = push(cf2, 2);
    cf2 = push(cf2, 3);

    cout<<"cf2 = 17/10 = "<<continuedFraction(cf2)<<endl;
    del(cf2);
/*
    cf3 = NULL;
    cf3 = push(cf3, 1);
    cf3 = push(cf3, 2);
    cf3 = push(cf3, 2);
    cf3 = push(cf3, 2);
    cf3 = push(cf3, 2);
    cf3 = push(cf3, 2);             // evabe hoy
    cf3 = push(cf3, 2);
    cf3 = push(cf3, 2);
    cf3 = push(cf3, 2);
    cout<<"cf3 = 17/10 = "<<continuedFraction(cf3)<<endl;
    del(cf3);
*/
    cf3 = NULL;
    cf3 = construct();
    display(cf3);
    cout<<"value inputted continued function "<<continuedFraction(cf3)<<endl;
    del(cf3);
            // evabe hoitese na , constructor e loop er moddhe kono push hoitese na -_-
return 0;
}


