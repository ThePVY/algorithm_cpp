/*!\file
 * \brief Этот файл содержит функции, необходимые для взаимодействия с аппаратным блоком FPU.
 *
 * Copyright(C) НПП Цифровые решения, 2018
 * Copyright(C) Команда разработчиков НПП Цифровые решения
 * Все права защищены.
 *
 * Программное обеспечение, описанное в этом файле, предназначено только для 
 * демонстрационных целей, и предоставляет программистам информацию о продукции 
 * организации "Цифровые решения". Это программное обеспечение поставляется "КАК ЕСТЬ" 
 * без каких-либо гарантий, "Цифровые решения" отказываются от любых гарантий, 
 * фактических или подразумеваемых, включая все подразумеваемые гарантии товарной пригодности, 
 * пригодности для конкретной цели и сохранения прав интеллектуальной собственности. 
 * Организация "Цифровые решения" не несет никакой ответственности за использование 
 * программного обеспечения, не предоставляет лицензий или прав на патент, авторское право, 
 * или любые другие права интеллектуальной собственности, на какие-либо продукты. 
 * Организация "Цифровые решения" оставляет за собой право вносить изменения в программное 
 * обеспечение без уведомления. Организация "Цифровые решения" также не дает никаких 
 * заверений или гарантий, что это программное приложение подойдет для использования 
 * без дальнейшего тестирования или модификаций.
 *
 * Разрешение на использование, копирование, изменение и распространение этого программного 
 * обеспечения и документации предоставляется согласно условиям "Цифровых решений" и 
 * соответствующих авторских прав своей лицензии без оплаты, при условии, 
 * что это программное обеспечение используется совместно с микроконтроллерами организации
 * "Цифровые решения". Эти права должны распространяться во всех копиях этого кода.
 */

#include "chip_5023BC016.h"
#include "system.h"
#include "fpu.h"

#define PI       3.14159265358979323846                                         ///< Пи 


/**
 * @brief Сброс блока FPU.
 * @retval None.
 */
void FPU_DeInit(void)
{
    PWR_CLK_Disable(FPU_CTRL_NUM); 
    CLK_INIT_PAUSE;
    PWR_RST_Enable(FPU_CTRL_NUM);
}

/**
 * @brief Инициализация блока FPU.
 * @retval None.
 */
void FPU_Init(void)
{
    PWR_CLK_Enable(FPU_CTRL_NUM); 
    CLK_INIT_PAUSE;
    PWR_RST_Disable(FPU_CTRL_NUM);
}


/**
 * @brief Сложение двух чисел при помощи блока FPU
 * @param A: слагаемое 1
 * @param B: слагаемое 2
 * @retval сумма
 */
float FPU_ADD(float A, float B)
{
    FPU->ADD_SUB = FPU_ADD_SUB_ADD_EN;
    FPU->ADD_A = A;
    FPU->ADD_B = B;
    FPU->CONTROL = FPU_CONTROL_ADD_EN;
    return FPU->ADD_OUT;
}  

/**
 * @brief Вычитание двух чисел при помощи блока FPU
 * @param A: уменьшаемое
 * @param B: вычитаемое
 * @retval разница
 */
float FPU_SUB(float A, float B)
{
    FPU->ADD_SUB = FPU_ADD_SUB_SUB_EN;
    FPU->ADD_A = A;
    FPU->ADD_B = B;
    FPU->CONTROL = FPU_CONTROL_ADD_EN;
    return FPU->ADD_OUT;
}  

/**
 * @brief умножение двух чисел при помощи блока FPU
 * @param A: множитель 1
 * @param B: множитель 2
 * @retval произведение
 */
float FPU_MUL(float A, float B)
{
    FPU->MUL_A = A;
    FPU->MUL_B = B;
    FPU->CONTROL = FPU_CONTROL_MUL_EN;
    return FPU->MUL_OUT;
}  
    
/**
 * @brief вычисление синуса
 *
 * Для оптимизации скорости выолнения данной операции использовались как программные средства вычисления, так и средства блока FPU
 * @param A: параметр в радианах
 * @retval синус
 */
float FPU_SIN(float A)
{ 
    if ((A>-1)&&(A<1))
    {
        float T = FPU_MUL(FPU_MUL(A,A),A);                                      ///< A^3            
        float X = FPU_SUB(A,(float)(T/factorial(3)));                           ///< A - A^3/3!     
        float Y = FPU_MUL(FPU_MUL(T,A),A);                                      ///< A^5            
        float res = FPU_ADD(X,(float)(Y/factorial(5)));                         ///< A - A^3/3! +  A^5/5!
        return res;
    }
    else
    {
        float res = sinf(A);
        return res;
    }
}

