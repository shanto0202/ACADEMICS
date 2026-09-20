select customer_number
from
    (select customer_number
    from Orders
    Group by customer_number
    order by count(*) Desc
    )
where rownum= 1