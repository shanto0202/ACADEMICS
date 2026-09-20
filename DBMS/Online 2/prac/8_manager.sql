select e1.name as name
from Employee e1
join Employee e2
ON e1.id= e2.managerId
group by e1.name, ei.id
having count(e2.id)>=5