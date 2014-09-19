/*
 * date.cpp
 *
 */

#include "date.hpp"

/*
 * Estrutura Date da classe Date
 */
struct Date::DateStruct{
    time_t secondsFull;
};

Date::Date(){
    data = new DateStruct;
    setDate();
}

Date::~Date(){
    delete data;
    data = NULL;
}

void Date::setDate(){
    data->secondsFull = time(0);
}

void Date::printDate(DateFormat dateFormat, bool showWeek){
    tm* tm = localtime(&(data->secondsFull));

    cout<< tm->tm_mday <<endl;
}
