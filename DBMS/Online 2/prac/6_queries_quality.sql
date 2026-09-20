select query_name,
    round(sum(quality)/count(*),2) as quality,
    round(sum(poor)/count(*)*100,2) as poor_query_percentage
from
    (
        select query_name,
        rating/position as quality,
        case
            when rating< 3
            then 1
            else 0
            end as poor
        from Queries
    )
Group by query_name