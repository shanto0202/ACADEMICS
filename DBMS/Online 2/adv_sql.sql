/*
===============================================================================
ORACLE ADVANCED SQL - 30 MIN COMPACT CHEATSHEET
Sukarna Barua Ch 5,6,7,11 | HR Schema | Sec-A/Online style
Every example keeps the QUESTION immediately before the query as a comment.
===============================================================================
*/

/* QUICK FIND
JOIN | SELF JOIN | LEFT JOIN | GROUP BY | DEPT AVG | SECOND HIGHEST
EXISTS | NOT EXISTS | EVERY | ANY ALL | SELECT SUBQUERY | FROM SUBQUERY
INTERSECT | UNION | MINUS | XOR | CASE | DECODE | WITH | SEC-A | ERRORS
*/

/* HR PATHS
EMPLOYEES.DEPARTMENT_ID = DEPARTMENTS.DEPARTMENT_ID
EMPLOYEES.JOB_ID        = JOBS.JOB_ID
EMPLOYEES.MANAGER_ID    = EMPLOYEES.EMPLOYEE_ID
EMPLOYEES.EMPLOYEE_ID   = JOB_HISTORY.EMPLOYEE_ID
DEPARTMENTS.LOCATION_ID = LOCATIONS.LOCATION_ID
LOCATIONS.COUNTRY_ID     = COUNTRIES.COUNTRY_ID
*/


/*=============================================================================
1. JOIN
=============================================================================*/

/* Q: Show employee_id, last_name, department_name. */
SELECT E.EMPLOYEE_ID, E.LAST_NAME, D.DEPARTMENT_NAME
FROM EMPLOYEES E
JOIN DEPARTMENTS D
  ON E.DEPARTMENT_ID = D.DEPARTMENT_ID;


/* Q: Same using USING. */
SELECT E.EMPLOYEE_ID, DEPARTMENT_ID, D.DEPARTMENT_NAME
FROM EMPLOYEES E
JOIN DEPARTMENTS D
USING (DEPARTMENT_ID);

/* USING RULE: after USING(DEPARTMENT_ID), select DEPARTMENT_ID, not E.DEPARTMENT_ID. */


/* Q: Show employee_id, department_name, city, country_name. */
SELECT E.EMPLOYEE_ID, D.DEPARTMENT_NAME, L.CITY, C.COUNTRY_NAME
FROM EMPLOYEES E
JOIN DEPARTMENTS D ON D.DEPARTMENT_ID = E.DEPARTMENT_ID
JOIN LOCATIONS L   ON L.LOCATION_ID = D.LOCATION_ID
JOIN COUNTRIES C   ON C.COUNTRY_ID = L.COUNTRY_ID;


/* SELF JOIN
Q: Show employee name and manager name.
*/
SELECT E.FIRST_NAME || ' ' || E.LAST_NAME AS EMPLOYEE_NAME,
       M.FIRST_NAME || ' ' || M.LAST_NAME AS MANAGER_NAME
FROM EMPLOYEES E
JOIN EMPLOYEES M
  ON E.MANAGER_ID = M.EMPLOYEE_ID;


/* LEFT JOIN
Q: Show all employees even if manager is NULL.
*/
SELECT E.LAST_NAME AS EMPLOYEE, M.LAST_NAME AS MANAGER
FROM EMPLOYEES E
LEFT JOIN EMPLOYEES M
  ON E.MANAGER_ID = M.EMPLOYEE_ID;


/* Q: Show every department with employee count, including zero. */
SELECT D.DEPARTMENT_ID, D.DEPARTMENT_NAME,
       COUNT(E.EMPLOYEE_ID) AS EMP_COUNT
FROM DEPARTMENTS D
LEFT JOIN EMPLOYEES E
  ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
GROUP BY D.DEPARTMENT_ID, D.DEPARTMENT_NAME;

/* OUTER JOIN COUNT: use COUNT(E.EMPLOYEE_ID), not COUNT(*), if zero must remain zero. */


