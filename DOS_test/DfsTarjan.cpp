#include<vector>
#include<string>
#include<map>
#include<iostream>
#include <cstring>
#include "UDGraph.h"
using namespace std;
class DfsTarjan{
private:
    int traversal_order_;
    bool *is_visited_, is_empty_;
    int *dfn_, *low_;
    VertexPosition *parent_;
    UDGraph &graph_;
public:
    DfsTarjan(UDGraph &graph);
    void SetGraph(UDGraph &graph);
    void destroy();
    void dfs(VertexPosition position_this);
};
DfsTarjan::DfsTarjan(UDGraph &graph):graph_(graph){
    traversal_order_ = 0;
    is_empty_ = true;
    //this->graph_ = graph;
}
void DfsTarjan::SetGraph(UDGraph &graph){
    destroy();
    graph_ = graph;
    traversal_order_ = 0;
    is_visited_ = new bool[graph.num_vertex_];
    dfn_ = new int[graph.num_vertex_];
    low_ = new int[graph.num_vertex_];
    parent_ = new VertexPosition[graph.num_vertex_];
    memset(parent_, -1, sizeof(VertexPosition)*graph.num_vertex_);
    memset(is_visited_, false, sizeof(bool)*graph.num_vertex_);
}
void DfsTarjan::destroy(){
    if(is_empty_)return;

    delete[] is_visited_;
    delete[] dfn_;
    delete[] low_;
    delete[] parent_;
}
void DfsTarjan::dfs(VertexPosition this_node_position){
    int num_children = 0;
    Edge *this_node_edge_ptr = graph_.vertex_list_[this_node_position].first_edge;
    is_visited_[this_node_position] = true;
    dfn_[this_node_position] = low_[this_node_position] = ++traversal_order_;



    for(; this_node_edge_ptr != NULL; this_node_edge_ptr = this_node_edge_ptr->next){
        VertexPosition adj_vex = this_node_edge_ptr->adj_vex;
        if(!is_visited_[adj_vex]){
            num_children++;
            parent_[adj_vex] = this_node_position;
            dfs(adj_vex);
            low_[this_node_position] = min(low_[this_node_position], low_[adj_vex]);

            if(parent_[this_node_position] == -1 && num_children > 1){
                cout << "1:" << this_node_position << ":" << adj_vex << endl;
            }
            else if(parent_[this_node_position] != -1 && low_[adj_vex] >= dfn_[this_node_position]){
                cout << "2:" << this_node_position << ":" << adj_vex << endl;
            }
        } else if(adj_vex != parent_[this_node_position]){
            low_[this_node_position] = min(low_[this_node_position], dfn_[adj_vex]);
        }
    }
}
int main()
{
    UDGraph g;
    int num;
    string a,b;
    cout << "¶¥µãÊý" << endl;
    cin >> num;
    for(int i = 0; i < num; i++){
        cin >> a;
        g.InsertVertex(a);
    }
    cout << "±ßÊý" << endl;
    cin >> num;
    for(int i = 0; i < num; i++){
        cin >> a >> b;
        g.InsertEdge(a, b);
    }
    //g.Print();
    DfsTarjan dfs(g);
    dfs.SetGraph(g);
    dfs.dfs(0);
    return 0;
}
//6 a b c d e f 6 a c c d b d a b a e d f
