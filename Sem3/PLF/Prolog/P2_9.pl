%sterge(L:list,F:int,R:list)
%(i,i,o)

sterge([],_,[]).
sterge([A],0,[A]).
sterge([_],1,[]).
sterge([H1,H2|T],0,[H1|R]):-
    H1=\=H2-1,
    sterge([H2|T],0,R).
sterge([H1,H2|T],_,R):-
    H1=:=H2-1,
    sterge([H2|T],1,R).
sterge([H1,H2|T],1,R):-
    H1=\=H2-1,
    sterge([H2|T],0,R).