/* Q: Match employee salary to JOB_GRADES salary range. */
SELECT E.LAST_NAME, E.SALARY, J.GRADE_LEVEL
FROM EMPLOYEES E
JOIN JOB_GRADES J
  ON E.SALARY BETWEEN J.LOWEST_SAL AND J.HIGHEST_SAL;


/*=============================================================================
2. GROUP BY + HAVING
=============================================================================*/

/* Q: Departments with at least 3 employees and avg salary > 5000. */
SELECT D.DEPARTMENT_ID, D.DEPARTMENT_NAME,
       COUNT(*) EMP_COUNT, AVG(E.SALARY) AVG_SALARY
FROM DEPARTMENTS D
JOIN EMPLOYEES E ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
GROUP BY D.DEPARTMENT_ID, D.DEPARTMENT_NAME
HAVING COUNT(*) >= 3
   AND AVG(E.SALARY) > 5000;

/* WHERE = row filter before grouping. HAVING = group/aggregate filter. */


/*=============================================================================
3. SCALAR + CORRELATED SUBQUERY
=============================================================================*/

/* Q: Employees earning above overall company average. */
SELECT E.EMPLOYEE_ID, E.LAST_NAME, E.SALARY
FROM EMPLOYEES E
WHERE E.SALARY >
      (SELECT AVG(X.SALARY) FROM EMPLOYEES X);


/* DEPT AVG
Q: Employees earning above their own department average.
*/
SELECT E.EMPLOYEE_ID, E.LAST_NAME, E.SALARY, E.DEPARTMENT_ID
FROM EMPLOYEES E
WHERE E.SALARY >
      (
        SELECT AVG(X.SALARY)
        FROM EMPLOYEES X
        WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID
      );


/* Q: Employees earning above own dept avg, but dept has at most 5 employees. */
SELECT E.EMPLOYEE_ID, E.LAST_NAME, E.SALARY
FROM EMPLOYEES E
WHERE E.SALARY >
      (
        SELECT AVG(X.SALARY)
        FROM EMPLOYEES X
        WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID
      )
AND (
        SELECT COUNT(*)
        FROM EMPLOYEES X
        WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID
    ) <= 5;


/*=============================================================================
4. HIGHEST / SECOND HIGHEST / TOP-k
=============================================================================*/

/* Q: Highest-paid employee(s) in each department. */
SELECT E.EMPLOYEE_ID, E.LAST_NAME, E.DEPARTMENT_ID, E.SALARY
FROM EMPLOYEES E
WHERE E.SALARY =
      (
        SELECT MAX(X.SALARY)
        FROM EMPLOYEES X
        WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID
      );


/* SECOND HIGHEST
Q: Second-highest salary employee(s) in each department; allow ties.
*/
SELECT E.EMPLOYEE_ID, E.LAST_NAME, E.DEPARTMENT_ID, E.SALARY
FROM EMPLOYEES E
WHERE (
        SELECT COUNT(DISTINCT X.SALARY)
        FROM EMPLOYEES X
        WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID
          AND X.SALARY > E.SALARY
      ) = 1;


/* Q: Top 3 distinct salary levels including ties. */
SELECT E.EMPLOYEE_ID, E.LAST_NAME, E.SALARY
FROM EMPLOYEES E
WHERE (
        SELECT COUNT(DISTINCT X.SALARY)
        FROM EMPLOYEES X
        WHERE X.SALARY > E.SALARY
      ) < 3
ORDER BY E.SALARY DESC;

/* kth highest DISTINCT value -> COUNT(DISTINCT greater values) = k-1 */


/*=============================================================================
5. EXISTS / NOT EXISTS / EVERY
=============================================================================*/

