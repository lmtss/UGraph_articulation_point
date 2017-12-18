#ifndef UDGraph_H
#define UDGraph_H

#include<vector>
#include<string>
#include<map>
#include<iostream>
#include<fstream>
#include "UDGraph_Node.h"


class UDGraph{
private:
    std::vector<Vertex> vertex_list_;
    std::map<std::string, VertexPosition> map_name_position_;
    size_t num_vertex_, num_edge_;


    void DeleteVertex(std::string delete_vertex_name, VertexPosition delete_vertex_position){
        vertex_list_.erase(vertex_list_.begin() + delete_vertex_position);
        map_name_position_.erase(map_name_position_.find(delete_vertex_name));
        for(int i = 0; i < vertex_list_.size(); i++)
            vertex_list_[i].DeleteEdge(delete_vertex_position);
        num_vertex_--;
    }

public:
    UDGraph(){
        vertex_list_ .reserve(50);
        num_vertex_ = 0;
        num_edge_ = 0;
    }
    bool is_exist_vertex(VertexPosition pos){
        return (pos < vertex_list_.size())?true:false;
    }
    bool is_exist_vertex(std::string name){
        return (map_name_position_.find(name) == map_name_position_.end())?false:true;
    }
    int InsertVertex(std::string new_vertex_name){
        if(is_exist_vertex(new_vertex_name)){
            return 0;
        }
        else {
            VertexPosition new_vertex_position = num_vertex_;
            map_name_position_[new_vertex_name] = new_vertex_position;

            vertex_list_.push_back(Vertex(new_vertex_name));
            num_vertex_++;
            return 1;
        }
    }
    void DeleteVertex(std::string delete_vertex_name){
        if(is_exist_vertex(delete_vertex_name)){
            DeleteVertex(delete_vertex_name, map_name_position_[delete_vertex_name]);
        }
        else ;
    }
    void DeleteVertex(VertexPosition delete_vertex_position){
        if(is_exist_vertex(delete_vertex_position)){
            DeleteVertex(vertex_list_[delete_vertex_position].name, delete_vertex_position);
        }
        else ;
    }
    void DeleteEdge(std::string vertex_name_1, std::string vertex_name_2){
        if( (!is_exist_vertex(vertex_name_1)) || (!is_exist_vertex(vertex_name_2)));
        else {
            VertexPosition vertex_pos_1 = map_name_position_[vertex_name_1], vertex_pos_2 = map_name_position_[vertex_name_2];
            vertex_list_[vertex_pos_1].DeleteEdge(vertex_pos_2);
            vertex_list_[vertex_pos_2].DeleteEdge(vertex_pos_1);
            num_edge_--;
        }
    }
    void DeleteEdge(std::string vertex_name_1, std::string vertex_name_2, int num_delete){
        if( (!is_exist_vertex(vertex_name_1)) || (!is_exist_vertex(vertex_name_1)));
        else {
            VertexPosition vertex_pos_1 = map_name_position_[vertex_name_1], vertex_pos_2 = map_name_position_[vertex_name_2];
            vertex_list_[vertex_pos_1].DeleteEdge(vertex_pos_2,num_delete);
            vertex_list_[vertex_pos_2].DeleteEdge(vertex_pos_1,num_delete);
            num_edge_--;
        }
    }
    Edge *InsertEdge(std::string vertex_name_1, std::string vertex_name_2){
        if( (!is_exist_vertex(vertex_name_1)) || (!is_exist_vertex(vertex_name_1))){
            return NULL;
        }

        else {
            VertexPosition vertex_pos_1 = map_name_position_[vertex_name_1], vertex_pos_2 = map_name_position_[vertex_name_2];
            vertex_list_[vertex_pos_1].AddEdge(vertex_pos_2);
            vertex_list_[vertex_pos_2].AddEdge(vertex_pos_1);
            num_edge_++;

            return (vertex_pos_1 < vertex_pos_2)?vertex_list_[vertex_pos_1].first_edge:vertex_list_[vertex_pos_2].first_edge;
        }
    }
    void Print(){
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
    void CreateFromFile(std::string file_name){
        std::ifstream file;
        file_name = "test.txt";
        file.open(file_name);

        int num;
        file >> num;

        std::string name1, name2;
        for(int i = 0; i < num; i++){
            file >> name1;
            InsertVertex(name1);
        }
        file >> num;
        for(int i = 0; i < num; i++){
            file >> name1 >> name2;
            InsertEdge(name1,name2);
        }
    }
    void SaveAsFile(std::string file_name){
        std::ofstream file;
        //file_name = "f.txt";
        file.open(file_name);
        file << num_vertex_ << std::endl;
        for(int i = 0; i < num_vertex_; i++){
            file << vertex_list_[i].name << std::endl;
        }
        file << num_edge_ << std::endl;
        for(int i = 0; i < num_vertex_; i++){
            Edge *ptr = vertex_list_[i].first_edge;
            for(; ptr != NULL; ptr = ptr->next){
                if(ptr->adj_vex >= i){
                    file << vertex_list_[i].name << std::endl;
                    file << vertex_list_[ptr->adj_vex].name << std::endl;
                }
            }
        }
    }

    int IsExistEdge(std::string vertex_name_1, std::string vertex_name_2){
        if((!is_exist_vertex(vertex_name_1)) || (!is_exist_vertex(vertex_name_2))){
            return -1;
        }else
            return vertex_list_[map_name_position_[vertex_name_1]].IsExistEdge(map_name_position_[vertex_name_2]);
    }

    friend class DfsTarjan;
    friend class MainWindow;
};

#endif // UDGraph_H
