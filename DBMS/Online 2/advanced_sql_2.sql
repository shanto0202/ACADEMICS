/*
===============================================================================
ORACLE ADVANCED SQL LAB TEST CHEATSHEET
HR Schema: JOIN + GROUP BY + SUBQUERY + EXISTS + CASE + SET OPERATIONS + WITH

Prepared from:
- Sukarna Barua, A Brief Introduction to Oracle SQL/PL-SQL
  Chapters 4-7 and 11 (printed pages 36-58 and 82-89)
- CSE 215 SQL lectures on joins, aggregation, subqueries, and set operations
- July 2025 CSE 216 Online-2: A1+A2, B1+B2, and C1+C2

IMPORTANT:
- Oracle SQL syntax is used throughout.
- Examples assume the standard Oracle HR schema.
- Do not run this entire file at once. Copy only the required query block.
- Read the question carefully: row condition -> WHERE; group condition -> HAVING.
- Give every table a short alias in multi-table queries.
===============================================================================
*/


/*=============================================================================
0. HR SCHEMA MAP - MOST USED PATHS
=============================================================================*/

-- Employee -> department
-- EMPLOYEES.DEPARTMENT_ID = DEPARTMENTS.DEPARTMENT_ID

-- Employee -> job
-- EMPLOYEES.JOB_ID = JOBS.JOB_ID

-- Department -> location -> country -> region
-- DEPARTMENTS.LOCATION_ID = LOCATIONS.LOCATION_ID
-- LOCATIONS.COUNTRY_ID = COUNTRIES.COUNTRY_ID
-- COUNTRIES.REGION_ID = REGIONS.REGION_ID

-- Employee -> manager: both are rows of EMPLOYEES
-- EMPLOYEES.MANAGER_ID = manager.EMPLOYEE_ID

-- Employee -> previous job records
-- EMPLOYEES.EMPLOYEE_ID = JOB_HISTORY.EMPLOYEE_ID

-- Common full-name expression
SELECT E.FIRST_NAME || ' ' || E.LAST_NAME AS FULL_NAME
FROM EMPLOYEES E;


/*=============================================================================
1. JOIN TEMPLATES
=============================================================================*/

-- Inner join: only matching rows.
SELECT E.EMPLOYEE_ID,
       E.FIRST_NAME,
       D.DEPARTMENT_NAME
FROM EMPLOYEES E
JOIN DEPARTMENTS D
  ON D.DEPARTMENT_ID = E.DEPARTMENT_ID;

-- USING is shorter when both columns have the same name.
-- Do not write E.DEPARTMENT_ID in SELECT after USING; use DEPARTMENT_ID.
SELECT E.EMPLOYEE_ID,
       DEPARTMENT_ID,
       D.DEPARTMENT_NAME
FROM EMPLOYEES E
JOIN DEPARTMENTS D
USING (DEPARTMENT_ID);

-- Employee + department + location + country.
SELECT E.EMPLOYEE_ID,
       D.DEPARTMENT_NAME,
       L.CITY,
       C.COUNTRY_NAME
FROM EMPLOYEES E
JOIN DEPARTMENTS D
  ON D.DEPARTMENT_ID = E.DEPARTMENT_ID
JOIN LOCATIONS L
  ON L.LOCATION_ID = D.LOCATION_ID
JOIN COUNTRIES C
  ON C.COUNTRY_ID = L.COUNTRY_ID;

-- Self join: employee and manager.
-- Inner join excludes the top employee whose MANAGER_ID is NULL.
SELECT E.EMPLOYEE_ID,
       E.FIRST_NAME || ' ' || E.LAST_NAME AS EMPLOYEE_NAME,
       M.FIRST_NAME || ' ' || M.LAST_NAME AS MANAGER_NAME
FROM EMPLOYEES E
JOIN EMPLOYEES M
  ON M.EMPLOYEE_ID = E.MANAGER_ID;

-- Left join keeps employees even when they have no manager.
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME AS EMPLOYEE,
       M.LAST_NAME AS MANAGER
FROM EMPLOYEES E
LEFT JOIN EMPLOYEES M
  ON M.EMPLOYEE_ID = E.MANAGER_ID;

-- Keep all departments, including departments with zero employees.
-- COUNT(E.EMPLOYEE_ID) is required; COUNT(*) would return 1 for an empty dept.
SELECT D.DEPARTMENT_ID,
       D.DEPARTMENT_NAME,
       COUNT(E.EMPLOYEE_ID) AS EMP_COUNT
FROM DEPARTMENTS D
LEFT JOIN EMPLOYEES E
  ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
GROUP BY D.DEPARTMENT_ID, D.DEPARTMENT_NAME;

-- Non-equi join example: match salary to a salary range.
SELECT E.LAST_NAME,
       E.SALARY,
       G.GRADE_LEVEL
FROM EMPLOYEES E
JOIN JOB_GRADES G
  ON E.SALARY BETWEEN G.LOWEST_SAL AND G.HIGHEST_SAL;


/*=============================================================================
2. JOIN + GROUP BY + HAVING
=============================================================================*/

-- Department statistics with department name.
SELECT D.DEPARTMENT_ID,
       D.DEPARTMENT_NAME,
       COUNT(*) AS EMP_COUNT,
       ROUND(AVG(E.SALARY), 2) AS AVG_SALARY,
       MAX(E.SALARY) AS MAX_SALARY
FROM DEPARTMENTS D
JOIN EMPLOYEES E
  ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
GROUP BY D.DEPARTMENT_ID, D.DEPARTMENT_NAME
HAVING COUNT(*) >= 3
   AND AVG(E.SALARY) > 5000;

-- WHERE filters individual rows before grouping.
-- HAVING filters complete groups after aggregation.
SELECT E.DEPARTMENT_ID,
       COUNT(*) AS HIGH_EARNER_COUNT
FROM EMPLOYEES E
WHERE E.SALARY > 5000
GROUP BY E.DEPARTMENT_ID
HAVING COUNT(*) >= 3;

-- All selected non-aggregate columns must appear in GROUP BY.
-- Correct: both ID and name are grouped.
SELECT D.DEPARTMENT_ID,
       D.DEPARTMENT_NAME,
       COUNT(*) AS EMP_COUNT
FROM DEPARTMENTS D
JOIN EMPLOYEES E
  ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
GROUP BY D.DEPARTMENT_ID, D.DEPARTMENT_NAME;


/*=============================================================================
3. SUBQUERY OUTPUT TYPES AND WHERE OPERATORS
=============================================================================*/

-- Scalar subquery: must return exactly one value; use =, >, <, >=, <=, <>.
SELECT E.EMPLOYEE_ID, E.LAST_NAME, E.SALARY
FROM EMPLOYEES E
WHERE E.SALARY >
      (SELECT AVG(X.SALARY)
       FROM EMPLOYEES X);

-- Multi-row, one-column subquery: use IN, ANY, or ALL.
SELECT E.EMPLOYEE_ID, E.LAST_NAME, E.DEPARTMENT_ID
FROM EMPLOYEES E
WHERE E.DEPARTMENT_ID IN
      (SELECT D.DEPARTMENT_ID
       FROM DEPARTMENTS D
       WHERE D.LOCATION_ID IN (1700, 1800));

-- IN means equal to at least one returned value.
-- = ANY has the same basic meaning as IN.

-- Multi-column comparison.
SELECT E.EMPLOYEE_ID, E.JOB_ID, E.SALARY
FROM EMPLOYEES E
WHERE (E.JOB_ID, E.SALARY) IN
      (SELECT X.JOB_ID, MAX(X.SALARY)
       FROM EMPLOYEES X
       GROUP BY X.JOB_ID);

-- Subquery in SELECT: it must return at most one value for each outer row.
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       (SELECT D.DEPARTMENT_NAME
        FROM DEPARTMENTS D
        WHERE D.DEPARTMENT_ID = E.DEPARTMENT_ID) AS DEPARTMENT_NAME
FROM EMPLOYEES E;

-- Subquery in FROM: creates a temporary result table.
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       E.SALARY,
       S.AVG_SALARY
FROM EMPLOYEES E
JOIN (SELECT DEPARTMENT_ID,
             AVG(SALARY) AS AVG_SALARY
      FROM EMPLOYEES
      GROUP BY DEPARTMENT_ID) S
  ON S.DEPARTMENT_ID = E.DEPARTMENT_ID
WHERE E.SALARY > S.AVG_SALARY;


/*=============================================================================
4. CORRELATED SUBQUERIES
=============================================================================*/

