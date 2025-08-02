#database/mysql 

```sql
-------------------------- column --------------------------

alter table info1
add column recipient varchar(42) not null default '' after amount, -- `after amount` == put column after column 'amount'
add column name varchar(50) not null;

alter table info1
add column id int auto_increment primary key first;  -- 'first' == put column as first column

alter table info1
modify column name varchar(42) not null;

alter table info1
rename column name to name1;

alter table info1
drop column name;

---------------------------- index -----------------------------------------

-- when you create an index on a column, MySQL creates and maintains a special, separate data structure
-- this structure stores two key things: 1. the values from the indexed column  2. a 'pointer' or reference back to the row in main table
--  where each value occurs
-- the data in index is kept sorted typically using data-structure called B-Tree; this sorting allows MySQL to find specific values very
--  quickly, similar to how you can find a word in a dictionary
-- when you run a query with a `where` clause on a indexed column, MySQL's query optimizer realizes it can use index
--  it searches index for the value, typically taking logarithmic time complexity O(log n) instead of linear time O(n) for a full table scan

-- index_name must be unique 'only within the table' in which it is created; not need to be unique across entire database
ALTER TABLE your_table_name ADD INDEX index_name (column_name);
ALTER TABLE balance ADD INDEX idx_userId (userId);

------------------------------- unique, foreign-key -----------------------------

-- single column
alter table info1
add constraint unique_info1_name unique (name);

-- combination of columns
ALTER TABLE your_table_name
add constraint unique_combination unique (column1, column2);

create table info2(
   info1_id int not null
);

-- suppose each row in info2 references to multiple rows in info1
create table joint_table (
    info2_id INT,
    info1_id INT,
    foreign key (info2_id) references info2(id),
    foreign key (info1_id) references info1(id),
    --primary key (info2_id, info1_id),
    unique (service_request_id, withdrawal_id)
);

alter table info2
add constraint fk_info2_info1
foreign key (info1_id) references info1(id);
-- forign key have table scope (foreign needs to be within table, but need not to be unique in whole database)

alter table donation
drop foreign key donation_donor_id;

------------------------------ single JOIN ON ----------------------------------------------

SELECT columns  -- select given columns
FROM table1     -- from table1
JOIN table2     -- wait, first look at table2
ON table1.column = table2.column; -- consider rows only where table1's column value is equal to table2's column value
-- it's a common practice to mention table mentioned after "FROM" to use on left side of "=" after "ON"


-- join types: left join, right join, inner join, full join
-- now to get all info1 rows referenced in a single info2 row, we can use following query
select info1.id, info1.name
from info1
join joint_table ON info1.id = joint_table.info1_id  -- join without prefix == inner join
where joint_table.info2_id = [specific_info2_id];


update refund_request
join donor on refund_request.user_id = user.id
set refund_request.user_clerkid = user.clerk_id;

------------------------------ double JOIN ON ----------------------------------------------

SELECT DISTINCT service_request.*
FROM service_request
JOIN distributed_funds ON service_request.id = distributed_funds.service_request_id
JOIN donation ON distributed_funds.donation_id = donation.id
WHERE donation.donor_id = 3;

------------------------------ UNION ----------------------------------------------
-- UNION removes duplicate rows from the final result set.
-- UNION ALL keeps all rows, including duplicates.

(SELECT
    'debit' AS type,
    CONCAT('d-', df.id) AS unique_id,
    df.amount,
    df.created_at
FROM
    distributed_funds df
JOIN
    donation d ON df.transaction_id = d.id
WHERE
    d.donor_id = 15)

UNION ALL

(SELECT
    'credit' AS type,
    CONCAT('c-', d.id) AS unique_id,
    d.currency_amt AS amount,
    d.created_at
FROM
    donation d
WHERE
    d.donor_id = 15)

ORDER BY
    created_at ASC
LIMIT 10; 
```