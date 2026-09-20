
/*=============================================================================
JULY 2025 ONLINE-2: C1+C2 COMPLETE SOLUTIONS
=============================================================================*/

-- C1 Q1
-- Above department average in departments with more than 4 employees.
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
       WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID) > 4;

-- C1 Q2
-- Salary above manager salary OR above department average.
-- If both are true, "Higher Than Manager" gets priority in CASE.
SELECT E.EMPLOYEE_ID,
       E.FIRST_NAME || ' ' || E.LAST_NAME AS FULL_NAME,
       E.SALARY,
       CASE
           WHEN E.SALARY > M.SALARY THEN 'Higher Than Manager'
           ELSE 'Above Dept Avg'
       END AS EMPLOYEE_TYPE
FROM EMPLOYEES E
LEFT JOIN EMPLOYEES M
  ON M.EMPLOYEE_ID = E.MANAGER_ID
WHERE E.SALARY > M.SALARY
   OR E.SALARY >
      (SELECT AVG(X.SALARY)
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID);

-- C1 Q3
-- Employee beats department average and manager beats company average.
SELECT E.FIRST_NAME || ' ' || E.LAST_NAME AS FULL_NAME,
       E.SALARY,
       D.DEPARTMENT_NAME,
       CASE
           WHEN E.SALARY > 1.5 *
                (SELECT AVG(X.SALARY)
                 FROM EMPLOYEES X
                 WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID)
               THEN 'Dept Top Earner'
           ELSE 'Dept Above Avg'
       END AS EMPLOYEE_LEVEL
FROM EMPLOYEES E
JOIN EMPLOYEES M
  ON M.EMPLOYEE_ID = E.MANAGER_ID
JOIN DEPARTMENTS D
  ON D.DEPARTMENT_ID = E.DEPARTMENT_ID
WHERE E.SALARY >
      (SELECT AVG(X.SALARY)
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID)
  AND M.SALARY > (SELECT AVG(X.SALARY) FROM EMPLOYEES X);

-- C1 Q4
-- Employee department is in the same city as manager department.
SELECT E.EMPLOYEE_ID,
       E.FIRST_NAME || ' ' || E.LAST_NAME AS FULL_NAME,
       ED.DEPARTMENT_NAME
FROM EMPLOYEES E
JOIN EMPLOYEES M
  ON M.EMPLOYEE_ID = E.MANAGER_ID
JOIN DEPARTMENTS ED
  ON ED.DEPARTMENT_ID = E.DEPARTMENT_ID
JOIN LOCATIONS EL
  ON EL.LOCATION_ID = ED.LOCATION_ID
JOIN DEPARTMENTS MD
  ON MD.DEPARTMENT_ID = M.DEPARTMENT_ID
JOIN LOCATIONS ML
  ON ML.LOCATION_ID = MD.LOCATION_ID
WHERE EL.CITY = ML.CITY;

-- C1 Q5
-- Every employee earns >5000; at least one employee has job history;
-- department max salary > company average.
SELECT D.DEPARTMENT_NAME,
       COUNT(*) AS EMP_COUNT,
       ROUND(AVG(E.SALARY), 2) AS AVG_SALARY,
       CASE
           WHEN AVG(E.SALARY) > 1.5 *
                (SELECT AVG(X.SALARY) FROM EMPLOYEES X)
               THEN 'Elite'
           ELSE 'Above Average'
       END AS SALARY_LEVEL
FROM DEPARTMENTS D
JOIN EMPLOYEES E
  ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
GROUP BY D.DEPARTMENT_ID, D.DEPARTMENT_NAME
HAVING MIN(E.SALARY) > 5000
   AND MAX(E.SALARY) > (SELECT AVG(X.SALARY) FROM EMPLOYEES X)
   AND EXISTS
       (SELECT 1
        FROM EMPLOYEES EH
        JOIN JOB_HISTORY JH
          ON JH.EMPLOYEE_ID = EH.EMPLOYEE_ID
        WHERE EH.DEPARTMENT_ID = D.DEPARTMENT_ID);
