/*=============================================================================
 CSE 215 DATABASE — CT SQL SLIDE TEMPLATE
 BUET CSE | Oracle-oriented | Questions are comments, answers follow.

 CT coverage:
 - Multi-table query, cross product, natural join
 - Set operations
 - Inner/outer joins
 - NULL and aggregate functions
 - GROUP BY and HAVING
 - Subqueries, ALL/ANY, correlated subqueries, EXISTS
 - Attribute-based and tuple-based CHECK constraints

 NOTE: The lectures reuse table names with different schemas.
 Treat each topic section independently; do not execute the whole file at once.
=============================================================================*/


/*=============================================================================
 1. MULTI-TABLE QUERY, CROSS PRODUCT, NATURAL JOIN  [Lecture 08]
=============================================================================*/

/* Assumed schema for Q1-Q5:
   R(A, B)
   S(B, C)
*/

-- Q1. Show the Cartesian product of R and S.
SELECT R.A,
       R.B AS R_B,
       S.B AS S_B,
       S.C
FROM R CROSS JOIN S;

-- Slide-style equivalent.
SELECT R.A,
       R.B AS R_B,
       S.B AS S_B,
       S.C
FROM R, S;

-- Q2. Join R and S where their B values match.
SELECT R.A,
       R.B AS R_B,
       S.B AS S_B,
       S.C
FROM R
JOIN S ON R.B = S.B;

-- Slide-style equivalent: cross product followed by WHERE filtering.
SELECT R.A,
       R.B AS R_B,
       S.B AS S_B,
       S.C
FROM R, S
WHERE R.B = S.B;

-- Q3. Perform a NATURAL JOIN between R and S.
-- All same-named columns are automatically matched; common B appears once.
SELECT A, B, C
FROM R NATURAL JOIN S;


/* Assumed schema for Q4-Q8:
   Product(PName, Price, Category, Manufacturer)
   Company(CName, Country, StockPrice)
*/

-- Q4. Recover product information together with company information.
SELECT p.PName,
       p.Price,
       p.Category,
       c.CName,
       c.Country,
       c.StockPrice
FROM Product p
JOIN Company c ON p.Manufacturer = c.CName;

-- Q5. Find product names and prices below 200 made by Japanese companies.
SELECT p.PName,
       p.Price
FROM Product p
JOIN Company c ON p.Manufacturer = c.CName
WHERE c.Country = 'Japan'
  AND p.Price < 200;

-- Q6. Find Chinese companies producing electronic products or toys.
SELECT DISTINCT c.CName
FROM Product p
JOIN Company c ON p.Manufacturer = c.CName
WHERE c.Country = 'China'
  AND (p.Category = 'electronic' OR p.Category = 'toy');

-- Q7. Find countries that manufacture at least one Gadgets product.
SELECT DISTINCT c.Country
FROM Product p
JOIN Company c ON p.Manufacturer = c.CName
WHERE p.Category = 'Gadgets';


/* Assumed schema for Q8-Q10:
   Person(PName, Address, WorksFor)
   Company(CName, Address)
*/

-- Q8. Find persons living at the same address as the company they work for.
SELECT p.PName,
       p.Address
FROM Person p
JOIN Company c ON p.WorksFor = c.CName
WHERE p.Address = c.Address;

-- Q9. Find pairs of different persons who live at the same address.
-- x.PName < y.PName prevents (A,B)/(B,A) duplicate pairs.
SELECT x.PName AS Person_1,
       y.PName AS Person_2,
       x.Address
FROM Person x
JOIN Person y ON x.Address = y.Address
             AND x.PName < y.PName;

-- Q10. Show how aliases resolve an ambiguous same-named column.
SELECT p.PName,
       p.Address AS Person_Address,
       c.Address AS Company_Address
FROM Person p
JOIN Company c ON p.WorksFor = c.CName;


/*=============================================================================
 2. SET OPERATIONS  [Lecture 08]
=============================================================================*/

/* Assumed schema:
   Product(Maker, Model, Type)
   PC(Model, Speed, RAM, HD, Price)
   Laptop(Model, Speed, RAM, HD, Screen, Price)
*/

-- Q11. Find all PC and Laptop models with prices made by maker B.
SELECT pc.Model,
       pc.Price
FROM Product p
JOIN PC pc ON p.Model = pc.Model
WHERE p.Maker = 'B'

UNION

SELECT l.Model,
       l.Price
FROM Product p
JOIN Laptop l ON p.Model = l.Model
WHERE p.Maker = 'B';

