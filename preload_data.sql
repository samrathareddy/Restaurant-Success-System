
-- Sample customers
INSERT INTO customers (cust_id, cust_firstname, cust_lastname) VALUES
(1, 'John', 'Doe'),
(2, 'Jane', 'Smith');

-- Sample addresses
INSERT INTO address (delivery_address1, delivery_address2, delivery_city, delivery_zipcode) VALUES
('123 Main St', '', 'Cleveland', '44114'),
('456 Park Ave', 'Apt 7B', 'Columbus', '43215');

-- Sample items
INSERT INTO item (item_id, sku, item_name, item_cat, item_size, item_price) VALUES
('ITM001', 'SKU001', 'Cheeseburger', 'Main Course', 'Medium', 8.99),
('ITM002', 'SKU002', 'Veggie Pizza', 'Main Course', 'Large', 12.50);

-- Sample inventory
INSERT INTO inventory (item_id, quantity) VALUES
('ITM001', 50),
('ITM002', 30);

-- Sample orders
INSERT INTO orders (order_id, created_at, item_id, quantity, cust_id, delivery, add_id) VALUES
('ORD001', '2025-06-07 12:34:56', 'ITM002', 1, 1, 1, 1),
('ORD002', '2025-06-07 13:15:20', 'ITM001', 2, 2, 0, NULL);
