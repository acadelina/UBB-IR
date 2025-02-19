(defun exista (lista a)
    (cond
        ((null lista) nil)
        ((equal a (car lista))t)
        (t (exista (cdr lista) a))))

(defun lineara (lista)
    (cond
        ((null lista) nil)
        ((listp (car lista))(append(lineara(car lista))(lineara(cdr lista))))
        ((atom  (car lista))(cons (car lista)(lineara(cdr lista))))
         (t ;daca primul elem e o sublista aplicam fct recursiv
            (lineara(cdr lista)))))

(defun toSet(l r)
    (cond
    ((null l) r)
    ((exista r (car l))(toSet (cdr l) r))
    (t (toSet (cdr l) (append r (list (car l)))))))
        
(defun main(l)
    (toSet (lineara l) (list))
    )