/* EXISTS
Q: Employees who have a manager using EXISTS.
*/
SELECT E.EMPLOYEE_ID, E.LAST_NAME
FROM EMPLOYEES E
WHERE EXISTS
      (
        SELECT 1
        FROM EMPLOYEES M
        WHERE M.EMPLOYEE_ID = E.MANAGER_ID
      );


/* NOT EXISTS
Q: Employees with no JOB_HISTORY record.
*/
SELECT E.EMPLOYEE_ID, E.LAST_NAME
FROM EMPLOYEES E
WHERE NOT EXISTS
      (
        SELECT 1
        FROM JOB_HISTORY JH
        WHERE JH.EMPLOYEE_ID = E.EMPLOYEE_ID
      );


/* EVERY
Q: Departments where every employee earns > 5000.
*/
SELECT D.DEPARTMENT_ID, D.DEPARTMENT_NAME
FROM DEPARTMENTS D
JOIN EMPLOYEES E ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
GROUP BY D.DEPARTMENT_ID, D.DEPARTMENT_NAME
HAVING MIN(E.SALARY) > 5000;


/* Q: Same EVERY condition using NOT EXISTS. */
SELECT D.DEPARTMENT_ID, D.DEPARTMENT_NAME
FROM DEPARTMENTS D
WHERE EXISTS
      (
        SELECT 1 FROM EMPLOYEES E
        WHERE E.DEPARTMENT_ID = D.DEPARTMENT_ID
      )
AND NOT EXISTS
      (
        SELECT 1 FROM EMPLOYEES E
        WHERE E.DEPARTMENT_ID = D.DEPARTMENT_ID
          AND E.SALARY <= 5000
      );

/* EVERY P <=> NOT EXISTS(row violating P). */
/* Prefer NOT EXISTS over NOT IN when NULL may appear. */


/*=============================================================================
6. ANY ALL
=============================================================================*/

/* ANY ALL
Q: Employees earning more than at least one employee in dept 50.
*/
SELECT E.LAST_NAME, E.SALARY
FROM EMPLOYEES E
WHERE E.SALARY > ANY
      (
        SELECT X.SALARY
        FROM EMPLOYEES X
        WHERE X.DEPARTMENT_ID = 50
          AND X.SALARY IS NOT NULL
      );


/* Q: Employees earning more than every employee in dept 50. */
SELECT E.LAST_NAME, E.SALARY
FROM EMPLOYEES E
WHERE E.SALARY > ALL
      (
        SELECT X.SALARY
        FROM EMPLOYEES X
        WHERE X.DEPARTMENT_ID = 50
          AND X.SALARY IS NOT NULL
      );

/*
= ANY -> IN
> ANY -> > MIN
> ALL -> > MAX
< ANY -> < MAX
< ALL -> < MIN
*/


/*=============================================================================
7. SUBQUERY IN SELECT / FROM / HAVING
=============================================================================*/

/* SELECT SUBQUERY
Q: Show last_name, salary, department_name without JOIN in main query.
*/
SELECT E.LAST_NAME, E.SALARY,
       (
        SELECT D.DEPARTMENT_NAME
        FROM DEPARTMENTS D
        WHERE D.DEPARTMENT_ID = E.DEPARTMENT_ID
       ) AS DEPARTMENT_NAME
FROM EMPLOYEES E;


/* FROM SUBQUERY
Q: Employees earning above dept average using subquery in FROM.
*/
SELECT E.EMPLOYEE_ID, E.LAST_NAME, E.SALARY, S.AVG_SALARY
FROM EMPLOYEES E
JOIN
     (
      SELECT DEPARTMENT_ID, AVG(SALARY) AS AVG_SALARY
      FROM EMPLOYEES
      GROUP BY DEPARTMENT_ID
     ) S
  ON S.DEPARTMENT_ID = E.DEPARTMENT_ID
WHERE E.SALARY > S.AVG_SALARY;