-- Correlated subquery: uses the current row of the outer query.
-- Employees earning above their own department average.
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       E.SALARY,
       E.DEPARTMENT_ID
FROM EMPLOYEES E
WHERE E.SALARY >
      (SELECT AVG(X.SALARY)
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID);

-- Employees earning more than at least three other employees.
SELECT E.EMPLOYEE_ID, E.LAST_NAME, E.SALARY
FROM EMPLOYEES E
WHERE (SELECT COUNT(*)
       FROM EMPLOYEES X
       WHERE X.SALARY < E.SALARY) >= 3;

-- Highest-paid employee(s) in each department.
SELECT E.EMPLOYEE_ID, E.LAST_NAME, E.DEPARTMENT_ID, E.SALARY
FROM EMPLOYEES E
WHERE E.SALARY =
      (SELECT MAX(X.SALARY)
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID);

-- Department size as a correlated scalar value.
SELECT E.EMPLOYEE_ID, E.LAST_NAME, E.DEPARTMENT_ID
FROM EMPLOYEES E
WHERE (SELECT COUNT(*)
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID) > 5;


/*=============================================================================
5. EXISTS AND NOT EXISTS
=============================================================================*/

-- EXISTS checks whether at least one matching row exists.
-- Departments having at least one employee.
SELECT D.DEPARTMENT_ID, D.DEPARTMENT_NAME
FROM DEPARTMENTS D
WHERE EXISTS
      (SELECT 1
       FROM EMPLOYEES E
       WHERE E.DEPARTMENT_ID = D.DEPARTMENT_ID);

-- Employees who really have a manager, explicitly using EXISTS.
SELECT E.EMPLOYEE_ID, E.LAST_NAME
FROM EMPLOYEES E
WHERE EXISTS
      (SELECT 1
       FROM EMPLOYEES M
       WHERE M.EMPLOYEE_ID = E.MANAGER_ID);

-- Employees with at least one JOB_HISTORY record.
SELECT E.EMPLOYEE_ID, E.LAST_NAME
FROM EMPLOYEES E
WHERE EXISTS
      (SELECT 1
       FROM JOB_HISTORY JH
       WHERE JH.EMPLOYEE_ID = E.EMPLOYEE_ID);

-- Employees with no JOB_HISTORY record.
SELECT E.EMPLOYEE_ID, E.LAST_NAME
FROM EMPLOYEES E
WHERE NOT EXISTS
      (SELECT 1
       FROM JOB_HISTORY JH
       WHERE JH.EMPLOYEE_ID = E.EMPLOYEE_ID);

-- Department-level existence check.
-- Departments containing at least one employee with job history.
SELECT D.DEPARTMENT_ID, D.DEPARTMENT_NAME
FROM DEPARTMENTS D
WHERE EXISTS
      (SELECT 1
       FROM EMPLOYEES E
       JOIN JOB_HISTORY JH
         ON JH.EMPLOYEE_ID = E.EMPLOYEE_ID
       WHERE E.DEPARTMENT_ID = D.DEPARTMENT_ID);

-- NULL trap:
-- NOT IN can return no rows if its subquery contains NULL.
-- Prefer correlated NOT EXISTS for "no related row" questions.
SELECT E.EMPLOYEE_ID, E.LAST_NAME
FROM EMPLOYEES E
WHERE NOT EXISTS
      (SELECT 1
       FROM JOB_HISTORY JH
       WHERE JH.EMPLOYEE_ID = E.EMPLOYEE_ID);


/*=============================================================================
6. ANY AND ALL
=============================================================================*/

-- Greater than at least one value returned by the subquery.
SELECT E.EMPLOYEE_ID, E.LAST_NAME, E.SALARY
FROM EMPLOYEES E
WHERE E.SALARY > ANY
      (SELECT X.SALARY
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID = 50);

-- Greater than every value returned by the subquery.
SELECT E.EMPLOYEE_ID, E.LAST_NAME, E.SALARY
FROM EMPLOYEES E
WHERE E.SALARY > ALL
      (SELECT X.SALARY
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID = 50);

-- Memory shortcuts for a non-empty subquery without problematic NULL values:
-- > ANY(values)  means > MIN(values)
-- > ALL(values)  means > MAX(values)
-- < ANY(values)  means < MAX(values)
-- < ALL(values)  means < MIN(values)
-- = ANY(values)  means IN(values)

-- Salary greater than the highest salary of at least one OTHER department.
SELECT E.EMPLOYEE_ID, E.LAST_NAME, E.SALARY
FROM EMPLOYEES E
WHERE E.SALARY > ANY
      (SELECT MAX(X.SALARY)
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID <> E.DEPARTMENT_ID
       GROUP BY X.DEPARTMENT_ID);


/*=============================================================================
7. "EVERY", "ALL MEMBERS", AND UNIVERSAL CONDITIONS
=============================================================================*/

-- Every employee in the department earns more than 5000.
-- Inner join means an empty department is not included.
SELECT D.DEPARTMENT_ID,
       D.DEPARTMENT_NAME,
       COUNT(*) AS EMP_COUNT
FROM DEPARTMENTS D
JOIN EMPLOYEES E
  ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
GROUP BY D.DEPARTMENT_ID, D.DEPARTMENT_NAME
HAVING MIN(E.SALARY) > 5000;

-- General "every row satisfies condition" pattern.
-- Count of all rows must equal count of rows satisfying the condition.
SELECT E.DEPARTMENT_ID
FROM EMPLOYEES E
GROUP BY E.DEPARTMENT_ID
HAVING COUNT(*) = SUM(CASE WHEN E.SALARY > 5000 THEN 1 ELSE 0 END);

-- Same logic using double NOT EXISTS:
-- choose departments for which no violating employee exists.
SELECT D.DEPARTMENT_ID, D.DEPARTMENT_NAME
FROM DEPARTMENTS D
WHERE EXISTS
      (SELECT 1
       FROM EMPLOYEES E
       WHERE E.DEPARTMENT_ID = D.DEPARTMENT_ID)
  AND NOT EXISTS
      (SELECT 1
       FROM EMPLOYEES E
       WHERE E.DEPARTMENT_ID = D.DEPARTMENT_ID
         AND E.SALARY <= 5000);


/*=============================================================================
8. CASE AND CONDITIONAL AGGREGATION
=============================================================================*/

-- Searched CASE: first true WHEN wins.
SELECT E.EMPLOYEE_ID,
       E.SALARY,
       CASE
           WHEN E.SALARY > 15000 THEN 'Elite'
           WHEN E.SALARY > 10000 THEN 'High'
           ELSE 'Regular'
       END AS SALARY_LEVEL
FROM EMPLOYEES E;

-- Compare department average with company average.
SELECT E.DEPARTMENT_ID,
       ROUND(AVG(E.SALARY), 2) AS AVG_SALARY,
       CASE
           WHEN AVG(E.SALARY) > (SELECT AVG(X.SALARY) FROM EMPLOYEES X)
               THEN 'Above'
           ELSE 'Below or Equal'
       END AS SALARY_LEVEL
FROM EMPLOYEES E
GROUP BY E.DEPARTMENT_ID;

-- Conditional aggregation: count multiple categories in one query.
SELECT E.DEPARTMENT_ID,
       SUM(CASE WHEN E.SALARY > 10000 THEN 1 ELSE 0 END) AS HIGH_COUNT,
       SUM(CASE WHEN E.SALARY <= 10000 THEN 1 ELSE 0 END) AS OTHER_COUNT
FROM EMPLOYEES E
GROUP BY E.DEPARTMENT_ID;

-- Count with CASE. COUNT ignores NULL.
SELECT E.DEPARTMENT_ID,
       COUNT(CASE WHEN E.SALARY > 10000 THEN 1 END) AS HIGH_COUNT
FROM EMPLOYEES E
GROUP BY E.DEPARTMENT_ID;


/*=============================================================================
9. AND, OR, AND EXACTLY ONE CONDITION (XOR)
=============================================================================*/

-- OR: include a row when A, B, or both are true.
SELECT E.EMPLOYEE_ID, E.DEPARTMENT_ID, E.JOB_ID, E.SALARY
FROM EMPLOYEES E
JOIN JOBS J
  ON J.JOB_ID = E.JOB_ID
WHERE (SELECT COUNT(*)
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID) > 5
   OR J.MIN_SALARY > 10000;

