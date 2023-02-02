#include "ODEsolver.h"
ODEsolver::ODEsolver()
{
    m_mInputVaraible2Value.clear();
    m_vFunDef.clear();
    m_mVariable2Position.clear();
}
ODEsolver::~ODEsolver()
{

}
void ODEsolver::setMap(map<string, double> &input)
{
    m_mInputVaraible2Value=input;
}


void ODEsolver::setVector(vector<FUNCTIONDEF> &input)
{
    m_vFunDef=input;
}

bool ODEsolver::parser()
{
    for (unsigned i = 0; i < m_vFunDef.size(); i++)
    {
        FunctionParser fparser1;
        std::vector<std::string> vReturnVars;
        std::string sss = m_vFunDef[i].m_sFunctionExp;
//        qDebug()<<QString::fromStdString(sss)<<" is the function expression of "<<QString::fromStdString(m_vFunDef[i].m_sDifferentialName);
        //将变量名从函数表达式中提取出来
        int res = fparser1.ParseAndDeduceVariables(sss, vReturnVars);
        if(res >= 0)
        {
            std::cout << std::string(res + 7, ' ') << "^\n"
                << fparser1.ErrorMsg() << "\n\n";
            return false;
        }
        //检测函数表达式中的变量是否合法（当速率不使用质量作用定律时，速率函数表达式（可能不合法）被直接加入到函数表达式中）
        for(unsigned j=0;j<vReturnVars.size();j++)
        {
            int flag=0;
            for(unsigned k=0;k<m_vFunDef.size();k++)
            {
                if(m_vFunDef[k].m_sDifferentialName==vReturnVars[j])
                {
                    flag=1;
                    break;
                }
            }
            if(flag==0)
                return false;
        }
        m_vFunDef[i].m_Parser = fparser1;
        //将函数结构体中的映射表初始化
        m_vFunDef[i].m_mVaraible2Value.clear();
        for(unsigned j=0;j<vReturnVars.size();j++)
        {
            m_vFunDef[i].m_mVaraible2Value[vReturnVars[j]]=0.0;
        }
    }
    return true;
}

vector<double> ODEsolver::evaluate(double dx,double dh,bool state)
{
    //ode的初值数组，初始化
    double *dy0=new double[m_vFunDef.size()];
    for (unsigned i = 0; i < m_vFunDef.size(); i++)
    {
        m_mVariable2Position[m_vFunDef[i].m_sDifferentialName]=int(i);
        if(m_mInputVaraible2Value[m_vFunDef[i].m_sDifferentialName]<0.00000000001&&state==true)
        //if(m_mInputVaraible2Value[m_vFunDef[i].m_sDifferentialName]<=0.000000000001&&state==true)
        {
            dy0[i]=0;
        }
        else dy0[i]=m_mInputVaraible2Value[m_vFunDef[i].m_sDifferentialName];
        //qDebug()<<QString::fromStdString(m_vFunDef[i].m_sDifferentialName)<<" value "<<dy0[i];
    }
    //当前的值，以初值初始化
    std::valarray<double> darrayn(dy0,m_vFunDef.size());
    //下一步的值，全零初始化
    std::valarray<double> darraynext(0.0,m_vFunDef.size());
    //函数返回的数组
    vector<double> vReturn;
    //使用龙格库塔法进行计算
    ODERungeKuttaOneStep(dx,darrayn,dh,darraynext);

    //如果仿真需要检查负值
    if(state==true)
    {
        int flag=1;
        vector<int> record;
        //寻找出现零点向下的库所并记录
        for(unsigned i=0;i<m_vFunDef.size();i++)
        {
            //注意浮点数比较不要用!=和==
            if(abs(darrayn[i])<=1e-15&&darraynext[i]<0)
            {
                flag=0;
                record.push_back(int(i));
            }
        }
        //如果出现向下的零点
        if(flag==0)
        {
            //qDebug()<<"NEW ODESOLVER";
            vector<FUNCTIONDEF>temp_vector=Getm_vFunDef();
            //将出现零点向下的库所对应的函数表达式置零
            for(unsigned i=0;i<record.size();i++)
            {
                QString temp_qstring="0";
                temp_vector[unsigned(record[i])].m_sFunctionExp=temp_qstring.toStdString();
            }
            //使用更新后的函数表达式创建新的ode
            map<string,double>temp_map=Getm_mInputVaraible2Value();
            ODEsolver ode_temp;
            ode_temp.setMap(temp_map);
            ode_temp.setVector(temp_vector);
            ode_temp.parser();
            //用来保存新的计算结果
            double *dy=new double[m_vFunDef.size()];
            //重新计算
            vector<double>vector_temp=ode_temp.evaluate(dx,dh,state);
            for(unsigned i=0;i<m_vFunDef.size();i++)
            {
                dy[i]=vector_temp[i];
            }
            //更新计算结果
            std::valarray<double> valarray_temp(dy,m_vFunDef.size());
            darraynext=valarray_temp;
            delete[] dy;
        }
    }

    //更新ode的映射表
    for(unsigned i=0;i<m_vFunDef.size();i++)
    {
        vReturn.push_back(darraynext[i]);
        m_mInputVaraible2Value[m_vFunDef[i].m_sDifferentialName]=darraynext[i];
        //qDebug()<<QString::fromStdString(m_vFunDef[i].m_sDifferentialName)<<" values "<<vReturn[i];
    }
    delete[] dy0;
    return vReturn;
}


