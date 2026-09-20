-- ONLINE 1: C1/C2
-- Oracle SQL
-- Source: Online - 1 (C1_C2)

-- Q1. Group employees by the job acronym,
-- which is the part of JOB_ID after '_'.
-- Count employees with salary greater than 4000
-- and no commission.

SELECT SUBSTR(JOB_ID, INSTR(JOB_ID, '_') + 1) AS JOB_ACRONYM,
       COUNT(*) AS TOTAL_EMPLOYEES
FROM EMPLOYEES
WHERE SALARY > 4000
  AND COMMISSION_PCT IS NULL
GROUP BY SUBSTR(JOB_ID, INSTR(JOB_ID, '_') + 1);


-- Q2. Generate TAG using the first letters of
-- FIRST_NAME and LAST_NAME.
-- Keep employees whose two first letters are equal.
-- Sort by EMPLOYEE_ID.

SELECT EMPLOYEE_ID,
       FIRST_NAME,
       LAST_NAME,
       SUBSTR(FIRST_NAME, 1, 1)
       || SUBSTR(LAST_NAME, 1, 1) AS TAG
FROM EMPLOYEES
WHERE UPPER(SUBSTR(FIRST_NAME, 1, 1))
    = UPPER(SUBSTR(LAST_NAME, 1, 1))
ORDER BY EMPLOYEE_ID;


-- Q3. Create EMP_BONUS.
-- Every bonus belongs to an employee.
-- BONUS_AMOUNT is required and cannot be negative.
-- Insert one record.

CREATE TABLE EMP_BONUS
(
    BONUS_ID      NUMBER PRIMARY KEY,
    EMPLOYEE_ID   NUMBER NOT NULL,
    BONUS_AMOUNT  NUMBER(10, 2) NOT NULL
                  CHECK (BONUS_AMOUNT >= 0),
    CONSTRAINT EB_EMPLOYEE_FK
        FOREIGN KEY (EMPLOYEE_ID)
        REFERENCES EMPLOYEES(EMPLOYEE_ID)
);

INSERT INTO EMP_BONUS
    (BONUS_ID, EMPLOYEE_ID, BONUS_AMOUNT)
VALUES
    (1, 101, 5000);

COMMIT;


-- Q4. Show employees hired in December, January, or February.
-- Display 'No Commission' when COMMISSION_PCT is NULL.
-- Keep employees earning more than 8000.
-- Sort in the order: Dec, Jan, Feb.

SELECT EMPLOYEE_ID,
       HIRE_DATE,
       NVL(TO_CHAR(COMMISSION_PCT), 'No Commission') AS COMMISSION
FROM EMPLOYEES
WHERE TO_CHAR(HIRE_DATE, 'MM') IN ('12', '01', '02')
  AND SALARY > 8000
ORDER BY CASE TO_CHAR(HIRE_DATE, 'MM')
             WHEN '12' THEN 1
             WHEN '01' THEN 2
             WHEN '02' THEN 3
         END;


-- Q5. Show total monthly salary liability for each manager.
-- Keep managers with liability greater than 30000
-- and at least 5 subordinates.
-- Sort by liability descending.

SELECT MANAGER_ID,
       SUM(SALARY) AS TOTAL_MONTHLY_LIABILITY
FROM EMPLOYEES
WHERE MANAGER_ID IS NOT NULL
GROUP BY MANAGER_ID
HAVING SUM(SALARY) > 30000
   AND COUNT(*) >= 5
ORDER BY TOTAL_MONTHLY_LIABILITY DESC;