-- AND: both conditions must be true.
SELECT E.EMPLOYEE_ID, E.DEPARTMENT_ID, E.JOB_ID, E.SALARY
FROM EMPLOYEES E
JOIN JOBS J
  ON J.JOB_ID = E.JOB_ID
WHERE (SELECT COUNT(*)
       FROM EMPLOYEES X
       WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID) > 5
  AND J.MIN_SALARY > 10000;

-- XOR: exactly one is true; both true and both false are excluded.
-- Convert each Boolean condition to 1 or 0, then require total = 1.
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


/*=============================================================================
10. SET OPERATIONS
=============================================================================*/

-- Both SELECT statements must return the same number of compatible columns.
-- UNION: combine and remove duplicates.
SELECT E.EMPLOYEE_ID, E.JOB_ID
FROM EMPLOYEES E
UNION
SELECT JH.EMPLOYEE_ID, JH.JOB_ID
FROM JOB_HISTORY JH;

-- UNION ALL: combine and keep duplicates; usually faster.
SELECT E.EMPLOYEE_ID, E.JOB_ID
FROM EMPLOYEES E
UNION ALL
SELECT JH.EMPLOYEE_ID, JH.JOB_ID
FROM JOB_HISTORY JH;

-- INTERSECT: rows present in both results.
SELECT E.EMPLOYEE_ID, E.JOB_ID
FROM EMPLOYEES E
INTERSECT
SELECT JH.EMPLOYEE_ID, JH.JOB_ID
FROM JOB_HISTORY JH;

-- MINUS: rows in the first result but not the second result.
SELECT E.EMPLOYEE_ID
FROM EMPLOYEES E
MINUS
SELECT JH.EMPLOYEE_ID
FROM JOB_HISTORY JH;

-- OR can often be expressed using UNION.
SELECT E.EMPLOYEE_ID
FROM EMPLOYEES E
WHERE E.DEPARTMENT_ID = 50
UNION
SELECT E.EMPLOYEE_ID
FROM EMPLOYEES E
WHERE E.SALARY > 10000;

-- AND can often be expressed using INTERSECT.
SELECT E.EMPLOYEE_ID
FROM EMPLOYEES E
WHERE E.DEPARTMENT_ID = 50
INTERSECT
SELECT E.EMPLOYEE_ID
FROM EMPLOYEES E
WHERE E.SALARY > 10000;

-- A but not B can often be expressed using MINUS.
SELECT E.EMPLOYEE_ID
FROM EMPLOYEES E
WHERE E.DEPARTMENT_ID = 50
MINUS
SELECT E.EMPLOYEE_ID
FROM EMPLOYEES E
WHERE E.SALARY > 10000;

-- ORDER BY is written once at the end of the complete set expression.
SELECT E.EMPLOYEE_ID, E.JOB_ID
FROM EMPLOYEES E
UNION
SELECT JH.EMPLOYEE_ID, JH.JOB_ID
FROM JOB_HISTORY JH
ORDER BY 1, 2;


/*=============================================================================
11. WITH CLAUSE (CTE) - REUSABLE STATISTICS
=============================================================================*/

-- Department statistics used like a temporary table.
WITH DEPT_STATS AS
(
    SELECT E.DEPARTMENT_ID,
           COUNT(*) AS EMP_COUNT,
           AVG(E.SALARY) AS AVG_SALARY,
           MIN(E.SALARY) AS MIN_SALARY,
           MAX(E.SALARY) AS MAX_SALARY,
           AVG(MONTHS_BETWEEN(SYSDATE, E.HIRE_DATE) / 12) AS AVG_YEARS
    FROM EMPLOYEES E
    GROUP BY E.DEPARTMENT_ID
)
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       E.SALARY,
       S.EMP_COUNT,
       ROUND(S.AVG_SALARY, 2) AS DEPT_AVG
FROM EMPLOYEES E
JOIN DEPT_STATS S
  ON S.DEPARTMENT_ID = E.DEPARTMENT_ID
WHERE E.SALARY > S.AVG_SALARY
  AND S.EMP_COUNT > 5;

-- Multiple CTEs: department, job, and company statistics.
WITH DEPT_STATS AS
(
    SELECT DEPARTMENT_ID,
           COUNT(*) AS EMP_COUNT,
           AVG(SALARY) AS AVG_SALARY,
           MAX(SALARY) AS MAX_SALARY
    FROM EMPLOYEES
    GROUP BY DEPARTMENT_ID
),
JOB_STATS AS
(
    SELECT JOB_ID,
           COUNT(*) AS EMP_COUNT,
           AVG(SALARY) AS AVG_SALARY,
           MAX(SALARY) AS MAX_SALARY
    FROM EMPLOYEES
    GROUP BY JOB_ID
),
COMPANY_STATS AS
(
    SELECT AVG(SALARY) AS AVG_SALARY
    FROM EMPLOYEES
)
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       E.SALARY,
       DS.AVG_SALARY AS DEPT_AVG,
       JS.AVG_SALARY AS JOB_AVG,
       CS.AVG_SALARY AS COMPANY_AVG
FROM EMPLOYEES E
JOIN DEPT_STATS DS
  ON DS.DEPARTMENT_ID = E.DEPARTMENT_ID
JOIN JOB_STATS JS
  ON JS.JOB_ID = E.JOB_ID
CROSS JOIN COMPANY_STATS CS;


/*=============================================================================
12. TOP-N AND RANKING PATTERNS
=============================================================================*/

-- Top 3 rows after sorting. Oracle 12c+.
SELECT E.EMPLOYEE_ID, E.LAST_NAME, E.SALARY
FROM EMPLOYEES E
ORDER BY E.SALARY DESC
FETCH FIRST 3 ROWS ONLY;

-- Top 3 DISTINCT salary levels, including salary ties.
SELECT EMPLOYEE_ID, LAST_NAME, SALARY
FROM
(
    SELECT E.EMPLOYEE_ID,
           E.LAST_NAME,
           E.SALARY,
           DENSE_RANK() OVER (ORDER BY E.SALARY DESC) AS SALARY_RANK
    FROM EMPLOYEES E
)
WHERE SALARY_RANK <= 3
ORDER BY SALARY DESC;

-- Highest-paid employee(s) for every job.
SELECT E.EMPLOYEE_ID, E.LAST_NAME, E.JOB_ID, E.SALARY
FROM EMPLOYEES E
WHERE E.SALARY =
      (SELECT MAX(X.SALARY)
       FROM EMPLOYEES X
       WHERE X.JOB_ID = E.JOB_ID);

/*=============================================================================
13. EXTRA ORACLE OBJECTS: VIEW, SEQUENCE, AND INDEX
=============================================================================*/

-- Simple view.
CREATE OR REPLACE VIEW HIGH_SALARY_EMPLOYEES AS
SELECT EMPLOYEE_ID, FIRST_NAME, LAST_NAME, SALARY, DEPARTMENT_ID
FROM EMPLOYEES
WHERE SALARY > 10000;

-- Read-only view.
CREATE OR REPLACE VIEW DEPT_SALARY_SUMMARY AS
SELECT DEPARTMENT_ID,
       COUNT(*) AS EMP_COUNT,
       AVG(SALARY) AS AVG_SALARY
FROM EMPLOYEES
GROUP BY DEPARTMENT_ID
WITH READ ONLY;

-- Sequence for generating numeric IDs.
CREATE SEQUENCE TEST_EMP_SEQ
START WITH 1000
INCREMENT BY 1
NOCACHE
NOCYCLE;

-- NEXTVAL generates the next number; CURRVAL returns the current session value.
SELECT TEST_EMP_SEQ.NEXTVAL FROM DUAL;
SELECT TEST_EMP_SEQ.CURRVAL FROM DUAL;

-- Index. Do not create another index on a primary-key/unique column unnecessarily.
CREATE INDEX IDX_EMP_DEPT
ON EMPLOYEES(DEPARTMENT_ID);

-- Remove objects when explicitly required.
DROP VIEW HIGH_SALARY_EMPLOYEES;
DROP SEQUENCE TEST_EMP_SEQ;
DROP INDEX IDX_EMP_DEPT;


/*=============================================================================
14. DML USING SUBQUERIES
=============================================================================*/

-- Insert rows produced by a query.
INSERT INTO EMPLOYEE_BACKUP
       (EMPLOYEE_ID, FIRST_NAME, LAST_NAME, SALARY, DEPARTMENT_ID)
SELECT E.EMPLOYEE_ID,
       E.FIRST_NAME,
       E.LAST_NAME,
       E.SALARY,
       E.DEPARTMENT_ID
