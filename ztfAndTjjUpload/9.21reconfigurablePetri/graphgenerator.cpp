//#include "graphgenerator.h"

//GraphGenerator::GraphGenerator(Marking& init_mark,
//QMap<QString, int> &places_cap, QList<TRANS_RELATION> &relations)
//{
//  initialMarking = init_mark;
//  places = places_cap;
//  pt_relations = relations;
//}

//Graph GraphGenerator::generate_graph ()
//{
// Graph graph, tree;
// g_node_descriptor root_desc, src, tree_root_desc;

// nodes_markings_map graph_nodes = get(vertex_marking, graph);
// edges_names_map graph_edges = get(boost::edge_name, graph);
// nodes_markings_map tree_nodes = get(vertex_marking, tree);
// edges_names_map tree_edges = get(boost::edge_name, tree);

// //![0] Add the initial marking as a vertex(node)
// // to the graph then the tree
// root_desc = add_vertex(graph);
// graph_nodes[root_desc] = initialMarking;
// tree_root_desc = add_vertex(tree);
// tree_nodes[tree_root_desc] = initialMarking;

// //![1] Add the initial marking to work set
// QMap<g_node_descriptor, Marking> work;
// work[tree_root_desc] = initialMarking;

// // main loop
// while(!work.isEmpty())
// {
//     //![2] select a marking from work
//     QMap<g_node_descriptor, Marking >::iterator itr = work.begin();
//     g_node_descriptor M1_tree_desc = itr.key();
//     Marking M1 = itr.value();
//     work.remove(M1_tree_desc);

//            //![3] breadth first search to get M1's descriptor in the graph!
//            graph_bfs_visitor vis(M1, graph);
//            try{breadth_first_search(graph, root_desc, visitor(vis));}
//            catch (g_node_descriptor d){src = d;}


//     foreach(TRANS_RELATION t, pt_relations)
//     {
//       if(isTransitionEnabled(t, M1))
//       {
//     //![4] fire transition and get the new marking M2
//     // M1 -- t ---> M2
//     Marking M2 = fireTransition(t, M1);

//     //![5] check coverability and add omega
//     // M2 ----> M2(w)
//     addOmegas(M1_tree_desc, M2, tree_root_desc, tree);

//     //![5] breadth first search to verify if M2 exist in the graph
//     graph_bfs_visitor vis(M2, graph);
//     try{breadth_first_search(graph, root_desc, visitor(vis));}
//         // Exception: M2 exist with descriptor targ
//         catch (g_node_descriptor targ)
//                {
//                    // add vertex to tree
//                    g_node_descriptor tree_targ = add_vertex(tree);
//                    tree_nodes[tree_targ] = M2;
//                    // add edge to tree
//                    g_edge_descriptor e_tree = (add_edge(M1_tree_desc, tree_targ, tree)).first;
//                    tree_edges[e_tree] = t.name.toStdString();
//                    // add edge to graph and dont add a new vertex
//                    g_edge_descriptor e = (add_edge(src, targ, graph)).first;
//                    graph_edges[e] = t.name.toStdString();
//                    // jump to the next iteration of the foreach loop
//                    continue;
//                 }

//          // M2 does not exist in the graph
//          // add vertex to tree
//          g_node_descriptor tree_targ = add_vertex(tree);
//          tree_nodes[tree_targ] = M2;
//          // add edge to tree
//          g_edge_descriptor e_tree = (add_edge(M1_tree_desc, tree_targ, tree)).first;
//          tree_edges[e_tree] = t.name.toStdString();
//          // add M2 to the graph
//          g_node_descriptor targ = add_vertex(graph);
//          graph_nodes[targ] = M2;
//          // add edge M1 --> M2
//          g_edge_descriptor e = (add_edge(src, targ, graph)).first;
//          graph_edges[e] = t.name.toStdString();
//          // UPDATE THE WORK SET
//          work[tree_targ] = M2;
//        } // if
//     } //foreach
// } //while

// //![1] write the graph object into an output stream in graphviz dot format
// std::ofstream file("graph.dot");
// write_graphviz(file, graph, boost::default_writer(),
//                make_label_writer(graph_edges));
// file.close();

// //![2]
// return graph;
//}

///* check if M enable t */
//bool GraphGenerator::isTransitionEnabled(const TRANS_RELATION &t, const Marking &M)
//{
//   //![0] check pre-set
//   if(!check_pre_set(t,M))
//    return false;

//   //![1] check post-set
//   if(!check_post_set(t,M))
//    return false;

// return true;
//}

