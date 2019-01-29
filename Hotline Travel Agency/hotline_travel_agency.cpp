#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// task class Date
class Date{
public:
    Date(){
    }
    Date(short unsigned int d, short unsigned int m, short unsigned int y ){
        day = d;
        month = m;
        year = y;
    }
    Date* operator = (const Date &d){
        day = d.day;
        month = d.month;
        year = d.year;
        return this;
    }


    Date operator + (const short unsigned int n){
        short unsigned int d, m, y;
        if(n<=28){
            if( this->day + n > this->daysInMonth[this->month - 1] ){
                d = this->day + n - this->daysInMonth[this->month - 1];
                m = this->month + 1;
                y = this->year;
                if(m>12){
                    m = 1;
                    y = y + 1;
                }
            }
        }
        //cout<<*this<<" "<<this->day;
        //cout<<d<<" "<<m<<" "<<y;
        return Date(d,m,y);
    }

    friend istream &operator >> (istream &input, Date &d){
        unsigned int day, month, year;
        char dot;
        input>>day>>dot>>month>>dot>>year;
        d.day = day;
        d.month = month;
        d.year = year;
        return input;
    }

    friend ostream &operator << (ostream &output, Date &d){
        cout<< setprecision (2) << fixed <<d.day<<"."<< setprecision (2) << fixed <<d.month<<"."<< setprecision (4) <<d.year;
    }
private:
    short unsigned int day;
    short unsigned int month;
    short unsigned int year;
    const short unsigned int daysInMonth[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
};

// task class Board
enum typeOfBoard { all_inclusive = 'a' ,  breakfast = 'b' , half_board = 'h', no_meals = 'w' };
typedef enum typeOfBoard typeOfBoard;

// this is the main culprit -_-

ostream &operator << (ostream &output, typeOfBoard &b){
    switch(b){
        case no_meals : output<<" no meals"<<endl; break;
        case breakfast : output<<" breakfast"<<endl; break;
        case half_board : output<<" half board"<<endl; break;
        case all_inclusive : output<<" all inclusive"<<endl; break;
    }
    return output;
}

// task class Hotel
class Hotel{
public:
    Hotel(){
    }
    // overloaded constructor
    Hotel(string name_c, Date arrival_c, int nights_c, int singles_c, int doubles_c, typeOfBoard board_c,double priceNightSingle_c,double priceNightDouble_c,bool parking_c){
        name = name_c;
        arrival = arrival_c;
        nights = nights_c;
        singles = singles_c;
        doubles = doubles_c;
        board = board_c;
        priceNightSingle = priceNightSingle_c;
        priceNightDouble = priceNightDouble_c;
        parking = parking_c;

    }
    // destructor
    ~Hotel(){
        cout<<"destructor hotel "<<name<<" at ";
        cout<<arrival;
        cout<<" for "<<get_guests()<<"guests done"<<endl;
    }
    double get_price(){
        double p  = priceNightDouble*doubles + priceNightSingle*singles;
        if(parking){
            p = p + 10;
        }

        return p*nights;
    }
    Date get_arrival(){
        return arrival;
    }
    Date get_checkout(){
        return arrival+nights;
    }
    int get_guests(){

        return singles + doubles*2;
    }
    void print(){
        cout<<"hotel ";
        cout<<arrival;
        cout<<" "<<name<<" for "<<nights<<" night(s) "<<doubles<<" double bed room(s) "<<singles<<" single room(s)"<<endl;
        cout<<"      with";
        cout<<board;
        if(parking)
            cout<<", parking included"<<endl;
    }
private:
    string name;
    Date arrival;
    int nights;
    int singles;
    int doubles;
    typeOfBoard board;
    double priceNightSingle;
    double priceNightDouble;
    bool parking;
};

// task class Transport
class Transport{
public:
    virtual ~Transport(){
        cout<<"destructor Transport done"<<endl;
    }
    virtual bool withTransfer()=0;
    virtual double get_price()=0;
    virtual void print()=0;
};

//Task class SelfOrganised
class SelfOrganised : public Transport{
public:
    SelfOrganised(){
    }
    virtual ~SelfOrganised(){
        cout<<"destructor SelfOrganised done"<<endl;
    }
    virtual bool withTransfer() override{
        return false;
    }
    virtual double get_price() override{
        return 0;
    }
    virtual void print() override{
        cout<<"self organized transport"<<endl;
    }
};

// Task class PublicTransport
class PublicTransport : public Transport{
public:
    PublicTransport(){
    }
    PublicTransport(Date departureDay, string code_c, string from_c, string to_c, double price_c, bool firstClass_c = false){
        departure = departureDay;
        code = code_c;
        from = from_c;
        to = to_c;
        priceOneSeat = price_c;
        firstClass = firstClass_c;
    }
    virtual ~PublicTransport(){
        cout<<"destructor PublicTransport "<<code<<" at "<<departure<<" done"<<endl;
    }
    virtual void print() override {
        cout<<departure;
        cout<<" "<<code<<" from "<<from<<" to "<<to;
        if(firstClass)
            cout<<" (first class)";

    }
//private:
protected:
    Date departure;
    string code;
    string from;
    string to;
    double priceOneSeat;
    bool firstClass;

};

//Task class Flight
class Flight : public PublicTransport{
public:
    Flight(Date departureDay, string code_c, string from_c, string to_c, double price_c, bool firstClass_c = false, bool transfer_c = true){
        departure = departureDay;
        code = code_c;
        from = from_c;
        to = to_c;
        priceOneSeat = price_c;
        firstClass = firstClass_c;
        transfer = transfer_c;
    }
    virtual ~Flight() {
        cout<<"destructor Flight done"<<endl;
    }
    virtual bool withTransfer() override{
        return transfer;
    }
    virtual double get_price() override{
        if(firstClass)
            return priceOneSeat*2;
        else
            return  priceOneSeat;
    }
    virtual void print() override{
        cout<<"flight ";
        PublicTransport::print();
        cout<<endl;
        if(transfer)
            cout<<" transfer included";
        else
            cout<<" no transfer";
    }
private:
    bool transfer;

};

//Task class Train
class Train : public PublicTransport{
public:
    Train(Date departureDay, string code_c, string from_c, string to_c, double price_c, bool firstClass_c = false){
        departure = departureDay;
        code = code_c;
        from = from_c;
        to = to_c;
        priceOneSeat = price_c;
        firstClass = firstClass_c;

    }
    virtual ~Train(){
        cout<<"destructor Train done"<<endl;
    }
    virtual bool withTransfer() override{
        return false;
    }
    virtual double get_price() override{
        if(firstClass)
            return priceOneSeat*1.5;
        else
            return priceOneSeat;
    }
    virtual void print() override{
        cout<<"train ";
        PublicTransport::print();
        cout<<endl;
        cout<<" no transfer"<<endl;

    }
};

//Task class Trip
class Trip{
public:

