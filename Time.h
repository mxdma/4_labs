class Time{
public:
    Time(){
        struct timeval utime{};
        gettimeofday(&utime, nullptr);
        this->hour = (utime.tv_sec % SEC_IN_DAY) / SEC_IN_HOUR + 7;
        this->minute = (utime.tv_sec % SEC_IN_DAY % SEC_IN_HOUR) / SEC_IN_MIN;
        this->second = utime.tv_sec % SEC_IN_DAY % SEC_IN_HOUR %SEC_IN_MIN;
        this->msecond = utime.tv_usec / MSEC_IN_SEC;
        cout << "Constructor w/o argument called" << endl;
    }
    Time(int hour, int minute, int second, int msecond){
        if (hour >= 0 && hour < 24) {this->hour = hour % 24;} else {this->hour = 0;}
        if (minute >= 0 && minute < 60) {this->minute = minute % 60;} else {this->minute = 0;}
        if (second >= 0 && second < 60) {this->second = second % 60;} else {this->second = 0;}
        if (msecond >= 0 && msecond < 1000) {this->msecond = msecond % 1000;} else {this->msecond = 0;}
        cout << "Constructor w/ arguments #1 called" << endl;
    }
    Time(Time const &old){
        this->hour = old.hour;
        this->minute = old.minute;
        this->second = old.second;
        this->msecond = old.msecond;
        cout << "Constructor for copying called" << endl;
    }
    ~Time(){
        cout << "Destructor called" << endl;
    }

    int getTimeHour() {return hour;}
    int getTimeMinute() {return minute;}
    int getTimeSecond() {return second;}
    int getTimeMsecond() {return msecond;}
    

    void setTimeHour(int hour) {this->hour = hour;}
    void setTimeMinute(int minute) {this->minute = minute;}
    void setTimeSecond(int second) {this->second = second;}
    void setTimeMsecond(int msecond) {this->second = msecond;}

    
    char* c_str(){
        char* str = new char[15];
        sprintf(str, "%d:%d:%d:%d", hour, minute, second, msecond);
        return str;
    }
    static Time getSystemTime(Time& t){//stati4
        Time t4;
        struct timeval time{};
        gettimeofday(&time, nullptr);
        t4.hour = (time.tv_sec % SEC_IN_DAY) / SEC_IN_HOUR +7;
        t4.minute = (time.tv_sec % SEC_IN_DAY % SEC_IN_HOUR) / SEC_IN_MIN;
        t4.second = time.tv_sec % SEC_IN_DAY % SEC_IN_HOUR % SEC_IN_MIN;
        t4.msecond = time.tv_usec / MSEC_IN_SEC;
        return t4;
    }
    const char* getSystemTimeInString(){
        Time t = this->getSystemTime(t);
        stringstream ss;
        ss << t.hour << ":" << t.minute << ":" << t.second << ":" << t.msecond;
        return ss.str().c_str();
    }
    void diffTimeMilli(int ms){
        int msec = msecond + second * 1000 + minute  * 60 * 1000 + msecond * 60 * 60 * 1000 - ms;
        if(msec>0){
            msecond = msec % 1000;
            second = msec / 1000 % 60;
            minute = msec / 1000 / 60 % 60;
            hour = msec / 1000 / 60 / 60 % 24;
        }
        else{
            msecond = 0;
            second = 0;
            minute = 0;
            hour = 0;
        }
    }
    void sumTimeMilli(int ms){
        int msec = msecond + second * 1000 + minute  * 60 * 1000 + msecond * 60 * 60 * 1000 + ms;
        if(msec>0){
            msecond = msec % 1000;
            second = msec / 1000 % 60;
            minute = msec / 1000 / 60 % 60;
            hour = msec / 1000 / 60 / 60 % 24;
        }
    }
    static Time sumTime(Time& t1, Time& t2){
        Time t3;
        t3.msecond = (t1.msecond + t2.msecond) % 1000;
        t3.second = (t1.second + t2.second) % 60 + (t1.msecond + t2.msecond) / 1000;
        t3.minute = (t1.minute + t2.minute) % 60 + (t1.second + t2.second) / 60;
        t3.hour = (t1.hour + t2.hour) + (t1.minute + t2.minute) /60;
        return t3;
    }
    static Time diffTime(Time& t1, Time& t2){
        Time t3;
        int msec;
        msec = (t1.msecond + t1.second * 1000 + t1.minute * 60 * 1000 + t1.hour * 60 * 60 * 1000) -
        (t2.msecond + t2.second * 1000 + t2.minute * 60 * 1000 + t2.hour * 60 * 60 * 1000);
        t3.msecond = msec % 1000;
        t3.second = msec / 1000 % 60;
        t3.minute = msec / 1000 / 60 % 60;
        t3.hour = msec / 1000 / 60 / 60 % 24;
        return t3;
    }

    
private:
    int hour;
    int minute;
    int second;
    int msecond;

};
