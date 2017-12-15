/*
* UDGraph_Node.h 头文件
* 包含结构体 Edge Vertex 别名 VertexPosition
*
* By 赵元琪
*/


#ifndef UDGRAPH_NODE_H
#define UDGRAPH_NODE_H

#include<string>

typedef int VertexPosition;
struct Edge{
    VertexPosition adj_vex;
    Edge *next;
    Edge(){
        adj_vex = -1;
        next = NULL;
    }
    Edge(VertexPosition adj_vex){
        this->adj_vex = adj_vex;
        next = NULL;
    }
};


struct Vertex{
    std::string name;
    Edge *first_edge;
    Vertex();
    Vertex(const Vertex &v);
    ~Vertex();
    Vertex(std::string name):name(name){first_edge = NULL;}
    void AddEdge(VertexPosition adj_vex);
    void DeleteEdge(VertexPosition adj_vex);
    void DeleteEdge(VertexPosition adj_vex, int num_delete);
    void operator = (const Vertex &v );
};
Vertex::Vertex(){
    name = "null name";
    first_edge = NULL;
}
Vertex::Vertex(const Vertex &v){
    first_edge = NULL;
    name = v.name;
    if(v.first_edge){
        first_edge = new Edge(v.first_edge->adj_vex);
        Edge *v_ptr = v.first_edge->next;
        Edge *ptr = first_edge;
        while(v_ptr){
            ptr->next = new Edge(v_ptr->adj_vex);
            ptr = ptr->next;
            v_ptr = v_ptr->next;;
        }
    }
}
Vertex::~Vertex(){
    Edge *ptr = first_edge;
    Edge *next_ptr = NULL;
    while(ptr){
        next_ptr = ptr->next;
        delete ptr;
        ptr = next_ptr;;
    }
}


/*
* AddEdge(VertexPosition adj_vex)
* 作用: 添加一条与下标为 adj_vex 的顶点相接的边
* 参数: 与此顶点相联的顶点在数组里的位置 (下标)
*/

void Vertex::AddEdge(VertexPosition adj_vex){
    Edge *new_edge = new Edge(adj_vex);
    new_edge->next = first_edge;
    first_edge = new_edge;
}

/*
* DeleteEdge(VertexPosition adj_vex)
* 作用: 删除所有与下标为 adj_vex 的顶点相接的边
* 参数: 与此顶点相联的顶点在数组里的位置 (下标)
*/
void Vertex::DeleteEdge(VertexPosition adj_vex){
    Edge *cur_ptr = first_edge;

    if(!first_edge)return;
    while(first_edge->adj_vex == adj_vex){
        first_edge = first_edge->next;
        delete cur_ptr;
        if(!first_edge) return;
        cur_ptr = first_edge;
    }

    Edge *front_ptr = cur_ptr;
    cur_ptr = cur_ptr->next;
    while(cur_ptr){
        if(cur_ptr->adj_vex == adj_vex){
            front_ptr->next = cur_ptr->next;
            delete cur_ptr;
            cur_ptr = front_ptr->next;
        }
        else{
            cur_ptr = cur_ptr->next;
            front_ptr = front_ptr->next;
        }
    }
}

/*
* DeleteEdge(VertexPosition adj_vex, int num_delete)
* 作用: 删除 数量 <= num_delete 的 与下标为 adj_vex 的顶点相接的边
* 参数: 与此顶点相联的顶点在数组里的位置 (下标)
*/
void Vertex::DeleteEdge(VertexPosition adj_vex, int num_delete){
    Edge *cur_ptr = first_edge;
    int num_deleted = 0;

    if(!first_edge)return;
    while(first_edge->adj_vex == adj_vex){
        first_edge = first_edge->next;
        delete cur_ptr;
        if(!first_edge) return;
        cur_ptr = first_edge;

        num_deleted++;
        if(num_deleted >= num_delete)return;
    }

    Edge *front_ptr = cur_ptr;
    cur_ptr = cur_ptr->next;
    while(cur_ptr){
        if(cur_ptr->adj_vex == adj_vex){
            front_ptr->next = cur_ptr->next;
            delete cur_ptr;
            cur_ptr = front_ptr->next;
            num_deleted++;
            if(num_deleted >= num_delete)return;
        }
        else{
            cur_ptr = cur_ptr->next;
            front_ptr = front_ptr->next;
        }
    }
}

void Vertex::operator = (const Vertex &v){
    first_edge = NULL;
    name = v.name;
    if(v.first_edge){
        first_edge = new Edge(v.first_edge->adj_vex);
        Edge *v_ptr = v.first_edge->next;
        Edge *ptr = first_edge;
        while(v_ptr){
            ptr->next = new Edge(v_ptr->adj_vex);
            ptr = ptr->next;
            v_ptr = v_ptr->next;;
        }
    }
}


#endif // UDGRAPH_NODE_H
