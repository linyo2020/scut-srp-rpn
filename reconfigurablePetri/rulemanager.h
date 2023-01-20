#ifndef RULEMANAGER_H
#define RULEMANAGER_H

#include"rule/baserule.h"
#include"petritabwidget.h"
#include"componentlist.h"
#include"defs.h"
#include<QList>
#include<QVariant>

class RuleManager
{
public:
    RuleManager();
    //仿真前使用
    void appendRule(BaseRule*);
    const QList<BaseRule*>* getRuleList();
    /**
     * @param index 规则的索引
     * @return 成功返回true，其他情况如未找到规则返回false
     */
    bool deleteRule(int index);
    /**
     * @brief 交换两个索引位置的规则，提供索引有效性验证
     * @param 两条规则的索引
     * @return 成功返回true，否则返回false
     */
    bool swapRule(int a,int b);
    /**
     * @brief 将规则移至对应索引处，空出来的位置由后面的规则依次前移补上，提供索引有效性验证
     * @param from 要引动规则的索引
     * @param to 移动目标位置的索引
     * @return 成功返回true，否则返回false
     */
    bool moveRule(int from,int to);

    //仿真时使用
    /**
     * @brief 仿真前提供初始化信息
     * @param componentList 提供网络信息，从tabWidget中获取此指针
     * @param initInfo 初始化信息
     */
    void initRule(ComponentList*componentList,RULE_INITIALIZE_INFOMATION initInfo);
    /**
     * @brief （仿真阶段使用）判断规则是否满足，并进行规则对应的操作，需先使用initRule提供仿真相关信息
     * @return 若发生重构，则返回true，否则返回false
     */
    bool applyRule();

private:
    QList<BaseRule*>ruleList;
    ComponentList* m_componentList;
};

#endif // RULEMANAGER_H
