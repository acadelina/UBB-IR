
;invers(l1..ln)={
(defun invers(lista)
    (if (null lista)
        list
        (append(invers(cdr lista))(list(car lista)))))
(defun adauga(lista r)
     (if(null lista)
        (if(= r 0)
            nil;
            (list r))
        (let ((suma (+ (car lista) r)))
            (if(< suma 10)
                (cons suma (cdr lista))
                (let ((rest (MOD suma 10)))
                 (cons rest (adauga (cdr lista) 1)))))))
                 
(defun succesor(lista)
        (invers (adauga (invers lista) 1)))