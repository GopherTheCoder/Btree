#pragma once
#pragma warning(disable : 4996)
#include "BT.h"
#include <gvc.h>
#include <cgraph.h>
#include <stdlib.h>

typedef struct G
{
	Agraph_t *g;
	GVC_t *gvc;
} GraphRes;

GraphRes *InitGraph()
{
	GraphRes *res = (GraphRes *)malloc(sizeof(GraphRes));

	res->gvc = gvContext();
	res->g = agopen((char *)"G", Agstrictdirected, NULL);
	agattr(res->g, AGNODE, (char *)"shape", (char *)"record");

	return res;
}

void FreeGraph(GraphRes *G)
{
	gvFreeLayout(G->gvc, G->g);
	agclose(G->g);
	gvFreeContext(G->gvc);
	free(G);
}

Agnode_t* InitNode(BTree t, Agraph_t* g)
{
	Agnode_t* n = agnode(g, NULL, TRUE);
	char str[20];
	itoa(t->key[1], str, 10);
	for (int i = 2; i <= t->key[0]; i++)
	{
		char s[3];
		itoa(t->key[i], s, 10);
		strcat(str, "|");
		strcat(str, s);
	}
	agset(n, (char*)"label", str);

	return n;
}

void CreateGraph(BTree t, Agraph_t *g, Agnode_t *parent)
{
	Agnode_t *n = InitNode(t, g);
	if (parent)
		Agedge_t *e = agedge(g, parent, n, NULL, TRUE);

	if (t->children[0])
		for (int i = 0; i <= t->key[0]; i++)
			CreateGraph(t->children[i], g, n);
}

void RenderGraph(GraphRes *G)
{
	gvLayout(G->gvc, G->g, "dot");
	gvRenderFilename(G->gvc, G->g, "png", "output.png");
}