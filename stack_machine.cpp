#include <iostream>
#include <fstream>
#include <string>

struct node{
    int value;
    node* next;
};

node* head;

void push(int x){
    node* y = (node*) malloc(sizeof(node));
    y->next = nullptr;
    y->value = x;
    if(head==nullptr){
        head = y;
    }else{
        y->next=head;
        y->value=x;
        head = y;
    }
}


void pop(){
    if(head->next==nullptr){
        free(head);
    }else{
        node* temp = (node*) malloc(sizeof(node));
        temp = head;
        head = head->next;
        temp->next = nullptr;
        free(temp);
    }
}

void print_list(){
    node* x = head;
    while(x!=nullptr){
        std::cout<<x->value<<std::endl;
        x = x->next;
    }
}

void load_number_stack(std::string path){
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error! File: "  << path << " can't be read!" << std::endl;
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        push(stoi(line));
    }
}

void load_and_compile_command_txt(std::string path){
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error! File: "  << path << " can't be read!" << std::endl;
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        node* y = (node*) malloc(sizeof(node));
        y = head;
        if(line == "ADD"){
            (y->next)->value = y->value + (y->next)->value;
            pop();
        }else if(line == "MUL"){
            (y->next)->value = y->value * (y->next)->value;
            pop();
        }else if(line == "SUB"){
            (y->next)->value = y->value - (y->next)->value;
            pop();
        }else if(line == "DIV"){
            (y->next)->value = y->value / (y->next)->value;
            pop();
        }else{
            std::cout<<"Error while handling inputted commands. Wrong command syntax."<<std::endl;
        }
    }
}

int main(int argc, char *argv[]) {

    if(argc != 3){
        std::cout << "Program must be called with 2 parameters!";
    }else{
        std::cout<<"The starting stack:"<<std::endl;
        load_number_stack(argv[1]);
        print_list();
        std::cout<<"\n\n"<<std::endl;

        std::cout<<"The editted stack:"<<std::endl;
        load_and_compile_command_txt(argv[2]);
        print_list();
    }
    return 0;
}