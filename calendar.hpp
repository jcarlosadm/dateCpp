/*
 * calendar.hpp
 *
 */

#ifndef CALENDAR_HPP_
#define CALENDAR_HPP_

#include <iostream>
#include <ctime> // time_t, struct tm, funções de tempo
#include <string> // manipulação de string
#include <new> // new e delete

using namespace std;

/*
 * Enumerador das partes de uma data
 */
enum DateComponent{
    MDAY, // dia do mês
    YDAY, // dia do ano
    WDAY, // dia da semana
    MONTH, // mês
    YEAR, // ano
    HOUR, // hora (formato 24 horas)
    HOUR_AMPM, // hora (formato am/pm)
    MINUTE, // minutos
    SECOND // segundos
};

/*
 * Enumerador dos formatos da data
 */
enum DateFormat{
    DATE_DMY, // dd/mm/yyyy
    DATE_YMD, // yyyy/mm/dd
    DATE_HMS, // h:m:s 24 hours
    DATE_HMS_AMPM, // h:m:s am/pm format
    DATE_DMY_HMS, // dd/mm/yyyy h:m:s 24 hours
    DATE_YMD_HMS, // yyyy/mm/dd h:m:s 24 hours
    DATE_DMY_HMS_AMPM, // dd/mm/yyyy h:m:s am/pm format
    DATE_YMD_HMS_AMPM // yyyy/mm/dd h:m:s am/pm format
};

/*
 * Enumerador das partes da semana
 */
enum WeekComponent{
    SUNDAY, // Domingo
    MONDAY, // Segunda
    TUESDAY, // Terça
    WEDNESDAY, // Quarta
    THURSDAY, // Quinta
    FRIDAY, // Sexta
    SATURDAY // Sábado
};

/*
 * Classe Calendario
 */
class Calendar {
public:

    /*
     * Construtor padrão
     */
    Calendar();

    /*
     * Destrutor
     */
    ~Calendar();

    /*
     * Configura a data do calendário para a data atual
     */
    void setDate();

    /*
     * Configura uma data específica no calendário
     *
     */
    bool setDate(int day, int month, int year);

private:
    /*
     * Estrutura de uma data
     */
    struct Date;
    /*
     * Dados referentes ao calendário
     */
    Date* data;
};


#endif /* CALENDAR_HPP_ */
