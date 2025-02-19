%Insert(el:int,L:list,Rez:list)
%Model de flux:(i,i,o)
%el-elementul pe care il inseram in lista
%L-lista in care vrem sa inseram elementul
%Rez-lista care contine si elementul inserat
%TESTE:
%insert(4,[1,3,5],[1,3,4,5])
%insert(1,[],[1])
%insert(2,[1,2,3],[1,2,2,3])

insert(E,[],[E]).
insert(E,[H|T],[E,H|T]):-
    E=<H.
insert(E,[H|T],Rez):-
    E>H,
    insert(E,T,Rez1),
    Rez=[H|Rez1].

%Sort(L:list,Rez:list)
%Model de flux:(i,o)
%L:lista pe care vrem sa o sortam
%Rez:lista sortata
%TESTE:
%sortare([2,3,1,4],[1,2,3,4])
%sortare([2,3,2,1,4],[1,2,2,3,4])
%sortare([],[])

sortare([],[]).
sortare([H|T],Rez):-
    sortare(T,Rez1),
    insert(H,Rez1,Rez).

%Subpunctul b
%SortareSubliste(L:heterogeneous list,Rez:heterogeneous list)
%Model de flux(i,o)
%L-lista eterogena a caror subliste vrem sa le sortam
%Rez-lista cu sublistele sortate
%TESTE:
% sortareSubliste([1,2,[4,1,4],3,6,[7,10,1,3,9],5,[1,1,1],7],[1, 2, [1, 4, 4], 3, 6, [1, 3, 7, 9, 10], 5, [1, 1, 1], 7])
% sortareSubliste([2,3,[3,6,2],[2,2,0]],[2,3,[2,3,6],[0,2,2]])
% sortareSubliste([],[])
% sortareSubliste([1,3,[]],[1,3,[]])

sortareSubliste([],[]).
sortareSubliste([H|T],Rez):-
    \+ is_list(H),
    sortareSubliste(T,Rez2),
    Rez=[H|Rez2].
sortareSubliste([H|T],Rez):-
    is_list(H),
    sortare(H,Rez1),
    sortareSubliste(T,Rez2),
    Rez=[Rez1|Rez2].

