#include "Graphviz.h"
#include <string>

GraphRes *Graph::InitGraph()
{
    GraphRes *res = (GraphRes *)malloc(sizeof(GraphRes));

    res->gvc = gvContext();
    res->g = agopen((char *)"G", Agstrictdirected, NULL);
    agattr(res->g, AGNODE, (char *)"shape", (char *)"record");

    return res;
}

void Graph::FreeGraph(GraphRes *G)
{
    gvFreeLayout(G->gvc, G->g);
    agclose(G->g);
    gvFreeContext(G->gvc);
    free(G);
}

Agnode_t *Graph::InitNode(BTree t, Agraph_t *g)
{
    Agnode_t *n = agnode(g, NULL, TRUE);
    std::string s = std::to_string(t->key[1]);
    for (int i = 2; i <= t->key[0]; i++)
    {
        s += "|";
        s += std::to_string(t->key[i]);
    }
    agset(n, (char *)"label", (char *)s.c_str());

    return n;
}

void Graph::CreateGraph(BTree t, Agraph_t *g, Agnode_t *parent)
{
    Agnode_t *n = Graph::InitNode(t, g);
    if (parent)
        Agedge_t *e = agedge(g, parent, n, NULL, TRUE);

    if (t->children[0])
        for (int i = 0; i <= t->key[0]; i++)
            Graph::CreateGraph(t->children[i], g, n);
}

void Graph::RenderGraph(GraphRes *G)
{
    gvLayout(G->gvc, G->g, "dot");
    gvRenderFilename(G->gvc, G->g, "png", "output.png");
}
