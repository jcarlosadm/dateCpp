/**
 * \file date.hpp
 * Módulo que cria e manipula uma data
 */

#ifndef DATE_HPP_
#define DATE_HPP_

#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <new>

using std::cout;
using std::endl;
using std::string;
using std::ostringstream;

namespace dateCpp{

/**
 * Enumerador das partes de uma data
 */
enum DateComponent{
    MDAY, ///< dia do mês
    YDAY, ///< dia do ano
    WDAY, ///< dia da semana
    MONTH, ///< mês
    YEAR, ///< ano
    HOUR, ///< hora (formato 24 horas)
    HOUR_AMPM, ///< hora (formato am/pm)
    MINUTE, ///< minutos
    SECOND ///< segundos
};

/**
 * Enumerador dos formatos da data
 */
enum DateFormat{
    DATE_DMY, ///< dd/mm/yyyy
    DATE_YMD, ///< yyyy/mm/dd
    DATE_HMS, ///< h:m:s 24 hours
    DATE_HMS_AMPM, ///< h:m:s am/pm format
    DATE_DMY_HMS, ///< dd/mm/yyyy h:m:s 24 hours
    DATE_YMD_HMS, ///< yyyy/mm/dd h:m:s 24 hours
    DATE_DMY_HMS_AMPM, ///< dd/mm/yyyy h:m:s am/pm format
    DATE_YMD_HMS_AMPM ///< yyyy/mm/dd h:m:s am/pm format
};

/**
 * Enumerador das partes da semana
 */
enum WeekComponent{
    SUNDAY, ///< Domingo
    MONDAY, ///< Segunda
    TUESDAY, ///< Terça
    WEDNESDAY, ///< Quarta
    THURSDAY, ///< Quinta
    FRIDAY, ///< Sexta
    SATURDAY ///< Sábado
};

/**
 * Definição da string AM
 */
#define AM "am"
/**
 * Definição da string PM
 */
#define PM "pm"

/**
 * Classe que cria objetos Date
 */
class Date {
public:

    /**
     * Construtor padrão<BR>
     * Configura data para a data atual
     */
    Date();

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
    Date(int day,int month, int year, int hour=0, int minute=0, int second=0);

    /**
     * Destrutor
     */
    ~Date();

    /**
     * Configura a data para a data atual
     */
    void setDate();

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
    bool setDate(int day, int month, int year, int hour=0, int minute=0, int second=0);

    /**
     * Configura data a partir dos segundos desde 1900
     * \return false se não conseguir (data não válida)
     * \param seconds Segundos desde 1900
     */
    bool setDate(time_t seconds);

    /**
     * Retorna a data em segundos desde 1900
     * \return Segundos desde 1900
     */
    time_t getDateInSeconds();

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
    int getDateComponent(DateComponent dateComponent);

    /**
     * Gera uma string e coloca em dateString
     * \param dateFormat Indica qual o formato da string a ser utilizado
     *            (veja o enumerador DateFormat neste header file)
     * \param dateString String a ser preenchida
     * \param showWeek Opção que indica se o nome do dia da semana é incluído
     *                 (por padrão sim)
     */
    void getStringDate(DateFormat dateFormat, string& dateString, bool showWeek=true);

    /**
     * Gera uma string do dia da semana e coloca em weekString
     * \param weekString String a ser preenchida
     */
    void getStringWeek(string& weekString);

    /**
     * Adiciona (ou subtrai) um valor em uma componente da data
     * \return false se não conseguir
     * \param dateComponent Parte da data a ser adicionada (ou subtraída)
     * \param value Valor a ser adicionado (ou subtraído)
     * \param add Se deverá adicionar ou subtrair (adiciona por padrão)
     */
    bool addDateComponent(DateComponent dateComponent, int value, bool add=true);

    /**
     * Imprime data no prompt
     * \param dateFormat Enumerador que indica o formato da string
     *          a ser utilizado (veja o enumerador neste header file)
     * \param showWeek Se o nome do dia da semana deve ser mostrado
     *                  (sim por padrão)
     */
    void printDate(DateFormat dateFormat, bool showWeek=true);

    /**
     * Imprime no prompt o nome do dia da semana
     */
    void printWeekName();

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
    bool validateDate(int day, int month, int year, int hour=0, int minute=0, int second=0);

private:
    /**
     * Estrutura de uma data
     */
    struct DateStruct;
    
    /**
     * Dados referentes à data
     */
    DateStruct* data;
};

} /** namespace dateCpp */

#endif /* DATE_HPP_ */
