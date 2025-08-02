#database/mysql 

```sql
create table info1(
  id int auto_increment primary key,
  userId int unsigned,
  name varchar(30) not null,
  amount decimal(14,4) not null,
  completed bool not null default false,
  status enum('verified', 'rejected', 'pending') not null default 'pending',
  wallet_address varchar(42) null default null,
  created_at timestamp not null default current_timestamp,
  updated_at timestamp not null default current_timestamp on update current_timestamp,
  birth_date date not null,
  expiry_at timestamp not null
);

rename table info1 to info3;

drop table info1;   -- delete table info1
```