FROM EMPLOYEES E
WHERE E.SALARY > (SELECT AVG(X.SALARY) FROM EMPLOYEES X);

-- Update rows selected by a subquery.
UPDATE EMPLOYEES E
SET SALARY = E.SALARY * 1.10
WHERE E.DEPARTMENT_ID IN
      (SELECT X.DEPARTMENT_ID
       FROM EMPLOYEES X
       GROUP BY X.DEPARTMENT_ID
       HAVING AVG(X.SALARY) < 6000);

-- Correlated update: assign each row its department average.
-- Run only on a practice copy, not on the original HR table.
UPDATE EMPLOYEE_COPY E
SET SALARY =
    (SELECT AVG(X.SALARY)
     FROM EMPLOYEE_COPY X
     WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID)
WHERE E.DEPARTMENT_ID IS NOT NULL;

-- Delete employees having no job-history record from a practice table.
DELETE FROM EMPLOYEE_COPY E
WHERE NOT EXISTS
      (SELECT 1
       FROM JOB_HISTORY JH
       WHERE JH.EMPLOYEE_ID = E.EMPLOYEE_ID);

-- Transaction control.
COMMIT;
ROLLBACK;


/*=============================================================================
15. LEETCODE MYSQL -> ORACLE QUICK CONVERSION
=============================================================================*/

-- MySQL LIMIT 1 OFFSET 1
-- Oracle 12c+: OFFSET 1 ROW FETCH NEXT 1 ROW ONLY
SELECT DISTINCT E.SALARY
FROM EMPLOYEES E
ORDER BY E.SALARY DESC
OFFSET 1 ROW FETCH NEXT 1 ROW ONLY;

-- MySQL IFNULL(value, replacement) -> Oracle NVL(value, replacement)
SELECT NVL(E.COMMISSION_PCT, 0) AS COMMISSION
FROM EMPLOYEES E;

-- MySQL CONCAT(a, b, c) -> Oracle a || b || c
SELECT E.FIRST_NAME || ' ' || E.LAST_NAME AS FULL_NAME
FROM EMPLOYEES E;

-- MySQL YEAR(date_col) -> Oracle EXTRACT(YEAR FROM date_col)
SELECT EXTRACT(YEAR FROM E.HIRE_DATE) AS HIRE_YEAR
FROM EMPLOYEES E;

-- MySQL DATEDIFF(date1, date2) -> Oracle date1 - date2, in days.
SELECT TRUNC(SYSDATE - E.HIRE_DATE) AS DAYS_WORKED
FROM EMPLOYEES E;

-- MySQL boolean IF(condition, a, b) -> Oracle CASE.
SELECT E.SALARY,
       CASE WHEN E.SALARY > 10000 THEN 'High' ELSE 'Regular' END AS CATEGORY
FROM EMPLOYEES E;


/*=============================================================================
16. FAST QUESTION-TO-SQL DECISION GUIDE
=============================================================================*/

-- "Show department/job/location name"       -> JOIN the required table.
-- "His/her manager"                         -> self JOIN EMPLOYEES.
-- "Above department average"                -> correlated AVG subquery.
-- "Department has more than N employees"    -> COUNT(*) correlated or HAVING.
-- "No history / no related row"             -> NOT EXISTS.
-- "Has a manager/history/related row"        -> EXISTS.
-- "At least one returned value"              -> ANY or EXISTS.
-- "Greater than everybody"                   -> > ALL or > MAX.
-- "Every employee satisfies..."              -> HAVING MIN(...) or NOT EXISTS violation.
-- "Exactly one of A/B"                       -> CASE(A)+CASE(B)=1.
-- "Combine two result sets"                  -> UNION / UNION ALL.
-- "Common to both result sets"               -> INTERSECT.
-- "First result excluding second"            -> MINUS.
-- "Reuse calculated statistics"              -> WITH clause / FROM subquery.
-- "Output a label"                           -> CASE in SELECT.
-- "Filter individual rows"                   -> WHERE.
-- "Filter aggregate groups"                  -> HAVING.


/*=============================================================================
17. FINAL ERROR CHECKLIST
=============================================================================*/

-- 1. ORA-00979: selected non-aggregate column is missing from GROUP BY.
-- 2. ORA-01427: scalar subquery returned multiple rows; use IN/ANY/ALL or fix it.
-- 3. Missing join condition causes a Cartesian product and duplicate-looking rows.
-- 4. = NULL is wrong; use IS NULL or IS NOT NULL.
-- 5. NOT IN is dangerous when the subquery can return NULL; prefer NOT EXISTS.
-- 6. COUNT(column) ignores NULL; COUNT(*) counts rows.
-- 7. LEFT JOIN + condition on right table in WHERE may become an inner join.
-- 8. UNION branches need the same number of compatible columns.
-- 9. ORDER BY goes at the end of a set-operation query.
-- 10. CASE returns one value; it does not filter rows unless used in a condition.
-- 11. A correlated subquery must connect inner alias to outer alias.
-- 12. Use DISTINCT only when duplicate removal is logically required.
-- 13. Use MONTHS_BETWEEN(SYSDATE, HIRE_DATE) / 12 for years in Oracle.
-- 14. Verify > versus >= and "more than N" versus "at least N".
-- 15. Before UPDATE or DELETE, run the same WHERE clause with SELECT first.
/*=============================================================================
18. ADDENDUM SCOPE
=============================================================================*/

/*
Added mainly for:
- Sukarna Barua Chapter 5  : JOINS
- Sukarna Barua Chapter 6  : SUBQUERIES
- Sukarna Barua Chapter 7  : SET OPERATIONS
- Sukarna Barua Chapter 11 : DECODE, CASE, WITH
- January 2026 Sec-A online question style
- July 2025 Advanced SQL online patterns

Goal:
- Keep reusable patterns, not long explanations.
- Prefer Oracle HR-schema syntax.
- When a question changes only a number/name/threshold, edit the marked parts.
*/


/*=============================================================================
19. CHAPTER 5 EXTRA: USING vs ON
=============================================================================*/

-- USING:
-- Use when the equality join column has the SAME NAME in both tables.
-- After USING, use the common column WITHOUT table qualifier.
SELECT E.EMPLOYEE_ID,
       DEPARTMENT_ID,
       D.DEPARTMENT_NAME
FROM EMPLOYEES E
JOIN DEPARTMENTS D
USING (DEPARTMENT_ID);

-- Wrong after USING:
-- SELECT E.DEPARTMENT_ID ...

-- ON:
-- Use for different column names, self join, non-equi join,
-- or whenever the join condition is more complex.
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       D.DEPARTMENT_NAME
FROM EMPLOYEES E
JOIN DEPARTMENTS D
  ON E.DEPARTMENT_ID = D.DEPARTMENT_ID;


/*=============================================================================
20. CHAPTER 5 EXTRA: LEFT / RIGHT OUTER JOIN
=============================================================================*/

-- LEFT JOIN: keep all rows from LEFT table.
-- Show every department, including departments with zero employees.
SELECT D.DEPARTMENT_ID,
       D.DEPARTMENT_NAME,
       COUNT(E.EMPLOYEE_ID) AS EMP_COUNT
FROM DEPARTMENTS D
LEFT JOIN EMPLOYEES E
  ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
GROUP BY D.DEPARTMENT_ID, D.DEPARTMENT_NAME;

-- RIGHT JOIN: keep all rows from RIGHT table.
-- Show every job, including jobs currently held by nobody.
SELECT J.JOB_ID,
       J.JOB_TITLE,
       COUNT(E.EMPLOYEE_ID) AS EMP_COUNT
FROM EMPLOYEES E
RIGHT JOIN JOBS J
  ON E.JOB_ID = J.JOB_ID
GROUP BY J.JOB_ID, J.JOB_TITLE;

-- Equivalent style: swap table order and use LEFT JOIN.
SELECT J.JOB_ID,
       J.JOB_TITLE,
       COUNT(E.EMPLOYEE_ID) AS EMP_COUNT
FROM JOBS J
LEFT JOIN EMPLOYEES E
  ON E.JOB_ID = J.JOB_ID
GROUP BY J.JOB_ID, J.JOB_TITLE;

-- IMPORTANT:
-- With OUTER JOIN, condition on the optional/right table in WHERE may remove NULL rows.
-- Put matching/filter condition inside ON when zero-match rows must remain.