-- Q12. Find makers that produce both PCs and Laptops.
SELECT Maker
FROM Product
WHERE Type = 'pc'

INTERSECT

SELECT Maker
FROM Product
WHERE Type = 'laptop';

-- Q13. Find makers that produce Laptops but do not produce PCs.
SELECT Maker
FROM Product
WHERE Type = 'laptop'

MINUS

SELECT Maker
FROM Product
WHERE Type = 'pc';

-- Q14. Find makers that produce PCs, Laptops, or both.
SELECT Maker
FROM Product
WHERE Type = 'pc'

UNION

SELECT Maker
FROM Product
WHERE Type = 'laptop';

-- Q15. Preserve all duplicate rows while combining two query results.
SELECT Maker
FROM Product
WHERE Type = 'pc'

UNION ALL

SELECT Maker
FROM Product
WHERE Type = 'laptop';

/* Theory only:
   UNION             -> duplicate rows removed.
   INTERSECT         -> common distinct rows.
   MINUS             -> first result minus second result.
   UNION ALL         -> a + b occurrences.
   INTERSECT ALL     -> MIN(a,b) occurrences; not supported by Oracle.
   EXCEPT/MINUS ALL  -> MAX(0,a-b) occurrences; not supported by Oracle.
*/


/*=============================================================================
 3. INNER AND OUTER JOINS  [Lecture 09]
=============================================================================*/

/* Assumed slide schema for this section:
   PC(Model, Maker)
   Laptop(Model, Maker)
*/

-- Q16. Show only makers appearing in both PC and Laptop.
SELECT pc.Model AS PC_Model,
       pc.Maker AS PC_Maker,
       l.Model AS Laptop_Model,
       l.Maker AS Laptop_Maker
FROM PC pc
INNER JOIN Laptop l ON pc.Maker = l.Maker;

-- Q17. Show all PC rows and matching Laptop rows.
SELECT pc.Model AS PC_Model,
       pc.Maker AS PC_Maker,
       l.Model AS Laptop_Model,
       l.Maker AS Laptop_Maker
FROM PC pc
LEFT OUTER JOIN Laptop l ON pc.Maker = l.Maker;

-- Q18. Show all Laptop rows and matching PC rows.
SELECT pc.Model AS PC_Model,
       pc.Maker AS PC_Maker,
       l.Model AS Laptop_Model,
       l.Maker AS Laptop_Maker
FROM PC pc
RIGHT OUTER JOIN Laptop l ON pc.Maker = l.Maker;

-- Q19. Show matching and dangling rows from both tables.
SELECT pc.Model AS PC_Model,
       pc.Maker AS PC_Maker,
       l.Model AS Laptop_Model,
       l.Maker AS Laptop_Maker
FROM PC pc
FULL OUTER JOIN Laptop l ON pc.Maker = l.Maker;

-- Q20. Find makers that sell both PCs and Laptops.
SELECT DISTINCT pc.Maker
FROM PC pc
INNER JOIN Laptop l ON pc.Maker = l.Maker;

-- Q21. Find PC makers that do not make Laptops.
SELECT DISTINCT pc.Maker
FROM PC pc
LEFT OUTER JOIN Laptop l ON pc.Maker = l.Maker
WHERE l.Maker IS NULL;

-- Q22. Find Laptop makers that do not make PCs.
SELECT DISTINCT l.Maker
FROM PC pc
RIGHT OUTER JOIN Laptop l ON pc.Maker = l.Maker
WHERE pc.Maker IS NULL;

-- Q23. Find makers appearing in PC or Laptop or both using FULL OUTER JOIN.
SELECT DISTINCT COALESCE(pc.Maker, l.Maker) AS Maker
FROM PC pc
FULL OUTER JOIN Laptop l ON pc.Maker = l.Maker;

-- Simpler set-operation solution for Q23.
SELECT Maker FROM PC
UNION
SELECT Maker FROM Laptop;


/*=============================================================================
 4. FORMULAS AND NULL  [Lecture 10]
=============================================================================*/

/* Assumed schema:
   Purchase(Product, Day, Price, Quantity)
   Marks(Student, Mark)
   Person(Age, Height, Weight)
*/

-- Q24. Find the sale value of every purchase row.
SELECT Product,
       Day,
       Price * Quantity AS Sales
FROM Purchase;

-- Q25. Show each mark divided by 3.
-- If Mark is NULL, Mark/3 is also NULL.
SELECT Student,
       Mark,
       Mark / 3 AS Mark_Divided_By_3
FROM Marks;

-- Q26. Find rows where Age is unknown.
SELECT *
FROM Person
WHERE Age IS NULL;

