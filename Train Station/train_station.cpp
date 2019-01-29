#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
//task  1
class Time{
    public:
        //constructor
        Time(){
        }
        //overloaded constructor
        Time(unsigned int init){
            if(init>=0 && init<24*60)
                minuteofDay = init;
            else
                minuteofDay = init%(24*6);          // modulo midnight
        }
        //overloaded constructor
        Time(int hour, int minute){
            set_time(hour, minute);
        }
        void set_time(int hour, int minute){
            if(hour>=24 && minute>=60){
                cout<<"error"<<endl;
                Time(0);
            }
            else{
                Time(hour*60 + minute);
                cout<<hour*60+minute;
            }
        }
        int get_hour(){
            return minuteofDay/60;
        }
        int get_minute(){
            return minuteofDay%60 ;
        }
        int get_minuteofDay(){
            return minuteofDay;
        }
        Time operator + (unsigned int m){
            return Time(get_minuteofDay() + m);
        }
        friend istream &operator >> (istream &input, Time &t);
        friend ostream &operator << (ostream &output, Time &t);

    private:
        int minuteofDay;

};

//task 2 - operator overload
istream &operator >> (istream &input, Time &t){
    int hour, minute;
    char colon;
    input>>hour>>colon>>minute;         // 12:45 hour :(ignore) minute
    t=Time(hour*60+minute);
    return input;
}

//task3 - operator overload
ostream &operator << (ostream &output, Time &t){
    output<<setfill('0')<<setw(2)<<t.get_hour()<<":"<<setw(2)<<t.get_minute();
    return output;
}
/*-------------------------------------------------------------------*/
//task4
class Train
{
    public:
        Train();
        Train(string n, string t, string o);
        string get_no();
        string get_to();
        string get_over();
        ~Train();

    private:
        string no;
        string to;
        string over;
};
/* definition outside the class */
Train::Train(string n, string t, string o){
    no = n;
    to = t;
    over = o;
}
string Train::get_no(){
    return no;
}
string Train::get_to(){
    return to;
}
string Train::get_over(){
    return over;
}
Train::~Train(){
}


/*--------------------------------------------------------------*/
//task5
class Station
{
    public:
        Station(){
        }
        // constructor initializing const variables
        Station(string st_name):station(st_name),schedule(){
        }

        void addDeparture(Time time, int platform, Train *train){
            schedule[time.get_minuteofDay()][platform] = train;
            //cout<<"added~"<<time<<"~"<<schedule[time.get_minuteofDay()][platform]->get_no()<<"~"<<schedule[time.get_minuteofDay()][platform]->get_over()<<"~"<<schedule[time.get_minuteofDay()][platform]->get_to()<<"~"<<platform<<endl;
            return;
        }
        void showDeparture(Time ti, unsigned int m){
            int i,j;
            Time ki;
            ki=ti+m;
            for(i = ti.get_minuteofDay() ; i <= ki.get_minuteofDay() ; i++){
                for(j=0;j<platforms; j++){
                    if(schedule[i][j] != NULL){
                        Time temp(i);
                        cout<<temp<<"    "<<schedule[i][j]->get_no()<<"    "<<schedule[i][j]->get_over()<<"    "<<schedule[i][j]->get_to()<<"    "<<j<<endl;
                    }
                }
            }
        }

        ~Station(){
            for(int x=0; x<24*60; x++){
                for(int y=0; y<platforms; y++){
                    if(schedule[x][y] != NULL){
                        Time X(x);
                        cout<<X<<" platform: "<<y<<" Train "<<schedule[x][y]->get_no()<<" to "<<schedule[x][y]->get_to()<<" deleted"<<endl;
                        delete schedule[x][y];
                    }
                }
            }
            cout<<"schedule for DUISBERG MAIN TRAIN STATION completely deleted"<<endl;
        }

    private:
        const string station;
        static const unsigned int platforms = 15;
        Train* schedule[24*60][platforms];
};



int main(){

    Station duisburg("DUISBERG");

    for(int i = 7; i<24*60 ; i=i+20){
        Time t1(i);
        Train train_object("s1", "Solingen Hbf", "Muelheim(Ruhr)Styrum - Muelheim(Ruhr) - Essen");
        duisburg.addDeparture(t1, 9, &train_object);          // each 20 minutes
    }



    for(int i = 15; i<24*60 ; i=i+20){
        Time t1(i);
        Train train_object("s1", "Solingen Hbf", "Duisburg - Schlenk - Duesseldorf Flughafen");
        duisburg.addDeparture(t1, 5, &train_object);          // each 20 minutes
    }


    for(int i = 35; i<24*60 ; i=i+120){
        Time t1(i);
        Train train_object("s2", "Dortmund Hbf", "Oberhausen - Gelsenkirchen - Wanne-Eickel");
        duisburg.addDeparture(t1, 2, &train_object);           // hourly
    }



    for(int i = 35; i<24*60 ; i=i+240){
        Time t1(i);
        Train train_object("RE1", "Aachen Hbf", "Duesseldorf Flughafen - Duesseldorf - Koeln");
        duisburg.addDeparture(t1, 4, &train_object);           // hourly
    }


    for(int i = 35; i<24*60 ; i=i+600){
        Time t1(i);
        Train train_object("RE2", "Muenster Hbf", "Muelheim(Ruhr) - Essen - Gelsenkirchen");
        duisburg.addDeparture(t1, 10, &train_object);           // hourly
    }

    /*---test---*/
    /*
    Time aty(0);
    duisburg.showDeparture(aty, 1000);
    */

    unsigned int next_min;
    int platform;
    int choice;
    while(1){

        cout<<"0 end"<<endl<<"1 schedule train"<<endl<<"2 show schedule"<<endl;
        cin>>choice;

        if(choice == 0){
            break;
        }
        else if(choice == 1){
            string train_no, to, over;
            cout<<"time of departure? ";
            Time dep;
            cin>>dep;

            cout<<"platform? ";
            cin>>platform;

            cout<<"train? ";
            cin>>train_no;
            cin.ignore();

            cout<<"to? ";
            getline(cin, to, '\n');

            cout<<endl<<"over? ";
            getline(cin, over, '\n');

            Train train_object(train_no, to, over);
            duisburg.addDeparture(dep, platform, &train_object);
        }
        else if(choice == 2){

            cout<<"show departure starting at? ";
            Time dep;
            cin>>dep;

            cout<<"for how many next minutes? ";
            cin>>next_min;
            Time to = dep + next_min;

            cout<<"DUISBERG MAIN TRAIN STATION"<<endl;
            cout<<"DEPARTURE "<<dep<<"-"<<to<<endl;
            cout<<"==================================="<<endl;
            //formatting
            cout<<setfill(' ')<<left<<setw(15)<<"Time"<<right<<setw(15)<<left<<setw(15)<<"Train"<<right<<setw(15)<<left<<setw(15)<<"over"<<right<<setw(35)<<left<<setw(15)<<"to"<<right<<setw(15)<<"platform"<<endl;
            duisburg.showDeparture(dep, next_min);
        }
    }

return 0;
}
