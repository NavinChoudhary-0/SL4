#include<iostream>
using namespace std;

struct Node{
    int data;
    int ref;
    struct Node* next[3];
};
Node* arr[8];
Node* root1, *root2;

Node* newNode(int val){
	Node* star = (Node*)malloc(sizeof(Node));
	star->data = val;
	star->ref = 0;
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
    
    root1 = arr[0];
    arr[0]->ref += 1;
    
    arr[0]->next[0] = arr[1];
    arr[1]->ref += 1;
    
    root2 = arr[1];
    arr[1]->ref += 1;
    
    arr[1]->next[0] = arr[2];
    arr[2]->ref += 1;
    
    arr[1]->next[1] = arr[3];
    arr[3]->ref += 1;
    
    arr[1]->next[2] = arr[4];
    arr[4]->ref += 1;
    
    arr[5]->next[0] = arr[1];
    arr[1]->ref += 1;
    
    arr[5]->next[1] = arr[6];
    arr[6]->ref += 1;
    
    arr[6]->next[0]=arr[4];
    arr[4]->ref += 1;
    
    arr[7]->next[0] = arr[6];
    arr[6]->ref += 1;

    arr[7]->next[1] =arr[4];
    arr[4]->ref += 1;
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

void countRefrence(){
    bool f = 0;
    for(int i = 0; i < 8; i++){
        if(arr[i] != NULL && arr[i]->ref == 0){
           	int j = 0;
           	while(j < 3 && arr[i]->next[j] != NULL){
               	arr[i]->next[j]->ref -= 1;
               	arr[i]->next[j] = NULL;
               	j++;
               	f = 1;
    		}
    		cout<<arr[i]->data<<" ";
            delete arr[i];
            arr[i] = NULL;
            
        }
    }
    
    if(f)
        countRefrence();
    
}
int main(){
    initialize();
    cout<<"HEAP BEFORE CLEANUP"<<endl;
    PrintHeap();
    cout<<"____________________________________________________________________________"<<endl;
    cout<<"NODES CONNECTED TO ROOT1 AND ROOT2"<<endl;
	PrintNode(root1);
    PrintNode(root2);
    cout<<"____________________________________________________________________________"<<endl;
    cout<<"DELETED NODES"<<endl;
	countRefrence();
    cout<<"\n____________________________________________________________________________"<<endl;
    cout<<"HEAP AFTER CLEANING:"<<endl;
    PrintHeap();
}