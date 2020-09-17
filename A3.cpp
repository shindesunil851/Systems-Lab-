#include<stdio.h> 
#include <ctime>
#include<stdio.h> 
#include<stdlib.h> 
#include <bits/stdc++.h>
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include <iostream>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<iostream>
#include <sys/types.h>
#include <vector>

using namespace std;

vector<int>Sb;
vector<int>Se;
vector<int>Lb;
vector<int>Le;

//Checks if the snake is present at the current position
void checkSn(int *pos,int ct)
{
    for(int i=0;i<Sb.size();i++)
    {
        if(Sb[i]==pos[ct])
        {
            cout<<"Player "<<ct+1<<"Got Snake at Position "<<Sb[i]<<"\n";
            pos[ct]=Se[i];
            return;
        }
    }
}

//Checks if ladder is present at the current position
void checkLd(int *pos,int ct)
{
        
    for(int i=0;i<Lb.size();i++)
    {
        if(Lb[i]==pos[ct])
        {
            cout<<"Player "<<ct+1<<"Got Ladder at Position "<<Lb[i]<<"\n";
            pos[ct]=Le[i];
            return;
        }
    }
}


int main(int argc, char *argv[])
{
	    if(argc!=4)
		return 0; 
  
  int N = atoi(argv[1]);
  //int N=stoi(argv[1]);
  int P = atoi(argv[2]);
  
  string fn=argv[3];
  

    fstream file; 
    string word, t, q; 
  
   
    // opening the file that contains the information about snakes and ladder 
    file.open(fn.c_str()); 
  
    // extracting words from the file 

    while (file >> word) 
    { 
    
        // Validating and storing the input into respective vectors
        if(word=="S")
        {
        	int x,y;
        	file>>x;
        	file>>y;
        	Sb.push_back(x);
        	Se.push_back(y);
			if(x<y)
        	{
        		cout<<"Enter valid Snake input";
        		return 0;
			}
          
		
		}
		else if(word=="L")
		{
			
        	int x,y;
        	file>>x;
        	file>>y;
        	Lb.push_back(x);
        	Le.push_back(y);
        	if(x>y)
        	{
        		cout<<"Enter Valid Ladder input";
        		return 0;
			}
            
		}
        
        
    } 
    for(int i=0;i<Lb.size();i++)
            {
                for(int j=0;j<Se.size();j++)
                {
                    if(Se[j]==Lb[i])
                    {
                        cout<<"Enter Valid Snake input";
                        return 0;
                    }
        
                }
             }
     for(int i=0;i<Sb.size();i++)
            {
                    for(int j=0;j<Le.size();j++)
                {
                            if(Le[j]==Sb[i])
                            {
                                cout<<"Enter Valid Ladder input";
                                return 0;
                            }
                }
                }
       for(int i=0;i<Sb.size();i++)
       {
           for(int j=0;j<Lb.size();j++)
                {
                   if(Sb[i]==Lb[j])
                   {
                       cout<<"Snake And Ladder Colliding\n";
                       return 0;
                   }
                }
       }


// Validation ends

    srand((unsigned) time(0));
    int finished=0;
    
    //int N=50,P=3;
    int result = 1 + (rand() % 6);
   
    for(int i=0;i<Le.size();i++)
    {
        //cout<<Le[i]<<endl;
        if(Le[i]>N || Lb[i]>N)
          {
              cout<<" Check bounds on ladder positions\n";
              return 0;
          }
        
    }

    for(int i=0;i<Se.size();i++)
    {
        //cout<<Le[i]<<endl;
        if(Sb[i]>N || Se[i]>N)
          {
              cout<<" Check bounds on snake positions\n";
              return 0;
          }
        
    }

   
    int fd1[P][2];
    int fd2[P][2];
    for(int i=0;i<P;i++)
    {
        int r1,r2;


        //Creating pipes for unidirectional communication between parent and child process
        r1=pipe(fd1[i]);
        r2=pipe(fd2[i]);
        
        if(r1==-1 || r2==-1)
        {
            cout<<"Pipe Not Created Properly";
            return 0;
            
        }
    }
    //cin>>P>>N;
    
    int pos[P]={0};
    //cout<<pos[2]<<endl;
   // int grid[N];
    
    pid_t pr[P];
                /*
                for(int i=0;i<Lb.size();i++)
                    cout<<Lb[i]<<endl;
                */
                for(int i=0;i<P;i++) // loop will run n times (n=5) 
                { 
                    //Entering the child process
                    if((pr[i]=fork())==0) 
                    { 
                    
                    //Closing the pipes when are not required anymore
                    for(int x=0; x<P; x++)
                    {
                        if(x != i)
                        {
                            close(fd1[x][0]);
                            close(fd1[x][1]);
                            close(fd2[x][0]);
                            close(fd2[x][1]);
                        }
                    }
                    //close(fd1[i][1]);


                    // Generating random values and sending to parent
                    srand((unsigned) time(0)*i);

                    while(true)
                    {
                        char data[30];
                        int check;
                        check=read(fd1[i][0],data,30);
                  
                        if(check<0)
                             exit(0);
                                
                        result = 1 + (rand() % 6);
                        
                        string mssg;
                        mssg=to_string(result);
                        

                        //Sending generated dice value to parent process
                        write(fd2[i][1],mssg.c_str(),2);
                                //perror("After Write");
                            
                    }   
                    wait(NULL);     
                    }   
                } 
                
                        
                    int counter =  (rand() % P);
                    while(!finished)
                    {
                        // cout<<getpid()<<" parent\n";
            
            
                    
                    cout<<"Turn: "<<counter+1<<endl;


                    //Sending message to child process numbered counter 
                    write(fd1[counter][1],"Start",6);
                    //cout<<": "<<endl;
                    char bdata[100];
                            // Reading data received from that child process
                            if(read(fd2[counter][0],bdata,100)>0)
                            {
                                checkSn(pos,counter);
                                checkLd(pos,counter);
                                
                                
                                
                                int nmove=atoi(bdata);
                                cout<<"Player "<<counter+1<<" got "<<nmove<<endl;
                                pos[counter]+=nmove;
                                checkSn(pos,counter);
                                checkLd(pos,counter);
                                if(pos[counter]>=N) 
                                {
                                    finished=1;
                                    //declaring the winner if player crosses N
                                    cout<<"Winner is Player No :- "<<counter+1<<endl;
                                    for(int j=0;j<P;j++)
                                                {
                                                    
                                                    close(fd1[j][0]);
                                                    close(fd1[j][1]);
                                                    close(fd2[j][0]);
                                                    close(fd2[j][1]); 
                                                    
                                                }
                                    
                                    
                                    exit(0);
                                }
                                for(int i=0;i<P;i++)
                                {
                                    cout<<"Position of Player "<<i+1<<" is "<<pos[i]<<endl;
                                }
                                cout<<"\n\n";
                                int flag=0;
                                
                                // Handling the case when dice rolls 6
                                while(nmove==6)
                                {
                                    flag=1;     
                                    checkSn(pos,counter);
                                    checkLd(pos,counter);
                                    
                                    write(fd1[counter][1],"Start",6);
                                    char bdata[100];
                                    if(read(fd2[counter][0],bdata,100)>0)
                                    {
                                                nmove=atoi(bdata);
                                                cout<<"Player "<<counter+1<<" got "<<nmove<<endl;
                                                pos[counter]+=nmove;
                                                checkSn(pos,counter);
                                                checkLd(pos,counter);
                                
                                                if(pos[counter]>=N) 
                                                {
                                                    finished=1;
                                                     //declaring the winner if player crosses N
                                                    cout<<"Winner is Player No :- "<<counter+1<<endl;

                                                    for(int i=0;i<P;i++)
                                                    {
                                                        cout<<"Position of Player "<<i+1<<" is "<<pos[i]<<endl;
                                                    }
                                                    cout<<"\n\n";

                                                    for(int j=0;j<P;j++)
                                                    {
                                                    
                                                        close(fd1[j][0]);
                                                        close(fd1[j][1]);
                                                        close(fd2[j][0]);
                                                        close(fd2[j][1]); 
                                                        
                                                    }

                                                    exit(0);
                                                }
                                    }
                            
                                        for(int i=0;i<P;i++)
                                        {
                                            cout<<"Position of Player "<<i+1<<" is "<<pos[i]<<endl;
                                        }
                                        cout<<"\n\n";
                                    }
                                if(flag)
                                {
                                    checkSn(pos,counter);
                                    checkLd(pos,counter);
                                
                               
                                        bdata[0]='0';
                                        bdata[1]='\n';
                                    if(pos[counter]>=N) 
                                        {
                                            finished=1;
                                             //declaring the winner if player crosses N
                                            cout<<"Winner is Player No :- "<<counter+1<<endl;
                                            for(int j=0;j<P;j++)
                                                { 
                                                    close(fd1[j][0]);
                                                    close(fd1[j][1]);
                                                    close(fd2[j][0]);
                                                    close(fd2[j][1]); 
                                                
                                                }

                                            exit(0);
                                        }
                            
                                }
                            }
                        
                                counter=(counter+1)%P;
                            
                                // cout<<result<<"zzz\n";
                                //for(int i=0;i<5;i++) // loop will run n times (n=5) 
                                //wait(NULL); 
                                // cout<<finished<<endl;
                                //finished=1;
                }
}