-- ONLINE 1: B1/B2
-- Oracle SQL
-- Source: Online - 1 (B1_B2)

-- Q1. Group employees by the country code in PHONE_NUMBER.
-- The country code is the part before the first dot.
-- Count employees hired after 1 January 2005.

SELECT SUBSTR(PHONE_NUMBER, 1, INSTR(PHONE_NUMBER, '.') - 1) AS COUNTRY_CODE,
       COUNT(*) AS TOTAL_EMPLOYEES
FROM EMPLOYEES
WHERE HIRE_DATE > TO_DATE('01-JAN-2005', 'DD-MON-YYYY')
GROUP BY SUBSTR(PHONE_NUMBER, 1, INSTR(PHONE_NUMBER, '.') - 1);


-- Q2. Show the absolute difference between SALARY
-- and its nearest multiple of 1000.

SELECT EMPLOYEE_ID,
       SALARY,
       ABS(SALARY - ROUND(SALARY / 1000) * 1000) AS SALARY_DIFF
FROM EMPLOYEES;


-- Q3. Create EMP_TRAINING.
-- Each training belongs to an employee.
-- TRAINING_NAME is required.
-- REG_DATE defaults to SYSDATE.
-- Insert one record.

CREATE TABLE EMP_TRAINING
(
    TRAINING_ID    NUMBER PRIMARY KEY,
    EMPLOYEE_ID    NUMBER NOT NULL,
    TRAINING_NAME  VARCHAR2(100) NOT NULL,
    REG_DATE       DATE DEFAULT SYSDATE,
    CONSTRAINT ET_EMPLOYEE_FK
        FOREIGN KEY (EMPLOYEE_ID)
        REFERENCES EMPLOYEES(EMPLOYEE_ID)
);

INSERT INTO EMP_TRAINING
    (TRAINING_ID, EMPLOYEE_ID, TRAINING_NAME)
VALUES
    (1, 101, 'Oracle Database Fundamentals');

COMMIT;


-- Q4. Show total annual payout for each department.
-- Keep departments with more than 2 employees
-- and minimum salary at least 2500.
-- Format the payout with commas.

SELECT DEPARTMENT_ID,
       TO_CHAR(SUM(SALARY * 12), 'FM99,999,999') AS TOTAL_ANNUAL_PAYOUT
FROM EMPLOYEES
GROUP BY DEPARTMENT_ID
HAVING COUNT(*) > 2
   AND MIN(SALARY) >= 2500;


-- Q5. Generate SECURITY_CODE:
-- first 2 letters of FIRST_NAME in uppercase
-- + length of LAST_NAME
-- + last character of PHONE_NUMBER.
-- Keep employees whose FIRST_NAME is longer than LAST_NAME.
-- Sort by SECURITY_CODE length descending.

SELECT EMPLOYEE_ID,
       SECURITY_CODE
FROM
(
    SELECT EMPLOYEE_ID,
           UPPER(SUBSTR(FIRST_NAME, 1, 2))
           || TO_CHAR(LENGTH(LAST_NAME))
           || SUBSTR(PHONE_NUMBER, -1) AS SECURITY_CODE
    FROM EMPLOYEES
    WHERE LENGTH(FIRST_NAME) > LENGTH(LAST_NAME)
)
ORDER BY LENGTH(SECURITY_CODE) DESC;