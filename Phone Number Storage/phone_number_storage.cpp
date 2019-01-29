#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//task1
enum num_type {home, work, fax, mobile, other};

//task2
#define max 15
struct contact {
    string name;
    string number;
    num_type type;
};
typedef contact contact;

int count = 0;
contact contacts[max];
contact node;


//task3
void ordered_insert(contact node_to_insert){

    int first= 0;
    int i = count; // array te already inserted last element er iterator

// insert target into arr such that arr[first..last] is sorted,
//   given that arr[first..last-1] is already sorted.
//   Return the position where inserted.

    while ( (i > first) && ( (node_to_insert.name).compare(contacts[i-1].name) < 0 ) )
    {
      contacts[i] = contacts[i-1];
      i = i - 1;
    }
    contacts[i] = node_to_insert;
return;

}
bool new_contact(){

    if(count<=max){
        string name, number;
        char type;
        cout<<"Please enter number: ";
        cin>>number;
        cout<<endl;
        cout<<"Please enter name: ";
        //cin>>name;          // multiple word and spaces
        cin.ignore();
        getline (cin,name);
        cout<<endl;
        cout<<"Type of number (f for fax, h for home, m for mobile, w for work , o for other): ";
        cin>>type;
        cout<<type;
        cout<<endl;

        node.name = name;
        node.number = number;
        if(type = 'f')
            node.type = fax;
        else if(type = 'h')
            node.type = home;
        else if(type = 'm')
            node.type = mobile;
        else if(type = 'w')
            node.type = work;
        else if(type = 'o')
            node.type = other;

        ordered_insert(node);
        count++;
        return true;

    }
    else
        return false;
}

//task4
bool delete_contact(){
    bool flag = false;
    string name;

    cout<<"Please enter name to delete contact: ";
    cin>>name;
    //find
    int i;
    for(i=0; i<=count; i++){
        if(contacts[i].name == name){
            flag = true;
            //target = i;
            break;
        }
    }
    //delete and reshape
    while(i<=count){
        contacts[i]=contacts[i+1];
        i++;
    }
    if(flag == true)
        count--;
return flag;
}

//task5
void show_contacts(){
    string type;
    for(int i=0; i<count; i++){
        if(contacts[i].type == 0)
            type = "home";
        else if(contacts[i].type == 1)
            type = "work";
        else if(contacts[i].type == 2)
            type = "fax";
        else if(contacts[i].type == 3)
            type = "mobile";
        else if(contacts[i].type == 4)
            type = "other";
        cout<<left<<setw(15)<<contacts[i].name<<right<<setw(15)<<left<<setw(15)<<contacts[i].number<<right<<setw(15)<<"( "<<type<<" )"<<endl;
    }
return;
}

//task6
void show_menu(){
    cout<<"*** "<<count<<" contact entries ****"<<endl;
    cout<<"0 End"<<endl;
    cout<<"1 new contact"<<endl;
    cout<<"2 delete contact"<<endl;
    cout<<"3 show all contact"<<endl;
    cout<<"9 empty contact memory"<<endl;
    cout<<(max - count)<<" empty contact memory"<<endl;
return;
}

int main(){
    int choice;
    while(1){
        show_menu();
        cin>>choice;

        if(choice == 0)
            break;
        if(choice == 1){
            if(new_contact())
                cout<<"contact stored"<<endl;
            else
                cout<<"cannot store contact"<<endl;
        }
        if(choice == 2){
            if(delete_contact())
                cout<<"contact deleted"<<endl;
            else
                cout<<"cannot delete contact"<<endl;
        }
        if(choice == 3)
            show_contacts();
        if(choice == 9){
            count = 0;
        }
    }
return 0;
}