/* Q: Departments whose avg salary > company avg. */
SELECT E.DEPARTMENT_ID, AVG(E.SALARY) AS DEPT_AVG
FROM EMPLOYEES E
GROUP BY E.DEPARTMENT_ID
HAVING AVG(E.SALARY) >
       (SELECT AVG(X.SALARY) FROM EMPLOYEES X);


/* Q: Jobs whose max salary > average of all job maximum salaries. */
SELECT E.JOB_ID, MAX(E.SALARY) AS JOB_MAX
FROM EMPLOYEES E
GROUP BY E.JOB_ID
HAVING MAX(E.SALARY) >
       (
        SELECT AVG(JOB_MAX)
        FROM
             (
              SELECT MAX(SALARY) AS JOB_MAX
              FROM EMPLOYEES
              GROUP BY JOB_ID
             )
       );


/*=============================================================================
8. MULTI-COLUMN SUBQUERY
=============================================================================*/

/* Q: Find employee(s) with maximum salary of their job. */
SELECT E.EMPLOYEE_ID, E.JOB_ID, E.SALARY
FROM EMPLOYEES E
WHERE (E.JOB_ID, E.SALARY) IN
      (
        SELECT X.JOB_ID, MAX(X.SALARY)
        FROM EMPLOYEES X
        GROUP BY X.JOB_ID
      );


/*=============================================================================
9. SET OPERATIONS
=============================================================================*/

/* UNION
Q: Employees either in dept 50 OR salary > 10000.
*/
SELECT EMPLOYEE_ID FROM EMPLOYEES WHERE DEPARTMENT_ID = 50
UNION
SELECT EMPLOYEE_ID FROM EMPLOYEES WHERE SALARY > 10000;


/* INTERSECT
Q: Employees in dept 50 AND salary > 10000.
*/
SELECT EMPLOYEE_ID FROM EMPLOYEES WHERE DEPARTMENT_ID = 50
INTERSECT
SELECT EMPLOYEE_ID FROM EMPLOYEES WHERE SALARY > 10000;


/* MINUS
Q: Employees who are not managers.
*/
SELECT EMPLOYEE_ID FROM EMPLOYEES
MINUS
SELECT MANAGER_ID FROM EMPLOYEES
WHERE MANAGER_ID IS NOT NULL;


/* XOR
Q: Employees satisfying exactly one:
A) dept 50
B) salary > 10000
*/
(
 SELECT EMPLOYEE_ID FROM EMPLOYEES WHERE DEPARTMENT_ID = 50
 MINUS
 SELECT EMPLOYEE_ID FROM EMPLOYEES WHERE SALARY > 10000
)
UNION
(
 SELECT EMPLOYEE_ID FROM EMPLOYEES WHERE SALARY > 10000
 MINUS
 SELECT EMPLOYEE_ID FROM EMPLOYEES WHERE DEPARTMENT_ID = 50
);

/*
UNION = OR, duplicate removed
UNION ALL = keep duplicate
INTERSECT = BOTH
MINUS = A NOT B
XOR = (A-B) UNION (B-A)

SET RULES:
same number of columns
compatible corresponding datatypes
ORDER BY only once at final end
*/


/*=============================================================================
10. CASE / DECODE
=============================================================================*/

/* CASE
Q: Salary label: <5000 C, <10000 B, <15000 A, otherwise A+.
*/
SELECT E.EMPLOYEE_ID, E.SALARY,
       CASE
         WHEN E.SALARY < 5000  THEN 'C'
         WHEN E.SALARY < 10000 THEN 'B'
         WHEN E.SALARY < 15000 THEN 'A'
         ELSE 'A+'
       END AS SALARY_GRADE
FROM EMPLOYEES E;


/* Q: Count high earners (>10000) per department. */
SELECT E.DEPARTMENT_ID,
       SUM(CASE WHEN E.SALARY > 10000 THEN 1 ELSE 0 END) AS HIGH_COUNT
FROM EMPLOYEES E
GROUP BY E.DEPARTMENT_ID;


