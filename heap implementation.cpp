#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// creating heap space using array
char Array[200];

struct allocate_list_pointer{
	
	char name[20];
	int start,end;
	struct allocate_list_pointer *next,*prev;
	int size;
		
} *alloc_list; 


struct free_list_pointer{
	
	int start,end;
	struct free_list_pointer *next,*prev;
	int size;
		
} *free_list;


typedef struct allocate_list_pointer Alloc_list;
typedef struct free_list_pointer Free_list;
// alloc_list stores all the space which is allocated in the form of connectd linked list 
// free_list stores all the free space which is yet to be allocated 

void Initialise(){
	
	
	free_list = (Free_list*)malloc(sizeof(Free_list));
	free_list->start = 0;
	free_list->end = 199;
	free_list->prev = NULL;
	free_list->next = NULL;
	free_list->size = 200;
	alloc_list = NULL;
		
}
//initialises all the function at the start of the programm

char* alloc_space(int space_req,char* var_name){
	
	Free_list *tptr;
	tptr = free_list;
	
	while(tptr != NULL && tptr->size < space_req){
		tptr=tptr->next;	
	}
		//search till the space greater than equal to required space is found
		
	if(tptr != NULL){
			
	if(tptr->size == space_req){
		
		if(tptr != free_list){
			
			tptr->prev->next = tptr->next;
		    if(tptr->next != NULL){
				tptr->next->prev = tptr->prev;
			}
			
		}else{
			
			if(tptr->next != NULL){
				free_list = tptr->next;
				tptr->next->prev = NULL;
			}
		}
		
	}else{
			Free_list* temp = (Free_list*)malloc(sizeof(Free_list));
            temp->start = tptr->start + space_req;
            temp->end = tptr->end;
            temp->next = temp->prev = NULL;
            temp->size = tptr->size - space_req;
            
            if (tptr == free_list)
            {
            	free_list = free_list->next;
                temp->next = free_list;
                free_list = temp;
            }
            else
            {
                tptr->prev->next = temp;
                temp->next = tptr->next;
                temp->prev = tptr->prev;
                
                if(tptr->next)
                    tptr->next->prev = temp;
                    
            }
            
		
		}
		
		Alloc_list *new_allocate = (Alloc_list*)malloc(sizeof(Alloc_list));
		new_allocate->next = new_allocate->prev = NULL;
		new_allocate->size = space_req;
		new_allocate->start = tptr->start;
		strcpy(new_allocate->name,var_name);
		new_allocate->end = tptr->start + space_req-1; 
		
		
		if(alloc_list == NULL){
			alloc_list = new_allocate;
		}else{
			// add the alloc at the start of alloc list
			new_allocate->next = alloc_list;
			alloc_list->prev = new_allocate;
			alloc_list = new_allocate;	
		}
		printf("%d bytes of space allocated in heap....\nStarting from index %d to %d\n",space_req,new_allocate->start,new_allocate->end);
		return Array + new_allocate->start;
		
    }else{
    	printf("NO SPACE AVAILABLE!!!.....");
    	return NULL;
	}

	
}

void free_space(char var_name[]){

	Alloc_list *tptr = alloc_list;
	
	while(tptr && strcmp(tptr->name,var_name) != 0){
		tptr = tptr->next;
	}
	//search till the space is found
	
	if(tptr != NULL){
		Free_list *new_free = (Free_list*)malloc(sizeof(Free_list));
		new_free->next = new_free->prev = NULL;
        new_free->size = tptr->size;
        new_free->start = tptr->start;
        new_free->end = tptr->end;
        
		if(tptr == alloc_list){
			
        	alloc_list = alloc_list->next;
        	
		}else{
			tptr->prev->next = tptr->next;
			
            if (tptr->next != NULL)
                tptr->next->prev = tptr->prev;
            
		}
		
		free(tptr);
		
		Free_list *fptr = free_list;
		
		if(free_list == NULL){
			
			free_list = new_free;
			
		}else{
			if(new_free->end + 1 == fptr->start){
				//new_free = 10-15 fptr = 16-30
				//fptr = 10-30
				fptr->start = new_free->start;
					
			
			}else if(new_free->end < fptr->start){
	            // new_free = 10-15 fptr = 20-38
	            
				new_free->next = fptr;
				fptr->prev = new_free;
				free_list = new_free;
				
			}else{
				 
				while(fptr->next && fptr->next->start < new_free->start){
					fptr = fptr->next;
				}
				// fptr->next->start >= new_free->start then fptr->start < new_start->end
			
				Free_list *j;
				if(fptr->end + 1 == new_free->start){	
					//new_free = 10-15 fptr = 6-9
					//fptr = 6-15
					fptr->end = new_free->end;
					if(fptr->next && new_free->end+1 == fptr->next->start ){
						//fptr = 6-15 fptr->next = 16-30
						//fptr = 6-30
						fptr->end = fptr->next->end;
						j = fptr->next;
						fptr->next = fptr->next->next;
						if(fptr->next){
							fptr->next->prev = fptr;
						}
						
					}
					
				}else{
					//new_free = 10-15 fptr = 1-6
					//fptr->next =  16-30
					if(fptr->next && new_free->end+1 == fptr->next->start){
						
						fptr->next->start = new_free->start;
						
					}else{
					//new_free = 10-15 fptr = 1-4
					//fptr->next = 20-25
					new_free->prev = fptr;
					new_free->next = fptr->next;
					fptr->next = new_free;
					
					if(new_free->next)
						new_free->next->prev = new_free;
					
					}
					
				}
			
			}
			printf("Space deallocted for variable \n ");	
		}	
	}else{
		
		printf("Pointer not found, please check your input!!!...\n");
		
	}	
}

int main(){
	
	Initialise();
	int t = 1,n,space;
	char name[10];
	char *a;
	
	while(t != 0){
		printf("Enter 1 to alloc a memory\nEnter 2 to free a memory\n");
		scanf("%d",&n);
		if(n == 1){
			printf("Enter space required : ");
			scanf("%d",&space);
			fflush(stdin);
			printf("Enter variable name : ");
			gets(name);
			fflush(stdin);
			a = alloc_space(space,name);
			
		}else{
			printf("Enter the variable name for which you wnat to free space : ");
			fflush(stdin);
			gets(name);
			fflush(stdin);
			free_space(name);
		}
		printf("Enter 0 to break the loop or any other number to continue : ");
		scanf("%d",&t);
		
	}
	
	return 0;
}
 