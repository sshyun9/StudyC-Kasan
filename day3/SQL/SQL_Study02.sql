-- Sample DB Employees 학습
-- Department 부서테이블 조회
SELECT dp.dept_no, dp.dept_name
 FROM departments as dp;
 
 SELECT dm.emp_no, dm.dept_no, dm.from_date, dm.to_date
 FROM dept_manager as dm;


-- 합치기 (조인) INNER JOIN
SELECT dp.dept_no
	, dp.dept_name
	, dm.emp_no
	, dm.from_date
	, dm.to_date
    /*, em.emp_no*/
    , date_format(em.birth_date, '%Y년 %m월 %d일') as '생일'
    , CONCAT(em.first_name, ' ', em.last_name) as 'full_name'
    , CASE WHEN em.gender = 'F' then '여성'
		   WHEN em.gender = 'M' then '남성'
		   ELSE '오류' END as '성별'
 FROM departments as dp
INNER JOIN dept_manager as dm
		ON dp.dept_no = dm.dept_no
INNER JOIN employees as em
		on em.emp_no = dm.emp_no;
        
-- Employees & Salaries
SELECT em.emp_no
	 , em.birth_date
     , em.first_name
     , em.last_name
	 , em.gender
	 , hire_date 
     , sl.salary
     , sl.from_date
     , sl.to_date
      from employees as em
INNER JOIN salaries as sl
		ON em.emp_no = sl.emp_no
	 WHERE em.emp_no = 10002;

select count(*) From salaries; -- 2844047
SELECT sum(salary) FROM salaries;  -- 181480757419

-- 회사 직원중 10299번까지의 직원의
-- 평균연봉, 연봉총합, 근무년수를 출력
SELECT res.emp_no
	 , res.1 as '연봉총합'
     , res.2 as '평균연봉'
     , res.3 as '근무년수'
     , emp.first_name
     , emp.last_name
     , emp.gender
From(
 SELECT sl.emp_no
	 , sum(sl.salary) as '1'
     , AVG(sl.salary) as '2'
     , COUNT(sl.salary) as '3'
  FROM salaries as sl
  Where sl.emp_no <= 10299
 GROUP BY sl.emp_no
 HAVING Count(sl.salary) >=15
 ) as res

SELECT sl.emp_no
	 , sl.salary
     , sl. from_date
     , sl. to_date
  from Salaries as sl;
  

-- Employee
SELECT em.emp_no, em.birth_date, em.first_name, em.last_name, em.gender, em.hire_date
  FROM employees as em;
  

