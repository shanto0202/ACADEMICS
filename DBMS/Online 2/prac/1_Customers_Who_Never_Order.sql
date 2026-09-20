select c.name as Customers
from Customers c
Left Join Orders o
    ON o.customerId=c.id
where o.id is NULL;