*GenData(1) *GenData(2) *GenData(3) *GenData(4)
*GenData(5) *GenData(6) *GenData(7)
*GenData(8) *GenData(9) *GenData(10)
*Set Cond Dirichlet *nodes
*set var ND=CondNumEntities(int)
*Set Cond Neumann *nodes
*set var NN=CondNumEntities(int)
*npoin *nelem *ND *NN

Coordinates
*set elems(all)
*loop nodes
*NodesNum *NodesCoord(1,real) *NodesCoord(2,real)
*end nodes
EndCoordinates

Elements
*loop elems
*ElemsNum *ElemsConec
*end elems
EndElements

Dirichlet
*Set Cond Dirichlet *nodes
*loop nodes *OnlyInCond
*NodesNum
*end nodes
EndDirichlet

Neumann
*Set Cond Neumann *nodes
*loop nodes *OnlyInCond
*NodesNum
*end nodes
EndNeumann