-- Keep all departments; count only employees with salary > 10000.
SELECT D.DEPARTMENT_ID,
       D.DEPARTMENT_NAME,
       COUNT(E.EMPLOYEE_ID) AS HIGH_EARNERS
FROM DEPARTMENTS D
LEFT JOIN EMPLOYEES E
  ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
 AND E.SALARY > 10000
GROUP BY D.DEPARTMENT_ID, D.DEPARTMENT_NAME;


/*=============================================================================
21. CHAPTER 5 EXTRA: COUNT(*) vs COUNT(column) WITH OUTER JOIN
=============================================================================*/

-- For each employee, count how many employees he/she manages.
-- Employees managing nobody must show 0.
SELECT E1.EMPLOYEE_ID,
       E1.LAST_NAME,
       COUNT(E2.EMPLOYEE_ID) AS TOTAL_MANAGED
FROM EMPLOYEES E1
LEFT JOIN EMPLOYEES E2
  ON E2.MANAGER_ID = E1.EMPLOYEE_ID
GROUP BY E1.EMPLOYEE_ID, E1.LAST_NAME
ORDER BY TOTAL_MANAGED;

-- DO NOT replace COUNT(E2.EMPLOYEE_ID) with COUNT(*).
-- LEFT JOIN creates one NULL-extended row for a manager with no matches.
-- COUNT(*) counts that row as 1; COUNT(E2.EMPLOYEE_ID) ignores its NULL.


/*=============================================================================
22. CHAPTER 5 EXTRA: SELF JOIN
=============================================================================*/

-- Employee + manager.
SELECT E.EMPLOYEE_ID,
       E.FIRST_NAME || ' ' || E.LAST_NAME AS EMPLOYEE_NAME,
       M.FIRST_NAME || ' ' || M.LAST_NAME AS MANAGER_NAME
FROM EMPLOYEES E
JOIN EMPLOYEES M
  ON E.MANAGER_ID = M.EMPLOYEE_ID;

-- Keep employee even if manager is NULL.
SELECT E.EMPLOYEE_ID,
       E.FIRST_NAME || ' ' || E.LAST_NAME AS EMPLOYEE_NAME,
       M.FIRST_NAME || ' ' || M.LAST_NAME AS MANAGER_NAME
FROM EMPLOYEES E
LEFT JOIN EMPLOYEES M
  ON E.MANAGER_ID = M.EMPLOYEE_ID;

-- Count employees earning more than current employee.
SELECT E1.EMPLOYEE_ID,
       E1.LAST_NAME,
       COUNT(E2.EMPLOYEE_ID) AS HIGHER_SALARY_COUNT
FROM EMPLOYEES E1
LEFT JOIN EMPLOYEES E2
  ON E2.SALARY > E1.SALARY
GROUP BY E1.EMPLOYEE_ID, E1.LAST_NAME;


/*=============================================================================
23. CHAPTER 5 EXTRA: NON-EQUI JOIN
=============================================================================*/

-- Generic non-equi self join.
-- Pair each employee with employees earning more.
SELECT E1.LAST_NAME AS EMPLOYEE,
       E2.LAST_NAME AS HIGHER_PAID_EMPLOYEE
FROM EMPLOYEES E1
JOIN EMPLOYEES E2
  ON E1.SALARY < E2.SALARY;

-- If a JOB_GRADES(LOWEST_SAL,HIGHEST_SAL,GRADE_LEVEL) table is supplied:
SELECT E.LAST_NAME,
       E.SALARY,
       J.GRADE_LEVEL
FROM EMPLOYEES E
JOIN JOB_GRADES J
  ON E.SALARY BETWEEN J.LOWEST_SAL AND J.HIGHEST_SAL;


/*=============================================================================
24. CHAPTER 5 EXTRA: LONG JOIN PATHS
=============================================================================*/

-- Employee -> Department -> Location -> Country -> Region
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       D.DEPARTMENT_NAME,
       L.CITY,
       C.COUNTRY_NAME,
       R.REGION_NAME
FROM EMPLOYEES E
JOIN DEPARTMENTS D
  ON D.DEPARTMENT_ID = E.DEPARTMENT_ID
JOIN LOCATIONS L
  ON L.LOCATION_ID = D.LOCATION_ID
JOIN COUNTRIES C
  ON C.COUNTRY_ID = L.COUNTRY_ID
JOIN REGIONS R
  ON R.REGION_ID = C.REGION_ID;

-- MEMORY:
-- Need a column from another table? Join a path until that table is reached.
-- Once joined, any column of that joined table may be selected.


/*=============================================================================
25. CHAPTER 6: SCALAR vs MULTI-ROW vs MULTI-COLUMN SUBQUERY
=============================================================================*/

-- SCALAR: one value -> =, >, <, >=, <=, <>
SELECT E.EMPLOYEE_ID, E.LAST_NAME, E.SALARY
FROM EMPLOYEES E
WHERE E.SALARY >
      (SELECT AVG(X.SALARY)
       FROM EMPLOYEES X);

-- MULTI-ROW, ONE COLUMN -> IN / ANY / ALL
SELECT E.EMPLOYEE_ID, E.LAST_NAME, E.DEPARTMENT_ID
FROM EMPLOYEES E
WHERE E.DEPARTMENT_ID IN
      (
          SELECT D.DEPARTMENT_ID
          FROM DEPARTMENTS D
          WHERE D.LOCATION_ID IN (1700, 1800)
      );

-- MULTI-COLUMN comparison.
-- Highest-paid employee(s) in each department.
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       E.DEPARTMENT_ID,
       E.SALARY
FROM EMPLOYEES E
WHERE (E.DEPARTMENT_ID, E.SALARY) IN
      (
          SELECT X.DEPARTMENT_ID,
                 MAX(X.SALARY)
          FROM EMPLOYEES X
          GROUP BY X.DEPARTMENT_ID
      );


/*=============================================================================
26. CHAPTER 6: MULTIPLE SUBQUERIES IN ONE QUESTION
=============================================================================*/

-- Above own department average AND department has at most 5 employees.
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       E.SALARY,
       E.DEPARTMENT_ID
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

-- Above overall company average AND department has >= 3 employees.
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       E.SALARY
FROM EMPLOYEES E
WHERE E.SALARY >
      (SELECT AVG(X.SALARY) FROM EMPLOYEES X)
  AND E.DEPARTMENT_ID IN
      (
          SELECT X.DEPARTMENT_ID
          FROM EMPLOYEES X
          GROUP BY X.DEPARTMENT_ID
          HAVING COUNT(*) >= 3
      );


/*=============================================================================
27. CHAPTER 6: CORRELATED SUBQUERY - CORE PATTERNS
=============================================================================*/

-- Above own department average.
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       E.SALARY,
       E.DEPARTMENT_ID
FROM EMPLOYEES E
WHERE E.SALARY >
      (
          SELECT AVG(X.SALARY)
          FROM EMPLOYEES X
          WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID
      );

-- Above own job average.
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       E.JOB_ID,
       E.SALARY
FROM EMPLOYEES E
WHERE E.SALARY >
      (
          SELECT AVG(X.SALARY)
          FROM EMPLOYEES X
          WHERE X.JOB_ID = E.JOB_ID
      );

-- Department size condition per employee.
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       E.DEPARTMENT_ID
FROM EMPLOYEES E
WHERE (
          SELECT COUNT(*)
          FROM EMPLOYEES X
          WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID
      ) > 5;

-- More salary than at least three other employees.
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       E.SALARY
FROM EMPLOYEES E
WHERE (
          SELECT COUNT(*)
          FROM EMPLOYEES X
          WHERE X.SALARY < E.SALARY
      ) >= 3;


/*=============================================================================
28. CHAPTER 6: HIGHEST / SECOND-HIGHEST / TOP-k WITHOUT WINDOW FUNCTIONS
=============================================================================*/

-- Highest salary in each department.
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       E.DEPARTMENT_ID,
       E.SALARY
FROM EMPLOYEES E
WHERE E.SALARY =
      (
          SELECT MAX(X.SALARY)
          FROM EMPLOYEES X
          WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID
      );

-- SECOND-HIGHEST DISTINCT salary in each department.
-- EXACTLY ONE distinct salary is greater.
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       E.DEPARTMENT_ID,
       E.SALARY
FROM EMPLOYEES E
WHERE (
          SELECT COUNT(DISTINCT X.SALARY)
          FROM EMPLOYEES X
          WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID
            AND X.SALARY > E.SALARY
      ) = 1;

-- kth-highest DISTINCT salary in a group:
-- COUNT(DISTINCT greater_salary) = k - 1

