#include<iostream>
#include<fstream>

using namespace std;


/*-------------------------task 2-----------*/
class data{
    public:
        string code;
        string description;
};



struct list{
    data info;
    struct list *next;
};
typedef struct list node;
node *data_list;
node *prev;
/*------------------------------------------------------------------------*/
/*----------------------------------task3---------------------------------*/
node* push(node *head, data item){
    node *temp;
    if(head==NULL){
        head=new node();
        head->info=item;
        head->next=NULL;
        prev=head;
    }
    else{
        temp=new node();
        temp->info=item;
        temp->next=NULL;
        prev->next=temp;
        prev=temp;
    }


return head;
}

node* read_csv(){
    //list<data> data_list;

    ifstream file("Section111ValidICD10-2018.csv");

    if(!file.is_open())
        cout<<"no file"<<endl;

    string code;
    string description;
    string ignore;

    while(file.good()){
        getline(file, code, ';');
        getline(file, description, ';');
        getline(file, ignore, '\n');
        data d;
        if(code != "CODE"){
            d.code = code;

            d.description = description;
            //data_list.push_back(d);
            data_list = push(data_list, d);
        }
    }
    file.close();

return data_list;
}
/*----------------------------------------------------------*/


/*--------------------------task 4----------------------------------*/
bool is_substr(string to_search, string data){
    int i=0;
    int j=0;
    int k=0;
    bool flag = false;

    for(i=0; data[i]!=NULL; i++){
        k=0;
        for(j=i; j<i+to_search.length(); j++){
            if(tolower(data[j])==tolower(to_search[k])){
                k++;
				continue;
            }
            else
                break;
        }

        if(j >= i+to_search.length()){
            flag = true;
            //cout<<"found"<<endl;
        }
	 }

return flag;
}


void search_list(node *data_list, string to_search, bool is_code){
    node *i;
    i = data_list;

    while(i != NULL){
    //for (list<data>::const_iterator i = data_list.begin(); i != data_list.end(); ++i){
        if(is_code){
            if(is_substr(to_search, i->info.code)){
                cout<<i->info.code<<"    "<<i->info.description<<endl;
            }
        }
        else if(!is_code){
            if(is_substr(to_search, i->info.description)){
                cout<<i->info.code<<"    "<<i->info.description<<endl;
            }
        }
        i=i->next;
    }
}
/*------------------------------------------------------------------------*/

int main(){

    data_list = read_csv();
    cout<<"data read"<<endl;

    /*node *head;
    head = data_list;
    while(head != NULL){
        cout<<head->info.code<<endl;
    }*/

    int choice;
    string input;

    while(1){
        cout<<"World Health Organization (WHO)"<<endl;
        cout<<"International Classification of Diseases (ICD)"<<endl;
        cout<<"0 end"<<endl;
        cout<<"1 search for ICD code(s) (e.g. G4453)"<<endl;
        cout<<"2 search for diagnosis(s) (e.g. agina, Ebola, horse, Malaria, wheelchair)"<<endl;
        cin>>choice;
        if(choice == 0)
            break;
        else if(choice == 1){
            cout<<"to search for ICD code:";
            cin>>input;
            //search
            search_list(data_list, input, true);

        }
        else if(choice == 2){
            cout<<"to search for diagnosis:";
            cin>>input;
            //search
            search_list(data_list, input, false);
        }
        cout<<endl;
    }

return 0;
}

