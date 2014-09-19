/*
 * date.hpp
 *
 */

#ifndef DATE_HPP_
#define DATE_HPP_

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
 * Classe Date
 */
class Date {
public:

    /*
     * Construtor padrão
     * Configura data para a data atual
     */
    Date();

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
    Date(int day,int month, int year, int hour=0, int minute=0, int second=0);

    /*
     * Destrutor
     */
    ~Date();

    /*
     * Configura a data para a data atual
     */
    void setDate();

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
    bool setDate(int day, int month, int year, int hour=0, int minute=0, int second=0);

    /*
     * Configura data a partir dos segundos desde 1900
     * Retorna false se não conseguir (data não válida)
     *
     * time_t seconds : segundos desde 1900
     */
    bool setDate(time_t seconds);

    /*
     * Retorna a data em segundos desde 1900
     */
    time_t getDateInSeconds();

    /*
     * Retorna um componente da data (dia, mês, ano, hora ...)
     * Retorna -1 se não conseguir retornar o solicitado
     *
     * DateComponent dateComponent : enumerador que indica a parte da
     * data a ser retornada (veja o enumerador neste header file)
     *
     * Obs: alguns retornos específicos:
     * dia do mês: 1 - 31
     * dia do ano: 1 - 365
     * dia da semana: 0 (domingo) - 6(sábado)
     * mês: 1 - 12
     * hora: 0 - 23
     * hora_ampm: 1-12
     * outros: formatos já esperados
     */
    int getDateComponent(DateComponent dateComponent);

    /*
     * Gera uma string e coloca em dateString
     *
     * DateFormat dateFormat : indica qual o formato da string a ser utilizado
     *            (veja o enumerador DateFormat neste header file)
     * string& dateString : string a ser preenchida
     * bool showWeek : opção que indica se o nome do dia da semana é incluído
     *                 (por padrão sim)
     */
    void getStringDate(DateFormat dateFormat, string& dateString, bool showWeek=true);

    /*
     * Gera uma string do dia da semana e coloca em weekString
     *
     * string& weekString : string a ser preenchida
     */
    void getStringWeek(string& weekString);

    /*
     * Adiciona (ou subtrai) um valor em uma componente da data
     * Retorna false se não conseguir
     *
     * DateComponent dateComponent : parte da data a ser adicionada (ou subtraída)
     * int value : valor a ser adicionado (ou subtraído)
     * bool add : se deverá adicionar ou subtrair (adiciona por padrão)
     */
    bool addDateComponent(DateComponent dateComponent, int value, bool add=true);

    /*
     * Imprime data no prompt
     *
     * DateFormat dateFormat : enumerador que indica o formato da string
     *          a ser utilizado (veja o enumerador neste header file)
     * bool showWeek : se o nome do dia da semana deve ser mostrado
     *                  (sim por padrão)
     */
    void printDate(DateFormat dateFormat, bool showWeek=true);

    /*
     * Imprime no prompt o nome do dia da semana
     */
    void printWeekName();

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
    bool validateDate(int day, int month, int year, int hour=0, int minute=0, int second=0);

private:
    /*
     * Estrutura de uma data
     */
    struct DateStruct;
    /*
     * Dados referentes à data
     */
    DateStruct* data;
};


#endif /* DATE_HPP_ */
