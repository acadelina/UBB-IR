%Cazul de baza: cand m este mai mare decat n, lista e goala
range(M,N,[]) :- M>N.
%Cazul recursiv: adaug M la lista si apelam recursiv pt M+1
range(M,N,[M|Rest]):-
    M=<N,
    M1 is M+1,
    range(M1, N, Rest).