void ODEsolver::ODERungeKuttaOneStep(double dxn,const std::valarray<double>& dyn,double dh,std::valarray<double>& dynext)
{
    //微分方程组中方程的个数，同时是初值y(n)和下一步值y(n+1)的长度
    size_t n = dyn.size();

    if (n != dynext.size())
    {
        //下一步的值y(n+1)与y(n)长度相等
        dynext.resize(n, 0.0);
    }
    std::valarray<double> K1(0.0, n), K2(0.0, n), K3(0.0, n), K4(0.0, n);
    odefunc(dxn, dyn, K1);               //求解K1
    odefunc(dxn+dh/2, dyn+dh/2*K1, K2);  //求解K2
    odefunc(dxn+dh/2, dyn+dh/2*K2, K3);  //求解K3
    odefunc(dxn+dh, dyn+dh*K3, K4);      //求解K4
    std::valarray<double> l_K2(0.0, n), l_K3(0.0, n);
    for(unsigned i=0;i<n;i++)
    {
        //归一化
        l_K2[i]=2*K2[i];
        l_K3[i]=2*K3[i];
    }
    //下一步的值y(n+1)=y(n)+1/6*h*(K1+2*K2+2*K3+K4)
    dynext = dyn + (K1 + l_K2 + l_K3 + K4)*dh/6.0;
}

void ODEsolver::odefunc(double dx, const std::valarray<double>& dyn, std::valarray<double>& fai)
{
    //函数的数量
    int l_iSize=m_vFunDef.size();

    for(int i=0;i<l_iSize;i++)
    {
        //当前函数所含变量数
        int n=m_vFunDef[i].m_mVaraible2Value.size();

        double  *vals = new double[n];
        std::map<std::string, double>::iterator itMap;
        int k=0;
        //将变量目前对应的值有序地保存在vals数组中
        for(itMap=m_vFunDef[i].m_mVaraible2Value.begin();itMap!=m_vFunDef[i].m_mVaraible2Value.end();itMap++)
        {
            //注意：m_mVaraible2Value中的库所名称顺序与dyn中的库所名称顺序可能不同
            vals[k]=dyn[m_mVariable2Position[itMap->first]];
            k++;
        }
        //通过parser识别函数表达式中的变量并把值代入到其中计算出函数值
        fai[i]=m_vFunDef[i].m_Parser.Eval(vals);
        delete[] vals;
    }
}
