#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <string.h>
#include <vector>
#include <bits/stdc++.h> 
#include <dirent.h>
#include <sys/stat.h> 
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"



using namespace std;

void get_input(char* input)
{
    char* input_buffer;
    input_buffer = readline(" ");
    if (strlen(input_buffer)>0)
    {
        add_history(input_buffer);
        strcpy(input,input_buffer);
    }
}

bool iequals(const string& str1, const string& str2)
{
    return std::equal(str1.begin(), str1.end(),
                      str2.begin(), str2.end(),
                      [](char str1, char str2) {
                          return tolower(str1) == tolower(str2);
                      });
}
int isDir(const char *path)
{
    struct stat fileStats;
    stat(path, &fileStats);

    // Check if the file is present
    if (S_ISDIR(fileStats.st_mode))
        return 1;

    return 0;
}
bool is_file_exist(const char *fileName)
{
		std::ifstream infile(fileName);
		return infile.good();
}
int main()
{
	cout<<"-----------------------------------Shell Created-----------------------------------------\n\n\n";  


	//Code for obtaining the hostname and the username

	char hostname[HOST_NAME_MAX];
	char username[LOGIN_NAME_MAX];
	int name;

	name = gethostname(hostname, HOST_NAME_MAX);
	if (name)
		{
		perror("gethostname");
		return EXIT_FAILURE;
		}

	name = getlogin_r(username, LOGIN_NAME_MAX);
	if (name)
		{
		perror("getlogin_r");
		return EXIT_FAILURE;
		}
			//cout<<username<<endl;

	// Main Shell Code
	while(true)
	{
			char curr_Working_Directory[1024];

			if (getcwd(curr_Working_Directory, sizeof(curr_Working_Directory)) == NULL)
				perror("getcwd() error");
				//cout<<"current working directory is: \n"<<cwd;


		string newCw;     
		newCw=curr_Working_Directory;

		int size=strlen(username);
		string sub = newCw.substr(size+newCw.find(username));
		char xy[PATH_MAX];
		int j = 0;
		for(int i=0; i<sub.length(); i++)
		{
			xy[j++] = sub[i];
		}
		xy[j] = '\0';
		
		string s;
		char ss[1000];
		strcpy(ss, s.c_str()); 
		char *input_buffer;
		printf(YELLOW);
		char naam[PATH_MAX];
		snprintf(naam,PATH_MAX, "%s%s@%s:~%s%s%s$ ",YELLOW, username,hostname,GREEN,xy,RESET);
		input_buffer = readline(naam);
		printf(RESET);
		s=input_buffer;
		strcpy(ss, input_buffer);
		add_history(input_buffer);
	

			//code for ls command  with option -a
			if(s[0]=='l'&&s[1]=='s')
			{
					char curr_Working_Directory[1024];
					    int pos = s.find("-a"); 

						if (pos != string::npos) 
						 {
									if (getcwd(curr_Working_Directory, sizeof(curr_Working_Directory)) == NULL)
										perror("getcwd() error");
									
										DIR *loc;
										struct dirent *ent;
										string cw=curr_Working_Directory;
										string hm="/home/";
										hm.append(username); 

										if ((loc = opendir (cw.c_str())) != NULL)
										{
										// Displays everything including the hidden files and directory as well
											while ((ent = readdir (loc)) != NULL) 
											{
												cout<<ent->d_name<<"\t";
											}
											cout<<"\n";
											closedir (loc);
										} 
										else {
											// not able to open the directory
											perror ("");
											return EXIT_FAILURE;
										}
			
						}
						else
						{ 
								if (getcwd(curr_Working_Directory, sizeof(curr_Working_Directory)) == NULL)
									perror("getcwd() error");
									
										DIR *loc;
										struct dirent *ent;
										string cw=curr_Working_Directory;
										string hm="/home/";
										hm.append(username); 

										if ((loc = opendir (cw.c_str())) != NULL)
										{
										// Displays all the files and directories except hidden ones
											while ((ent = readdir (loc)) != NULL) 
											{
												if(ent->d_name[0]=='.')
													continue; 
												cout<<ent->d_name<<"\t";
										}
											cout<<"\n";
											closedir (loc);
										} 
										else {
											// not able to open the directory
											perror ("");
											return EXIT_FAILURE;
										
			
						                 }

						}
			}

			//code for cd command 
			else if(s[0]=='c'&&s[1]=='d')
			{
				string newDir;
				newDir=s.substr(s.find(' ')+1);
			
			
					//cin >> newDir;
					int rc = chdir(newDir.c_str());
					//cout<<"ddddddddddddddddd";
					if (rc < 0) {
					cout<<"bash: cd: "+newDir+": No such file or directory\n";
					}
			}

			//code for cat command and cat with -n
			else if(s[0]=='c'&&s[1]=='a' && s[2]=='t')
			{
					bool flag=0;
					FILE *file;
					char line[1000];
					
						//cout<<"Reached here";
					string fileName;
						
					fileName=s.substr(s.find(' ')+1);
						// Code for normal cat command
						if(fileName[0]!='-'&&fileName[1]!='n')
						{
								//cout<<"IamHere";3

								flag = is_file_exist(fileName.c_str());
								if(flag==1)
								{
								file = fopen(fileName.c_str(),"r");
									
								//cout<<"Output\n";
								// file is being read line by line 
								while(fscanf(file,"%[^\n]\n",line)!=EOF)
								{
										cout<<line<<"\n";
								}
								fclose(file);
								//cout<<"\n";
								}
								else
								{
										cout<<"cat: "+fileName+": No such file or directory\n";
								}
						
						}

							//Code for cat command with option -n
							else if(fileName[0]=='-'&&fileName[1]=='n')
							{
								
								fileName=s.substr(s.find("-n")+3);
									//cout<<fileName<<endl;
									file = fopen(fileName.c_str(),"r");
											
									int count=1;
									
									// file is being read line by line 
									while(fscanf(file,"%[^\n]\n",line)!=EOF)
									{
										cout<<count<<" "<<line<<"\n";
										count++;
									}
									fclose(file);
									flag=1;
							}
							else
							{
								cout<<"bash: cat: "+fileName+": No such file or directory\n";
							}
							//cout<<endl;
			}


			//code for mkdir with option -m
			else if(s[0]=='m' && s[1]=='k' && s[2]=='d' && s[3]=='i' && s[4]=='r')
			{
					s=s.substr(s.find(' ')+1);
					if(s=="mkdir")
					{
						cout<<"mkdir: missing operand\n";
						continue;
					}
						if(s[0]!='-'&&s[1]!='m')
							{
							// Directory is created here 
							if (mkdir(s.c_str(), 0777) == -1) 
								cerr << "Error : " << strerror(errno) << endl; 
							}

						else
						{
							int x;
							string mode;
							s=s.substr(s.find(' ')+1);
							mode=s;
							char md[4]={'0'};
                            for(int i=0;i<strlen(mode.c_str());i++)
                            {
								if(mode[i]<='7' && mode[i]>='0')
                                 md[i+1]=mode[i]  ;
								 else
								 {
                                   // cout<<"\nInvalid Mode"; 
									
								 }  
							}
							
							x=strtol(md,0,8);
							int local=umask(0);
							s=s.substr(s.find(' ')+1);
							cout<<s;
							if (mkdir(s.c_str(),x) == -1) 
								cerr << "Error : " << strerror(errno) << endl; 
							
						}
			}


			//code for cp command with option -u
			else if(s[0]=='c'&&s[1]=='p')
			{
					string filename;
					//cout<<filename<<"\n";
					filename=s.substr(s.find(' ')+1);
					if(s=="cp")
					{
						cout<<"cp: missing file operand\n";
						continue;
					}
					s=filename;

					//code for normal cp command
					if(filename[0]!='-' && filename[1]!='u')
					{
						string currDir;
						string outDir;
						filename=s.substr(0,s.find(' '));
						outDir=s.substr(s.find(' ')+1);
				
					     if(outDir==filename)
						 {
							 cout<<"cp: missing destination file operand \n";
							 continue;
						 }   
						char curr_Working_Directory[1024];
						fstream newfile;

						if (getcwd(curr_Working_Directory, sizeof(curr_Working_Directory)) == NULL)
									perror("getcwd() error");

						currDir=curr_Working_Directory;
						vector<string> fileData; 			//vector for storing the file data
						newfile.open(filename);             //Opening the file to read data
						if (newfile.is_open())   
						{  
							//cout<<"ENTER";
							string tp;
							while (newfile >> tp) 
							{ 
								//cout << tp << endl; 
								fileData.push_back(tp);
							} 
							newfile.close(); 

						}
						
							// checking if the second argument is directory
							if (isDir(outDir.c_str()))
							{

								int rc = chdir(outDir.c_str());
								if (rc < 0) {
									cout<<"bash: cd: "+outDir+": No such file or directory\n";
									continue;
								}

								//ofstream object for writing the file data to destination file or directory
								ofstream out;     
								string line; 
								 
								out.open(filename);
										
								//writing the data from vector to the file		
								for(int i=0;i<fileData.size();i++)
								{
									out << fileData[i] << endl; 	

								}
										
								out.close();

								// changing the directory to current working directory
								rc = chdir(currDir.c_str());
							}


							//code for cp command if the second argument is file
							else
							{
								ofstream out; 
								string line; 
								
								out.open(outDir); 

								//writing the data from vector to the file			
								for(int i=0;i<fileData.size();i++)
								{
									out << fileData[i] << endl; 	
								}

								out.close();

							}
					}


					//code for cp command with option -u
					else
					{
						struct stat p1,p2;
						
						
						string currDir;
						string outDir;
						//cin>>outDir;
						s=s.substr(s.find(' ')+1);
						filename=s.substr(0,s.find(' '));
						outDir=s.substr(s.find(' ')+1);
						
						if(outDir==s)
						{
							cout<<"cp: missing file operand\n";
							continue;
						}
						char curr_Working_Directory[1024];
						fstream newfile;

						if (getcwd(curr_Working_Directory, sizeof(curr_Working_Directory)) == NULL)
							perror("getcwd() error");

						currDir=curr_Working_Directory;
						
						vector<string> fileData;
						newfile.open(filename); //Opening the file to read data
						{   
							stat(filename.c_str(),&p1);
							//cout<<p1.st_mtime<<endl;
						
							string tp;
							while (newfile >> tp) 
							{ 
								fileData.push_back(tp);
							} 
							newfile.close();


						}
						
							//if second argument is directory
							if (isDir(outDir.c_str()))
							{
								int rc = chdir(outDir.c_str());
								if (rc < 0) {
								cout<<"bash: cd: "+outDir+": No such file or directory\n";
								continue;
								}

								
								ofstream out; 
								fstream newfile1;
								string line1; 
								vector<string> fileData1;
								newfile1.open(filename); //Opening the file to read data
								if (newfile1.is_open())
								{ 

									stat(filename.c_str(),&p2);
									//cout<<p2.st_mtime<<endl;
									if(p1.st_mtime > p2.st_mtime)
									{
										out.open(filename); 
											for(int i=0;i<fileData.size();i++)
											{
												out << fileData[i] << endl; 	

											} 	
											out.close();
									}		
									rc = chdir(currDir.c_str());
									
								
								}
								else
								{
										//If the file is not present create it and copy the contents
										out.open(filename); 

										for(int i=0;i<fileData.size();i++)
										{
											out << fileData[i] << endl; 	

										}
										out.close();

										// changing the directory to current working directory		
										rc = chdir(currDir.c_str());


								}
									
							}
							//if the second argument is file
							else
							{
								stat(outDir.c_str(),&p2);
								ofstream out; 
								//cout<<p1.st_mtime<<endl;
								//cout<<p2.st_mtime<<endl;
								if(p1.st_mtime > p2.st_mtime)
								{	
										out.open(outDir); 
										for(int i=0;i<fileData.size();i++)
										{
											out << fileData[i] << endl; 	
										}
										out.close();

								}
							}
							
					}
					
			}	

			// code for grep command with option -i
			else if(s[0]=='g' && s[1]=='r' && s[2]=='e' && s[3]=='p')
			{
					fstream newfile;
                    string pat,temp,fn;
                    s=s.substr(s.find(' ')+1);
                    pat=s.substr(0,s.find(' '));

					if(s==pat)
					{
						cout<<"Pattern missing\n";
						continue;
					}
					//fn=s.substr(s.find(' ')+1);


				//code for normal grep command 	
				if(pat!="-i")
				{
					fn=s.substr(s.find(' ')+1);
					
					//when pattern is present anywhere in the line
					if(pat[0]!='^')
					{
						//cout<<"XXX";
						newfile.open(fn,ios::in);  //Opening the file to read data
						if (newfile.is_open())
						{   
							string tp;
							while(getline(newfile, tp))
							{
								if(tp.find(pat)!= string::npos)
								cout<<tp<<endl;
							}
							newfile.close();
						}
					}

					//when pattern should be present at the beginning
					else 
					{
						newfile.open(fn,ios::in);  //Opening the file to read data
						if (newfile.is_open())
						{   
							string tp;
							pat=pat.substr(1);
							//cout<<pat<<endl;

							int ln=pat.size();

							while(getline(newfile, tp))
							{ 
								int j;
								//cout<<tp<<"      "<<pat;
								for(j=0;j<ln;j++)
								{
									if(tp[j]!=pat[j])
									break;
								} 
								if(j==ln)     
									cout<<tp<<endl;
							}
							
							/*
							cout<<pat<<endl;
							if(tp.find(pat)!=string::npos )
							{
								size_t=tp.find(pat);
								if(size_t =='0')	
								cout<<tp<<endl;

							}*/
							newfile.close();
						}
					}
				
				}

				//code for grep without option
				else
				{
					s=s.substr(s.find(' ')+1);
					pat=s.substr(0,s.find(' '));
					fn=s.substr(s.find(' ')+1);

					//when pattern is present anywhere in the line
					if(pat[0]!='^')
					{
						//cout<<"XXX";
						newfile.open(fn,ios::in);  //Opening the file to read data
						if (newfile.is_open())
						{  
							string tp;
							while(getline(newfile, tp))
							{ 
								string s1,s2;
								char p1[1000],p2[1000];
								for (int i=0; i<strlen(pat.c_str()); i++)
										p1[i]=(tolower(pat[i]));
								
								for (int i=0; i<strlen(tp.c_str()); i++)
										p2[i]=(tolower(tp[i]));
								
								s1=p2;
								s2=p1;

							
								if(s1.find(s2)!= string::npos)
									cout<<tp<<endl;
							}
							newfile.close(); //close the file object.
						}
					}

					//when pattern should be present at the beginning
					else 
					{
						newfile.open(fn,ios::in); //Opening the file to read data
						if (newfile.is_open())
						{   
							string tp;
							pat=pat.substr(1);
							//cout<<pat<<endl;
							int ln=pat.size();
							while(getline(newfile, tp))
							{ 
							
								int j;
								//cout<<tp<<"      "<<pat;
								for(j=0;j<ln;j++)
								{
									if(tp[j]!=pat[j])
									break;
								} 
								if(j==ln)     
									cout<<tp<<endl;
							}
							/*
							cout<<pat<<endl;
							if(tp.find(pat)!=string::npos )
							{
								size_t=tp.find(pat);
								if(size_t =='0')	
								cout<<tp<<endl;

							}*/
							newfile.close(); //close the file object.
						}
					}
				
				}
				
					
			}

			// code for sort command with and without option -r 
			else if(s[0]=='s' && s[1]=='o' && s[2]=='r' && s[3]=='t')
			{
				fstream newfile;
				char fn[1000], temp[2000];
	
                s=s.substr(s.find(' ')+1);
				//cout<<s<<endl;

					//  code for sort command without -r option
					if(s[0]!='-'&&s[1]!='r')
					{
						vector<string> data;      //vector for storing the file content
                         //   cout<<s<<endl;
						newfile.open(s,ios::in); //Opening the file to read data
						if (newfile.is_open())
						{   
							string tp;
							while(getline(newfile, tp))
							{
								data.push_back(tp);
							}
							newfile.close();
						
							sort(data.begin(), data.end());

							for(int i= 0;i<data.size();i++)
							{
								cout<<data[i]<<endl;
							}
						}	
					}

					//  code for sort command with -r option
					else
					{
					 
						fstream newfile;
						string xyz;
							
                        xyz=s.substr(s.find('-')+3);
						//cout<<xyz;	
						vector<string> str; 
						//cout<<name;
						newfile.open(xyz,ios::in); 

						if (newfile.is_open())
						{  
							string tp;
							//cout<<"hello"<<endl;
							while(getline(newfile, tp))
							{
								str.push_back(tp);
								//cout<<tp<<endl;	
							}
							newfile.close();
						}
						sort(str.begin(), str.end());

						for(int i= str.size()-1;i>=0;i--)
						{
							cout<<str[i]<<endl;
						}
						
						
					}
				
			}


			else if(s=="clear")
			{
				system("clear");
			}
			else if(s=="exit")
			{
				exit(0);
			}
			else
			{
				cout<<s<<" : command not found\n";
				continue;
			}
			
			






	}






}


