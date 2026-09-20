/* Write your PL/SQL query statement below */
select w2.id as id
from Weather w1, Weather w2
where w2.recordDate - w1.recordDate = 1
and w1.temperature < w2.temperature