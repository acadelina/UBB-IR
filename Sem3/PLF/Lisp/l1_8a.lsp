;elimina-poz-n(l1..ln, m)={ [] , n<1
						;   l2..ln, m=1
                        ;   l1(+)elimina-poz-n(l2..ln,m-1), altfel
						;	}
;l-lisat din care eliminam al m-lea element
;m- pozitia de pe care vrem sa eliminam elementul 
						
;Testare:(elimina-poz-n '(1 2 3 4 5) 2)=>(1 3 4 5)
;(elimina-poz-n '(1 2 3 4 5) 0)=>(1 2 3 4 5)
;(elimina-poz-n '(1 2 3 4 5) 6)=>(1 2 3 4 5)
(defun elimina-poz-n (lista n)
    (if (or (null lista) (< n 1))
        lista
        (if (and (= n 1) (not(listp (car lista)))) 
            (cdr lista)
			(if (listp (car lista))
				(cons (car lista) (elimina-poz-n(cdr lista) n ))
				(cons (car lista) (elimina-poz-n(cdr lista)(- n 1)))))))