//bool GraphGenerator::check_pre_set(const TRANS_RELATION &t, const Marking &M)
//{
//   QMapIterator<QString, QString> p1(t.preSet);
//   while (p1.hasNext())
//   {
//     p1.next();
//     QString w = p1.value();
//     double token = M.value(p1.key());
//     if(QString::number(token) < w)
//        return false;
//   }

// return true;
//}

//bool GraphGenerator::check_post_set(const TRANS_RELATION &t, const Marking &M)
//{
//   QMapIterator<QString, QString> p2(t.postSet);
//   while (p2.hasNext())
//   {
//     p2.next();
//     QString w = p2.value();
//     int c = places.value(p2.key());
//     double token = M.value(p2.key());

//     // c = omega, means that the place capacity is unbounded
//     //if(((w + token) > c) &&(c != omega))
//         //return false;
//   }

// return true;
//}

///* M ---t---> M2 */
//Marking GraphGenerator::fireTransition (const TRANS_RELATION &t, const Marking& M)
//{
//   Marking M2 = M;

//   //![0] fire pre-set
//   fire_pre_set(t, M2);
//   //![1] fire post-set
//   fire_post_set(t, M2);

//   return M2;
//}

//void GraphGenerator::fire_pre_set (const TRANS_RELATION &t, Marking& M)
//{
//   QMapIterator<QString, QString> prePlace(t.preSet);
//   while (prePlace.hasNext())
//   {
//     prePlace.next();
//     //QString w = prePlace.value();
//     //int token = M.value(prePlace.key());

//     //if(token != omega)
//        //M[prePlace.key()] = token - w;

//     //this place update for weight from double to QString by syx 8.15
//   }

//}

//void GraphGenerator::fire_post_set (const TRANS_RELATION &t, Marking& M)
//{
//   QMapIterator<QString, QString> postPlace(t.postSet);
//   while (postPlace.hasNext())
//   {
//     postPlace.next();
//     //QString w = postPlace.value();
//     //int token = M[postPlace.key()];

//     //if(token != omega)
//        //M[postPlace.key()] = w + M.value(postPlace.key());
//     //this place update for weight from double to QString by syx 8.15
//   }

//}

///* AddOmegas sub-routine */
//void GraphGenerator::addOmegas(g_node_descriptor M1_desc, Marking &M2,
//                           g_node_descriptor start, Graph &tree)
//{
// QList<g_node_descriptor> m1_descriptors;
// nodes_markings_map tree_nodes_map = get(vertex_marking, tree);
// Marking M1 = tree_nodes_map[M1_desc];

//   // search for all M1 in the tree
//   tree_bfs_visitor vis(M1, tree_nodes_map, m1_descriptors);
//   breadth_first_search(tree, start, visitor(vis));

// foreach(g_node_descriptor desc, m1_descriptors)
// {
//   QList<g_node_descriptor> path_desc = getPath(start, desc, tree);
//   foreach (g_node_descriptor d, path_desc)
//   {
//     Marking M = tree_nodes_map[d];
//     if(M2_covers_M(M2, M))
//     {
//       QMapIterator<QString, double> p(M2);
//       while (p.hasNext())
//       {
//     p.next();
//     if((p.value() - M[p.key()]) != 0)
//        M2[p.key()] = omega;
//       }
//       break;
//     }
//   }
// }
//}

//// get the vertices in the path from M0 (src) to M1 (targ)
//QList<g_node_descriptor> GraphGenerator::getPath(
//    g_node_descriptor src, g_node_descriptor targ, const Graph& tree)
//{
//  QList<g_node_descriptor> path;

//  //add M1's descriptor
//  path << targ;

//  std::pair<in_edge_itr, in_edge_itr> inp;

//  // M1 always has in_edges
//  inp = in_edges(targ, tree);

//  while(in_degree(targ, tree) > 0) // while the current node has in_edges
//  {
//    g_edge_descriptor e = *inp.first;
//    targ = source(e, tree);
//    path << targ;
//    //go to the upper nodes till M0
//    inp = in_edges(targ, tree);
//  }//M0 has no in_edges because it's the root node of the tree

//  // add the root node descriptor to the path
//  path << src;

//  return path;
//}

//// check if M2 cover M <=> for each place p : M2(p) > M(p)
//bool GraphGenerator::M2_covers_M(const Marking &M2, const Marking &M) const
//{
//    //![0] M2 != M
//    if(M2 == M)
//       return false;

//    //![1] M2(P) >= M(P)
//    QMapIterator<QString, double> p(M);
//    while (p.hasNext())
//     {
//       p.next();
//       if(p.value() > M2.value(p.key()))
//            return false;
//     }

//   return true;
//}

