/*
===============================================================================
ORACLE SQL TEST TEMPLATE
Basic SELECT + Functions + GROUP BY + DDL + DML
Based on the teacher's Oracle SQL book and the five uploaded online sets.

IMPORTANT:
- This is a reference file. Do not run the whole file at once.
- Copy only the block needed for a question.
- Examples assume the standard Oracle HR schema.
- Text/date values use single quotes. Column aliases with spaces use double quotes.

Book map:
- Basic SELECT and conditions: printed pages 11-23
- Single-row functions: printed pages 24-35
- Aggregate functions: printed pages 36-42
- Basic subqueries: printed pages 48-54
- DML: printed pages 59-66
- DDL: printed pages 67-75
- CASE: printed pages 84-85
===============================================================================
*/


/*=============================================================================
1. BASIC SELECT
=============================================================================*/

-- Select specific columns.
SELECT EMPLOYEE_ID, FIRST_NAME, SALARY
FROM EMPLOYEES;

-- Select every column.
SELECT *
FROM EMPLOYEES;

-- Arithmetic expression and alias.
SELECT EMPLOYEE_ID,
       SALARY,
       SALARY * 12 AS ANNUAL_SALARY
FROM EMPLOYEES;

-- Alias containing spaces requires double quotes.
SELECT SALARY * 12 AS "ANNUAL SALARY"
FROM EMPLOYEES;

-- Join text values using ||.
SELECT FIRST_NAME || ' ' || LAST_NAME AS FULL_NAME
FROM EMPLOYEES;

-- Remove duplicate output rows.
SELECT DISTINCT DEPARTMENT_ID
FROM EMPLOYEES;

-- View table structure.
DESCRIBE EMPLOYEES;


/*=============================================================================
2. WHERE CONDITIONS
=============================================================================*/

-- Comparison operators: =, <>, !=, >, >=, <, <=
SELECT *
FROM EMPLOYEES
WHERE SALARY >= 10000;

-- Range is inclusive.
SELECT *
FROM EMPLOYEES
WHERE SALARY BETWEEN 7000 AND 12000;

-- Match a list of values.
SELECT *
FROM EMPLOYEES
WHERE DEPARTMENT_ID IN (50, 80);

-- Combine conditions.
SELECT *
FROM EMPLOYEES
WHERE DEPARTMENT_ID = 80
  AND SALARY > 5000;

-- Use parentheses when AND and OR are mixed.
SELECT *
FROM EMPLOYEES
WHERE DEPARTMENT_ID = 80
  AND (SALARY > 5000 OR COMMISSION_PCT IS NOT NULL);

-- NULL must use IS NULL or IS NOT NULL.
SELECT *
FROM EMPLOYEES
WHERE COMMISSION_PCT IS NULL;

-- Wrong: COMMISSION_PCT = NULL


/*=============================================================================
3. LIKE PATTERN MATCHING
=============================================================================*/

-- % means zero or more characters.
SELECT *
FROM EMPLOYEES
WHERE LAST_NAME LIKE 'S%';          -- starts with S

SELECT *
FROM EMPLOYEES
WHERE LAST_NAME LIKE '%son';        -- ends with son

SELECT *
FROM EMPLOYEES
WHERE LAST_NAME LIKE '%a%';         -- contains a

-- _ means exactly one character.
SELECT *
FROM EMPLOYEES
WHERE FIRST_NAME LIKE 'M___%';      -- starts M, length at least 4

-- Starts with M, ends with k, length at least 4.
SELECT *
FROM EMPLOYEES
WHERE FIRST_NAME LIKE 'M%k'
  AND LENGTH(FIRST_NAME) >= 4;

-- Case-insensitive match.
SELECT *
FROM EMPLOYEES
WHERE LOWER(LAST_NAME) LIKE '%a%';

-- Match a literal underscore.
SELECT *
FROM EMPLOYEES
WHERE JOB_ID LIKE 'SA\_%' ESCAPE '\';

