/*=============================================================================
JULY 2025 ONLINE-2: B1+B2 COMPLETE SOLUTIONS
=============================================================================*/

-- B1 Q1
-- Department managers in Toronto/Oxford whose department average is above
-- the overall company average.
SELECT M.EMPLOYEE_ID,
       M.FIRST_NAME || ' ' || M.LAST_NAME AS MANAGER_NAME,
       D.DEPARTMENT_NAME
FROM DEPARTMENTS D
JOIN EMPLOYEES M
  ON M.EMPLOYEE_ID = D.MANAGER_ID
JOIN LOCATIONS L
  ON L.LOCATION_ID = D.LOCATION_ID
WHERE L.CITY IN ('Toronto', 'Oxford')
  AND (SELECT AVG(X.SALARY)
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID = D.DEPARTMENT_ID)
      >
      (SELECT AVG(X.SALARY)
       FROM EMPLOYEES X);

-- B1 Q2
-- Employees in departments with >5 employees AND salary > company average.
SELECT E.EMPLOYEE_ID,
       E.FIRST_NAME || ' ' || E.LAST_NAME AS FULL_NAME,
       E.SALARY,
       E.DEPARTMENT_ID
FROM EMPLOYEES E
WHERE (SELECT COUNT(*)
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID) > 5
  AND E.SALARY > (SELECT AVG(X.SALARY) FROM EMPLOYEES X);

-- B1 Q3
-- Employees in departments that have managers, with no job history,
-- and salary above department average.
SELECT E.FIRST_NAME || ' ' || E.LAST_NAME AS FULL_NAME,
       E.SALARY,
       D.DEPARTMENT_NAME,
       CASE
           WHEN E.SALARY > 1.7 *
                (SELECT AVG(X.SALARY)
                 FROM EMPLOYEES X
                 WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID)
               THEN 'Stable High Earner'
           ELSE 'Dept Above Avg'
       END AS EMPLOYEE_LEVEL
FROM EMPLOYEES E
JOIN DEPARTMENTS D
  ON D.DEPARTMENT_ID = E.DEPARTMENT_ID
WHERE D.MANAGER_ID IS NOT NULL
  AND NOT EXISTS
      (SELECT 1
       FROM JOB_HISTORY JH
       WHERE JH.EMPLOYEE_ID = E.EMPLOYEE_ID)
  AND E.SALARY >
      (SELECT AVG(X.SALARY)
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID);

-- B1 Q4
-- Department has >5 employees OR job minimum salary is >10000.
SELECT E.EMPLOYEE_ID,
       E.FIRST_NAME,
       E.LAST_NAME,
       E.DEPARTMENT_ID,
       E.JOB_ID,
       E.SALARY
FROM EMPLOYEES E
JOIN JOBS J
  ON J.JOB_ID = E.JOB_ID
WHERE (SELECT COUNT(*)
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID) > 5
   OR J.MIN_SALARY > 10000;

-- B1 Q5
-- Exactly one condition: large department XOR high job minimum salary.
SELECT E.EMPLOYEE_ID,
       E.FIRST_NAME || ' ' || E.LAST_NAME AS FULL_NAME,
       E.DEPARTMENT_ID,
       E.JOB_ID,
       E.SALARY
FROM EMPLOYEES E
JOIN JOBS J
  ON J.JOB_ID = E.JOB_ID
WHERE CASE
          WHEN (SELECT COUNT(*)
                FROM EMPLOYEES X
                WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID) > 5
          THEN 1 ELSE 0
      END
    + CASE
          WHEN J.MIN_SALARY > 10000
          THEN 1 ELSE 0
      END = 1;
