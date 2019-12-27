#pragma once
#include <gvc.h>
#include <cgraph.h>
#include <stdlib.h>
#include "BT.h"

typedef struct G {
	Agraph_t* g;
	GVC_t* gvc;
}GraphRes;

GraphRes* InitGraph() {
	GraphRes* res = (GraphRes*)malloc(sizeof(GraphRes));

	res->gvc = gvContext();
	res->g = agopen((char*)"G", Agstrictdirected, NULL);
	agattr(res->g, AGNODE, (char*)"shape", (char*)"record");

	return res;
}

void FreeGraph(GraphRes* G) {
	gvFreeLayout(G->gvc, G->g);
	agclose(G->g);
	gvFreeContext(G->gvc);
	free(G);
}