-- Simpler alternative for prefix SA_.
SELECT *
FROM EMPLOYEES
WHERE SUBSTR(JOB_ID, 1, 3) = 'SA_';


/*=============================================================================
4. ORDER BY
=============================================================================*/

-- ASC is default; DESC reverses the order.
SELECT LAST_NAME, SALARY
FROM EMPLOYEES
ORDER BY SALARY DESC, LAST_NAME ASC;

-- Alias can be used directly in ORDER BY.
SELECT EMPLOYEE_ID,
       SALARY * 12 AS ANNUAL_SALARY
FROM EMPLOYEES
ORDER BY ANNUAL_SALARY DESC;


/*=============================================================================
5. CHARACTER FUNCTIONS
=============================================================================*/

-- LOWER: convert to lowercase.
SELECT LOWER('Hello WORLD') AS RESULT
FROM DUAL;

-- UPPER: convert to uppercase.
SELECT UPPER(FIRST_NAME) AS NAME
FROM EMPLOYEES;

-- INITCAP: capitalize the first letter of each word.
SELECT INITCAP('hello world') AS RESULT
FROM DUAL;

-- LENGTH: number of characters.
SELECT FIRST_NAME, LENGTH(FIRST_NAME) AS NAME_LENGTH
FROM EMPLOYEES;

-- SUBSTR(text, start, length): extract characters.
SELECT FIRST_NAME,
       SUBSTR(FIRST_NAME, 1, 3) AS FIRST_THREE
FROM EMPLOYEES;

-- Negative start counts from the end.
SELECT PHONE_NUMBER,
       SUBSTR(PHONE_NUMBER, -3) AS LAST_THREE
FROM EMPLOYEES;

-- INSTR: position of text; returns 0 when not found.
SELECT JOB_ID,
       INSTR(JOB_ID, '_') AS UNDERSCORE_POSITION
FROM EMPLOYEES;

-- Part before underscore.
SELECT JOB_ID,
       SUBSTR(JOB_ID, 1, INSTR(JOB_ID, '_') - 1) AS DEPT_ACRONYM
FROM EMPLOYEES;

-- Part after underscore.
SELECT JOB_ID,
       SUBSTR(JOB_ID, INSTR(JOB_ID, '_') + 1) AS JOB_ACRONYM
FROM EMPLOYEES;

-- Last occurrence of a character.
SELECT LAST_NAME,
       INSTR(LOWER(LAST_NAME), 'e', -1) AS LAST_E_POSITION
FROM EMPLOYEES;

-- CONCAT joins exactly two expressions.
SELECT CONCAT(FIRST_NAME, LAST_NAME) AS NAME
FROM EMPLOYEES;

-- TRIM removes spaces from both ends.
SELECT TRIM('   Oracle SQL   ') AS RESULT
FROM DUAL;

-- REPLACE changes matching text.
SELECT REPLACE('A-B-C', '-', '.') AS RESULT
FROM DUAL;

-- LPAD/RPAD make fixed-width text.
SELECT LPAD(SALARY, 10, '0') AS PADDED_SALARY
FROM EMPLOYEES;

SELECT RPAD(FIRST_NAME, 20, '*') AS PADDED_NAME
FROM EMPLOYEES;


/*=============================================================================
6. REGULAR EXPRESSION USED IN ONLINE QUESTIONS
=============================================================================*/

-- Find identical consecutive characters, ignoring case.
-- Examples matched: AA, bB, Cc, dd
SELECT EMPLOYEE_ID, LAST_NAME
FROM EMPLOYEES
WHERE REGEXP_LIKE(LAST_NAME, '(.)\1', 'i')
ORDER BY LAST_NAME;


/*=============================================================================
7. NUMBER FUNCTIONS
=============================================================================*/

-- ROUND(number, decimal_places)
SELECT ROUND(45.926, 2) AS RESULT
FROM DUAL;                            -- 45.93

