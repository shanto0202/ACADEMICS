select s.name as name
from SalesPerson s
where s.sales_id Not IN (
    select o.sales_id
    from Orders O
    where o.com_id IN (
    select c.com_id
    from Company c
    where c.name='RED'
    )
)