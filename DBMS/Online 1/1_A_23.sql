-- ONLINE 1: A1/A2
-- Oracle SQL
-- Source: Online - 1 (A1_A2)

-- Q1. Group employees by hiring month (JAN-DEC).
-- Count employees whose last name contains 'a' (case-insensitive).
-- Sort chronologically.

SELECT TO_CHAR(HIRE_DATE, 'MON', 'NLS_DATE_LANGUAGE=ENGLISH') AS HIRE_MONTH,
       COUNT(*) AS TOTAL_EMPLOYEES
FROM EMPLOYEES
WHERE LOWER(LAST_NAME) LIKE '%a%'
GROUP BY TO_CHAR(HIRE_DATE, 'MON', 'NLS_DATE_LANGUAGE=ENGLISH'),
         TO_CHAR(HIRE_DATE, 'MM')
ORDER BY TO_CHAR(HIRE_DATE, 'MM');


-- Q2. Show employees whose last name contains identical
-- consecutive characters, ignoring case. Sort by last name.

SELECT EMPLOYEE_ID,
       LAST_NAME
FROM EMPLOYEES
WHERE REGEXP_LIKE(LAST_NAME, '(.)\1', 'i')
ORDER BY LAST_NAME;


-- Q3. Create PERFORMANCE_REVIEW.
-- Each review belongs to an employee.
-- Rating must be between 1 and 5.
-- Remarks are optional.
-- Insert one record.

CREATE TABLE PERFORMANCE_REVIEW
(
    REVIEW_ID    NUMBER PRIMARY KEY,
    EMPLOYEE_ID  NUMBER NOT NULL,
    REVIEW_YEAR  NUMBER(4),
    RATING       NUMBER(1) CHECK (RATING BETWEEN 1 AND 5),
    REMARKS      VARCHAR2(200),
    CONSTRAINT PR_EMPLOYEE_FK
        FOREIGN KEY (EMPLOYEE_ID)
        REFERENCES EMPLOYEES(EMPLOYEE_ID)
);

INSERT INTO PERFORMANCE_REVIEW
    (REVIEW_ID, EMPLOYEE_ID, REVIEW_YEAR, RATING, REMARKS)
VALUES
    (1, 101, 2026, 5, 'Excellent performance');

COMMIT;


-- Q4. Generate USER_ID using the first 3 letters of FIRST_NAME
-- and the last 3 characters of PHONE_NUMBER.
-- Phone length must be at least 10.
-- Department must be 50 or 80.
-- Sort by FIRST_NAME length descending.

SELECT EMPLOYEE_ID,
       FIRST_NAME || ' ' || LAST_NAME AS FULL_NAME,
       SUBSTR(FIRST_NAME, 1, 3) || SUBSTR(PHONE_NUMBER, -3) AS USER_ID
FROM EMPLOYEES
WHERE LENGTH(PHONE_NUMBER) >= 10
  AND DEPARTMENT_ID IN (50, 80)
ORDER BY LENGTH(FIRST_NAME) DESC;


-- Q5. Show JOB_ID and salary gap.
-- Salary gap must be greater than 3000.
-- Average salary must be at least 6000.
-- Sort by salary gap descending.

SELECT JOB_ID,
       MAX(SALARY) - MIN(SALARY) AS SALARY_GAP
FROM EMPLOYEES
GROUP BY JOB_ID
HAVING MAX(SALARY) - MIN(SALARY) > 3000
   AND AVG(SALARY) >= 6000
ORDER BY SALARY_GAP DESC;