-- TRUNC(number, decimal_places)
SELECT TRUNC(45.926, 2) AS RESULT
FROM DUAL;                            -- 45.92

-- MOD returns the remainder.
SELECT MOD(23, 5) AS RESULT
FROM DUAL;                            -- 3

-- ABS returns absolute value.
SELECT ABS(-500) AS RESULT
FROM DUAL;                            -- 500

-- Difference from nearest multiple of 1000.
SELECT EMPLOYEE_ID,
       SALARY,
       ABS(SALARY - ROUND(SALARY / 1000) * 1000) AS SALARY_DIFF
FROM EMPLOYEES;


/*=============================================================================
8. DATE VALUES AND DATE FUNCTIONS
=============================================================================*/

-- Current database date and time.
SELECT SYSDATE
FROM DUAL;

-- Explicit date conversion is safest.
SELECT *
FROM EMPLOYEES
WHERE HIRE_DATE > TO_DATE('01-JAN-2005', 'DD-MON-YYYY');

-- Format a date as text.
SELECT HIRE_DATE,
       TO_CHAR(HIRE_DATE, 'DD-MON-YYYY') AS FORMATTED_DATE
FROM EMPLOYEES;

-- Useful date format models.
SELECT TO_CHAR(HIRE_DATE, 'YYYY') AS HIRE_YEAR,
       TO_CHAR(HIRE_DATE, 'MM')   AS MONTH_NUMBER,
       TO_CHAR(HIRE_DATE, 'MON')  AS MONTH_NAME,
       TO_CHAR(HIRE_DATE, 'DDD')  AS DAY_OF_YEAR,
       TRIM(TO_CHAR(HIRE_DATE, 'DAY')) AS DAY_NAME
FROM EMPLOYEES;

-- FM removes extra padding.
SELECT TO_CHAR(HIRE_DATE, 'FMDAY') AS DAY_NAME
FROM EMPLOYEES;

-- Extract numeric year or month.
SELECT EXTRACT(YEAR FROM HIRE_DATE) AS HIRE_YEAR,
       EXTRACT(MONTH FROM HIRE_DATE) AS HIRE_MONTH
FROM EMPLOYEES;

-- Date arithmetic: DATE - DATE gives number of days.
SELECT LAST_NAME,
       SYSDATE - HIRE_DATE AS DAYS_EMPLOYED
FROM EMPLOYEES;

-- Add months.
SELECT HIRE_DATE,
       ADD_MONTHS(HIRE_DATE, 120) AS TEN_YEAR_ANNIVERSARY
FROM EMPLOYEES;

-- Months between two dates.
SELECT LAST_NAME,
       MONTHS_BETWEEN(SYSDATE, HIRE_DATE) AS MONTHS_EMPLOYED
FROM EMPLOYEES;

-- First day of the month/year.
SELECT TRUNC(HIRE_DATE, 'MONTH') AS MONTH_START,
       TRUNC(HIRE_DATE, 'YEAR')  AS YEAR_START
FROM EMPLOYEES;

-- Employees hired in March.
SELECT *
FROM EMPLOYEES
WHERE TO_CHAR(HIRE_DATE, 'MM') = '03';

-- Employees hired in the first half of a year.
SELECT *
FROM EMPLOYEES
WHERE TO_CHAR(HIRE_DATE, 'MM') BETWEEN '01' AND '06';

-- Odd day number within the year.
SELECT *
FROM EMPLOYEES
WHERE MOD(TO_NUMBER(TO_CHAR(HIRE_DATE, 'DDD')), 2) = 1;

-- Winter order: December, January, February.
SELECT EMPLOYEE_ID, HIRE_DATE
FROM EMPLOYEES
WHERE TO_CHAR(HIRE_DATE, 'MM') IN ('12', '01', '02')
ORDER BY CASE TO_CHAR(HIRE_DATE, 'MM')
             WHEN '12' THEN 1
             WHEN '01' THEN 2
             WHEN '02' THEN 3
         END;

