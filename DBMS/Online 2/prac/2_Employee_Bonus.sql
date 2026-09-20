select e.name as name, b.bonus as bonus
from Employee e
Left Join Bonus b
    ON e.empId= b.empId
Where b.bonus< 1000 and b.bonus is NULL