-- Q27. Find rows where Age is known.
SELECT *
FROM Person
WHERE Age IS NOT NULL;

-- Q28. Include every row, including rows whose Age is NULL.
SELECT *
FROM Person
WHERE Age < 25
   OR Age >= 25
   OR Age IS NULL;

-- Q29. Evaluate a three-valued-logic condition.
-- Only rows whose final condition is TRUE pass WHERE.
SELECT *
FROM Person
WHERE Age < 25
  AND (Height > 6 OR Weight > 190);

/* NULL reminders:
   NULL is not 0 and not an empty string.
   Arithmetic with NULL -> NULL.
   Comparison with NULL -> UNKNOWN.
   WHERE keeps TRUE only; FALSE and UNKNOWN are rejected.
   Use IS NULL / IS NOT NULL, never = NULL.
*/


/*=============================================================================
 5. AGGREGATE FUNCTIONS, GROUP BY, HAVING  [Lecture 10]
=============================================================================*/

-- Q30. Show common aggregate values.
SELECT SUM(Mark) AS Total_Mark,
       AVG(Mark) AS Average_Mark,
       MIN(Mark) AS Minimum_Mark,
       MAX(Mark) AS Maximum_Mark,
       COUNT(*) AS Total_Rows
FROM Marks;

-- Q31. Compare COUNT(*) and COUNT(Mark).
-- COUNT(*) counts rows; COUNT(Mark) ignores NULL marks.
SELECT COUNT(*) AS Total_Rows,
       COUNT(Mark) AS Known_Marks
FROM Marks;

-- Q32. Count distinct non-NULL values.
SELECT COUNT(DISTINCT Mark) AS Distinct_Known_Marks
FROM Marks;

-- Q33. Find total sales over all purchase rows.
SELECT SUM(Price * Quantity) AS Total_Sales
FROM Purchase;

-- Q34. Find total Bagel sales.
SELECT SUM(Price * Quantity) AS Bagel_Sales
FROM Purchase
WHERE Product = 'Bagel';

-- Q35. Find total sales per product after 04-Oct-2005.
SELECT Product,
       SUM(Price * Quantity) AS Total_Sales
FROM Purchase
WHERE Day > DATE '2005-10-04'
GROUP BY Product;

-- Q36. After 04-Oct-2005, show products with at least 30 items sold.
SELECT Product,
       SUM(Price * Quantity) AS Total_Sales
FROM Purchase
WHERE Day > DATE '2005-10-04'
GROUP BY Product
HAVING SUM(Quantity) >= 30;

/* Assumed schema for Q37-Q43:
   Product(Maker, Model, Type)
   PC(Model, Speed, RAM, HD, Price)
*/

-- Q37. Find makers that produce at least three PC models.
SELECT Maker
FROM Product
WHERE Type = 'pc'
GROUP BY Maker
HAVING COUNT(DISTINCT Model) >= 3;

-- Q38. Find makers that produce all three product types.
SELECT Maker
FROM Product
GROUP BY Maker
HAVING COUNT(DISTINCT Type) = 3;

-- Q39. Find makers producing only one product type but multiple models.
SELECT Maker
FROM Product
GROUP BY Maker
HAVING COUNT(DISTINCT Type) = 1
   AND COUNT(DISTINCT Model) > 1;

-- Q40. Find the average speed of all PCs.
SELECT AVG(Speed) AS Average_PC_Speed
FROM PC;

-- Q41. Find the average price of PCs made by maker A.
SELECT AVG(pc.Price) AS Average_Price
FROM Product p
JOIN PC pc ON p.Model = pc.Model
WHERE p.Maker = 'A';

-- Q42. For each speed above 2.0, find the average PC price.
SELECT Speed,
       AVG(Price) AS Average_Price
FROM PC
WHERE Speed > 2.0
GROUP BY Speed;

-- Q43. For every maker, find the maximum PC price.
SELECT p.Maker,
       MAX(pc.Price) AS Maximum_PC_Price
FROM Product p
JOIN PC pc ON p.Model = pc.Model
GROUP BY p.Maker;

/* GROUP BY reminders:
   WHERE filters rows before grouping.
   HAVING filters groups after grouping.
   Every selected non-aggregate expression should appear in GROUP BY.
*/


/*=============================================================================
 6. SUBQUERY BASICS, ALL, ANY  [Lecture 11]
=============================================================================*/

/* Assumed schema:
   Employee(ID, Dept, Salary)
*/

-- Q44. Find the highest-paid employee(s) using MAX.
SELECT ID
FROM Employee
WHERE Salary = (
    SELECT MAX(Salary)
    FROM Employee
);

