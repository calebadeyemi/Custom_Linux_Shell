#include<iostream>
#include<cstdlib>
#include<ctime>
#include<unistd.h>
#include<stdlib.h>
#include<regex>
#include<string>
#include<vector>
#include<stdio.h>
#include<string.h>
#include<string>
#include<sstream>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

using namespace std;

char buf[1024];
string raw;
void execute_vector(vector<string>);

void update_prompt()
{
   char* reset[] = {"pwd", NULL};
    
    if (fork() == 0){
        execvp(reset[0], reset);
    } else {
        wait(NULL);
    }
}

vector<string> split_on_spaces(string input)
{
    vector<string> myVec;
    string token = "";
    
    for(int i=0; i<input.size(); i++)
    {
        if(input[i] != ' ')
        {
            token += input[i];
        }
        else
        {
            myVec.push_back(token);
            token = "";
        }
    }
    myVec.push_back(token);
    return myVec;
}

vector<string> split_on_pipe(string input)
{
    vector<string> myVec;
    string token = "";
    
    for(int i=0; i<input.size(); i++)
    {
        if(input[i] != '|')
        {
            token += input[i];
        }
        else
        {
            myVec.push_back(token);
            token = "";
        }
    }
    myVec.push_back(token);
    return myVec;
}

string read_input()
{
    getline(cin, raw);
    return raw;
}

bool check_special_command(string s){
    return false;
}


bool check_command_name(string s)
{
    vector<string> cmd = split_on_spaces(s);
    
    
    char* b0;
    char* b1;
    char* b2;
    char* b3;
    char* b4;
    char* b5;
    char* b6;
    char* b7;
    char* b8;
    char* b9;
    char* b10;
    
    if(cmd.size()>0){
        b0 = new char[cmd[0].size()];
        strcpy(b0, cmd[0].c_str());
    } else{
        b0 = (char*)NULL;
    }
    
    if(cmd.size()>1){
        b1 = new char[cmd[1].size()];
        strcpy(b1, cmd[1].c_str());
    } else{
        b1 = (char*)NULL;
    }
    
    if(cmd.size()>2){
        b2 = new char[cmd[2].size()];
        strcpy(b2, cmd[2].c_str());
    } else{
        b2 = (char*)NULL;
    }
    
    if ( cmd.size() > 3 ){
        b3 = new char[cmd[3].size()];
        strcpy(b3, cmd[3].c_str());
    } else{
        b3 = (char*)NULL;
    }
    
    if(cmd.size()>4){
        b4 = new char[cmd[4].size()];
        strcpy(b4, cmd[4].c_str());
    } else{
        b4 = (char*)NULL;
    }
    if(cmd.size()>5){
        b5 = new char[cmd[5].size()];
        strcpy(b5, cmd[5].c_str());
    } else{
        b5 = (char*)NULL;
    }
    if(cmd.size()>6){
        b6 = new char[cmd[6].size()];
        strcpy(b6, cmd[6].c_str());
    } else{
        b6 = (char*)NULL;
    }
    if(cmd.size()>7){
        b7 = new char[cmd[7].size()];
        strcpy(b7, cmd[7].c_str());
    } else{
        b7 = (char*)NULL;
    }
    if(cmd.size()>8){
        b8 = new char[cmd[8].size()];
        strcpy(b4, cmd[8].c_str());
    } else{
        b8 = (char*)NULL;
    }
    if(cmd.size()>9){
        b9 = new char[cmd[9].size()];
        strcpy(b9, cmd[9].c_str());
    } else{
        b9 = (char*)NULL;
    }
    char *temp[] = {b0,
        b1,
        b2,
        b3,
        b4,
        b5,
        b6,
        b7,
        b8,
        b9,
        b10,
        (char*)NULL};
    
    execvp(temp[0],temp);
    
    return false;
}

bool check_command_args(string s)
{
    return false;
}

bool check_unix_command(string s)
{
    for( int i = 0; i < s.size(); i++){
        // PIPE
        if(s[i]=='|'){
            //check_command_args();
        }
        else{
            // DO NOTHING
        }
    }
    
    check_command_name(s);
    
    return true;
}