-- Chronological month grouping: JAN to DEC.
SELECT TO_CHAR(HIRE_DATE, 'MON') AS HIRE_MONTH,
       COUNT(*) AS TOTAL
FROM EMPLOYEES
GROUP BY TO_CHAR(HIRE_DATE, 'MON'),
         TO_CHAR(HIRE_DATE, 'MM')
ORDER BY TO_CHAR(HIRE_DATE, 'MM');


/*=============================================================================
9. NULL HANDLING AND CONVERSION
=============================================================================*/

-- NVL(value, replacement)
SELECT LAST_NAME,
       NVL(COMMISSION_PCT, 0) AS COMMISSION
FROM EMPLOYEES;

-- Display text when a numeric value is NULL.
SELECT EMPLOYEE_ID,
       NVL(TO_CHAR(COMMISSION_PCT), 'No Commission') AS COMMISSION
FROM EMPLOYEES;

-- Convert text to number.
SELECT TO_NUMBER('12345') + 5 AS RESULT
FROM DUAL;

-- Format a number with commas; FM removes leading spaces.
SELECT TO_CHAR(3654000, 'FM99,999,999') AS RESULT
FROM DUAL;


/*=============================================================================
10. CASE EXPRESSIONS
=============================================================================*/

-- CASE in SELECT: does not modify the table.
SELECT EMPLOYEE_ID,
       SALARY,
       CASE
           WHEN SALARY > 10000 THEN 'High Fixed'
           WHEN SALARY >= 10000 THEN 'Standard Fixed'
           ELSE 'Below Standard'
       END AS INCOME_STATUS
FROM EMPLOYEES;

-- Salary grade.
SELECT EMPLOYEE_ID,
       SALARY,
       CASE
           WHEN SALARY < 7000 THEN 'L'
           WHEN SALARY BETWEEN 7000 AND 12000 THEN 'M'
           ELSE 'H'
       END AS SALARY_GRADE
FROM EMPLOYEES;

-- CASE order matters: first matching WHEN is used.


/*=============================================================================
11. AGGREGATE FUNCTIONS AND GROUP BY
=============================================================================*/

-- Common group functions.
SELECT SUM(SALARY) AS TOTAL_SALARY,
       AVG(SALARY) AS AVERAGE_SALARY,
       MIN(SALARY) AS MINIMUM_SALARY,
       MAX(SALARY) AS MAXIMUM_SALARY,
       COUNT(*) AS TOTAL_ROWS
FROM EMPLOYEES;

-- COUNT(column) ignores NULL; COUNT(*) counts rows.
SELECT COUNT(COMMISSION_PCT) AS NON_NULL_COMMISSIONS,
       COUNT(*) AS TOTAL_EMPLOYEES
FROM EMPLOYEES;

-- One row per department.
SELECT DEPARTMENT_ID,
       SUM(SALARY) AS TOTAL_SALARY
FROM EMPLOYEES
GROUP BY DEPARTMENT_ID;

-- WHERE filters rows before grouping.
SELECT DEPARTMENT_ID,
       COUNT(*) AS TOTAL_EMPLOYEES
FROM EMPLOYEES
WHERE SALARY > 4000
GROUP BY DEPARTMENT_ID;

-- HAVING filters groups after grouping.
SELECT DEPARTMENT_ID,
       SUM(SALARY) AS TOTAL_SALARY
FROM EMPLOYEES
GROUP BY DEPARTMENT_ID
HAVING SUM(SALARY) > 30000;

-- Multiple group conditions.
SELECT DEPARTMENT_ID,
       TO_CHAR(SUM(SALARY * 12), 'FM99,999,999') AS TOTAL_PAYOUT
FROM EMPLOYEES
GROUP BY DEPARTMENT_ID
HAVING COUNT(*) > 2
   AND MIN(SALARY) >= 2500;