-- Top 3 DISTINCT salary levels in the company, including ties.
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       E.SALARY
FROM EMPLOYEES E
WHERE (
          SELECT COUNT(DISTINCT X.SALARY)
          FROM EMPLOYEES X
          WHERE X.SALARY > E.SALARY
      ) < 3
ORDER BY E.SALARY DESC;


/*=============================================================================
29. SEC-A ONLINE EXACT PATTERN: SECOND-HIGHEST PER DEPARTMENT
=============================================================================*/

-- Reusable for January 2026 Sec-A style.
-- Includes department and job names, keeps salary ties.
SELECT E.EMPLOYEE_ID,
       E.FIRST_NAME || ' ' || E.LAST_NAME AS FULL_NAME,
       E.SALARY,
       D.DEPARTMENT_NAME,
       J.JOB_TITLE
FROM EMPLOYEES E
JOIN DEPARTMENTS D
  ON D.DEPARTMENT_ID = E.DEPARTMENT_ID
JOIN JOBS J
  ON J.JOB_ID = E.JOB_ID
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
ORDER BY D.DEPARTMENT_NAME ASC,
         E.SALARY DESC;


/*=============================================================================
30. CHAPTER 6: EXISTS / NOT EXISTS
=============================================================================*/

-- EXISTS = at least one matching row.
SELECT D.DEPARTMENT_ID,
       D.DEPARTMENT_NAME
FROM DEPARTMENTS D
WHERE EXISTS
      (
          SELECT 1
          FROM EMPLOYEES E
          WHERE E.DEPARTMENT_ID = D.DEPARTMENT_ID
      );

-- Employee has a manager, explicitly with EXISTS.
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME
FROM EMPLOYEES E
WHERE EXISTS
      (
          SELECT 1
          FROM EMPLOYEES M
          WHERE M.EMPLOYEE_ID = E.MANAGER_ID
      );

-- Employee has NO JOB_HISTORY.
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME
FROM EMPLOYEES E
WHERE NOT EXISTS
      (
          SELECT 1
          FROM JOB_HISTORY JH
          WHERE JH.EMPLOYEE_ID = E.EMPLOYEE_ID
      );

-- Highest in department using NOT EXISTS:
-- Keep E if no same-department employee earns more.
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       E.DEPARTMENT_ID,
       E.SALARY
FROM EMPLOYEES E
WHERE NOT EXISTS
      (
          SELECT 1
          FROM EMPLOYEES X
          WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID
            AND X.SALARY > E.SALARY
      );


/*=============================================================================
31. CHAPTER 6: "EVERY EMPLOYEE..." / UNIVERSAL CONDITION
=============================================================================*/

-- "Every employee earns > 5000"
-- Method 1: MIN.
SELECT D.DEPARTMENT_ID,
       D.DEPARTMENT_NAME,
       COUNT(*) AS EMP_COUNT
FROM DEPARTMENTS D
JOIN EMPLOYEES E
  ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
GROUP BY D.DEPARTMENT_ID, D.DEPARTMENT_NAME
HAVING MIN(E.SALARY) > 5000;

-- Method 2: no violating row exists.
SELECT D.DEPARTMENT_ID,
       D.DEPARTMENT_NAME
FROM DEPARTMENTS D
WHERE EXISTS
      (
          SELECT 1
          FROM EMPLOYEES E
          WHERE E.DEPARTMENT_ID = D.DEPARTMENT_ID
      )
  AND NOT EXISTS
      (
          SELECT 1
          FROM EMPLOYEES E
          WHERE E.DEPARTMENT_ID = D.DEPARTMENT_ID
            AND E.SALARY <= 5000
      );

-- General memory:
-- EVERY row satisfies P
-- <=> NOT EXISTS(row that violates P)


/*=============================================================================
32. CHAPTER 6: ANY / ALL
=============================================================================*/

-- > ANY = greater than AT LEAST ONE returned value.
SELECT E.LAST_NAME,
       E.SALARY
FROM EMPLOYEES E
WHERE E.SALARY > ANY
      (
          SELECT X.SALARY
          FROM EMPLOYEES X
          WHERE X.DEPARTMENT_ID = 80
            AND X.SALARY IS NOT NULL
      );

-- > ALL = greater than EVERY returned value.
SELECT E.LAST_NAME,
       E.SALARY
FROM EMPLOYEES E
WHERE E.SALARY > ALL
      (
          SELECT X.SALARY
          FROM EMPLOYEES X
          WHERE X.DEPARTMENT_ID = 80
            AND X.SALARY IS NOT NULL
      );

-- Useful mental conversions for NON-EMPTY, non-NULL result sets:
-- = ANY  <=> IN
-- > ANY  <=> > MIN
-- > ALL  <=> > MAX
-- < ANY  <=> < MAX
-- < ALL  <=> < MIN

-- "Salary is greater than the highest salary of at least one other department."
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       E.SALARY
FROM EMPLOYEES E
WHERE E.SALARY > ANY
      (
          SELECT MAX(X.SALARY)
          FROM EMPLOYEES X
          WHERE X.DEPARTMENT_ID <> E.DEPARTMENT_ID
          GROUP BY X.DEPARTMENT_ID
      );


/*=============================================================================
33. CHAPTER 6: SUBQUERY IN SELECT
=============================================================================*/

-- Scalar subquery in SELECT:
-- must return at most one value for each outer row.
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       E.SALARY,
       (
           SELECT D.DEPARTMENT_NAME
           FROM DEPARTMENTS D
           WHERE D.DEPARTMENT_ID = E.DEPARTMENT_ID
       ) AS DEPARTMENT_NAME
FROM EMPLOYEES E;

-- January 2026 Sec-A style:
-- no JOIN in main query, correlated WHERE + scalar SELECT subquery.
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
34. CHAPTER 6: SUBQUERY IN FROM
=============================================================================*/

-- Subquery in FROM behaves like a temporary result table.
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       E.SALARY,
       S.AVG_SALARY
FROM EMPLOYEES E
JOIN
     (
         SELECT DEPARTMENT_ID,
                AVG(SALARY) AS AVG_SALARY
         FROM EMPLOYEES
         GROUP BY DEPARTMENT_ID
     ) S
  ON S.DEPARTMENT_ID = E.DEPARTMENT_ID
WHERE E.SALARY > S.AVG_SALARY;

-- Department statistics in FROM.
SELECT D.DEPARTMENT_NAME,
       S.EMP_COUNT,
       S.AVG_SALARY,
       S.MAX_SALARY
FROM DEPARTMENTS D
JOIN
     (
         SELECT DEPARTMENT_ID,
                COUNT(*) AS EMP_COUNT,
                AVG(SALARY) AS AVG_SALARY,
                MAX(SALARY) AS MAX_SALARY
         FROM EMPLOYEES
         GROUP BY DEPARTMENT_ID
     ) S
  ON S.DEPARTMENT_ID = D.DEPARTMENT_ID;


/*=============================================================================
35. CHAPTER 6: SUBQUERY IN HAVING
=============================================================================*/

-- Department average > company average.
SELECT E.DEPARTMENT_ID,
       AVG(E.SALARY) AS DEPT_AVG
FROM EMPLOYEES E
GROUP BY E.DEPARTMENT_ID
HAVING AVG(E.SALARY) >
       (
           SELECT AVG(X.SALARY)
           FROM EMPLOYEES X
       );

-- Job maximum > average of all job maximums.
SELECT E.JOB_ID,
       MAX(E.SALARY) AS JOB_MAX
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

-- Pattern:
-- aggregate(current group)
-- OP
-- (SELECT aggregate( grouped-aggregate ) FROM (...GROUP BY...))


/*=============================================================================
36. JULY ONLINE STYLE: MANAGER + DEPT AVG + COMPANY AVG
=============================================================================*/

-- Employee salary > own dept avg
-- AND manager salary > company avg.
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
JOIN EMPLOYEES M
  ON M.EMPLOYEE_ID = E.MANAGER_ID
JOIN DEPARTMENTS D
  ON D.DEPARTMENT_ID = E.DEPARTMENT_ID
WHERE E.SALARY >
      (
          SELECT AVG(X.SALARY)
          FROM EMPLOYEES X
          WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID
      )
  AND M.SALARY >
      (
          SELECT AVG(X.SALARY)
          FROM EMPLOYEES X
      );


/*=============================================================================
37. JULY ONLINE STYLE: SAME CITY AS MANAGER'S DEPARTMENT
=============================================================================*/

