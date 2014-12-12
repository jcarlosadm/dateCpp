/**
 * \file date.cpp
 * Implementação do arquivo date.hpp
 */

#include "../hpp_files/date.hpp"

/***************************************************************************
 * Estruturas
 ***************************************************************************/

/**
 * Estrutura Date da classe Date
 */
struct Date::DateStruct{
    // tempo em segundos desde 1900
    time_t secondsFull;
};

/**
 * enumerador que indica AM ou PM
 */
enum AMPMSystem {
    AM_SYSTEM,
    PM_SYSTEM
};

/***************************************************************************
 * Funções auxiliares
 ***************************************************************************/

/**
 * Pega hora em formato 24 horas e devolve em formato AM PM
 * \return Horas no formato de 12 horas
 * \param hour Hora em formato 24 horas
 */
int getHourInAmPm(int hour){
    int returning;

    if(hour == 0)
        returning = 12;
    else if(hour > 12 && hour < 24)
        returning = (hour - 12);
    else
        returning = hour;

    return returning;
}

/**
 * Pega hora em formato 24 horas e devolve valor de AM_SYSTEM ou
 * PM_SYSTEM
 * \return AM_SYSTEM ou PM_SYSTEM
 * \param hour Hora em formato de 24 horas
 */
int getAmPmSystem(int hour){
    if(hour >= 0 && hour < 12)
        return AM_SYSTEM;
    else
        return PM_SYSTEM;
}

/**
 * Imprime o dia da semana de acordo com o valor fornecido
 * \param weekDay Dia da semana (0 - 6, começando pelo Domingo)
 */
void printWeek(int weekDay){

    // imprime uma string de acordo com o dia da semana
    switch(weekDay){
    case SUNDAY:
        cout<<"Sunday";
        break;

    case MONDAY:
        cout<<"Monday";
        break;

    case TUESDAY:
        cout<<"Tuesday";
        break;

    case WEDNESDAY:
        cout<<"Wednesday";
        break;

    case THURSDAY:
        cout<<"Thursday";
        break;

    case FRIDAY:
        cout<<"Friday";
        break;

    case SATURDAY:
        cout<<"Saturday";
    }

}

/**
 * Cria data em segundos desde 1900
 * \return Data em segundos desde 1900
 * \param day Dia do mês
 * \param month Mês
 * \param year Ano
 * \param hour Hora
 * \param minute Minutos
 * \param second Segundos
 */
