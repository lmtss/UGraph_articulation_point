#ifndef UDGraph_H
#define UDGraph_H

#include<vector>
#include<string>
#include<map>
#include<iostream>
#include "UDGraph_Node.h"

class UDGraph{
private:
    std::vector<Vertex> vertex_list_;
    std::map<std::string, VertexPosition> map_name_position_;
    size_t num_vertex_, num_edge_;
    bool is_exist_vertex(std::string name){
        return (map_name_position_.find(name) == map_name_position_.end())?false:true;
    }
    bool is_exist_vertex(VertexPosition pos){
        return (pos < vertex_list_.size())?true:false;
    }
    void DeleteVertex(std::string delete_vertex_name, VertexPosition delete_vertex_position);

public:
    UDGraph();
    void InsertVertex(std::string new_vertex_name);
    void DeleteVertex(std::string delete_vertex_name);
    void DeleteVertex(VertexPosition delete_vertex_position);
    void DeleteEdge(std::string Vertex_name_1, std::string vertex_name_2);
    void DeleteEdge(std::string vertex_name_1, std::string vertex_name_2, int num_delete);
    void InsertEdge(std::string vertex_name_1, std::string vertex_name_2);
    void Print();

    friend class DfsTarjan;
};
UDGraph::UDGraph(){
    vertex_list_ .reserve(50);
    num_vertex_ = 0;
    num_edge_ = 0;
}
void UDGraph::InsertVertex(std::string new_vertex_name){
    if(is_exist_vertex(new_vertex_name));
    else {
        VertexPosition new_vertex_position = num_vertex_;
        map_name_position_[new_vertex_name] = new_vertex_position;

        vertex_list_.push_back(Vertex(new_vertex_name));
        num_vertex_++;
    }
}
void UDGraph::DeleteVertex(std::string delete_vertex_name){
    if(is_exist_vertex(delete_vertex_name)){
        DeleteVertex(delete_vertex_name, map_name_position_[delete_vertex_name]);
    }
    else ;
}
void UDGraph::DeleteVertex(VertexPosition delete_vertex_position){
    if(is_exist_vertex(delete_vertex_position)){
        DeleteVertex(vertex_list_[delete_vertex_position].name, delete_vertex_position);
    }
    else ;
}
void UDGraph::DeleteVertex(std::string delete_vertex_name, VertexPosition delete_vertex_position){
    vertex_list_.erase(vertex_list_.begin() + delete_vertex_position);
    map_name_position_.erase(map_name_position_.find(delete_vertex_name));
    for(int i = 0; i < vertex_list_.size(); i++)
        vertex_list_[i].DeleteEdge(delete_vertex_position);

}
void UDGraph::Print(){
    for(int i = 0; i < vertex_list_.size(); i++){
        std::cout << vertex_list_[i].name << std::endl;
        Edge *ptr_edge = vertex_list_[i].first_edge;
        while(ptr_edge){
            std::cout << ptr_edge->adj_vex << ":" << vertex_list_[ptr_edge->adj_vex].name << " ";
            ptr_edge = ptr_edge->next;
        }
        std::cout << std::endl;
    }
}
void UDGraph::InsertEdge(std::string vertex_name_1, std::string vertex_name_2){
    if( (!is_exist_vertex(vertex_name_1)) || (!is_exist_vertex(vertex_name_1)));
    else {
        VertexPosition vertex_pos_1 = map_name_position_[vertex_name_1], vertex_pos_2 = map_name_position_[vertex_name_2];
        vertex_list_[vertex_pos_1].AddEdge(vertex_pos_2);
        //vertex_list_[vertex_pos_2].AddEdge(vertex_pos_1);
    }
}
void UDGraph::DeleteEdge(std::string vertex_name_1, std::string vertex_name_2){
    if( (!is_exist_vertex(vertex_name_1)) || (!is_exist_vertex(vertex_name_1)));
    else {
        VertexPosition vertex_pos_1 = map_name_position_[vertex_name_1], vertex_pos_2 = map_name_position_[vertex_name_2];
        vertex_list_[vertex_pos_1].DeleteEdge(vertex_pos_2);
        vertex_list_[vertex_pos_2].DeleteEdge(vertex_pos_1);
    }
}
void UDGraph::DeleteEdge(std::string vertex_name_1, std::string vertex_name_2, int num_delete){
    if( (!is_exist_vertex(vertex_name_1)) || (!is_exist_vertex(vertex_name_1)));
    else {
        VertexPosition vertex_pos_1 = map_name_position_[vertex_name_1], vertex_pos_2 = map_name_position_[vertex_name_2];
        vertex_list_[vertex_pos_1].DeleteEdge(vertex_pos_2,num_delete);
        vertex_list_[vertex_pos_2].DeleteEdge(vertex_pos_1,num_delete);
    }
}

#endif // UDGraph_H