-- Employee department and manager department can differ.
-- Compare their LOCATION -> CITY.
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


/*=============================================================================
38. JULY ONLINE STYLE: EVERY + EXISTS + GROUP CONDITION
=============================================================================*/

-- Department conditions:
-- 1) every employee earns > 5000
-- 2) at least one employee has JOB_HISTORY
-- 3) department max salary > company average
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
JOIN EMPLOYEES E
  ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
GROUP BY D.DEPARTMENT_ID, D.DEPARTMENT_NAME
HAVING MIN(E.SALARY) > 5000
   AND MAX(E.SALARY) >
       (SELECT AVG(X.SALARY) FROM EMPLOYEES X)
   AND EXISTS
       (
           SELECT 1
           FROM EMPLOYEES X
           JOIN JOB_HISTORY JH
             ON JH.EMPLOYEE_ID = X.EMPLOYEE_ID
           WHERE X.DEPARTMENT_ID = D.DEPARTMENT_ID
       );


/*=============================================================================
39. CHAPTER 7: SET OPERATIONS - CORE
=============================================================================*/

-- UNION: A or B; duplicate rows removed.
SELECT EMPLOYEE_ID
FROM EMPLOYEES
WHERE DEPARTMENT_ID = 50
UNION
SELECT EMPLOYEE_ID
FROM EMPLOYEES
WHERE SALARY > 10000;

-- UNION ALL: A + B; duplicates kept.
SELECT EMPLOYEE_ID
FROM EMPLOYEES
WHERE DEPARTMENT_ID = 50
UNION ALL
SELECT EMPLOYEE_ID
FROM EMPLOYEES
WHERE SALARY > 10000;

-- INTERSECT: common rows.
SELECT EMPLOYEE_ID
FROM EMPLOYEES
WHERE DEPARTMENT_ID = 50
INTERSECT
SELECT EMPLOYEE_ID
FROM EMPLOYEES
WHERE SALARY > 10000;

-- MINUS: A but not B.
SELECT EMPLOYEE_ID
FROM EMPLOYEES
WHERE DEPARTMENT_ID = 50
MINUS
SELECT EMPLOYEE_ID
FROM EMPLOYEES
WHERE SALARY > 10000;

-- Memory:
-- OR      -> UNION
-- AND     -> INTERSECT
-- A NOT B -> MINUS


/*=============================================================================
40. CHAPTER 7: SET OPERATION RULES
=============================================================================*/

-- RULE 1: same number of selected columns.
-- RULE 2: corresponding columns must have compatible data types.
-- RULE 3: final output column names come from FIRST SELECT.
-- RULE 4: ORDER BY goes once, at the end of the whole set expression.
-- RULE 5: use parentheses when mixing set operators to make intended grouping clear.

SELECT EMPLOYEE_ID,
       JOB_ID
FROM EMPLOYEES
UNION
SELECT EMPLOYEE_ID,
       JOB_ID
FROM JOB_HISTORY
ORDER BY 1, 2;


/*=============================================================================
41. CHAPTER 7: TYPE CONVERSION IN SET OPERATIONS
=============================================================================*/

-- Example assumes EMPLOYEES2.JOB_ID has NUMBER type.
-- EMPLOYEES.JOB_ID is character, so convert corresponding branch.
SELECT LAST_NAME,
       JOB_ID,
       SALARY
FROM EMPLOYEES
UNION ALL
SELECT LAST_NAME,
       TO_CHAR(JOB_ID),
       SALARY
FROM EMPLOYEES2;

-- Typed placeholder if one branch does not naturally have a value.
SELECT EMPLOYEE_ID,
       JOB_ID,
       TO_CHAR(NULL) AS SOURCE_NOTE
FROM EMPLOYEES
UNION ALL
SELECT EMPLOYEE_ID,
       JOB_ID,
       'HISTORY' AS SOURCE_NOTE
FROM JOB_HISTORY;


/*=============================================================================
42. CHAPTER 7: XOR WITH SET OPERATIONS
=============================================================================*/

-- Exactly one of A or B:
-- (A MINUS B) UNION (B MINUS A)

(
    SELECT EMPLOYEE_ID
    FROM EMPLOYEES
    WHERE DEPARTMENT_ID = 50

    MINUS

    SELECT EMPLOYEE_ID
    FROM EMPLOYEES
    WHERE SALARY > 10000
)
UNION
(
    SELECT EMPLOYEE_ID
    FROM EMPLOYEES
    WHERE SALARY > 10000

    MINUS

    SELECT EMPLOYEE_ID
    FROM EMPLOYEES
    WHERE DEPARTMENT_ID = 50
);


/*=============================================================================
43. SEC-A ONLINE EXACT PATTERN: INTERSECT DEPARTMENT CONDITIONS
=============================================================================*/

-- Find departments satisfying BOTH:
-- A) more than 3 employees
-- B) average salary > 6000
-- Then print employees of those departments.

SELECT E.EMPLOYEE_ID,
       E.FIRST_NAME || ' ' || E.LAST_NAME AS FULL_NAME,
       D.DEPARTMENT_NAME,
       E.SALARY,
       CASE
           WHEN E.SALARY > 10000 THEN 'Top Tier'
           ELSE 'Standard Tier'
       END AS SALARY_TIER
FROM EMPLOYEES E
JOIN DEPARTMENTS D
  ON D.DEPARTMENT_ID = E.DEPARTMENT_ID
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
ORDER BY D.DEPARTMENT_NAME ASC,
         E.SALARY DESC;


/*=============================================================================
44. CHAPTER 11: DECODE
=============================================================================*/

-- General:
-- DECODE(expr,
--        match1, result1,
--        match2, result2,
--        ...,
--        default)

-- Equality mapping.
SELECT E.EMPLOYEE_ID,
       E.DEPARTMENT_ID,
       DECODE(E.DEPARTMENT_ID,
              10, 'Admin',
              20, 'Marketing',
              50, 'Shipping',
              'Other') AS DEPT_TYPE
FROM EMPLOYEES E;

-- DECODE is equality-oriented.
-- For range conditions, transform the expression into buckets.
SELECT E.FIRST_NAME,
       E.SALARY,
       DECODE(FLOOR(E.SALARY / 5000),
              0, 'C',
              1, 'B',
              2, 'A',
              'A+') AS SALARY_GRADE
FROM EMPLOYEES E
ORDER BY E.SALARY DESC;

-- Detect whether JOB_TITLE contains MANAGER.
SELECT J.JOB_ID,
       J.JOB_TITLE,
       DECODE(INSTR(UPPER(J.JOB_TITLE), 'MANAGER'),
              0, 'Not a manager',
              'Manager') AS TYPE
FROM JOBS J;

-- No default -> NULL if no match.
-- Keep result/default expressions type-compatible.


/*=============================================================================
45. CHAPTER 11: SIMPLE CASE vs SEARCHED CASE
=============================================================================*/

-- SIMPLE CASE: one expression compared with fixed values.
SELECT E.EMPLOYEE_ID,
       E.DEPARTMENT_ID,
       CASE E.DEPARTMENT_ID
           WHEN 10 THEN 'Admin'
           WHEN 20 THEN 'Marketing'
           WHEN 50 THEN 'Shipping'
           ELSE 'Other'
       END AS DEPT_TYPE
FROM EMPLOYEES E;

-- SEARCHED CASE: each WHEN contains a Boolean condition.
SELECT E.EMPLOYEE_ID,
       E.SALARY,
       CASE
           WHEN E.SALARY < 5000  THEN 'C'
           WHEN E.SALARY < 10000 THEN 'B'
           WHEN E.SALARY < 15000 THEN 'A'
           ELSE 'A+'
       END AS SALARY_GRADE
FROM EMPLOYEES E;

-- CASE checks top-to-bottom.
-- First TRUE WHEN wins.


/*=============================================================================
46. CHAPTER 11: CASE IN GROUP BY
=============================================================================*/

-- Group by a computed grade.
SELECT CASE
           WHEN SALARY < 5000  THEN 'C'
           WHEN SALARY < 10000 THEN 'B'
           WHEN SALARY < 15000 THEN 'A'
           ELSE 'A+'
       END AS SALARY_GRADE,
       COUNT(*) AS TOTAL
FROM EMPLOYEES
GROUP BY CASE
             WHEN SALARY < 5000  THEN 'C'
             WHEN SALARY < 10000 THEN 'B'
             WHEN SALARY < 15000 THEN 'A'
             ELSE 'A+'
         END
