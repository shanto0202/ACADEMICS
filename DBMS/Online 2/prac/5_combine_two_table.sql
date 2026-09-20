/* Write your PL/SQL query statement below */
select p.firstName, p.lastName, a.city, a.state
from Person p
Left Outer Join Address a
ON p.personId=a.personId