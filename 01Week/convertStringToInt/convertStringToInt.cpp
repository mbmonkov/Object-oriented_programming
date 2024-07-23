#include <iostream> 


bool isDigit(char ch)
{
    return ch >= '0' && ch <= '9';  
}


int convertCharToNumber(char ch)
{
    return ch - '0';  // Връща числото, което съответства на символа
}

// Дефиниране на изброим тип за кодове на грешки
enum class ErrorCode
{
    OK,                  // Няма грешка
    NullptrGiven,        // Подаден е нулев указател
    WrongCharInString,   // Невалиден символ в низа
    EmptyString          // Празен низ
};

// Структура за резултат от преобразуването
struct ConvertResult
{
    ErrorCode errCode;  // Код на грешката
    unsigned result;    // Резултат от преобразуването
};

// Функция за преобразуване на низ към число
ConvertResult convertStringToNumber(const char* str)
{
    if (!str)  // Проверка дали указателят е нулев
        return { ErrorCode::NullptrGiven, 0 };  // Връщане на грешка за нулев указател

    unsigned num = 0;  // Променлива за съхраняване на резултата
    if (!*str)  // Проверка дали низът е празен
        return { ErrorCode::EmptyString, num };  // Връщане на грешка за празен низ

    while (*str)  // Докато не се достигне края на низа
    {
        if (!isDigit(*str))  // Проверка дали текущият символ е цифра
            return { ErrorCode::WrongCharInString, 0 };  // Връщане на грешка за невалиден символ
        (num *= 10) += convertCharToNumber(*str);  // Преобразуване на символа и добавяне към числото
        str++;  // Преминаване към следващия символ в низа
    }
    return { ErrorCode::OK, num };  // Връщане на резултата и код за успешно преобразуване
}


int main()
{
    ConvertResult res = convertStringToNumber("12343");  

    if (res.errCode == ErrorCode::OK)  // Проверка дали преобразуването е успешно
    {
        std::cout << res.result << std::endl;
    }
    else
    {
        std::cout << "Error!" << std::endl;  
    }
}
