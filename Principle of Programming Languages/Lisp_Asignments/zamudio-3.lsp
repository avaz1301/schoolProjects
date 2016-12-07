
(defun MIN-2 (x y)
	(if (AND (numberp x) (numberp y)) 
		(cond ((<= x y) x) 
			  ((> x y) y)) 
		'ERROR ))


(defun SAFE-AVG (x y)
	(AND (numberp x) 
		 (numberp y) 
		 (/ (+ x y) 2)))


(defun ODD-GT-MILLION (x)
	(if (integerp x) 
		(AND (oddp x) 
			 (> x 1000000)
			  T)
		'NIL))


(defun MULTIPLE-MEMBER (x y)
	(if (AND (OR (symbolp x) (numberp x)) (listp y))
		(member x (rest (member x y))) 
		'NIL)) 


(defun MONTH->INTEGER (x)
	(cond 
		((equal x 'JANUARY) 1)
		((equal x 'FEBUARY) 2)
		((equal x 'MARCH) 3)
		((equal x 'APRIL) 4)
		((equal x 'MAY) 5)
		((equal x 'JUNE) 6)
		((equal x 'JULY) 7)
		((equal x 'AUGUST) 8)
		((equal x 'SEPTMBER) 9)
		((equal x 'OCTOBER) 10)
		((equal x 'NOVEMBER) 11)
		((equal x 'DECEMBER) 12)
		('ERROR)))


(defun SCORE->GRADE (s)
	(if (numberp s) 
		(cond 
		  ((>= s 90) 'A)
		  ((>= s 87) 'A-)
		  ((>= s 83) 'B+)
		  ((>= s 80) 'B)
		  ((>= s 77) 'B-)
		  ((>= s 73) 'C+)
		  ((>= s 70) 'C)
		  ((>= s 60) 'D)
		  ((< s 60) 'F))))


(defun GT (x y)
	(AND (numberp x) 
		 (numberp y) 
		 (> x y)
		 (T))) 


(defun SAME-SIGN (x y)
	(AND 
		(numberp x) 
		(numberp y) 
		(OR 
			(AND (> x 0) (> y 0) T)
			(AND (= x 0) (= y 0) T)
			(AND (< x 0) (< y 0) T))))

(defun SAFE-DIV (x y)
	(AND 
		(numberp x) 
		(numberp y) 
		(OR 
			(> y 0) 
			(< y 0)) 
			(/ x y)))
		




