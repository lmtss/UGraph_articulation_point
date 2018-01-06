#ifndef DFSTARJAN_H
#define DFSTARJAN_H

#include<vector>
#include<string>
#include<map>
#include<iostream>
#include <cstring>
#include "UDGraph.h"

using namespace std;
struct DfsTarjanFuZhuNode{
    VertexPosition position;
    DfsTarjanFuZhuNode *next, *front;
    DfsTarjanFuZhuNode(){position = 0; next = NULL; front = NULL;}
    DfsTarjanFuZhuNode(VertexPosition p):position(p){next = NULL; front = NULL; }
    ~DfsTarjanFuZhuNode(){}
};
typedef DfsTarjanFuZhuNode *DfsTarjanFuZhuNodePtr;
struct DfsTarjanFuZhu{
    bool *is_visited;
    DfsTarjanFuZhuNodePtr *ptr_list;
    DfsTarjanFuZhuNode *first_node;
    int num_vertex;
    bool is_empty;

    DfsTarjanFuZhu(){
        is_empty = true;
        Set(1);
    }
    DfsTarjanFuZhu(int num){
        is_empty = true;
        Set(num);
    }
    ~DfsTarjanFuZhu(){
        destroy();
    }
    void Set(int num){
        first_node = NULL;
        destroy();
        if(num <= 0){
            num = 1;
        }
        num_vertex = num;
        is_visited = new bool[num];
        memset(is_visited, false, num);
        ptr_list = new DfsTarjanFuZhuNodePtr[num];

        first_node = new DfsTarjanFuZhuNode(0);
        ptr_list[0] = first_node;
        DfsTarjanFuZhuNode *ptr = first_node, *fro_ptr = first_node;
        for(int i = 1; i < num; i++){
            fro_ptr = ptr;
            ptr = new DfsTarjanFuZhuNode(i);
            ptr_list[i] = ptr;
            //ptr->next->front = ptr;
            fro_ptr->next = ptr;
            ptr->front = fro_ptr;

        }
        is_empty = false;
    }//aÈöµ©
    void destroy(){
        if(is_empty)return;
        delete[] is_visited;
        delete[] ptr_list;
        //DfsTarjanFuZhuNode *ptr = first_node, *next_ptr = NULL;//cout << first_node->position;
        /*while(ptr != NULL){
            next_ptr = ptr->next;
            delete ptr;
            ptr = next_ptr;
            ptr = ptr->next;
        }*/
    }//6 a b c d e f 6 a c c d b d a b a e d f
    VertexPosition First(){
        if(first_node != NULL) return first_node->position;
        else return -1;
    }
    void Delete(VertexPosition position){
        if(position >= num_vertex || is_visited[position])return;
        if(ptr_list[position] == first_node){
            if(ptr_list[position]->next != NULL){
                first_node = ptr_list[position]->next;
                first_node->front = NULL;
            }else first_node = NULL;
        }
        else {
            if(ptr_list[position]->next != NULL){
                ptr_list[position]->front->next = ptr_list[position]->next;
                ptr_list[position]->next->front = ptr_list[position]->front;
            }else ptr_list[position]->front->next = NULL;
        }
        delete ptr_list[position];
        is_visited[position] = true;
    }
};

class DfsTarjan{
private:
    int traversal_order_;
    bool is_empty_;
    int *dfn_, *low_;
    VertexPosition *parent_;
    UDGraph &graph_;
    int connected_component_;
    DfsTarjanFuZhu *FuZhu_;

    string cut_edges_, cut_vertex_;
public:
    DfsTarjan(UDGraph &graph):graph_(graph){
        is_empty_ = true;
        SetGraph(graph_);
    }
    ~DfsTarjan(){
        destroy();
    }
    void SetGraph(UDGraph &graph){
        destroy();
        graph_ = graph;
        traversal_order_ = 0;
        connected_component_ = 0;
        is_empty_ = false;
        dfn_ = new int[graph.num_vertex_];
        low_ = new int[graph.num_vertex_];
        parent_ = new VertexPosition[graph.num_vertex_];
        FuZhu_ = new DfsTarjanFuZhu(graph_.num_vertex_);

        memset(parent_, -1, sizeof(VertexPosition)*graph.num_vertex_);
        memset(dfn_, -1, sizeof(int)*graph.num_vertex_);
        //memset(low_, -1, sizeof(int)*graph.num_vertex_);
    }
    void destroy(){
        if(is_empty_)return;
        is_empty_ = true;
        //delete[] is_visited_;
        delete[] dfn_;
        delete[] low_;
        delete[] parent_;
        delete FuZhu_;
    }
    void dfs(VertexPosition this_node_position, Edge *f_){
        int num_children = 0;
        Edge *this_node_edge_ptr = graph_.vertex_list_[this_node_position].first_edge;
        dfn_[this_node_position] = low_[this_node_position] = ++traversal_order_;
        FuZhu_->Delete(this_node_position);

        for(; this_node_edge_ptr != NULL; this_node_edge_ptr = this_node_edge_ptr->next){
            VertexPosition adj_vex = this_node_edge_ptr->adj_vex;
            if(dfn_[adj_vex] == -1){
                num_children++;
                parent_[adj_vex] = this_node_position;
                dfs(adj_vex, this_node_edge_ptr);
                low_[this_node_position] = min(low_[this_node_position], low_[adj_vex]);


                if(parent_[this_node_position] == -1 && num_children > 1){
                    cout << "1:" << this_node_position << ":" << adj_vex << endl;
                    cut_vertex_ += to_string(this_node_position);
                    cut_vertex_ += ",";
                }
                else if(parent_[this_node_position] != -1 && low_[adj_vex] >= dfn_[this_node_position]){
                    cout << "2:" << this_node_position << ":" << adj_vex << endl;
                    cut_vertex_ += to_string(this_node_position);
                    cut_vertex_ += ",";
                }
            } else if(adj_vex != parent_[this_node_position]){
                low_[this_node_position] = min(low_[this_node_position], dfn_[adj_vex]);
            }
        }
    }
    int GetTraOrder(){return traversal_order_;}
    void print(){
        for(int i = 0; i < graph_.num_vertex_; i++){
            cout << graph_.vertex_list_[i].name << "dfn:" << dfn_[i] << " low:" << low_[i] << endl;
        }
    }
    void Make(){
        cut_edges_ = "";
        cut_vertex_ = "";
        while(graph_.num_vertex_ != traversal_order_){
            VertexPosition first_position = FuZhu_->First();
            if(first_position == -1)return;
            dfs(first_position, NULL);
            connected_component_++;
        }

        for(int i = 0; i < graph_.num_vertex_; i++){
            if(parent_[i]!=-1){
                if(low_[i] > dfn_[parent_[i]]){
                    cut_edges_ += to_string(i);
                    cut_edges_ += ",";
                    cut_edges_ += to_string(parent_[i]);
                    cut_edges_ += ",";
                }
            }

        }

    }
    string CutVertex(){
        return cut_vertex_;
    }
    string CutEdge(){
        return cut_edges_;
    }
};


#endif // DFSTARJAN_H