/* DECODE
Q: Label dept 10 Admin, 20 Marketing, 50 Shipping, else Other.
*/
SELECT E.EMPLOYEE_ID, E.DEPARTMENT_ID,
       DECODE(E.DEPARTMENT_ID,
              10, 'Admin',
              20, 'Marketing',
              50, 'Shipping',
              'Other') AS DEPT_TYPE
FROM EMPLOYEES E;

/* DECODE = equality mapping. Range/complex conditions -> CASE. */


/*=============================================================================
11. WITH / CTE
=============================================================================*/

/* WITH
Q: Compute dept avg/count once; find above-avg employees in depts >5 employees.
*/
WITH DEPT_STATS AS
(
 SELECT DEPARTMENT_ID,
        COUNT(*) AS EMP_COUNT,
        AVG(SALARY) AS AVG_SALARY
 FROM EMPLOYEES
 GROUP BY DEPARTMENT_ID
)
SELECT E.EMPLOYEE_ID, E.LAST_NAME, E.SALARY, S.AVG_SALARY
FROM EMPLOYEES E
JOIN DEPT_STATS S
  ON S.DEPARTMENT_ID = E.DEPARTMENT_ID
WHERE E.SALARY > S.AVG_SALARY
  AND S.EMP_COUNT > 5;


/*=============================================================================
12. SEC-A Q1 STYLE
=============================================================================*/

/*
Q: Find employees earning strictly more than overall average.
Display EMPLOYEE_ID, FULL_NAME, DEPARTMENT_NAME, SALARY.
Order salary descending.
*/
SELECT E.EMPLOYEE_ID,
       E.FIRST_NAME || ' ' || E.LAST_NAME AS FULL_NAME,
       D.DEPARTMENT_NAME,
       E.SALARY
FROM EMPLOYEES E
LEFT JOIN DEPARTMENTS D
  ON D.DEPARTMENT_ID = E.DEPARTMENT_ID
WHERE E.SALARY >
      (SELECT AVG(X.SALARY) FROM EMPLOYEES X)
ORDER BY E.SALARY DESC;


/*=============================================================================
13. SEC-A Q2 STYLE
=============================================================================*/

/*
Q: For each department find second-highest salary employee(s).
Display employee_id, full_name, salary, department_name, job_title.
Exclude departments with fewer than 2 employees.
*/
SELECT E.EMPLOYEE_ID,
       E.FIRST_NAME || ' ' || E.LAST_NAME AS FULL_NAME,
       E.SALARY,
       D.DEPARTMENT_NAME,
       J.JOB_TITLE
FROM EMPLOYEES E
JOIN DEPARTMENTS D ON D.DEPARTMENT_ID = E.DEPARTMENT_ID
JOIN JOBS J        ON J.JOB_ID = E.JOB_ID
WHERE (
        SELECT COUNT(DISTINCT X.SALARY)
        FROM EMPLOYEES X
        WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID
          AND X.SALARY > E.SALARY
      ) = 1
AND (
      SELECT COUNT(*)
      FROM EMPLOYEES X
      WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID
    ) >= 2
ORDER BY D.DEPARTMENT_NAME ASC, E.SALARY DESC;


/*=============================================================================
14. SEC-A Q3 STYLE
=============================================================================*/

/*
Q: Salary > own department average.
Print last_name, salary, department_name.
No JOIN in main query; correlated subquery in WHERE.
*/
SELECT E.LAST_NAME,
       E.SALARY,
       (
        SELECT D.DEPARTMENT_NAME
        FROM DEPARTMENTS D
        WHERE D.DEPARTMENT_ID = E.DEPARTMENT_ID
       ) AS DEPARTMENT_NAME
FROM EMPLOYEES E
WHERE E.SALARY >
      (
       SELECT AVG(X.SALARY)
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID
      );


/*=============================================================================
15. SEC-A Q4 STYLE - INTERSECT
=============================================================================*/

