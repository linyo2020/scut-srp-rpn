#ifndef ODESOLVER_H
#define ODESOLVER_H
#include <iostream>
#include <vector>
//#include "stdafx.h"
#include "fparser.hh"
#include <map>
#include <valarray>
#include <QString>
#include <QDebug>
using namespace std;


struct FUNCTIONDEF
{
    string m_sDifferentialName;                 /**< 函数名*/
    string m_sFunctionExp;                      /**< 函数表达式*/
    map<string,double> m_mVaraible2Value;       /**< 变量名与其值*/
    FunctionParser m_Parser;                    /**< 函数表达式的解析器*/
};
/**
 * @brief The ODEsolver class
 */
class ODEsolver
{
public:
    ODEsolver();
    ~ODEsolver();
    /**
     * @brief parser 对函数表达式中的变量进行解析
     * @return       返回布尔变量，true代表变量名合法，false表示变量名非法
     */
    bool parser();
    /**
     * @brief evaluate  计算y(dx+dh)的值
     * @param dx        dx为y'=f(t,y)中的定值tn
     * @param dh        步长
     * @param state     是否检查负数
     * @attention       计算得到的结果会刷新该类的变量-值的映射表；可以将yn=0,ynext<0的情况修正为yn=ynext=0
     * @return          返回存储y(dx+dh)数值的数组
     */
    vector<double> evaluate(double,double,bool);
    /**
     * @brief setVector
     */
    void setVector(vector<FUNCTIONDEF>&);
    /**
     * @brief setMap
     */
    void setMap(map<string,double>&);
    /**
     * @brief 使用tn,yn计算ode方程y'=f(t,y)
     * @param  dx为y'=f(t,y)中的定值tn
     * @param  dyn为y'=f(t,y)中的定值yn，不可修改
     * @param  fai为t=tn,y=yn条件下的待求解yn'，传入用来记录计算结果
     */
    void odefunc(double,const valarray<double>&,valarray<double>&);

    /**
     * @brief ODERungeKuttaOneStep 使用四阶龙格库塔法单步求解ode
     * @param dxn                   dxn为y'=f(t,y)中的定值tn
     * @param dyn                   dyn为y'=f(t,y)中的定值yn，不可修改
     * @param dh                    dh为y'=f(t,y)中的时间间隔h
     * @param dynext                dynext为下一个值y(n+1)，传入用来记录计算结果
     */
    void ODERungeKuttaOneStep(double,const valarray<double>&,double,valarray<double>&);

    map<string, double>* GetInputVaraible2Value()
	{
		return &m_mInputVaraible2Value;
	}
    map<string,double> Getm_mInputVaraible2Value()
    {
        return m_mInputVaraible2Value;
    }
    vector<FUNCTIONDEF> Getm_vFunDef()
    {
        return m_vFunDef;
    }

private:
    map<string,double> m_mInputVaraible2Value;     /**< 变量与其值*/
    vector<FUNCTIONDEF> m_vFunDef;                 /**< 函数集合*/
    map<string,int> m_mVariable2Position;          /**< 变量在变量初始值数组dy0中的下标*/
};

#endif // ODESOLVER_H