-- Q45. Find the highest-paid employee(s) using ALL.
SELECT ID
FROM Employee
WHERE Salary >= ALL (
    SELECT Salary
    FROM Employee
);

-- Q46. Slide-style nested ALL/ANY solution for the maximum salary.
SELECT ID
FROM Employee
WHERE Salary > ALL (
    SELECT Salary
    FROM Employee
    WHERE Salary < ANY (
        SELECT Salary
        FROM Employee
    )
);

-- Q47. Find the highest-paid employee(s) in each department.
SELECT ID,
       Dept
FROM Employee
WHERE (Dept, Salary) IN (
    SELECT Dept,
           MAX(Salary)
    FROM Employee
    GROUP BY Dept
);

-- Q48. Find employees earning above the overall average salary.
SELECT *
FROM Employee
WHERE Salary > (
    SELECT AVG(Salary)
    FROM Employee
);

/* ALL/ANY shortcuts for non-empty subquery S:
   x >  ALL(S)  <=> x >  MAX(S)
   x <  ALL(S)  <=> x <  MIN(S)
   x >  ANY(S)  <=> x >  MIN(S)
   x <  ANY(S)  <=> x <  MAX(S)
*/


/*=============================================================================
 7. CORRELATED SUBQUERY, EXISTS, NOT EXISTS  [Lecture 11]
=============================================================================*/

-- Q49. Find employees earning above their own department average.
SELECT e.*
FROM Employee e
WHERE e.Salary > (
    SELECT AVG(x.Salary)
    FROM Employee x
    WHERE x.Dept = e.Dept
);

/* Assumed slide schema for Q50-Q51:
   PC(Model, Maker)
   Laptop(Model, Maker)
*/

-- Q50. Find PC makers that also make at least one Laptop.
SELECT DISTINCT pc.Maker
FROM PC pc
WHERE EXISTS (
    SELECT 1
    FROM Laptop l
    WHERE l.Maker = pc.Maker
);

-- Q51. Find PC makers that make no Laptop.
SELECT DISTINCT pc.Maker
FROM PC pc
WHERE NOT EXISTS (
    SELECT 1
    FROM Laptop l
    WHERE l.Maker = pc.Maker
);

/* Assumed standard PC schema for Q52:
   PC(Model, Speed, RAM, HD, Price)
*/

-- Q52. Find model(s) having the maximum PC speed.
SELECT Model
FROM PC
WHERE Speed = (
    SELECT MAX(Speed)
    FROM PC
);

-- Equivalent ALL solution.
SELECT Model
FROM PC
WHERE Speed >= ALL (
    SELECT Speed
    FROM PC
);


/*=============================================================================
 8. SUBQUERY IN FROM  [Lecture 11]
=============================================================================*/

/* Assumed schema:
   Product(Maker, Model, Type)
   PC(Model, Speed, RAM, HD, Price)
   Laptop(Model, Speed, RAM, HD, Screen, Price)
*/

-- Q53. Find makers having at least two PC/Laptop models with speed >= 2.0.
SELECT Maker
FROM (
    SELECT p.Maker,
           pc.Model
    FROM Product p
    JOIN PC pc ON p.Model = pc.Model
    WHERE pc.Speed >= 2.0

    UNION

    SELECT p.Maker,
           l.Model
    FROM Product p
    JOIN Laptop l ON p.Model = l.Model
    WHERE l.Speed >= 2.0
) Fast_Computer
GROUP BY Maker
HAVING COUNT(Model) >= 2;

-- Q54. Find makers having at least two PCs with speed >= 2.0.
SELECT p.Maker
FROM Product p
JOIN PC pc ON p.Model = pc.Model
WHERE pc.Speed >= 2.0
GROUP BY p.Maker
HAVING COUNT(DISTINCT pc.Model) >= 2;

-- Q55. Find makers having at least two Laptops with speed >= 2.0.
SELECT p.Maker
FROM Product p
JOIN Laptop l ON p.Model = l.Model
WHERE l.Speed >= 2.0
GROUP BY p.Maker
HAVING COUNT(DISTINCT l.Model) >= 2;

-- Q56. Alternative: combine PC/Laptop into a derived table first.
SELECT p.Maker
FROM Product p
JOIN (
    SELECT Model, Speed FROM PC
    UNION
    SELECT Model, Speed FROM Laptop
) Computer ON p.Model = Computer.Model
WHERE Computer.Speed >= 2.0
GROUP BY p.Maker
HAVING COUNT(DISTINCT Computer.Model) >= 2;


