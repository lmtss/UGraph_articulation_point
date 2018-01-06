#include<iostream>
#include<string>
#include "UDGraph.h"
//#include "DfsTarjan.h"
using namespace std;
int main()
{
    UDGraph g;
    //String command;

    g.InsertVertex("a");
    g.InsertVertex("b");
    g.InsertVertex("c");
    g.InsertVertex("d");
    g.InsertVertex("e");

    /*g.InsertEdge("a","b");
    g.InsertEdge("a","b");*/
    g.DeleteVertex("a");
    cout << g.Pos("c");

    /*DfsTarjan dfs(g);
    dfs.Make();
    cout << dfs.CutEdge() << endl;
    cout << dfs.CutVertex() << endl;*/

    return 0;
}
