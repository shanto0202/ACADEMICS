/*=============================================================================
JULY 2025 ONLINE-2: A1+A2 COMPLETE SOLUTIONS
=============================================================================*/

-- A1 Q1
-- Find job titles in departments where employees have worked more than
-- 5 years on average. JOBS.MAX_SALARY must be greater than the average
-- MAX_SALARY across all rows of JOBS.
WITH DEPT_STATS AS
(
    SELECT E.DEPARTMENT_ID,
           AVG(MONTHS_BETWEEN(SYSDATE, E.HIRE_DATE) / 12) AS AVG_YEARS
    FROM EMPLOYEES E
    GROUP BY E.DEPARTMENT_ID
)
SELECT DISTINCT J.JOB_TITLE
FROM EMPLOYEES E
JOIN JOBS J
  ON J.JOB_ID = E.JOB_ID
JOIN DEPT_STATS DS
  ON DS.DEPARTMENT_ID = E.DEPARTMENT_ID
WHERE DS.AVG_YEARS > 5
  AND J.MAX_SALARY > (SELECT AVG(X.MAX_SALARY) FROM JOBS X);

-- If a question instead says "maximum salary EARNED by employees in each job",
-- calculate MAX(EMPLOYEES.SALARY) per JOB_ID as shown in JOB_STATS section 11.

-- A1 Q2
-- Employees above their department average, excluding departments with
-- more than 5 employees.
SELECT E.EMPLOYEE_ID,
       E.FIRST_NAME || ' ' || E.LAST_NAME AS FULL_NAME,
       E.SALARY,
       E.DEPARTMENT_ID
FROM EMPLOYEES E
WHERE E.SALARY >
      (SELECT AVG(X.SALARY)
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID)
  AND (SELECT COUNT(*)
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID) <= 5;

-- A1 Q3
-- USA employees who have a manager (EXISTS), have no job history
-- (NOT EXISTS), and earn above their department average.
SELECT E.FIRST_NAME || ' ' || E.LAST_NAME AS FULL_NAME,
       E.SALARY,
       CASE
           WHEN E.SALARY > 1.4 *
                (SELECT AVG(X.SALARY)
                 FROM EMPLOYEES X
                 WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID)
               THEN 'USA Star'
           ELSE 'USA Above'
       END AS EMPLOYEE_LEVEL
FROM EMPLOYEES E
JOIN DEPARTMENTS D
  ON D.DEPARTMENT_ID = E.DEPARTMENT_ID
JOIN LOCATIONS L
  ON L.LOCATION_ID = D.LOCATION_ID
WHERE L.COUNTRY_ID = 'US'
  AND EXISTS
      (SELECT 1
       FROM EMPLOYEES M
       WHERE M.EMPLOYEE_ID = E.MANAGER_ID)
  AND NOT EXISTS
      (SELECT 1
       FROM JOB_HISTORY JH
       WHERE JH.EMPLOYEE_ID = E.EMPLOYEE_ID)
  AND E.SALARY >
      (SELECT AVG(X.SALARY)
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID);

-- A1 Q4
-- Departments where every employee earns more than 5000.
-- Label by comparison of department average with company average.
SELECT D.DEPARTMENT_NAME,
       COUNT(*) AS EMP_COUNT,
       CASE
           WHEN AVG(E.SALARY) > (SELECT AVG(X.SALARY) FROM EMPLOYEES X)
               THEN 'Above'
           ELSE 'Below or Equal'
       END AS SALARY_LEVEL
FROM DEPARTMENTS D
JOIN EMPLOYEES E
  ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
GROUP BY D.DEPARTMENT_ID, D.DEPARTMENT_NAME
HAVING MIN(E.SALARY) > 5000;

-- A1 Q5
-- Employees earning more than the highest salary of at least one other dept.
-- Own department has at least 3 employees; employee has no job history.
SELECT E.EMPLOYEE_ID,
       E.FIRST_NAME || ' ' || E.LAST_NAME AS FULL_NAME,
       D.DEPARTMENT_NAME,
       E.SALARY
FROM EMPLOYEES E
JOIN DEPARTMENTS D
  ON D.DEPARTMENT_ID = E.DEPARTMENT_ID
WHERE E.SALARY > ANY
      (SELECT MAX(X.SALARY)
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID <> E.DEPARTMENT_ID
       GROUP BY X.DEPARTMENT_ID)
  AND (SELECT COUNT(*)
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID) >= 3
  AND NOT EXISTS
      (SELECT 1
       FROM JOB_HISTORY JH
       WHERE JH.EMPLOYEE_ID = E.EMPLOYEE_ID);