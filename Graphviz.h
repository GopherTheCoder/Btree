#pragma once
//#pragma warning(disable : 4996)

#include "BT.h"
#include <gvc.h>
#include <cgraph.h>
#include <stdlib.h>

typedef struct G
{
	Agraph_t *g;
	GVC_t *gvc;
} GraphRes;

class Graph
{
public:
	static GraphRes *InitGraph();
	static void FreeGraph(GraphRes *G);
	static Agnode_t *InitNode(BTree t, Agraph_t *g);
	static void CreateGraph(BTree t, Agraph_t *g, Agnode_t *parent);
	static void RenderGraph(GraphRes *G);
};
