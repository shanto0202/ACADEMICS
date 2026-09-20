-- =========================================================
-- QUESTION 1
-- Find all employees who earn strictly more than the overall
-- average salary of the entire company.
-- Display:
-- 1. EMPLOYEE_ID
-- 2. FULL_NAME
-- 3. DEPARTMENT_NAME
-- 4. SALARY
-- Order results by SALARY descending.
-- =========================================================

SELECT EMPLOYEE_ID,
       FIRST_NAME || ' ' || LAST_NAME AS FULL_NAME,
       DEPARTMENT_NAME,
       SALARY
FROM EMPLOYEES
LEFT JOIN DEPARTMENTS USING (DEPARTMENT_ID)
WHERE SALARY > (
    SELECT AVG(SALARY)
    FROM EMPLOYEES
)
ORDER BY SALARY DESC;


-- =========================================================
-- QUESTION 2
-- For each department, find the employee(s) with the
-- second-highest salary.
-- Display employee_id, full name, salary, department_name,
-- and job_title.
-- Exclude departments that have fewer than two employees.
-- Sort by department_name ascending and salary descending.
-- =========================================================

SELECT E.EMPLOYEE_ID,
       E.FIRST_NAME || ' ' || E.LAST_NAME AS FULL_NAME,
       E.SALARY,
       D.DEPARTMENT_NAME,
       J.JOB_TITLE
FROM EMPLOYEES E
JOIN DEPARTMENTS D
ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
JOIN JOBS J
ON E.JOB_ID = J.JOB_ID
WHERE 1 = (
    SELECT COUNT(DISTINCT E2.SALARY)
    FROM EMPLOYEES E2
    WHERE E2.DEPARTMENT_ID = E.DEPARTMENT_ID
      AND E2.SALARY > E.SALARY
)
ORDER BY D.DEPARTMENT_NAME ASC, E.SALARY DESC;


-- =========================================================
-- QUESTION 3
-- Find employees whose salary is higher than the average
-- salary of the department he/she works in.
-- Print employee last name, salary, and department name.
-- You cannot use JOIN in the main query.
-- Use correlated sub-query in WHERE clause.
-- You can use sub-query in SELECT clause to print
-- the department name.
-- =========================================================

SELECT E.LAST_NAME,
       E.SALARY,
       (
           SELECT D.DEPARTMENT_NAME
           FROM DEPARTMENTS D
           WHERE D.DEPARTMENT_ID = E.DEPARTMENT_ID
       ) AS DEPARTMENT_NAME
FROM EMPLOYEES E
WHERE E.SALARY > (
    SELECT AVG(E2.SALARY)
    FROM EMPLOYEES E2
    WHERE E2.DEPARTMENT_ID = E.DEPARTMENT_ID
);


-- =========================================================
-- QUESTION 4
-- Find all employees who belong to departments satisfying
-- BOTH conditions using INTERSECT:
-- 1. Department has more than 3 employees.
-- 2. Department average salary is greater than 6000.
--
-- Display:
-- EMPLOYEE_ID
-- FULL_NAME
-- DEPARTMENT_NAME
-- SALARY
-- SALARY_TIER:
--   'Top Tier' if salary > 10000
--   'Standard Tier' otherwise
--
-- Order by DEPARTMENT_NAME ascending, then SALARY descending.
-- =========================================================

WITH DESIRED_DEPARTMENTS AS (

    SELECT DEPARTMENT_ID
    FROM EMPLOYEES
    GROUP BY DEPARTMENT_ID
    HAVING COUNT(*) > 3

    -- SELECT DISTINCT E.DEPARTMENT_ID
    -- FROM EMPLOYEES E
    -- WHERE (
    --     SELECT COUNT(*)
    --     FROM EMPLOYEES E2
    --     WHERE E2.DEPARTMENT_ID = E.DEPARTMENT_ID
    -- ) > 3

    INTERSECT

    SELECT DEPARTMENT_ID
    FROM EMPLOYEES
    GROUP BY DEPARTMENT_ID
    HAVING AVG(SALARY) > 6000

    -- SELECT DISTINCT E.DEPARTMENT_ID
    -- FROM EMPLOYEES E
    -- WHERE (
    --     SELECT AVG(E2.SALARY)
    --     FROM EMPLOYEES E2
    --     WHERE E2.DEPARTMENT_ID = E.DEPARTMENT_ID
    -- ) > 6000

)

SELECT EMPLOYEE_ID,
       FIRST_NAME || ' ' || LAST_NAME AS FULL_NAME,
       DEPARTMENT_NAME,
       SALARY,
       CASE
           WHEN SALARY > 10000 THEN 'Top Tier'
           ELSE 'Standard Tier'
       END AS SALARY_TIER
FROM EMPLOYEES
JOIN DEPARTMENTS USING (DEPARTMENT_ID)
WHERE DEPARTMENT_ID IN (
    SELECT DEPARTMENT_ID
    FROM DESIRED_DEPARTMENTS
)
ORDER BY DEPARTMENT_NAME ASC, SALARY DESC;