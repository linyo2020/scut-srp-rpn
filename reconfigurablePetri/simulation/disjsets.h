#ifndef DISJSETS_H
#define DISJSETS_H
#include "defs.h"
#include<QList>
#include<QVector>
#include<QMap>

class DisjSets
{
public:
    explicit DisjSets(QList<CONNECTOR_ATTR>);
    /**
     * @brief find 利用路径压缩执行一次find
     * 为简单起见，忽略差错检验
     * 返回包含QString的集合
     * @return
     */
    int find(QString);
    /**
     * @brief find 利用路径压缩执行的嵌套find
     * @return
     */
    int find(int);
    /**
     * @brief unionSets 按高度（秩）合并
     * @param root1
     * @param root2
     */
    void unionSets(int root1,int root2);
    bool isEmpty();
    QList<QString> getPlaceIDInDisjSets();
private:
    QVector<int> m_root;
    QMap<QString,int>m_placeID2Index;
};

#endif // DISJSETS_H
