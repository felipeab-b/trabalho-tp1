#include "date.hpp"

void Date::validate(int day, int month, int year) {

    if (year < 2000 || year > 2099) {
        throw invalid_argument("Invalid year");
    }
    if (month < 1 || month > 12) {
        throw invalid_argument("Invalid month");
    }

    int maxDay;

    if (month == 4 || month == 6 || month == 9 || month == 11){
        maxDay = 30;
    } else if((month == 2 && year%4 == 0 && year%100 == 0 && year%400 == 0) || (month == 2 && year%4 == 0 && year%100 != 0)) { 
        maxDay = 29;
    } else if((month == 2 && year%4 != 0) || (month == 2 && year%4 == 0 && year%100 == 0 && year%400 != 0)) {
        maxDay = 28;
    } else {
        maxDay = 31;
    }

    if (day < 1 || day > maxDay) {
        throw invalid_argument("Invalid day");
    }
}

void Date::set(int day, int month, int year) {
    validate(day, month, year);
    this->day = day;
    this->month = month;
    this->year = year;
}

string Date::get() const {
    string formattedDay;
    string formattedMonth;
    string formattedYear = to_string(year);

    if (day < 10) {
        formattedDay = "00";
        formattedDay[0] = '0';
        formattedDay[1] = '0' + day;
    } else {
        formattedDay = to_string(day);
    }

    if (month < 10) {
        formattedMonth = "00";
        formattedMonth[0] = '0';
        formattedMonth[1] = '0' + month;
    } else {
        formattedMonth = to_string(month);
    }

    return formattedDay + "/" + formattedMonth + "/" + formattedYear;
}