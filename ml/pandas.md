- pandas is the most popular Python library for data analysis

```python
import pandas as pd

# create a table with two columns
cars = pd.Series(['BMW', 'Toyota', 'Honda'])
colors = pd.Series(['Red', 'Blue', 'White'])
car_data = pd.DataFrame({'Car': cars, 'Color': colors})

# read, write
car_sales = pd.read_csv('./car-sales.csv')
car_sales.to_csv('exported-car-sales.csv', index=False)
car_sales.dtypes    # data types of columns
car_sales.columns
len(car_sales)     # get number of rows
car_sales['Doors'].sum()    # sum of all numbers in doors column
car_sales.head(7)    # view top 7 rows
car_sales.tail(7)    # view last 7 rows
car_sales.loc[3]     # view row at index 3
car_sales.iloc[3]    # view row at position 3, refers to line-number
```

## 2 core objects in pandas: 
### 1. The DataFrame
- A DataFrame is a table. 
- DataFrame entries can be integers, strings
- It contains an array of individual entries, each of which has a certain value. Each entry corresponds to a row(or record) and a column.
	```python
	pd.DataFrame({'Yes': [50, 21], 'No': [131, 2]})
	
	|  |Yes|No |
	|--|---|---|
	|0 | 50|131|
	|1 | 21|  2|
	```
- The list of row labels used in a DataFrame is known as an **Index**. We can assign values to it by using an `index` parameter in our constructor
	```python
	pd.DataFrame({'Bob': ['I liked it.', 'It was awful.'], 
	'Sue': ['Pretty good.', 'Bland.']},
	index=['Product A', 'Product B'])
	```
	
	```text
	Bob 	        Sue
	Product A 	I liked it. 	Pretty good.
	Product B 	It was awful. 	Bland.
	```
### 2. The Series
- If a DataFrame is a table, a Series is a list. And in fact you can create one with nothing more than a list:
	- `pd.Series([1, 2, 3, 4, 5])`
	```text
	0    1
	1    2
	2    3
	3    4
	4    5
	dtype: int64
	```
- A Series is, in essence, a single column of a DataFrame. So you can  assign row labels to the Series the same way as before, using an `index` parameter. However, a Series does not have a column name, it only has one overall `name`:
	- `pd.Series([30, 35, 40], index=['2015 Sales', '2016 Sales', '2017 Sales'], name='Product A')`
	```text
	2015 Sales    30
	2016 Sales    35
	2017 Sales    40
	Name: Product A, dtype: int64
	```
- The Series and the DataFrame are intimately related. It's helpful to  think of a DataFrame as actually being just a bunch of Series "glued  together".
## read files
```python
pd.set_option('display.max_rows', 5)
# read the data into a DataFrame
wine_reviews = pd.read_csv("../input/wine-reviews/winemag-data-130k-v2.csv")

# check how large the resulting DataFrame is
wine_reviews.shape 
# (129971, 14)

# grab first five rows
wine_reviews.head()


# by default, pandas add new column to index rows, to avoid that column you can pass `index_col=0`
wine_reviews = pd.read_csv("../input/wine-reviews/winemag-data-130k-v2.csv", index_col=0) 
```

