#include "disjsets.h"
#include "QDebug"

DisjSets::DisjSets(QList<CONNECTOR_ATTR>connectorAttrList)
{
    int l_num=0;
    int root1,root2;
    int l_length=connectorAttrList.size();
    m_root.fill(-1,l_length*2);
    QString l_source,l_target;
    //遍历connector列表
    for(int i=0;i<l_length;i++)
    {
        //记录一个connector的库所信息
        l_source=connectorAttrList[i].source;
        l_target=connectorAttrList[i].target;
        if(!m_placeID2Index.contains(l_source))
        {
            m_placeID2Index[l_source]=l_num;
            l_num++;
        }
        if(!m_placeID2Index.contains(l_target))
        {
            m_placeID2Index[l_target]=l_num;
            l_num++;
        }
        //合并两个库所所在的集合
        root1=find(m_placeID2Index[l_source]);
        root2=find(m_placeID2Index[l_target]);
        if(root1!=root2)
            unionSets(root1,root2);
    }

}

int DisjSets::find(QString placeID)
{
    if(m_placeID2Index.contains(placeID))
       qDebug()<<placeID<<"is not in the disjSet";
    int l_index=m_placeID2Index[placeID];
    return find(l_index);
}

int DisjSets::find(int x)
{
    if(m_root[x]<0)
        return x;
    else {
        return m_root[x]=find(m_root[x]);
    }
}

void DisjSets::unionSets(int root1,int root2)
{
    if(m_root[root2]<m_root[root1])  //root2更深
        m_root[root1]=root2;         //使root2为新的根
    else {
        {
            if(m_root[root1]==m_root[root2])
                --m_root[root1];      //如果相同，则更新高度
            m_root[root2]=root1;      //使root1为新的根
        }
    }
}

QList<QString> DisjSets::getPlaceIDInDisjSets()
{
    return m_placeID2Index.keys();
}
