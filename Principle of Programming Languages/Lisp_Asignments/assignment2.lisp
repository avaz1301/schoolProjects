(defun perim (length height) 
	(* length height))

(SETF X '(a b c))
(append x x)

(QUOTE (QUOTE (QUOTE (a)) ) )

(SETF y (list  'a 'b))

(list 'd (car y))


(defun QUADRATIC (a b c)
	(list (/ (+ (* -1 b) (SQRT (- (* b b) (* 4 a c))))  (* 2 a)) (/ (- (* -1 b) (SQRT (- (* b b) (* 4 a c))))  (* 2 a)) ))

(defun circle (radius)
	(* PI radius radius))

(defun FTOC (f)
	(* 5/9 (- f 32)))

(defun ROTATE-LEFT (lst)
	(append  (cdr lst) (list(car lst))))

(defun POINTS (a b y z)
 	(SQRT (+ (* (- a y) (- a y)) (* (- b z) (- b z)))))

(defun HEAD (lst)
	(car lst))

(defun TAIL (lst)
	(cdr lst))

(defun SWITCH (lst)
	(append (cdr lst) (list (car lst)))) 		

(setf 8*7 5) -->5

(defun 8+7 (x y) (+ x y))  

(defun 8*7 () 9)

(8+7 (* 8 7) (8+7 (8*7) 8*7)) -->70

(SETF e '(a b x d))
(car (cdr (cdr e)))
(A B X D)

(SETF e '(a (b (x d))))
(car (car (cdr (car (cdr e)))))
(A (B (X D)))

(SETF e '(((a (b (x) d)))))
(car (car (cdr (car (cdr (car (car e)))))))
(((A (B (X) D))))

(cons 'a (cons 'b (cons 'x (cons 'd nil))))
(A B X D)

(cons 'a (cons (cons 'b (cons (cons 'x '(d)) 'nil)) 'nil))
(A (B (X D)))

(cons (cons (cons 'a (cons (cons 'b (cons (cons 'x 'nil) (cons 'd 'nil))) 'nil)) 'nil) 'nil)
(((A (B (X) D))))