bool check_string()
{
    string token = "";
    
    int begin = 0;
    int end  = raw.size();
    
    // Parse String
    for( int i = 0; i < raw.size(); i++){
        // PIPE
        if(raw[i]=='|'){
            string a = raw.substr(begin,i-1);
            // Increment Token Window
            begin = i+1;
        }
        // REDIRECTION <
        else if(raw[i]=='<') {
            
        }
        // REDIRECTION >
        else if(raw[i]=='>'){
            
        }
        // AMP
        else if(raw[i]=='&'){
        }
        // DO NOTHING
        else{
            // DO NOTHING
        }
    }
    // UNIX COMMAND
    if(check_unix_command(raw)){
        
    }
    
    // SPECIAL COMMAND
    if(check_special_command(raw)){
        
    }
    
    // COMMAND NOT SUPPORTED
    return false;
}

bool detect_cd(vector<string> cmd){
    if(!cmd[0].find("cd") > 0){
        if (fork() == 0){
            chdir (cmd[1].c_str());
        }
        else{
            wait(NULL);
        }
        return true;
    }
    return false;
}

bool detect_redirection(vector<string> cmd)
{
    // Detect Redirection
    bool redirection_detected = false;
    for( int i = 0; i < cmd.size(); i++){
        
        // Redirect Command Output into File
        if(cmd[i]==">"){
            redirection_detected = true;
            
            int pipe_red[2];
            
            if(pipe(pipe_red) == -1){
                perror("pipe");
                exit(EXIT_FAILURE);
            }
            
            pid_t pid = fork();
            
            if(pid == 0) // Child
            {
                close(pipe_red[0]);
                dup2(pipe_red[1], 1);
                close(pipe_red[1]);
                
                vector<string> s;
                for(int j = 0; j < i; j++){
                    s.push_back(cmd[j]);
                }
                
                execute_vector(s);
            }
            else // Parent
            {
                wait(NULL);
                
                close(pipe_red[1]);
                
                char* b;
                
                int file_fd = open(cmd[i+1].c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                
                while(read(pipe_red[0],&b,1)!=0) write(file_fd,&b,1);
                
                close(file_fd);
                close(pipe_red[0]);
            }
            break;
        }
        
        // Redirect File into Command
        if(cmd[i]=="<"){
            redirection_detected = true;
            
            pid_t pid = fork();
            
            if(pid == 0) // Child
            {
                int file_fd = open(cmd[i+1].c_str(), O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                
                dup2(file_fd, 0);
                
                vector<string> s;
                for(int j = 0; j < i; j++){
                    s.push_back(cmd[j]);
                }
                
                close(file_fd);
                execute_vector(s);
            }
            else // Parent
            {
                wait(NULL);
            }
            break;
        }
        
        
        
    }
    
    
    return redirection_detected;
}

void execute_vector(vector<string> cmd)
{
    
    // INPUT REDIRECTION
    if(!detect_redirection(cmd) && !detect_cd(cmd))
    {
        
        
        char* b0;
        char* b1;
        char* b2;
        char* b3;
        char* b4;
        char* b5;
        char* b6;
        char* b7;
        char* b8;
        char* b9;
        char* b10;
        
        if(cmd.size()>0){
            b0 = new char[cmd[0].size()];
            strcpy(b0, cmd[0].c_str());
        } else{
            b0 = (char*)NULL;
        }
        
        if(cmd.size()>1){
            b1 = new char[cmd[1].size()];
            strcpy(b1, cmd[1].c_str());
        } else{
            b1 = (char*)NULL;
        }
        
        if(cmd.size()>2){
            b2 = new char[cmd[2].size()];
            strcpy(b2, cmd[2].c_str());
        } else{
            b2 = (char*)NULL;
        }
        
        if ( cmd.size() > 3 ){
            b3 = new char[cmd[3].size()];
            strcpy(b3, cmd[3].c_str());
        } else{
            b3 = (char*)NULL;
        }
        
        if(cmd.size()>4){
            b4 = new char[cmd[4].size()];
            strcpy(b4, cmd[4].c_str());
        } else{
            b4 = (char*)NULL;
        }
        if(cmd.size()>5){
            b5 = new char[cmd[5].size()];
            strcpy(b5, cmd[5].c_str());
        } else{
            b5 = (char*)NULL;
        }
        if(cmd.size()>6){
            b6 = new char[cmd[6].size()];
            strcpy(b6, cmd[6].c_str());
        } else{
            b6 = (char*)NULL;
        }
        if(cmd.size()>7){
            b7 = new char[cmd[7].size()];
            strcpy(b7, cmd[7].c_str());
        } else{
            b7 = (char*)NULL;
        }
        if(cmd.size()>8){
            b8 = new char[cmd[8].size()];
            strcpy(b4, cmd[8].c_str());
        } else{
            b8 = (char*)NULL;
        }
        if(cmd.size()>9){
            b9 = new char[cmd[9].size()];
            strcpy(b9, cmd[9].c_str());
        } else{
            b9 = (char*)NULL;
        }
        char *temp[] = {b0,
            b1,
            b2,
            b3,
            b4,
            b5,
            b6,
            b7,
            b8,
            b9,
            b10,
            (char*)NULL};
        
        execvp(temp[0],temp);

        execvp(temp[0],temp);
    }
}

int main(int argc, char** argv)
{
    // READ INPUT ON NEWLINE
    
    /* Parse command line arguments */
    
    /* Initialize prompt to default (current directory followed by a colon */
    
    /* Vector to maintain background processes */
    
    while(true){
        update_prompt();
        
        
        string input = read_input();
        
        // Detect Background Character "&"
        bool background = false;
        for( int c = 0; c < input.size(); c++){
            if(input[c]=='&'){
                background = true;
                input[c]=' ';
            }
        }
        
        // Split on Pipe
        vector<string> pipes = split_on_pipe(input);
        
        // Split on Spaces
        vector<vector<string>> commands;
        for( int p = 0; p < pipes.size(); p++){
            vector<string> spaces = split_on_spaces(pipes[p]);
            
            // Clean 
            vector<string> clean_spaces;
            for( int j = 0; j < spaces.size(); j++){
                if(spaces[j]!=" " && spaces[j]!="\0"){
                    clean_spaces.push_back(spaces[j]);
                }
            }
            
            // Add Cleaned Command to Vector
            commands.push_back(clean_spaces);
        }
        
   
        // PIPED
        if(commands.size()>1){
            
            // CREATE PIPES
            int pipe_fds[commands.size()-1][2];
            
            for( int p = 0; p < commands.size()-1; p++){
                if( pipe(pipe_fds[p]) == -1 ){
                    perror("pipe");
                    exit(EXIT_FAILURE);
                }
            }
            
            for( int p = 0; p < commands.size(); p++){
                pid_t pid = fork();
                
                // Child
                if(pid==0){
                    
                    // Configure Input
                    if(p>0)
                    {
                        close(pipe_fds[p-1][1]);
                        dup2 (pipe_fds[p-1][0], 0); // Standard Input -> Pipe
                        close(pipe_fds[p-1][0]);
                    }
                    
                    // Configure Output
                    if(p < commands.size()-1){
                        close(pipe_fds[p][0]);
                        dup2 (pipe_fds[p][1], 1); // Standard Output -> Pipe
                        close(pipe_fds[p][1]);
                    }
                    
                    execute_vector(commands[p]);
                    
                    exit(0);
                }
                // Parent
                else{
                    wait(NULL);
                    
                    if(p > 0) close(pipe_fds[p-1][0]);
                    if(p < commands.size() - 1) close(pipe_fds[p][1]);
                }
            }
            
            for( int p = 0; p < commands.size()-1; p ++){
                close( pipe_fds[p][0] );
                close( pipe_fds[p][1] );
            }
            
            
        }
        // NO PIPED
        else{
            if(fork()==0)
                execute_vector(commands[0]);
            else
                wait(NULL);
            
        }
        
        
    }
    return 0;
}

