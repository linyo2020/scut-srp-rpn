//#ifndef GRAPHGENERATOR_H
//#define GRAPHGENERATOR_H

//#include <QGraphicsScene>

//#include "defs.h"
////#include "boost_graph.h"

//class GraphGenerator
//{
// public:

//    explicit GraphGenerator(Marking& init_mark, QMap<QString, int> &places_cap,
//                   QList<TRANS_RELATION> &relations);

//    //Graph generate_graph();
//    bool isTransitionEnabled(const TRANS_RELATION &t, const Marking &M);
//    bool check_pre_set(const TRANS_RELATION &t, const Marking &M);
//    bool check_post_set(const TRANS_RELATION &t, const Marking &M);
//    Marking fireTransition (const TRANS_RELATION &t, const Marking &M);
//    void fire_pre_set (const TRANS_RELATION &t, Marking& M);
//    void fire_post_set (const TRANS_RELATION &t, Marking& M);

//    //void addOmegas(g_node_descriptor M1_desc, Marking &M2, g_node_descriptor start, Graph &tree);
//    bool M2_covers_M(const Marking &M2, const Marking &M) const;
//    //QList<g_node_descriptor> getPath(g_node_descriptor src, g_node_descriptor targ, const Graph& tree);

// private:

//    Marking initialMarking;
//    QMap<QString, int> places;
//    QList<TRANS_RELATION> pt_relations;
//};

//#endif // GRAPHGENERATOR_H

