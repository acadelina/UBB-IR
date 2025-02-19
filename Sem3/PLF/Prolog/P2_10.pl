%addElem(L:list,P:int,C1:int,C2:int,E:int,R:list)
%(i,i,i,i,o)

addElem([],_,_,_,_,[]).
addElem([H|T],P,C1,C2,E,[H|R]):-
    P<C1,
    P1 is P+1,
    addElem(T,P1,C1,C2,E,R).
addElem([_|T],P,C1,C2,E,[E|R]):-
    P=:=C1,
    P1 is P+1,
    C3 is C1+C2,
    C4 is C2+1,
    addElem(T,P1,C3,C4,E,R).
