
-- Restaurant Success System SQL Schema and Sample Data

-- Table: customers
CREATE TABLE customers (
    cust_id INT PRIMARY KEY,
    cust_firstname VARCHAR(50),
    cust_lastname VARCHAR(50)
);

INSERT INTO customers VALUES
(1, 'John', 'Doe'),
(2, 'Jane', 'Smith');

-- Table: address
CREATE TABLE address (
    add_id INT PRIMARY KEY,
    delivery_address1 VARCHAR(200),
    delivery_address2 VARCHAR(200),
    delivery_city VARCHAR(50),
    delivery_zipcode VARCHAR(20)
);

INSERT INTO address VALUES
(1, '123 Main St', NULL, 'Cleveland', '44114'),
(2, '456 Park Ave', 'Apt 7B', 'Columbus', '43215');

-- Table: item
CREATE TABLE item (
    item_id VARCHAR(10) PRIMARY KEY,
    sku VARCHAR(20),
    item_name VARCHAR(100),
    item_cat VARCHAR(100),
    item_size VARCHAR(10),
    item_price DECIMAL(10,2)
);

INSERT INTO item VALUES
('ITM001', 'SKU001', 'Cheeseburger', 'Main Course', 'Medium', 8.99),
('ITM002', 'SKU002', 'Veggie Pizza', 'Main Course', 'Large', 12.50);

-- Table: ingredient
CREATE TABLE ingredient (
    ing_id VARCHAR(10) PRIMARY KEY,
    ing_name VARCHAR(200),
    ing_weight INT,
    ing_meas VARCHAR(20),
    ing_price DECIMAL(5,2)
);

INSERT INTO ingredient VALUES
('ING001', 'Cheese', 200, 'grams', 1.50),
('ING002', 'Tomato Sauce', 100, 'ml', 0.75);

-- Table: recipe
CREATE TABLE recipe (
    row_id INT PRIMARY KEY,
    recipe_id VARCHAR(20),
    ing_id VARCHAR(10),
    quantity INT,
    FOREIGN KEY (recipe_id) REFERENCES item(item_id),
    FOREIGN KEY (ing_id) REFERENCES ingredient(ing_id)
);

INSERT INTO recipe VALUES
(1, 'ITM002', 'ING001', 2),
(2, 'ITM002', 'ING002', 1);

-- Table: inventory
CREATE TABLE inventory (
    inv_id INT PRIMARY KEY,
    item_id VARCHAR(10),
    quantity INT,
    FOREIGN KEY (item_id) REFERENCES item(item_id)
);

INSERT INTO inventory VALUES
(1, 'ITM001', 50),
(2, 'ITM002', 30);

-- Table: staff
CREATE TABLE staff (
    staff_id VARCHAR(20) PRIMARY KEY,
    first_name VARCHAR(50),
    last_name VARCHAR(50),
    position VARCHAR(100),
    hourly_rate DECIMAL(5,2)
);

INSERT INTO staff VALUES
('S001', 'Alice', 'Johnson', 'Chef', 18.50),
('S002', 'Bob', 'Williams', 'Server', 15.00);

-- Table: shift
CREATE TABLE shift (
    shift_id VARCHAR(20) PRIMARY KEY,
    day_of_week VARCHAR(10),
    start_time TIME,
    end_time TIME
);

INSERT INTO shift VALUES
('SH001', 'Monday', '10:00:00', '18:00:00'),
('SH002', 'Tuesday', '12:00:00', '20:00:00');

-- Table: rota
CREATE TABLE rota (
    row_id INT PRIMARY KEY,
    rota_id VARCHAR(20),
    date DATETIME,
    shift_id VARCHAR(20),
    staff_id VARCHAR(20),
    FOREIGN KEY (shift_id) REFERENCES shift(shift_id),
    FOREIGN KEY (staff_id) REFERENCES staff(staff_id)
);

INSERT INTO rota VALUES
(1, 'R001', '2025-06-10', 'SH001', 'S001'),
(2, 'R002', '2025-06-11', 'SH002', 'S002');

-- Table: orders
CREATE TABLE orders (
    row_id INT PRIMARY KEY,
    order_id VARCHAR(10),
    created_at DATETIME,
    item_id VARCHAR(10),
    quantity INT,
    cust_id INT,
    delivery BOOLEAN,
    add_id INT,
    FOREIGN KEY (item_id) REFERENCES item(item_id),
    FOREIGN KEY (cust_id) REFERENCES customers(cust_id),
    FOREIGN KEY (add_id) REFERENCES address(add_id)
);

INSERT INTO orders VALUES
(1, 'ORD001', '2025-06-07 12:34:56', 'ITM002', 1, 1, TRUE, 1),
(2, 'ORD002', '2025-06-07 13:15:20', 'ITM001', 2, 2, FALSE, NULL);

-- Sample Queries

-- 1. Most ordered items
SELECT item_name, SUM(o.quantity) AS total_ordered
FROM orders o
JOIN item i ON o.item_id = i.item_id
GROUP BY item_name
ORDER BY total_ordered DESC;

-- 2. Staff schedule on a specific date
SELECT s.first_name, s.last_name, sh.day_of_week, sh.start_time, sh.end_time
FROM rota r
JOIN staff s ON r.staff_id = s.staff_id
JOIN shift sh ON r.shift_id = sh.shift_id
WHERE r.date = '2025-06-10';

-- 3. Low inventory items
SELECT i.item_name, inv.quantity
FROM inventory inv
JOIN item i ON inv.item_id = i.item_id
WHERE inv.quantity < 10;

-- 4. Orders with delivery details
SELECT o.order_id, c.cust_firstname, c.cust_lastname, a.delivery_address1, a.delivery_city
FROM orders o
JOIN customers c ON o.cust_id = c.cust_id
JOIN address a ON o.add_id = a.add_id
WHERE o.delivery = TRUE;