-- Group by an expression.
SELECT SUBSTR(JOB_ID, INSTR(JOB_ID, '_') + 1) AS JOB_ACRONYM,
       COUNT(*) AS TOTAL
FROM EMPLOYEES
WHERE SALARY > 4000
  AND COMMISSION_PCT IS NULL
GROUP BY SUBSTR(JOB_ID, INSTR(JOB_ID, '_') + 1);

-- Job salary gap.
SELECT JOB_ID,
       MAX(SALARY) - MIN(SALARY) AS SALARY_GAP
FROM EMPLOYEES
GROUP BY JOB_ID
HAVING MAX(SALARY) - MIN(SALARY) > 3000
   AND AVG(SALARY) >= 6000
ORDER BY SALARY_GAP DESC;

-- Logical clause order:
-- SELECT
-- FROM
-- WHERE
-- GROUP BY
-- HAVING
-- ORDER BY


/*=============================================================================
12. USEFUL ONLINE-STYLE STRING PATTERNS
=============================================================================*/

-- Country code: part before first dot in PHONE_NUMBER.
SELECT SUBSTR(PHONE_NUMBER, 1, INSTR(PHONE_NUMBER, '.') - 1) AS COUNTRY_CODE,
       COUNT(*) AS TOTAL
FROM EMPLOYEES
GROUP BY SUBSTR(PHONE_NUMBER, 1, INSTR(PHONE_NUMBER, '.') - 1);

-- User ID: first 3 letters of first name + last 3 phone characters.
SELECT EMPLOYEE_ID,
       SUBSTR(FIRST_NAME, 1, 3)
       || SUBSTR(PHONE_NUMBER, -3) AS USER_ID
FROM EMPLOYEES;

-- Tag: first letter of first name + first letter of last name.
SELECT EMPLOYEE_ID,
       SUBSTR(FIRST_NAME, 1, 1)
       || SUBSTR(LAST_NAME, 1, 1) AS TAG
FROM EMPLOYEES
WHERE UPPER(SUBSTR(FIRST_NAME, 1, 1))
    = UPPER(SUBSTR(LAST_NAME, 1, 1));

-- Security code:
-- first 2 first-name letters uppercase + last-name length + last phone character.
SELECT EMPLOYEE_ID,
       UPPER(SUBSTR(FIRST_NAME, 1, 2))
       || LENGTH(LAST_NAME)
       || SUBSTR(PHONE_NUMBER, -1) AS SECURITY_CODE
FROM EMPLOYEES;

-- Position from the end:
-- reverse_position = LENGTH(text) - normal_position + 1
SELECT FIRST_NAME, LAST_NAME
FROM EMPLOYEES
WHERE INSTR(LOWER(FIRST_NAME), 'e') != 0
  AND INSTR(LOWER(LAST_NAME), 'e', -1) != 0
  AND INSTR(LOWER(FIRST_NAME), 'e')
      = LENGTH(LAST_NAME)
        - INSTR(LOWER(LAST_NAME), 'e', -1) + 1;


/*=============================================================================
13. BASIC SUBQUERIES
=============================================================================*/

-- Compare against one value returned by a subquery.
SELECT LAST_NAME, SALARY
FROM EMPLOYEES
WHERE SALARY >
      (
          SELECT SALARY
          FROM EMPLOYEES
          WHERE EMPLOYEE_ID = 141
      );

-- Latest recruitment year.
SELECT *
FROM EMPLOYEES
WHERE EXTRACT(YEAR FROM HIRE_DATE) =
      (
          SELECT MAX(EXTRACT(YEAR FROM HIRE_DATE))
          FROM EMPLOYEES
      );

-- IN for a subquery returning multiple rows.
SELECT *
FROM EMPLOYEES
WHERE DEPARTMENT_ID IN
      (
          SELECT DEPARTMENT_ID
          FROM DEPARTMENTS
          WHERE LOCATION_ID = 1700
      );

