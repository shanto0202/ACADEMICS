-- ONLINE B
-- Oracle SQL

-- Q1. Select Employee_ID, Full Name, Job_ID, and Salary of employees
-- whose First Name starts with 'M', ends with 'k', and has at least
-- 4 characters.

SELECT EMPLOYEE_ID, FIRST_NAME,JOB_ID, LAST_NAME, SALARY
FROM EMPLOYEES
WHERE FIRST_NAME LIKE 'M___%' AND FIRST_NAME LIKE '%k'


-- Q2. Find employees whose first 'e' position in FIRST_NAME equals
-- the position of an 'e' counted backward from the end of LAST_NAME.
-- Include only employees hired from July to December.
-- Do not use < or >.

SELECT FIRST_NAME || ' ' || LAST_NAME AS FULL_NAME,EMAIL
FROM EMPLOYEES
WHERE INSTR(LOWER(FIRST_NAME), 'e') != 0
  AND INSTR(LOWER(LAST_NAME), 'e', -1) != 0
  AND INSTR(LOWER(FIRST_NAME), 'e') = LENGTH(LAST_NAME) - INSTR(LOWER(LAST_NAME), 'e', -1) + 1
  AND TO_CHAR(HIRE_DATE, 'MM') IN ('07', '08', '09', '10', '11', '12');


-- Q3. Show DEPARTMENT_ID and total salary expenses for employees
-- whose 10-year anniversary falls from January to June.

SELECT DEPARTMENT_ID, SUM(SALARY) AS PAYROLL
FROM EMPLOYEES
WHERE TO_CHAR(ADD_MONTHS(HIRE_DATE, 120),'MM')
      BETWEEN '01' AND '06'
      GROUP BY DEPARTMENT_ID;


-- Q4.
-- i. Create PROJECTS.
-- ii. Add constraints:
--     PROJECT_ID is PRIMARY KEY.
--     PROJECT_NAME is UNIQUE.
--     BUDGET > 50000.
--     STATUS is N, A, or F.
-- iii. Add MANAGER_NAME VARCHAR2(40).

--CREATING TABLE

CREATE TABLE PROJECTS
(
    PROJECT_ID   NUMBER(4),
    PROJECT_NAME VARCHAR2(50),
    BUDGET       NUMBER(10, 2),
    START_DATE   DATE,
    END_DATE     DATE,
    STATUS       CHAR(1)
);

--ADDING CONSTRAINT

ALTER TABLE PROJECTS
ADD CONSTRAINT P1
PRIMARY KEY(PROJECT_ID);

ALTER TABLE PROJECTS
ADD CONSTRAINT P2
UNIQUE (PROJECT_NAME);

ALTER TABLE PROJECTS
ADD CONSTRAINT P3
CHECK (BUDGET > 50000);

ALTER TABLE PROJECTS
ADD CONSTRAINT P4
CHECK (STATUS IN ('N', 'A', 'F'));

--ADDING COLUMN 

ALTER TABLE PROJECTS
ADD MANAGER_NAME VARCHAR2(40);


-- Q5.
-- i. Add IS_HIRED_IN_FIRST_HALF with allowed values Y and N.
-- ii. Set Y for January-June, otherwise N.
-- iii. Add WORK_EMAIL and set it as:
--      first_name.department_acronym.hire_year@company.com
--      Department acronym is the part of JOB_ID before '_'.

ALTER TABLE EMPLOYEES
ADD IS_HIRED_IN_FIRST_HALF CHAR(1)
    CONSTRAINT EMP_FIRST_HALF_CK
    CHECK (IS_HIRED_IN_FIRST_HALF IN ('Y', 'N'));

UPDATE EMPLOYEES
SET IS_HIRED_IN_FIRST_HALF =
    CASE
        WHEN TO_CHAR(HIRE_DATE, 'MM')
             IN ('01', '02', '03', '04', '05', '06')
        THEN 'Y'
        ELSE 'N'
    END;

ALTER TABLE EMPLOYEES
ADD WORK_EMAIL VARCHAR2(100);

UPDATE EMPLOYEES
SET WORK_EMAIL =
    LOWER(
        FIRST_NAME || '.' ||
        SUBSTR(JOB_ID, 1, INSTR(JOB_ID, '_') - 1) || '.' ||
        TO_CHAR(HIRE_DATE, 'YYYY') ||
        '@company.com'
    );

COMMIT;