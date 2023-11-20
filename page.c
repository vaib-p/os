#include<stdio.h>


#define frame_size 3

void display_frames(int frames[],int fault){
 printf("\n\n");
 for(int i=0;i<frame_size;i++){
  printf("[%d]\t",frames[i]);
 }
 printf("\t\tpage fault = %d ",fault);
}

void fcfs(int pages[],int n){
 int frames[frame_size],k=0,fault=0;
 for(int i=0;i<frame_size;i++){
  frames[i]=-1;
 
 }
 
 for(int i=0;i<n;i++){
   if(frames[k]==-1){
    frames[k]=pages[i];
    fault++;
    k=(k+1)%frame_size;
   }else{
     int match=0;
     for(int j=0;j<frame_size;j++){
      if(pages[i]==frames[j]){
       match=1;
      }
     }
     
     if(match==0){
      fault++;
      frames[k]=pages[i];
      k=(k+1)%frame_size;
     }
   }
   
   display_frames(frames,fault);
 }

}

void lru(int pages[],int n){
 int frames[frame_size],k=0,fault=0;
 for(int i=0;i<frame_size;i++){
  frames[i]=-1;
 
 }
 for(int i=0;i<n;i++){
   if(frames[k]==-1){
    frames[k]=pages[i];
    fault++;
    k=(k+1)%frame_size;
   }else{
     int match=0,select_pos=0;
     
     for(int j=0;j<frame_size;j++){
      if(pages[i]==frames[j]){
       match=1;
      }
     }
     
     if(match==0){
       int pos=i-1;;
       for(int j=0;j<frame_size;j++){
        for(int l=i-1;l>=0;l--){
         if(frames[j]==pages[l]){
          if(l<pos){
            pos=l;
            select_pos=j;
          }
          
          break;
         }
       } 
      }
      frames[select_pos]=pages[i];     
     
      fault++;
     }
     
     
   }
   
   display_frames(frames,fault);
 }

 
}





void optimal(int pages[],int n){
 int frames[frame_size],k=0,fault=0;
 for(int i=0;i<frame_size;i++){
  frames[i]=-1;
 
 }
 for(int i=0;i<n;i++){
   if(frames[k]==-1){
    frames[k]=pages[i];
    fault++;
    k=(k+1)%frame_size;
   }else{
     int match=0,select_pos=0;
     
     for(int j=0;j<frame_size;j++){
      if(pages[i]==frames[j]){
       match=1;
      }
     }
     
     if(match==0){
       int pos=i+1,present=0;
       for(int j=0;j<frame_size;j++){
       
        present=0;
        for(int l=i+1;l<n;l++){
         if(frames[j]==pages[l]){
          present=1;
          if(l>pos){
            pos=l;
            select_pos=j;
          }
          
          break;
         }
       } 
       
       if(present==0){
          select_pos=j;
          break;
       
       }
      }
      frames[select_pos]=pages[i];     
     
      fault++;
     }
     
     
   }
   
   display_frames(frames,fault);
 }

 
}
int main(){
 int pages[] = {1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6};
 int n = sizeof(pages) / sizeof(pages[0]);
 printf("\nfor FCFS:\n");
 fcfs(pages,n);
 printf("\n\nfor LRU:\n");
 lru(pages,n);
 printf("\n\nfor Optimal:\n");
 optimal(pages,n);

 return 0;
}
