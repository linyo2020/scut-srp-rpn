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
        qDebug()<<QString::fromStdString(m_vFunDef[i].m_sFunctionExp)<<" is the function expression of ";
        int res = fparser1.ParseAndDeduceVariables(sss, vReturnVars);
        if(res >= 0)
        {
            std::cout << std::string(res + 7, ' ') << "^\n"
                << fparser1.ErrorMsg() << "\n\n";
            return false;
        }
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
        m_vFunDef[i].m_mVaraible2Value.clear();
        for(unsigned j=0;j<vReturnVars.size();j++)
        {
            m_vFunDef[i].m_mVaraible2Value[vReturnVars[j]]=0.0;
        }
    }
    return true;
}
/*
vector<double> ODEsolver::evalulate(double dx,double dh,bool state)
{
    for (unsigned i = 0; i < m_vFunDef.size(); i++)//对于每个函数
    {
        m_mVariable2Position[m_vFunDef[i].m_sDifferentialName]=i;
        std::map<std::string, double>::iterator itMap;//由string得到double
        for (itMap = m_vFunDef[i].m_mVaraible2Value.begin(); itMap != m_vFunDef[i].m_mVaraible2Value.end(); itMap++)
        {//对于每个变量
            if (m_mInputVaraible2Value.find(itMap->first) != m_mInputVaraible2Value.end())//如果值不相对应
            {//赋值
                double l_dvalue = m_mInputVaraible2Value.find(itMap->first)->second;
                itMap->second=l_dvalue;
            }
        }
    }
    double *dy0=new double[m_vFunDef.size()];//初值数组
    for(unsigned i=0;i<m_vFunDef.size();i++)
    {
        if(m_mInputVaraible2Value[m_vFunDef[i].m_sDifferentialName]<0&&state==true)
            dy0[i]=0;
        else dy0[i]=m_mInputVaraible2Value[m_vFunDef[i].m_sDifferentialName];
    }
    std::valarray<double> darrayn(dy0,m_vFunDef.size());//当前的值
    std::valarray<double> darraynext(0.0,m_vFunDef.size()); //下一步的值,最好初始化
    vector<double> vReturn;
    ODERungeKuttaOneStep(dx,darrayn,dh,darraynext);
    for(unsigned i=0;i<m_vFunDef.size();i++)
    {
        vReturn.push_back(darraynext[i]);
        m_mInputVaraible2Value[m_vFunDef[i].m_sDifferentialName]=darraynext[i];
    }
    delete dy0;
    return vReturn;
}*/


vector<double> ODEsolver::evaluate(double dx,double dh,bool state)
{
    //vector<int>list;//新增
    double *dy0=new double[m_vFunDef.size()];//初值数组
    for (unsigned i = 0; i < m_vFunDef.size(); i++)//对于每个函数
    {
        m_mVariable2Position[m_vFunDef[i].m_sDifferentialName]=int(i);
        if(m_mInputVaraible2Value[m_vFunDef[i].m_sDifferentialName]<0.00000000001&&state==true)
        //if(m_mInputVaraible2Value[m_vFunDef[i].m_sDifferentialName]<=0.000000000001&&state==true)
        {
            dy0[i]=0;
            //list.push_back(i);//新增
        }
        else dy0[i]=m_mInputVaraible2Value[m_vFunDef[i].m_sDifferentialName];
        //qDebug()<<QString::fromStdString(m_vFunDef[i].m_sDifferentialName)<<" value "<<dy0[i];
    }
    std::valarray<double> darrayn(dy0,m_vFunDef.size());//当前的值
    std::valarray<double> darraynext(0.0,m_vFunDef.size()); //下一步的值,最好初始化
    vector<double> vReturn;
    ODERungeKuttaOneStep(dx,darrayn,dh,darraynext);
    //_______________________________________

    if(state==true)
    {
        int flag=1;
        vector<int> record;
        for(unsigned i=0;i<m_vFunDef.size();i++)
        {
            if(darrayn[i]==0&&darraynext[i]<0)
            {
                flag=0;
                record.push_back(int(i));
            }
        }
        if(flag==0)
        {
            //qDebug()<<"NEW ODESOLVER";
            vector<FUNCTIONDEF>temp_vector=Getm_vFunDef();
            for(unsigned i=0;i<record.size();i++)
            {
                QString temp_qstring="0";
                temp_vector[unsigned(record[i])].m_sFunctionExp=temp_qstring.toStdString();
            }
            map<string,double>temp_map=Getm_mInputVaraible2Value();
            ODEsolver ode_temp;
            ode_temp.setMap(temp_map);
            ode_temp.setVector(temp_vector);
            ode_temp.parser();
            double *dy=new double[m_vFunDef.size()];
            vector<double>vector_temp=ode_temp.evaluate(dx,dh,state);
            for(unsigned i=0;i<m_vFunDef.size();i++)
            {
                dy[i]=vector_temp[i];
            }
            std::valarray<double> valarray_temp(dy,m_vFunDef.size());
            darraynext=valarray_temp;
            delete[] dy;
        }
    }

    //_______________________________________
    for(unsigned i=0;i<m_vFunDef.size();i++)
    {
        vReturn.push_back(darraynext[i]);
        m_mInputVaraible2Value[m_vFunDef[i].m_sDifferentialName]=darraynext[i];
        //qDebug()<<QString::fromStdString(m_vFunDef[i].m_sDifferentialName)<<" values "<<vReturn[i];
    }
    /*
    for(int i=0;i<list.size();i++)//新增
    {
        if(vReturn[list[i]]<0)
        {
            qDebug()<<"Change "<<QString::fromStdString(m_vFunDef[i].m_sDifferentialName)<<"  "<<vReturn[list[i]];
            vReturn[list[i]]=0;
            m_mInputVaraible2Value[m_vFunDef[list[i]].m_sDifferentialName]=0;
        }
    }*/
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
    for(int i=0;i<n;i++)
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
        for(itMap=m_vFunDef[i].m_mVaraible2Value.begin();itMap!=m_vFunDef[i].m_mVaraible2Value.end();itMap++)
        {
            vals[k]=dyn[m_mVariable2Position[itMap->first]];
            k++;
        }
        fai[i]=m_vFunDef[i].m_Parser.Eval(vals);
        delete[] vals;
    }
}