-- EXISTS: true when the correlated subquery returns a row.
SELECT *
FROM EMPLOYEES E
WHERE EXISTS
      (
          SELECT 1
          FROM EMPLOYEES X
          WHERE X.MANAGER_ID = E.EMPLOYEE_ID
      );

-- NOT EXISTS: rows with no related record.
SELECT *
FROM LOCATIONS L
WHERE NOT EXISTS
      (
          SELECT 1
          FROM DEPARTMENTS D
          WHERE D.LOCATION_ID = L.LOCATION_ID
      );


/*=============================================================================
14. DDL: CREATE TABLE
=============================================================================*/

-- Common Oracle data types:
-- NUMBER
-- NUMBER(precision, scale)
-- VARCHAR2(maximum_size)
-- CHAR(fixed_size)
-- DATE

CREATE TABLE PROJECTS
(
    PROJECT_ID    NUMBER(4),
    PROJECT_NAME  VARCHAR2(50),
    BUDGET        NUMBER(10, 2),
    START_DATE    DATE,
    END_DATE      DATE,
    STATUS        CHAR(1)
);

-- Create constraints directly.
CREATE TABLE EMP_TRAINING
(
    TRAINING_ID    NUMBER
                   CONSTRAINT ET_PK PRIMARY KEY,

    EMPLOYEE_ID    NUMBER NOT NULL,

    TRAINING_NAME  VARCHAR2(100) NOT NULL,

    REG_DATE       DATE DEFAULT SYSDATE,

    CONSTRAINT ET_EMPLOYEE_FK
        FOREIGN KEY (EMPLOYEE_ID)
        REFERENCES EMPLOYEES(EMPLOYEE_ID)
);

-- Table-level constraints.
CREATE TABLE PERFORMANCE_REVIEW
(
    REVIEW_ID     NUMBER,
    EMPLOYEE_ID   NUMBER NOT NULL,
    REVIEW_YEAR   NUMBER(4),
    RATING        NUMBER(1) NOT NULL,
    REMARKS       VARCHAR2(200),

    CONSTRAINT PR_PK PRIMARY KEY (REVIEW_ID),
    CONSTRAINT PR_EMP_FK
        FOREIGN KEY (EMPLOYEE_ID)
        REFERENCES EMPLOYEES(EMPLOYEE_ID),
    CONSTRAINT PR_RATING_CK
        CHECK (RATING BETWEEN 1 AND 5)
);

-- Constraint meanings:
-- PRIMARY KEY = UNIQUE + NOT NULL; one primary key per table.
-- UNIQUE = no duplicate non-NULL values.
-- NOT NULL = value is required.
-- CHECK = row must satisfy a condition.
-- FOREIGN KEY = value must exist in referenced PRIMARY/UNIQUE key.
-- DEFAULT = used when the column is omitted during INSERT.

-- Composite primary key.
CREATE TABLE ENROLLMENT
(
    STUDENT_ID  NUMBER,
    COURSE_ID   NUMBER,
    CONSTRAINT ENROLLMENT_PK
        PRIMARY KEY (STUDENT_ID, COURSE_ID)
);


/*=============================================================================
15. CREATE TABLE AS SELECT (CTAS)
=============================================================================*/

-- Copy structure and all selected rows.
CREATE TABLE EMPLOYEES_COPY AS
SELECT *
FROM EMPLOYEES;

-- Copy structure only.
CREATE TABLE YOUNG_EMPLOYEES AS
SELECT *
FROM EMPLOYEES
WHERE 1 = 0;

-- CTAS usually does not copy PRIMARY KEY, FOREIGN KEY,
-- UNIQUE, CHECK, or DEFAULT definitions. Add them separately.


/*=============================================================================
16. ALTER TABLE
=============================================================================*/

-- Add one column.
ALTER TABLE EMPLOYEES
ADD WORK_EMAIL VARCHAR2(100);