/**
 * @brief вычисление косинуса
 *
 * Для оптимизации скорости выолнения данной операции использовались как программные средства вычисления, так и средства блока FPU
 * @param A: параметр в радианах
 * @retval косинус
 */
float FPU_COS(float A)
{
    if ((A>-1)&&(A<1))
    {
        float T = FPU_MUL(A,A);                                                 ///< A^2            
        float X = FPU_SUB(1,(float)(T/factorial(2)));                           ///< 1 - A^2/2!     
        float Y = FPU_MUL(FPU_MUL(T,A),A);                                      ///< A^4            
        float res = FPU_ADD(X,(float)(Y/factorial(4)));                         ///< 1 - A^2/2! +  A^4/4!
        return res;
    }
    else
    {
        float res = cosf(A);
        return res;
    }
}
            
/**
 * @brief Вычисление квадратного корня при помощи блока FPU
 * @param A: число
 * @retval квадратный корень от A 
 */
float FPU_sqrt(float A)
{
    return sqrtf(A);
}

/**
 * @brief Возведение в квадрат при помощи блока FPU
 * @param A: число
 * @retval квадрат от A 
 */
float FPU_pow2(float A)
{
    return FPU_MUL(A,A);
}

/**
 * @brief Возведение в куб при помощи блока FPU
 * @param A: число
 * @retval куб от A 
 */
float FPU_pow3(float A)
{
    return FPU_MUL(FPU_pow2(A),A);
}

/**
 * @brief вычисление тангенса
 *
 * Для оптимизации скорости выолнения данной операции использовались как программные средства вычисления, так и средства блока FPU
 * @param A: параметр в радианах
 * @retval тангенс
 */
float FPU_tg(float A)
{
    if ((A>-1)&&(A<1))
    {
        float T = FPU_pow3(A);                                                  ///< A^3            
        float X = FPU_ADD(A,T/3);                                               ///< A + A^3/3
        float Y = FPU_MUL(FPU_MUL(2*T/15,A),A);                                 ///< 2*A^5/15
        float Z = FPU_MUL(FPU_MUL(T,T),17*A/315);                               ///<17*A^7/315
        float Z1 = FPU_ADD (X,Y);
        float res = FPU_ADD(Z,Z1);      
        return res;
    }
    else
    {
        float res = tanf(A);
        return res;
    }
}

/**
 * @brief вычисление арктангенса
 *
 * Для оптимизации скорости выолнения данной операции использовались как программные средства вычисления, так и средства блока FPU
 * @param A: параметр в радианах
 * @retval арктангенс
 */
float FPU_atg(float A)
{
    if ((A>-1)&&(A<1))
    {
        float T = FPU_pow3(A);                                                  ///< A^3            
        float X = FPU_SUB(A,T/3);                                               ///< A - A^3/3     
        float Y = FPU_MUL(FPU_MUL(T,A),A/5);                                    ///< A^5            
        float Z = FPU_ADD(X,Y);                                                 ///< A - A^3/3 +  A^5
        float Z1 = FPU_MUL(FPU_MUL(Y,A),A/7);                                   ///<A^7/7
        float res = FPU_SUB(Z,Z1);
        return res;
    }
    else
    {
        float res = atanf(A);
        return res;
    }
}

/**
 * @brief вычисление арксинуса
 *
 * Для оптимизации скорости выолнения данной операции использовались как программные средства вычисления, так и средства блока FPU
 * @param A: параметр в радианах
 * @retval арксинус
 */
float FPU_ASIN(float A)
{
    if ((A>-1)&&(A<1))
    {
        float T = FPU_MUL(FPU_MUL(A,A),A);                                      ///< A^3            
        float X = FPU_ADD(A,(float)(T/6));                                      ///< A + A^3/6     
        float Y = FPU_MUL(FPU_MUL(T,A),A);                                      ///< A^5            
        float res = FPU_ADD(X,(float)(3*Y/40));                                 ///< A + A^3/6 +  3*A^5/40
        return res;
    }
    else
    {
        float res = asinf(A);
        return res;
    }
}

/**
 * @brief вычисление арккосинуса
 *
 * Для оптимизации скорости выолнения данной операции использовались как программные средства вычисления, так и средства блока FPU
 * @param A: параметр в радианах
 * @retval арккосинуса
 */
float FPU_ACOS(float A)
{
    if ((A>-1)&&(A>1))
    {
        float res = PI - FPU_ASIN(A);
        return res;

    }
    else
    {
        float res = acosf(A);
        return res;
    }
}

