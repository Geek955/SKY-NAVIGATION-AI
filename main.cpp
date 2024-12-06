#include<iostream>
#include<fstream>
# include <string>
using namespace std;


//=====================================================================
//                       NODE    CLASS
//=====================================================================

struct node{
    string src;
    string dest;
    int date;
    int take_of_time;
    int land_time;
    float price;
    string airline;
    node* next;

    node(string s , string d , int dat , int t , int l , float p , string a){
        src=s;
        dest=d;
        date=dat;
        take_of_time=t;
        land_time=l;
        price=p;
        airline=a;
        next=NULL;
    }
};

//=====================================================================
//                       ADJCENT LIST CLASS
//=====================================================================

struct adjecent_list{
    string city_name;
    float hotel_charges;
    node *head=NULL;

    adjecent_list(){}
    
    void insert(string s , string d , int dat , int t , int l , float p , string a){
        if(head==NULL){
            head=new node(s , d , dat , t , l , p , a);
            return ;
        }

        node *temp=head;
        while(temp->next!=NULL){
            temp=temp->next;
        }

        temp->next=new node(s , d , dat , t , l , p , a);
    }

    void Display(){
        node *temp=head;
        int x=0;
        while(temp!=0){

            cout<<temp->dest<<"\033[0;33m"<<" >-->>--> ";
                        cout<<"\033[1;34m";
            temp=temp->next;
            x++;
        } 
        cout<<"\033[1;0m";
        cout<<"\nTOTALL NUMBER OF NODES : "<<x<<endl<<endl;
        cout<<endl;
    }

    ~adjecent_list(){
        delete[] head;
        head=NULL;
    }


};

//=====================================================================
//                        GRAPH   CLASS
//=====================================================================

struct graph{
    adjecent_list * adj_list;
    int vert{0};
    int size{0};

    graph(int no_of_cities){
        size=no_of_cities;
        adj_list=new adjecent_list[size];
        vert=0;
    }

    void insert_vertex(string name_of_city , float p){ //store the name of each city in each node of addjecency  , making them vertex
        adj_list[vert].city_name=name_of_city;
        adj_list[vert].hotel_charges=p;
        vert++;
    }

    void read_file(){
        ifstream fp("Flights.txt");

        if(!fp){
            cout<<"FILE COULDNOT BE OPENED"<<endl;
        }

        string destination;
        string source;
        string date;
        string t_time;
        string l_time;
        string garbage;
        float pric;
        string service;
        int a=1;
        while(!fp.eof()){
            cout<<"\033[1;34m";
            getline(fp, source, ' ');        
            getline(fp, destination, ' ');  
            getline(fp, date, '/');

            getline(fp , garbage , ' '); //collecting garbage */12/2019

            getline(fp, t_time, ':');

            getline(fp , garbage , ' '); //collecting garbage */12/2019
            
            getline(fp, l_time, ':');

            getline(fp , garbage , ' '); //collecting garbage */12/2019
        
            fp >> pric;                   
            fp.ignore();                  
            getline(fp, service , '\n'); 

            add_edges(source , destination , stoi(date) , stoi(t_time) , stoi(l_time) , pric , service );


        }

    }

    void add_edges(string s , string d , int dat , int t , int l , float p , string a){  //aka add the details of flight going from one city to another 
        for(int i=0 ; i<size ; i++){
            if(!(adj_list[i].city_name.compare(s))){
                adj_list[i].insert(s , d , dat , t , l , p , a);
                break;
            }
        }
    }

    void display(){
        for(int i=0 ; i<size ; i++){
            cout<<"\033[0;31m";
            cout<<"Flight from this city "<<"\033[1;31m"<<adj_list[i].city_name<<"\033[0;31m"<<" Can go to follwoing cities : "<<endl;
            cout<<"\033[1;34m";
            adj_list[i].Display();
        }
    }

    // void booking(){
    //     cout<<"Enter the source : ";
    //     cin>>source;
    //     cout<<"Enter the destination : ";
    //     cin>>destination;
    //     cout<<"Enter the date"
    // }

};


void insert_vertices(graph &g){ //Read DATA from the file and add vertices in the graph
    ifstream fp("HotelCharges_perday.txt");

    if(!fp){
        cout<<"FILE COULDNOT BE OPENED"<<endl;
    }

    string city;
    float price;
    int a=1;

    while(!fp.eof()){
        cout<<"\033[1;34m";
        getline(fp, city, ' ');        
        fp >> price;                  
        fp.ignore() ;
        cout<<city<<"  "<<price<<endl;
        g.insert_vertex(city , price);
    }

    g.insert_vertex("Sydney" , 0);
}



int main(){

graph g(11);
insert_vertices(g);
g.read_file();

g.display();
    return 0;
}