-- Add multiple columns.
ALTER TABLE EMPLOYEES
ADD
(
    TEMP_FLAG CHAR(1),
    TEMP_NOTE VARCHAR2(100)
);

-- Change datatype/size or add NOT NULL.
ALTER TABLE EMPLOYEES
MODIFY WORK_EMAIL VARCHAR2(150);

ALTER TABLE YOUNG_EMPLOYEES
MODIFY FIRST_NAME NOT NULL;

-- Add constraints.
ALTER TABLE PROJECTS
ADD CONSTRAINT PROJECTS_PK
PRIMARY KEY (PROJECT_ID);

ALTER TABLE PROJECTS
ADD CONSTRAINT PROJECTS_NAME_UK
UNIQUE (PROJECT_NAME);

ALTER TABLE PROJECTS
ADD CONSTRAINT PROJECTS_BUDGET_CK
CHECK (BUDGET > 50000);

ALTER TABLE PROJECTS
ADD CONSTRAINT PROJECTS_STATUS_CK
CHECK (STATUS IN ('N', 'A', 'F'));

-- Add a foreign key.
ALTER TABLE EMP_TRAINING
ADD CONSTRAINT ET_EMP_FK
FOREIGN KEY (EMPLOYEE_ID)
REFERENCES EMPLOYEES(EMPLOYEE_ID);

-- Drop a column.
ALTER TABLE YOUNG_EMPLOYEES
DROP COLUMN COMMISSION_PCT;

-- Drop a named constraint.
ALTER TABLE PROJECTS
DROP CONSTRAINT PROJECTS_STATUS_CK;

-- Existing invalid data can make ADD CONSTRAINT or MODIFY NOT NULL fail.


/*=============================================================================
17. DROP AND TRUNCATE
=============================================================================*/

-- Remove table structure and data.
DROP TABLE PROJECTS;

-- Remove all rows but keep the table structure.
TRUNCATE TABLE PROJECTS;

-- DELETE can use WHERE and can be rolled back before COMMIT.
-- TRUNCATE cannot use WHERE and is DDL.
-- DROP removes the table itself.


/*=============================================================================
18. DML: INSERT
=============================================================================*/

-- Insert values into every column in table order.
INSERT INTO PROJECTS
VALUES
(
    1,
    'Database Project',
    75000,
    TO_DATE('21-JUL-2026', 'DD-MON-YYYY'),
    NULL,
    'N'
);

-- Safer: state the column names.
INSERT INTO PROJECTS
    (PROJECT_ID, PROJECT_NAME, BUDGET, STATUS)
VALUES
    (2, 'Web Project', 60000, 'A');

-- Omitted columns receive DEFAULT or NULL.
INSERT INTO EMP_TRAINING
    (TRAINING_ID, EMPLOYEE_ID, TRAINING_NAME)
VALUES
    (1, 101, 'Oracle Database Fundamentals');

-- Insert rows returned by a query.
INSERT INTO YOUNG_EMPLOYEES
SELECT *
FROM EMPLOYEES
WHERE EXTRACT(YEAR FROM HIRE_DATE) =
      (
          SELECT MAX(EXTRACT(YEAR FROM HIRE_DATE))
          FROM EMPLOYEES
      );


/*=============================================================================
19. DML: UPDATE
=============================================================================*/

-- Update selected rows only.
UPDATE EMPLOYEES
SET SALARY = SALARY * 1.08
WHERE SUBSTR(JOB_ID, 1, 3) = 'SA_'
  AND TO_CHAR(HIRE_DATE, 'MM') = '03';

-- Update more than one column.
UPDATE PROJECTS
SET STATUS = 'A',
    START_DATE = SYSDATE
WHERE PROJECT_ID = 1;

-- Conditional update with CASE.
UPDATE EMPLOYEES
SET SALARY_GRADE =
    CASE
        WHEN SALARY < 7000 THEN 'L'
        WHEN SALARY BETWEEN 7000 AND 12000 THEN 'M'
        ELSE 'H'
    END;

