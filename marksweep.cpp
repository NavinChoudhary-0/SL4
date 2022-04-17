#include<iostream>
#include<stdlib.h>
using namespace std;
struct Node{
    int data;
    bool mark;
    struct Node* next[3];
}; 
Node* arr[8];
Node* root1, *root2;

Node* newNode(int val){
	Node* star = (Node*)malloc(sizeof(Node));
	star->data = val;
	star->mark = false;
	star->next[0] = NULL;
	star->next[1] = NULL;
	star->next[2] = NULL;
	return star;
}

void initialize(){    

    Node* temp = newNode(5);
    arr[0]=temp;
    temp = newNode(1);
    arr[1]=temp;
    temp = newNode(2);
    arr[2]=temp;
    temp = newNode(9);
    arr[3]=temp;
    temp = newNode(10);
    arr[4]=temp;
    temp = newNode(7);
    arr[5]=temp;
    temp = newNode(8);
    arr[6]=temp;
    temp = newNode(3);
    arr[7]=temp;
    root1 = arr[0];//root1->5
    arr[0]->next[0] = arr[1];//5->1
    root2 = arr[1];//root2->1
    arr[1]->next[0] = arr[2];//1->2
    arr[1]->next[1] = arr[3];//1->9
    arr[1]->next[2] = arr[4];//1->10
    arr[5]->next[0] = arr[1];//7->1
    arr[5]->next[1] = arr[6];//7->8
    arr[6]->next[0] = arr[4];//8->10
    arr[7]->next[0] = arr[6];//3->8
    arr[7]->next[1] = arr[4];//3->10
    //connections done
}

void PrintNode(Node* nptr){
    if(nptr != NULL){
        int i = 0;
        cout<<nptr->data<<" = ";
        while(nptr->next[i] != NULL){
            cout<<nptr->next[i]->data<<"->";
            i++;
        }
        cout<<"NULL\n";
    }
}

void PrintHeap(){
    for(int i = 0; i < 8; i++){
        if(arr[i]!=NULL)
            PrintNode(arr[i]);
    }
}


void markNode(Node* ptr){
    if(ptr == NULL){
        return ;
    }
    Node* head = ptr;
        if(!head->mark){
            head->mark = true;
        }
        int  i = 0;
        while(i < 3 &&  head->next[i]!=NULL && !head->next[i]->mark){
            markNode(head->next[i]);
            i++;
        }
}

void sweep(){
    for(int i=0;i<8;i++)
    {
        if(arr[i]!=NULL)
        {
            if(!arr[i]->mark){
                arr[i]->next[0]=NULL;
                arr[i]->next[1]=NULL;
                arr[i]->next[2]=NULL;
                delete arr[i];
                arr[i]=NULL;
            }
        }
    }
}

int main(){
    initialize();
    cout<<"ALL THE POINTER PRESENT ON HEAP: "<<endl;
    PrintHeap();
    cout<<"POINTER WHICH ARE ACCESSIBLE(root pointers): "<<endl;
    PrintNode(root1);
    PrintNode(root2);
    markNode(root1);//marking all the nodes accessible through root1
    markNode(root2);//marking all the nodes accessible through root2
    sweep();//sweep process begin
	cout<<"HEAP ELEMENT AFTER GARBAGE COLLECTION:"<<endl;    
    PrintHeap();
} 