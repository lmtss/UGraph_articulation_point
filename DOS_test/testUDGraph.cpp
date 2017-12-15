#include<iostream>
#include<string>
#include "UDGrapg.h"
using namespace std;
int main()
{
    UDGraph g;
    //String command;

    g.InsertVertex("aaa");
    g.InsertVertex("bbb");
    g.InsertVertex("ccc");
    g.InsertVertex("ddd");
    g.InsertVertex("eee");

    g.InsertEdge("aaa","bbb");
    g.InsertEdge("ccc","ddd");
    g.InsertEdge("eee","aaa");
    g.InsertEdge("aaa","ccc");

    g.Print();

    g.DeleteEdge("aaa","bbb");
    g.Print();

    return 0;
}