ORDER BY SALARY_GRADE;


/*=============================================================================
47. CHAPTER 11: CONDITIONAL AGGREGATION
=============================================================================*/

-- Count categories using SUM(CASE).
SELECT E.DEPARTMENT_ID,
       SUM(CASE WHEN E.SALARY > 10000 THEN 1 ELSE 0 END) AS HIGH_COUNT,
       SUM(CASE WHEN E.SALARY <= 10000 THEN 1 ELSE 0 END) AS OTHER_COUNT
FROM EMPLOYEES E
GROUP BY E.DEPARTMENT_ID;

-- Same style using COUNT(CASE); COUNT ignores NULL.
SELECT E.DEPARTMENT_ID,
       COUNT(CASE WHEN E.SALARY > 10000 THEN 1 END) AS HIGH_COUNT
FROM EMPLOYEES E
GROUP BY E.DEPARTMENT_ID;

-- Multiple salary grade counts per department.
SELECT E.DEPARTMENT_ID,
       COUNT(CASE WHEN E.SALARY < 5000 THEN 1 END) AS C_COUNT,
       COUNT(CASE WHEN E.SALARY >= 5000
                   AND E.SALARY < 10000 THEN 1 END) AS B_COUNT,
       COUNT(CASE WHEN E.SALARY >= 10000
                   AND E.SALARY < 15000 THEN 1 END) AS A_COUNT,
       COUNT(CASE WHEN E.SALARY >= 15000 THEN 1 END) AS A_PLUS_COUNT
FROM EMPLOYEES E
GROUP BY E.DEPARTMENT_ID;


/*=============================================================================
48. CHAPTER 11: WITH CLAUSE
=============================================================================*/

-- One reusable CTE.
WITH DEPT_STATS AS
(
    SELECT DEPARTMENT_ID,
           COUNT(*) AS EMP_COUNT,
           AVG(SALARY) AS AVG_SALARY,
           MAX(SALARY) AS MAX_SALARY
    FROM EMPLOYEES
    GROUP BY DEPARTMENT_ID
)
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       E.SALARY,
       S.EMP_COUNT,
       S.AVG_SALARY
FROM EMPLOYEES E
JOIN DEPT_STATS S
  ON S.DEPARTMENT_ID = E.DEPARTMENT_ID
WHERE E.SALARY > S.AVG_SALARY
  AND S.EMP_COUNT > 5;

-- Multiple CTEs.
WITH
DEPT_STATS AS
(
    SELECT DEPARTMENT_ID,
           COUNT(*) AS EMP_COUNT,
           AVG(SALARY) AS AVG_SALARY
    FROM EMPLOYEES
    GROUP BY DEPARTMENT_ID
),
COMPANY_STATS AS
(
    SELECT AVG(SALARY) AS AVG_SALARY
    FROM EMPLOYEES
)
SELECT E.EMPLOYEE_ID,
       E.LAST_NAME,
       E.SALARY,
       DS.AVG_SALARY AS DEPT_AVG,
       CS.AVG_SALARY AS COMPANY_AVG
FROM EMPLOYEES E
JOIN DEPT_STATS DS
  ON DS.DEPARTMENT_ID = E.DEPARTMENT_ID
CROSS JOIN COMPANY_STATS CS;


/*=============================================================================
49. CHAPTER 11: SAME CTE USED TWICE
=============================================================================*/

-- Employee department count + manager department count.
WITH EMPCOUNTBYDEPT AS
(
    SELECT DEPARTMENT_ID,
           COUNT(*) AS EMPCOUNT
    FROM EMPLOYEES
    GROUP BY DEPARTMENT_ID
)
SELECT E.FIRST_NAME,
       ED.EMPCOUNT AS EMPLOYEE_DEPT_COUNT,
       MD.EMPCOUNT AS MANAGER_DEPT_COUNT
FROM EMPLOYEES E
JOIN EMPLOYEES M
  ON M.EMPLOYEE_ID = E.MANAGER_ID
JOIN EMPCOUNTBYDEPT ED
  ON ED.DEPARTMENT_ID = E.DEPARTMENT_ID
JOIN EMPCOUNTBYDEPT MD
  ON MD.DEPARTMENT_ID = M.DEPARTMENT_ID;


/*=============================================================================
50. SEC-A ONLINE PATTERN 1: ABOVE OVERALL COMPANY AVERAGE
=============================================================================*/

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
51. SEC-A ONLINE PATTERN 2: ABOVE OWN DEPARTMENT AVERAGE, NO MAIN JOIN
=============================================================================*/

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
52. SEC-A / ONLINE QUESTION FAMILY - WHAT TO EXPECT
=============================================================================*/

/*
These are QUESTION FAMILIES, not guaranteed exact questions.

A. JOIN path questions
   - employee + department + job
   - employee department city/country
   - employee vs manager
   - employee department vs manager department location/city

B. Per-group comparison
   - salary > own department average
   - salary > own job average
   - manager salary > company average
   - department avg/max/min vs company statistic

C. Top-k per group
   - highest / second-highest / kth-highest salary per department/job
   - include ties using COUNT(DISTINCT greater values)

D. Existence
   - has JOB_HISTORY        -> EXISTS
   - no JOB_HISTORY         -> NOT EXISTS
   - department has manager -> EXISTS or join/IS NOT NULL

E. Universal condition
   - every employee earns > X
   - HAVING MIN(salary) > X
   - or NOT EXISTS violating employee

F. Set operator
   - both conditions        -> INTERSECT
   - either condition       -> UNION
   - first but not second   -> MINUS
   - exactly one            -> symmetric difference / CASE XOR

G. Output labels
   - CASE / DECODE
   - often combines threshold with dept/company average

H. Repeated statistics
   - WITH / FROM-subquery for department counts/averages/max

I. Nested aggregation
   - a group's MAX/AVG compared with AVG/MAX of all group statistics
*/


/*=============================================================================
53. FAST "QUESTION WORD -> SQL IDEA" MAP
=============================================================================*/

/*
"overall/company average"              -> scalar subquery AVG(...)
"department average"                   -> correlated AVG by DEPARTMENT_ID
"job average"                          -> correlated AVG by JOB_ID
"more than N employees in department"  -> correlated COUNT(*) or GROUP BY HAVING
"second-highest in each department"    -> COUNT(DISTINCT greater salaries) = 1
"kth-highest in each group"             -> COUNT(DISTINCT greater values) = k-1
"at least one"                          -> EXISTS / ANY
"none/no record"                        -> NOT EXISTS
"every/all employees satisfy"           -> HAVING MIN(...) or NOT EXISTS violation
"greater than all"                      -> > ALL or > MAX
"greater than at least one"             -> > ANY
"same city as manager dept"             -> self join + 2 dept + 2 location
"both group conditions"                 -> INTERSECT
"either result"                         -> UNION
"A but not B"                           -> MINUS
"exactly one of A/B"                    -> XOR
"label as ..."                          -> CASE
"reuse department stats"                -> WITH clause
"show related name"                     -> JOIN table containing that name
*/


/*=============================================================================
54. FINAL EXTRA ERROR CHECKLIST FOR CH 5/6/7/11
=============================================================================*/

/*
1. USING(column):
   use column unqualified after USING.

2. OUTER JOIN:
   COUNT(*) can incorrectly show 1 for zero matches.
   Count a nullable column from the optional table instead.

3. LEFT JOIN:
   right-table filter in WHERE may destroy outer-join behavior.

4. Scalar subquery:
   must return at most one row.
   Multiple rows -> IN / ANY / ALL or aggregate it.

5. Correlated subquery:
   MUST connect inner row to current outer row.

6. Top-k with ties:
   count DISTINCT greater values, not rows.

7. NOT IN:
   dangerous if subquery can return NULL.
   Prefer NOT EXISTS when appropriate.

8. ANY/ALL:
   remove/consider NULLs carefully.

9. INTERSECT/UNION/MINUS:
   same number of columns + compatible corresponding types.

10. ORDER BY with set operations:
    put it once at the end.

11. CASE:
    first TRUE WHEN wins.

12. DECODE:
    equality matching; it is not a searched Boolean CASE.

13. GROUP BY:
    every selected non-aggregate expression must be grouped.

14. WHERE vs HAVING:
    WHERE filters rows BEFORE grouping.
    HAVING filters groups AFTER grouping.

15. Exact English matters:
    "more than 5"  -> > 5
    "at least 5"   -> >= 5
    "strictly more"-> >
*/