time_t makeDate(int day,int month,int year,int hour,int minute,int second){

    // constrói uma data com os valores passados
    tm tm;
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

/***************************************************************************
 * Funções da classe Date
 ***************************************************************************/

/**
 * Construtor padrão<BR>
 * Configura data para a data atual
 */
Date::Date(){
    // aloca memória para ponteiro-membro data
    data = new DateStruct;
    // configura para a data atual
    setDate();
}

/**
 * Construtor personalizado<BR>
 * Configura a data para uma data especificada
 * \param day Dia do mês
 * \param month Mês
 * \param year Ano
 * \param hour Hora (valor padrão 0)
 * \param minute Minutos (valor padrão 0)
 * \param seconds Segundos (valor padrão 0)
 */
Date::Date(int day,int month, int year, int hour, int minute, int second){
    // aloca memória para ponteiro-membro data
    data = new DateStruct;
    // se a data especificada não for válida...
    if(!setDate(day,month,year,hour,minute,second))
        // configura para a data atual
        setDate();
}

/**
 * Destrutor
 */
Date::~Date(){
    // desaloca memória de onde data aponta
    delete data;
    // configura data para NULL
    data = NULL;
}

/**
 * Configura a data para a data atual
 */
void Date::setDate(){
    // configura a hora atual
    data->secondsFull = time(0);
}

/**
 * Configura a data completa
 * \return false se não conseguir (a data não é válida)
 * \param day Dia do mês
 * \param month Mês
 * \param year Ano
 * \param hour Hora (padrão 0)
 * \param minute Minutos (padrão 0)
 * \param seconds Segundos (padrão 0)
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

/**
 * Configura data a partir dos segundos desde 1900
 * \return false se não conseguir (data não válida)
 * \param seconds Segundos desde 1900
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

/**
 * Retorna a data em segundos desde 1900
 * \return Segundos desde 1900
 */
time_t Date::getDateInSeconds(){
    // retorna segundos totais desde 1900
    return data->secondsFull;
}

/**
 * Retorna um componente da data (dia, mês, ano, hora ...)
 * \return -1 se não conseguir retornar o solicitado<BR>
 * Obs: alguns retornos específicos:<BR>
 * &nbsp; &nbsp; dia do mês: 1 - 31<BR>
 * &nbsp; &nbsp; dia do ano: 1 - 365<BR>
 * &nbsp; &nbsp; dia da semana: 0 (domingo) - 6(sábado)<BR>
 * &nbsp; &nbsp; mês: 1 - 12<BR>
 * &nbsp; &nbsp; hora: 0 - 23<BR>
 * &nbsp; &nbsp; hora_ampm: 1-12<BR>
 * &nbsp; &nbsp; outros: formatos já esperados
 * \param dateComponent Enumerador que indica a parte da
 * data a ser retornada (veja o enumerador neste header file)
 */
int Date::getDateComponent(DateComponent dateComponent){
    tm* tm = localtime(&(data->secondsFull));

    switch(dateComponent){
    case MDAY:
        return tm->tm_mday;
    case YDAY:
        return tm->tm_yday;
    case WDAY:
        return tm->tm_wday;
    case MONTH:
        return (tm->tm_mon + 1);
    case YEAR:
        return (tm->tm_year + 1900);
    case HOUR:
        return tm->tm_hour;
    case HOUR_AMPM:
        return getHourInAmPm(tm->tm_hour);
    case MINUTE:
        return tm->tm_min;
    case SECOND:
        return tm->tm_sec;
    default:
        return -1;
    }
}

/**
 * Gera uma string e coloca em dateString
 * \param dateFormat Indica qual o formato da string a ser utilizado
 *            (veja o enumerador DateFormat neste header file)
 * \param dateString String a ser preenchida
 * \param showWeek Opção que indica se o nome do dia da semana é incluído
 *                 (por padrão sim)
 */
void Date::getStringDate(DateFormat dateFormat, string& dateString, bool showWeek){

    tm* tm = localtime(&(data->secondsFull));
    int day,month,year,hour,min,sec;
    string ampm;

    if(dateFormat==DATE_DMY || dateFormat==DATE_YMD || dateFormat==DATE_DMY_HMS
        || dateFormat==DATE_YMD_HMS || dateFormat==DATE_DMY_HMS_AMPM
        || dateFormat==DATE_YMD_HMS_AMPM){
        day = tm->tm_mday;
        month = tm->tm_mon+1;
        year = tm->tm_year+1900;
    }

    if(dateFormat==DATE_HMS || dateFormat==DATE_DMY_HMS || dateFormat==DATE_YMD_HMS){
        hour = tm->tm_hour;
        min = tm->tm_min;
        sec = tm->tm_sec;
    }

    if(dateFormat==DATE_HMS_AMPM || dateFormat==DATE_DMY_HMS_AMPM
        || dateFormat==DATE_YMD_HMS_AMPM){
        hour = getHourInAmPm(tm->tm_hour);
        min = tm->tm_min;
        sec = tm->tm_sec;
        ampm = (getAmPmSystem(tm->tm_hour)==AM_SYSTEM ? AM : PM);
    }

    ostringstream os;
    switch(dateFormat){

    case DATE_DMY:
        os << day <<"/"<< month <<"/"<<year;
        break;
    case DATE_YMD:
        os << year <<"/"<< month <<"/"<< day;
        break;
    case DATE_HMS:
        os << hour << ":" << min << ":" << sec;
        break;
    case DATE_HMS_AMPM:
        os << hour << ":" << min << ":" << sec << " " << ampm;
        break;
    case DATE_DMY_HMS:
        os << day <<"/"<< month <<"/"<< year <<" "<< hour <<":"<< min <<":"<<sec;
        break;
    case DATE_YMD_HMS:
        os << year <<"/"<< month <<"/"<< day <<" "<< hour <<":"<< min <<":"<<sec;
        break;
    case DATE_DMY_HMS_AMPM:
        os << day <<"/"<< month <<"/"<< year <<" "<< hour <<":"<< min <<":"<<sec<<" "<<ampm;
        break;
    case DATE_YMD_HMS_AMPM:
        os << year <<"/"<< month <<"/"<< day <<" "<< hour <<":"<< min <<":"<<sec<<" "<<ampm;
    }

    dateString = os.str();

    if(showWeek){

        switch(tm->tm_wday){
        case SUNDAY:
            dateString += " Sunday";
            break;
        case MONDAY:
            dateString += " Monday";
            break;
        case TUESDAY:
            dateString += " Tuesday";
            break;
        case WEDNESDAY:
            dateString += " Wednesday";
            break;
        case THURSDAY:
            dateString += " Thursday";
            break;
        case FRIDAY:
            dateString += " Friday";
            break;
        case SATURDAY:
            dateString += " Saturday";
        }
    }

}

/**
 * Gera uma string do dia da semana e coloca em weekString
 * \param weekString String a ser preenchida
 */
void Date::getStringWeek(string& weekString){

    tm* tm = localtime(&(data->secondsFull));

    switch(tm->tm_wday){
    case SUNDAY:
        weekString = "Sunday";
        break;
    case MONDAY:
        weekString = "Monday";
        break;
    case TUESDAY:
        weekString = "Tuesday";
        break;
    case WEDNESDAY:
        weekString = "Wednesday";
        break;
    case THURSDAY:
        weekString = "Thursday";
        break;
    case FRIDAY:
        weekString = "Friday";
        break;
    case SATURDAY:
        weekString = "Saturday";
    }

}

/**
 * Adiciona (ou subtrai) um valor em uma componente da data
 * \return false se não conseguir
 * \param dateComponent Parte da data a ser adicionada (ou subtraída)
 * \param value Valor a ser adicionado (ou subtraído)
 * \param add Se deverá adicionar ou subtrair (adiciona por padrão)
 */
bool Date::addDateComponent(DateComponent dateComponent, int value, bool add){

    tm* tm = localtime(&(data->secondsFull));

    switch(dateComponent){
    case MDAY:
        if(add) tm->tm_mday += value;
        else tm->tm_mday -= value;
        break;
    case YDAY:
        if(add) tm->tm_yday += value;
        else tm->tm_yday -= value;
        break;
    case WDAY:
        if(add) tm->tm_wday += value;
        else tm->tm_wday -= value;
        break;
    case MONTH:
        if(add) tm->tm_mon += value;
        else tm->tm_mon -= value;
        break;
    case YEAR:
        if(add) tm->tm_year += value;
        else tm->tm_year -= value;
        break;
    case HOUR:
        if(add) tm->tm_hour += value;
        else tm->tm_hour -= value;
        break;
    case HOUR_AMPM:
        if(add) tm->tm_hour += value;
        else tm->tm_hour -= value;
        break;
    case MINUTE:
        if(add) tm->tm_min += value;
        else tm->tm_min -= value;
        break;
    case SECOND:
        if(add) tm->tm_sec += value;
        else tm->tm_sec -= value;
    }

    time_t date2 = mktime(tm);

    if(date2 != -1){
        data->secondsFull = date2;
        return true;
    }
    else
        return false;

}

/**
 * Imprime data no prompt
 * \param dateFormat Enumerador que indica o formato da string
 *          a ser utilizado (veja o enumerador neste header file)
 * \param showWeek Se o nome do dia da semana deve ser mostrado
 *                  (sim por padrão)
 */
void Date::printDate(DateFormat dateFormat, bool showWeek){

    // coloca data em uma estrutura struct tm (ver time.h)
    tm* tm = localtime(&(data->secondsFull));

    // imprime de acordo com o formato determinado em dateString
    switch(dateFormat){

    case DATE_DMY:
        cout<<tm->tm_mday<<"/"<<tm->tm_mon+1<<"/"<<tm->tm_year+1900;
        break;

    case DATE_YMD:
        cout<<tm->tm_year+1900<<"/"<<tm->tm_mon+1<<"/"<<tm->tm_mday;
        break;

    case DATE_HMS:
        cout<<tm->tm_hour<<":"<<tm->tm_min<<":"<<tm->tm_sec;
        break;

    case DATE_HMS_AMPM:
        cout<<getHourInAmPm(tm->tm_hour)<<":"<<tm->tm_min<<":"<<tm->tm_sec;
        if(getAmPmSystem(tm->tm_hour) == AM_SYSTEM)
            cout<<" "<<AM;
        else
            cout<<" "<<PM;
        break;

    case DATE_DMY_HMS:
        cout<<tm->tm_mday<<"/"<<tm->tm_mon+1<<"/"<<tm->tm_year+1900;
        cout<<" "<<tm->tm_hour<<":"<<tm->tm_min<<":"<<tm->tm_sec;
        break;

    case DATE_YMD_HMS:
        cout<<tm->tm_year+1900<<"/"<<tm->tm_mon+1<<"/"<<tm->tm_mday;
        cout<<" "<<tm->tm_hour<<":"<<tm->tm_min<<":"<<tm->tm_sec;
        break;

    case DATE_DMY_HMS_AMPM:
        cout<<tm->tm_mday<<"/"<<tm->tm_mon+1<<"/"<<tm->tm_year+1900;
        cout<<" "<<getHourInAmPm(tm->tm_hour)<<":"<<tm->tm_min<<":"<<tm->tm_sec;
        if(getAmPmSystem(tm->tm_hour) == AM_SYSTEM)
            cout<<" "<<AM;
        else
            cout<<" "<<PM;
        break;

    case DATE_YMD_HMS_AMPM:
        cout<<tm->tm_year+1900<<"/"<<tm->tm_mon+1<<"/"<<tm->tm_mday;
        cout<<" "<<getHourInAmPm(tm->tm_hour)<<":"<<tm->tm_min<<":"<<tm->tm_sec;
        if(getAmPmSystem(tm->tm_hour) == AM_SYSTEM)
            cout<<" "<<AM;
        else
            cout<<" "<<PM;
        break;
    }

    // imprime o nome do dia da semana, se foi solicitado
    if(showWeek){
        cout<<" ";
        printWeek(tm->tm_wday);
    }

    // dá quebra de linha
    cout<<endl;

}

/**
 * Imprime no prompt o nome do dia da semana
 */
void Date::printWeekName(){
    tm* tm = localtime(&(data->secondsFull));

    printWeek(tm->tm_wday);
}

/**
 * Verifica se uma data é válida
 * \return false se não for
 * \param day Dia do mês
 * \param month Mês
 * \param year Ano
 * \param hour Hora (valor padrão 0)
 * \param minute Minutos (valor padrão 0)
 * \param second Segundos (valor padrão 0)
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
