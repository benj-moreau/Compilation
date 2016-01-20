#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodeType
{
    nodeType *left;
    nodeType *right;
    char name[];
};

nodeType * genConc(nodeType * p1, nodeType * p2){
	nodeType * node;
	node->left = p1;
	node->right = p2;
	strcpy(node->name, "conc");
	return (node);
}

nodeType * genUnion(nodeType * p1, nodeType * p2){
	nodeType * node;
	node->left = p1;
	node->right = p2;
	strcpy(node->name, "union");
	return (node);
}

nodeType * genStar(nodeType * p1){
	nodeType * node;
	node->left = p1;
	node->right = NULL;
	strcpy(node->name, "star");
	return (node);
}

nodeType * genUn(nodeType * p1){
	nodeType * node;
	node->left = p1;
	node->right = NULL;
	strcpy(node->name, "un");
	return (node);
}

nodeType * genAtom(){//TODO
	nodeType * node;
	return (node);
}

nodeType ** genForet(){
	nodeType * foret[5];
	return foret;
}

void ImprimArbreRec(nodeType *root, int prof){
  ++prof;
  char nodeName[10];
  strcpy(nodeName,root->name);
  for(int i=1; i=prof; ++i){
    printf("---");
  }
  printf(">%s\n", nodeName);
  if (nodeName == "conc"){
     //printf(">conc\n");
     ImprimArbreRec(root->left, prof);
     ImprimArbreRec(root->right, prof);
  }else if (nodeName == "union"){
    //printf(">union\n");
    ImprimArbreRec(root->left, prof);
    ImprimArbreRec(root->right, prof);
  }else if (nodeName == "star"){
    // printf(">star\n");
    ImprimArbreRec(root->left, prof);
  }else if (nodeName == "un"){
     //printf(">un\n");
     ImprimArbreRec(root->left, prof);
  }else { //atome
     //TODO
  }
}
void ImprimArbre(nodeType *root){
  ImprimArbreRec(root, 1);
}

int main(){

	return 0;
}