/*=============================================================================
 9. ATTRIBUTE-BASED CHECK CONSTRAINTS  [Lecture 06, CT pages]
=============================================================================*/

-- Q57. Create a Laptop table where speed must be at least 2.0.
CREATE TABLE Laptop_Check_1 (
    Model NUMBER PRIMARY KEY,
    Speed NUMBER(4,2) CHECK (Speed >= 2.0)
);

-- Q58. Create a Printer table allowing only laser, ink-jet, or bubble-jet.
CREATE TABLE Printer_Check_1 (
    Model NUMBER PRIMARY KEY,
    Type VARCHAR2(20)
        CHECK (Type IN ('laser', 'ink-jet', 'bubble-jet'))
);

/* Q59. Require Product.Model to appear in PC, Laptop, or Printer.
   Slide/standard-SQL concept only: Oracle does NOT permit subqueries in CHECK.

CREATE TABLE Product_Check_Attribute (
    Maker VARCHAR2(20),
    Model NUMBER CHECK (
        Model IN (
            SELECT Model FROM PC
            UNION
            SELECT Model FROM Laptop
            UNION
            SELECT Model FROM Printer
        )
    ),
    Type VARCHAR2(20)
);
*/


/*=============================================================================
 10. TUPLE-BASED CHECK CONSTRAINTS  [Lecture 06, CT pages]
=============================================================================*/

/* Implication conversion:
   P -> Q  is equivalent to  NOT P OR Q.
*/

-- Q60. If a department head is male, the name must not start with 'Ms.'.
CREATE TABLE Department_Check_1 (
    Dept_ID NUMBER PRIMARY KEY,
    Head_Name VARCHAR2(60),
    Gender CHAR(1),
    CHECK (Gender <> 'M' OR Head_Name NOT LIKE 'Ms.%')
);

-- Q61. A PC with speed below 2.0 must cost at most 800.
-- speed < 2.0 -> price <= 800
CREATE TABLE PC_Check_1 (
    Model NUMBER PRIMARY KEY,
    Speed NUMBER(4,2),
    Price NUMBER(10,2),
    CHECK (Speed >= 2.0 OR Price <= 800)
);

-- Q62. A Laptop with screen below 15 must have HD >= 40 or Price < 1000.
-- screen < 15 -> (hd >= 40 OR price < 1000)
CREATE TABLE Laptop_Check_2 (
    Model NUMBER PRIMARY KEY,
    Screen NUMBER(4,1),
    HD NUMBER,
    Price NUMBER(10,2),
    CHECK (Screen >= 15 OR HD >= 40 OR Price < 1000)
);

/* Q63. If Product.Type is pc/laptop/printer, Model must exist in that table.
   Tuple-based because Type and Model are checked together.
   Slide/standard-SQL concept only: Oracle does NOT permit subqueries in CHECK.

CREATE TABLE Product_Check_Tuple (
    Maker VARCHAR2(20),
    Model NUMBER,
    Type VARCHAR2(20),
    CHECK (
           (Type = 'pc'
            AND Model IN (SELECT Model FROM PC))
        OR (Type = 'laptop'
            AND Model IN (SELECT Model FROM Laptop))
        OR (Type = 'printer'
            AND Model IN (SELECT Model FROM Printer))
    )
);
*/


/*=============================================================================
 11. VERY SHORT CT MEMORY BLOCK
=============================================================================*/

/*
 Cross product:       every left row with every right row.
 Natural join:        automatically matches every same-named column.
 Inner join:          matching rows only.
 Left join:           matches + left dangling rows.
 Right join:          matches + right dangling rows.
 Full join:           matches + dangling rows from both sides.

 UNION:               either result, duplicates removed.
 INTERSECT:           common result.
 MINUS:               first result but not second.

 NULL arithmetic:     NULL.
 NULL comparison:     UNKNOWN.
 WHERE keeps:         TRUE only.

 COUNT(*):            all rows.
 COUNT(column):       non-NULL values.
 COUNT(DISTINCT col): distinct non-NULL values.
 WHERE:               filters rows before GROUP BY.
 HAVING:              filters groups after GROUP BY.

 ALL:                 condition must hold for every returned value.
 ANY:                 condition must hold for at least one returned value.
 EXISTS:              subquery returns at least one row.
 NOT EXISTS:          subquery returns no row.
 Correlated subquery: references the outer query row.

 Attribute CHECK:     normally restricts one attribute.
 Tuple CHECK:         may compare multiple attributes of one row.
 P -> Q:              NOT P OR Q.
*/