    Trip(unsigned int travellers_c, Hotel *hotel_c, Transport *transportOutward_c, Transport *transportBack_c, Trip *next_c = NULL){
        //lastNo++;
        //no = lastNo;
        travellers = travellers_c;
        hotel = hotel_c;
        transportOutward = transportOutward_c;
        transportBack = transportBack_c;
        next = next_c;
    }
    virtual ~Trip(){
        delete(hotel);
        delete(transportOutward);
        delete(transportBack);
        cout<<"destructor Trip done"<<endl;
    }
    int get_no(){
        return no;
    }
    Trip* get_next(){
        return next;
    }
    void set_next(Trip* next_trip){
        next = next_trip;
    }
    double get_price(){
        return ( hotel->get_price() + (transportBack->get_price()+transportOutward->get_price())*travellers );       // genjam
    }
    void print(){
        cout<<"Trip inquiry "<<no<<" for "<<travellers<<" person(s)"<<endl;
        cout<<"check-in: "<<setfill(' ')<<right<<setw(15);
        hotel->print();
        cout<<"outward journey: ";
        transportOutward->print();
        cout<<"journey back: ";
        transportBack->print();
        cout<<endl;
        cout<<"        "<<"price: "<< setprecision (2) << fixed <<get_price()<<" EUR"<<endl;
        cout<<endl;
    }
private:
    const unsigned int no=++lastNo;
    static unsigned int lastNo;
    unsigned int travellers;
    Hotel *hotel;
    Transport *transportOutward;
    Transport *transportBack;
    Trip *next;
};
unsigned int Trip::lastNo = 0;

//Task class TravelAgency
class TravelAgency{
public:

    TravelAgency(){
        trips = NULL;
    }
    void add(Trip *head){
        if(trips == NULL)
            trips = head;   // add as head
        else
            head->set_next(trips);
            trips = head;

    }
    void remove(Trip *trip){
        if(trips == trip){
            trips = trip->get_next();
            delete(trip);
        }
        else{
            Trip *temp = trips;
            while(temp->get_next() != NULL){
                if(temp->get_next() == trip){
                    temp->set_next(temp->get_next()->get_next());
                    delete(trip);
                }
                else
                    temp = temp->get_next() ;
            }
        }
    }
    Trip* search(int no){
        Trip *temp = trips;
        while(temp!=NULL){
            if(temp->get_no() == no)
                return temp;
            else
                temp = temp->get_next();
        }
    }
    void printAllTrips(){
        Trip *temp = trips;
        while(temp!=NULL){
            temp->print();
            temp=temp->get_next();
        }
    }
private:
    Trip* trips;

};

int main(){

    TravelAgency travelAgency;
    int choice;
    while(1){
        cout<<endl<<"HOTLINE TRAVEL AGENCY\n0 end\n1 new trip\n2 search trip\n3 show all trip offers"<<endl;
        cout<<"your choice : ";
        cin>>choice;
        if(choice == 0)
            break;
        else if(choice == 1){

            cout<<"Name of hotel: ";
            string name;
            cin>>name;
            cout<<"Arrival on: ";
            Date date_arrival;
            cin>>date_arrival;
            cout<<"How many nights: ";
            int singles, doubles;
            short unsigned int nights;
            cin>>nights;
            if(nights > 28){
                cout<<"error";
                break;
            }

            Date date_departure = date_arrival+nights;
            //cout<<"departure: "<<date_departure<<endl;

            cout<<"how many single bed rooms: ";
            cin>>singles;
            cout<<"how many double bed rooms: ";
            cin>>doubles;
            // board
            cout<<"a all inclusive\nb breakfast\nh half board\nw without meals"<<endl;
            char b;
            cin>>b;

            typeOfBoard type_ofBoard = (typeOfBoard) b;

            // hotel
            cout<<"price one night in single bed room: ";
            double priceSingle;
            cin>>priceSingle;

            cout<<"price one night in double bed room: ";
            double priceDouble;
            cin>>priceDouble;

            cout<<"with parking (y)es or (n)o: ";
            char if_parking;
            bool parking;
            cin>>if_parking;
            if(if_parking == 'y')
                parking = true;
            else if(if_parking == 'n')
                parking = false;

            Hotel *hotel = new Hotel(name, date_arrival, nights, singles, doubles, type_ofBoard, priceSingle, priceDouble, parking);

            // transport
            Transport *out, *back;
            cout<<"please choose transport for outward journey\n0 self organised\n1 by flight\n2 by train\nyour choice: ";
            int choice_transport1;
            cin>>choice_transport1;

            if(choice_transport1 == 0){
                // self organised object
                out = new SelfOrganised();
            }
            else if(choice_transport1 == 1){
                        // flight
                cin.ignore();
                string code;
                string from, to;
                double ticket_price;
                cout<<"code of flight: ";
                getline(cin, code, '\n');
                cout<<"airport of departure: ";
                getline(cin, from, '\n');
                cout<<"airport of arrival: ";
                getline(cin, to, '\n');

                cout<<"price for one passenger: ";

                cin>>ticket_price;

                // flight object
                out = new Flight(date_arrival, code, from, to, ticket_price);

            }
            else if(choice_transport1 == 2){
                // train
                cin.ignore();
                string code;
                string from, to;
                double ticket_price;
                cout<<"code of train: ";
                getline(cin, code, '\n');
                cout<<"main train station of departure: ";
                getline(cin, from, '\n');
                cout<<"main train station of arrival: ";
                getline(cin, to, '\n');
                cout<<"price for one passenger: ";
                cin>>ticket_price;
                //Train object
                out = new Train(date_arrival, code, from, to, ticket_price);

            }

            cout<<"please choose transport for journey back\n0 self organised\n1 by flight\n2 by train\nyour choice: ";
            int choice_transport2;
            cin>>choice_transport2;

            if(choice_transport2 == 0){
                // self organised object
                back = new SelfOrganised();
            }
            else if(choice_transport2 == 1){
                        // flight
                cin.ignore();
                string code;
                string from, to;
                double ticket_price;
                cout<<"code of flight: ";
                getline(cin, code, '\n');
                cout<<"airport of departure: ";
                getline(cin, from, '\n');
                cout<<"airport of arrival: ";
                getline(cin, to, '\n');
                cout<<"price for one passenger: ";
                cin>>ticket_price;
                // flight object
                back = new Flight(date_departure, code, from, to, ticket_price);

            }
            else if(choice_transport2 == 2){
                // train

                cin.ignore();
                string code;
                string from, to;
                double ticket_price;
                cout<<"code of train: ";
                getline(cin, code, '\n');
                cout<<"main train station of departure: ";
                getline(cin, from, '\n');
                cout<<"main train station of arrival: ";
                getline(cin, to, '\n');

                cout<<"price for one passenger: ";

                cin>>ticket_price;
                // Train object
                back = new Train(date_departure, code, from, to, ticket_price);
            }

            /*create trip and add to travel agency*/
            Trip *trip1 = new Trip(hotel->get_guests(), hotel, out, back);
            travelAgency.add(trip1);
        }
        else if(choice == 2){
            int numberOfTrip;
            cout<<"number of trip: ";
            cin>>numberOfTrip;
            Trip* trip = travelAgency.search(numberOfTrip);
            if(trip){
                trip->print();
                cout<<"(d)elete or (n)ot: ";
                char if_delete;
                cin>>if_delete;
                if(if_delete == 'd'){
                    travelAgency.remove(trip);
                }
            }
            else
                cout<<"Trip not found"<<endl;
        }
        else if(choice == 3){
            travelAgency.printAllTrips();
        }
    }

return 0;
}