-- First-half flag.
UPDATE EMPLOYEES
SET IS_HIRED_IN_FIRST_HALF =
    CASE
        WHEN TO_CHAR(HIRE_DATE, 'MM') BETWEEN '01' AND '06'
        THEN 'Y'
        ELSE 'N'
    END;

-- Generate work email.
UPDATE EMPLOYEES
SET WORK_EMAIL =
    LOWER
    (
        FIRST_NAME || '.'
        || SUBSTR(JOB_ID, 1, INSTR(JOB_ID, '_') - 1) || '.'
        || TO_CHAR(HIRE_DATE, 'YYYY')
        || '@company.com'
    );

-- Update using a scalar subquery.
UPDATE EMPLOYEES E
SET SALARY =
    (
        SELECT MAX(X.SALARY)
        FROM EMPLOYEES X
        WHERE X.DEPARTMENT_ID = E.DEPARTMENT_ID
    )
WHERE E.DEPARTMENT_ID IS NOT NULL;

-- WARNING: UPDATE without WHERE changes every row.


/*=============================================================================
20. DML: DELETE
=============================================================================*/

-- Delete selected rows.
DELETE FROM EMPLOYEES
WHERE SALARY < 5000;

-- Delete all rows but keep structure.
DELETE FROM PROJECTS;

-- Delete rows with no related record.
DELETE FROM LOCATIONS L
WHERE NOT EXISTS
      (
          SELECT 1
          FROM DEPARTMENTS D
          WHERE D.LOCATION_ID = L.LOCATION_ID
      );

-- Foreign-key dependencies may block a DELETE.


/*=============================================================================
21. TRANSACTION CONTROL
=============================================================================*/

-- Permanently save current DML changes.
COMMIT;

-- Undo uncommitted DML changes.
ROLLBACK;

-- DDL statements such as CREATE, ALTER, DROP, and TRUNCATE
-- cause an automatic COMMIT in Oracle.

-- Safe workflow:
-- 1. Run SELECT with the same WHERE condition.
-- 2. Run UPDATE or DELETE.
-- 3. Verify using SELECT.
-- 4. COMMIT when correct; otherwise ROLLBACK.


/*=============================================================================
22. QUICK CONSTRAINT INSPECTION
=============================================================================*/

-- View constraints of a table.
SELECT CONSTRAINT_NAME,
       CONSTRAINT_TYPE,
       STATUS
FROM USER_CONSTRAINTS
WHERE TABLE_NAME = 'PROJECTS';

-- Constraint type:
-- P = Primary key
-- U = Unique
-- R = Foreign key
-- C = Check or NOT NULL


/*=============================================================================
23. FINAL EXAM REMINDERS
=============================================================================*/

-- String/date literal: 'text'
-- Number: no quotes
-- Full name: FIRST_NAME || ' ' || LAST_NAME
-- NULL check: IS NULL / IS NOT NULL
-- Case-insensitive: LOWER(column) or UPPER(column)
-- At least N characters: LENGTH(column) >= N
-- Part before _: SUBSTR(col, 1, INSTR(col, '_') - 1)
-- Part after _:  SUBSTR(col, INSTR(col, '_') + 1)
-- Last N characters: SUBSTR(col, -N)
-- Month number: TO_CHAR(date_col, 'MM')
-- Year: TO_CHAR(date_col, 'YYYY') or EXTRACT(YEAR FROM date_col)
-- Odd number: MOD(value, 2) = 1
-- First half: month BETWEEN '01' AND '06'
-- Latest year: MAX(EXTRACT(YEAR FROM date_col))
-- Row filtering: WHERE
-- Group filtering: HAVING
-- Save DML: COMMIT
-- Undo uncommitted DML: ROLLBACK
-- Verify UPDATE/DELETE conditions using SELECT first.
===============================================================================