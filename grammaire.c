struct nodeType
{
    nodeType *left;
    nodeType *right;
    char class[10];
};

nodeType * genConc(nodeType * p1, nodeType * p2){
	nodeType node;
	node.left = p1;
	node.right = p2;
	node.class = "conc";
	return (&node);
}

nodeType * genUnion(nodeType * p1, nodeType * p2){
	nodeType node;
	node.left = p1;
	node.right = p2;
	node.class = "union";
	return (&node);
}

nodeType * genStar(nodeType * p1){
	nodeType node;
	node.left = p1;
	node.class = "star";
	return (&node);
}

nodeType * genUn(nodeType * p1){
	nodeType node;
	node.left = p1;
	node.class = "un";
	return (&node);
}

nodeType * genAtom(){
	nodeType node;
	return (&node)
}

nodeType ** genForet(){
	nodeType * foret[5];
	return foret;
}

void ImprimArbre(nodeType *root, int prof = 1){
	
}

int main(){
	
	return 0;
}
