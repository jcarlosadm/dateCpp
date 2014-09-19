/*
 * date.cpp
 *
 */

#include "date.hpp"

/*
 * Estrutura Date da classe Date
 */
struct Date::DateStruct{
    // tempo em segundos desde 1900
    time_t secondsFull;
};

/* **************************************************
 * Funções auxiliares
 ****************************************************/

time_t makeDate(int day,int month,int year,int hour,int minute,int second){

    // constrói uma data com os valores passados
    struct tm tm;
    tm.tm_mday = day;
    tm.tm_mon = month - 1;
    tm.tm_year = year - 1900;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    tm.tm_sec = second;

    // passa para o formato em segundos desde 1900
    time_t data = mktime(&tm);

    return data;
}

/* **************************************************
 * Funções da classe Date
 ****************************************************/

/*
 * Construtor padrão
 * Configura data para a data atual
 */
Date::Date(){
    // aloca memória para ponteiro-membro data
    data = new DateStruct;
    // configura para a data atual
    setDate();
}

/*
 * Construtor personalizado
 * Configura a data para uma data especificada
 *
 * int day : dia do mês
 * int month : mês
 * int year : ano
 * int hour : hora (padrão 0)
 * int minute : minutos (padrão 0)
 * int seconds : segundos (padrão 0)
 */
Date::Date(int day,int month, int year, int hour, int minute, int second){
    // aloca memória para ponteiro-membro data
    data = new DateStruct;
    // se a data especificada não for válida...
    if(!setDate(day,month,year,hour,minute,second))
        // configura para a data atual
        setDate();
}

/*
 * Destrutor
 */
Date::~Date(){
    // desaloca memória de onde data aponta
    delete data;
    // configura data para NULL
    data = NULL;
}

/*
 * Configura a data para a data atual
 */
void Date::setDate(){
    // configura a hora atual
    data->secondsFull = time(0);
}

/*
 * Configura a data completa
 * Retorna false se não conseguir (a data é falsa)
 *
 * int day : dia do mês
 * int month : mês
 * int year : ano
 * int hour : hora (padrão 0)
 * int minute : minutos (padrão 0)
 * int seconds : segundos (padrão 0)
 */
bool Date::setDate(int day, int month, int year, int hour, int minute, int second){

    // verifica se a data é válida, e retorna false caso não seja
    if(!validateDate(day,month,year,hour,minute,second)) return false;

    // constrói uma data com os valores passados
    time_t seconds_t = makeDate(day,month,year,hour,minute,second);

    // se conseguir passar para segundos...
    if(seconds_t != -1){
        // sucesso
        data->secondsFull = seconds_t;
        return true;
    }
    // caso contrário, falha
    else
        return false;

}

/*
 * Configura data a partir dos segundos desde 1900
 * Retorna false se não conseguir (data não válida)
 *
 * time_t seconds : segundos desde 1900
 */
bool Date::setDate(time_t seconds){
    // se segundos menores que zero, retorna false
    if(seconds < 0)
        return false;
    // caso contrário...
    else{
        // define nova data e retorna sucesso
        data->secondsFull = seconds;
        return true;
    }
}

/*
 * Retorna a data em segundos desde 1900
 */
time_t Date::getDateInSeconds(){
    // retorna segundos totais desde 1900
    return data->secondsFull;
}

/* corrigir depois */
void Date::printDate(DateFormat dateFormat, bool showWeek){
    tm* tm = localtime(&(data->secondsFull));

    cout<< tm->tm_mday <<endl;
}

/*
 * Verifica se uma data é válida
 * Retorna false se não for
 *
 * int day : dia do mês
 * int month : mês
 * int year : ano
 * int hour : hora (padrão 0)
 * int minute : minutos (padrão 0)
 * int second : segundos (padrão 0)
 */
bool Date::validateDate(int day, int month, int year, int hour, int minute, int second){

    // primeira checagem
    if(second<0 || second>59)
        return false;
    else if(minute<0 || minute>59)
        return false;
    else if(hour<0 || hour>23)
        return false;
    else if(month<1 || month>12)
        return false;
    else if(day<1 || day>31)
        return false;

    // agora vamos validar o dia
    switch(month){
    case 2:
        if(year%4==0){
            if(day>29) return false;
        }
        else if(day>28)return false;
        break;
    case 4:
        if(day>30)return false;
        break;
    case 6:
        if(day>30)return false;
        break;
    case 9:
        if(day>30)return false;
        break;
    case 11:
        if(day>30)return false;
    }

    return true;
}