/*
Q: Employees from departments satisfying BOTH using INTERSECT:
1) more than 3 employees
2) avg salary > 6000
Show employee_id, full_name, dept_name, salary,
CASE Top Tier if salary >10000 else Standard Tier.
*/
SELECT E.EMPLOYEE_ID,
       E.FIRST_NAME || ' ' || E.LAST_NAME AS FULL_NAME,
       D.DEPARTMENT_NAME,
       E.SALARY,
       CASE
         WHEN E.SALARY > 10000 THEN 'Top Tier'
         ELSE 'Standard Tier'
       END AS SALARY_TIER
FROM EMPLOYEES E
JOIN DEPARTMENTS D ON D.DEPARTMENT_ID = E.DEPARTMENT_ID
WHERE E.DEPARTMENT_ID IN
      (
       SELECT DEPARTMENT_ID
       FROM EMPLOYEES
       WHERE DEPARTMENT_ID IS NOT NULL
       GROUP BY DEPARTMENT_ID
       HAVING COUNT(*) > 3

       INTERSECT

       SELECT DEPARTMENT_ID
       FROM EMPLOYEES
       WHERE DEPARTMENT_ID IS NOT NULL
       GROUP BY DEPARTMENT_ID
       HAVING AVG(SALARY) > 6000
      )
ORDER BY D.DEPARTMENT_NAME ASC, E.SALARY DESC;


/*=============================================================================
16. ONLINE COMBINED: EMPLOYEE + MANAGER + DEPT AVG
=============================================================================*/

/*
Q: Employee salary > dept avg AND manager salary > company avg.
Show full_name, salary, dept_name.
Label Dept Top Earner if salary >1.5*dept avg, else Dept Above Avg.
*/
SELECT E.FIRST_NAME || ' ' || E.LAST_NAME AS FULL_NAME,
       E.SALARY,
       D.DEPARTMENT_NAME,
       CASE
         WHEN E.SALARY >
              1.5 * (
                     SELECT AVG(X.SALARY)
                     FROM EMPLOYEES X
                     WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID
                    )
         THEN 'Dept Top Earner'
         ELSE 'Dept Above Avg'
       END AS EARNER_TYPE
FROM EMPLOYEES E
JOIN EMPLOYEES M   ON M.EMPLOYEE_ID = E.MANAGER_ID
JOIN DEPARTMENTS D ON D.DEPARTMENT_ID = E.DEPARTMENT_ID
WHERE E.SALARY >
      (
       SELECT AVG(X.SALARY)
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID
      )
AND M.SALARY >
    (SELECT AVG(X.SALARY) FROM EMPLOYEES X);


/*=============================================================================
17. ONLINE COMBINED: SAME CITY AS MANAGER DEPT
=============================================================================*/

/*
Q: employee_id, full_name, department_name where employee department
is in same city as manager department.
*/
SELECT E.EMPLOYEE_ID,
       E.FIRST_NAME || ' ' || E.LAST_NAME AS FULL_NAME,
       ED.DEPARTMENT_NAME
FROM EMPLOYEES E
JOIN EMPLOYEES M    ON M.EMPLOYEE_ID = E.MANAGER_ID
JOIN DEPARTMENTS ED ON ED.DEPARTMENT_ID = E.DEPARTMENT_ID
JOIN LOCATIONS EL   ON EL.LOCATION_ID = ED.LOCATION_ID
JOIN DEPARTMENTS MD ON MD.DEPARTMENT_ID = M.DEPARTMENT_ID
JOIN LOCATIONS ML   ON ML.LOCATION_ID = MD.LOCATION_ID
WHERE EL.CITY = ML.CITY;


/*=============================================================================
18. ONLINE COMBINED: EVERY + JOB_HISTORY + MAX
=============================================================================*/

