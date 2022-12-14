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
    string m_sDifferentialName;                 /**<函数名*/
    string m_sFunctionExp;                      /**<函数表达式*/
    map<string,double> m_mVaraible2Value;       /**<变量名与其值*/
    FunctionParser m_Parser;                    /**<函数表达式的解析器*/
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
     * @brief parser
     * @return
     */
    bool parser();
    /**
     * @brief evaluate
     * @return
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
     * @param  dyn为y'=f(t,y)中的定值yn
     * @param  fai为t=tn,y=yn条件下的待求解yn'
     */
    void odefunc(double,const valarray<double>&,valarray<double>&);

    /**
     * @brief ODERungeKuttaOneStep 使用四阶龙格库塔法单步求解ode
     * @param dxn
     * @param dyn
     * @param dh
     * @param dynext
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
    map<string,double> m_mInputVaraible2Value;     /**<因变量与其值*/
    vector<FUNCTIONDEF> m_vFunDef;                 /**<函数*/
    map<string,int> m_mVariable2Position;          /**<因变量在因变量初始值数组dy0中的下标*/
};

#endif // ODESOLVER_H
