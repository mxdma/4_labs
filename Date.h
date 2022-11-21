class Date{
public:
    Date() {
        time_t now = std::time(0);
        tm *ltm = localtime(&now);
        this->year = ltm->tm_year + 1900;
        this->month = ltm->tm_mon + 1;
        this->day = ltm->tm_mday;
        cout << "Constructor w/o arguments called" << endl;
    }
    
    Date(int year, int month, int day) {
        if (year >= 0) {this->year = year;} else {this->year = -year;}
        if (month >= 1 && month < 12) {this->month = month;} else {this->month = month % 12;}
        if (day >= 1 && day < 31) {this->day = day;} else {this->day = day % 31;}
        cout << "Constructor w/ arguments #1 called" << endl;
    }
    
    Date(Date const &old){
        this->year = old.year;
        this->month = old.month;
        this->day = old.day;
        cout << "Constructor for copying called" << endl;
    }
    
    ~Date(){
        cout << "Destructor called" << endl;
    }
    
    int getDateYear() {return year;}
    int getDateMonth() {return month;}
    int getDateDay() {return day;}
    

    void setDateYear(int year) {this->year = year;}
    void setDateMonth(int month) {this->month = month;}
    void setDateDay(int day) {this->day = day;}
    
    char* c_str(){
        char* str = new char[25];
        sprintf(str, "%d:%d:%d", year, month, day);
        return str;
    }
    
    static Date getSystemDate(Date& d){
        Date d1;
        time_t now = std::time(0);
        tm *ltm = localtime(&now);
        d1.year = ltm->tm_year + 1900;
        d1.month = ltm->tm_mon + 1;
        d1.day =ltm->tm_mday;
        return d1;
    }
    
    const char* getSystemDateInString(){
        Date d = this->getSystemDate(d);
        stringstream ss;
        ss << d.year << ":" << d.month << ":" << d.day;
        return ss.str().c_str();
    }
    
    static Date sumDate(Date& d1, Date &d2) {
        Date d3;
        d3.day = (d1.day + d2.day) % 31;
        d3.month = (d1.month + d2.month) % 12  + (d1.day + d2.day) / 31;
        d3.year = (d1.year + d2.year)  + (d1.month + d2.month) / 12;
        return d3;
    }
    
    static Date diffDate(Date& d1, Date& d2){
        Date d3;
        int days = 0;
        if(d1.year >= d2.year && d1.month >= d2.month && d1.day >= d2.day){
            days = (d1.day + d1.month * 31 + d1.year * 365) - (d2.day + d2.month * 31 + d2.year * 365);
        }else
        {
            cout << "error" << endl;
        }
        d3.day = days % 365 % 31;
        d3.month = days / 31 % 12;
        d3.year = days / 365;
        cout << d3.year << ":" << d3.month << ":" << d3.day << endl;
        return d3;
    }
    
private:
    int year;
    int month;
    int day;
};