/*
Q: Departments where:
1) every employee salary >5000
2) at least one employee has JOB_HISTORY
3) dept max salary > company avg
Show dept_name, emp_count, avg_salary,
Elite if dept avg >1.5*company avg else Above Average.
*/
SELECT D.DEPARTMENT_NAME,
       COUNT(*) AS EMP_COUNT,
       AVG(E.SALARY) AS AVG_SALARY,
       CASE
         WHEN AVG(E.SALARY) >
              1.5 * (SELECT AVG(X.SALARY) FROM EMPLOYEES X)
         THEN 'Elite'
         ELSE 'Above Average'
       END AS SALARY_LEVEL
FROM DEPARTMENTS D
JOIN EMPLOYEES E ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
GROUP BY D.DEPARTMENT_ID, D.DEPARTMENT_NAME
HAVING MIN(E.SALARY) > 5000
AND MAX(E.SALARY) >
    (SELECT AVG(X.SALARY) FROM EMPLOYEES X)
AND EXISTS
    (
     SELECT 1
     FROM EMPLOYEES X
     JOIN JOB_HISTORY JH ON JH.EMPLOYEE_ID = X.EMPLOYEE_ID
     WHERE X.DEPARTMENT_ID = D.DEPARTMENT_ID
    );


/*=============================================================================
19. QUESTION WORD -> IDEA
=============================================================================*/

/*
overall/company average      -> scalar AVG subquery
department average           -> correlated AVG by DEPARTMENT_ID
job average                  -> correlated AVG by JOB_ID
dept has > N employees       -> GROUP BY HAVING COUNT(*) > N / correlated COUNT
highest per dept             -> correlated MAX
second-highest               -> COUNT(DISTINCT greater salary)=1
k-th highest                 -> COUNT(DISTINCT greater)=k-1
at least one                 -> EXISTS / ANY
no record                    -> NOT EXISTS
every employee               -> MIN(...) / NOT EXISTS violation
greater than all             -> > ALL / > MAX
greater than at least one    -> > ANY / > MIN
both                         -> AND / INTERSECT
either                       -> OR / UNION
A but not B                  -> MINUS
exactly one A/B              -> XOR
label                        -> CASE / DECODE
reuse statistics             -> WITH
related name/city/country    -> JOIN path
*/


/*=============================================================================
20. ERRORS
=============================================================================*/

/*
1. USING(col) -> do not qualify col in SELECT.
2. LEFT JOIN + WHERE condition on right table can remove NULL rows.
3. Zero-match count -> COUNT(right.id), not COUNT(*).
4. Selected non-aggregate columns -> GROUP BY them.
5. Row condition -> WHERE; group condition -> HAVING.
6. Scalar subquery must return <=1 row.
7. Multi-row -> IN / ANY / ALL.
8. Correlated subquery must reference outer row.
9. Top-k with ties -> COUNT(DISTINCT greater values).
10. NOT IN + NULL danger -> prefer NOT EXISTS.
11. SET: same column count + compatible types.
12. SET ORDER BY -> once at end.
13. CASE -> first TRUE WHEN wins.
14. DECODE -> equality; ranges -> CASE.
15. "more than 5" => >5; "at least 5" => >=5.
*/


/*=============================================================================
21. LAST 20 SECONDS
=============================================================================*/

/*
DEPT AVG:
WHERE E.SALARY > (
 SELECT AVG(X.SALARY)
 FROM EMPLOYEES X
 WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID
)

SECOND HIGHEST:
WHERE (
 SELECT COUNT(DISTINCT X.SALARY)
 FROM EMPLOYEES X
 WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID
 AND X.SALARY > E.SALARY
)=1

NO JOB HISTORY:
WHERE NOT EXISTS (
 SELECT 1 FROM JOB_HISTORY JH
 WHERE JH.EMPLOYEE_ID = E.EMPLOYEE_ID
)

EVERY SALARY >5000:
HAVING MIN(SALARY)>5000

CASE:
CASE WHEN condition THEN 'A' ELSE 'B' END

SET:
OR=UNION | BOTH=INTERSECT | A NOT B=MINUS
*/
